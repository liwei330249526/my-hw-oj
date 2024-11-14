/*
 * 题目描述
 * 为了充分发挥gpu 算力，要尽可能多的将任务交给GPU 执行，现在有一个任务数组，数组元素表示在这1秒内新增任务个数，
 * 且每秒都有新增任务。
 * 假设GPU最多一次执行n个任务，一次执行耗时1秒，在保证GPU不空闲的情况下，最少多长时间执行完成。
 *
 * 输入
 * 第一个参数为gpu 一次最多执行的任务个数
 * 第二个参数为任务数组长度
 * 第三个参数为任务数组
 * 输出
 * 执行完所有任务最少需要多少秒
 *
输入
3
5
1 2 3 4 5

输出
6

说明:
一次最多执行3个任务，最少耗时6s

 *
 *
 *
 *
 * */

#include "string"
#include "iostream"
#include "vector"
using namespace std;
int main() {
  int m;
  int n;

  cin >> m;  // 每秒执行几个任务
  cin >> n; // n 个数

  vector<int> arr(n);
  for (int i = 0; i < arr.size(); i++) {
    cin >> arr[i];
  }

  int sum = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum = max(sum + arr[i] - m, 0);
  }

  int res = arr.size();

  res += sum / m;
  if (sum % m != 0) {
    res += 1;
  }
  cout << res << endl;
  return 0;
}