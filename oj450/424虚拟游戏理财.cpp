/*
 *
题目描述
在一款虚拟游戏中生活，你必须进行投资以增强在虚拟游戏中的资产以免被淘汰出局。现有一家bank，它提供有若干理财产品m，风险及投资回报不同，你有N
元进行投资，能接受的总风险为X。
你要在可接受范围内选择最优的投资方式获得最大回报。

说明
1 在虚拟游戏中，每项投资风险值相加为总风险值；
2 在虚拟游戏中，最多能投资2个理财产品；
3 在虚拟游戏中，最小单位为整数，不能拆分为小数；
投资额* 回报率 = 投资回报

输入
第1行：产品数， 总投资额， 可接受总风险
第2行：产品投资回报率序列，输入为整数
第3行，产品风险值序列
第4行：最大投资额度序列

输出
每个产品的投资额序列

样例1
输入
5 100 10
10 20 30 40 50
3 4 5 6 10
20 30 20 40 30


输出
0 30 0 40 0


说明:
投资第二项 30 个单位，第四项 40 个单位，总的投资风险为两项相加为 4+6=10


样例2
输入
1 1000 10
10
5
1000


输出
1000

 *
 *
 * */

#include "iostream"
#include "vector"
using namespace std;

int main() {
  int m; // 产品数
  int n; // 钱数
  int x; // 最高风险
  cin >> m >> n >> x;

  vector<int> benefits(m); // 回报率
  vector<int> risks(m); // 风险值
  vector<int> limits(m); // 最大限制

  for (int i = 0; i < m; i++) {
    cin >> benefits[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> risks[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> limits[i];
  }

  // 选一个

  int choose1 = -1;
  int money1 = -1;
  int choose2 = -1;
  int money2 = -1;

  int ret = 0;
  for (int i = 0; i < m; i++) {
    if (risks[i] <= x) { // 风险可以承受
      int realBuy = min(n, limits[i]);
      if (ret < ret, realBuy * benefits[i] / 100) {
        ret = ret, realBuy * benefits[i] / 100;
        choose1 = i;
        money1 = realBuy;
      }
    }
  }

  // 两两组合
  int prior1= -1;  // 第一优先
  int prior2= -1; // 第二优先
  for (int i = 0; i < m; i++) {
    for (int j = i+1; j < m; j++) {
      if (risks[i] + risks[j] <= x) { // 风险可以承受
        if (benefits[i] > benefits[j]) { // 优先投资 i
          prior1 = i;
          prior2 = j;
        } else {
          prior1 = j;
          prior2 = i;
        }

        // 优先投资 prior1
        if (n <= limits[prior1]) { // 如果 prior1 已经用完了钱，说明值选一个， 这个场景在上面计算了，这里可以再加一下
//          int realBuy = n;
//          ret = max(ret, realBuy * benefits[prior1] / 100); // 维护最大收益
//          if (ret < realBuy * benefits[prior1] / 100) {
//            ret = realBuy * benefits[prior1] / 100;
//            choose1 = prior1;
//            money1 = realBuy;
//          }
        } else { // 投资完 prior1 还有余钱投资 prior2
          int realBuy1 = limits[prior1];
          int realBuy2 = limits[prior2];
          realBuy2 = min(realBuy2, n - limits[prior1]);
          if (ret < realBuy1 * benefits[prior1] / 100 + realBuy2 * benefits[prior2] / 100) {
            ret = realBuy1 * benefits[prior1] / 100 + realBuy2 * benefits[prior2] / 100;
            choose1 = prior1;
            money1 = realBuy1;

            choose2 = prior2;
            money2 = realBuy2;
          }
        }
      }
    }
  }

  for (int i = 0; i < m; i++) {
    if (i == choose1) {
      cout << money1;
    } else if (i == choose2) {
      cout << money2;
    } else {
      cout << 0;
    }

    if (i != m-1) {
      cout << " ";
    }
  }
  cout << endl;


  return 0;
}