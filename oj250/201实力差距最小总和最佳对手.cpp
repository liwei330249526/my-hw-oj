/*
 *
题目描述
游戏里面，队伍通过匹配实力相近的对手进行对战，但是如果匹配得队伍实力相差太大，对于双方游戏体验都不会太好。
给定n个队伍的实力值，对其进行两两实力匹配，两支队伍实力差距在允许的最大差距d内，则可以匹配。
要求在匹配队伍最多的情况下匹配出的各组实力差距的总和最小。

输入
第一行， n d  对业务个数n， 允许的最大实力差距d

第二行， n个队伍的实力值空格分隔

输出
匹配后，各组对战的实力差值综合，若干没有队伍可以匹配，则输出-1
 *
 * 样例1
 * 输入
6 30
81 87 47 59 81 18

输出
57

说明：
18与47配对，实力差距29
59与81配对，实力差距22
81与87配对，实力差距6
总实力差距29+22+6=57

 *
 * 样例2
 * 输入
6 20
81 87 47 59 81 18

输出
12

说明：
最多能匹配成功4支队伍，47与59配对，实力差距12,81与81配对，实力差距0，总实力差距12+0=12

 *
 * 样例3
 * 输入
6 20
81 87 47 59 81 18

输出
12

说明：
最多能匹配成功4支队伍，47与59配对，实力差距12,81与81配对，实力差距0，总实力差距12+0=12

 *
 * 动态规划
 *
 * */

#include "vector"
#include "string"
#include "iostream"
#include "algorithm"
#include "stdint.h"
using namespace std;
int main() {
  int n;
  int mxGap;
  cin >> n >>mxGap;
  vector<int> strengths(n);
  for (int i = 0; i < n; i++) {
    cin >> strengths[i];
  }
  sort(strengths.begin(),strengths.end());

  vector<vector<int>> dp(n+1, vector<int>(n/2+1, INT32_MAX)); // dp[i][j], 前i队伍，形成j队时， 总实力差距最小是多少
  dp[0][0] = 0; // 当没有团队参与时，匹配0 对， 实力差为0
//  for (int j = 0; j < dp[0].size(); j++) {
//    dp[0][j] = 0;
//  }

  for(int i = 1; i <= n; i++) { // 物品个数, i 个物品，的index 是i-1
    for (int j = 0; j <= i/2; j++) {    // 遍历背包
      if (i >= 2 && j >= 1 && strengths[i-1] - strengths[i-2] <= mxGap && dp[i-2][j-1] != INT32_MAX) {
        // 选，和不选i组队
        // 不选择 i 队， 继承 i-1 个队的结果
        // 选择 i队， i 和 i - 1 组1队，   dp[i-2][j-1] 组成j-1对，  共j 对
        int v1 = dp[i-1][j];
        int v2 = dp[i-2][j-1] + strengths[i-1] - strengths[i-2];
        dp[i][j] = min(v1, v2);
      } else {
        // 不选 i 组队
        dp[i][j] = dp[i-1][j];
      }
    }
  }
  // 最后一行, 从后向前遍历，如果有值，则返回
  // ...
  // ...
  // ...
  int outv = -1;
  for(int j = dp[0].size()-1; j >= 0; j--) {
    if (dp[n][j] != INT32_MAX) {
      if (j == 0){
        break;
      } else {
        outv = dp[n][j];
        break;
      }
    }
  }

  cout << outv << endl;

  return 0;
}