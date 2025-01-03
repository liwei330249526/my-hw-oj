/*
 *
题目描述
输入m和n两个数，m和n 表示一个m*n 的棋盘。输入棋盘内的数据。棋盘中存在数字和 '.' 两种字符，如果是数字表示该位置一匹马，如果是 '.' 表示
该位置是空的，棋盘内的数字 表示该马能走的最大步数。
例如棋盘内某个位置一个数字位k，表示该马只能移动1-k步距离。
棋盘内的马移动类似中国象棋中马移动，先在水平或数值方向移动一格，然后将其移动到对角线位置。
棋盘内的马可以移动同一个位置，同一个位置可以有多匹马。
请问能否将棋盘上所有的马移动到同一个位置，若可以，请输入动一动的最小步数。若干不可以输出-1.

输入
输入m和n两个数，m和n表示一个m*n的棋盘。输入棋盘内的数据。
输出
能否将棋盘上所有马移动到同一个位置，若可以请输入移动的最小步数。若不可以输出-1.


样例1
输入
3 2
. .
2 .
. .



输出
0
    '  |  '
 '     |    '
 ------|--------
 '     |    '
    '  |  '
 （-1，2）(-2,1)   (1,2) (2,1)   (1,-2) (2,-1)  (-1,-2) (-2,-1)    8个方向

 遍历每匹马， 记录它能到的所有位置；
 所有马都能到大的位置的  最小步数.
 *
 *
 * */

#include "iostream"
#include "vector"
#include "queue"
using namespace std;

// bfs 扩散
void bfs(int row, int col, int msteps, vector<vector<int>> &allows) {
  vector<vector<int>> dirs = {{-1,2},{-2,1},{1,2},{2,1}, {1,-2},{2,-1},{-1,-2},{-2,-1}};
  queue<vector<int>> que;
  que.push({row, col});  // 将点 row， col 加入que

  int step = 0;
  while (!que.empty() && step < msteps) {   // 1 < 2;
    step++;   // 接下来的的逻辑尝试走1步
    int size = que.size();
    for (int i = 0; i < size; i++) {
      int curR = que.front()[0];  // 获取左边的点
      int curC = que.front()[1];
      que.pop();

      // 8 个方向感染
      for (int j = 0; j < dirs.size(); j++) { // 8 个方向； 嵌套循环的 index 使用错误
        int nr = curR + dirs[j][0];
        int nc = curC + dirs[j][1];
        if (nr >= 0 && nr < allows.size() && nc >= 0 && nc < allows[0].size() && allows[nr][nc] == -1) {
          que.push({nr, nc}); // 加入que 的时候，将step 设置
          allows[nr][nc] = step;
        }
      }
    }
  }
}

void resetAllows(vector<vector<int>> &allows) {
  for (int i = 0; i < allows.size(); i++) {
    for (int j = 0; j < allows[0].size(); j++) {
      allows[i][j] = -1;
    }
  }
  return;
}

void handleAllows(vector<vector<int>> &tol, vector<vector<int>> &allows) {
  for (int i = 0; i < tol.size(); i++) {
    for (int j = 0; j < tol[0].size(); j++) {
      if (allows[i][j] == -1) {  // 如果该马，不可达 i，j位置，则设置tol[i][j] 为-1
        tol[i][j] = -1;
      } else {
        if (tol[i][j] != -1) {   // 如果tol 可达， 则累加本马的计数
          tol[i][j] += allows[i][j];
        }
      }
    }
  }
  return;
}

int main() {
  int rows;
  int cols;
  cin >> rows >> cols;
  vector<vector<int>> gd(rows, vector<int>(cols));

  // 获取地图
  string input;
  vector<vector<int>> que;   // (x,y, steps)
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> input;
      if (input != ".") {
        que.push_back({i, j, stoi(input)}); // 如果是数马，则加入que中
      }
    }
  }

  vector<vector<int>> tol(rows, vector<int>(cols, 0));
  vector<vector<int>> allows(rows, vector<int>(cols, -1));  // 每个点是否可达
  for (int i = 0; i < que.size(); i++) { // 遍历所有马， 进行bfs 跳跃
    // 对每个马进行bfs 操作
    int row = que[i][0];
    int col = que[i][1];
    int msteps = que[i][2];
    resetAllows(allows);
    allows[row][col] = 0; // 马原先所在位置无需走， 即0步
    bfs(row, col, msteps, allows);
    handleAllows(tol, allows);
  }


  int ret = -1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (tol[i][j] != -1) {
        if (ret == -1) { // 第一个
          ret = tol[i][j];
        } else {
          ret = min(ret, tol[i][j]);  // 后续计算最小的
        }
      }
    }
  }

  cout << ret << endl;

  return 0;
}