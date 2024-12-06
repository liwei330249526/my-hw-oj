/*
 *
题目描述
疫情期间需要大家保证一定的社交距离，公司举止开交流会议，一排共N个座位，编号分别为[0，N-1]，需要员工一个接一个进入会议室，并且可以
在任何时候离开会议室。
满足：
每当一个员工进入时，需要做到最大社交距离（最大化自己和他人的距离的座位）；
如果有多个这样的座位，则做到索引最小的那个座位。

输入
会议室座位总数 seatNum
员工进入的顺序 seatOrLeave 数组， 元素值为1，表示进场；元素值为负数，表示出场；

输出
最后来的员工，他坐哪个位置，如果满了，返回-1
 *
 * 样例1
 * 输入
10
[1,1,1,1,-4,1]


输出
5


说明：                                                            [0,1,2,3,4,5,6,7,8,9]
seat -> 0，空在任何位置都行，但是要给他安排索弓|最小的位置，也就是座位0    [x,1,2,3,4,5,6,7,8,9]
seat -> 9,要和旁边的人距离最远，也就是座位9                            [x,1,2,3,4,5,6,7,8,x]
seat -> 4,要和旁边的人距离最远，应该坐到中间，也就是座位4                [x,1,2,3,x,5,6,7,8,x]    可以看出 1 2 3 中插入2位置
seat-> 2,员工最后坐在2号座位上                                       [x,1,x,3,4,5,6,7,8,x]
leave[4], 4号座位的员工离开                                          [x,1,2,3,4,5,6,7,8,x]
seat-> 5,员工最后坐在5号座位上

 *
 * 样例2
 * 输入
10
[1,0,0,0,1,0,0,0,0,1]


输出
8


0 1 2 3 4 5 6 7 8 9
1                 1

 *
 * 思路
 * 找空座数量最多的一个区间，将1设置进去即可
 *
 * */

#include "iostream"
#include "vector"
#include "sstream"
using namespace std;

// 1,0,0,0,1,0,0,0,0,1
int process(int seatNum, vector<int> &seatOrLeave) {
  vector<int> seat(seatNum); // 初始化座位， 都为0
  int targetId = -1;
  for (int i = 0; i < seatOrLeave.size(); i++) {

    int left = -1;
    int right = -1;
    int interval = -1;
    int leftCur = 0;
    int rightCur = 0;
    if (seatOrLeave[i] >= 0) { // 进入一个
      // 遍历 seat， 找到最大的连续 0 的区间, [left, right]
      for(int j = 0; j < seat.size();) {
        if (seat[j] == 0) {
          leftCur = j;
        } else {
          j++;
          continue;
        }

        while (j < seat.size() && seat[j] == 0) {
          rightCur = j; // 符合为0
          j++;
        }
        // j 是最后一个， 或 seat[j] != 0
        int curInterval = (rightCur - leftCur) / 2;
        if (rightCur == seat.size()-1) {
          curInterval = rightCur - leftCur;
        }
        if(interval < curInterval) { // 0 组成的空间， 例如 0 1 2 3,  3个0组成了2个空间
          interval = curInterval; // 记录最小interval
          left = leftCur;            // 记录最小interval 的左右
          right = rightCur;
        }
      }

      if (left != -1) {
        if (left == 0) {
          targetId = 0;
        } else if (right == seat.size()-1) {
          targetId = seat.size()-1;
        } else {
          targetId = (left + right) / 2;
        }
//      cout << "add " << targetId << endl;

        seat[targetId] = 1;
      } else {
        targetId = -1;
      }


    } else if (seatOrLeave[i] < 0) { // 离开
//      cout << "del " << -seatOrLeave[i] << endl;
      seat[-seatOrLeave[i]] = 0;
    }
  }

  return targetId;
}

int main() {
  string str;
  // 获取座位数
  int seatNum;
  cin >> seatNum;
  cin >> str;
  string strB = str.substr(1, str.size()-2);

//  cout << seatNum << endl;
//  cout << strB << endl;

  // 获取打卡次序
  stringstream stm(strB);
  string token;
  vector<int> seatOrLeave;
  while (getline(stm, token, ',')) {
    seatOrLeave.push_back(stoi(token));
  }

  int ret = process(seatNum, seatOrLeave);
  cout << ret << endl;

  return 0;
}