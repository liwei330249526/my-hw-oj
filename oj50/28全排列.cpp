/*
 * 题目描述
 * 给定一个只不包含大写英文字母的字符串S，要求你给出S重新排列的所有不同的排列数
 * 如： S为 ABA 的不同排列数为 ABA  AAB  BAA 三种
 *
输入
ABA

输出
3



输入
ABCDEFGHHA

输出
907200

 * */

#include "string"
#include "iostream"
#include "unordered_map"
using namespace std;

int64_t getJ(int64_t a) {
  int64_t ret = 1;
  while (a > 0) {
    ret *= a;
    a--;
  }
  return ret;
}

int main() {
  string str;
  getline(cin, str);

  unordered_map<char, int> freq;
  for (char c : str) {
    freq[c]++;
  }

  int64_t tol = getJ(str.size());
  for (auto it = freq.begin(); it != freq.end(); it++) {
    tol /= getJ(it->second);
  }

  cout << tol << endl;

  return 0;
}