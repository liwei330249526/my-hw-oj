/*
 *
题目描述
100 个人围成一圈，每个人有一个编码，编号从1开始到100；
他们从1开始一次报数，报到位M的人自动退出圈圈，然后下一个人接着从1开始报数，直到剩余的人数少于M。
请问最后剩余的人在原先的编号为多少？

输入输出
输入
输入一个整数参数M

输出
如果输入参数M小于等于1或大于等于100，输出 "ERROR"
否则按照原先的编号从到大的顺序，以英文逗号分隔输出编号字符串

样例1
 输入
3

输出
58,91

说明：
输入M为3，最后剩下两个人


 样例2
 输入
4

输出
34,45,97

说明：
输入M为4，最后剩下三个人


 * */

#include "string"
#include "iostream"
#include "vector"
using namespace std;
int main() {
  int m;
  cin >> m;

  vector<int> arr(100, 1);
  int remain = 100;

  int count = 0;
  while (remain >= m) {
    for (int i = 0; i < arr.size(); i++) {
      if (arr[i] == 1) {
        count++; // 计数
        if(count == m) { // 如果计数到了 m， 则该人离场
          arr[i] = 0;
          remain--;

          count = 0;  // 重新计数
        }
      }
    }
  }

  int i = 0;
  for (i = 0; i < arr.size(); i++) {
    if(arr[i] == 1) {
      cout << i+1;
      break;
    }
  }
  i = i+1;
  for (; i < arr.size(); i++) {
    if (arr[i] == 1) {
      cout << "," << i+1;
    }
  }

  cout << endl;

  return 0;
}