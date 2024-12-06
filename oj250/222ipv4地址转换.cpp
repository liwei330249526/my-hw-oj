/*
 *
题目描述
存在一种虚拟地址，由4个小节组成，每节的范围为0-255，以#号间隔，虚拟ipv4地址可以转换为一个32位整数，例如
128#0#255#255, 转换为32整数的结果为2147549183(0x8000FFFF)
1#0#0#0， 转换为32位整数的结果为16777216（0x0100 0000）
现以字符串形式给出一个虚拟ipv4地址，限制第一小节范围为1-128，即每节范围分别为(1-128)#(0-255)#(0-255)#(0-255),
要求每个ipv4地址只能对应到唯一的整数，如果是非法的ipv4，返回 invalid IP.
 *
 * 样例1
 * 输入
100#101#1#5


输出
1684340997


 *
 * 样例2
 * 输入
01#01#01#01

输出
invalid IP


 *
 * */

#include "iostream"
#include "vector"
#include "sstream"
#include "cstdint"

using namespace std;

string isValid(vector<int> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    if (i == 0) {
      if (arr[0])
      if(!(arr[i] >= 1 && arr[i] <= 128)) {
        return "invalid IP";
      }
    } else {
      if (!(arr[i] >= 0 && arr[i] <= 255)) {
        return "invalid IP";
      }
    }
  }

  return "";
}

int main() {
  string str;
  getline(cin, str);

  stringstream stm(str);
  vector<int> arr;
  string token;
//  cout << str ;
//  return 0;
  while (getline(stm, token, '#')) {
    // 校验前导0
    if (token.front() == '0' && token.size() > 1) {
      cout << "invalid IP" << endl;
      return 0;
    }
    arr.push_back(stoi(token));
  }

  if (arr.size() != 4) {
    cout << "invalid IP" << endl;
    return 0;
  }

  string ret = isValid(arr);
  if (ret.size() != 0) {
    cout << ret << endl;
    return 0;
  }

  uint32_t outNum;
  for (int i = 0; i < arr.size(); i++) {
    outNum = (outNum << 8) | arr[i];
  }
  cout << outNum << endl;

  return 0;
}