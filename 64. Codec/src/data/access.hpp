#ifndef DETAIL_DATA_ACCESS
#define DETAIL_DATA_ACCESS

#include <stdint.h> // for size_t
#include <string> // for static_assert() checking that string will be optimized
#include <type_traits> // for std::enable_if, std::remove_reference, and such
#include <utility> // for std::declval
#include <vector> // for static_assert() checking that vector will be optimized

#include "../detail/config.hpp" // for CPPCODEC_ALWAYS_INLINE

namespace cppcodec {
    namespace data {

        // This file contains a number of templated data accessors that can be
        // implemented in the cppcodec::data namespace for types that don't fulfill
        // the default type requirements:
        // For result types: init(Result&, ResultState&, size_t capacity),
        //     put(Result&, ResultState&, char), finish(Result&, State&)
        // For const (read-only) types: char_data(const T&)
        // For both const and result types: size(const T&)

        template <typename T>
        CPPCODEC_ALWAYS_INLINE size_t size(const T& t) { return t.size(); }

        template <typename T, size_t N>
        CPPCODEC_ALWAYS_INLINE constexpr size_t size(const T (&t)[N]) noexcept {
            return (void)t, N * sizeof(t[0]);
        } // size()

        class general_t {};
        class specific_t : public general_t {};

        class empty_result_state {
            template <typename Result>
            CPPCODEC_ALWAYS_INLINE void size(const Result& result) { return size(result); }
        }; // class empty_result_state

        // SFINAE: Generic fallback in case no specific state function applies.
        template <typename Result>
        CPPCODEC_ALWAYS_INLINE empty_result_state create_state(Result&, general_t) {
            return empty_result_state();
        } // create_state()

        // Generic templates for containers: Use these init()/put()/finish()
        // implementations if no specialization was found.

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void init(Result& result, empty_result_state&, size_t capacity) {
            result.resize(0);
            result.reserve(capacity);
        } // init()

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void finish(Result&, empty_result_state&) {
            // Default is to push_back(), which already increases the size.
        } // finish()

        // For the put() default implementation, we try calling push_back() with either uint8_t or char,
        // whichever compiles. Scary-fancy template magic from http://stackoverflow.com/a/1386390.
        namespace fallback {
            struct flag { char c[2]; }; // sizeof > 1
            flag put_uint8(...);

            int operator,(flag, flag);

            template <typename T> void operator,(flag, T&); // map everything else to void
            char operator,(int, flag); // sizeof 1
        } // namespace fallback

        template <typename Result> inline void put_uint8(Result& result, uint8_t c) { result.push_back(c); }

        template <bool> struct put_impl;
        template <> struct put_impl<true> { // put_uint8() available
            template<typename Result>
            static CPPCODEC_ALWAYS_INLINE void put(Result& result, uint8_t c) {
                put_uint8(result, c);
            } // put()
        }; // template struct put_impl<true>

        template <> struct put_impl<false> { // put_uint8() not available
            template<typename Result>
            static CPPCODEC_ALWAYS_INLINE void put(Result& result, uint8_t c) {
                result.push_back(static_cast<char>(c));
            } // put()
        }; // template struct put_impl<false>

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void put(Result& result, empty_result_state&, uint8_t c) {
            using namespace fallback;
            put_impl<sizeof(fallback::flag(), put_uint8(result, c), fallback::flag()) != 1>::put(result, c);
        } // put()

        // Specialization for container types with direct mutable data access,
        // e.g. std::vector<uint8_t>.
        //
        // The expected way to specialize is to draft a new xyz_result_state type and
        // return an instance of it from a create_state() template specialization.
        // You can then create overloads for init(), put() and finish()
        // for the new result state type.
        //
        // If desired, a non-templated overload for both specific types
        // (result & state) can be added to tailor it to that particular result type.

        template <typename T>
        constexpr auto data_is_mutable(T* t) -> decltype(t->data()[size_t(0)] = 'x', bool()) {
            return (void)t, true;
        } // data_is_mutable()

        constexpr bool data_is_mutable(...) { return false; }

        template <typename Result>
        class direct_data_access_result_state {
        public:
            CPPCODEC_ALWAYS_INLINE void init(Result& result, size_t capacity) {
                // reserve() may not actually allocate the storage right away,
                // and it isn't guaranteed that it will be untouched upon the
                //.next resize(). In that light, resize from the start and
                // slightly reduce the size at the end if necessary.
                result.resize(capacity);

                // result.data() may perform a calculation to retrieve the address.
                // E.g. std::string (since C++11) will use small string optimization,
                // so it needs to check if it's using allocated data or (ab)using
                // its own member variables interpreted as char array.
                // (This result_state is used for std::string starting with C++17.)
                // Conditional code paths are slow so we only do it once, at the start.
                m_buffer = result.data();
            } // init()

            CPPCODEC_ALWAYS_INLINE void put(Result&, char c) {
                m_buffer[m_offset++] = c;
            } // put()

            CPPCODEC_ALWAYS_INLINE void finish(Result& result) {
                result.resize(m_offset);
            } // finish()

            CPPCODEC_ALWAYS_INLINE size_t size(const Result&) {
                return m_offset;
            } // size()

        private:
            // Make sure to get the mutable buffer decltype by using assignment.
            typename std::remove_reference<
                    decltype(std::declval<Result>().data()[size_t(0)] = 'x')>::type* m_buffer;
            size_t m_offset = 0;
        }; // class direct_data_access_result_state

        // SFINAE: Select a specific state based on the result type and possible result state type.
        // Implement this if direct data access (`result.data()[0] = 'x') isn't already possible
        // and you want to specialize it for your own result type.
        // Note: The enable_if should ideally be part of the class declaration,
        //       but Visual Studio C++ will not compile it that way.
        //       Have it here in the factory function instead.
        template <typename Result,
                typename = typename std::enable_if<
                        data_is_mutable(static_cast<Result*>(nullptr))>::type>
        CPPCODEC_ALWAYS_INLINE direct_data_access_result_state<Result> create_state(Result&, specific_t) {
            return direct_data_access_result_state<Result>();
        } // create_state()

        static_assert(std::is_same<
                decltype(create_state(*static_cast<std::vector<uint8_t>*>(nullptr), specific_t())),
                direct_data_access_result_state<std::vector<uint8_t>>>::value,
                "std::vector<uint8_t> must be handled by direct_data_access_result_state");

        // Specialized init(), put() and finish() functions for direct_data_access_result_state.
        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void init(Result& result, direct_data_access_result_state<Result>& state, size_t capacity) {
            state.init(result, capacity);
        } // init()

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void put(Result& result, direct_data_access_result_state<Result>& state, char c) {
            state.put(result, c);
        } // put()

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void finish(Result& result, direct_data_access_result_state<Result>& state) {
            state.finish(result);
        } // finish()

        // Specialization for container types with direct mutable array access,
        // e.g. std::string. This is generally faster because bound checks are
        // minimal and operator[] is more likely noexcept. In addition,
        // std::string::push_back() needs to write a null character on every
        // expansion, which should be more efficient when done in bulk by resize().
        //
        // Compared to the above, tracking an extra offset variable is cheap.

        template <typename T>
        constexpr auto array_access_is_mutable(T* t) -> decltype((*t)[size_t(0)] = 'x', bool()) {
            return (void)t, true;
        } // array_access_is_mutable()

        constexpr bool array_access_is_mutable(...) { return false; }

        template <typename Result>
        class array_access_result_state {
        public:
            CPPCODEC_ALWAYS_INLINE void init(Result& result, size_t capacity) {
                // reserve() may not actually allocate the storage right away,
                // and it isn't guaranteed that it will be untouched upon the
                //.next resize(). In that light, resize from the start and
                // slightly reduce the size at the end if necessary.
                result.resize(capacity);
            } // init() 

            CPPCODEC_ALWAYS_INLINE void put(Result& result, char c) {
                result[m_offset++] = c;
            } // put()

            CPPCODEC_ALWAYS_INLINE void finish(Result& result) {
                result.resize(m_offset);
            } // finish() 

            CPPCODEC_ALWAYS_INLINE size_t size(const Result&) {
                return m_offset;
            } // size()

        private:
            size_t m_offset = 0;
        }; // class array_access_result_state

        // SFINAE: Select a specific state based on the result type and possible result state type.
        // Note: The enable_if should ideally be part of the class declaration,
        //       but Visual Studio C++ will not compile it that way.
        //       Have it here in the factory function instead.
        template <typename Result,
                typename = typename std::enable_if<
                        !data_is_mutable(static_cast<Result*>(nullptr)) // no more than one template option
                        && array_access_is_mutable(static_cast<Result*>(nullptr))>::type>
        CPPCODEC_ALWAYS_INLINE array_access_result_state<Result> create_state(Result&, specific_t) {
            return array_access_result_state<Result>();
        } // create_state()

        #if __cplusplus >= 201703L || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
        static_assert(std::is_same<
            decltype(create_state(*static_cast<std::string*>(nullptr), specific_t())),
            direct_data_access_result_state<std::string>>::value,
            "std::string (C++17 and later) must be handled by direct_data_access_result_state");
        #elif __cplusplus < 201703 && !defined(_MSVC_LANG) // we can't trust MSVC to set this right
        static_assert(std::is_same<
                decltype(create_state(*static_cast<std::string*>(nullptr), specific_t())),
                array_access_result_state<std::string>>::value,
                "std::string (pre-C++17) must be handled by array_access_result_state");
        #endif

        // Specialized init(), put() and finish() functions for array_access_result_state.
        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void init(Result& result, array_access_result_state<Result>& state, size_t capacity) {
            state.init(result, capacity);
        } // init()

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void put(Result& result, array_access_result_state<Result>& state, char c) {
            state.put(result, c);
        } // put()

        template <typename Result>
        CPPCODEC_ALWAYS_INLINE void finish(Result& result, array_access_result_state<Result>& state) {
            state.finish(result);
        } // finish()

        // char_data() is only used to read, not for result buffers.
        template <typename T> inline const char* char_data(const T& t) {
            return reinterpret_cast<const char*>(t.data());
        } // char_data()

        template <typename T, size_t N> inline const char* char_data(const T (&t)[N]) noexcept {
            return reinterpret_cast<const char*>(&(t[0]));
        } // char_data()

        template <typename T> inline const uint8_t* uchar_data(const T& t) {
            return reinterpret_cast<const uint8_t*>(char_data(t));
        } // uchar_data()
        
    } // namespace data
} // namespace cppcodec

#endif