/*
 *
题目描述
给定一个整数数组nums，可以在数组的任意位置进行分隔，将数组分隔成两个费控子数组，
分别对子数组求和得到两个数 sum1，sum2， 请输出所有的分隔方案中，差值最大的值。

输入
第一行输入数组的中的元素个数n
第二行输入数字额序列，以空格分隔，数字取值为4字节整数
输出
输出差值最大值

样例1
输入
6
1 -2 3 4 -9 7

输出
10


样例2
输入
3
1 2 3

输出
4


 0 1 2 3 4 5

 pre[0] = 0 ,   即空的
 suf[0] -- [0] 开始到结尾

 pre[len -> 6], 前6个，即整个数组
 suf[len -> 6], [len] 到结尾的数字， 即空的 ， 直接为 0 即可

 前缀和 pre[len+1],  pre[i] 前i个数字和， 不包括[i]
 后缀和，suf[len+1],  suf[i] 从i 到结尾的数字和， 包括[i]
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
  vector<int> pre(n+1);
  vector<int> suf(n+1);
  for (int i = 1; i < n+1; i++) { // 前1个， 到前 n个， 左边
    pre[i] = pre[i-1] + arr[i-1];
  }

  for (int i = n-1; i >= 0; i--) { // 从n-1 开始， 到从0开始， 向右
    suf[i] = suf[i+1] + arr[i];
  }

  int ret = 0;
  for (int i = 1; i < n; i++) { // pre 的前1个到 前 n-1 个
    int diff = abs(pre[i] - suf[i]); // pre[i] 包括[i], suf[i] 不包括[i]
    ret = max(ret, diff);
  }

  cout << ret << endl;

  return 0;
}


