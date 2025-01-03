/*
 *
题目描述
定义构造三叉搜索树规则如下：
每个节点都存有一个数，当插入一个新的数时，从根节点向下寻找，直到找到一个合适的空节点插入

查找规则是：
1 如果数小于节点的数减去500， 则将数插入节点的左子树。
2 如果数大于节点的数加上500， 则将数插入节点的右字数。
3 否则，将数插入节点的中子数。
给你一系列数，清按以上规则，按顺序将数插入树中，构建出一颗三叉搜索树，最后输出树的高度。

输入
第一行为一个数N，表示有N个数
第二行为N个空格分隔的整数，每个数的范围为[1,10000]

输出
输出树的高度（根节点的高度为1）

样例1
输入
5
5000 2000 5000 8000 1800

输出
3

样例2
输入
3
5000 4000 3000

输出
3


样例3
输入
9
5000 2000 5000 8000 1800 7500 4500 1400 8100


输出
4



 *
 * */


#include "iostream"
#include "vector"
using namespace std;


class Node {
public:
    Node(int val){
      this->val = val;
    }

    Node *left = nullptr;
    Node *mid = nullptr;
    Node *right = nullptr;
    int val;
};


// node 为 根 节点， 将val 插入到三叉树中；
Node* buildTree(Node *node, int val) {
  if (node == nullptr) { // 新减节点， 并返回
    Node *ret;
    ret = new Node(val);
    return ret;
  }

  if (val < node->val - 500) { // val 应该放在左子树上
    node->left = buildTree(node->left, val);
  } else if (val > node->val + 500) { // val应该放在右子树上
    node->right = buildTree(node->right, val);
  } else { // val 应该放在中树上
    node->mid = buildTree(node->mid, val);
  }
  return node;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // 构建三叉树
  Node *root = nullptr;
  for (int i = 0; i < arr.size(); i++) {
    root = buildTree(root, arr[i]);
  }

  // 求树高

  auto dfs = [&](auto &&dfs, Node *node) -> int{
    if (node == nullptr) {
      return 0;
    }

    int left = dfs(dfs, node->left);
    int mid = dfs(dfs, node->mid);
    int right = dfs(dfs, node->right);

    int ret = left;       // 最大的一个
    ret = max(ret, mid);
    ret = max(ret, right);

    return ret + 1; // 返回
  };

  int ret = dfs(dfs, root);

  cout << ret << endl;

  return 0;
}