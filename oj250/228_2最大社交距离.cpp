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

//[x,1,2,3,x,5,6,7,8,x]
// 处理一下上面的场景，我们知道, 1 2 3 有3个空位，  5 6 7 8 有4个空位，那么插入哪个位置呢？
// 如果插入位置2， 则离2最近的人距离是2； 如果插入位置6， 则离6位置最近的位置是2； 但位置2的index较小，所以插入位置2；
// 那么怎么保证呢， 我们计算出了 1 2 3 有3个空位， 即 numZero = 3； 1 2 3 前后的人距离是多少呢？ distance = 4; 我要插入的的话肯定要插入中间位置，
// 那么中间位置与最近的人距离为多少呢？  4 / 2 = 2, 所以插入位置2((1+3)/2)， 与最近的人距离为2；

// 再考虑位置6， 5 6 7 8 共4个空位， 即 numZero = 4， 5 6 7 8 前后的人距离是多少呢？ distance = 5; 我要插入的话肯定要插入中间位置，
// 那么中间位置与最近的人距离为多少呢？ 5 / 2 = 2, 所以插入位置6 ((5+8)/2)， 与最近的人距离 2；
// 既然插入2 和插入 6 效果是一样的，即最近的人距离都为2， 所以应该插入index 较小的2；


// [x,1,2,3,4,x,6,7,8,9]
// 处理一下上面的场景, 我们得到两个空座区间，第一个区间为 1 2 3 4 ， 如果在这个区间插入，很明显应该插入 2 即((1+4)/2)，
// 1 2 3 4， 有4个空位， numZero = 3，  1 2 3 4 前后人的距离是多少呢？  distance = 5; 如果插入的话肯定要插入中间位置， 那么中间位置与最近的人
// 的距离是多少呢？  5/2 =2。 我们插入2位置，很明显和最近的人的距离为2；

// 第二个空座区间为  6 7 8 9, 如果在这个区间插入，很明显应该插入9位置。
// 6 7 8 9 ， 共4个空位， 如果插入9位置，距离是多少呢?  distance = 8 / 2 = 4, 即插入9位置，最近的距离为4，  所以应该插入9位置

// 1,0,0,0,1,0,0,0,0,1
int process(int seatNum, vector<int> &seatOrLeave) {
  vector<int> seat(seatNum); // 初始化座位， 都为0
  int targetId = -1;

  // 遍历进入序列
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
        // 找这段连续的 0 的区间
        while (j < seat.size() && seat[j] == 0) {
          rightCur = j; // 符合为0
          j++;
        }
        // j 是最后一个， 或 seat[j] != 0
        int numZero = rightCur - leftCur + 1;  // 有几个连续的空位 0

        int curInterval = 0;
        if (rightCur == seat.size()-1) { // 如果是最后一个位置位0， 则如果坐在最后一个位置，最近的人的距离是多少？
          curInterval = numZero;
        } else {
          int distance = numZero + 1;  // 这段连续空位0，前后的人的距离是多少
          curInterval = distance / 2;  // 坐在中间位置，则最近的人的距离是多少
        }

        if(interval < curInterval) { // 0 组成的空间， 例如 0 1 2 3,  3个0组成了2个空间
          interval = curInterval; // 记录最小interval
          left = leftCur;            // 记录最小interval 的左右
          right = rightCur;
        }
      }

      if (left != -1) {
        // 找到了符合的位置
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
        // 没有找到符合位置
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