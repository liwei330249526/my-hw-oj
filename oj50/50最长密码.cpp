/*
 * 题目描述
 * 小王在闯关，每个关卡需要一个密码才能通过，密码条件如下
 * 密码本中，每个密码都由26个小写字母组成，每页密码不同，需要从密码本中寻找这样一个最长的密码
 * 从它的尾部一次去掉一位，得到的新密码也在密码本中。
 * 请输出符合要求的密码，如果有多个符合要求的Miami，则返回字典序最大的密码。
 * 若没有符合要求的密码，返回空字符串。
 *
 * 样例1
输入
h he hel hell hello

输出
hello

 *
 * 样例2
输入
b ereddred bw bww bwwl bwwlm bwwln

输出
bwwln

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "unordered_map"
using namespace std;

bool isPasswd(string word, unordered_map<string, int> &dict) {
  for (int i = 1; i <= word.size(); i++) {
    if (dict.find(word.substr(0, i)) == dict.end()) { // 如果前缀在字典中不存在， 则false
      return false;
    }
  }

  return true;
}

int main() {
  string str;
  getline(cin, str);

  vector<string> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(token);
  }

  unordered_map<string, int> dict;
  for (string s : arr) {
    dict[s] = 1;
  }

  string res;
  for (string s : arr) {
    if (isPasswd(s, dict)) {
      if (res.size() < s.size()) {
        res = s;
      } else if (res.size() == s.size()) {
        if (res < s) {
          res = s;
        }
      }
    }
  }

  cout << res << endl;

  return 0;
}