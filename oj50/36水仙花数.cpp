/*
 * 题目描述
 * 所谓水仙花数，是指一个n位的正整数，其个位数字的n次方和等于该数本身。
 * 例如153是水仙花数，153是一个3位数，并且153=1^3 + 5^3 + 3^3
 *
 *
n 在3 - 7 之间， 包含3和7
m 表示返回第m个水仙花数, 从0开始编号
若m 大于水仙花个数，则返回最后一个水仙花数和m 的乘积
输入不合法，则返回-1

 *
 *
输入
9
1

输出
-1

说明：9超出范围

 *
 * */

#include "string"
#include "iostream"
#include "algorithm"
#include "cmath"
#include "vector"
//#include ""
using namespace std;

bool isSx(int n, int num) {
//  if (num == 153) {
//    cout << num << endl;
//  }
  int numt = num;

  int sum = 0;
  while (numt > 0) {
    int nmy = numt % 10;
    sum += pow(nmy, n);
    numt = numt / 10;
  }

  return sum == num;
}

int main() {
  int n;
  int m;

  cin >> n;
  cin >> m;

  if (n < 3 || n > 7) {
    cout << -1 << endl;
    return 0;
  }

//  cout << n << " " << m << endl;

  int left = pow(10, n-1);
  int right = pow(10, n) - 1;

  vector<int> resNums;
  for (int i = left; i <= right; i++) {
    if (isSx(n, i)) {
      resNums.push_back(i);
    }
  }

  if (m >= resNums.size()) {
    cout << m * resNums.back() << endl;
  } else if (m >= 0) {
    cout << resNums[m] << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}