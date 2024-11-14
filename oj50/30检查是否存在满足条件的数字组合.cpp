/*
 * 题目描述
 * 给定一个正整数数组，检查数组中是否存在满足规则的数字组合
 * 规则: A=B+2C
 *
输入
4
2 7 3 0

输出
7 3 2

说明：
7 = 3 + 2 * 2

 * */


#include "vector"
#include "iostream"
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int A = 0;
  int B = 0;
  int C = 0;
  bool find = false;
  for (int i = 0; i < arr.size(); i++) {
    A = arr[i];
    for (int j = 0; j < arr.size(); j++) {
      if (j == i) {
        continue;
      }
      B = arr[j];
      for (int k = 0; k < arr.size(); k++) {
        if (k == i || k == j) {
          continue;
        }

        C = arr[k];

        if (A == B + 2*C) {
          find = true;
          break;
        }
      }

      if (find) {
        break;
      }
    }

    if (find) {
      break;
    }
  }


  cout << A << " " << B << " " << C << endl;
  return 0;
}