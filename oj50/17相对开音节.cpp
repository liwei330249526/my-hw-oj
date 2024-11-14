/*
 * 相对开音节构成结构为辅音+元音(aeiou) + 辅音(r除外)+e，常见的单词有bike，cake等
 * 给定一个字符串，以空格为分隔付，翻转每个单词中的字母，若单词中包含数字等其他非字母时不进行翻转。
 * 翻转后，计算其中含有相对开音节的结构的子串个数(连续的子串部分字符可以重复)
 *
输入
ekam a ekac


输出
2


说明：

反转后为 make a cake 其中make、cake为相对开音节子串，返回2。

 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
using namespace std;

bool isVow(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
    return true;
  }
  return false;
}

int main() {

  char input[1000];
  cin.getline(input, sizeof(input));
  string str = string(input);

//  string str;
//  getline(cin, str);

  // 获取所有单词
  vector<string> strs;
  string token;
  stringstream stm(str);
  while(getline(stm, token, ' ')) {
    strs.push_back(token);
  }

  // 遍历每个单词
  int count ;
  for (int i = 0; i < strs.size(); i++) {

    // 如果单词不是长度为4，则忽略
    if (strs[i].size() != 4)  {
      continue;
    }

    // 校验单词都是小写字母
    int j = 0;
    for (j = 0; j < strs[i].size(); j++) {
      if (!islower(strs[i][j])) {
        break;
      }
    }

    if (j != strs[i].size()) {
      break;
    }

    // 所有都是小写字符
    int left = 0;
    int right = strs[i].size()-1;

    // 翻转
    string strt = strs[i];
    for(;left < right;) {
      swap(strt[left], strt[right]);
      left++;
      right--;
    }
    strs[i] = strt;

//    bool f1 = !isVow(strs[i][0]);
//    bool f2 = isVow(strs[i][1]);
//    bool f3 = !isVow(strs[i][2]) && strs[i][2] != 'r';
//    bool f4 = strs[i][3] == 'e';
//    bool f5 = (!isVow(strs[i][0]) && isVow(strs[i][1]) && !isVow(strs[i][2]) && strs[i][2] != 'r' && strs[i][3] == 'e'));
    // 判断符合开音节
    if (!isVow(strs[i][0]) &&
        isVow(strs[i][1]) &&
        (!isVow(strs[i][2]) && strs[i][2] != 'r')
        && strs[i][3] == 'e') {
      count++;
    }
  }
  cout << count << endl;
  return 0;
}