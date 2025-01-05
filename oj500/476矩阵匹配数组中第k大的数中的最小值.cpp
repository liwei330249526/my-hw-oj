/*
 *
题目描述
从一个N*M (N<M)的矩阵中选出N个数，任意两个数字不能再同一行或同一列， 求选出来的N个数中第K大的数字的最小值是多少。

样例1
输入
3 4 2
1 5 6 6
8 3 4 3
6 8 6 3


输出
3

说明：
样例中选出的组合数组有24种，最小数组为1,3,3, 则2大的最小值为3

样例2
输入
3 3 1
1 2 3
4 5 6
7 8 9



输出
7

 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
#include "stdint.h"
using namespace std;

int ret = INT32_MAX;
void dfs(vector<vector<int>> &mt, int row, vector<bool> &colVis, vector<int> path, int k) {
//  if (path.size() == mt.size()) { // path
//    sort(path.begin(), path.end(), [](int a, int b){
//      return a > b;
//    });
//    ret = min(ret, path[k-1]);  // 第k个数字
//    return;
//  }
  if(row == mt.size()) { // 到了最后一行
    sort(path.begin(), path.end(), [](int a, int b){ // 排序
        return a > b;
    });
    ret = min(ret, path[k-1]);  // 第k个数字， 并记录最小值
    return;
  }

//  dfs(mt, row+1, colVis, path, k); // 第 row 行不选

  for (int i = 0; i < mt[0].size(); i++) { // 遍历每列，  第row 行选第 i 列
    if (!colVis[i]) { // 如果没有访问
      colVis[i] = true; // 记录
      path.push_back(mt[row][i]); // 将值加入到path
      dfs(mt, row + 1, colVis, path, k);
      path.pop_back(); // 回溯
      colVis[i] = false; // 回溯
    }
  }
  return;
}

int main() {
  int N; // N 行
  int M; // M 列
  int K; // 第K个数
  cin >> N >> M >> K;

  // 获得矩阵
  vector<vector<int>> mt(N, vector<int>(M));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> mt[i][j];
    }
  }

  vector<int> path;
  vector<bool> colVis(M, false);

  dfs(mt, 0, colVis, path, K);  // 递归回溯

  cout << ret << endl;

  return 0;
}