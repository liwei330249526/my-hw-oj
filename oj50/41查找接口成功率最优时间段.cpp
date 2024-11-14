/*
 * 题目描述
 * 服务之间交换的接口成功率作为服务调用关键质量特性，某个时间段内的接口失败率用一个数组表示，
 * 数组中每个元素都是大内时间内失败率数值，数组中的数值为0-100的整数，
 * 给定一个数值（minAverageLost）表示某个时间段内平均失败率容忍值，几平均失败率小于等于 minAverageLost，
 * 找出数组中最长时间段，如果未找到则直接返回null。
 *
 * 输入
 * 输入两行内容，第1行为 minAverageLost，第2行为数组，数组元素通过空格分隔，
 * minAvergeLost 及数组中元素值范围为0-100的整数，数组元素个数不超过100个。
 * 输出
 * 找出平均值小于等于 minAverageLost 的最长时间段，输出数组小标对
 * 如果同时存在多个最长时间段，则输出多个下标对且下标对之间用空格拼接，多个下表对按下表从小到大排序。
 *
 * 样例1
输入
1
0 1 2 3 4

输出
0-2

输入解释：minAverageLost=1，数组[0, 1, 2, 3, 4]

前3个元素的平均值为1，因此数组第一个至第三个数组下标，即0-2

 *
 * 样例2
输入
2
0 0 100 2 2 99 0 2

输出
0-1 3-4 6-7

输入解释：minAverageLost=2，数组[0, 0, 100, 2, 2, 99, 0, 2]

通过计算小于等于2的最长时间段为：数组下标为0-1即[0, 0]，数组下标为3-4即[2, 2]，数组下标为6-7即[0, 2]，这三个部分都满足平均值小于等2的要求，因此输出0-1 3-4 6-7

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
using namespace std;
int main() {
  string str1;
  getline(cin, str1);

  string str2;
  getline(cin, str2);

  int minAverageLost = stoi(str1);
  vector<int> arr;
  stringstream stm(str2);
  string token;
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  vector<vector<int>> res;
  int resLen = 0;
  int left = 0;
  int sum = 0;
  for (int i = 0; i < arr.size(); ) {
    if ((sum + arr[i])  <= (i - left + 1) * minAverageLost) { // 如果加上数字 arr[i] 后， 符合，则计入 sum
      sum += arr[i];
      i++;
    } else {
      if (i == left) { // 如果i就是left， 且数字 arr[i] 不符合，则更新 left， 和 i
        left = i + 1;
        i++;
        continue;
      }

      // 包括left， 不包括 i
      if (resLen < (i - left)) { // 如果新的范围更大
        resLen = i - left;
        res.clear();
        res.push_back(vector<int>{left, i-1});
      } else if (resLen == (i - left)) { // 如果新的范围和之前最大范围相等
        res.push_back(vector<int>{left, i-1});
      }

      sum = 0; // 更新sum 和 left， i 不变，下次仍然从 i开始计算
      left = i;
    }
  }

  if(left <= arr.size() - 1) { // 如果[left, arr.size()-1] 不是正常区间，则不加入
    if(resLen < arr.size()-1 - left + 1) {
      res.clear();
      res.push_back(vector<int>{left, int(arr.size()-1)});
    } else if (resLen == arr.size()-1 - left + 1) {
      res.push_back(vector<int>{left, int(arr.size()-1)});
    }
  }

  if(!res.empty()) {
    for (int i = 0 ;i < res.size(); i++) {
      cout << res[i][0] << "-" << res[i][1];
      if (i != res.size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  } else {
    cout << "NULL" << endl;
  }



  return 0;
}