/*
 * 题目描述
 * 输入一个由N个大小写字母组成的字符串
 * 按照ASCII码值从小到大排序
 * 查找字符串中低 k 个最小的字母
 * 输出该字母在字符串中的位置索引
 * k如果大于字符串长度，输出最大ASCII码值字母所在的字符串位置索引
 * 如果有重复字母，则输出字母最小位置索引
输入
AbCdeFG
3


输出
5

说明:
根据ASCII码值排序，第三个ASCII码值的字母为F
F在字符串中位置索引为5(0为字符串的第一个字母位置索引)



输入
fAdDAkBbBq
4


输出
6

说明:
根据ASCII码值排序前4个字母为AABB由于B重复则只取B的第一个最小位置索引6，
而不是第二个B的位置索引8


 * */

#include "string"
#include "iostream"
#include "algorithm"
using namespace std;

int main() {
  string str;
  getline(cin, str);
  int id;
  cin >> id;

  string sorted_str = str;
  sort(sorted_str.begin(), sorted_str.end());

  if (id > sorted_str.size()) {
    id = sorted_str.size();
  }

  id--;

  char target_c = sorted_str[id];
  int pos = 0;
  for (pos = 0; pos < str.size(); pos++) {
    if (str[pos] == target_c) {
      break;
    }
  }
  cout << pos << endl;
  return 0;
}