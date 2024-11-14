/*
 * 题目描述
 * 给定一个正整数数组，设为nums，求从第一个元素到最后一个元素，所使用的最少步骤数。
 * 要求
 * 1 第一步必须从第一个元素开始，1<= 第一步步数 < len/2
 * 2 从第二步开始, 只能以对应位置的数字作为相应的步数，如果目标不可达则返回-1， 否则输出最少步数.
 *
 * 样例1
输入
7 5 9 4 2 6 8 3 5 4 3 9

输出
2

说明：
第一步:第一个可选步长选择2,从第一个成员7开始走2步, 到达9;
第二步:从9开始，过自身数字9对应的9个成员到最后。

 *
 *
 * 样例2
输入
1 2 3 7 1 5 9 3 2 1

输出
-1

 *
 * 样例3
输入
1 2 3 4 5

输出
-1

 *
 * 样例4
输入
3 2 1 4 5

输出
-1

 *
 * 样例5
输入
1 1 1 1 1

输出
4

 *
 * 样例6
输入
2 4 6 8 10

输出
-1

 *
 * 样例7
输入
1 3 5 7 9

输出
2

 *
 * 样例8
输入
2 1 3 2 4 3 5 4 6 5

输出
-1

 *
 *
 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "unordered_map"
#include "deque"
#include "queue"
using namespace std;
/*
 * 广度优先搜索
 * */
int main() {
  // 获取字符串
  string str;
  getline(cin, str);

  vector<int> arr;
  string token;
  stringstream stm(str);
  // 获取数字数组
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  // 初始化步数为1, 初始化que
  int step = 1;
  deque<int> que;
  unordered_map<int, int> dict;
  for (int i = 0; i < arr.size() / 2; i++) {
    que.push_back(i);
    dict[i] = 1;
  }

  // 广度优先搜索
  bool find = false;
  while (!que.empty()) {
    int size = que.size();
    step++; // 步数
    for (int i = 0; i < size; i++) {
      int cur = que.front();
      que.pop_front();
      int target = cur + arr[cur];

      if (target == arr.size() - 1) {
        find = true;
        break;
      }

      if (dict.find(target) == dict.end()) { // 还未访问
        que.push_back(target);
        dict[target] = 1;
      }
    }

    if (find) {
      break;
    }
  }

  if (find) {
    cout << step << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}