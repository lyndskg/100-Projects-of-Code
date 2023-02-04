#include <src/hex_lower.hpp>
#include <src/base32_rfc4648.hpp>
#include <src/base64_rfc4648.hpp>

#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <stdint.h>
#include <string>
#include <vector>

#define BENCHMARK_ENCODING_STR true
#define BENCHMARK_DECODING_STR true
#define BENCHMARK_DECODING_VEC_U8 true

using namespace std;

const size_t max_iterations = 1000000; // 1m iterations ought to be enough for anybody
const size_t iteration_max_ms = 500; // half a second

uint8_t random_uint8() {
    static random_device rd;
    static mt19937 pseudo_random(rd());
    static uniform_int_distribution<int> dist(0, 255);

    return static_cast<uint8_t>(dist(pseudo_random));
} // random_uint8()

template <typename Codec>
void benchmark(ostream& stream, const vector<size_t>& decoded_sizes) {
    using clock = chrono::high_resolution_clock;

    // Measure decoding into both uint8_t and string.
    vector<double> time_encoding_str(decoded_sizes.size());
    vector<double> time_decoding_vec_u8(decoded_sizes.size());
    vector<double> time_decoding_str(decoded_sizes.size());
    vector<vector<uint8_t>> decoded_vec_u8(decoded_sizes.size());
    vector<string> decoded_str(decoded_sizes.size());
    vector<string> encoded_str(decoded_sizes.size());

    for (size_t i = 0; i < decoded_sizes.size(); ++i) {
        decoded_vec_u8[i].resize(decoded_sizes[i]);
        for (size_t j = 0; j < decoded_sizes[i]; ++j) {
            decoded_vec_u8[i][j] = random_uint8();
        } // for 
    } // for

    auto flags = stream.flags();
    auto precision = stream.precision();
    stream << fixed << setprecision(4);

#if BENCHMARK_ENCODING_STR
    stream << "Encoding:\n";

    for (size_t i = 0; i < decoded_sizes.size(); ++i) {
        encoded_str[i] = Codec::encode(decoded_vec_u8[i]);

        clock::time_point start = clock::now();
        clock::time_point end = start + chrono::milliseconds(iteration_max_ms);
        
        size_t j = 0;
        for (; j < max_iterations; ++j) {
            if (clock::now() > end) {
                break;
            } // if
            encoded_str[i] = Codec::encode(decoded_vec_u8[i]);
        } // for

        time_encoding_str[i] = chrono::duration_cast<chrono::microseconds>(
                clock::now() - start).count() / static_cast<double>(j);

        stream << (i == 0 ? "" : "\t") << decoded_sizes[i] << ": "
                << time_encoding_str[i] << flush;
    } // for 
    stream << "\n";

#else
    // Even if we're not benchmarking encoding, we still need the encoded strings.
    for (size_t i = 0; i < decoded_sizes.size(); ++i) {
        encoded_str[i] = Codec::encode(decoded_vec_u8[i]);
    }
#endif // BENCHMARK_ENCODING_STR

#if BENCHMARK_DECODING_STR
    stream << "Decoding to string:\n";

    for (size_t i = 0; i < decoded_sizes.size(); ++i) {
        decoded_str[i] = string();
        clock::time_point start = clock::now();
        clock::time_point end = start + chrono::milliseconds(iteration_max_ms);
        size_t j = 0;
        for (; j < max_iterations; ++j) {
            if (clock::now() > end) {
                break;
            } // if 
            decoded_str[i] = Codec::template decode<string>(encoded_str[i]);
        } // for 

        time_decoding_str[i] = chrono::duration_cast<chrono::microseconds>(
                clock::now() - start).count() / static_cast<double>(j);

        stream << (i == 0 ? "" : "\t") << decoded_sizes[i] << ": "
                << time_decoding_str[i] << flush;
    } // for

    stream << "\n";

#endif // BENCHMARK_DECODING_STR

#if BENCHMARK_DECODING_VEC_U8
    stream << "Decoding to vector<uint8_t>:\n";

    for (size_t i = 0; i < decoded_sizes.size(); ++i) {
        decoded_vec_u8[i] = vector<uint8_t>();
        clock::time_point start = clock::now();
        clock::time_point end = start + chrono::milliseconds(iteration_max_ms);

        size_t j = 0;
        for (; j < max_iterations; ++j) {
            if (clock::now() > end) {
                break;
            } // if
            decoded_vec_u8[i] = Codec::decode(encoded_str[i]);
        } // for 

        time_decoding_vec_u8[i] = chrono::duration_cast<chrono::microseconds>(
                clock::now() - start).count() / static_cast<double>(j);

        stream << (i == 0 ? "" : "\t") << decoded_sizes[i] << ": "
                << time_decoding_vec_u8[i] << flush;
    } // for 

    stream << "\n";

#endif // BENCHMARK_DECODING_VEC_U8

    stream << setprecision(precision) << "\n";
    stream.flags(flags);
} // benchmark()

int main() {
    vector<size_t> decoded_sizes = {
        1, 4, 8, 16, 32, 64, 128, 256, 2048, 4096, 32768
    }; // decoded_sizes

    cout << "base64_rfc4648: [decoded size: microseconds]\n";
    
    benchmark<cppcodec::base64_rfc4648>(cout, decoded_sizes);
    
    return 0;
} // main()