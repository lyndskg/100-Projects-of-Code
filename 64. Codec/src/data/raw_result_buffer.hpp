#ifndef DETAIL_RAW_RESULT_BUFFER
#define DETAIL_RAW_RESULT_BUFFER

#include <stdint.h> // for size_t
#include <stdlib.h> // for abort()

#include "access.hpp"

namespace cppcodec {
    namespace data {
        class raw_result_buffer {
        public:
            raw_result_buffer(char* data, size_t capacity)
                : m_ptr(data + capacity)
                , m_begin(data)
            {}

            CPPCODEC_ALWAYS_INLINE void push_back(char c) { *m_ptr = c; ++m_ptr; }
            CPPCODEC_ALWAYS_INLINE size_t size() const { return m_ptr - m_begin; }
            CPPCODEC_ALWAYS_INLINE void resize(size_t size) { m_ptr = m_begin + size; }

        private:
            char* m_ptr;
            char* m_begin;
        }; // class raw_result_buffer

        template <> inline void init<raw_result_buffer>(
                raw_result_buffer& result, empty_result_state&, size_t capacity) {
            // This version of init() doesn't do a reserve(), and instead checks whether the
            // initial size (capacity) is enough before resetting m_ptr to m_begin.
            // The codec is expected not to exceed this capacity.
            if (capacity > result.size()) {
                abort();
            } // if 
            result.resize(0);
        } // init<>
        
        template <> inline void finish<raw_result_buffer>(raw_result_buffer&, empty_result_state&) { }

    } // namespace data
} // namespace cppcodec

#endif