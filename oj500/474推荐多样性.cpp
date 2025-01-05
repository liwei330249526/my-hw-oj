/*
 *
题目描述
推荐多样性需要从多个列表中厕元素，一次性要返回N屏数据（窗口数量），每屏展示K个元素（窗口大小），选择策略：
各个列表元素要做穿插处理，即先从第一个列表中为每屏选择一个元素，再从第二个列表汇总为每屏选择一个元素，依次类推，
每个额列表的元素尽量分为N份，如果不够N个，也要全部分配完，参考例图：


样例1
输入
4
7
0 1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29



输出
0 10 20 4 14 24 8 1 11 21 5 15 25 9 2 12 22 6 16 26 18 3 13 23 7 17 27 19
解释
4 个窗口， 每个窗口 7 个元素.
从第1行中选4个， 分别放在每个窗口中
从第2行中选4个，分别放在每个窗口中。



样例2
输入
3
5
0 1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29


输出
0 10 20 3 13 1 11 21 4 14 2 12 22 5 15

 *
 * */

#include "iostream"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  int windowNum;
  int windowSize;
  string str;
  getline(cin, str);
  windowNum = stoi(str);

  getline(cin, str);
  windowSize = stoi(str);

  // 获取所有列表
  vector<vector<int>> arrs;
  while (getline(cin, str)) {
    if (str.size() == 0) {
      break;
    }

    stringstream stm(str);
    string token;
    vector<int> arr;
    while (getline(stm, token, ' ')) {
      arr.push_back(stoi(token));
    }
    arrs.push_back(arr);
  }

  vector<vector<int>> windows(windowNum, vector<int>());   // num 个窗口
  vector<int> ids(arrs.size());  // 维护每个列表的 index

  int tol = windowNum * windowSize;
  int count = 0;

  int j = 0; // 第j个window
  while (count < tol) {
    // 遍历每个列表， 从每个列表选出 windowNum 个数字加入到每个 window中
    int curCount = 0;
    for (int i = 0; i < arrs.size(); i++) {
      for (int j = ids[i]; j < arrs[i].size(); j++) { // 遍历每个数字
        curCount++; // 共 windowNum 个数字了
        count++;
        ids[i] = j+1; // 保存 index， 下一次开始的位置
        windows[curCount-1].push_back(arrs[i][j]);

        if (curCount == windowNum) { // 找到了 windowNum个数字.  curCount 置0， 并从下一行继续寻找
          curCount = 0;
          break;
        }

        if(count == tol) {
          break;
        }
      }
      if(count == tol) {
        break;
      }
    }
  }

  // 输出每个 window
  for(int i = 0; i < windows.size(); i++) {
    for (int j = 0; j < windows[i].size(); j++) {
      cout << windows[i][j];
      if (!( i == windows.size()-1 && j == windows[i].size()-1)) {
        cout << " ";
      }
    }
  }

  return 0;
}