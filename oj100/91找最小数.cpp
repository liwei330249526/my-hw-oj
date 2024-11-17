/*
 *
题目描述
给一个正整数num1，计算出新正整数num2，num2为num1中移除N位数字后的结果，需要使得num2的值最小。

输入
1 第一行为一个字符串，由0-9字符组成，记录正整数num1，num1长度小于32.
2 第二行，为需要移除的数字个数，小于num1长度。
输出
一个数字字符串，记录最小值num2

 *
 * 样例1
输入
2645371
4


输出
231

 *
 *
 * 栈
 * */

#include "iostream"
#include "string"
#include "vector"
using namespace std;
int main() {
  string str;
  cin >> str;
  int n;
  cin >> n;

  // 如果 str[i] 较小，则pop 一次，即删除一个字符， 即删除较大的
  vector<char> st;
  for (int i = 0; i < str.size(); i++) {
    while (!st.empty() && st.back() > str[i] && n > 0) {
      st.pop_back();
      n--;
    }

    st.push_back(str[i]);
  }

  // 如果还有未删除的，则继续删除较大的
  while (n > 0) {
    st.pop_back();
    n--;
  }

  // 打印剩余字符
  int i = 0;

  for (i = 0; i < st.size(); i++) {
    if (st[i] != '0') {
      break;
    }
  }

  string res;
  for (; i < st.size(); i++) {
    res += st[i];
  }

  if (res.size() == 0) {
    cout << "0";
  } else {
    cout << res;
  }

  cout << endl;

  return 0;
}