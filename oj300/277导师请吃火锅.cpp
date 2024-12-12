/*
 *
题目描述
入职后，导师会请你吃饭，你选择了火锅，火锅里会在不同时间下很多菜
不同食材要煮不同的时间，才能变得刚好合适，你希望吃到最多的刚好合适的菜，单你的手速不够快，用m代表手速，每下手捞菜后至少要过ms才能再捞（每次只能捞一个）
那么勇最合理的策略，最多能吃到的合适的菜


输入
第一行两个整数， n， m ， 其中n代表锅里下的菜的个数，m代表手速。
接下来有n行，每行有两个整数，x，y 代表第x秒下的菜，再过y秒才能变得合适

输出
输出一个整数代表用最合理的策略，最多能吃到刚好合适的菜的数量

样例1
输入
2 1
1 2
2 1

输出
1

按尾部排序
按 start 排序
  [              ]             ok
    [      ]                   not ok
               [        ]      not ok

按 end 排序
     [       ]                 ok
  [              ]             not ok
                [      ]       ok
 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

struct DishCompare {
  bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
    return p1.first + p1.second < p2.first + p2.second;
  }
};

int main() {
  int n;  // n个菜
  int freeze; // 取菜冷却
  cin >> n >> freeze;

  vector<pair<int, int>> dishes(n);
  for (int i = 0; i < n; i++) {
    cin >> dishes[i].first >> dishes[i].second;
  }

  sort(dishes.begin(), dishes.end(), DishCompare());

  int count = 0;
  int lastEnd = 0; // 上次结束时间， 包括冷却时间
  for (int i = 0; i < dishes.size(); i++) {
    if (lastEnd <= dishes[i].first + dishes[i].second) { // 如果上次结束时间小于或等于当前 i 菜的合适时间， 则可以吃到
      count++;
      lastEnd = dishes[i].first + dishes[i].second + freeze;
    }
  }

  cout << count << endl;

  return 0;
}