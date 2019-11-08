#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <snappy.h>

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
    int sz = s.length();
    std::vector<char> v(sz/2);
    for (int i = 0 ; i < sz ; i += 2) {
        char c = (char) ((hexchar2int(s.at(i)) << 4) | hexchar2int(s.at(i+1)));
        v.push_back(c);
    }
    return v;
}

string bytes2hex(string bytes)
{
    string str("");
    string hex("0123456789abcdef");
    for (int i = 0; i < bytes.size(); i++)
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
    string input_str = std::string(input.begin(), input.end());
    string output;
    snappy::Compress(input_str.data(), input_str.size(), &output);
    string result = bytes2hex(output);
    return result;
}

string uncompress(string input)
{
    std::vector<char> bytes = hex2bytes(input);
    string byte_str = std::string(bytes.begin(), bytes.end());
    string output;
    snappy::Uncompress(byte_str.data(), byte_str.size(), &output);
    return output;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: zipluac filename" << endl;
        return -1;
    }

    string filename = argv[1];
    fstream input(filename.c_str(), input.binary | input.in);
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
    fstream output(output_filename.c_str(), output.out);
    output.write(result.c_str(), result.size());
    output.flush();
    output.close();

    return 0;
}
