/*
 * 题目描述
 * 输入两个字符串S和L，都只包含英文小写字母。s长度<=100, L长度<=500,000
 * 判定S是否是L的有效子串。
 * 判定规则：
 * S中的每个字符在L中都能找到（可以不连续），且S在L中字符的前后顺序与S中的顺序要保持一致
 *
 * 输出，S串最后一个有效字符在L中的位置（首位从0开始计算，无有效字符返回-1）
 *
输入
ace
abcdea


输出
4


 输入
fgh
abcde

输出
-1




 * */

#include "string"
#include "iostream"
using namespace std;
int main() {
  string str1;
  string str2;
  getline(cin, str1);
  getline(cin, str2);
  cin >> str1 >> str2;

  int id1 = 0;
  int id2 = 0;

  int lastLId = 0;
  for (;id1 < str1.size() && id2 < str2.size();) {
    if (str1[id1] == str2[id2]) {
      id1++;
      lastLId = id2;
      id2++;
    } else {
      id2++;
    }
  }

  // s 是 l 的子集
  if (id1 == str1.size()) {
    cout << lastLId << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}