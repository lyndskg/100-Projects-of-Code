#ifndef DETAIL_HEX
#define DETAIL_HEX

#include <stdint.h>
#include <stdlib.h> // for abort()

#include "../data/access.hpp"
#include "../parse_error.hpp"
#include "stream_codec.hpp"

namespace cppcodec {
    namespace detail {

        template <typename CodecVariant>
        class hex : public CodecVariant::template codec_impl<hex<CodecVariant>> {
        public:
            static inline constexpr uint8_t binary_block_size() { return 1; }
            static inline constexpr uint8_t encoded_block_size() { return 2; }

            static CPPCODEC_ALWAYS_INLINE constexpr uint8_t num_encoded_tail_symbols(uint8_t /*num_bytes*/) noexcept {
                // Hex encoding only works on full bytes so there are no tails,
                // no padding characters, and this function should (must) never be called.
                return 0;
            } // num_encoded_tail_symbols()

            template <uint8_t I>
            static CPPCODEC_ALWAYS_INLINE constexpr uint8_t index(
                    const uint8_t* b /*binary block*/) noexcept {
                static_assert(I >= 0 && I < encoded_block_size(),
                        "invalid encoding symbol index in a block");

                return (I == 0) ? (b[0] >> 4) // first 4 bits
                        : /*I == 1*/ (b[0] & 0xF); // last 4 bits
            } // index()

            // With only 2 bytes, enc<1> will always result in a full index() call and
            // enc<0> will be protected by a not-reached assertion, so we don't actually
            // care about index_last() except optimizing it out as good as possible.
            template <bool B>
            using uint8_if = typename std::enable_if<B, uint8_t>::type;

            template <uint8_t I>
            static CPPCODEC_ALWAYS_INLINE constexpr uint8_if<I == 0> index_last(
                    const uint8_t* /*binary block*/) noexcept {
                return 0;
            } // index_last()

            template <uint8_t I>
            static CPPCODEC_ALWAYS_INLINE uint8_if<I != 0> index_last(
                    const uint8_t* /*binary block*/) {
                throw std::domain_error("invalid last encoding symbol index in a tail");
            } // index_last()

            template <typename Result, typename ResultState>
            static CPPCODEC_ALWAYS_INLINE void decode_block(
                    Result& decoded, ResultState&, const alphabet_index_t* idx);

            template <typename Result, typename ResultState>
            static CPPCODEC_ALWAYS_INLINE void decode_tail(
                    Result& decoded, ResultState&, const alphabet_index_t* idx, size_t idx_len);
        }; // class hex


        template <typename CodecVariant>
        template <typename Result, typename ResultState>
        CPPCODEC_ALWAYS_INLINE void hex<CodecVariant>::decode_block(
                Result& decoded, ResultState& state, const alphabet_index_t* idx) {
            data::put(decoded, state, static_cast<uint8_t>((idx[0] << 4) | idx[1]));
        } // decode_block()

        template <typename CodecVariant>
        template <typename Result, typename ResultState>
        CPPCODEC_ALWAYS_INLINE void hex<CodecVariant>::decode_tail(
                Result&, ResultState&, const alphabet_index_t*, size_t) {
            throw invalid_input_length(
                    "odd-length hex input is not supported by the streaming octet decoder, "
                    "use a place-based number decoder instead");
        } // decode_tail()

    } // namespace detail
} // namespace cppcodec

#endif // DETAIL_HEX