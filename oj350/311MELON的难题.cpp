/*
 *
MELON 有一堆精美的雨花石（数量为n，重量各异），准备送给S和W。MELON希望送给两人的雨花石重量一致，请你设计一个程序，确认
是否能将雨花石平均分配.

输入
第一行输入雨花石个数
第二行输入各个雨花石的重量

输出
如果可以均分，从当前雨花石中最少拿出几块，可以使两对重量相等；如果不能均分，输出-1

样例1
输入
4
1 1 2 2



输出
2

说明：
总和为 1+1+2+2=6 那么 可以拿出 重量为1和2的组合 因此至少拿出2块，输出2


样例2
输入
5
1 1 2 2 1



输出
-1

说明：
总和为7为奇数不可能均分，输出-1


样例3
输入
3
3 1 2


输出
1


样例4
输入
10
1 1 1 1 1 9 8 3 7 10


输出
3


说明：
输入第一行代表共10颗雨花石，

第二行代表4颗雨花石重量分别为1、1、1、1、1、9、8、3、7、10 。

均分时可以1,1,1,1,1,9,7和10,8,3，也可以1,1,1,1,9,8和10,7,3,1，或者其他均分方式，但第一种只需要拿出重量为10,8,3的3块雨花石，第二种需要拿出4块，所以输出3(块数最少)



动态规划
dp[j] ,  组成目标target 需要的最少石头

遍历物品  i,
   遍历背包   0 - target
   选择物品 i-1, dp[j] = dp[j-nums[i-1]] + 1  , 较小值
   不选物品 i-1, dp[j] = dp[j]
 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int n;
  cin >> n;
  // 获取数组
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int sum = 0;
  int num_max = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
    num_max = max(num_max, arr[i]);
  }

  // 为奇数则，不能找到一半
  if (sum % 2 == 1) {
    cout << -1 << endl;
    return 0;
  }
  // 如果最大大于一半， 则不能找到一半
  if (num_max > sum / 2) {
    cout << -1 << endl;
    return 0;
  }

  // 动态规划, dp[j], 组成数值 j 最少需要的石子数量
  int target = sum / 2;
  vector<int> dp(target + 1, (arr.size()));
  dp[0] = 0; // 组成0， 肯定为0， 其他位置初始化为 arr.size()
  for (int i = 0; i < n; i++) { // 遍历物品
    for (int j = 0; j < dp.size(); j++) { // 遍历背包
      // 选择物品
      if (j >= arr[i]) { // 如果背包足够大
        // 选择， 或不选择
        dp[j] = min(dp[j], dp[j - arr[i]] + 1);
      } else {
        // 不选
        dp[j] = dp[j];
      }
    }
  }

  cout << dp.back() << endl;
  return 0;
}

