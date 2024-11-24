/*
 * 题目描述
 * 记账本上记录了若干条多国货币集合，需要转换为人民币（fen），汇总后输出。
 * 每行记录一条金额，金额带有货币单位，格式为数字+单位，可能单独元，或者单独分，或者元与分的组合。
 * 要求将这些货币全部换算成人民币（fen）后进行汇总，汇总结果仅保留整数，系数部分舍弃。
 * 元与分的换算都是1:100，如下：
 * 1CNY=100fen     元-分
 * 1HKD=100cents   港元-港分
 * 1JPY=100sen     元-仙
 * 1EUP=100eurocents  欧元-欧分
 * 1GBP=100pence   英镑-便士
 *
 * 汇率表如下
 * CNY   JPY     HKD   EUR   GBP
 * 100   1825    123   14    12
 *
 * 样例1
输入
1
100CNY

输出
10000

说明：
100CNY转换后是10000fen,所以输出结果为10000
 *
 * 样例2
输入
1
3000fen

输出
3000

说明：
3000fen,结果就是3000
 *
 *
 * 样例3
输入
1
123HKD

输出
10000

说明：
HKD与CNY的汇率关系是123:100,所以换算后，输出结果为10000


 *
 *
 * 样例4
输入
2
20CNY53fen
53HKD87cents

输出
6432

说明：
20元53分+53港元87港分，换算成人民币分后汇总，为6432


 *
 * */



#include "string"
#include "iostream"
#include "vector"
using namespace std;

// 转换为分单位
float getV(string unit) {
  if (unit == "CNY") {
    return 100;
  } else if(unit == "fen") {
    return 1;
  }  else if(unit == "HKD") {
    return float(100) / 123 * 100;
  } else if(unit == "cents") {
    return float(1) / 123 * 100;
  } else if(unit == "JPY") {
    return float(100) / 1825 * 100;
  } else if(unit == "sen") {
    return float(1) / 1825 * 100;
  } else if(unit == "EUP") {
    return float(100) / 14 * 100;
  } else if(unit == "eurocents") {
    return float(1) / 14 * 100;
  } else if(unit == "GBP") {
    return float(100)/12 * 100;
  } else if(unit == "pence") {
    return float(1)/12 * 100;
  }
  return 0;
}

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<string> moneys(n);

  // 获取所有行
  for (int i = 0; i < n; i++) {
    getline(cin, moneys[i]);
  }

  // 20CNY53fen
  float sum = 0;
  for (int i = 0; i < moneys.size(); i++) { // 遍历每行
    int id = 0;
    int left = 0;

    while (id < moneys[i].size()) {
      while (id < moneys[i].size() && (isdigit(moneys[i][id]) || moneys[i][id] == '.')) { // 获取数字
        id++;
      }
      // id 非数字， C
      int curNum = stoi(moneys[i].substr(left, id - left));
      left = id;

      while (id < moneys[i].size() && isalpha(moneys[i][id])) { // 获取单位字符串
        id++;
      }
      // id 非字母， 5
      string unit = moneys[i].substr(left, id - left);
      sum += curNum * getV(unit); // 获取某个单位转换为 分
      left = id;
    }
  }
  cout << int(sum) << endl;

  return 0;
}