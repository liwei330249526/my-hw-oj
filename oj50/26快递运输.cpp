/*
 * 快递放在大小不等的长方体盒子中，为了能装在更多的快递，且同时不能让货车超载，计算最多能装多少个快递
 * 不考虑体积
 *
 * 输入
 * 第一行输入每个快递的重量
 * 第二行输入火车的载重量
 *
 * 输出
 * 最多能装多少个快递
 *
输入
5,10,2,11
20

输出
3


思路，装最多快递，则优先装最小的快递， 排序。
 * */

#include "string"
#include "iostream"
#include "vector"
#include "algorithm"
#include "sstream"
using namespace std;

int main() {
  string str;
  getline(cin, str);
  int tol;
  cin >> tol;
  string token;
  vector<int> nums;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    nums.push_back(stoi(token));
  }

  sort(nums.begin(), nums.end());

  int count = 0;
  int sum = 0;
  int maxC = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (sum + nums[i] <= tol) {
      sum += nums[i];
      maxC++;
    } else {
      break;
    }
//    sum += nums[i];
//    if (sum <= tol) {
//      maxC++;
//    } else {
//      break;
//    }
  }
  cout << maxC << endl;
  return 0;
}