/*
 *
题目描述
公司某部门软件教导团正在组织新员工每日打卡活动，他们开展这项学习活动已经一个月，统计下这个月的优秀打卡员工。每个员工一个id，每天
打卡记录记录打卡员工的集合，一共30天。

请你实现代码帮助统计打卡次数top5的员工。加入打卡次数相同，将较早打卡的员工排在前面，如果开始参与打卡时间也一样，将id较小的员工排在前面。

注：不考虑丙类的情况，按规则返回前5名员工id即可，如果当月打卡员工少于5个，按顺序返回所有打卡记录员工id。

输入
第一行输入为新员工数量N，表示新员工编号0 - N-1
第二行输入30个整数，表示每天打卡的员工数量，每天至少有xx名员工打卡。
之后30行为每天打卡的员工id集合，id不重复

输出
按顺序㤕打卡的top5员工id，空格隔开

 *
 * 样例1
 * 输入
11
4 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2
0 1 7 10
0 1 6 10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
6 10
7 10


输出
10 0 1 7 6

说明：
员工编号范围为0~10，id为10的员工连续打卡30天，排第一, id为0,1,6,7的员工打卡都是两天, id为0,1,7的员工在第一天就打卡， 比id为6的员工早,排在前面，0,1,7按id升序排列， 所以输出[10,0,1,7,6]



 *
 * 样例2
 * 输入
7
6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5





输出
0 1 2 3 4

说明：
员工编号范围为0-6，id为0，1, 2, 3, 4，5的员工打卡次数相同，最早开始打卡的时间也一样，所以按id升序返回前5个id


 *
 * 样例3
 * 输入
2
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
0 1
0 1



输出
1 0

说明：
只有两名员工参与打卡，按规则排序输出两名员工的id


 *
 *

{
 int times;
 int start;
 int no;
 }

 {

 }

 *
 * */


#include "iostream"
#include "vector"
#include "unordered_map"
#include "algorithm"
using namespace std;
typedef struct Employee_t{
  int times;
  int start;
  int no;
}Employee;


int main() {
  int n;  // 员工人数
  vector<int> amountDayClock(30); // 每天打卡人数
  cin >> n;
  vector<Employee> employees(n);
  for (int i = 0; i < employees.size(); i++) {
    employees[i].start = -1; // 未设置首次打卡
    employees[i].no = i;
  }

  for (int i = 0; i < 30; i++) {
    cin >> amountDayClock[i];
  }

//  vector<vector<int>> numberDayClock(30);
  int empNum;
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < amountDayClock[i]; j++) {
      cin >> empNum; // 打卡员工编号
      employees[empNum].times++;
      if (employees[empNum].start == -1) {
        employees[empNum].start = i; // 设置首次打卡
      }
    }
  }


  sort(employees.begin(), employees.end(), [&](Employee &e1, Employee &e2){
    if (e1.times != e2.times) {
      return e1.times > e2.times;
    }
    if (e1.start != e2.start) {
      return e1.start < e2.start;
    }

    return e1.no < e2.no;
  });

  for (int i = 0; i < 5 && i < employees.size(); i++) {
    cout << employees[i].no << " ";
  }
  cout << endl;
  return 0;
}