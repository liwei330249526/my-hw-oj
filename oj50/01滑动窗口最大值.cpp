/*
 * 滑动窗口最大值
 *
 * 题目描述
 * 有一个N个整数的数组，和一个长度为M的窗口，窗口从数组内的第一个数开始滑动直到窗口不能滑动为止，
 * 每次窗口滑动产生一个窗口和（窗口内所有数的和），求窗口产生的所有窗口和最大值
 *
 * 样例
 * 输入
 * 6
 * 12 10 20 30 15 23
 * 3
 *
 * 输出
 * 68
 *
 * 说明，窗口长度为3，窗口滑动山城的窗口和分别是 12+10+20=42, 10+20+30=60， 20+30+15=55， 30+15+23=68
 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int n;
  cin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int with;
  cin >> with;

//  cout << n << endl;
//  for (int i = 0; i < n; i++) {
//    cout << arr[i];
//  }
//  cout << "" << endl;
//  cout << with << endl;

  int sum = 0;
  int ans = 0;
  for (int i = 0; i < with; i++) {
    sum += arr[i];
  }
  ans = sum;

  int right = with;
  for (;right < n;right++) {
    sum = sum + arr[right] - arr[right-with];
    ans = max(ans, sum);
  }
  cout << ans << endl;
  return 0;
}