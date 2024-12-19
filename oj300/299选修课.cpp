/*
 *
题目描述
现有两门选修课，每门选修课程都有一部分学生选修，每个学生都有选修课的成绩，需要你找出同时选修了两门选修课的学生，现按照班级进行划分，班级编号小的先输出，
每个班级按照两门选修课成绩和降序排序，成绩相同时，按照学生学号升序排序

输入
第一行为第一门选修课学生的成绩，第二行为第二门选修课学生的成绩，每行数据中学生之间以分号分隔，每个学生的学号和成绩以英文逗号分隔，学生学号的格式为
8位数字。

输出
同时选修了两门选修课的学生的学号，如果没有同时选修两门选修课的学生，则输入NULL。如果有，则先按班级划分，编辑编号小的线输出，每个班级先输出班级编号（学号前5位），
然后另起一行输出这个班级同时选修两门选修课的学生学号，学号哪找要求排序（按照两门选修课成绩和的降序，乘积和相同时按照学号升序），学生之间以英文分号分隔。

样例1
输入
01202021,75;01201033,95;01202008,80;01203006,90;01203088,100
01202008,70;01203088,85;01202111,80;01202021,75;01201100,88




输出
01202
01202008;01202021
01203
01203088

说明：
同时选修了两门选修课的学生01202021、01202008、 01203088, 这三个学生两门选修课的成绩和分别为150、150、 185,01202021、01202008属于01202班的学生
按照成绩和降序，成绩相同时按学号升序输出的结果01202008;01202021,01203088属于01203班的学生
按照成绩和降序，成绩相同时按学号升序输出的结果01203088, 01202的班级编号小于01203的班级编号，需要先输出


样例2
输入
01201022,75;01202033,95;01202018,80;01203006,90;01202066,100
01202008,70;01203102,85;01202111,80;01201021,75;01201100,88


输出
NULL

说明：
没有同时选修了两门选修课的学生，输出NULL

 *
 * */

#include "string"
#include "vector"
#include "unordered_map"
#include "iostream"
#include "algorithm"
#include "sstream"
using namespace std;
int main() {
  string str1;
  string str2;
  cin >> str1;
  cin >> str2;

  unordered_map<string, int> dict1;
  stringstream stm(str1);
  string token;
  while (getline(stm, token, ';')) {
    int sid = token.find(',');
    dict1[token.substr(0, sid)] = stoi(token.substr(sid+1));
  }

  unordered_map<string, int> dict2;
  stringstream stm2(str2);
  while (getline(stm2, token, ';')) {
    int sid = token.find(',');
    dict2[token.substr(0,sid)] = stoi(token.substr(sid+1));
  }

  unordered_map<string, vector<pair<string, int>>> dict3;  // 班级 ： {学生1, 总成绩} {学生2， 总乘积}
  for (auto it : dict1) {
    string stuNum = it.first;  // 学号
    int stuScore1 = it.second; // 1 成绩
    if (dict2.find(stuNum) != dict2.end()) { // 存在
      dict3[stuNum.substr(0, 5)].push_back({stuNum, stuScore1 + dict2[stuNum]}); // 加入学生1
    }
  }

  if (dict3.empty()) {
    cout << "NULL" << endl;
    return 0;
  }

  // 班级排序
  vector<string> cls;
  for (auto it : dict3) {
    cls.push_back(it.first);
  }
  sort(cls.begin(), cls.end(), [](string s1, string s2) {
    return s1 < s2;
  });

  for (int i = 0; i < cls.size(); i++) {
    vector<pair<string, int>> studs = dict3[cls[i]]; // 这个班级的学生
    sort(studs.begin(), studs.end(), [](pair<string, int> &p1, pair<string, int> &p2) {
      if(p1.second != p2.second) {
        return p1.second > p2.second;
      }
      return  p1.first < p2.first;
    });

    // 输出这个班级的 学生学号
    cout << cls[i] << endl;
    for (int j = 0; j < studs.size(); j++) {
      cout << studs[j].first;
      if (j != studs.size()-1) {
        cout << ";";
      }
    }
    cout << endl;
  }


  return 0;
}