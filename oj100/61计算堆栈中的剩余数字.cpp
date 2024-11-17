/*
 *
题目描述
向一个空栈中依次存入正整数，假设入栈元素n(1<=n<=2^31-1)按顺序依次为nx..n4 n3 n2 n1 ，每当元素入栈时，
如果 n1=n2+..ny(y的范围[2,x], 1<=x<=1000), 则n1-ny全部元素出栈，重新入栈新元素m(m=2*n1)。

如：一次向栈中存入 6 1 2 3 , 当存入 6 1 2 时，栈第至栈顶一次为 [6, 1, 2]；当存入 3 时，3=2+1, 则3 2 1 全部出栈，重新入栈
元素6(6=2*3), 此时栈中只有元素6；
因为6=6，所以两个6全部出栈，然后入栈12， 最终栈中只有一个元素12.

样例1
输入
5 10 20 50 85 1

输出
1 170

说明：
5+10+20+50=85，输入85时，5、 10、 20、 50、 85 全部出栈，
入栈170，最终依次出栈的数字为1和170。


样例2
输入
6 7 8 13 9

输出
9 13 8 7 6


 样例3
 输入
1 2 5 7 9 1 2 2

输出
4 1 9 14 1

 *
 * */

#include "string"
#include "vector"
#include "iostream"
#include "sstream"
#include "unordered_map"
using namespace std;

void Push2Stack(vector<int> &st, int num) {  // 5 1 2 3
  int stId = st.size()-1;
  int stNum = num;

  // 大的循环， 循环尝试插入数字 stNum
  while (true) {
    while (stNum > 0 && stId >= 0) { // 从 len -1 向左查找，是否有符合的后缀和
      stNum -= st[stId];
      stId--;
    }

    if (stNum == 0) { // 如果有后缀和等于 stNum,  删除 [stId + 1 , ) 区间
      st.erase(st.begin() + stId+1, st.end());

      num = num * 2; // 继续下次尝试，  5 1 2 3， num 作为下次寻找后缀和的数字，如果下次寻找没有找到，则num 作为最终push 的数字
      stNum = num;
    } else {  // 如果没有后缀和等于 stNum， 则直接加入 num
      st.push_back(num);
      break;
    }
  }
}

int main() {
  string str;
  getline(cin, str);
  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  vector<int> st;
  for (int i = 0; i < arr.size(); i++)  {  //  6 1 2 3
    Push2Stack(st, arr[i]);
  }

  for (int i = st.size()-1; i >= 0; i--) {
    cout << st[i];
    if (i != 0) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}