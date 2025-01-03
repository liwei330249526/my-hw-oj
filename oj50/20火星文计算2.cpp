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

// 7#6$5#12
int getResult(string str) {
  if (str.find('#') != string::npos) {
    int id = str.rfind('#');     // 这里的重点是，要从rfind， 为什么呢，因为最终的相同优先级要从左向右计算，
    string left = str.substr(0, id - 0); // 所以要保持左边的的地柜分支比右边深，才能保证左边的数字，先回溯出来，进行计算
    string right = str.substr(id+1);
    return 2*getResult(left) + 3*getResult(right) + 4;
  }

  if (str.find('$') != string::npos) {  // 这里保证 $ 优先级高
    int id = str.rfind('$');   // 这里的重点是，要从rfind
    string left = str.substr(0, id - 0);
    string right = str.substr(id+1);
    return 3*getResult(left) + getResult(right) + 2;
  }

  return stoi(str);
}

int main() {
  string str;
  getline(cin, str);

  int ret = getResult(str);

  cout << ret << endl;
  return 0;
}