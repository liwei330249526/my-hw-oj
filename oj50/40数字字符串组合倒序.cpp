/*
 * 题目描述
 * 对数字，字符，数字串，字符串，以及数字与字符串组合进行倒序排列。
 * 字符范围：
 * a-z, A到Z， 数字范围：0-9
 * 符号定义
 * 1 "-" 作为链接使用时作为字符串的一部分，例如 "20-years" 作为一个整体字符串。
 * 2 链接出现 2个 "-" 以及以上时视为字符串间隔付，如 "out--standing" 中的"--" 视为间隔符，是2个独立的字符串
 * "out" 和 "standing";
 * 3 除了1， 2 里面定义的字符意外其他的所有字符都是非法字符，作为字符串的间隔符处理，倒序后间隔符作为空格处理；
 * 4 要求倒排后的单词间隔符以一个空格表示； 如果有多个间隔符时，倒排转换后也只允许出现一个间隔符.
 *
输入
I am an 20-years out--standing @ * -stu- dent


输出
dent stu standing out 20-years an am I


 *
 * */

#include "string"
#include "iostream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<string> strArr;
  int left = 0;
  string strt;
  for (int i = 0; i < str.size(); i++) {
    if (isdigit(str[i]) || isalpha(str[i])) {
      strt += str[i];
    } else if (i > 0 && i < str.size()-1 && str[i] == '-' &&
              (isdigit(str[i-1]) || isalpha(str[i-1])) &&
              (isdigit(str[i+1]) || isalpha(str[i+1]))) {
      //
      strt += str[i];
    } else {
      if(!strt.empty()) {
        strArr.push_back(strt);
        strt = "";
      }
    }
  }

  strArr.push_back(strt);


  for (int i = strArr.size()-1; i >= 0; i--) {
    cout << strArr[i];
    if (i != 0) {
      cout << " ";
    }
  }

  cout << endl;


  return 0;
}