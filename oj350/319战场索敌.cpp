/*
 *
题目描述
有一个大小是 N*M 的战场地图，被墙壁 # 分隔成大小不同的区域，上下左右4个方向乡里的空地 . 属于同一个区域，只有空地上可能存在敌人
E， 请求出地图上总共有udoshao区域的敌人小于K

输入
第一行输入为N M K
N 表示地图的行数，M 代表地图的列数，K 代表目标敌人的数量，之后为一个 N * M 大小的字符数组
输出
敌人数小于K的区域数量

样例1
输入
3 5 2
..#EE
E.#E.
###..


输出
1

说明：
地图被墙壁分为两个区域，左边区域有1个敌人，右边区域有3个敌人，符合条件的区域数量是1



样例2
输入
4 4 3
..#.
E..E
.#E.
..##


输出
0


遍历矩阵，如果是 . , 则计算区域人数


 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int N;
  int M;
  int K;
  cin >> N >> M >> K;

  vector<vector<char>> gd(N, vector<char>(M));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> gd[i][j];
    }
  }


  vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
  int curCount = 0;
  vector<vector<int>> vs(N, vector<int>(M));
  auto dfs = [&](auto &&dfs, int row, int col) {
    if (row < 0 || row >= gd.size() ||
        col < 0 || col >= gd[0].size()) {
      return;
    }

    // 如果访问过，则返回
    if (vs[row][col] == 1) {
      return;
    }

    // 如果是墙 ，则返回
    if (gd[row][col] == '#') {
      return;
    }

    vs[row][col] = 1; // 设置访问
    if(gd[row][col] == 'E') { // 发现敌人
      curCount++;
    }


    // 个方向递进
    for (int i = 0; i < dirs.size(); i++) {
      dfs(dfs, row + dirs[i][0], col + dirs[i][1]);
    }
    return;
  };

  // 是否访问过

  int ret = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (gd[i][j] != '#' && vs[i][j] == 0) {
        curCount = 0;
        dfs(dfs, i, j);
        if (curCount != 0 && curCount < K) {
          ret++;
        }
      }
    }
  }

  cout << ret << endl;
  return 0;
}

