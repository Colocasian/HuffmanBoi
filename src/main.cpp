#include <iostream>
#include "../include/Huffman.hxx"

int main()
{
    std::string yay("Hello Sir, my name is Chinappa");
    Huffman encoder;
    encoder.huffEncode(yay);
    std::cout << encoder.getEncoded() << std::endl;
}
