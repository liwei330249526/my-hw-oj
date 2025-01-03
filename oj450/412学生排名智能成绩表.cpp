/*
 *
题目描述
小明来到学校当老师，需要讲学生按考试总分或单科分数进行排名，你能帮帮他吗？

输入
第1行输入两个整数，学生人数n和科目数量m
第2行输入m个客户名称，彼此之间用空格隔开
第3行开始的n行，每行包含一个学生的姓名和该生的m个科目的成绩

输出一行，按成绩排序后的学生名字，成绩相同按学生姓名字典序排序

样例1
输入
3 2
yuwen shuxue
fangfang 95 90
xiaohua 88 98
minmin 100 82
shuxue

输出
xiaohua fangfang minmin

样例2
输入
3 2
yuwen shuxue
fangfang 95 90
xiaohua 88 95
minmin 90 95
zongfen



输出
fangfang minmin xiaohua


说明:
排序科目不存在，按总分排序，fangfang和minmin总分相同，按姓名的字典序顺序，fangfang 排在前面


students map<string, vector<int>>

subjects , map<string>

rankSubject string

 *
 * */

#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
#include "numeric"
using namespace std;

int main() {
  int n; // 学生人数
  int m; // 科目数
  cin >> n >> m;

  vector<string> subjects;
  string inputSubj;
  for (int i = 0; i < m; i++) {
    cin >> inputSubj;
    subjects.push_back(inputSubj);
  }

  string inputName;
  string inputScore;
  unordered_map<string, vector<int>> students;  // name: 多个分数的数组
  for (int i = 0; i < n; i++) {
    cin >> inputName;
    for (int j = 0; j < m; j++) {
      cin >> inputScore;
      int scoreNum = stoi(inputScore);
      students[inputName].push_back(scoreNum);
    }
  }

  string rankSubj;
  cin >> rankSubj;

  vector<pair<string, vector<int>>> sorted_students(students.begin(), students.end());  // 构造一个 pair 的； string:vecotr<int>;  即一个map的 k：v
  if (find(subjects.begin(), subjects.end(), rankSubj) != subjects.end() ) {  // 存在，则按 rankSubj 科目排序
//  if (subjects (rankSubj) != subjects.end()) {
//    int rankId = subjects.find(rankSubj); // 第几个科目
    int rankId = find(subjects.begin(),subjects.end(), rankSubj) - subjects.begin(); // 找到排序的 subj 的 index

    sort(sorted_students.begin(), sorted_students.end(), [&](pair<string, vector<int>> &p1, pair<string, vector<int>> &p2){
      if (p1.second[rankId] != p2.second[rankId]) {
        return p1.second[rankId] > p2.second[rankId];
      }
      return p1.first < p2.first;
    });

  } else { // 按总和排序
    sort(sorted_students.begin(), sorted_students.end(), [&](pair<string, vector<int>> &p1, pair<string, vector<int>> &p2){
         int sum1 = accumulate(p1.second.begin(), p1.second.end(), 0);
         int sum2 = accumulate(p2.second.begin(), p2.second.end(), 0);
         if (sum1 != sum2) {
           return sum1 > sum2;
         }
         return p1.first < p2.first;
    });
  }

  for (int i = 0; i < sorted_students.size(); i++) {
    cout << sorted_students[i].first;
    if (i != sorted_students.size()-1) {
      cout << " ";
    }
  }
  cout << endl;


  return 0;
}