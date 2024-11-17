/*
 *
题目描述
给定两个字符串s1和s2和正整数k，其中s1长度为n1，s2长度为n2，在s2中选一个子串，满足：
该子串长度为n1+k
该子串中包含s1中全部字母
该子串每个字母出现次数不小于s1中对应字母
我们称s2以长度k冗余覆盖s1，给定s1，s2，k，求醉左侧的s2以长度k冗余覆盖s1的子串的收个元素下表，如果没有，返回-1
 *
 * 样例1
输入
ab
aabcd
1

输出
0

 *
 * 样例2
输入
abc
dfs
10

输出
-1

 *
 * */

#include "string"
#include "iostream"
#include "unordered_map"

using namespace std;

// s2 是否包含了 s1
bool isS2ContainS1(unordered_map<char, int> &dict1, unordered_map<char, int> &dict2) {
  for (auto &it : dict1) {
    if (it.second > dict2[it.first]) {
      return false;
    }
  }

  return true;
}

int main() {
  string s1, s2;
  int k;
  cin >> s1 >> s2 >> k;
  int n1 = s1.size();
  int n2 = s2.size();

  unordered_map<char, int> dict1;
  unordered_map<char, int> dict2;

  // 记录str1 的字符计数
  for (char c : s1) {
    dict1[c]++;
  }

  int left = 0;
  for (int i = 0; i < s2.size(); i++) {
    dict2[s2[i]]++;
    // 包括 i 和 left
    if (i - left + 1 >= n1 + k) {
      // 校验 [left, i] 是否符合
      if (isS2ContainS1(dict1, dict2)) {
        cout << left << endl;
        return 0;
      } else {
        dict2[s2[left]]--;
        left++;
      }
    }
  }

  cout << -1 << endl;
  return 0;
}