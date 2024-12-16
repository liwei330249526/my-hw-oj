/*
 *
题目描述
商人经营一家店铺，有number种商品，由于仓库限制没见商品的最大持有数量是 item[index], 每种商品的价格是 item-price[item_index][day],
通过对商品的买进和卖出获利，请给出商人在days天内能获得最大利润。

输入
第一行输入商品的数量 number， 比如3
第二行输入商品售货天数days，比如3
第三行输入仓库限制每件商品的最大持有数量items[index], 比如 4 5 6
后面继续输入 number 行的days 列，含义如下
第一件商品每天价格，如 1 2 3
第二件商品每天价格，如 4 3 2
第三件商品每天价格，如 1 4 3

输出
商人获得最大利润.

 *
 * 样例1
输入
3
3
4 5 6
1 2 3
4 3 2
1 5 2



输出
32


 *
 * */

#include "iostream"
#include "vector"
using namespace std;
int main() {
  int numbers; // 商品数量
  int days;   // 天数

  cin >> numbers >> days;
  vector<int> limits(numbers);
  for (int i = 0; i < numbers; i++) {
    cin >> limits[i];
  }

  vector<vector<int>> prices(numbers, vector<int>(days));
  for (int i = 0; i < numbers; i++) { // 每件商品
    for (int j = 0; j < days; j++) { // 每天
      cin >> prices[i][j];
    }
  }


  int ret = 0;
  for (int i = 0; i < numbers; i++) { // 每件商品
    int curRet = 0;
    for (int j = 0; j < days; j++) { // 每天
      // 贪心， 如果今天大于昨天，则昨天买，今天卖
      if (j > 0 && prices[i][j-1] < prices[i][j]) {
        curRet += prices[i][j] - prices[i][j-1];
      }
    }

    ret += curRet * limits[i];
  }

  cout << ret << endl;

  return 0;
}