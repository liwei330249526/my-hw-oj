/*
 *
题目描述
给定一个非空字符串S，其被N个 '-' 分隔成N+1 个子串，给定正整数K，要求除了第一个子串外，其余的子串每K个字符组成新的子串，并用 '-' 分隔
对于新组成的每个子串，如果它含有的小写字母比大写字母多，则将这个子串的所有大写字母转换为小写字母；反之，如果它含有的大写字母比小写字母多，
则将这个子串的所有小写字母转换为大写字母；大小写字母数量相等时，不做转换。

输入
第一行为参数K，第二行为字符串S
输出
输出转换后的字符串

样例1
输入
3
12abc-abCABc-4aB@

输出
12abc-abc-ABC-4aB-@


说明：子串为12abc、abCABc、 4aB@, 第一个子串保留,后面的子串每3个字符一组为abC、ABc、4aB、 @,
abC中小写字母较多，转换为abc, ABc中大写字母较多，转换为ABC, 4aB中大小写字母都为1个，不做转换,
@中没有字母，连起来即12abc abc-ABC 4aB-@


样例2
 输入
12
12abc-abCABc-4aB@

输出
12abc-abCABc4aB@


说明：
子串为12abc、abCABc、 4aB@,
第一个子串保留,后面的子串每12个字符一组为abCABc4aB@, 这个子串中大小写字母都为4个
不做转换,连起来即12abc-abCABc4aB@



样例3
 输入
4
aBcDe-FgHiJ-KlMnO

输出
aBcDe-FgHi-JKLM-nO


样例4
 输入
5
aBcDe-FgHiJ-KlMnO

输出
aBcDe-FGHIJ-KLMNO



 样例5
 输入
1
aBcDe-FgHiJ-KlMnO

输出
aBcDe-F-g-H-i-J-K-l-M-n-O

 *
 *
 *
 * */

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
#include "algorithm"
using namespace std;

void test() {
  string str = "abc@#$";
  string str2(6, ' ');
  transform(str.begin(), str.end(), str2.begin(), ::toupper); // 转换为大写, 用全局的toupper
  cout << str2 << endl;
  return;
}

int main() {
  // 获取 k， 和str
  int k;
  cin >> k;
  string str;
  cin >> str;

  // 以 '-' 分隔字符串
  stringstream stm(str);
  string token;
  vector<string> arr;
  while (getline(stm, token, '-')) {
    arr.push_back(token);
  }

  // 拼接字符串 [1:]
  string res = arr[0];
  string extraStr;
  for (int i = 1; i < arr.size();i++) {
    extraStr += arr[i];
  }
  // aBcDe-FGHIJ-KLMNO
  // 遍历后续字符串， 每 k个字符做一次处理
  int i = 0;
  int lowerCount = 0;
  int upperCount = 0;
  string temStr;
  for (i = 0; i < extraStr.size(); i++) {
    if (islower(extraStr[i])) {
      lowerCount++;
    } else if (isupper(extraStr[i])) {
      upperCount++;
    }
    temStr += extraStr[i];
    // i + 1 是字母的count
    if((i+1) % k == 0) { // 到了指定个数, 做一次处理
      res += '-';
      if(lowerCount < upperCount) { // 如果大写字母多，则转为大写字符串
        transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
        res += temStr;
      } else if (lowerCount > upperCount) { // 如果小写字母多，则转为小写字符串
        transform(temStr.begin(), temStr.end(), temStr.begin(), ::tolower);
        res += temStr;
      } else { // 如果相等，则不做转换
        res += temStr;
      }

      lowerCount = 0;
      upperCount = 0;
      temStr = "";
    }
  };
  // 尾部处理
  if(temStr != "") {
    res += '-';
    if(lowerCount < upperCount) {
      transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
      res += temStr;
    } else if (lowerCount > upperCount) {
      transform(temStr.begin(), temStr.end(), temStr.begin(), ::tolower);
      res += temStr;
    } else {
      res += temStr;
    }
  }

  cout << res << endl;
  return 0;
}

