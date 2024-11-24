/*
 *
题目描述
判断一组不等式是否满足约束并输出最大差
要求
1 不等式系数为double，是一个二维数组
2 不等式的变量为int，是一维数组
3 不等式目标值为double，是一维数组
4 不等式约束是字符串数组，只能是 >  >=  <   <=  =

例如不等式 a11*x1 + a12*x2 + a13*x3 + a14*x4 + a15*x5 <= b1;
         a21*x1 + a22*x2 + a23*x3 + a24*x4 + a25*x5 <= b2;
         a31*x1 + a32*x2 + a33*x3 + a34*x4 + a35*x5 <= b3;

最大差 max{a11*x1 + a12*x2 + a13*x3 + a14*x4 + a15*x5 - b1;
         a21*x1 + a22*x2 + a23*x3 + a24*x4 + a25*x5 - b2;
         a31*x1 + a32*x2 + a33*x3 + a34*x4 + a35*x5 - b3;
         }
 *
 * 样例1
输入
2.3,3,5.6,7,6;11,3,8.6,25,1;0.3,9,5.3,66,7.8;1,3,2,7,5;340,670,80.6;<=,<=,<=




输出
false 458


说明
// 2.3   ×   1   +   3   ×   3   +   5.6   ×   2   +   7   ×   7   +   6   ×   5   -   340 = -238.5
// 11   ×   1   +   3   ×   3   +   8.6   ×   2   +   25   ×   7   +   5   ×   1   -   670 = -452.8
// 0.3   ×   1   +   9   ×   3   +   5.3   ×   2   +   66   ×   7   +   7.8   ×   5   -   80.6 = 458.3

前两个不满足条件，所以输出为false。
然后计算三个差值中的最大值，取整数部分。

 *
 *
 * 样例2
输入
2.36,3,6,7.1,6;1,30,8.6,2.5,21;0.3,69,5.3,6.6,7.8;1,13,2,17,5;340,67,300.6;<=,>=,<=




输出
false 758

 *
 * */

#include "sstream"
#include "vector"
#include "iostream"
#include "string"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<string> strArr;
  stringstream stm(str);
  string token;
  while (getline(stm, token, ';')) {
    strArr.push_back(token);
  }
  stm.str("");
  stm.clear();

  // 系数二维数组
  vector<vector<double>> numArr(strArr.size()-3);
  for (int i = 0; i < strArr.size()-3; i++) {
    string s = strArr[i];
    stm.str("");
    stm.clear();
    stm << s;
    while (getline(stm, token, ',')) {
      numArr[i].push_back(stod(token));
    }
  }
  stm.str("");
  stm.clear();

  // 变量一维数组
  vector<int> varArr;
  string s = strArr[strArr.size()-3];
  stm << s;
  while (getline(stm, token, ',')) {
    varArr.push_back(stoi(token));
  }
  stm.str("");
  stm.clear();

  // 目标值一维数组
  vector<double> targetArr;
  s = strArr[strArr.size()-2];
  stm << s;
  while (getline(stm, token, ',')) {
    targetArr.push_back(stod(token));
  }
  stm.str("");
  stm.clear();

  // 约束一维数组
  vector<string> opArr;
  s = strArr[strArr.size()-1];
  stm << s;
  while (getline(stm, token, ',')) {
    opArr.push_back(token);
  }

  double ansMax;
  bool hasFalse = false;
  for(int i = 0; i < numArr.size(); i++) {
    double rest = 0;
    for (int j = 0; j < numArr[i].size(); j++) {
      rest += numArr[i][j] * varArr[j];
    }
    // 最大差
    if(i == 0) {
      ansMax = rest - targetArr[i];
    } else {
      ansMax = max(ansMax, rest - targetArr[i]);
    }

    if (hasFalse) {
      continue;
    }

    // >  >=  <   <=  =
    if (opArr[i] == ">") {
      if (!(rest > targetArr[i])) {
        hasFalse = true;
      }
    } else if (opArr[i] == ">=") {
      if (!(rest >= targetArr[i])) {
        hasFalse = true;
      }
    } else if (opArr[i] == "<") {
      if (!(rest < targetArr[i])) {
        hasFalse = true;
      }
    } else if (opArr[i] == "<=") {
      if (!(rest <= targetArr[i])) {
        hasFalse = true;
      }
    } else if (opArr[i] == "=") {
      if (!(rest == targetArr[i])) {
        hasFalse = true;
      }
    }
  }

  string outResult;
  if (hasFalse) {
    outResult = "false";
  } else {
    outResult = "true";
  }

  cout << outResult << " " << ansMax << endl;

  return 0;
}