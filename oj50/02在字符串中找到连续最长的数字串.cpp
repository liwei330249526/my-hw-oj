
/**
 *  题目描述
 *  在一个字符串中找出连续最长的数字串，并返回这个数字串
 *  如果存在多个，则返回最后一个
 *  如果没有符合条件的数字串，则返回空字符串 ""
 *
 * 注意： 数字串游数字 0-9, 小数点， 正负号组成；
 * 数字串中的小数点，正负号只能出现一次，小数点两边必须是数字，正负号出现在开头且其后必须有数字
 *
 * 输入
 * 1234567890abcd9.+12345.678.9ed
 *
 * 输出
 * +12345.678
 * */

#include <regex>
#include "string"
#include "iostream"
using namespace std;
int main() {
  string str;
  getline(cin, str);  // getline(cin, str)
//  cout << str << endl;

  string pattern = "[+=]?\\d+(\\.\\d+)?"; // pattern ,  [+-]?(\\d)+(\\.\\d)?
  string res;
  for (int i = 0; int(i < str.size()); i++) {
    string strt = str.substr(i); // 从某个字符串开始的子串
    regex reg(pattern);
    smatch match;
    if (regex_search(strt, match, reg)) {
      string matchStr = match.str();
//      cout << matchStr << endl;
      if ( res.size() <= matchStr.size()) { // 保留最后一个最长数字串
        res = matchStr;
      }
    }
  }

  cout << res << endl;
  return 0;
}