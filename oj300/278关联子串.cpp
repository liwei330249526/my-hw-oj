/*
 *
题目描述
给定两个字符串str1和str2，str1进行排列组合只要有一个str2的子串则认为str1和str2是关联子串
请返回子串在str2的起始位置，若不是关联子串则返回-1
两个字符串的长度范围[1,100000] 之间

样例1
输入
abc efghicbaiii

输出
5

样例2
输入
abc efghiccaiii

输出
-1


 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main(){
  string str;
  getline(cin, str);
  int id = str.find(' ');
  transform(str.begin(), str.end(), str.begin(), [](char c){
    return tolower(c);
  });
  string str1 = str.substr(0, id);
  string str2 = str.substr(id+1);

  if (str1.size() > str2.size()) {
    cout << -1 << endl;
    return 0;
  }

  vector<int> count1(26);
  vector<int> count2(26);
  int index = 0;
  for (index = 0; index < str1.size(); index++) {
    count1[str1[index] - 'a']++;
    count2[str2[index] - 'a']++;
  }

  if (count1 == count2) {
    cout << 0 << endl;
    return 0;
  }

  int left = 0;  // 窗口即将删除这个
  int right = index; // 窗口即将加上这个
  while (right < str2.size()) {
    count2[str2[left] - 'a']--;
    count2[str2[right]- 'a']++;
    left++;
    right++;
    if (count1 == count2) {
      cout << left << endl;
      return 0;
    }
  }
  cout << -1 << endl;

  return 0;
}