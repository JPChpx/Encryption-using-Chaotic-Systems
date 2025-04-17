/// Code by JP Champeaux (2025)
/// jpc@irsamc.ups-tlse.fr   
/// free to use for academic / non commercial purpose 
/// please refere to author if use

#include <iostream>
#include <complex>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>
#include "Cout_color.h"
#include "version.h"

// Base64 encoding characters
const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Lookup table for Base64 decoding
const std::vector<int> base64_lookup = [] {
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; ++i) T[base64_chars[i]] = i;
    return T;
}();

// Generate a random 512-bit hexadecimal key (128 hex characters)
std::string generateKey() {
    std::ostringstream oss;
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distrib(0, 15);
    for (int i = 0; i < 128; ++i) {
        oss << std::hex << std::uppercase << distrib(gen);
    }
    return oss.str();
}

// Encode binary string to Base64
std::string base64Encode(const std::string& input) {
    std::string output;
    int val = 0, valb = -6;
    for (uint8_t c : input) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            output.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        output.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (output.size() % 4)
        output.push_back('=');
    return output;
}

// Decode Base64 to vector of 16-bit integers (used as iteration key)
std::vector<int> base64ToIterationKey(const std::string& b64) {
    std::string rawBytes;
    int val = 0, valb = -8;
    for (uint8_t c : b64) {
        if (base64_lookup[c] == -1) break;
        val = (val << 6) + base64_lookup[c];
        valb += 6;
        if (valb >= 0) {
            rawBytes.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    std::vector<int> key;
    for (size_t i = 0; i + 1 < rawBytes.size(); i += 2) {
        uint16_t num = (static_cast<uint8_t>(rawBytes[i]) << 8) | static_cast<uint8_t>(rawBytes[i + 1]);
        key.push_back(num);
    }

    return key;
}

// Convert iteration key to Base64
std::string iterationKeyToBase64(const std::vector<int>& key) {
    std::string rawBytes;
    for (int val : key) {
        rawBytes.push_back(static_cast<char>(val >> 8));
        rawBytes.push_back(static_cast<char>(val & 0xFF));
    }
    return base64Encode(rawBytes);
}

// Generate Mandelbrot-based iteration key
std::vector<int> generateMandelbrotKey(const std::string& hexKey, int textLength, int maxIterations) {
    if (hexKey.size() < 16)
        throw std::runtime_error("Key too short!");

    std::vector<int> iterationKey;
    try {
        for (int i = 0; i < textLength; ++i) {
            size_t pos = (i * 4) % (hexKey.size() - 8);
            unsigned long realPart = std::stoul(hexKey.substr(pos, 4), nullptr, 16);
            unsigned long imagPart = std::stoul(hexKey.substr(pos + 4, 4), nullptr, 16);

            double r = (realPart % 10000) / 4000.0 - 2.0;
            double im = (imagPart % 10000) / 5000.0 - 1.0;

            std::complex<double> c(r, im);
            std::complex<double> z = 0;

            int iter = 0;
            while (std::abs(z) <= 2.0 && iter < maxIterations) {
                z = z * z + c;
                ++iter;
            }

            iterationKey.push_back(iter);
        }
    } catch (...) {
        // Fallback in case of error
        iterationKey.assign(textLength, 1);
    }

    return iterationKey;
}

// Robust encoding using position and iteration key
std::string encodeText(const std::string& text, const std::vector<int>& iterationKey) {
    std::string encodedText;
    for (size_t i = 0; i < text.size(); ++i) {
        uint8_t originalByte = static_cast<uint8_t>(text[i]);
        int shift = iterationKey[i % iterationKey.size()] + i + (i % 5);
        encodedText += static_cast<char>((originalByte + shift) % 256);
    }
    return encodedText;
}

// Robust decoding using position and iteration key
std::string decodeText(const std::string& encodedText, const std::vector<int>& iterationKey) {
    std::string decodedText;
    for (size_t i = 0; i < encodedText.size(); ++i) {
        uint8_t encodedByte = static_cast<uint8_t>(encodedText[i]);
        int shift = iterationKey[i % iterationKey.size()] + i + (i % 5);
        decodedText += static_cast<char>((encodedByte - shift + 256) % 256);
    }
    return decodedText;
}

// Convert a string to binary representation
std::string toBinary(const std::string& input) {
    std::ostringstream oss;
    for (unsigned char c : input) {
        for (int i = 7; i >= 0; --i)
            oss << ((c >> i) & 1);
        oss << ' ';
    }
    return oss.str();
}

// Main function to demonstrate the full process
// Proof of concept

int main() {

    // Colored header display
    cout << blue;
    std::cout << "-----------------------------------------------------------------------\n";
    cout << white;
    cout << blue << "Encoder Decoder using Chaos C++ \n";
    cout << green << "Coded by JP CHAMPEAUX                 \n";
    cout << white;
    cout << red << AutoVersion::FULLVERSION_STRING << endl;
    cout << AutoVersion::DATE << "/" << AutoVersion::MONTH << "/" << AutoVersion::YEAR << endl;
    cout << AutoVersion::STATUS << " version" << endl;
    cout << blue;
    cout << "Dependencies :        none " << endl;
    std::cout << "-----------------------------------------------------------------------\n";
    cout << white;

    std::string key = generateKey();
    std::string text = "Bonjour, ceci est un test a encoder 12";
    int maxIterations = 100000;

    std::vector<int> iterationKey = generateMandelbrotKey(key, text.size(), maxIterations);
    std::string encodedText = encodeText(text, iterationKey);
    std::string decodedText = decodeText(encodedText, iterationKey);

    std::string base64Key = iterationKeyToBase64(iterationKey);
    std::vector<int> fromBase64 = base64ToIterationKey(base64Key);
    std::string decodedFromBase64 = decodeText(encodedText, fromBase64);

    std::string badKey = generateKey();
    std::vector<int> badIterationKey = generateMandelbrotKey(badKey, text.size(), maxIterations);
    std::string wrongDecoded = decodeText(encodedText, badIterationKey);

    // Output results
    std::cout <<green<< "Hex Key:\n" <<white<< key << "\n\n";
    std::cout <<blue<<"Original Text:\n" <<green<< text << "\n\n";
    std::cout <<red<< "Encoded Text:\n" <<white<< encodedText << "\n\n";
    std::cout <<red<< "Encoded (Base64):\n" <<white<< base64Encode(encodedText) << "\n\n";
    std::cout <<red<< "Iteration Key (Base64):\n" <<white<< base64Key << "\n\n";
    std::cout <<blue<< "Decoded with Correct Key:\n" <<white<< decodedText << "\n";
    std::cout <<blue<< "Decoded with Base64 Key:\n" <<white<< decodedFromBase64 << "\n";
    std::cout <<red<< "\nDecoded with Wrong Key:\n" <<yellow<< wrongDecoded << "\n"<<white;

    return 0;
}

