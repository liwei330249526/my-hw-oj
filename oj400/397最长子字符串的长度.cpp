/*
 *
题目描述
给你一个字符串s，字符串s 首位相连成一个环形，请你再环中找出 'l', 'o', 'x', 字符都恰好出现了偶数次最长子字符串的长度
输入
输入小写字母组成的字符串
输出
一个整数

样例1
输入
alolobo

输出
6


样例2
输入
looxdolx

输出
7

aaoaobo

 *
 * */

#include "iostream"
using namespace std;

/*
 * 2倍的str
 * 维护每个字母计数
 * 维护每个字母首次出现的位置
 *
 *
 * */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
//  'i', 'o', 'x'
int find_longest_even_o(const string& s, int n) {
  int status = 0;
  unordered_map<int, int> dict; // 某个状态出现的位置
  dict[0] = -1; // 初始状态位置-1， ??aa,  则status = 0， 则3-(-1) = 4 , 则有4个字符
  string exS = s + s;

  int ret = 0;
  for (int i = 0; i < exS.size(); i++) {
    // 计算状态
    if (exS[i] == 'l') {
      status = status ^ (1 << 0);
    } else if (exS[i] == 'o') {
      status = status ^ (1 << 1);
    } else if (exS[i] == 'x') {
      status = status ^ (1 << 2);
    }

    if(dict.find(status) != dict.end()) { // 有首次出现
      if (i - dict[status] <= n) {
        ret = max(ret, i - dict[status]);
      }

    } else { // 没有首次出现
      dict[status] = i;
    }
  }

  return ret;
}

int main() {
  string s;
  cin >> s; // 输入字符串
  cout << find_longest_even_o(s, s.size()) << endl; // 输出最长子字符串的长度
  return 0;
}


