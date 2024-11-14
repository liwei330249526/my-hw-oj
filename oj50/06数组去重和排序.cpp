/*
 * 题目描述
 * 给定一个乱序数组，删除所有的重复的元素，使得每个元素只出现一次，并且按照出现的次数从高到低排序，相同出现次数按照第一次出现
 * 顺序进行先后排序
 *

输入
1,3,3,3,2,4,4,4,5


输出
3,4,1,2,5


说明:
数组大小不超过100 数组元素值大小不超过100。


 * */
#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "unordered_map"
#include "algorithm"
using namespace std;
int main() {
  // 读取一行字符串
  string str;
  getline(cin, str);

  // 以逗号分隔，获取整数数组
  stringstream strm(str);
  string token;
  vector<int> nums;
  while(getline(strm, token, ',')) {
    nums.push_back(stoi(token));
  }

//  for (int num : nums) {
//    cout << num << endl;
//  }

  // 数字计数， 用map
  unordered_map<int, pair<int, int>> cal_m;
  for (int i = 0; i < nums.size(); i++) {
    int num = nums[i];
    if (cal_m.find(num) != cal_m.end()) { // 存在
      cal_m[num].first = cal_m[num].first + 1;
    } else {
      cal_m[num] = make_pair(1, i);
    }
  }

  // 提取 key
  vector<int> key_arr;
  for (auto it : cal_m) {
    key_arr.push_back(it.first);
  }

  // sort 排序
  sort(key_arr.begin(), key_arr.end(), [&](int a, int b) ->bool  {
    if (cal_m[a].first != cal_m[b].first) { // 计数，大的在前面
      return cal_m[a].first > cal_m[b].first;
    }

    return cal_m[a].second < cal_m[b].second; // 索引， 小的在前面
  });

  for (int i = 0; i < key_arr.size(); i++) {
    cout << key_arr[i];
    if (i != key_arr.size()-1) {
      cout << ",";
    }
  }
  cout << endl;
  return 0;
}