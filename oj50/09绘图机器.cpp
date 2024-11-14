/*
 * 题目描述
 * 绘图机器的绘图笔初始位置在原点(0,0)，机器启动后按照以下规则来绘制直线。
 * 1 尝试沿着横线左边正向绘制直线直到给定的终点E
 * 2 期间可以通过指令在纵坐标轴方向进行偏移，offsetY为正数表示正向偏移，为负数表示负向偏移
 * 给定的横坐标终点值E以及若干条绘图指令
 * 请计算绘制的直线和横坐标轴以及x=E直线组成的图形面积
 *
样例1：
输入
4 10
1 1
2 1
3 1
4 -2


输出
12


样例2：
输入
2 4
0 1
2 -2


输出
4


样例9：
 输入
8 18
1 1
4 -4
6 6
8 -8
9 9
12 -12
14 14
17 -17

输出
77


样例10：
 输入
7 14
1 1
3 3
5 5
7 -7
9 9
11 -11
13 13

输出
67



 * */

#include "iostream"
using namespace std;
int main() {
  int n;
  int endP;
  cin >> n >> endP;

  int preX = 0;
  int preY = 0;
  int ans = 0;
  int x;
  int offsetY;
  for (int i = 0; i < n; i++) {
    cin >> x >> offsetY;
    ans += (x - preX) * abs(preY);

    preX = x;
    preY += offsetY;
  }

  ans += (endP - preX) * abs(preY);
  cout << ans << endl;
  return 0;
}