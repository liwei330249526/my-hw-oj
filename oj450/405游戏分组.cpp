/*
 *
题目描述
部门准备举办一场王者荣耀演奏，有10名游戏爱好者参与，分别为两队，每对5人。每位参与者都有一个评分，代表着他的游戏水平。
为了表演赛尽可能精彩，我们需要把10名参赛者分为实力尽量相近的两队，一对的实力可以表示为这一对5名队员的评分综合
现在给你10名参与者的游戏水平评分，请你根据上述要求分队，最后输出两组的实力差绝对值

输入
10个整数，表示10名参与者游戏水平评分
输出
1个整数，表示分组后两组实力差绝对值的最小值

样例1
输入
1 2 3 4 5 6 7 8 9 10

输出
1

样例2
输入
5 5 5 5 5 5 5 5 5 5

输出
0


dfs 暴力即可
 *
 * */

#include "vector"
#include "iostream"
using namespace std;
int main() {
  vector<int> arr(10);
  for (int i = 0; i < arr.size(); i++) {
    cin >> arr[i];
  }

  int sum_num = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum_num += arr[i];
  }

  vector<bool> vis(10);

  int ret = sum_num;
  auto dfs = [&](auto &&dfs, int sum, int count) {
    // 结束标志
    if (count == 5) {
      ret = min(ret, abs(sum_num - sum - sum));
      return;
    }

    // 遍历每个数字，如果某个数字 i 没有访问过，则加入sum， 即继续下一个
    for (int i = 0; i < arr.size(); i++) {
      if (vis[i]) {
        continue;
      }
      dfs(dfs, sum + arr[i], count+1);
    }
    return;
  };

  dfs(dfs, 0, 0);

  cout << ret << endl;

  return 0;
}
