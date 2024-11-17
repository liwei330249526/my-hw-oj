/*
 *
题目描述
幼儿园两个班的小朋友在排队时混在了一起，每位小朋友都指导自己是否与前面一位小朋友同班，请你帮忙把同班的小朋友找出来。
小朋友的编号是整数，与前一位小朋友同班用Y表示，不同班用N表示。
学生序号范围(0-999)，如果输入不合法则打印ERROR。


 *输入
1/N 2/Y 3/N 4/Y

输出
1 2
3 4


 *
 * 输入
1/N 2/Y 3/N 4/Y 5/Y

输出
1 2
3 4 5

 *
 *
 * */

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  stringstream stm(str);
  string token;
  vector<string> arr;

  vector<int> c1;
  vector<int> c2;
  int cid = -1;
  while (getline(stm, token, ' ')) { // 获取所有同学
    arr.push_back(token);
  }

  for (int i = 0; i < arr.size(); i++) { // 遍历每个同学，处理
    int id = arr[i].find('/');
    if (id == string::npos) {
      cout << "ERROR" << endl;
      return 0;
    }

    string stuStr = arr[i].substr(0, id); // 同学编号

    int stu = 0;
    try {
      stu = stoi(stuStr);     // 如果转换失败，捕获异常
    } catch (exception &e) {
      cout << "ERROR" << endl;
      return 0;
    }

    string sameClass = arr[i].substr(id+1); // 同学是否同班级

    if (sameClass == "N") { // 不同
      if (cid == -1) { // 如果是第一个，则加入到 c1
        cid = 1;
        c1.push_back(stu);
      } else if (cid == 1) { // 如果之前是c1， 则转换班级 c2
        cid = 2;
        c2.push_back(stu);
      } else {               // 如果之前是c2, 则转换班级 c1
        cid = 1;
        c1.push_back(stu);
      }
    } else if (sameClass == "Y") {  // 如果相同，则加入班级 cid 的班级
      if (cid == 1) {
        c1.push_back(stu);
      } else {
        c2.push_back(stu);
      }
    } else {                     // 如果垂涎 N Y 之外的字符， 则打印错误
      cout << "ERROR" << endl;
      return 0;
    }
  }

  for (int i = 0; i < c1.size(); i++) {
    cout << c1[i];
    if (i != c1.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  for (int i = 0; i < c2.size(); i++) {
    cout << c2[i];
    if (i != c2.size()-1) {
      cout << " ";
    }
  }
  cout << endl;


  return 0;
}
