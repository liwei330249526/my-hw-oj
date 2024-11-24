/*
 *
题目描述
某短信厂商，为庆祝国庆，退出充值优惠活动。
现在给出客户预算和优惠序列，求最多可获得的短信条数。

输入
第一行客户预算M， 0<=M<=10^6
第二行给出售价表，P1，P2，...Pn,其中 1<=n<=100
Pi为充值i元获得的短信条数。 1<=Pi<=1000, 1<=n<=100

输出
最多获得的短信条数

 *
 * 样例1
输入
6
10 20 30 40 60




输出
70

说明
分两次充值最优，1块和5块各充一次，总条数10+60=70

 *
 * 样例2
输入
15
10 20 30 40 60 70 80 90 150




输出
220

 *
 * 动态规划
 *
 *
 * */

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
using namespace std;

int main() {
  string targetStr;
  int numTarget;

  getline(cin, targetStr);
  numTarget = stoi(targetStr);

  string str;
  getline(cin, str);

  vector<int> messages;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    messages.push_back(stoi(token));
  }

  vector<int> dp(numTarget+1);  // dp[j] 动态规划，j 这么大的背包，能背的价值最多多大？
  for(int i = 0; i < messages.size(); i++) { // 遍历物品, 物品价格是 i+1
    for (int j = 0; j < dp.size(); j++) {  // 遍历背包
      // 价格
      int curP = i+1;                      // i 的当前价格是 i+1
      if (curP <= j) {              // 对每个dp[j], 1 可以取 i 方案，结果为 [j-curP]这么多钱的最大价值加上 i方案的价值，即则 dp[j-curP]+messages[i]；
        dp[j] = max(dp[j-curP] + messages[i], dp[j]);  //   2 可以不取i方案, 则上一轮循环的结果， 即dp[j]
      }
    }
  }

  cout << dp[dp.size()-1] << endl;

  return 0;
}