/*
 *
题目描述
输入N个互不相同的二维整数坐标，求这N个坐标可以构成的正方形数量。[内积为零的两个向量垂直]

输入输出
输入
第一行输入为N，N代表坐标数量，N为正整数。N<=100
之后的K行输入为坐标x,y 以 空格分割，x,y 为整数， -10 <=x, y<=10

输出
输出可以构成正方形数量

样例1
输入
3
1 3
2 4
3 1

输出
0(3个点不足以构成正方形)


样例2
 输入
4
0 0
1 2
3 1
2 -1

输出
1


样例3
 输入
4
0 -1
0 1
-1 0
1 0

输出
1


 样例4
 输入
4
0 0
1 1
1 0
0 1

输出
1


 样例5
 输入
5
-1 0
0 1
1 0
0 -1
1 2



输出
1


 样例 6
输入
10
-1 0
0 1
1 0
0 -1
1 2
2 1
0 2
2 0
-2 0
0 -2


输出
3


 样例7
 输入
7
0 0
1 1
2 2
3 3
0 1
1 2
2 3

输出
0



解
获取所有点；获取每个4点组合；判断这个4个点是否能组成正方向，共6个边，对6个边排序，前4个边长度相等，后2个边长度相等且垂直。


 * */

#include "iostream"
#include "vector"
#include "math.h"
#include "algorithm"

using namespace std;

int lineLen(vector<int> &p1, vector<int> &p2) {
  int ret = 0;
  int ret1 = (p1[0]-p2[0]) * (p1[0]-p2[0]) + (p1[1]-p2[1]) * (p1[1]-p2[1]);
//  int ret2 = pow(p1[0]-p2[0], 2) + pow(p1[1]-p2[1], 2);
//  cout << ret1 << " " << ret2 << endl;
  return ret1;
}

bool is_square(vector<int> &p1, vector<int> &p2, vector<int> &p3, vector<int> &p4) {
  vector<vector<int>> ps;
  ps.push_back(p1);
  ps.push_back(p2);
  ps.push_back(p3);
  ps.push_back(p4);

  vector<int> lenArr;
  for (int i = 0; i < ps.size(); i++) {
    for (int j = i+1; j < ps.size(); j++) {
      lenArr.push_back(lineLen(ps[i], ps[j]));
    }
  }
  sort(lenArr.begin(), lenArr.end());

  if (lenArr[0] == lenArr[1] &&  lenArr[0] == lenArr[2] && lenArr[0] && lenArr[3] &&
      lenArr[4] == lenArr[5]) {
    return true;
  }
  return false;
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> points(n, vector<int>(2));

  // 获取所有点
  for (int i = 0; i < n; i++) {
    cin >> points[i][0] >> points[i][1];
  }

  // 获取4个点
  int ret = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i+1; j < points.size(); j++) {
      for (int k = j+1; k < points.size(); k++) {
        for (int m = k+1; m < points.size(); m++) {
          // 判断该4个点是否为正方形
          if(is_square(points[i],points[j], points[k], points[m])) {
            ret++;
          }
        }
      }
    }
  }

  cout << ret << endl;
  return 0;
}