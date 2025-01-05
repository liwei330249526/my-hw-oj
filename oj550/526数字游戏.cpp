/*
 *
题目描述
小明玩一个游戏
系统阀1+n张牌，每张牌有一个整数。
第一张给小明，后n张按照发牌顺序排成连续的一行。
需要小明判断，后n张牌中，是否存在连续的若干张牌，启和可以整除小明手中牌上的数字

输入
输入数据有多组，每组输入数据有两行，输入到文件结尾结束
第1行有两个整数n和m，空格隔开。m代表发给小明牌上的数字。
第2行有n个数，代表后续发的n张牌上的数字，以空格隔开。
输出
对每组输入，如果存在满足条件的若干张牌，则输出1；否则输出0

 3 5 9 11
 3 8 27 48

样例1
输入
6 7
2 12 6 3 5 5
10 11
1 1 1 1 1 1 1 1 1 1

0 2 14 20 23 28 32

输出
1
0


说明：
两组输入,第一组小明牌的数字为7,再发了6张牌;
第1、2两张牌教字和为14,可以整除7,输出1;
第二组小明牌的教字为11,再发了10张牌,这10张牌数字和为10,无法整除11,输出0

 *
 *
 *
 * */

#include "iostream"
#include "vector"
#include "sstream"
#include "unordered_map"
using namespace std;
int main() {
  string str;
  vector<string> data;
  while (getline(cin, str)) {
    if (str.size() == 0) {
      break;
    }

    data.push_back(str);
  }

  int dataId = 0;
  while (dataId < data.size()) {
    string str1 = data[dataId];
    dataId++;
    string str2 = data[dataId];
    dataId++;

    stringstream stm(str1);
    string token;
    vector<int> arr1;
    while (getline(stm, token, ' ')) {
      arr1.push_back(stoi(token));
    }

    stm.clear();
    stm.str(str2);
    vector<int> arr2;
    while (getline(stm, token, ' ')) {
      arr2.push_back(stoi(token));
    }

    int target = arr1[1];

    unordered_map<int, int> preSum;
    preSum[0] = 1;
    int sum = 0;
    bool find = false;
    for (int i = 0; i < arr2.size(); i++) {
      sum += arr2[i];
//      if (preSum.find(sum - target) != preSum.end()) { // 存在 , 这里是连续数字和 等于target
//        find = true;
//        break;
//      }

      // 连续数字和是tatget 的倍数
      if(preSum.find(sum % target) != preSum.end()) {
        find = true;
        break;
      }

      preSum[sum % target]++;
    }

    if (find) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }

  return 0;
}