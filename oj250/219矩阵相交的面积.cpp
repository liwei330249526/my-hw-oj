/*
 *
题目描述
给出3组点坐标（x, y, w, h）
(x, y, w, h) 表示平面直角坐标系中的一个矩形
x，y 为矩形左上角坐标点， w，h表示向右w，向下h
(x, y w, h) 表示x轴(x, x+w) 和 y 轴(y, y-h) 围成的矩形区域；
(0, 0, 2, 2) 表示x轴(0,2) 和 y 轴(0, -2) 围成的矩形区域。
(3, 5, 4, 6) 表示x轴(3,7) 和 y 轴(5, -1) 围成的矩形区域。
求3组坐标构成的矩形区域重合部分面积
 *
 * 样例1
 * 输入
1 6 4 4
3 5 3 4
0 3 7 3

1,6     5,2
3,5     6,1
0,3     7,0

3,3     5,2

输出
2

 *
求3个矩形的相交面积，求相交左上，和相交右下点

1 左上坐标， x 取3者最大， y 取3者最小
2 右下坐标， x 取3者最小， y取3者最大
 *
 *
 * */

#include "vector"
#include "iostream"
using namespace std;
int main() {
  // 3 个矩形
  vector<vector<int>> rects(3, vector<int>(4));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> rects[i][j];
    }
  }

  // 左上角， x max, y min
  // 右下角， x min, y max
  int x1 = max(rects[0][0], max(rects[1][0], rects[2][0]));
  int y1 = min(rects[0][1], min(rects[1][1], rects[2][1]));
  int x2 = min(rects[0][0] + rects[0][2], min(rects[1][0] + rects[1][2], rects[2][0] + rects[2][2]));
  int y2 = max(rects[0][1] - rects[0][3], max(rects[1][1] - rects[1][3], rects[2][1] - rects[2][3]));

//  cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << endl;

  if (x1 >= x2 || y1 <= y2) {
    cout << 0 << endl;
  } else {
    cout << (x2 - x1) * (y1 - y2) << endl;
  }

  return 0;
}