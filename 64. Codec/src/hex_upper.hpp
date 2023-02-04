#ifndef HEX_UPPER
#defineHEX_UPPER

#include "detail/codec.hpp"
#include "detail/hex.hpp"

namespace cppcodec {
    namespace detail {
        static constexpr const char hex_upper_alphabet[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'A', 'B', 'C', 'D', 'E', 'F'
        }; // hex_upper_alphabet[]

        class hex_upper {
        public:
            template <typename Codec> using codec_impl = stream_codec<Codec, hex_upper>;

            static CPPCODEC_ALWAYS_INLINE constexpr size_t alphabet_size() {
                static_assert(sizeof(hex_upper_alphabet) == 16, "hex alphabet must have 16 values");
                return sizeof(hex_upper_alphabet);
            } // alphabet_size()

            static CPPCODEC_ALWAYS_INLINE constexpr char symbol(alphabet_index_t index) {
                return hex_upper_alphabet[index];
            } // symbol()

            static CPPCODEC_ALWAYS_INLINE constexpr char normalized_symbol(char c) {
                // Hex decoding is always case-insensitive (even in RFC 4648), the question
                // is only for encoding whether to use upper-case or lower-case letters.
                return (c >= 'a' && c <= 'f') ? (c - 'a' + 'A') : c;
            } // normalized_symbol()

            static CPPCODEC_ALWAYS_INLINE constexpr bool generates_padding() { return false; }
            
            // FIXME: doesn't require padding, but requires a multiple of the encoded block size (2)
            static CPPCODEC_ALWAYS_INLINE constexpr bool requires_padding() { return false; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_padding_symbol(char) { return false; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_eof_symbol(char c) { return c == '\0'; }

            // Sometimes hex strings include whitespace, but this variant forbids it.
            static CPPCODEC_ALWAYS_INLINE constexpr bool should_ignore(char) { return false; }
        }; // class hex_upper
    } // namespace detail

    using hex_upper = detail::codec<detail::hex<detail::hex_upper>>;
} // namespace cppcodec

#endif // HEX_UPPER