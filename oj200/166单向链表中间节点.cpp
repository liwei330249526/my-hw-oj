/*
 *
题目描述
求单向链表的中间的节点值，如果奇数个节点取中间，偶数隔节点取偏右边那个值

输入
第一行：链表头节点地址后续输入的节点数n
后续输入每行表示一个节点，格式节点地址 节点值 下一个节点地址， -1表示空指针
输入保证链表不会出现环，并且可能存在一些节点不属于链表

输出
单向链表的节点值
 *
 * 样例1
 * 输入
00010 4
00000 3 -1
00010 5 12309
11451 6 00000
12309 7 11451

输出
6

 *
 * 节点2
 * 输入
10000 3
76892 7 12309
12309 5 -1
10000 1 76892

输出
7

 *
 *
 * */

#include "iostream"
#include "string"
#include "vector"
#include "unordered_map"
using namespace std;
int main() {
  string head;
  int n;
  unordered_map<string, pair<int, string>> dict;
  cin >> head >> n;

  for (int i = 0; i < n; i++) {
    string curAddr;
    int curVal;
    string nextAddr;
    cin >> curAddr >> curVal >> nextAddr;
    dict[curAddr] = make_pair(curVal, nextAddr);
  }

  int targetIndex = -1;
  if (n % 2 == 0) { // 4 , 0 1 2 3,   2
    targetIndex = n / 2;
  } else {         // 5 , 0 1 2 3 4   2
    targetIndex = n / 2;
  }

  string cur = head;
  int ret = 0;
  while (cur != "") {
    pair<int, string> &node =  dict[cur];
    if (targetIndex == 0) {
      ret = node.first;
      break;
    }
    cur = node.second;
    targetIndex--;
  }

  cout << ret << endl;

  return 0;
}