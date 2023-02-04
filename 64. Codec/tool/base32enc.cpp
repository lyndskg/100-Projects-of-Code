#include <src/base32_crockford.hpp>
#include <src/base32_rfc4648.hpp>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        size_t arglen = strlen(argv[i]);

        cout << cppcodec::base32_crockford::encode(argv[i], arglen) << endl;
        cout << cppcodec::base32_rfc4648::encode(argv[i], arglen) << endl;
    } // for

    return 0;
} // main()