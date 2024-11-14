/*
 * 一天一支猴子想从山脚爬到山顶，途中有一N个台阶，
 * 猴子每个只能跳1步或3步，问猴子通过这个阶梯有多少种不同的跳跃方式。
 *
 * 台阶数N 大于0， 小于50
 *
 * 样例1
输入
50

输出
122106097

 *
 * 样例2
输入
3

输出
2

 *
 * */

#include "vector"
#include "iostream"
using namespace std;
int main() {
  int n;
  cin >> n;

  vector<int> dp(n+1);

  int res = 0;
  int p1 = 1;
  int p2 = 1;
  int p3 = 2;
  int p4 = 0;
  if (n == 1) {
    res = 1;
//    dp[n] = 1;
  } else if (n == 2) {
    res = 1;
//    dp[n] = 1;
  } else if (n == 3) {
    res = 2;
//    dp[n] = 2;
  } else {
//    dp[1] = 1;
//    dp[2] = 1;
//    dp[3] = 2;
    int p1 = 1;
    int p2 = 1;
    int p3 = 2;

    for (int i = 4; i <= n; i++) {
//      dp[i] = dp[i-1] + dp[i-3];
      p4 = p3 + p1;
      p1 = p2;
      p2 = p3;
      p3 = p4;
    }
    res = p3;
  }

  cout << res << endl;

  return 0;

}