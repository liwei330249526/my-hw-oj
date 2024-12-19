/*
 *
题目描述
程序员小明打了一辆出租车取上班，处于职业敏感，他转移到这两出租车的计费表有点问题，总是偏大，出租车司机解释说他不喜欢数字4，所以改装了计费表，
任何数字位置遇到数字4就直接跳过，其余功能都正常
比如
1 23 多一块变成25
2 39 多一块变成50
3 399 多一块变成 500
小明识破了司机的伎俩，准备利用自己的学识打败司机的阴谋，给出计费表的表面读书，返回实际产生的费用

输入
只有一行，数字N，表示里程表的读书
输出
一个数字，表示实际产生的费用，以回车结束

样例1
输入
5


输出
4

说明：
5表示计费表的表面读数，4表示实际产生的费用其实只有4块钱


样例2
输入
17

输出
15

说明：
17表示计费表的表面读数，15表示实际产生的费用其实只有15块钱


 100
 9*9

 200
 2*9*9

 500
 4*9*9



 0 0 5
 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int num;
  cin >> num;

  vector<int> arr;
  while (num > 0) {
    arr.push_back(num % 10) ;
    num = num / 10;
  }

  int res = 0;
  for (int i = arr.size()-1; i >= 0; i--) {
    int curNum = 0;
    if (arr[i] >= 5) {
      curNum = arr[i]-1;
    } else {
      curNum = arr[i];
    }
    res = res * 9 + curNum;
  }

  cout << res << endl;

  return 0;
}