#ifndef __HUFFMAN_ENCODER_BY_COLOCASIAN
#define __HUFFMAN_ENCODER_BY_COLOCASIAN

#include <string>
#include <vector>

class Huffman {
private:
    typedef struct HuffNode {
        char c;
        struct HuffNode *right, *left;
    } HuffNode;

    HuffNode* key;
    std::string encoded;
    char rem;

    class HuffQueue {
    private:
        typedef struct QNode {
            HuffNode* _node;
            int _freq;
        } QNode;
        QNode arr[129];
        int top;

        void swap(int p1, int p2)
        {
            int tint = arr[p1]._freq;
            arr[p1]._freq = arr[p2]._freq;
            arr[p2]._freq = tint;
            HuffNode* tptr = arr[p1]._node;
            arr[p1]._node = arr[p2]._node;
            arr[p2]._node = tptr;
        }

        void upMove(int at)
        {
            int p = at >> 1;
            while (p) {
                if (arr[at]._freq < arr[p]._freq)
                    this->swap(at, p);
                else
                    break;
                at = p;
                p = at >> 1;
            }
        }

        void downMove(int at)
        {
            int left = at << 1;
            int right = left + 1;
            while (left <= this->top) {
                if (right == this->top + 1
                    || arr[left]._freq <= arr[right]._freq) {
                    if (arr[at]._freq > arr[left]._freq)
                        this->swap(at, left);
                    else
                        break;
                    at = left;
                } else {
                    if (arr[at]._freq > arr[right]._freq)
                        this->swap(at, right);
                    else
                        break;
                    at = right;
                }
                left = at << 1;
                right = left + 1;
            }
        }

        void push(HuffNode* node, int freq)
        {
            top++;
            arr[top]._node = node;
            arr[top]._freq = freq;
            upMove(top);
        }

        QNode pop()
        {
            QNode ans = arr[1];
            arr[1]._freq = arr[top]._freq;
            arr[1]._node = arr[top]._node;
            this->top--;
            downMove(1);
            return ans;
        }

    public:
        HuffQueue() { top = 0; }

        HuffNode* process(int freqArr[])
        {
            for (int i = 0; i < 128; i++) {
                if (freqArr[i]) {
                    HuffNode* ptr = new HuffNode;
                    ptr->c = (char)i;
                    ptr->left = nullptr;
                    ptr->right = nullptr;
                    this->push(ptr, freqArr[i]);
                }
            }

            if (top == 1) {
                QNode nod = this->pop();
                HuffNode* ptr = new HuffNode;
                ptr->c = '\0';
                ptr->right = nullptr;
                ptr->left = nod._node;
                this->push(ptr, 0);
            } else {
                while (this->top != 1) {
                    QNode a = this->pop();
                    QNode b = this->pop();
                    HuffNode* n = new HuffNode;
                    n->c = '\0';
                    n->left = a._node;
                    n->right = b._node;
                    this->push(n, a._freq + b._freq);
                }
            }
            return this->pop()._node;
        }
    };

    void createBook(
        HuffNode* ptr, std::vector<std::string>& book, const std::string& res)
    {
        if (ptr == nullptr)
            return;
        if (ptr->c)
            book[(int)ptr->c] = res;
        else {
            createBook(ptr->left, book, res + '0');
            createBook(ptr->right, book, res + '1');
        }
    }

public:
    Huffman()
    {
        this->key = nullptr;
        this->encoded.clear();
    }

    void encode(std::string text)
    {
        this->encoded.clear();
        this->key = nullptr;
        if (text.empty())
            return;

        int arr[128];
        for (char x : text)
            arr[(int)x]++;

        HuffQueue grinder;
        this->key = grinder.process(arr);
        std::vector<std::string> book(128);
        this->createBook(this->key, book, "");

        int sz = 0;
        for (char x : text)
            sz += book[(int)x].length();
        this->encoded.resize((sz + 7) / 8);
        this->rem = sz % 8;

        int at = 0;
        for (char x : text) {
            for (char y : book[(int)x]) {
                if (y == '1')
                    this->encoded[at / 8] |= (1 << (at % 8));
                at++;
            }
        }
    }

    std::string decode()
    {
        if (this->encoded.empty())
            return ("");

        std::string ans("");

        char last;
        if (this->rem) {
            last = this->encoded.back();
            this->encoded.pop_back();
        }

        HuffNode* at = this->key;
        for (char x : encoded) {
            for (int i = 0; i < 8; i++) {
                if (x & (1 << i))
                    at = at->right;
                else
                    at = at->left;
                if (at->c != '\0') {
                    ans += at->c;
                    at = this->key;
                }
            }
        }

        if (this->rem) {
            for (int i = 0; i < this->rem; i++) {
                if (last & (1 << i))
                    at = at->right;
                else
                    at = at->left;
                if (at->c != '\0') {
                    ans += at->c;
                    at = this->key;
                }
            }
        }

        return ans;
    }
};

#endif
