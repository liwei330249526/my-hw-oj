/*
 *
现有一个机器人放置在mxn网格的任意位置，每个网格包括一个数字，当相邻网格的数字小于或等于1时，机器人可以在网格间移动。
问题：机器人可活动的最大范围对应的网格点数目。

输入
第一行输入 m n ， 分别代表网格的行数和列数。
之后的m 行，代表m行网格值。

输出
1行，活动区域网格点

 *
 * 样例1
 * 输入
4 4
1 2 5 2
2 4 4 5
3 5 7 1
4 6 2 4




输出
6


 *
 * dfs 找最大的一片区域
 *
 * */

#include "iostream"
#include "vector"

using namespace std;

int dfs(int row, int col, vector<vector<int>> &gd, vector<vector<int>> &visited) {
  // 设置访问标记
  visited[row][col] = 1;
  vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
  int ret = 1; // 初始为 1

  // 如果按dir 方向延伸的点符合条件，且没有别访问过，则dfs 进去访问
  for (int i = 0; i < dirs.size(); i++) {
    int rowt = row+dirs[i][0];
    int colt = col + dirs[i][1];
    if (rowt >= 0 && rowt < gd.size() && colt >= 0 && colt < gd[0].size() &&
        visited[rowt][colt] == 0 && abs(gd[row][col] - gd[rowt][colt]) <= 1) {
      //
      ret += dfs(row+dirs[i][0], col+dirs[i][1], gd, visited);
    }
  }

  return ret;
}



int main() {
  int m;
  int n;
  m = 3;
  n = 6;
  cin >> m >> n;

  vector<vector<int>> gd(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> gd[i][j];
    }
  }
  vector<vector<int>> visited(m, vector<int>(n, 0));
//  for (int i = 0; i < m; i++) {
//    for(int j = 0; j < n; j++) {
//      cout << visited[i][j] << " ";
//    }
//    cout << endl;
//  }

  int ret = 0;
  for (int i = 0; i < gd.size(); i++) {
    for (int j = 0; j < gd[0].size(); j++) {
      if (visited[i][j] == 0) {
        ret = max(ret, dfs(i, j, gd, visited));
      }
    }
  }

  cout << ret << endl;

  return 0;
}