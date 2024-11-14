/*
 * 题目描述
 * 小明从糖果盒中随意抓一把糖果，每次小明会取出一半的糖果分给同学们。
 * 当糖果不能平均分配时，小明可以选择从糖果盒中（假设盒中糖果足够）取出一个糖果或放回一个糖果。
 * 小明最少需要多少次（取出、放回和平均分配均记一次），能将收中的糖果分至只剩一颗。
 *
 * 样例
输入
15

输出
5

说明：
15+1=16
16/2=8
8/2=4
4/2=2
2/2=1
所以为5次

 *
 * */

// 递归

#include "string"
#include "iostream"

using namespace std;

int dfs(int num, int step) {
  if (num == 1) {
    return step;
  }

  if (num % 2 == 1) {
    int ret1 = dfs((num+1) / 2, step+2);
    int ret2 = dfs((num-1)/2, step+2);
    return min(ret1, ret2);
  } else {
    return dfs(num / 2, step+1);
  }
}

int main() {
  int n;
  cin >> n;

  int ret = dfs(n, 0);

  cout << ret << endl;

  return 0;
}