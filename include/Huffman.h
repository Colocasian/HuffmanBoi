#ifndef _HAS_INCLUDED_HUFFMAN_TREE_BY_COLOCASIAN
#define _HAS_INCLUDED_HUFFMAN_TREE_BY_COLOCASIAN

#include <exception>
#include <string>
#include <vector>

class Huffman {
private:
    typedef struct huffNode {
        char c;
        struct huffNode *right, *left;
    } huffNode;

    typedef struct huffQueue {
        huffNode* tree;
        int freq;
    } huffQueue;

    huffNode* key;
    std::string encoded;

    class HuffPrior {
    private:
        huffQueue qu[257];
        int top;

        void swap(int pos1, int pos2)
        {
            int tmp = qu[pos1].freq;
            huffNode* root = qu[pos1].tree;
            qu[pos1].freq = qu[pos2].freq;
            qu[pos1].tree = qu[pos2].tree;
            qu[pos2].freq = tmp;
            qu[pos2].tree = root;
        }

    public:
        HuffPrior() { top = 0; }

        bool size() { return top; }

        void push(huffNode* root, int freq)
        {
            qu[++top].tree = root;
            qu[top].freq = freq;
            int at = top;
            while (at > 1) {
                if (qu[at].freq < qu[at >> 1].freq) {
                    this->swap(at, at >> 1);
                    at >>= 1;
                } else
                    break;
            }
        }

        void pop()
        {
            if (top == 0)
                throw new std::exception;
            qu[1] = qu[top--];

            int at = 1;
            while (true) {
                int left = at << 1, right = left + 1;
                if (right > top) {
                    if (left <= top && qu[left].freq < qu[at].freq)
                        this->swap(left, at);
                    break;
                }

                if (qu[right].freq < qu[left].freq) {
                    if (qu[right].freq < qu[at].freq) {
                        this->swap(right, at);
                        at = right;
                    } else
                        break;
                } else {
                    if (qu[left].freq < qu[at].freq) {
                        this->swap(left, at);
                        at = left;
                    } else
                        break;
                }
            }
        }

        huffNode* peek()
        {
            if (top == 0)
                throw new std::exception;
            return qu[1].tree;
        }

        int peekFreq()
        {
            if (top == 0)
                throw new std::exception;
            return qu[1].freq;
        }

        huffNode* process()
        {
            if (top == 0)
                return nullptr;

            while (top > 1) {
                huffNode* left = this->peek();
                int freq = this->peekFreq();
                this->pop();
                huffNode* right = this->peek();
                freq += this->peekFreq();
                this->pop();

                huffNode* n = new huffNode;
                n->c = '\0';
                n->left = left;
                n->right = right;
                this->push(n, freq);
            }
            return this->peek();
        }
    };

    void createBook(
        huffNode* key, std::string res, std::vector<std::string>& book)
    {
        if (key != nullptr) {
            if (key->c != '\0')
                book[(int)key->c] = res;
            createBook(key->left, res + "0", book);
            createBook(key->right, res + "1", book);
        }
    }
    std::vector<std::string> createBook(huffNode* key)
    {
        std::vector<std::string> book(256, "");
        createBook(key, "", book);
        return book;
    }

public:
    Huffman()
    {
        this->key = nullptr;
        this->encoded = "";
    }

    std::string getEncoded() { return this->encoded; }

    void encode(std::string text)
    {
        int count[256];
        for (int i = 0; i < 256; i++)
            count[i] = 0;
        for (char x : text)
            count[(int)x]++;

        HuffPrior grinder;

        for (int i = 0; i < 256; i++) {
            if (count[i] != 0) {
                huffNode* n = new huffNode;
                n->c = (char)i;
                n->right = nullptr;
                n->left = nullptr;
                grinder.push(n, count[i]);
            }
        }

        this->key = grinder.process();
        std::vector<std::string> book(createBook(this->key));
        this->encoded = "";
        for (char x : text)
            this->encoded += book[(int)x];
    }

    std::string decode()
    {
        std::string ans;
        huffNode* ptr = this->key;

        for (char x : this->encoded) {
            if (x == '0')
                ptr = ptr->left;
            else
                ptr = ptr->right;
            if (ptr->c != '\0') {
                ans += ptr->c;
                ptr = this->key;
            }
        }

        return ans;
    }
};

#endif
