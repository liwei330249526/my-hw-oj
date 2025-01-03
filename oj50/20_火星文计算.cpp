/*
 * 已知火星人使用的运算符为 # $, 其与地球人的等价公式如下：
 * x#y = 2*x + 3*y + 4
 * x$y = 3*x + y + 2
 *
 * 1 其中 x y 是无符号整数
 * 2 地球人公式按c语言规则计算
 * 3 火星人公式中， $ 的优先级高于 # , 想通的运算符，按从左到右的顺序计算
 *
输入
7#6$5#12


输出
226


 * */

#include "string"
#include "iostream"
#include "vector"
using namespace std;

// x#y
int op1(int x, int y) {
  return 2*x + 3*y + 4;
}

// x$y    高优先级
int op2(int x, int y) {
  return 3*x + y + 2;
}
// 7#6$5#12
int getResult(string str) {
  vector<int> st;
  int left = 0;
  char curOp;

  for (int i = 0; i < str.size(); i++) {
    int num = 0;
    if (i == str.size()-1) {
      num = stoi(str.substr(left, i - left+1)) ; // 获取一个数字
      if (curOp == '#' || st.empty()) {
        st.push_back(num);
      } else if (curOp == '$') {
        int numt = op2(st.back(), num);
        st[st.size()-1] = numt;
      }
      break;
    } else {
      if (str[i] == '#' || str[i] == '$') {
        num = stoi(str.substr(left, i - left)) ; // 获取一个数字
        if (curOp == '#' || st.empty()) { // 优先级低，入栈
          st.push_back(num);
        } else if (curOp == '$') { // 优先级高，直接计算
          int numt = op2(st.back(), num);
          st[st.size()-1] = numt;
        }
        curOp = str[i]; // 更新curOp

        left = i+1;
      }
    }
  }

  int ans = st[0];
  for (int i = 1; i < st.size(); i++) {
    ans = op1(ans, st[i]);
  }
  return ans;
}

int main() {
  string str;
  getline(cin, str);

  int ret = getResult(str);

  cout << ret << endl;
  return 0;
}