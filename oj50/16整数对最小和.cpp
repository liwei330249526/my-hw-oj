/*
 * 给定两个整数数组 array1 array2 ，数组元素按升序排列
 * 假设从array1  array2 中分别取出一个元素可构成一对元素，现在需要取出k对元素，
 * 并对取出的所有元素求和，计算和的最小值
 *
输入
3 1 1 2
3 1 2 3
2


输出
4


说明：

用例中，需要取2对元素

取第一个数组第0个元素与第二个数组第0个元素组成1对元素[1,1];

取第一个数组第1个元素与第二个数组第0个元素组成1对元素[1,1];

求和为1+1+1+1=4，为满足要求的最小和。

 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  int count1;
  cin >> count1;
  vector<int> arr1(count1);
  for (int i = 0; i < count1; i++) {
    cin >> arr1[i];
  }

  int count2;
  cin >> count2;
  vector<int> arr2(count2);
  for (int i = 0; i < count2; i++) {
    cin >> arr2[i];
  }

  int sum_count;
  cin >> sum_count;

  vector<int> sum_arr;
  for (int i = 0; i < count1; i++) {
    for (int j = 0; j < count2; j++) {
      sum_arr.push_back(arr1[i] + arr2[j]);
    }
  }

  sort(sum_arr.begin(), sum_arr.end());

  int ans = 0;
  for (int i = 0; i < sum_count; i++) {
    ans += sum_arr[i];
  }

  cout << ans << endl;

  return 0;
}