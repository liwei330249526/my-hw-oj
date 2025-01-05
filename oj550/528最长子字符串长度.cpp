/*
 *
题目描述
给你一个字符串s，首位相连成一个环形，请你在环中找出 'o' 出现了偶数次最长子字符串的长度。
输入
输入一个小写字母组成的字符串

输出
输出一个整数

样例1
输入
alolobo


输出
6


说明：
最长子字符串之一是 "alolob"，它包含2个'o'


样例2
输入
looxdolx


输出
7

说明：
最长子字符串"oxdolxl"，由于是首尾连接一起的，所以最后一个'x'和开头的'l'是连接在一起的，此字符串包含2个'o'

样例3
输入
bcbcbc


输出
6

说明：
这个示例中，字符串"bcbcbc"本身就是最长的，因为'o'都出现了0次。

 *
 * */

/*
 *
 * 思路，判断 o 的个数， 如果是 偶数个， 则返回字符串长度
 *                    如果是奇数个，则返回字符串长度-1
 *                    因为，首位相连，总能找到一个 o ，将其删除， 剩余的字符串的组成一个串
 *
 * */

#include "iostream"
using namespace std;
int main() {
  string str;
  cin >> str;
  int count = 0;
  for (int i = 0; i < str.size(); i++) {
    if(str[i] == 'o') {
      count++;
    }
  }
  if (count % 2 == 0) {
    cout << str.size() << endl;
  } else {
    cout << str.size()-1 << endl;
  }

  return 0;
}