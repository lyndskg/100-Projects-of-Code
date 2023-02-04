#ifndef DETAIL_CONFIG_HPP
#define DETAIL_CONFIG_HPP

#ifndef __has_attribute
  #define __has_attribute(x) 0
#endif

#if __GNUC__ || __has_attribute(always_inline)
#define CPPCODEC_ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#define CPPCODEC_ALWAYS_INLINE inline __forceinline
#else
#define CPPCODEC_ALWAYS_INLINE inline
#endif

#endif // DETAIL_CONFIG_HPP