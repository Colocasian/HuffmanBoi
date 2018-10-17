#pragma ONCE

#include <queue>

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
public:

};
