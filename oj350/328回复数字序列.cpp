/*
 *
题目描述
对于一个连续正整数数组的序列，可以将其拼接成一个字符串，再将字符串里的部分字符打乱顺序。如 8 9 10 11 12， 拼接成的字符串 81101112，打乱
一部分字符后得到90811211，原来的正整数10就被拆成了0和1
先给定一个按如上规则得到的打乱字符的字符串，请将其还原成连续的正整数序列，并输出序列中最小的数字


输入
输入1行，为打乱的字符串和正整数序列的长度，两者空格分隔，字符串长度不超过200， 正整数不超过1000， 保证输入可以还原成唯一序列
输出
输出一个数字，为列中最小的数字。

样例1
输入
19801211  5


输出
8

样例2
输入
432111111111 4


输出
111



 *
 *
 * */

#include "string"
#include "iostream"
#include "unordered_map"
#include "vector"
using namespace std;


int test1() {
  string str;
  int n;
  cin >> str >> n;

  // 字符统计
  unordered_map<char, int> dict1;
//  vector<int> dict1(10);
  for (int i = 0; i< str.size(); i++) {
    dict1[str[i]]++;
  }

  int width = str.size() / n;

  int numStart = 1;
  int numEnd = 1000;

  for (int i  = numStart; i <= numEnd; i++) { // 从每个数字开始
    unordered_map<char, int> dict2;
//    vector<int> dict2(10);
    for (int j = i ; j < i + n; j++) { // n 个数字
      int num = j;
      string numStr = to_string(num);
      for (int j = 0; j < numStr.size(); j++) {
        dict2[numStr[j]]++;
      }
    }

    if (dict1 == dict2) {
      cout << i << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}

// 滑动窗口
int test2() {
  string str;
  int n;
  cin >> str >> n;

  // 字符统计
//  unordered_map<char, int> dict1;
  vector<int> dict1(10);

  for (int i = 0; i< str.size(); i++) {
    dict1[str[i] - '0']++;
  }

  int numStart = 1;
  int numEnd = 1000;
//  unordered_map<char, int> dict2;
  vector<int> dict2(10);

  for(int i = numStart; i <= n; i++) {
    int num = i;
    string numStr = to_string(num);
    for (int j = 0; j < numStr.size(); j++) {
      dict2[numStr[j] - '0']++;
    }
  }

  if (dict1 == dict2) {
    cout << 1 << endl;
    return 0;
  }

  int left = 1; // 将要删除1
  int right = n+1;  // 将要加上n
  while (right <= numEnd) {
    string numStr = to_string(left);
    for (int j = 0; j < numStr.size(); j++) {
      dict2[numStr[j] - '0']--;
    }

    numStr = to_string(right);
    for (int j = 0; j < numStr.size(); j++) {
      dict2[numStr[j] - '0']++;
    }

    left++;
    right++;
    if (dict1 == dict2) {
      cout << left << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return  0;
}


int main() {
  test2();
  return 0;

}