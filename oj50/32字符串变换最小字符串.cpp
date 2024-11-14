/*
 * 题目描述
 * 给定一个字符串s，最多只能进行一次变换，返回变换后能得到的最小字符串（字典序）。
 * 变换规则：交换字符串中任意两个不同位置的字符
 *
输入
abcdef

输出
abcdef

说明：

abcdef已经是最小字符串，不需要交换。


输入
bcdefa

输出
acdefb

说明：
a和b进行位置交换，可以得到最小字符串。

 * */

#include "string"
#include "iostream"
using namespace std;
int main() {
  string str;
  cin >> str;

  int left = -1;
  int right = -1;

  for (int i = 0; i < str.size(); i++) {
    if (str[i] == 'a') {
      continue;
    }

    char cur = str[i];
    for (int j = i+1; j < str.size(); j++) {
      if (cur >= str[j]) {
        // 没有break，找到最后一个
        cur = str[j];  // 维护最小
        left = i;
        right = j;
      }
    }

    // 如果找到一个最后最小的字符
    if (right != -1) {
      break;
    }
  }

  swap(str[left], str[right]);
  cout << str << endl;
  return 0;
}