/*
 *
题目描述
有一种简易压缩算法：针对全部由小写英文字母组成的字符串，将其中连续超过两个相同字母的部分压缩为连续个数加该字母，其他部分保持原样不变
例如： 字符串"aaabbccccd" 经过压缩成为字符串 "3abb4cd"

请您编写解压函数，根据输出的字符串，判断其是否为合法压缩过的字符串
若输入合法则输出解压缩后的字符串，否则输出字符串"!error" 来报告错误

输入
输入一行，为一个ASCII字符串，长度不超过100字符，用力保证输出的字符串长度也不会超过100字符
输出
若判断输入为合法的经过压缩后的字符串，则输出压缩前的字符串；若输入不合法，则输出字符串"!error"

样例1
 输入
4dff

输出
ddddff

说明：
4d扩展为dddd,故解压后的字符串为ddddff


样例2
 输入
2dff

输出
!error

说明：
两个d不需要压缩，故输入不合法

样例3
 输入
4d@A

输出
!error

说明：
全部由小写英文字母组成的字符串压缩后不会出现特殊字符@和大写字母A，故输入不合法


 *
 * */

#include "vector"
#include "string"
#include "iostream"
using namespace std;

bool check(string str) {
  if (isdigit(str.back())) {
    return false;
  }

  for(int i = 0; i < str.size(); i++) {
    if (!(isdigit(str[i]) || isalpha(str[i]) && islower(str[i]))) {
      return false;
    }
  }
  return true;
}

// 2dff
int main() {
  string str;
  cin >> str;

  // check
  if(!check(str)) {
    cout << "!error" << endl;
    return 0;
  }

  int left = 0;
  string res;
  string rest;
  int num = 0;
  char preC;
  int preNum;
  for (int i = 0; i < str.size(); i++) {
    if (isdigit(str[i])) { // 数字
      left = i;
      while (i+1 < str.size() && isdigit(str[i+1])) {
        i = i+1;
      }
      // i 是该 item 的最后一个数字; 数字为[left, i]
      num = stoi(str.substr(left, i - left + 1)); // 获得数字
      if (num <= 2) {
        cout << "!error" << endl;
        return 0;
      }
    } else { // 字母
      // 之前是数字
      if (preC == str[i]) { // 非法， 前一段和本段字符一样
        cout << "!error" << endl;
        return 0;
      }

      // 重复字符， 例如 3a  -->  aaa
      if (num > 2) {
        // 非法，前一段的字符和 i+1 相同;  例如 3aa,   4bb
        if (i+1 < str.size() && str[i] == str[i+1]) {
          cout << "!error" << endl;
          return 0;
        }
        for (int j = 0; j < num; j++) {
          res += str[i];
        }
        preC = str[i];  // 记录该段
        preNum = num;
        rest = "";
        num = 0;
      } else {

        char preCh = str[i];
        int preChCount = 1;
        rest += str[i];
        while (i+1 < str.size() && islower(str[i+1])) { // 非法， 遍历过程中，连续3个和3个以上相同， 例如 aaa
          if (preCh == str[i+1]) {
            preChCount++;
          } else {
              preC = str[i+1];
            preChCount = 1;
          }
          if (preChCount >= 3) {
            cout << "!error" << endl;
            return 0;
          }

          rest += str[i+1];
          i = i+1;
        }
        // i 是小字符串的最后一个字符
        if (rest != "") {
          res += rest;
          rest = "";
        }
      }
    }
  }
  cout << res << endl;

  return 0;
}