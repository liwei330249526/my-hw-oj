/*
 * 题目描述
 * 1 单词中的字母比较不区分大小写，两个单词先以第一个字母作为排序的基准，如果第一个字母
 * 相同，就用第二个字母作为基准，如果第二个字母相同就以第三个字母为基准。
 * 以此类推，如果到某个字母不相同，字母顺序在前的那个单词顺序在前。
 * 2 DNA一个短单词和一个长单词的开头部分都相同（即短单词是长单词从首字母开始的一部分），段单词
 * 顺序在前。
 * 3 字母大小写不同的相同单词，只输出一次。
 *
输入
Hello hello world


输出
Hello world



 *
输入
i LOVE Cc I love CC Hello Hel Hellow


输出
Cc Hel Hello Hellow i LOVE


 * */

#include "string"
#include "iostream"
#include "vector"
#include "unordered_map"
#include "sstream"
#include "algorithm"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  stringstream stm(str);
  vector<string> words;
  string token;
  while (getline(stm, token, ' ')) {
    words.push_back(token);
  }

  // map, key 为word 转换为小写字符串后的字符串， value 为第一个word
  unordered_map<string, int> dict;
  for (int i = 0; i < words.size(); i++ ) {
    string word = words[i];
    string sortWord = word;
    transform(sortWord.begin(), sortWord.end(), sortWord.begin(), [](char c) {
      return tolower(c);
    });

    if (dict.find(sortWord) == dict.end()) {
      dict[sortWord] = i;
    }
  }

  // 将key，val 放在数组中， 对key 进行排序
  vector<pair<string ,int>> pairs;
  for (auto it : dict) {
    pairs.push_back(make_pair(it.first, it.second));
  }

  sort(pairs.begin(), pairs.end(), [](pair<string, int> &p1, pair<string ,int> p2) ->bool {
    return p1.first < p2.first;
  });

  for (int i = 0; i < pairs.size(); i++) {
    cout << words[pairs[i].second];
    if (i != pairs.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}