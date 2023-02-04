#ifndef BASE64_URL_UNPADDED
#define BASE64_URL_UNPADDED

#include "base64_url.hpp"

namespace cppcodec {
    namespace detail {
        class base64_url_unpadded : public base64_url {
        public:
            template <typename Codec> using codec_impl = stream_codec<Codec, base64_url_unpadded>;

            static CPPCODEC_ALWAYS_INLINE constexpr bool generates_padding() { return false; }
            static CPPCODEC_ALWAYS_INLINE constexpr bool requires_padding() { return false; }
        }; // class base64_url_unpadded
    } // namespace detail

    using base64_url_unpadded = detail::codec<detail::base64<detail::base64_url_unpadded>>;
} // namespace cppcodec

#endif // BASE64_URL_UNPADDED