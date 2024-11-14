/*
 * 输入一个字符串仅包含大小写字母和数字，求字符串中包含的最长的非严格递增连续数字序列的长度, （比如，12234 属于
 * 非严格递增数字序列）
 *
输入
abc2234019A334bc

输出
4

说明：
2234为最长的非严格递增连续数字序列，所以长度为4。

 * */

#include "string"
#include "iostream"
using namespace std;
int main () {
  string str;
  getline(cin, str);

  int curLen = 0;
  int ans = 0;
  for (int i = 0; i < str.size(); i++) {
    if (isdigit(str[i])) {
      if (i == 0) { // 如果是第[0] 个 char
        curLen = 1;
      } else if (!isdigit(str[i-1])){ // 如果pre不是数字
        curLen = 1;
      } else if (str[i-1] > str[i]){ // 如果是数字，但比 i 数字大
        curLen = 1;
      } else {
        curLen++;
      }

      ans = max(ans, curLen);

    } else {
      curLen = 0;
    }
  }

  cout << ans << endl;
  return 0;
}