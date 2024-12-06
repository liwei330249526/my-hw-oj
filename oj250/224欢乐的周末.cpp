/*
 *
小华和小为是很要的朋友，他们约定周末一起吃饭
通过手机交流，他们在地图上选择了多个聚餐地点（由于自然地形等原因，部分聚餐地点不可达），求小华和小微能到达的聚餐地点有多少个？

输入
第一行输入m和n，m代表地图的长度，n代表地图的宽度
0为通常的道路
1为障碍物（且仅为障碍物）
2为小华或小为，地图中必定有且仅有2个
3为被选中聚餐地点

输出
可以被两房都到达的聚餐地点数量
 *
 *
 * 样例1
 * 输入
4 4
2 1 0 3
0 1 2 1
0 3 0 0
0 0 0 0


输出
2

说明：
第一行输入地图的长宽为3和4，第二行开始为具体的地图，
其中: 3代表小华和小明选择的聚餐地点; 2代表小华或者小明(确保有2个) ; 0代表可以通行的位置; 1代表不可以通行的位置，此时两者能都能到达的聚餐位置有2处

 *
 *
 * 样例2
 * 输入
4 4
2 1 2 3
0 1 0 0
0 1 0 0
0 1 0 0

输出
0

说明：
第一行输入地图的长宽为4和4，第二行开始为具体的地图，其中: 3代表小华和小明选择的聚餐地点; 2代表小华或者小明(确保有2个) ; 0代表可以通行的位置; 1代表不可以通行的位置

由于图中小华和小为之间有个阻隔，此时，没有两人都能到达的聚餐地址，故而返回0
 *
 *
 * 思路
 * 1 找到xiaohua ， xiaoming 的位置
 * 2 对两个点进行dfs
 * 3 设置xiaohua 和 小明的 Visted 矩阵
 * 4 如果某个点事餐厅，且xiaohua 和xiaoming 都访问过，则计数
 *
 * */

#include "iostream"
#include "vector"
using namespace std;

void dfs(vector<vector<int>> &gd, int row, int col, vector<vector<int>> &visited) {
  // check
  if (!(row >= 0 && row < gd.size() &&
      col >= 0 && col < gd[0].size())) {
    return;
  }
  if (visited[row][col] == 1 || gd[row][col] == 1) {
    return;
  }

  // set
  visited[row][col] = 1;

  // 4 dirs
  vector<vector<int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};
  for (int i = 0; i < dirs.size(); i++) {
    int dx = dirs[i][0];
    int dy = dirs[i][1];
    dfs(gd, row + dx, col + dy, visited);
  }
}

int main() {
  int rows;
  int cols;
  cin >> rows >> cols;
  vector<vector<int>> gd(rows, vector<int>(cols));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> gd[i][j];
    }
  }

  // 获取小华和小为的坐标
  pair<int, int> p1(-1,-1);
  pair<int, int> p2(-1,-1);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (gd[i][j] == 2) {
        if (p1.first == -1) {
          p1.first = i;
          p1.second = j;
        } else {
          p2.first = i;
          p2.second = j;
        }
      }
    }
  }

  vector<vector<int>> visited1(rows, vector<int>(cols));
  vector<vector<int>> visited2(rows, vector<int>(cols));
  dfs(gd, p1.first, p1.second, visited1);
  dfs(gd, p2.first, p2.second, visited2);

//  cout << "visited1" << endl;
//  for (int i = 0; i < rows; i++) {
//    for (int j = 0; j < cols; j++) {
//      cout << visited1[i][j] << " ";
//    }
//    cout << endl;
//  }
//  cout << "visited2" << endl;
//  for (int i = 0; i < rows; i++) {
//    for (int j = 0; j < cols; j++) {
//      cout << visited2[i][j] << " ";
//    }
//    cout << endl;
//  }

  int ret = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (gd[i][j] == 3 && visited1[i][j] == 1 && visited2[i][j] == 1) {
        ret++;
      }
    }
  }

  cout << ret << endl;
  return 0;
}