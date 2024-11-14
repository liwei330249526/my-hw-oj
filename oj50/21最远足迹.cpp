/*
 *  探险队执行探险任务。随身携带记录器会不定期记录自身坐标，但记录间隙也会记录其他数据。
 *  探测结束后，需要获取最远足迹位置。
 *
 *  1 仪器记录坐标时，坐标的数据格式为(x,y),如 (1,2) (100, 200), 其中 0 < x <100, 0 < y < 1000。
 *    同时存在非法坐标，如(01,1) (1, 01)  (0, 100) 属于非法坐标。
 *  2 设定探险队总部的坐标为(0, 0), 某位置相对总部的距离为： xx + yy。
 *  3 若两个坐标的相对总部的距离相同，则第一次到大的坐标为最远的足迹。
 *  4 若记录仪中的坐标都不合法，输出总部坐标(0, 0).
 *
输入
ferg(3,10)a13fdsf3(3,4)f2r3rfasf(5,10)


输出
(5,10)


说明：
记录仪中的合法坐标有3个： (3,10)， (3,4)， (5,10)，其中(5,10)是相距总部最远的坐标， 输出(5,10)。


 * */

#include "iostream"
#include "string"
#include "sstream"
using namespace std;

bool getV(string str, int &v) {
  if (str.size() != 1 && str[0] == '0') {
    return false;
  }

  v = stoi(str);
  return true;
}

bool getXY(string str, int &x, int &y) {
  int id = str.find(',');
  if (id == string::npos) {
    return false;
  }

  string str1 = str.substr(0, id - 0);
  string str2 = str.substr(id+1);

  bool ret = getV(str1, x);
  if (!ret) {
    return false;
  }

  ret = getV(str2, y);
  if (!ret) {
    return false;
  }

  return true;
}

int main() {
//  string str = "01,100";
//  stringstream stm(str);
//  int a;
//  int b;
//  char deli;
//  stm >> a >> deli >> b;
//
//  cout << a << deli << b;

  string str;
  getline(cin, str);

  int ans = 0;
  int ansX = 0;
  int ansY = 0;
  int left = 0;
  int right = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '(') {
      left = i+1;
    } else if (str[i] == ')') {
      bool ret = getXY(str.substr(left, i - left), x, y);
      if (!ret) {
        continue;
      }

      if (x <= 0 || x >= 1000 ||
          y <= 0 || y >= 1000) {
        continue;
      }

      if (ans < x * x + y * y) {
        ans = x * x + y * y;
        ansX = x;
        ansY = y;
      }
    }
  }

  cout << "(" << ansX << "," << ansY << ")" << endl;
  return 0;
}