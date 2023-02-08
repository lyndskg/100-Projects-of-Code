#include <src/base64_rfc4648.hpp>
#include <iostream>

using namespace std;

int main() {
    constexpr const char encoded[] = { "YW55IGNhcm5hbCBwbGVhc3U=" };

    char decoded[cppcodec::base64_rfc4648::decoded_max_size(sizeof(encoded))];
    cppcodec::base64_rfc4648::decode(decoded, sizeof(decoded), encoded);

    cout << decoded << '\n';

    return 0;
} // main()