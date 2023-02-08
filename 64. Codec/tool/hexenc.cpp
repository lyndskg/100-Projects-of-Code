#include <src/hex_lower.hpp>
#include <src/hex_upper.hpp>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        size_t arglen = strlen(argv[i]);

        cout << cppcodec::hex_lower::encode(argv[i], arglen) << endl;
        cout << cppcodec::hex_upper::encode(argv[i], arglen) << endl;
    } // for 

    return 0;
} // main()