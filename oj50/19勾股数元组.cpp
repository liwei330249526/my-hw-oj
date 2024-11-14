/*
 * 题目描述
 * 如果3个正整数(a,b,c) 满足a^2 + b ^2 = c^2 的关系，则称(a,b,c) 为勾股数。
 * 为了探索勾股数的规律，我们定义如果勾股数（a,b,c）之间两两互质（即a与b，a与c，b与c之间均互质，没有公约数），
 * 则其为勾股数元组（例如（3，4，5）是勾股数元组(6,8，10)不是勾股数元组）。
 *
输入
1
20


输出
3 4 5
5 12 13
8 15 17


说明：

[1, 20]范围内勾股数有：(3 4 5)，(5 12 13)，(6 8 10)，(8 15 17)，(9 12 15)，(12 16 20)；

其中，满足(a,b,c)之间两两互质的勾股数元组有：(3 4 5)，(5 12 13)，(8 15 17)；

按输出描述中顺序要求输出结果。

 输出：
 1 a,b,c保证 a < b < c ， 输出格式： a b c；
 2 多组勾股数元组请哪找a升序，b升序，最后c升序的方式排序输出。
 3 给定范围中如果炸不到勾股数元组，输出 "NA".


 * */

#include "iostream"
#include "cmath"
#include "vector"
#include "algorithm"
using namespace std;

// 是否为互质，a，b 辗转相除，求最大公约数；如果为1，则是互质
// 8 2 ;  2 0
// 6 3    3 0
bool isCoprime(int a, int b) {
  while (b != 0) {
    int tem = b;
    b = a % b;
    a = tem;
  }
  // 最大公约数 a
  if (a == 1) {
    return true;
  }
  return false;
}


int main() {
//  cout << isCoprime(5,6) << endl;
  // 获取其实，终止数字
  int startNum;
  int endNum;
  cin >> startNum;
  cin >> endNum;

  // 获取所有数字组
  vector<vector<int>> arrs;
  for (int i = startNum; i <= endNum; i++) {
    for (int j = i+1; j <= endNum; j++) {
      int a = i;
      int b = j;
      int cc = a * a + b * b;
      int c = sqrt(cc);

      if (c * c == cc && c < endNum && isCoprime(a, b) && isCoprime(a,c) && isCoprime(b,c)) {
        arrs.push_back(vector<int>{a,b,c});
      }
    }
  }

  sort(arrs.begin(), arrs.end(), [](vector<int> &a, vector<int> &b) {
    if (a[0] != b[0]) {
      return a[0] < b[0];
    } else if (a[1] != b[1]) {
      return a[1] < b[1];
    } else {
      return a[2] < b[2];
    }
  });


  for (vector<int> &arr : arrs) {
    cout << arr[0] << " " << arr[1] << " " << arr[2] << endl;
  }

  return 0;
}
