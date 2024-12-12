/*
 *
题目描述
一群大雁往南飞，给定一个字符串记录地面上的有课听到的大雁叫声，请给出叫声最少由几只大雁发出：
具体的：
1 大雁发出的叫声为 "quack" , 因为由多只大雁同一时间嘎嘎作响，所以字符串中可能会混合多个 "quack"
2 大雁会一次完整发出 "quack", 即字符串中 'q', 'u', 'a', 'c', 'k' 这5个字母按顺序完整存在才能计数为一只大雁，如果不完整或没有按顺序则不于计数
3 如果字符串不是由 'q', 'u', 'a', 'c', 'k' 字母组合而成，或者没有找到一只大雁，返回 -1

输入
一个字符串，包含大雁 quack 的叫声， 1 <= 字符串长度 <= 1000, 字符串的字符只有 'q', 'u', 'a', 'c', 'k'
输出
大雁的数量

样例1
输入
quackquack

输出
1

样例2
输入
qaauucqckk

输出
-1

样例3
输入
quacqkuac

输出
1


样例4
输入
qququaauqccauqkkcauqqkcauuqkcaaukccakkck

输出
5


同一时间大雁发出；
同时发生的大雁的数量

q  vector<int> 起始数组
u 个数小于q
a 个数小于u
c 个数小于a
k 个数小于c
找到一个后， pop 第一个 q；  Vector.erase(vector.begin())

即一个大雁的 end 最多包含后续的多少个大雁的start
*
 * */

#include "iostream"
#include "vector"
#include "unordered_map"
using namespace std;

int main() {
  string str;
  cin >> str;

  string dayan = "quack";
  unordered_map<char, int> count; // q u a c k 的字母计数
  vector<pair<int, int>> yells; // 叫声span
  vector<int> yellStarts; // 开始叫声

  for(int i = 0; i < str.size(); i++) {
    if (str[i] == 'q') {
      yellStarts.push_back(i);  // quack 开始数字, 递增的
      count['q']++;
    } else if(str[i] == 'u'){
      if (count['q'] >= count['u']+1) {
        count['u']++;
      }
    } else if (str[i] == 'a') {
      if (count['u'] >= count['a']+1) {
        count['a']++;
      }
    } else if (str[i] == 'c') {
      if (count['a'] >= count['c']+1) {
        count['c']++;
      }
    } else if (str[i] == 'k') {
      if (count['c'] > 0) {
        // 获得一个 quack
        count['q']--;
        count['u']--;
        count['a']--;
        count['c']--;

        yells.push_back({yellStarts.front(), i});
        yellStarts.erase(yellStarts.begin());
      }
    }
  }

  // 选择一个 yell 跨度内， 相交的所有 yell
  if (yells.size() == 0) {
    cout << -1 << endl;
    return 0;
  }
  int ret = 1;
  for(int i = 0; i < yells.size(); i++) {
    int curRet = 1;
    for (int j = i+1; j < yells.size(); j++) {
      if (yells[i].second > yells[j].first) {
        curRet++;
      } else {
        break;
      }
    }
    ret = max(ret, curRet);
  }
  cout << ret << endl;

  return 0;
}