/*
 *
题目描述
羊，狼，农夫都在岸边，当羊的数量小于狼的数量时，狼会攻击羊，农夫会损失羊。农夫有一搜容量固定的串，能承载固定数量的动物。
要求求出不损失羊的情况下将全部羊和狼运到对岸需要的最小次数。
只计算农夫取对岸的次数，回程时农夫不会运送羊和狼。

备注： 农夫在或农夫离开后，羊的数量大于狼的数量，狼不会攻击。
 *
 * 样例1
 * 输入
5 3 3


输出
3


说明：
第一次运2只狼
第二次运3只羊
第三次运2只羊和1只狼

 *
 * 样例2
 * 输入
5 4 1


输出
0


说明：
如果找不到不损失羊的运送方案，输出0



 *
 * 样例3
 * 输入
15 13 5


输出
7

 *
 * 暴力破解，递归法
 *
 * 1 保证本岸 羊大于狼
 * 2 保证对岸，羊大于狼
 * 3 截止条件，羊加狼小于或等于 船容量。
 *
 * */




#include "iostream"
#include "stdint.h"
using namespace std;

void transPort(int sheepCount1, int wolfCount1, int sheepCount2, int wolfCount2, int boatCap, int times, int &minTimes) {
  if (sheepCount1 + wolfCount1 <= boatCap) {
    minTimes = min(minTimes, times+1);
    return;
  }

  for (int i = 0; i <=sheepCount1 && i <= boatCap; i++) {
    for (int j = 0; j <= wolfCount1 && j <= boatCap; j++) {
      if (i == 0 && j == 0) {
        continue;
      }

      if (i + j <= boatCap && sheepCount1-i > wolfCount1-j && sheepCount2 + i > wolfCount2+j) {
        transPort(sheepCount1 - i, wolfCount1 - j, sheepCount2 + i, wolfCount2 + j, boatCap, times+1, minTimes);
      }
    }
  }
}
int main() {
  int sheepCount;
  int wolfCount;
  int boatCap;

  cin >> sheepCount >> wolfCount >> boatCap;

  int minTimes = INT32_MAX;

  transPort(sheepCount, wolfCount, 0, 0, boatCap, 0, minTimes);

  if (minTimes == INT32_MAX) {
    cout << 0 << endl;
  } else {
    cout << minTimes << endl;
  }

  return 0;
}