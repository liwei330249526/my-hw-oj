/*
 * 题目描述
 * 给定一个整数数组，请从该数组中选择3个元素组成最小数字并输出
 * 如果数组长度小于3，请选择数组中所有元素组成最小数字。
 *
 * 样例1
输入
21,30,62,5,31

输出
21305

说明：

数组长度超过3，需要选3个元素组成最小数字,
21305由21,30,5三个元素组成的数字,所有组合中最小的数字。
 *
 * 样例2
输入
5,21

输出
215

说明：

数组长度小于3，选择所有元素来组成最小值, 215为最小值。

 *
 *
 * */

#include "vector"
#include "iostream"
#include "string"
#include "sstream"
#include "algorithm"
#include "stdint.h"

using namespace std;
int main() {
  string str;
  getline(cin, str);
  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }
  // 数字排序
  sort(arr.begin(), arr.end(), [](int a, int b) {
    return a < b;
  });

  // 取前3个数字
  vector<int> nums;
  for (int i = 0; i < 3 && i < arr.size(); i++) {
    nums.push_back(arr[i]);
  }

  // 全排列
  string res;
  do {
    string st;
    for (int i = 0; i < nums.size(); i++) {
      st += to_string(nums[i]);
    }

    // 比较字符串，一样
    if (res.empty()) {
      res = st;
    } else {
      if (st < res) {
        res = st;
      }
    }

  } while (next_permutation(nums.begin(), nums.end()));
  cout << res << endl;

  return 0;
}

void test1() {
  vector<int> nums;
  nums.push_back(5);
  nums.push_back(21);
  nums.push_back(30);

  do {
    for (int i = 0; i < nums.size(); i++) {
      cout << nums[i] << " ";
    }
    cout << endl;
  } while (next_permutation(nums.begin(), nums.end()));
  return;

  /// 5 2 1  更大排列
}
