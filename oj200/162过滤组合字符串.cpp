/*
 *
题目描述
每个数字关联多个字母，关联关系如下:
0 关联 a b c
1 关联 d e f
2 关联 g h f
3 关联 j k i
4 关联 m n o
5 关联 p q r
6 关联 s t
7 关联 u v
8 关联 w x
9 关联 y z
输入一串数字后，通过数字和字母的对应关系可以得到多个字母字符串（要求按照数字的顺序组合字母字符串）
屏蔽字符串：屏蔽字符串中的所有字母不能同时在输入的字符串中出现，如屏蔽字符串是 abc， 则要求字符串中不能同时出现 a b c
但是允许同时出现 a b, 或 a c， 或 b c等。
给定一个数字字符串和一个屏蔽字符串，输出所有可能的字符组合；

例如输入的数字字符串 78 和屏蔽字符串 ux， 输出结果为 uw, vw, vx; 数字字符串 78, 可以得到如下字符串 uw, ux, vw, vx; 由于 ux
是屏蔽字符串， 因此排除，最终的输出是 uw, vw, vx；
 *
 * 样例1
 * 输入
78
ux


输出
uw,vw,vx,

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "unordered_map"
#include "unordered_set"
using namespace std;

void getAllCollections(string numStr, unordered_map<char, string> &dict,
                       vector<string> &strCollects, string path, int index) {
  if (index == numStr.size()) {
    strCollects.push_back(path);
    return ;
  }
  string vStr = dict[numStr[index]];
  for (int i = 0; i < vStr.size(); i++) { // 遍历每个字符， 0 关联 a b c
    getAllCollections(numStr, dict, strCollects, path + vStr[i], index+1);
  }

  return;
}

// 如果str 的字符都在, 则被block，true； 否则，为false
bool isStrBlocked(string str, string blockChr) {
  for (char c : blockChr) {
    if (str.find(c) == string::npos) { // 不在
      return false;
    }
  }

  // 都在
  return true;
}


int main() {
  string numStr;
  string blockStr;

  getline(cin, numStr);
  getline(cin, blockStr);

  unordered_map<char, string> dict {
    { '0', "abc"},
    { '1', "def"},
    { '2', "ghf" },
    { '3', "jki" },
    { '4', "mno" },
    { '5', "pqr" },
    { '6', "st" },
    { '7', "uv" },
    { '8', "wx" },
    { '9', "yz" }
  };

  // 获取字符串集合
  vector<string> strCollects;
  getAllCollections(numStr, dict, strCollects, "", 0);

  // strCollects, blockStr

  vector<string> res;
  for(int i = 0; i < strCollects.size(); i++) {
    if(!isStrBlocked(strCollects[i], blockStr)) {
      res.push_back(strCollects[i]);
//      cout << strCollects[i] << endl;
    }
  }

  for(int i = 0; i < res.size(); i++) {
    cout << res[i] << ",";
  }

  return 0;
}