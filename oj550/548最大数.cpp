/*
 *
题目描述
给定一组非负整数 nums, 重新排列每个数的顺序，使之组成一个最大的整数。
注意： 输出的结果可能非常大，所以你需要返回一个字符串而不是整数。

样例1
输入：nums = [10,2]
输出："210"

样例2
输入：nums = [3,30,34,5,9]
输出："9534330"

 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
class Solution {
public:
    string largestNumber(vector<int>& nums) {
      sort(nums.begin(), nums.end(), [](int a, int b){
        return to_string(a) + to_string(b) > to_string(b) + to_string(a); // a + b 较大
      });

      for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
      }
      cout << endl;
      return "";
    }
};

int main() {
  Solution st;
  vector<int> arr1{10,2};
  vector<int> arr2{3,30,34,5,9};
  st.largestNumber(arr1);
  st.largestNumber(arr2);
  return 0 ;
}