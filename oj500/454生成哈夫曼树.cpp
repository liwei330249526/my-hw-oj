/*
 *
题目描述
给定长度为n的无序数字数组，每个数字代表二叉树的叶子节点权值，数字数组的值均大于等于1；请完成一个函数，根据输入的数字数组，生成哈夫曼树，
并将哈夫曼树按照终须遍历输出。
为了保证输出的二叉树终须遍历结果同意，增加以下限制：二叉树节点中，左节点权值小于右节点权值，根节点权值俄日左右节点权值之和。当左右节点权值相同时，
左子树高度小于等于右子树高度。

样例1
输入
5
5 15 40 30 10


输出
40 100 30 60 15 30 5 15 10

 *
 *
 * */

#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"
using namespace std;

// todo: 必记, 段错误， 首先找指针有没有赋值为 nullptr；
class Node {
public:
    Node(int val){
      this->val = val;
      this->left = nullptr;
      this->right = nullptr;
    }

    Node *left;
    Node *right;
    int val;
};


struct Mcompare {
//public:
    bool operator()(Node *node1, Node *node2){
      if (node1->val != node2->val) {
        return node1->val > node2->val;   // 子节点  ---- 父节点；  父节节点 权值更小
      }

      int h1 = getHeight(node1);
      int h2 = getHeight(node2);

      return h1 > h2;        // 子节点  ---- 父节点；  父节节点 深度小
    }

    int getHeight(Node *node) {
      if (node == nullptr) {
        return 0;
      }

      int left = getHeight(node->left);
      int right = getHeight(node->right);
      return max(left, right) + 1;
    }
};


Node *buildTree(priority_queue<Node*, vector<Node*>, Mcompare>  &que) {
  while (que.size() > 1) {
    Node *left = que.top();  // 建树时，先pop left， 再pop right； 所以left 在 right 前面；
    que.pop();               // 所以 que 的排序规则是， left 在堆顶，left 的特征是，  left 权值小， left 深度低

    Node *right = que.top();
    que.pop();

    Node *root = new Node(left->val + right->val);
    root->left = left;
    root->right = right;
    que.push(root);
  }
  // 最后结束时， que 中只有一个节点，集root节点

  return que.top();
}

void freeTree(Node *node) {
  if (node == nullptr) {
    return;
  }
  freeTree(node->left);
  freeTree(node->right);

  delete node;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // 建立哈夫曼树
  // arr 的权值按 做小顶堆；  pop 最小权值节点， push 进去 合成节点
  priority_queue<Node*, vector<Node*>, Mcompare> que;
  for(int i = 0; i < arr.size(); i++) {
    que.push(new Node(arr[i]));
  }

  Node *root = buildTree(que);


  // dfs， 终须遍历哈夫曼树
  vector<int> ret;
  auto dfs = [&](auto &&dfs, Node *node) {
    if (node == nullptr) {
      return;
    }

    dfs(dfs, node->left);
    ret.push_back(node->val);
    dfs(dfs, node->right);
    return;
  };

  dfs(dfs, root);

  for (int i = 0; i < ret.size(); i++) {
    cout << ret[i];
    if(i != ret.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  freeTree(root);

  return 0;
}










