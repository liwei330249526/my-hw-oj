/*
 * 题目描述
 * 给定一个费控的字符串S，其被N个'-'分隔成N+1个子串，给定正整数K，要求除第一个子串外，其余的串
 * 每k个用'-'分隔，并将小写字母转换为大写.
 *
 * 输入输出
 * 输入
 * 正整数K和'-'分隔的字符串，如
 * 2
 * 25G3C-abc-d
 *
 * 输出
 * 转换后的字符串
 *
 * 样例1
输入
4
5F3Z-2e-9-w


输出
5F3Z-2E9W

解释：

字符串 S 被分成了两个部分，每部分 4 个字符；

注意，两个额外的破折号需要删掉。

 *
 *
 * 样例2
输入
2
2-5g-3-J


输出
2-5G-3J


解释：

字符串 S 被分成了 3 个部分，按照前面的规则描述，第一部分的字符可以少于给定的数量，其余部分皆为 2 个字符

 *
 * */

#include "string"
#include "iostream"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  // 获取字符串 str 和数字 n
  string str1;
  string str2;
  getline(cin, str1);
  getline(cin, str2);

  int n;
  n = stoi(str1);

  // 字符串流，用'-' 分隔字符串
  stringstream stm(str2);
  string token;
  vector<string> parts;
  while (getline(stm, token, '-')) {
    parts.push_back(token);
  }

  string firstWord;

  string remain;
  // 剩余的字符串
  for (int i = 1; i < parts.size(); i++) {
    for (int j = 0; j < parts[i].size(); j++) {
      if(isalpha(parts[i][j]) || isdigit(parts[i][j])) {
        remain += toupper(parts[i][j]) ;
      }
    }
  }

  string res = firstWord = parts[0];

  // 对剩余的字符串格式化, 即每隔n个字符，加一个'-'
  for (int i = 0; i < remain.size(); i += n) {
    if(i+n < remain.size()) {
      res += "-" + remain.substr(i, n);
    } else {
      res += "-" + remain.substr(i, remain.size() - i);
    }
  }

  cout << res << endl;

  return 0;
}