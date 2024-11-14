/*
 * 现在有一堆小朋友，他们高矮不同，我们以正整数数组表示这一对小朋友的身高，如数组{5,3,1,2,3}.
 * 我们现在希望小朋友排队，以"高" "矮" "高" "矮" 顺序排列，每一个高位置的小朋友要比乡里你的位置高或者相等；每个矮位置的小朋友
 * 要比相邻的位置矮或者相等；
 * 要求下朋友们移动的距离和最小，第一个从高位开始排，输出最小移动距离即可。
 * 例如，在师范小队{5,3,1,2,3} 中 {5,1,3,2,3} 是排序结果
 * {5,2,3,1,3} 虽然也满足"高" "矮" "高" "矮" 顺序排列，但小朋友们的移动距离大， 所以不是最优结果。
 * 移动距离的定义如下所示：
 * 第二位下朋友移到第三位小朋友后面， 移动距离为1，若移动到第四位小朋友后面，移动距离为2；
 *


 样例1
 输入
4 1 3 5 2


输出
4 1 5 2 3

说明：
无



样例2
 输入
1 1 1 1 1




输出
1 1 1 1 1

说明：
相邻位置可以相等


 样例3
输入
xxx


输出
[]

说明：
出现非法参数情况， 返回空数组。

 *
 *
 * */

#include "string"
#include "iostream"

#include "sstream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  vector<int> arr;
  string token;
  stringstream stm(str);

  try {
    while (getline(stm, token, ' ')) {
      arr.push_back(stoi(token));
    }

    // 高矮高矮
    for (int i = 0; i < arr.size(); i++) {
      if (i % 2 == 0) {
        if (i < arr.size()-1 && arr[i] < arr[i+1]) {
          swap(arr[i], arr[i+1]);
        }
      } else {
        if (i < arr.size()-1 && arr[i] > arr[i+1]) {
          swap(arr[i], arr[i+1]);
        }
      }
    }

    for (int i = 0; i < arr.size(); i++) {
      cout << arr[i];
      if (i != arr.size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  } catch (const exception &e) {
    cout << "[]" << endl;
  }


  return 0;
}