#pragma once

#include <exception>
#include <string>

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

        void insert(huffNode* root, int freq)
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
    };
};
