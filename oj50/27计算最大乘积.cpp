/*
 * 给定一个元素类型为小写字符串的数组，请计算两个没有相同字符字符的元素的长度乘积最大值
 * 如果没有符合条件的两个元素，返回0
 *
输入
iwdvpbn,hk,iuop,iikd,kadgpf

输出
14

说明：

数组中有5个元素。

iwdvpbn与hk无相同的字符，满足条件，iwdvpbn的长度为7，hk的长度为2，乘积为14（7*2）。

iwdvpbn与iuop、iikd、kadgpf均有相同的字符，不满足条件。

iuop与iikd、kadgpf均有相同的字符，不满足条件。

iikd与kadgpf有相同的字符，不满足条件。

因此，输出为14。


 * */

#include "string"
#include "vector"
#include "iostream"
#include "sstream"
#include "unordered_set"
#include "algorithm"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  string token;
  vector<string> strs;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    strs.push_back(token);
  }
  int ret = 0;
  for (int i = 0; i < strs.size(); i++) {
    for (int j = i+1; j < strs.size(); j++) {
      bool notCommon = true;
      for (char c : strs[j]) {
        if(strs[i].find(c) != string::npos) { // 两个字符串有重叠, 不符合
          notCommon = false;
          break;
        }
      }

      if (notCommon) {
        ret = max(ret, int(strs[i].size() * strs[j].size()));
      }
    }
  }
  cout << ret << endl;
  return 0;
}