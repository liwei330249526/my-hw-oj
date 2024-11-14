/*
 *
题目描述
磁盘的容量单位常用的有M, G, T 这三个等级，他们之间的换算关系为 1T=1024G， 1G=1024M，现在给定n块磁盘的容量，请对他们按从小到大的顺序进行稳定排序，例如给定5块的容量，1T， 20M， 3G，106T，3M12G9M，排序后的结果为：20M, 2G, 2M12G8M, 1T, 10G6T.
注意单位可以重复出现，上述3M12G8M 表示的容量为 3M+12G+9M，和 12M12G相等。

输入输出
输入
第一行包含一个整数，表示磁盘的个数，接下来n行，每行一个字符串，表示磁盘的容量。
输出
输出n行，表示n块磁输出n行，表示n块磁盘容量的排序后的结果。
 *
 * 样例1
输入
3
1G
2G
1024M



输出
1G
1024M
2G

说明：
1G和1024M容量相等，稳定排序要求保留它们原来的相对位置，故1G在1024M之前。

 * 样例2
输入
3
2G4M
3M2G
1T


输出
3M2G
2G4M
1T

说明：1T的容量大于2G4M，2G4M的容量大于3M2G.


 *
 * 样例3
 *
 *
 * 样例4
 *
 *
 *
 * */

#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
using namespace std;
typedef struct Disk_t {
    string str;
    int size;
}Disk;

int getMuti(char c) {
  if (c == 'M') {
    return 1;
  } else if (c == 'G') {
    return 1024;
  } else if (c == 'T') {
    return 1024 * 1024;
  } else {
    return 0;
  }
}

int convertStr2Size(string str) {
  int ret = 0;
  int left = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == 'M' || str[i] == 'G' || str[i] == 'T') {
      ret += stoi(str.substr(left, i - left)) * getMuti(str[i]);
      left = i+1;
    }
  }

  return ret;
}

int main() {
  int n;
  cin >> n;
  cin.ignore();

  vector<Disk> disks(n);

  for (int i = 0; i < n; i++) {
    cin >> disks[i].str;
    disks[i].size = convertStr2Size(disks[i].str);
  }

  sort(disks.begin(), disks.end(), [](Disk &d1, Disk &d2) {
    return d1.size < d2.size;
  });

  for (int i = 0; i < n; i++) {
    cout << disks[i].str << endl;
  }

  return 0;
}