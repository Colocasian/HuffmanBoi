#pragma ONCE

#include <queue>
#include <string>

class Huffman
{
private:
    class HuffTree
    {
    public:
        char c;
        int freq;
        HuffTree *right, *left;

        bool operator<(const HuffTree &other) const
        {
            return this->freq < other.freq;
        }
    };

    HuffTree *root;
    std::string encoded;

public:
    void huffEncode(const std::string &text)
    {
        int freq[256];
        for (char x: text)
            freq[x]++;

        // Counted the freq...
    }

};
