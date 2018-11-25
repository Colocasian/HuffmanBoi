#include "../include/Huffman.hxx"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        cout << "No file specified" << endl;
        return -1;
    }

    ifstream reader(argv[1]);
    if (!reader.good())
    {
        cout << "No file in path" << endl;
        return -1;
    }
    cout << "File found" << endl;

    stringstream ss;
    ss << reader.rdbuf();
    string body = ss.str();
    cout << "Converted file to string" << endl;
    cout << "STRING:" << endl << body << endl;

    Huffman machine;
    machine.encode(body);
    cout << "Encoded string" << endl;

    cout << machine.decode() << endl;
    cout << "Decoded string" << endl;
    return 0;
}