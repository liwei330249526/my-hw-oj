/*
 *
题目描述
小明和朋友一起玩跳格子游戏，每个各自上有特定的分数 score=[1-1,-6,-17,7]，从起点 score[0] 开始，每次最大的步长为k，
请你返回小明调到终点 score[n-1] 时，能得到的最大得分。
输入
第1行输入总的格子数量n
第2行输入每个各自的分数 score[i]
第3行输入最大跳的步长k
输出
输出最大得分

样例1
输入
6
1 -1 -6 7 -17 7
2


输出
14


动态规划 ， dp[i] , 到i位置的最大得分.
 *
 * */

#include "iostream"
#include "vector"
#include "deque"
using namespace std;


void test1() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  int k;
  cin >> k;

  vector<int> dp(n+1);  // 动态规划 , 到第 i 个数的最大得分， 位置i 是[i]
  dp[0] = 0;
//  deque<int> que;  // 双端队列
//  que.push_back(0);

  // x -1 1 2 3 4  ,   i=3,  k = 2 ;  3-2
  for (int i = 1; i < dp.size(); i++) {  // 第i个数字
    int startId = max(0, i - k);  // 保证index 大于或等于0
    for (int j = startId; j < i; j++) {
      dp[i] = max(dp[i], dp[j] + arr[i-1]);
    }
  }

  cout << dp.back() << endl;
  return ;
}

// 滑动窗口
void test2() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  int k;
  cin >> k;

  vector<int> dp(n);  // 动态规划 , 到第 i 个数的最大得分， 位置i 是[i]
  dp[0] = arr[0];
  deque<int> que;  // 双端队列
  que.push_back(0);

  // x -1 1 2 3 4  ,   i=3,  k = 2 ;  3-2
  for(int i = 1; i < arr.size(); i++) {
    // 队列是否合规
    // 到了数字 i
    if (i - que.front() > k) { // 如果窗口大了， 则pop
      que.pop_front();
    }

    int mxId = que.front();
    dp[i] = dp[mxId] + arr[i];  // 窗口内的最大值加上 i, 值是 dp

    while (!que.empty() && que.back() <= dp[i]) { // 维护滑动窗口, 滑动窗口内的 dp[i] 的最大
      que.pop_back();
    }
    que.push_back(i);
  }

  cout << dp.back() << endl;
  return ;
}

int main() {
  test2();
  return 0;
}