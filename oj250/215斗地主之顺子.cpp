/*
 *
题目描述
在斗地主扑克牌游戏中，扑克牌由小到大的顺序为： 3，4，5，6，7，8，9，10，J, Q, K, A, 2； 玩家可以出的扑克牌阵型有：
单张，对子，顺子，飞机，炸弹等
其中顺子的出牌规则为：由至少5张连续递增的扑克牌组成，且不能包含2
给定一个包含13张牌的数组，如果有满足出牌规则数字你，请输出顺子
如果存在多个顺子，请每行输出一个好孙子，且需要按顺子的第一张牌的大小（必须从下到大）一次输出
如果没有满足出牌规则的顺子，清楚No
 *
 * 样例1
 * 输入
2 9 J 2 3 4 K A 7 9 A 5 6

输出
3 4 5 6 7

说明：
13张牌中，可以组成的顺子只有1组: 3 4 5 6 7

 *
 *
 * 样例2
 * 输入
2 9 J 10 3 4 K A 7 Q A 5 6

输出
3 4 5 6 7
9 10 J Q K A

说明：
13张牌中，可以组成2组顺子,从小到大分别为: 3 4 5 6 7和 9 10 J Q K A


 *
 * 样例3
 * 输入
2 9 9 9 3 4 K A 10 Q A 5 6

输出
No

说明：
13张牌中，无法组成顺子。


 *
 * 样例4
 * 输入
3 4 5 6 6 7 8 7 8 8 9 J Q

输出
3 4 5 6 7 8 9

 *
 *
 * 样例5
 * 输入
3 4 5 6 7 3 4 5 6 7 A A A

输出
3 4 5 6 7
3 4 5 6 7

 *
 * */

#include "iostream"
#include "string"
#include "unordered_map"
#include "vector"
#include "sstream"
#include "algorithm"
using namespace std;


int main() {
  string str;
  getline(cin, str);
  unordered_map<string, int> dict{
          {"3", 3},
          {"4", 4},
          {"5", 5},
          {"6", 6},
          {"7", 7},
          {"8", 8},
          {"9", 9},
          {"10", 10},
          {"J", 11},
          {"Q", 12},
          {"K", 13},
          {"A", 14},
  };

  unordered_map<int, string> revDict{
          {3, "3"},
          {4, "4"},
          {5, "5"},
          {6, "6"},
          {7, "7"},
          {8, "8"},
          {9, "9"},
          {10, "10"},
          {11, "J"},
          {12, "Q"},
          {13, "K"},
          {14, "A"},
  };

  vector<string> cards;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    if (token == "2") {
      continue;
    }
    cards.push_back(token);
  }

  unordered_map<int, int> cardsNums; // 每个牌对应的值， 的数量计数
  for (int i = 0; i < cards.size(); i++) {
    string card = cards[i];
    cardsNums[dict[card]]++;
  }

  vector<vector<int>> resNum;
  while (true) {
    vector<int> rest;
    bool find = false;
    for (int i = 3; i <= 13; i++) {
      if (cardsNums[i] <= 0) {
        continue;
      }

      if (rest.size() == 0) { // 加入
        rest.push_back(i);
        cardsNums[i]--;
      } else {
        if (rest.back() + 1 == i) { // 顺着，加入
          rest.push_back(i);
          cardsNums[i]--;
        } else {                    // 不顺，则判断是否符合，复合加入结果集； 然后重新计数
          if (rest.size() >= 5) { // 找到了一个
            resNum.push_back(rest);
            find = true;
          }               // 从i开始从新找
            rest.clear();
            rest.push_back(i);
            cardsNums[i]--;
        }
      }
    }

    if(rest.size() >= 5) {
      resNum.push_back(rest);
      find = true;
    }

    if (!find) {
      break;
    }
  }
  sort(resNum.begin(), resNum.end(), [](vector<int> &a, vector<int> &b){
    return a[0] < b[0];
  });
  if (resNum.size() == 0) {
    cout << "No" << endl;
  } else {
    for (int i = 0; i < resNum.size(); i++) {
      for (int j = 0; j < resNum[i].size(); j++) {
        cout << revDict[resNum[i][j]];
        if (j != resNum[i].size()-1) {
          cout << " ";
        }
      }
      cout << endl;
    }
  }

  return 0;
}