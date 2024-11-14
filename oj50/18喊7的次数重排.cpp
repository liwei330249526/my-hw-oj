/**
 * 喊7 是一个传统的聚会游戏，N个人围成一圈，按顺时针从1到N编号。
 * 编号为1的人从1开始喊数，下一个人喊的数字为上一个人的数字加，单是当将要喊出的数字是7的倍数或者数字本身含有7的话，
 * 不能把这个数字喊出来，而是要喊 "过"。
 * 假定玩这个游戏的N个人都没有失误地在正确的实际喊了"过"，当喊道数字K时，可以统计每个人喊 "过" 的出事。
 *
 * 现在给定一个长度为N的数组，存储了打乱顺序的每个人喊 "过" 的次数，请把它还原成正确的顺序，几数组的第i个元素存储
 * 编号i的人喊 "过" 的次数。
 *
输入
0 1 0


输出
1 0 0


说明：

一共只有一次喊”过”，那只会发生在需要喊7时，按顺序，编号为1的人会遇到7，故输出1 0 0。

注意，结束时的K不一定是7，也可以是8、9等，喊过的次数都是1 0 0。



输入
0 0 0 2 1

输出
0 2 0 1 0


说明：

一共有三次喊”过”，发生在7 14 17，按顺序，编号为2的人会遇到7 17，编号为4的人会遇到14，故输出0 2 0 1 0。


 *
 * */

#include "vector"
#include "string"
#include "iostream"
#include "sstream"
using namespace std;


bool isG(int num) {
  if (num % 7 == 0) {
    return true;
  }

  string numStr = to_string(num);
  auto it = numStr.find('7');
  if (it != string::npos) {
    return true;
  }

  return false;
}

int main() {
  // 先获取一行字符串
  string str;
  getline(cin, str);

  istringstream istream(str);  // isstringstream
  vector<int> disorderArry;

  // istringstream, 通过 >> , 获取所有数字
  int num;
  while (istream >> num) {
    disorderArry.push_back(num);
  }

  // 获取所有过的计数
  int totolG = 0;
  for (int i = 0; i < disorderArry.size(); i++) {
    totolG += disorderArry[i];
  }

  // 模拟数字从 1 开始，直到找到了 totolG 个 过
  num = 1;  // 数字从1开始
  int id = 0;  // 下表从0开始
  vector<int> orderArray(disorderArry.size());
  int arrLen = orderArray.size();
  for (;totolG > 0;) {
    if (isG(num)) { // 如果找到了一个 过， 则设置到指定为止 id, 且总需要的过减1
      orderArray[id % arrLen]++;
      totolG--;
    }
    id++;
    num++;
  }


  for (int i = 0; i < orderArray.size(); i++) {
    cout << orderArray[i];
    if (i != orderArray.size()-1) {
      cout << " ";
    }
  }
  cout << endl;
  return 0;
}