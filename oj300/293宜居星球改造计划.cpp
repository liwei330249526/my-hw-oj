/*
 *
2xxx 年， 人类通过对火星的大气尽心宜居改造分析，使得火星已在理论上具备人类宜居的条件；
由于技术原因，无法一次性将火星大气全部改造，只能通过局部处理形式；
假设将火星待改造的区域 row* column 的网格，每个网格有3个值，宜居区、可改造区、死亡区，使用 YES NO NA 代替， YES表示
该网格已经完成大气改造, NO 表示该网格未进行改造，后期进行改造，NA表示死亡区，不作为判断是否改造完的一起，无法穿过；初始化下，
该区域可能存在多个宜居区，并且每个一曲曲能同时在每个太阳日单位向上下左右4个方向的相邻各自进行扩散，自动将4个方向相邻的可改造区改为宜居区；
请计算这个待改造的区域的网格中，可改造区是否能全部成宜居区，如果可以，返回改造的太阳日天数，不可以则返回-1

输入
输入 row * column 个网格数据，每个网格枚举值如下： YES, NO, NA
输出
可改造区是否能全部变为宜居区，如果可以，则返回天数，否则返回-1；

样例1
输入
YES YES NO
NO NO NO
YES NO NO

输出
2

说明：
经过两个太阳日，完成改造


样例2
输入
YES NO NO NO
NO NO NO NO
NO NO NO NO
NO NO NO NO

输出
6

说明：
经过6个太阳日，完成改造


样例3
输入
NO NA

输出
-1

说明：
无改造初始条件，无法进行改造


样例4
输入
YES NO NO YES
NO NO YES NO
NO YES NA NA
YES NO NA NO

输出
-1

说明：
-1 ,右下角的区域，被周边三个死亡区挡住，无法实现改造

 *
 * */

#include "sstream"
#include "iostream"
#include "string"
#include "vector"
using namespace std;
int main() {
  vector<string> strArr;
  string inStr;
  int cols = 0;
  while (getline(cin, inStr)) {
    strArr.push_back(inStr);
    cols++;
//    if(cols == 4) {
//      break;
//    }
  }

//  for (int i = 0; i < strArr.size(); i++) {
//    cout << strArr[i] << endl;
//  }

  vector<vector<int>> gd(strArr.size());
  vector<vector<int>> que;
  int NoNum = 0;
  for (int i = 0; i < strArr.size(); i++) {
    string token;
    stringstream stm(strArr[i]);
    int jid = 0;
    while (getline(stm, token, ' ')) {
      if (token == "YES") { // 所有宜居
        gd[i].push_back(0);
        que.push_back({i,jid}); // 宜居区域
      } else if (token == "NO") { // 所有可改造
        NoNum++;
        gd[i].push_back(1);
      } else if (token == "NA") {
        gd[i].push_back(2);
      }

      jid++;
    }
  }

  if (NoNum == 0) {
    cout << 0 << endl;
    return 0;
  }

  if (que.empty()) {
    cout << -1 << endl;
    return 0;
  }

  int step = 0;
  vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  // que 中是所有 0
  while (!que.empty()) {
    int size = que.size();
    step++;
    for (int i = 0; i < size; i++) {
      vector<int> pos = que.front(); // 宜居区， 取一个
      que.erase(que.begin());

      for (int j = 0; j < dirs.size(); j++) { // 4 个方向扩散， 可改造区
        int nx = pos[0] + dirs[j][0];
        int ny = pos[1] + dirs[j][1];
        if (nx >= 0 && nx< gd.size() &&
            ny >= 0 && ny < gd[0].size() &&
            gd[nx][ny] == 1) {
          //
          que.push_back({nx, ny});  // 加入宜居区队列
          gd[nx][ny] = 0; // 设置宜居
        }
      }
    }
  }

  for (int i = 0; i < gd.size(); i++) {  // 如果还有可改造，则不行
    for (int j = 0; j < gd[0].size(); j++) {
      if (gd[i][j] == 1) { // 如果还升序no op
        cout << -1 << endl;
        return 0;
      }
    }
  }

  cout << step-1 << endl;
  return 0;
}

