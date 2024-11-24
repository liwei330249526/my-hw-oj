/*
 *
题目描述
小明每周上班都会拿到自己的工作清单，工作清单内包含n项工作，每项工作都有对应的耗时时间（单位h）和报酬，攻坚工作的总报酬为
所有已完成工作的报酬纸盒，那么请你帮小明安排一下工作，保证小明再指定的工作时间内的工作收入最大化。

输入
第一行两个整数T，n
T代表工作时长
n代表工作数量

接下来n行，每行包含两个整数 t w
t 代表工作消耗的时长，w代表该项工作的报酬。

输出
输出小明指定工作时内工作可获得的最大报酬。
 *
 * 输入
40 3
20 10
20 20
20 5




输出
30

 *
 * */

#include "iostream"
#include "string"
#include "vector"
using namespace std;

// 01 背包
// 先物品，再背包； 背包遍历从到小
// dp[j], 工作时长为j，获得的最大报酬；
//    1 选择第i个工作， dp[j] = dp[j - i工作时长] + i工作报酬
//    2 不选择第i个工作， dp[j] = dp[j]
int main() {
  int T; // 时长
  int n; // 报酬
  cin >> T >> n;
  vector<vector<int>> works(n, vector<int>(2));
  for (int i = 0; i < n; i++) {
    cin >> works[i][0] >> works[i][1];
  }

  vector<int> dp(T+1); // 背包， 即容量, 即最大时长
  for (int i = 0; i < n; i++) { // 遍历物品
    for (int j = dp.size()-1; j >= 0; j--) { // 遍历背包
      if (j >= works[i][0]) { // 背包大于物品
        dp[j] = max(dp[j], dp[j - works[i][0]] + works[i][1]);
      }
    }
  }

  cout <<  dp[dp.size()-1] << endl;

  return 0;
}