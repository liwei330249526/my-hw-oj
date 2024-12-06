/*
 *
题目描述
某块业务芯片最小容量单位为1.25G，总容量为M*1.25G, 对该芯片资源编号为 1,2,...M; 该芯片支持3中不同的配置，分别为A,B,C
配置A： 占用容量为1.25*1 = 1.25G
配置B： 占用容量为1.25*2 = 2.5G
配置C： 占用容量为1.25*8 = 10G
某块办卡上集成了N块上述芯片，对芯片编号为1,2,... N, 各个芯片之间彼此独立，不能夸芯片占用资源
给定办卡上芯片数量N，每块芯片容量为M，用户按次序配置后，请输出芯片资源占用情况，保证小号的芯片数量最少.
资源分配规则：按照芯片编号从小到大分配所需资源，芯片上资源如果被占用标记为1，没有被占用标记为0
用户配置序列：用户配置是按次序配置到芯片中，如果用户配置序列中某个配置超过了芯片总容量，丢弃该配置，继续遍历用户后续配置。

输入
M：每块芯片容量为M * 1.25G, 取值范围为： 1-256
N：每块板卡包含芯片数量，取值范围为1-32
用户配置序列：例如 ACABA, 长度不超过1000
输出
板卡上每块芯片的占用情况

 *
 * 样例1
 * 输入
8
2
ACABA

输出
1111100
1111111

说明：

用户第1个配置A:占用第1块芯片第1个资源，芯片占用情况为:
10000000
00000000

用户第2个配置C:第1块芯片剩余8.75G,配置C容量不够，只能占用第2块芯片，芯片占用情况为:
1000000
1111111

用户第3个配置A:第1块芯片剩余8.75G,还能继续配置，占用第1块芯片第2个资源，芯片占用情况为:
1100000
1111111

用户第4个配置B:第1块芯片剩余7.5G,还能继续配置，占用第1块芯片第3、4个资源，芯片占用情况为: .
11110000
1111111

用户第5个配置A:第1块芯片剩余5G,还能继续配置，占用第1块芯片第5个资源，芯片占用情况为:
1111100
1111111

 *
 *
 * */

#include "iostream"
#include "vector"
#include "string"
using namespace std;
int main() {
  int M;
  int N;
  string config;
  cin >> M >> N >> config;

  vector<vector<int>> mem(N, vector<int>(M)); // N 个芯片的 M个资源占用情况，初始为0
  vector<int> cap(N, M); // 初始每块芯片的初始剩余容量为M   // 10 5 , 10-5, 从第6个开始， 即[5] 开始
  for (char c : config) { // 遍历每个配置
    int choiceIndex = -1;  // 选择一个芯片
    int startIndex = -1;  // 从芯片的这个位置的资源开始使用
    int count = -1; // 用多少个资源
    for (int j = 0; j < N; j++) { // 遍历每个芯片
      if (c == 'A') {
        // 1
        if (1 <= cap[j]) {
          startIndex = M - cap[j];
          count = 1;
          choiceIndex = j;
          break;
        }
      } else if (c == 'B') {
        // 2
        if (2 <= cap[j]) {
          startIndex = M - cap[j];
          count = 2;
          choiceIndex = j;
          break;
        }
      } else if (c == 'C') {
        // 8
        if (8 <= cap[j]) {
          startIndex = M - cap[j];
          count = 8;
          choiceIndex = j;
          break;
        }
      }
    }

    if (choiceIndex != -1) { // 找到了
      for (int k = 0; k < count; k++) { // 设置choiceIndex芯片的从startIndex位置开始的count个资源
        mem[choiceIndex][startIndex+k] = 1;
      }
      cap[choiceIndex] -= count; // 重新计算choiceIndex芯片的剩余资源数量
    }
  }

  for (int i = 0; i < mem.size(); i++) {
    for (int j = 0; j < mem[0].size(); j++) {
      cout << mem[i][j];
    }
    cout << endl;
  }

  return 0;
}