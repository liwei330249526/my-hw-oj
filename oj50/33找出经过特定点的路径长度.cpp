/*
 * 输入一个字符串，都是以大写字母组成，每个相邻的距离是1，第二行输入一个字符串，表示必过的点
 * 说明：每个店可过多次.
 *
输入
ANTSEDXQOKPUVGIFWHJLYMCRZB
ABC


输出
28


 *
 * */

#include "string"
#include "iostream"
using namespace std;
int main() {
  string str1;
  string str2;
  getline(cin, str1);
  getline(cin, str2);

  int ret = 0;
  int start = str1.find(str2[0]); // 第一个字符在str1 的位置
  int end = start;
  for (int i = 1; i < str2.size(); i++) {
    end = str1.find(str2[i]);  // 遍历每个字符在str1 的位置
    ret += abs(start - end); // 记录end 和 start 的距离
    start = end;
  }

  cout << ret << endl;

  return 0;
}