/*
 *
3020 年，空间通信集团的员工人数突破20亿人，即将遇到现有工号不够用的窘境。
现在，请你负责调研新工号的系统。集成历史传统，新的工号系统由小写英文字母(a-z) 和数字(0-9)两部分构成。
 新工号由一段英文字母开头，之后跟随一段数字，比如 "aaahw0001", "a12345", "abcd1", "a00"。
 注意新工号不能权威字母或者数字，允许数字部分由签到0或全为0.
 但是过长的工号会增加同事本的记忆成本，现在给出新工号至少需要分配的人数X和新工号中字母的长度Y，求新工号中数字的最短长度Z。

 * 样例1
输入
260 1

输出
1

说明：
无
 *
 * 样例2
输入
26  1




输出
1

说明：
数字长度不能为0

 *
 * 样例3
输入
2600 1




输出
2

说明：
无

 *
 *
 * */

#include "iostream"
#include "math.h"
using namespace std;
int main() {
  int X; // 员工个数
  int Y; // 字母个数

  cin >> X >> Y;

  // 字母组合数
  int chCombineCounts = pow(26, Y);

  // 需要数字的组合数
  double numCombineCounts = ceil(X / chCombineCounts);

  // 需要几个数字
  int count = ceil(log10(numCombineCounts));

  count = max(count, 1);

  cout << count << endl;

  return 0;

}