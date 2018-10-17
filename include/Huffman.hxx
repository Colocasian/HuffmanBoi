#pragma ONCE

#include <queue>
#include <string>
#include <cstring>
#include <vector>

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

    void huffBook(HuffTree *root, std::string res, std::vector<std::string> &book)
    {
        if (root != nullptr)
            return;
        if (root->c == '\0')
        {
            huffBook(root->left, res+"0", book);
            huffBook(root->right, res+"1", book);
            return;
        }
        book[root->c] = res;
        return;
    }
    std::vector<std::string> huffBook(HuffTree *root)
    {
        std::vector<std::string> book(256);
        huffBook(root, "", book);
        return book;
    }

public:
    Huffman()
    {
        this->root = nullptr;
        this->encoded = "";
    }

    void huffEncode(const std::string &text)
    {
        int freq[256];
        memset(freq, 0, 256*sizeof(int));
        for (char x: text)
            freq[x]++;

        std::priority_queue<HuffTree> yolo;
        for (int i = 0; i < 256; i++)
        {
            if (freq[i])
            {
                HuffTree *n = new HuffTree;
                n->c = (char)i;
                n->freq = -freq[i];
                n->right = nullptr, n->left = nullptr;
                yolo.push(*n);
            }
        }

        while (yolo.size() > 1)
        {
            HuffTree left = yolo.top();
            yolo.pop();
            HuffTree right = yolo.top();
            yolo.pop();

            HuffTree *n = new HuffTree;
            n->left = &left;
            n->right = &right;
            n->c = '\0';
            n->freq = left.freq + right.freq;
            yolo.push(*n);
        }

        HuffTree temp = yolo.top();
        this->root = &temp;
        std::vector<std::string> book(huffBook(this->root));
        std::string ans("");
        for (char c: text)
            ans += book[c];
        this->encoded = ans;
    }

    std::string getEncoded()
    {
        return this->encoded;
    }

};
