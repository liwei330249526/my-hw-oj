/*
 *
题目描述
A B 两个人玩一个数字比大小的游戏，在游戏前，。两个人会拿到相同长度的两个数字列，两个数字序列不相同的且其中的数字是随机的。
A B 各自从数字列中挑选出一个数字进行大小比较，赢的人得1分，输的人扣一分，相等则各自的分数不变。用过的数字需要丢弃，求A 可能赢B
的最大分数。
输入
输入的第一个数字表示数字序列的长度 n， 后面紧跟着两个长度为n的数字序列
输出
A 可能赢b 的最大分数

样例1
输入
3
4 8 10
3 6 4
输出
3


样例2
输入
4
1 2 3 4
5 6 7 8


输出
-4

 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int test1() {
  int n;
  cin >> n;
  vector<int> arr1(n);
  vector<int> arr2(n);

  for (int i = 0; i < n; i++) {
    cin >> arr1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> arr2[i];
  }

  sort(arr1.begin(), arr1.end());
  sort(arr2.begin(), arr2.end());

  int i = 0;
  int j = 0;
  int ret = 0;
  for (j = 0; j < arr2.size(); j++) { // 遍历B
    int num2 = arr2[j]; // 2 的值，
    for (; i < arr1.size(); i++) { // 遍历A
      int num1 = arr1[i];
      if (num2 < num1) { // 找到一个数字比 num2 大
        break;
      }
    }
    // i == arr1.size ;  i < arr1.size && num2 < num1
    // j,  i

    if (i < arr1.size()) {
      if (arr2[j] < arr1[i]) {
        ret++;
      }
      i++;
    } else {
      ret--;
    }
  }

  cout << ret << endl;
}


int test() {
  int n;
  cin >> n;
  vector<int> arr1(n);
  vector<int> arr2(n);

  for (int i = 0; i < n; i++) {
    cin >> arr1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> arr2[i];
  }

  sort(arr1.begin(), arr1.end());
  sort(arr2.begin(), arr2.end());

  int i = 0;
  int j = 0;
  int ret = 0;
  for (j = 0; j < arr2.size(); j++) { // 遍历B
    while (i < arr1.size() && arr1[i] < arr2[j]) { // 找到第一个 arr1 的某个数大于或等于 arr2
      i++;
    }

    if (i < n && arr1[i] == arr2[j]) { // 然后arr1 递进；  下次 arr2 也要递进； 如果相等，arr2 也要递进
      i++;
    } else if (i < n && arr1[i] > arr2[j]) {
      ret++;
      i++;
    } else {
      ret--;
    }

  }

  cout << ret << endl;
  return 0;
}

int main() {

  test1();
  return 0;
}