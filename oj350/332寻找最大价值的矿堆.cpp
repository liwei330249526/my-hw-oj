/*
 *
题目描述
给你一个由 '0'空地， '1' 银矿， '2' 金矿， 组成的地图，矿堆只能由上下相邻的金矿或银矿形成。超出地图范围可认为是一个空地。
假设银矿价值1，金矿价值2，请找出地图中最大价值的矿堆，并输出矿堆的价值。

输入
地图元素信息
输出
地图元素信息

样例1
输入
22220
00000
00000
01111




输出
8


 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  vector<string> strArr;
  string str;
  while (getline(cin, str)) {
    if (str.empty()) {
      break;
    }
    strArr.push_back(str);
  }
  int ret = 0;
  int curRet;
  vector<vector<bool>> vs(strArr.size(), vector<bool>(strArr[0].size())); // 记录访问过
  vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
  auto dfs = [&](auto &&dfs, int row, int col) {
      if (row < 0 || row >= strArr.size() || col < 0 || col >= strArr[0].size()) {
        return;
      }
      if(strArr[row][col] == '0' || vs[row][col]) {
        return;
      }

      vs[row][col] = true; // 访问过
      if (strArr[row][col] == '1') {
        curRet += 1;
      } else if (strArr[row][col] == '2'){
        curRet += 2;
      }

      for (int i = 0; i < dirs.size(); i++) {
        dfs(dfs, row + dirs[i][0], col + dirs[i][1]);
      }
      return;
  };

  for (int i = 0; i < strArr.size(); i++) {
    for (int j = 0; j < strArr[i].size(); j++) {
      if (strArr[i][j] != '0' && vs[i][j] == 0) {
        curRet = 0;
        dfs(dfs, i, j);
        ret = max(ret, curRet);
      }
    }
  }
  cout << ret << endl;
  return 0;
}