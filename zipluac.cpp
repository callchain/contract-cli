#include <iostream>
#include <sstream>
#include <fstream>
#include "lz4.h"

using namespace std;

int hexchar2int(char c)  
{   
  if (c >= '0' && c <= '9') return (c - '0');  
  if (c >= 'A' && c <= 'F') return (c - 'A' + 10);  
  if (c >= 'a' && c <= 'f') return (c - 'a' + 10);  
  return 0;  
}  
  
char* hex2bytes(string s)  
{           
  int sz = s.length();  
  char *ret = new char[sz/2];  
  for (int i = 0 ; i < sz ; i += 2) {  
    ret[i/2] = (char) ((hexchar2int(s.at(i)) << 4) | hexchar2int(s.at(i+1)));  
  }  
  return ret;  
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

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cout << "Usage:\
      \t zipluac filename" << endl;
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

  char* buf = new char[size];
  input.read(buf, size);
  input.close();

  int max_size = LZ4_compressBound(size);
  char *output_buf = new char[max_size];
  int actual_size = LZ4_compress_default(buf, output_buf, size, max_size);

  string result = bytes2hex(output_buf, actual_size);
  string output_filename = filename + ".hex";
  fstream output(output_filename, output.out);
  output.write(result.c_str(), result.size());
  output.flush();
  output.close();

  return 0;
}
