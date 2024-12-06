/*
 *
题目描述
某个充电站，可提供n个充电设备，每个充电设备均有对应的输出功率。找出任意的设备综合，使功率综合P最优，即功率最大且不大于最大输出功率 p_max。
输入，3行
第1行：充电设备个数n
第2行：每个充电设备的输出功率
第3行：充电站最大输出功率p_max

输出
功率集合P的最优元素

 *
 * 样例1
 * 输入
4
50 20 20 60
90


输出
90

说明：
当充电设备输出功率50、20、 20组合时， 其输出功率总和为90，最接近充电站最大充电输出功率,因此最优元素为90




 *
 * 样例2
 * 输入
2
50 40
30



输出
0

说明：
所有充电设备的输出功率组合,均大于充电站最大充电输出功率30,此时最优元素值为0

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

  int pMax;
  cin >> pMax;

  // 0 1 背包
  // 不选arr[i], dp[j]
  // 选 arr[i],  dp[j - arr[i]] + arr[i]
  vector<int> dp(pMax+1);
  for (int i = 0; i < arr.size(); i++) { // 遍历物品
    for (int j = dp.size()-1; j >= 0; j--) { // 遍历背包
      if (j >= arr[i]) { // 如果背包大于物品
        dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
      }
    }
  }

  cout << dp[dp.size()-1] << endl;

  return 0;
}