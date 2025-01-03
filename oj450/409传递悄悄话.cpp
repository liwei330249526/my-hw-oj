/*
 *
题目描述
给定一个二叉树，每个节点站着一个人，节点数字表示父节点到该节点传递悄悄话需要花费的时间.
初始时，根节点所在位置的人有一个悄悄话想要传递给其他人，求二叉树所有节点上的人都接收到悄悄话花费的时间。
输入
给定二叉树
输出
返回所有节点都接收到悄悄话花费的时间

样例1
输入
0 9 20 -1 -1 15 7 -1 -1 -1 -1 3 2

输出
38

说明：-1表示空节点


样例2
输入
0 3 2 4 -1 -1 5 1 -1 -1 -1
输出
8

 *
 * */

#include "iostream"
#include "sstream"
#include "string"
#include "vector"
using  namespace std;

// 二叉树节点
class Node {
public:
    Node(int val){
      this->val = val;
    }

    Node *left;
    Node *right;
    int val;
};

Node* buildTree(vector<int> &arr, int rootId) {
  if (rootId >= arr.size() || arr[rootId] == -1) {
    return nullptr;
  }
  Node *root = new Node(arr[rootId]);
  root->left = buildTree(arr, 2 * rootId + 1);
  root->right = buildTree(arr, 2 * rootId + 2);

  return root;
}

void freeTree(Node *root) {
  if (root == nullptr) {
    return;
  }
  freeTree(root->left);
  freeTree(root->right);
  delete root;
}


int main() {
  string str;
  getline(cin, str);
  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }
  Node *root = buildTree(arr, 0);
  // 获取根到叶子节点的最大的时间

  int ret = 0;
  auto dfs = [&](auto &&dfs, Node* node ,int sum){
    if (node == nullptr) { // null
      ret = max(ret, sum);
      return;
    }
//    if (node->left == nullptr && node->right == nullptr) { // 到了叶子节点
//      sum += node->val;
//      ret = max(ret, sum);
//      return;
//    }

    dfs(dfs, node->left, sum + node->val);
    dfs(dfs, node->right, sum + node->val);
  };

  auto dfs2 = [&](auto &&dfs2, Node* node) -> int{
      if (node == nullptr) { // null
        return 0;
      }

      int leftV = dfs2(dfs2, node->left);
      int rightV = dfs2(dfs2, node->right);
      return node->val + max(leftV, rightV);
  };


  ret = dfs2(dfs2, root);

  freeTree(root);

  cout << ret << endl;
  return 0;
}