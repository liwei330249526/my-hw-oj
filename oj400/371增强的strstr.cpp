/*
 *
题目描述
C语言有一个库函数： char* strstr(const char *haystack, const char* needle), 实现在字符串haystack中查找第一次出现字符串 needle的位置，
如果未找到则返回null
先要求实现一个strstr 增强函数，可以使用待可选段的字符串来模糊查询，与strstr一样返回首次查找的字符串位置

可选段使用 "[]" 标识，标识该位置是可选段中任意一个字符即可满足匹配条件，比如 "a[bc]" 表示可以匹配 "ab" 或 "ac"

输入
与strstr函数，输入参数是两个字符串指针，分别是源字符串和目标字符串
输出
与strstr 函数不同，返回的是源字符串中，匹配子字符串相对于源字符串地址的偏移，如果没有匹配返回-1

样例1
输入
abcd
b[cd]

输出
1

说明：
相当于是在源字符串中查找bc或者bd, bc子字符串相对于abcd的偏移是1


样例2
输入
bbyyu
[ytg][u]


输出
3


例4：
abcdefg
c[de]

输出： 2

例5:
hello world
o[ ]w

输出： 4
 *
 * */

#include "iostream"
#include "string"
using namespace std;
int main() {
  string haystack;
  string needle;
  getline(cin, haystack);
  getline(cin, needle);

  for (int i = 0; i < haystack.size(); i++) { // 从原字符串每个字符开始计算
    int j = 0;
    int k = i;

    while (j < needle.size()) { // 遍历 needle
      if (needle[j] == '[') {
        j++;
        bool findMatch = false;
        while (needle[j] != ']') {  // == ]
          if (haystack[k] == needle[j]) {
            findMatch = true;
          }
          j++;
        }
        // 现在  needle[j] == ]
        if (!findMatch) {
          break;
        }

        // 如果找到了，继续匹配

      } else {
        if (haystack[k] != needle[j]) {
          break;
        }
        // 匹配
      }
      k++;
      j++;
    }
    if (j == needle.size()) {
      cout << i << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}