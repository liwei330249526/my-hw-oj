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
  for (int i = 0; i < arr.size(); i++) { // 遍历数组， 选一个A
    A = arr[i];
    for (int j = 0; j < arr.size(); j++) { // 遍历数组，选一个B
      if (j == i) {
        continue;
      }
      B = arr[j];
      for (int k = 0; k < arr.size(); k++) { // 遍历数组， 选一个C
        if (k == i || k == j) {
          continue;
        }

        C = arr[k];

        if (A == B + 2*C) { // 如果满足，则返回
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