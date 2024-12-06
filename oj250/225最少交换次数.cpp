/*
 *
题目描述
给出数字K，请输出所有结果小于K的整数组合到一起的最少交换次数，组合一起是指满足条件的数字相邻，不要求相邻后再数组中的位置
输入
第一行输入数组
第二行输入k数值

输出
第一行输出最少交换次数
 *
 *样例1
 * 输入
1 3 1 4 0
2

输出
1

说明：
小于2的表达式是1 10,共三种可能将所有符合要求数字组合起,最少交换1次

 *
 * 样例2
 * 输入
0 0 0 1 0
2


输出
0

 *
 *
 * 思路
 * 滑动窗口
 * 窗口大小， 整个数组有几个小于k的
 * 窗口初始值，有几个大于 k的
 * 向右滑动， 左侧滑出，右侧滑入。
 *
 * */

#include "string"
#include "iostream"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);
  int k;
  cin >> k;
  // 获取数组
  stringstream stm(str);
  string token;
  vector<int> arr;
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  // width
  int width = 0;
  for (int i = 0; i < arr.size(); i++) { // 数组中有多少个k的数字,则设置滑动窗口大小为多少
    if (arr[i] < k) {                     // 即需要将滑动窗口内的数字都变为小于k
      width++;
    }
  }

  int widChangeCount = 0;
  for (int i = 0; i < width; i++) {  // 初始化滑动窗口， 有几个大于或等于k的，需要移动多少次
    if (arr[i] >= k) {
      widChangeCount++;
    }
  }

  int left = 0;         // 滑动窗口边界
  int right = width;

  int ans = widChangeCount;
  while (right < arr.size()) { // 滑动窗口移动
    if (arr[left] >= k) {      // 左边界 left 移出
      widChangeCount--;
    }
    if (arr[right] >= k) { // 有边界 right 移入
      widChangeCount++;
    }
    left++;
    right++;

    ans = min(ans, widChangeCount); // 记录最小值
  }

  cout << ans << endl;

  return 0;
}