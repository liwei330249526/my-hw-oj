/*
 *
题目描述
有一个荒岛，只有左右两个港口，只有一座桥连接两个港口，现在有一群人需要从两个港口逃生，有的人往右逃生，有的人往左逃生，如果两个人相遇，
则pk， 体力值大的能够打赢体力值小的，体力值相同则同归于尽，赢得人继续往前逃生，并减少响应的体力。

输入
一行非0的整数，用空格隔开，整数代表向右逃生，负数代表向左逃生
输出
最终能够逃生的人数

样例1
输入
5 10 8 -8 -5




输出
2


 *
 * */

#include "sstream"
#include "iostream"
#include "vector"
#include "stack"
using namespace std;
int main() {
  string str;
  getline(cin, str);
  string token;
  vector<int> arr;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }
  vector<int> st;
  int ret = 0;
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > 0) { // arr[i]大于0， 入栈
      st.push_back(arr[i]);
    } else { // arr[i]小于0
      int curNum = arr[i];  // 对curNum 左遍历， 吃掉arr 的正数
      // 如果st 为空, 则如果curNum
      // 判断 top 是正数，则继续
      // 如果是负数，则push 并退出

      while (true) {
        if (st.empty()) { // 如果栈为空了， 且curNum 还小于 0即还有体力， 则逃生成功
          if (curNum < 0) {
            ret++;
          }
          break;
        }
        if (curNum == 0) { // 如果curNum 没有体力了
          break;
        }
         // 1 2 3  -2;   1 2 3 -4 ;   1 2 3 -3
        if (curNum + st.back() > 0) { // 如果curNum 没有打败栈顶，则退出，并重置栈顶
          st[st.size()-1] = curNum + st.back();
          break;
        } else if (curNum + st.back() < 0) { // 如果curNum 打败了栈顶，则继续向左打
          curNum = curNum + st.back();
          st.pop_back();
        } else {  // 1 2 3 -3  // 如果同归于尽，则栈顶也要退出， curNum 体力设置为0
          st.pop_back();
          curNum = 0;
        }
      }
    }
  }

  ret += st.size(); // 向左逃的数量ret， 加上 st 剩余的（向右逃的数量）
  cout << ret << endl;

  return 0;
}