/*
 *
题目描述
给定一个字符串s，找出这样一个子串:
1 该子串中任意一个字符最多出现2次。
2 该子串不包含指定某个字符。
请请你找出满足该条件的最长子串长度

输入
第一行，要求不包含的指定字符，为单个字符，取值范围[0-9a-zA-Z]
第二行，字符串s，每个字符范围[0-9a-zA-Z]，长度[1,10000]

输出
一个整数，满足条件的最长子串长度
如果不存在满足条件的子串，输出0
 *
 * 样例1
输入
D ABC123

输出
6

 *
 * 样例2
输入
D ABACA123D


输出
7

 *
 *
 * */

#include "string"
#include "iostream"
#include "unordered_map"
using namespace std;
int main() {
  char spe;
  cin >> spe;

  string str;
  cin >> str;

  int left = 0;
  unordered_map<char, int> dict;
  int ret = 0;
  for (int i = 0; i < str.size(); ) {
    if (str[i] == spe) { // 如果特殊字符，则清空 dict
      ret = max(ret, int(dict.size())); // 记录一次，字符串长度
      left = i+1;
      dict.clear();
      continue;
    }

    if (left != i) { // 左边减去一个
      dict.erase(str[left]);
      left++;
    }

    while (i < str.size() && dict[str[i]] < 2) { // 右边在符合条件下，尽量向右扩展
      dict[str[i]]++;
      i++;
      ret = max(ret, int(dict.size())); // 记录字符串长度
    }
  }

  cout << ret << endl;

  return 0;
}