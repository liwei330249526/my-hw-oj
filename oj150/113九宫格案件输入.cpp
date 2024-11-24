/*
 *
题目描述
[九宫格]案件输入，输出显示内容，有英文和数字两个模式，默认是数字模式，数字模式直接输出数字，英文模式连续按同一个按键会一次出现这个按键上的字母，如果输入"/"
或者其他字符，则循环中断。

字符对应关系如下
1 ,.
2 abc
3 def
4 ghi
5 jkl
6 mno
7 pqrs
8 tuv
9 wxyz
#
0
/


输入
输入范围为数字0-9和和字符 #
数字模式下，输入 1234， 显示1234
英文模式下，输入 1234， 显示adg

输出
# 用于切换模式，默认是数字模式，#后切换为英文模式
/ 表示延迟，例如在英文模式下，输入 22/222,显示 bc
英文模式下，多次按同意按键，例如输入2222，显示为b


 *
 * 样例1
输入
123#222235/56


输出
123adjjm


 *
 * 样例2
输入
#44444


输出
h

 *
 * 样例3
输入
/999


输出
999

 *
 * 样例4
 * 123#222#222
 *
 * */

#include "string"
#include "iostream"
#include "unordered_map"
#include "vector"
using namespace std;
int main() {
  string str;
//  getline(cin, str);    // 转换 getline 和 cin
  cin >> str;
  unordered_map<char, string> dict{
          {'1', "1"}, {'2', "abc"}, {'3', "def"},
          {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"},
          {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
          {'0', "0"}
  };


  string ret;
  string state = "number";

  char curKey = '\0'; // 初始化当前按键
  int alphaCount = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '#') { // 如果是 "#", 则尝试转换
      if (state == "number") { // 如果当前是 number， 则直接转为字母
        state = "alpha";
      } else {                // 如果当前是字母，则直接转为 number； 并尝试加入字母结果集
        // 加入前面的字符
        state = "number";
//        if (curKey != '\0') {
////          ret += dict[curKey][(alphaCount-1) % dict[curKey].size()];  // 切换的时候，不需要加入字符
//        }
      }
      curKey = '\0';
      alphaCount = 0;
    } else if (str[i] == '/') {  // 如果要延迟，则在字母状态下， 则尝试加入字母结果集
      // 加入前面的字符
      if (curKey != '\0') {
        ret += dict[curKey][(alphaCount-1) % dict[curKey].size()];
      }

      alphaCount = 0;
      curKey = '\0';
    } else if (state == "number") { // 如果是数字，则直接加入数字
      ret += str[i];
    } else {  // 如果是字母，则判断是否和 curKey 一致，如果已知，则增加计数； 如果不一致，则将curKey 假如结果集，并重新记录curKey
      if(i > 0 && curKey == str[i]) {
        alphaCount++;
      } else {
        if (curKey != '\0') {
          ret += dict[curKey][(alphaCount-1) % dict[curKey].size()];
        }
        curKey = str[i];
        alphaCount = 1;
      }
    }
  }

  if (curKey != '\0') {
    ret += dict[curKey][(alphaCount-1) % dict[curKey].size()];
  }

  cout << ret << endl;

  return 0;
}