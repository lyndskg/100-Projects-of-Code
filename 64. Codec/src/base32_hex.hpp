#ifndef BASE32_HEX
#define BASE32_HEX

#include "detail/codec.hpp"
#include "detail/base32.hpp"

namespace cppcodec {
    namespace detail {
        // RFC 4648 also specifies a hex encoding system which uses 0-9, then A-V.
        static constexpr const char base32_hex_alphabet[] = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'
        }; // base32_hex_alphabet[]

        class base32_hex {
        public:
            template <typename Codec> using codec_impl = stream_codec<Codec, base32_hex>;

            static CPPCODEC_ALWAYS_INLINE constexpr size_t alphabet_size() {
                static_assert(sizeof(base32_hex_alphabet) == 32, "base32 alphabet must have 32 values");
                
                return sizeof(base32_hex_alphabet);
            } // alphabet_size()

            static CPPCODEC_ALWAYS_INLINE constexpr char symbol(alphabet_index_t idx) {
                return base32_hex_alphabet[idx];
            } // symbol()

            static CPPCODEC_ALWAYS_INLINE constexpr char normalized_symbol(char c) {
                // Lower-case letters are accepted, though not generally expected.
                return (c >= 'a' && c <= 'v') ? (c - 'a' + 'A') : c;
            } // normalized_symbol()

            static CPPCODEC_ALWAYS_INLINE constexpr bool generates_padding() { return true; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool requires_padding() { return true; }
            static CPPCODEC_ALWAYS_INLINE constexpr char padding_symbol() { return '='; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_padding_symbol(char c) { return c == '='; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_eof_symbol(char c) { return c == '\0'; }

            // RFC4648 does not specify any whitespace being allowed in base32 encodings.
            static CPPCODEC_ALWAYS_INLINE constexpr bool should_ignore(char) { return false; }
        }; // class base32_hex
    } // namespace detail

    using base32_hex = detail::codec<detail::base32<detail::base32_hex>>;
} // namespace cppcodec

#endif // BASE32_HEX