#include <src/base64_rfc4648.hpp>
#include <src/base64_url.hpp>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        size_t arglen = strlen(argv[i]);

        try {
            cout << cppcodec::base64_rfc4648::decode<string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << std::endl;
        }

        try {
            cout << cppcodec::base64_url::decode<string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << endl;
        }
    }
    return 0;
}