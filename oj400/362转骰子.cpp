/*
 *
题目描述
骰子是一个立方体，每个面一个数字，初始为左1， 右2， 前3， 后4， 上5， 下6； 用123456 表示这个状态，放在平面上，可以向左翻转L，可以向右翻转R，
可以向前翻转F，可以向后翻转B，可以逆时针旋转A，可以顺时针旋转C；现在从123456这个初始状态开始，根据输入的动作序列，计算最终的状态。

初始状态  123456
左翻转L   563421   452310


初始状态  123456
右翻转R   653412   542301

初始状态  123456
前翻转F   125643   014532

初始状态  123456
后翻转B   126534   015423

初始状态  123456
逆翻转A   431256   320145

初始状态  123456
顺翻转C   342156   231045

输入
一行，为例如 LRFBAC 的字母序列
输出
输出最终状态

样例1
输入
LR



输出
123456


说明
骰子先向左翻转，响右翻转回来,故还是原来的状态123456


样例2
输入
FCR



输出
342156

 *
 * */

#include "iostream"
#include "string"
using namespace std;

int main() {
  string str;
  cin >> str;
  string res = "123456";

  auto reverse = [](string curSeq, char dir) ->string {
    string result;
    if (dir == 'L') {
      // 左翻转L   563421   452310
      result = result + curSeq[4] + curSeq[5] + curSeq[2] + curSeq[3] + curSeq[1] + curSeq[0];
    } else if (dir == 'R') {
      // 右翻转R   653412   542301
      result = result + curSeq[5] + curSeq[4] + curSeq[2] + curSeq[3] + curSeq[0] + curSeq[1];
    } else if (dir == 'F') {
      // 前翻转F   125643   014532
      result = result + curSeq[0] + curSeq[1] + curSeq[4] + curSeq[5] + curSeq[3] + curSeq[2];
    } else if (dir == 'B') {
      // 后翻转B   126534   015423
      result = result + curSeq[0] + curSeq[1] + curSeq[5] + curSeq[4] + curSeq[2] + curSeq[3];

    } else if (dir == 'A') {
      // 逆翻转A   431256   320145
      result = result + curSeq[3] + curSeq[2] + curSeq[0] + curSeq[1] + curSeq[4] + curSeq[5];

    } else if (dir == 'C') {
      // 顺翻转C   342156   231045
      result = result + curSeq[2] + curSeq[3] + curSeq[1] + curSeq[0] + curSeq[4] + curSeq[5];

    } else {
      cout << "err" << endl;
    }
    return result;
  };

  for (int i = 0; i < str.size(); i++) {
    res = reverse(res, str[i]);
  }
  cout << res << endl;
  return 0;
}