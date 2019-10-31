#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "lz4.h"

using namespace std;

int hexchar2int(char c)
{
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
    return 0;
}

std::vector<char> hex2bytes(string s)
{
    std::vector<char> v;
    int sz = s.length();
    for (int i = 0 ; i < sz ; i += 2) {
        char c = (char) ((hexchar2int(s.at(i)) << 4) | hexchar2int(s.at(i+1)));
        v.push_back(c);
    }
    return v;
}

string bytes2hex(char* bytes, int length)
{
    string str("");
    string hex("0123456789abcdef");
    for (int i = 0; i < length; i++)
    {
        int b;
        b = 0x0f & (bytes[i] >> 4);
        str.append(1, hex.at(b));
        b = 0x0f & bytes[i];
        str.append(1, hex.at(b));
    }
    return str;
}

string compress(std::vector<char> input)
{
    int max_size = LZ4_compressBound(input.size());
    char *output_buf = new char[max_size];
    int actual_size = LZ4_compress_default(&input[0], output_buf, input.size(), max_size);
    string result = bytes2hex(output_buf, actual_size);
    return result;
}

std::vector<char> uncompress(string input)
{
    std::vector<char> bytes = hex2bytes(input);
    int size = bytes.size();
    int max_size = size*2 + 8;
    char *output_buf = new char[max_size];
    int actual_size = LZ4_decompress_safe(&bytes[0], output_buf, size, max_size);
    std::vector<char> v(actual_size);
    std::copy(output_buf, output_buf + actual_size, v.begin());
    return v;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: zipluac filename" << endl;
        return -1;
    }

    string filename = argv[1];
    fstream input(filename, input.binary | input.in);
    if (!input.is_open())
    {
        cout << "File not exists" << endl;
        return -1;
    }

    input.seekg(0, input.end);
    int size = input.tellg();
    input.seekg(0, input.beg);

    std::vector<char> buf(size);
    input.read(&buf[0], size);
    input.close();

    string result = compress(buf);
    string output_filename = filename + ".hex";
    fstream output(output_filename, output.out);
    output.write(result.c_str(), result.size());
    output.flush();
    output.close();

    return 0;
}
