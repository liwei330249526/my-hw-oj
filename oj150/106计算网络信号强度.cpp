/*
 *
题目描述
网络信号经过传递会逐层衰减，且粤澳组个无无法穿透，但网络信号可以绕过阻隔物，在此情况下需要计算某个位置的信号值。
arr[m][n] 的二位数组代表网格地图
arr[i][j] = 0 代表此位置是空旷位置.
arr[i][j] = x ， x 为正整数代表此为止是信号源。
arr[i][j] = -1, 代表此为止是阻隔物。

求某位置的网络信号值
 *
 * 样例1
输入
6 5
0 0 0 -1 0 0 0 0 0 0 0 0 -1 4 0 0 0 0 0 0 0 0 0 0 -1 0 0 0 0 0
1 4
解释： 第一行表示输入是一个6行5列的矩阵；第2行是矩阵； 第3行是求[1][4] 的信号值


输出
2


 *
 *
 * 样例2
输入
6 5
0 0 0 -1 0 0 0 0 0 0 0 0 -1 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 1


输出
0

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "deque"
using namespace std;
// bfs
int main() {
  int m;
  int n;
  cin >> m >> n;

  vector<vector<int>> mt(m, vector<int>(n)); // 保存矩阵
  vector<vector<int>> fg(m, vector<int>(n)); // 加入到 que 的标记
  deque<vector<int>> que;

  // 获取整个矩阵
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> mt[i][j];
    }
  }

  // 获取target x，y
  int targetX;
  int targetY;
  cin >> targetX >> targetY;

  // 获取源 x, y
  int originX = -1;
  int originY = -1;
  bool findOrigin = false;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mt[i][j] > 0) {
        que.push_back(vector<int>{i,j});
        fg[i][j] = 1; // 标记加入了 que
        originX = i;
        originY = j;
        if (targetX == i && targetY == j) {
          cout << mt[i][j] << endl;
          return 0;
        }
        findOrigin = true;
        break;
      }
    }

    if (findOrigin) {
      break;
    }
  }

  // 4 个方向
  vector<vector<int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};

  int step = 0; // 共走了多少步
  // bfs 大法
  while (!que.empty()) {
    int size = que.size();
    step++; // 第一次bfs 扩散
    bool find = false;
    for (int i = 0; i < size; i++) {  // 获取里面的点，尝试向4个方向走一步
      vector<int> point = que.front(); // 从左向右pop
      que.pop_front();

      if (mt[point[0]][point[1]] == -1) { // 如果该点是障碍，则不计
        continue;
      }

      // 4 个方向
      for (int j = 0; j < dirs.size(); j++) {
        // 获取4个方向的点的值
        int nx = point[0] + dirs[j % 4][0];
        int ny = point[1] + dirs[j % 4][1];
        // 第一次4个方向寻找
        if(nx >= 0 && nx < m && ny >= 0 && ny < n && mt[nx][ny] == 0 && fg[nx][ny] == 0) { // nx, ny 是空地，且未加入过que
          // 第1，2 .. 次扩散过程中，找到了目标，则break
          if (nx == targetX && ny == targetY) {
            find = true;
            break;
          }

          que.push_back(vector<int>{nx, ny});
          fg[nx][ny] = 1;
        }
      }

      if (find) {
        break;
      }
    }

    if (find) {
      break;
    }
  }

  int ret = max(0, mt[originX][originY] - step);

  cout << ret << endl;
  return 0;
}