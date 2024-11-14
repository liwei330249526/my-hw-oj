/*
 * 题目描述
 * 小明今年升学到了1年级，发现小朋友身高参差不齐，然后想基于小朋友和自己的身高差，对他们进行排序，请帮他实现排序
 *
 * 输入
 * 第一行为正整数 h 和 n； h 是小明的身高， n 是其他小朋友个数
 * 第二行为n 个整数，代表其他小朋友的身高
 *
 * 输出
 * 排序结果，各个整数以空格分隔
 * 和小明身高差绝对值最小的排在前面
 * 和小明身高差绝对值最大的排在后面
 * 如果身高差一样，则各自小的排在前面
 *
 * 样例1
输入
100 10
95 96 97 98 99 101 102 103 104 105

输出
99 101 98 102 97 103 96 104 95 105

 *
 * */

#include "vector"
#include "iostream"
#include "algorithm"
using namespace std;

int main() {
  int h;
  int n;
  cin >> h >> n;
  vector<int> harr(n);
  for (int i = 0; i < n; i++) {
    cin >> harr[i];
  }
  sort(harr.begin(), harr.end(), [&](int a, int b) {
    if (abs(a-h) != abs(b-h)) {
      return abs(a-h) < abs(b-h);
    }

    return a < b;
  });

  for (int i = 0; i < harr.size(); i++) {
    cout << harr[i];
    if (i != harr.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}