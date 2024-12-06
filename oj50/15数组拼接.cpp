/*
 * 题目描述
 * 现在有多组整数数组，需要将他们合并成一个新的数组
 * 合并规则，从每个数组里按顺序取出固定长度的内容合并到新的数组中，取完后的内容会删掉，如果该行不足固定长度或者为空，
 * 则直接取出剩余部分内容放到新的数组中，继续下一行。
 *
 *

输入
3
2
2,5,6,7,9,5,7
1,7,4,3,4


输出
2,5,6,1,7,4,7,9,5,3,4,7

 * */

#include "string"
#include "iostream"
#include "vector"
#include "sstream"
#include "deque"
using namespace std;

string getStr(vector<vector<int>> &arrs, int width) {
  string ans;
  int id = 0; // 字符串起始索引
  bool hasF = false;
  while (true) {
    // 遍历所有行
    hasF = false;
    for (int i = 0; i < arrs.size(); i++) {
      if (id >= arrs[i].size()) { // 如果起始索引大于某个字符串长度，则忽略
        continue;
      }

      for (int j = 0; j < width && id+j < arrs[i].size(); j++) {
        ans += to_string(arrs[i][id+j]);
        hasF = true;  // 该次遍历， 有数据处理
      }
    }
    id += width;
    if (!hasF) { // 如果一次遍历，没有数据处理，说明arrs 中没有数据了
      break;
    }
  }

  return ans;
}

int main() {
  // 每次取的数字个数
  int width;
  cin >> width;

  // 几行数据
  int m;
  cin >> m;
  cin.ignore();  // cin 忽略
  vector<vector<int>> arrs(m); // 2 维数组
  for (int i = 0; i < m; i++) {
    string str;
    getline(cin, str); // 获取一行字符串

    // 分隔字符串，将字符数字 转为int
    stringstream stm(str); // string 流
    string token;
    while(getline(stm, token, ',')) {  // 以 , 作为分隔，获取所有数字字符； 并转换为数字
      int numToken = stoi(token);
      arrs[i].push_back(numToken);
    }
  }

  // 多行
  vector<int> ans;
  vector<string> ansStr;

  string rets = getStr(arrs, width);
  for (int i = 0; i < rets.size(); i++) {
    cout << rets[i];
    if (i != rets.size()-1) {
      cout << ",";
    }
  }
  cout << endl;

//
//  while (!arrs.empty()) { // 如果2为数组不为空
//    for (auto it = arrs.begin(); it != arrs.end();) { // 遍历2为数组
//
//      for (int j = 0; j < width; j++) { // 获取 width 个数字
//        if (it->empty()) { // it 代表一维数组的指针
//          break;
//        }
//        ans.push_back(it->front());  // 假如结果集
//        ansStr.push_back(to_string(it->front()));
//        it->erase(it->begin());      // 一维数组左边 erase 一个元素
//      }
//
//      if(it->empty()) { // 如果符合，则删除vector 中的 it
//        it = arrs.erase(it);  // 获取删除后的 it
//      } else {
//        it++;                 // it 递进
//      }
//    }
//  }
//
//  // arrs 为空了， 则数字都取完了
//
//  for (int i = 0; i < ans.size(); i++) {
//    cout << ans[i];
//    if (i != ans.size()-1) {
//      cout << ",";
//    }
//  }
//  cout << endl;
  return 0;
}