/*
 * 题目描述
 * 双11众多商品打折销售，小明想购买一些物品，他决定购买三件，且尽可能花完资金。
 * 请设计程序，比昂住小明计算尽可能花费的最大资金数额。
 *
 * 输出满足条件的最大花费额度
 * 如果不存在，则返回-1
 *
 * 样例1
输入
23,26,36,27
78

输出
76

说明：
金额23、26和27相加得到76, 而且最接近且小于输入金额78。

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
using namespace std;
int main() {
  string str;
  getline(cin, str);
  int money;
  cin >> money;

  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }

  vector<int> dp(money+1);

  int res = 0;
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr.size(); j++) {
      if (i == j) {
        continue;
      }

      for (int k = 0; k < arr.size(); k++) {
        if (i == k || j == k) {
          continue;
        }

        int sumt = arr[i] + arr[j] + arr[k];
        if (sumt <= money) {
          res = max(res, sumt);
        }
      }
    }
  }
  if (res == 0) {
    cout << -1 << endl;
  } else {
    cout << res << endl;
  }

  return 0;
}