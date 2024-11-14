/*
 * 题目描述
 * 全量和已占用字符集
 * 给定两个字符集合，一个是全量字符集，一个是已占字符集，已占用字符集中的字符不能再使用。
 * 要求输出剩余可用字符集。
 *
 * 输入输出
 * 输入
 * 1 输入一个字符串一定包含@, @前为全量字符集， @后的为已占用字符集。
 * 2 已占用字符集找那个的字符一定是全量字符集中的字符。
 * 3 字符集中的字符跟字符之间使用英文逗号隔开。
 * 4 每个字符都表示为字符+数字的形式用英文冒号分隔，比如a:1标识一个a字符。
 * 5 字符只考虑英文字母，区分大小写。
 * 6 数字只考虑整型，不超过100。
 * 7 如果一个字符都没被占用 @ 表示仍然存在。
 * 8 例如 a:3, b:5, c:2 @
 *
 * 输出
 * 1 输出可用字符集
 * 2 不同的输出字符集之间用回车换行
 * 3 注意，输出的字符顺序要和输入的一致
 * 4 如果某个字符全被占用，则不需要输出。
 *
输入
a:3,b:5,c:2@a:1,b:2

输出
a:2,b:3,c:2

说明：

全量字符集为三个a，5个b，2个c

已占用字符集为1个a，2个b

由于已占用字符不能再使用

因此剩余可用字符为2个a，3个b，2个c

因此输出a:2,b:3,c:2




输入
a:1,b:2,c:3@d:1,e:2,f:3
输出
a:1,b:2,c:3


输入
x:10,y:20,z:30@x:5,y:10,z:15
输出
x:5,y:10,z:15


输入
m:7,n:8,o:9@m:2,n:4,o:6
输出
m:5,n:4,o:3


 *
 *
 * */

#include "string"
#include "iostream"
#include "unordered_map"
#include "vector"
#include "sstream"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  int id = str.find("@");
  string str1 = str.substr(0, id);
  string str2 = str.substr(id+1);
  vector<string> orderStrs;
  unordered_map<string, int> strsCount;

  stringstream stm1(str1);
  string token;
  while (getline(stm1, token, ',')) {
    string c = string(1,token[0]);
    int count = stoi(token.substr(2));
    orderStrs.push_back(c);
    strsCount[c] += count;
  }

  stringstream stm2(str2);
  while (getline(stm2, token, ',')) {
    string c = string(1,token[0]);
    int count = stoi(token.substr(2));
    strsCount[c] -= count;
  }

  string res;

  for (int i = 0; i < orderStrs.size(); i++) {
    if (strsCount.find(orderStrs[i]) != strsCount.end()) { // str 在 字典中存在
      if(strsCount[orderStrs[i]] > 0) {
        if (!res.empty()) {
          res += ",";
        }

        res += orderStrs[i] + ":" + to_string(strsCount[orderStrs[i]]);
      }
    }
  }
  cout << res << endl;

  return 0;
}