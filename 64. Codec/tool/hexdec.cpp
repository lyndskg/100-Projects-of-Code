#include <src/hex_lower.hpp>
#include <src/hex_upper.hpp>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        size_t arglen = strlen(argv[i]);

        try {
            cout << cppcodec::hex_lower::decode<string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << endl;
        } // try-catch

        try {
            cout << cppcodec::hex_upper::decode<string>(argv[i], arglen) << endl;
        } catch (const cppcodec::parse_error& e) {
            cout << "#" << i << ": " << e.what() << endl;
        } // try-catch
    } // for

    return 0;
} // main()