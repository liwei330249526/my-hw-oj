/*
 *
题目描述
学校组织活动，将学生排成一个矩形方阵
请在矩形方阵中国找到最大位的位置相连的男生数量
这个相连位置在一个直线上，方向可以是水瓶的，垂直的，成对角先的，或呈反对角线的

输入
第一行为矩形的行数和列数，接下来的n行为矩形元素，元素间用 , 分隔
输出
输出一个整数，表示矩形中最长的位置相连的男生个数

样例1
输入
3,4
F,M,M,F
F,M,M,F
F,F,F,M

输出
3


样例2
输入
1,2
M,M
输出
2


样例3
输入
2,1
M
F

输出
1


动态规划
 *
 * */

#include "iostream"
#include "string"
#include "vector"
#include "sstream"
#include "algorithm"
using namespace std;
int main() {
  int row;
  int col;

  string strNums;
  getline(cin, strNums);
  int numSpliteId = strNums.find(',');
  if (numSpliteId == strNums.npos) {
    return 0;
  }
  row = stoi(strNums.substr(0, numSpliteId));
  col = stoi(strNums.substr(numSpliteId+1));

  vector<string> strArr(row);
  for (int i = 0; i < row; i++) {
    getline(cin, strArr[i]);
  }

  vector<vector<char>> mt(row, vector<char>(col));
  vector<vector<int>> dp1(row, vector<int>(col)); // 水平dp
  vector<vector<int>> dp2(row, vector<int>(col)); // 竖直dp
  vector<vector<int>> dp3(row, vector<int>(col)); // 对角dp
  vector<vector<int>> dp4(row, vector<int>(col)); // 反对角dp

  for (int i = 0; i < row; i++) {
      stringstream stm(strArr[i]);
      string token;
      int j = 0;
      while (getline(stm, token, ',')) {
        mt[i][j] = token[0];
        j++;
      }
  }

  int res = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      // 水平
      if (mt[i][j] == 'M') {
        if (j == 0) {
          dp1[i][j] = 1;
        } else {
          dp1[i][j] = dp1[i][j-1] + 1;
        }

        // 竖直
        if (i == 0) {
          dp2[i][j] = 1;
        } else {
          dp2[i][j] = dp2[i-1][j] + 1;
        }
        // 对角
        if (i == 0 || j == 0) {
          dp3[i][j] = 1;
        } else {
          dp3[i][j] = dp3[i-1][j-1] + 1;
        }

        // 反对角
        if (i == 0 || j == col-1) {
          dp4[i][j] = 1;
        } else {
          dp4[i][j] = dp4[i-1][j+1] + 1;
        }

        res = max({res, dp1[i][j], dp2[i][j], dp3[i][j], dp4[i][j]});
      } else {
        dp1[i][j] = 0;
        dp2[i][j] = 0;
        dp3[i][j] = 0;
        dp4[i][j] = 0;
      }
    }
  }

  cout << res << endl;

//  for (int i = 0; i < row; i++) {  ok
//    for (int j = 0; j < col; j++) {
//      cout << mt[i][j];
//    }
//    cout << endl;
//  }

  return 0;
}

