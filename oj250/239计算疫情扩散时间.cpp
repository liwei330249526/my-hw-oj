/*
 *
题目描述
在一个地图中（地图由n*n个区域组成），有部分区域被感染病菌，感染区域每天都会把周围(上下左右)4个区域感染，请根据给定的地图计算，
多少天后，全部区域会被感染，如果初始地图上的所有区域全部都别感染; 或者没有被感染区域，返回-1.

输入
一行n*n 个数字(只包含0，1 不会由其他数字)，表示一个地图，数字用, 分隔， 0 表示未感染区域，1表示已经感染区域，每n个数字表示地图的一行，
输入数据共表示n行n列的区域地图。

例如输入 1,0,1,0,0,0,1,0,1 表示地图
1，0，1
0，0，0
1，0，1

输出
一个整数，表示多少天后，全部区域都被感染


样例1
输入
1,0,1,0,0,0,1,0,1


输出
2

说明：
1天以后，地图中仅剩余中心点未被感染; 2天以后，全部被感染


样例2
输入
1,1,1,1,1,1,1,1,1

输出
-1

说明：
全部都感染



 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "algorithm"
#include "cmath"
#include "deque"
using namespace std;
int main() {
  string str;
  cin >> str;

  // 获得地图所有数字
  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }

  // 地图行数， 或列数
  int n = sqrt(arr.size());
  if (n * n != arr.size()) {
    return 0;
  }

  // 填充地图
  int mtIndex = 0;
  deque<vector<int>> dq;
  vector<vector<int>> mt(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0;j < n; j++) {
      mt[i][j] = arr[mtIndex];
      mtIndex++;
      if (mt[i][j] == 1) {
        dq.push_back({i,j});
      }
    }
  }

  if (dq.size() == 0 || dq.size() == n*n) {
    cout << -1 << endl;
    return 0;
  }

  // 循环感染, 每个循环感染一轮
  int step = 0;
  vector<vector<int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};

  while (!(dq.empty())) {
    step++;
    int size = dq.size();
    for (int i = 0; i < size; i++) {
      // front 取出一个点
      vector<int> pos = dq.front();
      dq.pop_front();

      // 4 个方向感染
      for (int j = 0; j < dirs.size(); j++) {
        int nx = pos[0] + dirs[j][0];
        int ny = pos[1] + dirs[j][1];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && mt[nx][ny] == 0) {
          // 感染, 并加入dq
          mt[nx][ny] = 1;
          dq.push_back({nx, ny});
        }
      }
    }
  }

  for(int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (mt[i][j] == 0) {
        cout << -1 << endl;
        return 0;
      }
    }
  }

  cout << step-1 << endl; // 最后一次循环， 没有在dq 中加入点

  return 0;
}