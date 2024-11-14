/*
 * 题目描述
 * 数轴 x 有两个店的序列A={A1，A2，... Am}和 B={B1，B2 ... Bn}均为正整数，A、B 赢从小到大排好序，
 * A、B 均部位空。
 * 给定一个距离R（正整数），列出同时满足如下条件的所有（Ai， Bj）数对：
 * 条件
 * 1 Ai <= Bj
 * 2 Ai, Bj 距离小于等于R， 但如果Ai找不到R范围内的Bj，则列出距离它最近的1个Bj，当然此种情况
 *    仍然要满足条件1，但如果仍然找不到，就丢弃Ai。
 *
输入
A={1,3,5},B={2,4,6},R=1

输出
(1,2)(3,4)(5,6)

 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
using namespace std;

/*
 * bi - ai >= 0
 *
 * bi - ai <= r
 *
 *
 * bi - ai > r
 *
 * bi - ai < 0
 *
 *    0   r
 *
 *    A={1,3,5}
 *    B={2,4,6}
 * */
string getStrArr(vector<int> &A, vector<int> &B, int R) {
  int id1 = 0;
  int id2 = 0;
  string ret;

  while (id1 < A.size() && id2 < B.size()) {
    if (B[id2] - A[id1] > R) { // B 太大了
      ret +=  "(" + to_string(A[id1]) + "," + to_string(B[id2]) + ")";
      id1++;
    } else if (B[id2] - A[id1] >= 0){
      int id3 = id2; // 临时id3
      while (id3 < B.size() && B[id3] - A[id1] >= 0 && B[id3] - A[id1] <= R) {
        ret +=  "(" + to_string(A[id1]) + "," + to_string(B[id3]) + ")";
        id3++;
      }
      id1++;
//      id2++;
    } else { // B 太小了
      id2++;
    }
  }

  return ret;
}

int main() {
//  string str = "A={1,3,5},B={2,4,6},R=1";
  string str;
  getline(cin, str);

  string str1;
  string str2;
  vector<int> arr1;
  vector<int> arr2;
  int R;

  int left = 0;
  int right = 0;
  left = str.find("A={");
  right = str.find("B={");
//  cout << left << " " << right << endl; // left+3, right -3 ;  right -3 - left - 3 + 1;  right - left -6 + 1
//  cout << str.substr(left+3, right - left - 5) << endl;
  str1 = str.substr(left+3, right - left - 5);

  left = right;
  right = str.find("R=");
//  cout << str.substr(left+3, right - left - 5) << endl;
  str2 = str.substr(left+3, right - left - 5);

  R = stoi(str.substr(right+2));
//  cout << R << endl;

  stringstream stm(str1);
  string token;
  while (getline(stm, token, ',')) {
    arr1.push_back(stoi(token));
  }

  stringstream stm2(str2);
  while (getline(stm2, token, ',')) {
    arr2.push_back(stoi(token));
  }

  string retStr = getStrArr(arr1, arr2, R);

  cout << retStr << endl;

  return 0;
}