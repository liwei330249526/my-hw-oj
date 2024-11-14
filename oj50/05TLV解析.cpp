/*
 * tlv, tag 固定占1个字节，length 固定站2个字节，字节序为小端序
 * 先给出tlv码流，以及需要的tag，解析出对应的valu
 *
输入
31
32 01 00 AE 90 02 00 01 02 30 03 00 AB 32 31 31 02 00 32 33 33 01 00 CC


输出
32 33

说明

需要解析的信元的Tag是31，从码流的起始处开始匹配，Tag为32的信元长度为1（01 00，小端序表示为1）；

第二个信元的Tag是90，其长度为2；第三个信元的Tag是30，其长度为3；

第四个信元的Tag是31，其长度为2（02 00），所以返回长度后面的两个字节即可，即32 33。


 * */


/*
 *
 * */

#include <sstream>
#include "string"
#include "iostream"
#include "vector"
#include "strings.h"
using namespace std;

void splitString(string str, char delim, vector<string> &res) {
  istringstream strm(str); // istringstream
  string token;

  while (getline(strm, token, delim)) {  // getline(stream, token, delim)
    res.push_back(token);
  }

  return;
}

int main() {
  string tag;
  getline(cin, tag);

  string text;
  getline(cin, text);

  vector<string> texts;
  splitString(text, ' ', texts);


//
  int id = 0;
  vector<string> res;
  for (;id < texts.size();) {
    string str2 = texts[id+2];
    string str1 = texts[id+1];
//    cout << str1 << " " << str2 << endl;
    int num2 = stoi(str2, nullptr, 16);
    int num1 = stoi(str1, nullptr, 16);
    int len = num2 * 16 + num1;
    string curTag = texts[id];
    if (tag == curTag) {
      for (int j = 0; j < len; j++) {
        res.push_back(texts[id+1+2+j]);
      }
    }
    id = id + 1 + 2 + len;
  }


  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << " ";
    }
  }
  cout << endl;
  return 0;
}