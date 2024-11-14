/*
 * 题目描述给定一个url 前缀和 url 后缀，通过 "," 分隔，需要将其链接为一个完整的url，如果前缀结尾和后缀开头都没有 "/",
 * 需要自动补上 "/" ; 如果前缀结尾和后缀开头都有 "/", 需要自动去重
 *
输入
/acm,/bb

输出
/acm/bb

 * */

#include "string"
#include "iostream"
using namespace std;

string joinStr(string pre, string suf) {
  if (pre.back() != '/' && suf.front() != '/') {
    return pre + "/" + suf;
  } else if (pre.back() == '/' && suf.front() == '/') {
    pre.pop_back();
    return pre + suf;
  } else {
    return pre + suf;
  }
}

int main() {
  string str;
  getline(cin, str);

  int partId = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ',') {
      partId = i;
      break;
    }
  }

  string pre = str.substr(0, partId);
  string suf = str.substr(partId+1);

//  cout << pre << " : " << suf << endl;

  string res = joinStr(pre, suf);
  cout << res << endl;
  return 0;
}