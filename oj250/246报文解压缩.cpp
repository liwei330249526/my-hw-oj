/*
 *
题目描述
为了提升数据传输的效率，会对传输的保温进行压缩处理，输入一个压缩后的报文，请返回它解压后的原始保温，压缩规则： n[str], 表示方括号内部的str
正好重复n次
注意： n 为正整数 0<n<=100, str 只包含小写英文字母，不考虑异常情况

输入
输入压缩后的报文
输出
解压后的原始保温

样例1
输入
3[k]2[mn]

输出
kkkmnmn

说明
k重复3次，mn重复2次,最终得到kkmnmn


样例2
输入
3[m2[c]]


输出
mccmccmcc


说明
m2[c]解压缩后为mcc，重复三次为mccmccmcc
 *
 * */

#include "iostream"
#include "string"
#include "vector"
using namespace std;

typedef struct MStr_t {
    string str;
    int times;
}MStr;
// 3[m2[c]]
int main() {
  string str;
  cin >> str;

  vector<MStr> strs;
  int id = 0;
  int times = 0;
  string rett;
  for (id = 0; id < str.size(); id++) {
    if (str[id] == '[') { // 左括号
      strs.push_back(MStr{rett, times});
      rett = "";
      times = 0;
    } else if (str[id] == ']') { // 右括号
      MStr mstr = strs.back();
      strs.pop_back();
      string internalStr;
      for (int j = 0; j < mstr.times; j++) {
        internalStr += rett;
      }
      rett = mstr.str + internalStr;
    } else if (isdigit(str[id])) { // 数字
      int left = id;
      while (id+1 < str.size() && isdigit(str[id+1])) {
        id = id+1;
      }
      // id 是该数字的最后数字字母
      times = stoi(str.substr(left, id-left+1));
    } else {  // 字母
      rett += str[id];
    }
  }

  cout << rett << endl;

  return 0;
}