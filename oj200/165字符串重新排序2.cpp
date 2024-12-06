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

  // 用一个 rank 递增的数字数组辅助排序
  sort(rank.begin(), rank.end(), [&](int i, int j) ->bool {
      if (dict[words[i]] != dict[words[j]]) {
        return dict[words[i]] > dict[words[j]];
      }

      if (words[i].size() != words[j].size()) {
        return words[i].size() < words[j].size();
      }

      return words[i] < words[j];
  });

  for (int i = 0; i < rank.size(); i++) {
    cout << words[rank[i]];
    if (i != rank.size()-1) {
      cout << " ";
    }
  }
  cout << endl;
  return 0;
}