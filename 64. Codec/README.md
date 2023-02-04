# 64. Codec

## Overview 

<ins>__Language__</ins>: C++  

<ins>__Completed on__</ins>: February 3rd, 2023 &mdash; PRESENT (Incomplete)

<b>Codec</b> is a header-only C++11 library comprised of (you guessed it...) codec software used to decode/encode various binary-to-text encoding schemes. Currently, the program supports base64, base64url, base32, base32hex, and hex (AKA base16) &mdash; in accordance with RFC 4648 and [Crockford's base32](http://www.crockford.com/base32.html). In terms of data types, it also supports raw pointers, `std::string`, and (templated) character vectors without unnecessary allocations.

This ended up being quite a hefty project, so its overarching framework is indeed heavily templated for the sake of recycling redundant code and for heightened flexibility. In terms of implementation, <b>Codec</b> is also largely inspired by Tplgy's [CppCodec](https://github.com/tplgy/cppcodec) &mdash; which offers an even more consistent, flexible API.
   

## To Do

While <b>Codec</b> is just about finished in terms of merely implementing all of its many files, the library as a whole necessitates further organization and a lot more formal commenting. 

With so many files, there are definitely a lot of bugs here and there. A good portion of time will definitely need to be dedicated towards testing and debugging everything.

## Usage

1. Import <b>Codec</b> into your project (copy, git submodule, etc.)
2. Add the <b>Codec</b> root directory to your build system's list of include directories.
3. Include headers and start using the API.

As a header-only library, no extra build step is needed. Alternatively, you may install the headers and build extra tools/tests with CMake.

## Variants

Expected standard use of <b>Codec</b>:

```C++
#include <src/base32_crockford.hpp>
#include <src/base64_rfc4648.hpp>
#include <iostream>

using namespace std;

int main() {
  using base32 = cppcodec::base32_crockford;
  using base64 = cppcodec::base64_rfc4648;

  vector<uint8_t> decoded = base64::decode("YW55IGNhcm5hbCBwbGVhc3VyZQ==");
  cout << "decoded size (\"any carnal pleasure\"): " << decoded.size() << '\n';
  cout << base32::encode(decoded) << endl; // "C5Q7J833C5S6WRBC41R6RSB1EDTQ4S8"
  
  return 0;
} // main()
```

<ins>__Currently Supported Codec Variants__</ins>:

### base64

* `base64_rfc4648` uses the PEM/MIME/UTF-7 alphabet, that is (in order)
  A-Z, a-z, 0-9 plus characters '+' and '/'. This is what's usually considered
  the "standard base64" that you see everywhere and requires padding ('=') but
  no line breaks. Whitespace and other out-of-alphabet symbols are regarded as
  a parse error.
* `base64_url` is the same as `base64_rfc4648` (and defined in the same RFC),
  but uses '-' (minus) and '_' (underscore) as special characters instead of
  '+' and '/'. This is safe to use for URLs and file names. Padding with '=' is
  required, it will be generated when encoding to a string and regarded as a
  parse error if it's not present when decoding.
* `base64_url_unpadded` variant is the same as `base64_url`, but '=' padding
  characters are optional. When encoding, no padding will be appended to the
  resulting string. Decoding accepts either padded or unpadded strings.

### base32
All base32 variants encode 5 bits as one (8-bit) character, which results in
an encoded length of roughly 160% (= 8/5). Their selling point is mainly
case-insensitive decoding, no special characters, and alphabets that can be
communicated via phone.

* `base32_rfc4648` implements the popular, standardized variant defined in
  RFC 4648. It uses the full upper-case alphabet A-Z for the first 26 values
  and the digit characters 2-7 for the last ten. Padding with '=' is required
  and makes the encoded string a multiple of 8 characters. The codec accepts
  no invalid symbols, so if you want to let the user enter base32 data then
  consider replacing numbers '0', '1' and '8' with 'O', 'I' and 'B' on input.
* `base32_crockford` implements [Crockford's base32](http://www.crockford.com/wrmg/base32.html).
  It's less widely used than the RFC 4648 alphabet, but offers a more carefully
  picked alphabet and also defines decoding similar characters 'I', 'i', 'L'
  'l' as '1' plus 'O' and 'o' as '0' so no care is required for user input.
  Crockford base32 does not use '=' padding. Checksums are not implemented.
* `base32_hex` is the logical extension of the hexadecimal alphabet, and also
  specified in RFC 4648. It uses the digit characters 0-9 for the first 10 values
  and the upper-case letters A-V for the remaining ones. The alphabet is
  conceptually simple, but contains all of the ambiguous number/letter pairs that
  the other variants try to avoid. It is also less suitable for verbal
  transmission. Padding with '=' is required and makes the encoded string a
  multiple of 8 characters.

### hex

* `hex_upper` outputs upper-case letters and accepts lower-case as well.
  This is an octet-streaming codec variant and for decoding, requires an even
  number of input symbols. 
* `hex_lower` outputs lower-case letters and accepts upper-case as well.
  Similar to `hex_upper`, it's stream-based (no odd symbol lengths) and does
  not deal with "0x" prefixes.


# API

All codecs expose the same API. In the below documentation, replace `<codec>` with a
default alias such as `base64`, `base32` or `hex`, or with the full namespace such as
`cppcodec::base64_rfc4648` or `cppcodec::base32_crockford`.

For templated parameters `T` and `Result`, you can use e.g. `std::vector<uint8_t>`,
`std::string` or anything that supports:
* `.data()` and `.size()` for `T` (read-only) template parameters,
* for `Result` template parameters, also `.reserve(size_t)`, `.resize(size_t)`
  and `.push_back([uint8_t|char])`.


### Encoding

```C++
// Convenient version, returns an std::string.
std::string <codec>::encode(const [uint8_t|char]* binary, size_t binary_size);
std::string <codec>::encode(const T& binary);

// Convenient version with templated result type.
Result <codec>::encode<Result>(const [uint8_t|char]* binary, size_t binary_size);
Result <codec>::encode<Result>(const T& binary);

// Reused result container version. Resizes encoded_result before writing to it.
void <codec>::encode(Result& encoded_result, const [uint8_t|char]* binary, size_t binary_size);
void <codec>::encode(Result& encoded_result, const T& binary);
```

Encode binary data into an encoded (base64/base32/hex) string.
Won't throw by itself, but the result type might throw on `.resize()`.

```C++
size_t <codec>::encode(char* encoded_result, size_t encoded_buffer_size, const [uint8_t|char]* binary, size_t binary_size) noexcept;
size_t <codec>::encode(char* encoded_result, size_t encoded_buffer_size, const T& binary) noexcept;
```

Encode binary data into pre-allocated memory with a buffer size of
`<codec>::encoded_size(binary_size)` or larger.

Returns the byte size of the encoded string excluding null termination,
which is equal to `<codec>::encoded_size(binary_size)`.


### Decoding

```C++
// Convenient version, returns an std::vector<uint8_t>.
std::vector<uint8_t> <codec>::decode(const char* encoded, size_t encoded_size);
std::vector<uint8_t> <codec>::decode(const T& encoded);

// Convenient version with templated result type.
Result <codec>::decode<Result>(const char* encoded, size_t encoded_size);
Result <codec>::decode<Result>(const T& encoded);

// Reused result container version. Resizes binary_result before writing to it.
void <codec>::decode(Result& binary_result, const char* encoded, size_t encoded_size);
void <codec>::decode(Result& binary_result, const T& encoded);
```

Decode an encoded (base64/base32/hex) string into a binary buffer.

Throws a cppcodec::parse_error exception (inheriting from std::domain_error)
if the input data does not conform to the codec variant specification.
Also, the result type might throw on `.resize()`.

```C++
size_t <codec>::decode([uint8_t|char]* binary_result, size_t binary_buffer_size, const char* encoded, size_t encoded_size);
size_t <codec>::decode([uint8_t|char]* binary_result, size_t binary_buffer_size, const T& encoded);
```

Decode an encoded string into pre-allocated memory with a buffer size of
`<codec>::decoded_max_size(encoded_size)` or larger.

Returns the byte size of the decoded binary data, which is less or equal to
`<codec>::decoded_max_size(encoded_size)`.