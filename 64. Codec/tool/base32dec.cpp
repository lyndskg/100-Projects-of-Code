#include <src/base32_crockford.hpp>
#include <src/base32_rfc4648.hpp>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        size_t arglen = strlen(argv[i]);

        try {
            cout << cppcodec::base32_crockford::decode<std::string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << std::endl;
        } // try-catch

        try {
            cout << cppcodec::base32_rfc4648::decode<std::string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << std::endl;
        } // try-catch
    }
    return 0;
} // main()