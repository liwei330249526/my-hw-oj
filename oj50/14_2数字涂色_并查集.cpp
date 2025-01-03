/*
 * 题目描述
 * 疫情过后，希望小学开学了，要制作黑板报
 * 黑板上已经写了N个正整数，同学们需要给每个数涂色。
 * 为了让黑板报有学习意思，老师要求同种颜色的所有数都可以被这种颜色中最小的那个数整除。
 * 请计算，虽少需要多少中颜色才能给这N个数进行上色.
 *
 *
输入
3
2 4 6

输出
1

说明：
所有数都能被2整除

 *

输入
4
2 3 4 9

输出
2

说明：
2与4涂一种颜色，4能被2整除；

3与9涂另一种颜色，9能被3整除。

不能4个数涂同一个颜色，因为3与9不能被2整除。所以最少的颜色是两种

 * */


#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"
using namespace std;

// 实现并查集

class UnionFind {
public:
    UnionFind(int n) { // 元素个数
      // 初始化并查集
      parent.resize(n); // 元素个数
      rank.resize(n); // range 个数
      for (int i = 0; i < parent.size(); i++) {
        parent[i] = i; // 初始化每个节点的父节点为自己，每个是一个单独集合
      }
      return;
    }

    // 查找root
    int find(int x) {
      if (parent[x] == x) { // 找到了 root
        return x;
      }
      int root = find(parent[x]);  // 找父节点的 root
      parent[x] = root;
      return root;
    }

    // 合并, 分别找xroot 和 yroot，比较rank，哪个rank大，则哪个作为root, 合并的是root
    void unit(int x, int y) {
      int rootX = find(x);
      int rootY = find(y);

      if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
          parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
          parent[rootX] = rootY;
        } else {
          parent[rootY] = rootX;
          rank[rootX]++; // 原来秩相等，现在让rootX 作为root， 则rootX 的秩++;
        }
      }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

vector<int> getPrimeFactors(int num) {
  vector<int> res;
  for (int i = 2; i <= num; i++) {
    for (;num % i == 0;) {
      res.push_back(i);
      num = num / i;
    }
  }
  return res;
}

void mPrint(vector<int> arr) {
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;
  return;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // 并查集
  UnionFind uf(101);
  // 获取一个数所有的质因子, 将该数与所有质因子join

  vector<int> res;
  for (int i = 0; i < arr.size(); i++) {
    res = getPrimeFactors(arr[i]);

    for (int j = 0; j < res.size(); j++) {
      uf.unit(arr[i], res[j]);  // 将每个数字 num 和它所有的因子 join 起来
    }
  }

  // 求有几个集合
  unordered_map<int, int> mem;
  for (int i = 0; i < arr.size(); i++) {
    mem[uf.find(arr[i])]++;
  }

  cout << mem.size() << endl;
  return 0;
}

