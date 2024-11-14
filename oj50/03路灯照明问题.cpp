/*
 * 题目描述
 * 一条笔直的公路上安装了N个路灯，从为止0开始安装，路灯之间间距固定位100米
 * 每个路灯都有自己的照明半径，请计算第一个路灯和最后一个路灯之间，无法照明的区间长度和。
 *
 * 输入
 * 4
 * 50 70 20 70
 *
 * 输出
 * 20
 *
 *
输入
8
10 10 10 250 10 10 10 10

输出
160

 *
 * 说明：
 * 路灯1 覆盖 0-50
 * 路灯2 覆盖 30-170
 * 路灯3 覆盖 180-220
 * 路灯4 覆盖 230-370
 *
 * 未覆盖去区域是 170-180  220-230   共20
 * */

/*
 * 思路
 * 1 建立区间
 * 2 区间合并
 * 3 合并过程中，计算区间间隔和
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  // 数字, 路灯数量
  int n;
  cin >> n;

  // 数组，路灯半径
  vector<int> rad(n);
  for (int i = 0; i < n; i++) {
    cin >> rad[i];
  }

  // 构建区间
  // 0  100  200  300 ...
  int right = (rad.size() - 1) * 100;
  vector<vector<int>> spans(n, vector<int>(2));
  for (int i = 0; i < rad.size(); i++) {
    spans[i][0] = max(0, i * 100 - rad[i]);
    spans[i][1] = min(right, i * 100 + rad[i]);
  }

  sort(spans.begin(), spans.end(), [](vector<int> &a, vector<int>b) {
    return a[0] < b[0];
  });

//  0 50
//  30 170
//  180 220
//  230 300
//  for (int i = 0; i < spans.size(); i++) {
//    cout << spans[i][0] << " " << spans[i][1] << endl;
//  }

  // 遍历区间，求间隔综合, 假装合并区间，但只是求值
  int tol = 0;
  int preStart = spans[0][0];
  int preEnd = spans[0][1];

  for (int i = 1; i < spans.size(); i++) {
    int curStart = spans[i][0];
    int curEnd = spans[i][1];

    if (curStart <= preEnd) {
      // 合并区间
      preEnd = max(preEnd, curEnd);
    } else {
      // 首先，计算间隔综合
      tol += curStart - preEnd;

      // 间隔区间
      preStart = curStart;
      preEnd = curEnd;
    }
  }
  cout << tol << endl;
  return 0;
}