/*
 *
题目描述
给定一个字符串，只包含大写字母，求在包含同一字母的子串中，长度第k长的子串的长度，相同字母只取最长的那个子串

输入
第1行有一个子串，只包含大写字母
第2行为k的值
输出
输出连续出现次数第k多的字母的次数

样例1
输入
AAAAHHHBBCDHHHH
3


输出
2


说明:
同一字母连续出现的最多的是A和H,出现四次;
第二多的是H, 3次,但是H已经存在4个连续的,故不考虑;
下个最长子串是BB，所以最终答案应该输出2


样例2
输入
AABAAA
2


输出
1

说明：
同一字母连续出现的最多的是A,三次;
第二多的还是A,两次,但A已经存在最大连续次数三次,故不考虑;
下个最长子串是B,所以输出1


 *
 * */

#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  string str;
  cin >> str;
  int k;
  cin >> k;
  unordered_map<char, int> dict;
  char preC = str[0];
  int count = 1;
  for (int i = 1; i < str.size(); i++) {
    if (preC == str[i]) { // 和前面一样
      count++;
    } else { // 和前面不一样
       // 记录preC，重置count和preC
       if (dict[preC] < count) {
         dict[preC] = count;
       }

       preC = str[i];
       count = 1;
    }
  }

  vector<int> sorted_arr;
  if (dict[preC] < count) { // 尾部字符
    dict[preC] = count;
  }

  for (auto it : dict) {
    sorted_arr.push_back(it.second);
  }
  sort(sorted_arr.begin(), sorted_arr.end(), [](int a, int b) {
      return a > b;
  });
  if (k-1 >= sorted_arr.size()) {
    cout << -1 << endl;
  } else {
    cout << sorted_arr[k-1] << endl;
  }

  return 0;
}