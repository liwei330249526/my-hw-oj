/*
 * 题目描述
 * 给定一个数组，里面有6个整数，求这个数组能够表示的最大24进制的时间是多少，输出这个时间，无法表示则输出 invalid
 *
输入
0 2 3 0 5 6


输出
23:56:00


 0 2 4 0 0 0

 * */

#include "vector"
#include "iostream"
#include "algorithm"
using namespace std;

string formStr(int v) {
  if (v < 10) {
    return "0" + to_string(v);
  } else {
    return to_string(v);
  }
}

int time1() {
  // 6 个数字
  vector<int> nums(6);
  for (int i = 0; i < 6; i++) {
    cin >> nums[i];
  }

  // 所有排列
  vector<vector<int>> all_nums;
  do {
    all_nums.push_back(nums);
  } while(next_permutation(nums.begin(), nums.end()));

  // 处理所有排列
  string ans;
  for (int i = 0; i < all_nums.size(); i++) {
    vector<int> &nms = all_nums[i];
    int hour = nms[0] * 10 + nms[1];
    int minute = nms[2] * 10 + nms[3];
    int sec = nms[4] * 10 + nms[5];

    // 校验合法
    if (hour <= 23 && minute <= 59 && sec <= 59) {
      string strt = formStr(hour) + ":" + formStr(minute) + ":" + formStr(sec);
      if (ans.size() == 0) {
        ans = strt;
      } else if (ans < strt) {
        ans = strt;
      }
    }
  }

  if (ans.size() == 0) {
    cout << "invalid" << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}

int time2() {
  // 6 个数字
  vector<int> nums(6);
  for (int i = 0; i < 6; i++) {
    cin >> nums[i];
  }

  sort(nums.begin(), nums.end());
  vector<int> res(nums.size());

  for (int i = 0; i < res.size(); i++) {
    int cur = -1;
    int chekId = -1;
    for (int j = 0; j < nums.size(); j++) {
      if (nums[j] == -1) {
        continue;
      }
      if (cur < nums[j]) {
        if (i == 0 && nums[j] >= 0 && nums[j] <= 2) {
          cur = nums[j];
          chekId = j; // 最大的一个
        } else if (i == 1 && res[0] <= 1 && nums[j] >= 0 && nums[j] <= 9) {
          cur = nums[j];
          chekId = j;
        } else if (i == 1 && res[0] == 2 && nums[j] >= 0 && nums[j] <= 3) {
          cur = nums[j];
          chekId = j;
        } else if (i == 2 && nums[j] >= 0 && nums[j] <= 5) {
          cur = nums[j];
          chekId = j;
        } else if (i == 3 && nums[j] >= 0 && nums[j] <= 9) {
          cur = nums[j];
          chekId = j;
        } else if (i == 4 && nums[j] >= 0 && nums[j] <= 5) {
          cur = nums[j];
          chekId = j;
        } else if (i == 5 && nums[j] >= 0 && nums[j] <= 9) {
          cur = nums[j];
          chekId = j;
        }
      }
    }
    if (cur != -1) { // 找到一个 i 位置，最最大且符合的值，值的索引是 checkId
      res[i] = nums[chekId];
      nums[chekId] = -1;
    }
  }

  return 0;
}

//输入
//0 2 3 0 5 6
//
//
//输出
//23:56:00

int main() {
  return time2();
}