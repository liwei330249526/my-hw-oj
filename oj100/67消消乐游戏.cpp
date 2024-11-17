/*
 *
题目描述
游戏规则：输入一个只包含英文字母的字符串，字符串中的两个字母如果相邻且相同，就可以消除。
在字符串上反复执行消除动作，指导无法继续消除为止，此时游戏结束。
输出最终得到的字符串长度。
 *
 * 样例1
输入
gg



输出
0

说明：
gg可以直接消除，得到空串，长度为0。

 *
 * 样例2
输入
mMbccbc



输出
3

说明：
在mMbccbc中，可以先消除cc ;
此时字符串变成mMbbc，可以再消除bb ;
此时字符串变成mMc，此时没有相邻且相同的字符,无法继续消除。
最终得到的字符串为mMc，长度为3。
 *
 * */

#include "iostream"
#include "string"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<char> st;

  for (int i = 0; i < str.size(); i++) {
    if (st.empty()) {
      st.push_back(str[i]);
      continue;
    } else {
      if (st.back() == str[i]) {
        st.pop_back();
      } else {
        st.push_back(str[i]);
      }
    }
  }

  cout << st.size() << endl;

  return 0;
}