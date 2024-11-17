/*
 *
题目描述
现需要实现一种算法，能将一组压缩字符串还原成原始字符串，还原规则如下：
1 字符后面加数字N，表示重复字符N次，例如：压缩内容为A3，表示原始字符串AAA。
2 花括号中的字符串加数字N，表示花括号中的字符重复N次。例如压缩内容为{A,B}3，表示原始字符串为ABABAB。
3 字符家N和花括号后面加N，支持任意的嵌套，包括互相嵌套，例如：压缩内容可以{A3B1{C}3}3.

 *
 * 样例
输入
{A3B1{C}3}3


输出：
AAABCCCAAABCCCAAABCCC

说明：
(A3B1{C}3}3代表A字符重复3次, B字符重复1次,花括号中的C字符重复3次，最外层花括号中的AAABCCC重复3次。


 *
解题思路
1 stack
2 遇到字母 入栈
3 遇到数字 获取值，出栈计算字符串, 入栈
4 遇到{   入栈，
5 遇到}   组合括号
 *
 * */


#include "string"
#include "iostream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<string> st;
  for (int i = 0; i < str.size();) {
    if (isalpha(str[i])) {
      st.push_back(string(1, str[i]) );
      i++;
    } else if (str[i] == '{') {
      st.push_back(string(1, str[i]) );
      i++;
    } else if (isdigit(str[i])) {
      int j = i;
      while (j < str.size() && isdigit(str[j])) { // 是数字，则递增
        j++;
      }
      // j 指向非数字
      int num = stoi(str.substr(i, j - i));
      string preStr = st.back();
      string inStr;
      st.pop_back();

      // 计算加倍后的字符串
      while (num > 0) {
        inStr += preStr;
        num--;
      }

      // 加倍后的字符串加入st
      st.push_back(inStr);

      // 更新迭代器
      i = j;
    } else if (str[i] == '}') {
      // 组合括号
      string inStr;
      while (!st.empty()) {
        if (st.back() == "{") {
          st.pop_back();
          st.push_back(inStr);
          break;
        }

        inStr = st.back() + inStr;
        st.pop_back();
      }
      i++;
    }
  }

  // 对 st 操作
  for (int i = 0; i < st.size(); i++) {
    cout << st[i];
  }
  return 0;
}