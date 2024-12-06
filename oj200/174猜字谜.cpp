/*
 *
题目描述
小王设计了一个简单的猜字谜游戏，游戏的谜面是一个错误的单词，比如 nesw, 玩家需要猜出谜底库中正确的单词。猜中的要求如下：
对于某个谜面和谜底的单词，满足下面任一条件都表示猜中：
1 变换顺序以后一样的，比如通过变化w 和 e 的顺序， "nwes" 跟 "news" 是可以完全对应的。
2 字母去重以后是一样的，比如 "woood" 和 "wood" 是一样的，他们去重后都是 "wod"
请你写一个程序帮忙在谜底库中找到正确的谜底。米面是多个单词，都需要找到对应的谜底，如果找不到的话，返回 "not found".

输入
1 谜面单词列表，以"," 分隔
2 谜底库单词列表，以 "," 分隔

输出
匹配到的正确单词列表，以"," 分隔
如果找不到，返回 "not found"
 *
 * 样例1
 * 输入
conection
connection,today

输出
connection

 *
 * 样例2
 * 输入
bdni,wooood
bind,wrong,wood

输出
bind,wood

 *
 *
 * 去重后比较
 * unorder_set 比较
 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "unordered_set"
#include "sstream"
using namespace std;
int main() {
  string riddleStr;
//  getline(cin, riddleStr);
  cin >> riddleStr;

  string answerStr;
//  getline(cin, answerStr);
  cin >> answerStr;
  // 谜面
  vector<string> riddles;
  string token;
  stringstream riddleStm(riddleStr);
  while (getline(riddleStm, token, ',')) {
    riddles.push_back(token);
  }

  // 谜底库
  vector<string> answers;
  stringstream answerStm(answerStr);
  while (getline(answerStm, token, ',')) {
    answers.push_back(token);
  }

  vector<string> ret;
  for (int i = 0; i < riddles.size(); i++) {
    // 谜面集合
    unordered_set<char> riddleSet(riddles[i].begin(), riddles[i].end());
    bool find = false;
    for (int j = 0; j < answers.size(); j++) {
      unordered_set<char> answerSet(answers[j].begin(), answers[j].end());
      if (riddleSet == answerSet) {
        ret.push_back(answers[j]);
        find = true;
        break;
      }
    }
    if (!find) {
      ret.push_back("not found");
    }
  }

  for (int i = 0; i< ret.size(); i++) {
    cout << ret[i];
    if (i != ret.size()-1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}