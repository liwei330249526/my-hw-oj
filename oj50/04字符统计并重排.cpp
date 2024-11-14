/*
 * 题目描述
 * 给出一个仅包含字母的字符串，不包含空格，统计字符串中哥哥字母（区分大小写）出现的次数，
 * 并按照字母出现次数从大到校的顺序。输出各个字母机器出现次数。
 * 如果次数相同，按照自然顺序进行排序，且小写字母写在大写字母之前。
 *
 * 输入
 * aabbccddAABBCCDD
 *
 * 输出
 * a:2;b:2;c:2;d:2;A:2;B:2;C:2;D:2;
 *
 * */


/*
 * 思路
 * 1 unordered_map<char, int> 统计次数
 * 2 vector<Pair<char, int>>  排序
 * 3 sort 函数排序， 3.1 先大小 2 小写在前  3 字母顺序
 * 4 遍历vector，构造字符串
 * */

#include "string"
#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  string str;
  cin >> str;
//  cout << str << endl;
  unordered_map<char, int> m;
  for (char c : str) {
    m[c]++;
  }

  vector<pair<char, int>> sortArr;
  for (auto it : m) {
    sortArr.push_back(make_pair(it.first, it.second));
  }

  sort(sortArr.begin(), sortArr.end(), [](pair<char, int> &a, pair<char, int> &b) {
    if (a.second != b.second) {    // 按统计次数排序， 大的在前
      return a.second > b.second;
    }

    if (islower(a.first) != islower(b.first)) { // 一个小写，一个大写
      if (islower(a.first)) {
        return true;
      } else {
        return false;
      }
    }

    return a.first < b.first; // 按字母排序
  });

  for (auto it : sortArr) {
    cout << it.first << ":" << it.second << ";";
  }
  cout << endl;

  return 0;
}