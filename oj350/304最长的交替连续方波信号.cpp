/*
 *
输入一串方波信号，求取最长的完全连续交替方波信号，并将其输出，如果有相同长度的交替方波信号，输出任一即可，方波信号高位用1标识，
低位用0标识，如图：

1 一个完整的信号一定以0开始然后一0结尾，即010是一个完整信号，但101， 1010， 0101不是
2 输入的一串方波信号由一个或多个完整信号组成
3 两个相邻信号之间坑有0个或多个低位
4 同一个信号中国可以有连续的高位
5 完全连续交替方波指10交替，如 01010是完全连续交替方波，0110不是

输入
输入信号字符串
输出
输出最长的完全连续交替方波信号串，若不存在，则输出-1

样例1
输入
00101010101100001010010



输出
01010


说明：
输入信号串中有三个信号:
0 010101010110(第一个信号段)
00 01010(第二个信号段)
010(第三个信号段)
第一个信号虽然有交替的方波信号段，但出现了11部分的连续高位，不算完全连续交替方波，在剩下的连续方波信号串中01010最长


 *
 * */

#include "iostream"
#include "string"
#include "sstream"
using namespace std;

string getStr(string str) {
  // 第一个1
  int start = 0;
  int end = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '1') {
      start = i;
      break;
    }
  }

  // 最后一个1
  for (int i = str.size()-1; i >= 0; i--) {
    if (str[i] == '1') {
      end = i;
      break;
    }
  }

  for (int i = start; i < end; i++) { // 最后一个字符不校验
    if (!(str[i] == '1' && str[i+1] == '0' ||
          str[i] == '0' && str[i+1] == '1')) {
      // not ok
      return "";
    }
  }

  return str.substr(start, end-start+1);
}

int main() {
  string str;
  cin >> str;

  // 判断是否存在 "00"
  int sId = str.find("00");
  if (sId == str.npos) {
    cout << -1 << endl;
    return 0;
  }

  string res;
  while (sId != str.npos) { // 循环条件， "00" 位置在字符串是存在的
    string str1 = str.substr(0, sId);
    // check 可能获取  1,  101 , 10101 , 1010101 ... 等等

    string rest = getStr(str1);
    if (res.size() < rest.size()) {
      res = rest;
    }

    str = str.substr(sId+2); // 取后续的字符串
    sId = str.find("00");
  }

  if (res.size() == 0) {
    cout << -1 << endl;
    return 0;
  }

  res = "0" + res + "0";
  cout << res << endl;
  return 0;
}