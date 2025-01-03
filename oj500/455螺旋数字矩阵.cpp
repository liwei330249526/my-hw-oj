/*
 *
题目描述
疫情期间，小明隔离在家，在纸上写数字玩；他发明了一种写法：给出数字个数n和行数m， 从左上角的1开始，按照顺时针螺旋向内的方式，一次写出2，3...n
最终形成m行矩阵
小明对这个矩阵由此要求：
1 每行数字的个数一样多
2 列的数量尽可能少
3 填充数字时优先填充外部
4 数字不够时，便用单个 * 号占位

输入
两个整数
输出
符合要求的唯一矩阵

样例1
输入
9 4


输出
1 2 3
* * 4
9 * 5
8 7 6

说明:
9个数字写成4行，最少需要3列


样例2
输入
3 5


输出
1
2
3
*
*

说明:
3个数字写5行，只有一列，数字不够用*号填充

 *
 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int n;
  int rows;
  int cols;
  cin >> n >> rows;
  // 3  /  3 = 1, 4 / 3 =1
  // 3+2 / 3 = 1,  4 +2 / 3 = 2
  cols = (n + rows-1)/ rows; // 向上取整

  vector<vector<int>> gd(rows, vector<int>(cols, 0));

  int num = 1;
  int row = 0;
  int col = 0;

  vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
  int dirId = 0;
  while (num <= n) { // 本次循环要填充 num 数字
    // set num
    gd[row][col] = num;
    num++;

    // 尝试递进
    int nrow = row + dirs[dirId][0];
    int ncol = col + dirs[dirId][1];
    if (nrow < 0 || nrow >= gd.size() || ncol < 0 || ncol >= gd[0].size() || gd[nrow][ncol] != 0) {
      dirId = (dirId + 1) % 4; // 调整方向
      nrow = row + dirs[dirId][0];
      ncol = col + dirs[dirId][1];
    }

    row = nrow;
    col = ncol;
  }


  for (int i = 0; i < gd.size(); i++) {
    for (int j = 0; j < gd[0].size(); j++) {
      if (gd[i][j] == 0) {
        cout << "*";
      } else {
        cout << gd[i][j];
      }

      if (j != gd[0].size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  }

  return 0;
}

