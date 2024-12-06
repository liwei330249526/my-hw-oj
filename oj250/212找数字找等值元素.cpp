/*
 *
题目描述
给一个二维数组 nums，对于每个元素 nums[i][j], 好处距离最近且值相等的元素，距离是两个数横纵坐标差绝对值的和，
如果没有等值元素，则输出-1

输入
第1行，输入矩阵rowLen行数
第2行，输入矩阵colLen列数
接下来输入 rowLen 行， colLen列的矩阵


 *
 *
 * 样例1
 * 输入
3
5
0 3 5 4 2
2 5 7 8 3
2 5 4 2 4

输出
[[-1,4,2,3,3],[1,1,-1,-1,4],[1,1,2,3,2]]

 *
 * */

#include "vector"
#include "iostream"
#include "unordered_map"
#include "stdint.h"
using namespace std;
int main() {
  int rowLen;
  int colLen;
  cin >> rowLen >> colLen;
  int inNum;
  unordered_map<int, vector<vector<int>>> valPos;
  vector<vector<int>> gd(rowLen, vector<int>(colLen));
  for (int i = 0; i < rowLen; i++) {
    for (int j = 0;j < colLen; j++) {
      cin >> inNum;
      gd[i][j] = inNum;
      valPos[inNum].push_back({i,j});
    }
  }

  vector<vector<int>> res(rowLen, vector<int>(colLen));
  for (int i = 0; i < rowLen; i++) {
    for (int j = 0; j < colLen; j++) {
      int curNum = gd[i][j];
      if (valPos[curNum].size() == 1) {
        res[i][j] = -1;
      } else {
        // 找一个最近的点
        int resV = INT32_MAX;
        for (auto it : valPos[curNum]) {
          if (it[0] == i && it[1] == j) {
            continue;
          }
          resV = min(resV, abs(it[0] - i) + abs(it[1] - j));
        }

        res[i][j] = resV;
      }
    }
  }

  cout << "[";
  for (int i = 0; i < rowLen; i++) {
    cout << "[";
    for (int j = 0; j < colLen; j++) {
      cout << res[i][j];
      if (j != colLen-1) {
        cout << ",";
      }
    }
    cout << "]";
    if (i != rowLen-1) {
      cout << ",";
    }
  }

  cout << "]";

  return 0;
}