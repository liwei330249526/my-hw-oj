/*
题目描述
主管期望你来实现英文输入法单词联想功能。
需求如下：
依据用户输入的单词前缀，从已输入的英文中联想出用户想输入的单词，按字典序联想到单词序列，如果联想不到，请输出用户输入的单词前缀。
注意：
1 英文单词联想时，区分大小写
2 缩略形式如 "don't" 判定为两个单词， "don" 和 "t"
3 输出的单词序列，不能有重复单词，只能是英文单词，不能有标点符号.
 *
 * 样例1
输入
I love you
He

输出
He

说明：
从用户已输入英文语句"I love you"中提炼出"I"、"love”、 "you" 三个单词,接下来用户输入"He”,从已输入信息中无法联想到任何符合要求的单词，因此输出用户输入的单词前缀。


 *
 * 样例2
输入
The furthest distance in the world, Is not between life and death, But when I stand in front of you, Yet you don't know that I loveyou.
f

输出
front furthest

说明：

从用户已输入英文语句The furthestdistance in the world, Is not between life and death, But when I stand in frontof you, Yet you dont know that 1
love you."中提炼出的单词，符合“f作为前缀的， 有"furthest"和"front", 按字典序排序并在单词间添加空格后输出，结果为"front furthest"。


 *
 * 样例3
输入
Hello world
W

输出
W

 *
 * 样例4
输入
I am a student
s

输出
student

 *
 * */


#include "string"
#include "vector"
#include "sstream"
#include "iostream"
#include "unordered_map"
#include "shared_mutex"
#include "memory"
#include "deque"
#include "algorithm"
using namespace std;

// 节点
class PreTreeNode {
public:
    // 构造，析构
    PreTreeNode(){}
    ~PreTreeNode() {
    }
    unordered_map<char, shared_ptr<PreTreeNode>> dict;
    bool isEnd;
    string word;
};

// 前缀树
class PreTree {
public:
    PreTree(){
      root = make_shared<PreTreeNode>();
    }
    ~PreTree(){
    }

    void insert(string word) {
      PreTreeNode *node = root.get();
      for (char c : word) {
        if(node->dict.find(c) == node->dict.end()) {
          node->dict[c] = make_shared<PreTreeNode>();
        }
        node = node->dict[c].get();
      }
      node->isEnd = true;
      node->word = word;
    }

    bool search(string word) {
      PreTreeNode *node = root.get();
      for (char c : word) {
        if(node->dict.find(c) == node->dict.end()) {
          return false;
        }
        node = node->dict[c].get();
      }

      return node->isEnd;
    }

    bool startWith(string word) {
      PreTreeNode *node = root.get();
      for (char c : word) {
        if(node->dict.find(c) == node->dict.end()) {
          return false;
        }
        node = node->dict[c].get();
      }

      return true;
    }

    void dfsFindWords(PreTreeNode *node, string prefix) {
      if (node->isEnd) {
        allWords.push_back(prefix);
      }
      for (auto &it : node->dict) {
        dfsFindWords(it.second.get(), prefix+it.first);
      }

      return;
    }

    void bfsFindWords(PreTreeNode *node) {
      deque<PreTreeNode*> que;
      que.push_back(node);

      while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
          // 获取一个节点， 处理
          PreTreeNode* node = que.front();
          que.pop_front();

          if (node->isEnd) {
            allWords.push_back(node->word);
          }

          // node 的子节点加入
          for (auto &it : node->dict) {
            que.push_back(it.second.get());
          }
        }
      }

      return;
    }

    void findWords(string prefix) {
      vector<string> res;
      PreTreeNode *node = root.get();
      for (char c : prefix) {
        if(node->dict.find(c) == node->dict.end()) {
          return;
        }
        node = node->dict[c].get();
      }

      bfsFindWords(node);
      return;
    }

    shared_ptr<PreTreeNode> root;

    vector<string> allWords;
};

int main() {
  string str;
  getline(cin, str);
  string prefix;
  cin >> prefix;
  // 获取所有字符串
  vector<string> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    int left = 0;
    for (int i = 0; i < token.size(); i++) {
      if (!isalpha(token[i])) {
        arr.push_back(token.substr(left, i - left));
        left = i + 1;
      }
    }

    if (left <= token.size()-1) {
      arr.push_back(token.substr(left, token.size() - left));
    }
  }

  PreTree tree;

  for (string word : arr) {
    tree.insert(word);
  }

  tree.findWords(prefix);

  if (tree.allWords.empty()) {
    cout << prefix << endl;
  } else {

    sort(tree.allWords.begin(), tree.allWords.end());

    for (int i = 0; i < tree.allWords.size(); i++) {
      cout << tree.allWords[i];
      if (i != tree.allWords.size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  }

  return 0;
}