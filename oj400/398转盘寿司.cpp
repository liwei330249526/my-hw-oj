/*
 *
题目描述
寿司店周年庆，正在举办优惠活动回馈老客户
寿司转盘上共有n 盘寿司，prices[i] 是第i盘寿司的价格，如果客户选择了低i盘寿司，寿司店免费送给客户距离第i盘寿司最忌你的下一盘寿司j，
前提是prices[j] < prices[i], 如果没有满足条件的j，则不赠送寿司
每个价格的寿司都是无线供应

输入
输入的每个数字代表每盘寿司的价格，每盘寿司的价格之间使用空格分隔
输出
输出享受优惠后的一组数据，每个值表示客户选择第i盘寿司时实际得到的寿司总价格

样例1
输入
3 15 6 14

3 15 6 14 3 15 6 14
   2 4 4     6
3
3 15
3 15 6 --  3 6
3 6 14
3 6 14 3 -- 3 3
3 3 15
3 3 15 6 -- 3 3 6
3 3 6 14


输出
3 21 9 17


说明
- 第1盘寿司的价格是3，没有比它价格更低的寿司，所以总价格就是它自己的价格，即3
- 第2盘寿司的价格是15，离它最近的价格更低的寿司是第3盘（价格6），所以总价格是15+6=21
- 第3盘寿司的价格是6，离它最近的价格更低的寿司是第1盘（价格3），所以总价格是6+3=9
- 第4盘寿司的价格是14，离它最近的价格更低的寿司是第1盘（价格3），所以总价格就是14+3=17

样例2
输入
3 10 5 7

输出
3 15 8 10

 *
 *
 * */

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
using namespace std;
vector<int> test1(vector<int> &arr) {
  vector<int> ret(arr.size());
  int arr_len = arr.size();
  for (int i = 0; i < arr.size(); i++) { // 遍历每个寿司， i， 计算该寿司
    int findFreeId = -1;
    for (int j = i+1; j < i + arr_len; j++) { // 从第 i+1 个寿司开始找第一个小于 arr[i] 的寿司 j
       int jid = j % arr_len;
       if (arr[jid] < arr[i]) {
         findFreeId = jid;
         break;
       }
    }
    ret[i] = arr[i];
    if (findFreeId != -1) { // 找到了
      ret[i] += arr[findFreeId];
    }
  }

  return ret;
}


// 右边较小值，单调递增栈
vector<int> test2(vector<int> &arr) {
  int arr_len = arr.size();
  vector<int> ret(arr_len);

  vector<int> st;
  vector<int> rightMin(arr_len, -1);
  for (int i = 0; i < arr_len * 2; i++) {
    int id = i % arr_len;
    while (!st.empty() && arr[st.back()] > arr[id]) { // 如果新值较小, 栈顶指向的值较大
      rightMin[st.back()] = id;
      st.pop_back();
    }
    st.push_back(id);
  }

  for(int i = 0; i < arr_len; i++) {
    ret[i] = arr[i];
    if (rightMin[i] != -1) {
      ret[i] += arr[rightMin[i]];
    }
  }
  return ret;
}

int main() {
  string str;
  getline(cin,str);
  string token;
  vector<int> arr;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  vector<int> ret = test2(arr);
  for (int i = 0; i < ret.size(); i++) {
    cout << ret[i];
    if (i != ret.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}