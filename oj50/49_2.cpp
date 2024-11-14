#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// 选取3个元素组成最小数字
int getMinNumber(vector<int>& nums) {
  sort(nums.begin(), nums.end()); // 对数组进行排序
  vector<int> permutation(nums.begin(), nums.begin() + min(3, (int)nums.size())); // 取前三个元素的全排列
  int minNumber = INT32_MAX;
  do {
    string str;
    for (int i = 0; i < permutation.size(); i++) {
      str += to_string(permutation[i]); // 将排列转换为字符串
    }
    int number = stoi(str); // 将字符串转换为整数
    minNumber = min(minNumber, number); // 更新最小数字
  } while (next_permutation(permutation.begin(), permutation.end())); // 获取下一个排列
  return minNumber;
}

int main() {
  string str;
  cin >> str; // 输入字符串
  vector<int> nums;
  size_t pos = 0;
  string token;
  while ((pos = str.find(",")) != string::npos) { // 将字符串按逗号分割成数字
    token = str.substr(0, pos);
    nums.push_back(stoi(token));
    str.erase(0, pos + 1);
  }
  nums.push_back(stoi(str));
  int minNumber = getMinNumber(nums); // 获取最小数字
  cout << minNumber << endl; // 输出最小数字
  return 0;
}


