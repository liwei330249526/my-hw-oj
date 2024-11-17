/*
 *
题目描述
小明正在规划一个大型数据中心机房，为了使得机柜上的机器都能正常满负荷工作，需要确保在每个机柜上至少要有一个电箱。
为了简化题目，假设这个机房是一整排，M表示机柜，I表示间隔，请你返回这整排机柜，至少需要多少个电箱。如果误解请返回-1.

 *
 * 样例1
输入
MIIM


输出
2


 *
 * 样例2
输入
MIM

输出
1


 *
 * 样例3
输入
M


输出
-1


 *
 * 样例4
输入
MMM


输出
-1


 *
 * 样例5
输入
I


输出
0


 *
 * */

#include "string"
#include "iostream"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  int res = 0;
  for (int i = 0; i < str.size(); ) {
    if (str[i] == 'M') {
      if (i+1 < str.size() && str[i+1] == 'I') {
        res++;
        i += 3;
      } else if (i-1 >= 0 && str[i-1] == 'I') {
        res++;
        i++;
      } else {
        // 无解
        res = -1;
        break;
      }
    } else {
      i++;
    }
  }

  cout << res << endl;
  return 0;
}

