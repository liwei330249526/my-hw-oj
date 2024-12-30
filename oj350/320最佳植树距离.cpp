/*
 *
题目描述
按照环保公司要求，小明需要在沙化严重的地区进行植树防沙工作，初步目标是种植一直线的树带。因为有些区域目前不适合植树，
所以只能在一些可以种植的点来种植树木。
在树苗有限的情况下，要达到最佳效果，就要尽量散开种植，不同树苗之间的最小间距要尽量大。给你一个适合种树木的点坐标和一个树苗的数量，
请帮小明选择一个最佳的最小种植间距。
例如，适合种植树木的位置分别为 1 3 4 5 6 10 13， 树苗种植量是3，织鬃位置在 1 6 13， 树苗之间的间距是6，均匀分开，就达到了散开种植的目的，
最佳的最小种植间距是6.

输入
第1行表示适合种树的坐标数量
第2行是适合种树的坐标位置
第3行是树苗的数量

样例1
输入
7
1 5 3 6 10 7 13
3

输出
6

说明：
3棵树苗分别种植在1,7, 13位置时，树苗种植的最均匀，最小间距为6


样例2
输入
6
1 2 3 4 5 6
2

输出
5


二分法， 选择一个mid作为距离
是否可以以 mid 为距离种完所有树苗，遍历所有第[0]位置中一个， 遍历所有位置，如果到了某个位置[i], 距离超过了mid，则可以种树
种完所有苗，即认为，mid 符合；


 left = 0;
 right = max

 ok
 ret = left
 left++

 not ok
 right--
 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int k;
  cin >> k;

  sort(arr.begin(), arr.end());

  int left = 1;
  int right = arr.back() - arr.front();

  auto isFeat = [&](int interval) ->bool {
    int count = 1;
    int prePos = arr[0];

    for (int i = 1; i < arr.size(); i++) {
      if (arr[i] - prePos >= interval) {
        count++;
        prePos = arr[i];
      }

      if (count == k) {
        return true;
      }
    }
    return false;
  };

  int ret = 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (isFeat(mid)) { // 符合
      ret = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  cout << ret << endl;

  return 0;
}
