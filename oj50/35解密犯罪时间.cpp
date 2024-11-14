/*
 * 题目描述
 * 警察在侦破一个案件时，得到了线人给出的可能犯罪时间，形如 "HH:MM"表示时刻。
 * 根据警察和线人的约定，为了隐蔽，该时间是修改过的。
 * 解密规则为：利用当前出现过的数字，构造下一个距离当前时间最近的时刻，则该时间为可能得犯罪时间。
 * 每个出现数字都可以被无限次使用。
 *
 * 备注：
 * 1 可以保证线人给的字符串一定是合法的。
 * 2 最近的时刻可能在第二天。
 *
20:12得到20:20

23:59得到22:22

12:58得到15:11

18:52得到18:55

23:52得到23:53

09:17得到09:19

07:08得到08:00

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<int> arr;
  for (int i = 0; i < str.size(); i++) {
    if (!isdigit(str[i])) {
      continue;
    }
    arr.push_back(stoi(str.substr(i,1)));
  }

  vector<int> sArr;
  for (int i = 0; i < arr.size(); i++) {
    sArr.push_back(arr[i]);
  }

  sort(sArr.begin(), sArr.end());  // 排序数字
  int i;
  int j;
  bool findBigger = false;
  bool findAnser = false;
  for (i = arr.size()-1; i >= 0; i--) { // 从第[3] 个数字开始向左遍历
    // 对数字 i 操作， 找比 i 大的第一个 数字
    findBigger = false;
    int num = arr[i];
    for (j = 0; j <sArr.size(); j++) { // 找到第一个大于数字arr[i] 的数字
      if (num < sArr[j]) {
        findBigger = true;
        break;
      }
    }

    if (findBigger) { // 找到了第一个大于 数字arr[i] 的数字
      if (i == 3 && sArr[j] >= 0 && sArr[j] <= 9) { // 如果现在在对[3] 操作，则取值范围是[0-9]
        arr[3] = sArr[j];
        findAnser = true;
      } else if (i == 2 && sArr[j] >= 0 && sArr[j] <= 5) { // 如果现在对[2] 操作，则取值范围是[0,5]
        arr[2] = sArr[j];
        arr[3] = sArr[0];
        findAnser = true;
      } else if (i == 1 && arr[0] <= 1 && sArr[j] >= 0 && sArr[j] <= 9) { // 如果对[1] 操作，如果[0] 不是2，则取值范围是[0-9]
        arr[1] = sArr[j];
        arr[2] = sArr[0];
        arr[3] = sArr[0];
        findAnser = true;
      } else if (i == 1 && arr[0] <= 2 && sArr[j] >= 0 && sArr[j] <= 3 ) { // 如果对[1] 操作，如果[0] 是2，则取值范围是[0-3]
        arr[1] = sArr[j];
        arr[2] = sArr[0];
        arr[3] = sArr[0];
      } else if (i == 0 && sArr[j] >= 0 && sArr[j] <= 2) { // 如果对[0] 操作，则取值范围是 [0-2]
        arr[0] = sArr[j];
        arr[1] = sArr[0];
        arr[2] = sArr[0];
        arr[3] = sArr[0];
        findAnser = true;
      }
    }

    if (findAnser == true) {
      break;
    }
  }

  if (!findAnser) {
    arr[0] = sArr[0];
    arr[1] = sArr[0];
    arr[2] = sArr[0];
    arr[3] = sArr[0];
  }

  cout << arr[0] << arr[1] << ":" << arr[2] << arr[3] << endl;

  return 0;
}