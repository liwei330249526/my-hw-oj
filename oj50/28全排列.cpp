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


思路：
排列组合思路
n个数字的排列数为， n!  n*(n-1)*(n-2)...(2)*(1)
如果里面有个数字有 m个。 则排列数为 m!
不重复的排列数为  n!/m!
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
  for (char c : str) { // 字符计数
    freq[c]++;
  }

  int64_t tol = getJ(str.size()); // 总排列数
  for (auto it = freq.begin(); it != freq.end(); it++) { // 除以 每个字符计数的排列数
    tol /= getJ(it->second);
  }

  cout << tol << endl;

  return 0;
}