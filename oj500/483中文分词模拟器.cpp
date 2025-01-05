/*
 *
题目描述
给定一个连续不包含空格的字符串，该字符串仅包含英文小写字母及英文标点符号（逗号、分号、句号），同时给定词库，对该字符串进行精确分词。

说明
1 精确分词：字符串分词后，不会出现重叠，即 "ilovechina", 不同词库可分割为 "i,love,china" , "ilove,china", 不能分割出现重叠的
"i,love,china"  i 出现重叠。
2 标点符号不成次，仅用于断句
3 词库：根据外部只是库统计出来的常用词汇例： dictionary=["i", "love", "china", "lovechina", "ilove"]
4 分词规则：采用分词顺序优先且最长匹配规则
  "ilovechina", 假设分词结果 [i, ilove, lo, love, ch, china, lovechina], 则输出 [ilove, china]
   错误输出[i, lovechina], 原因： "ilove" > 优先于 "lovechina" 成词.
   错误输出[i, love, china], 原因 "ilove" > "i" 醉熏最长匹配规则

输入
第1行输入待分词语句 "ilovechina" ，
第2行输入中文词库： "i,love,china,ch,na,ve,lo,this,is,this,word", 词库长度限制：1 < length < 100000

输出
按顺序输出分词结果: "i,love,china"

样例1
输入
ilovechina
i,love,china,ch,na,ve,lo,this,is,the,word

输出
i,love,china

样例2
输入
iat
i,love,china,ch,na,ve,lo,this,is,the,word,beauti,tiful,ful


输出
i,a,t


说明:
单个字母，不在词库中且不成词则输出单个字母


样例3
输入
ilovechina,thewordisbeautiful
i,love,chinaa,ch,na,ve,lo,this,is,the,word,beauti,tiful,ful

输出
i,love,china,the,word,is,beauti,ful


说明：

每次分词最长的即可

 *
 * */


#include "sstream"
#include "iostream"
#include "unordered_set"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  unordered_set<string> dict;
  string str2;
  getline(cin ,str2);

  stringstream stm(str2);
  string token;
  while (getline(stm, token, ',')) {
    dict.insert(token);
  }

  vector<string> res;
  string resT;
  for (int i = 0; i < str.size(); ) {
    // 如果遇到符号， 则将临时字符串加入到结果集
    if(str[i] == ',' || str[i] == ';' || str[i] == '.') {
      i++;
      continue;
    }

    // 找一个最长的匹配字符串, 从i开始
    int j = i; // 包括j
    int mxLen = 0;
    while (j < str.size()) {
      if (dict.find(str.substr(i, j-i+1)) != dict.end()) { // 如果存在， 记录最大字符串
        mxLen = max(mxLen, j-i+1);
      }
      j++;
    }

    if (mxLen == 0) { // 不存在
      res.push_back(string(1, str[i]));
      i++;
    } else { // 存在，则最大的一个串
      res.push_back(str.substr(i, mxLen));
      i += mxLen;
    }
  }

  string result = "";
  for (int i = 0; i < res.size(); i++) {
    if(res[i] != " ") {
      result += res[i];
      result += ",";
    }
  }
  cout << result.substr(0, result.size()-1) << endl;
  return 0;
}