/*
 * 题目描述
 * 特定大小的停车场，数组cars[] 表示，其中1表示有车，0表示没车
 * 车辆大小不一，小车占1个车位，火车占2个车位，卡车站3个车位
 * 统计停车场最少听多少辆车，返回夹具体数目
 *
输入
1,0,1


输出
2

说明:
1个小车占第1个车位，第二个车位空，1个小车占第3个车位，最少有两辆车


输入
1,1,0,0,1,1,1,0,1


输出
3

说明:
1个货车占第1、2个车位，第3、4个车位空，1个卡车占第5、6、7个车位
第8个车位空，1个小车占第9个车位，最少3辆车

 * */

#include "vector"
#include "iostream"
#include "sstream"
using namespace std;
int main() {
//  vector<char> a(1000);
//  cout << sizeof(a) << endl; // 为什么是24
//  cout << a.size() << endl;
  string str;
  getline(cin, str);

  stringstream str_stream(str);
  vector<int> arr;
  string token;
  while(getline(str_stream, token, ',')) {
    arr.push_back(stoi(token));
  }

  int count = 0;
  for (int i = 0; i < arr.size();) {
    if (arr[i] == 1) { // 如果是1， 则肯定要放一个车子
      if ((i+1 < arr.size() && arr[i+1] == 1) && (i+2 < arr.size() && arr[i+2] == 1)) { // 如果有3个1
        count += 1;
        i+=3;
      } else if (i+1 < arr.size() && arr[i+1] == 1) { // 如果有2个1
        count += 1;
        i += 2;
      } else { // 只有1个1
        count += 1;
        i += 1;
      }
    } else { // 0 不放车子
      i+=1;
    }
  }

  cout << count << endl;
  return 0;
}