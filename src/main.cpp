#include "../include/Huffman.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Welcome to Huffman encoder! Keep entering your text and end "
                 "it by entering -1:"
              << std::endl;

    std::string yolos, temp;
    while (getline(std::cin, temp)) {
        if (temp == "-1")
            break;
        yolos += temp;
        yolos += '\n';
    }
    if (!yolos.empty())
        yolos.pop_back();

    Huffman yolo;
    yolo.encode(yolos);
    std::cout << yolo.getEncoded() << std::endl
              << std::endl
              << "Original number of bits: "
              << yolos.length() * sizeof(char) * 8 << std::endl
              << "No. of bits used: " << yolo.getEncoded().length()
              << std::endl
              << std::endl
              << "Decoded:" << std::endl
              << yolo.decode() << std::endl;
    return 0;
}
