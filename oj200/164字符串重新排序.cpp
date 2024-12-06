/*
 *
题目描述
给定一个字符串s， s包括以空格分隔的若干单词，请对s进行一下处理后输出：
1 单词内部调整：对每个单词字母重新按字典序排序
2 单词间顺序调整：
  1统计每个单词出现的次数，并按次数降序排列
  2次数相同，按单词长度升序排列
  3 次数和单词长度均相同，按字典升序排列
 *
 * 样例1
 * 输入
This is an apple

输出
an is This apple

 *
 * 样例2
 * 输入
My sister is in the house not in the yard

输出
in in eht eht My is not adry ehosu eirsst
 *
 * */


#include "iostream"
#include "string"
#include "vector"
#include "sstream"
#include "algorithm"
#include "unordered_map"
using namespace std;
int main() {
  string str;
  getline(cin, str);
  vector<string> words;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    sort(token.begin(),token.end());
    words.push_back(token);
  }

  vector<int> rank(words.size());
  for (int i = 0; i < rank.size(); i++) {
    rank[i] = i;
  }

  unordered_map<string, int> dict;
  for (string word : words) {
    dict[word]++;
  }

  vector<pair<string, int>> sortedStr;  // 字符串，次数
  for (auto it : dict) {
    sortedStr.push_back(it); // 直接将 map 的迭代器 it push 到 vector<pair<string, int>> 中
  }

  sort(sortedStr.begin(), sortedStr.end(), [&](pair<string, int> &a, pair<string, int> b) ->bool {
      if (a.second != b.second) {
        return a.second > b.second;
      }

      if (a.first.size() != b.first.size()) {
        return a.first.size() < b.first.size();
      }

      return a.first < b.first;
  });

  vector<string> res;
  for (int i = 0; i < sortedStr.size(); i++) {
    for (int j = 0; j < sortedStr[i].second; j++) {
      res.push_back(sortedStr[i].first);
    }
  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << " ";
    }
  }

  cout << endl;
  return 0;
}