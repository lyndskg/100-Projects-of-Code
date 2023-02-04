#ifndef BASE64_RFC4648
#define BASE64_RFC4648

#include "detail/codec.hpp"
#include "detail/base64.hpp"

namespace cppcodec {
    namespace detail {
        static constexpr const char base64_rfc4648_alphabet[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
        }; // base64_rfc4648_alphabet[]

        class base64_rfc4648 {
        public:
            template <typename Codec> using codec_impl = stream_codec<Codec, base64_rfc4648>;

            static CPPCODEC_ALWAYS_INLINE constexpr size_t alphabet_size() {
                static_assert(sizeof(base64_rfc4648_alphabet) == 64, "base64 alphabet must have 64 values");
                
                return sizeof(base64_rfc4648_alphabet);
            } // alphabet_size()

            static CPPCODEC_ALWAYS_INLINE constexpr char symbol(alphabet_index_t idx) {
                return base64_rfc4648_alphabet[idx];
            } // symbol()

            static CPPCODEC_ALWAYS_INLINE constexpr char normalized_symbol(char c) { return c; }

            static CPPCODEC_ALWAYS_INLINE constexpr bool generates_padding() { return true; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool requires_padding() { return true; }
            static CPPCODEC_ALWAYS_INLINE constexpr char padding_symbol() { return '='; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_padding_symbol(char c) { return c == '='; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool is_eof_symbol(char c) { return c == '\0'; }

            // RFC4648 does not specify any whitespace being allowed in base64 encodings.
            static CPPCODEC_ALWAYS_INLINE constexpr bool should_ignore(char) { return false; }
        }; // class base64_rfc4648  
    } // namespace detail

    using base64_rfc4648 = detail::codec<detail::base64<detail::base64_rfc4648>>;
} // namespace cppcodec

#endif // BASE64_RFC4648