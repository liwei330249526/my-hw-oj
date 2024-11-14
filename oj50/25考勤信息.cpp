/*
 * 题目描述
 * 公司用一个字符串来表示出勤信息
 * absent:缺勤
 * late:迟到
 * leaveearly: 早退
 * present : 正常上班
 *
 * 现在根据全勤信息，判断本次能否获得全勤奖，能获得全勤奖的条件如下：
 * 缺勤不超过一次；
 * 没有连续的迟到/早退；
 * 任意连续7次考勤，缺勤/迟到/早退不超过3次
 *
输入
2
present
present present


输出
true
true



输入
2
present
present absent present present leaveearly present absent


输出
true
false




 输入
1
present absent absent


输出
false


 *
 * */

// 0 1 2 3 4 5 6 7 8

#include "vector"
#include "string"
#include "iostream"
#include "sstream"
using namespace std;

// 返回true， 说明考勤是不正常； 返回false， 说明考勤正常
bool isNotNormal(string str) {
  if (str == "absent" || str == "late" || str == "leaveearly") {
    return true;
  }
  return false;
}

bool getResult(string str) {
//  istringstream istm(str);
//  vector<string> strs;
//  string token;
//  while (istm >> token) {
//    strs.push_back(token);
//  }

  stringstream stm(str);
  vector<string> strs;
  string token;
  while (getline(stm, token, ' ')) {
    strs.push_back(token);
  }

  int absentCount = 0;
  int notNormalCount = 0;


  for (int i = 0; i < strs.size(); i++) {
    // = 8， 则要左边减去一个
    if (i + 1 >= 8) {
      if (isNotNormal(strs[i-7])) {
        // 窗口中减去1个
        notNormalCount--;
      }
    }

    if (isNotNormal(strs[i])){
      // 属于 absent  late  leaveearly 之一
      notNormalCount++;
      if (strs[i] == "absent") {
        absentCount++;
        if (absentCount > 1) {
          return false;
        }
      } else if (strs[i] == "late" || strs[i] == "leaveearly") {
        if (i > 0 && (strs[i-1] == "late" || strs[i-1] == "leaveearly")) {
          return false;
        }
      }
    } else {

    }

    // i = 6， 则有连续7天； 0 1 2 3 4 5 6
    if (i+1 >= 7) {
//      notNormalCount = 0;
//      for (int j = i; j >= i - 6; j--) {
//        if (strs[j] != "present") {
//          notNormalCount++;
//        }
//      }

      if (notNormalCount > 3) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<string> strs(n);

  for (int i = 0; i < n; i++) {
    getline(cin, strs[i]);
  }
  vector<bool> res;
  for (int i = 0; i < strs.size(); i++) {
    bool ret = getResult(strs[i]);
    res.push_back(ret);
  }

  for (int i = 0; i < res.size(); i++) {
    if (res[i]) {
      cout << "true" << endl;
    } else {
      cout << "false" << endl;
    }
  }

  return 0;
}