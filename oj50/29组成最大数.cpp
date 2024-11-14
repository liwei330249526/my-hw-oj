/*
 * 题目描述
 * 小组中每位都有一张卡片，卡片上是6位以内的正整数，将卡片连起来可以组成多种数字，计算组成的最大数字
 *
输入
22,221

输出
22221


输入
4589,101,41425,9999

输出
9999458941425101

 * */

#include "string"
#include "vector"
#include "iostream"
#include "sstream"
#include "algorithm"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  string token;
  vector<string> arrs;
  stringstream stm(str);
  while(getline(stm, token, ',')) {
    arrs.push_back(token);
  }

  sort(arrs.begin(), arrs.end(), [](string &a, string &b) {
    return a+b > b+a;
  });

  string ret;
  for (string s : arrs) {
    ret += s;
  }

  cout << ret << endl;

  return 0;
}