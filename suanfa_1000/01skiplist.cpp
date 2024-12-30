#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stdint.h"
#include "vector"
using namespace std;

const int MAX_LEVEL = 4; // 跳表的最大层数

/*
 *   节点有pre指针，和next指针， 跳表节点有有pre 指针数组， next指针数组
 *  next[5]      [0]
 *                  [1]
 *                  [2]
 *                  [3]
 *                  [4]
 *                  [5]
 *
 *  [->][->] node
 * */

//new 操作符在 C++ 中用于动态分配内存。在这里，new Node*[4] 的操作是在堆上动态分配了一个包含 4 个元素的数组，
//数组中的每个元素都是 Node 类型的指针（即 Node*）。
//
//然后将这个动态分配的数组的首地址赋值给 next，也就是让 next 指向了这个新分配的指针数组。
//这意味着可以通过 next 来访问这个数组中的每个指针元素，进一步通过这些指针元素去操作它们
//所指向的 Node 结构体实例（比如进行赋值、调用结构体中的成员函数等操作，前提是 Node 结构体有相应的成员和功能定义）。

struct Node { // 节点
    int key;  // key
    Node** next; // 指向下一个节点的指针数组

    Node(int k, int lvl) : key(k) { // 节点构造
      next = new Node*[lvl]; // 有3层
      for (int i = 0; i < lvl; ++i) { // 遍历数组每个 next 指针，赋值为null
        next[i] = nullptr;
      }
    }

    ~Node() { // 析构，delete 数组
      delete[] next;
    }
};

class SkipList {  // 跳表
private:
    Node* header; // 跳表的头节点，不存储实际数据
    int level; // 当前跳表的层数  例如2层， 则[0,1]

    // 随机生成层数
    int randomLevel() {
      int lvl = 1;
      while (rand() < RAND_MAX / 2 && lvl < MAX_LEVEL) { // 循环，如果随机数在小于最大值一半，概率上应为 0.5; 则层数+1； 直到不满足条件
        ++lvl;                                            // 所以层数为1， 概率0.5; 层数为2， 概率为0.25； 层数为3， 概率为0.125; 一次类推。
      }
      return lvl;
    }

public:
    SkipList() {
      srand(time(nullptr)); // 初始化随机数生成器
      header = new Node(INT32_MIN, MAX_LEVEL); // 头节点，key设为最小整数； 头节点; 头节点 高度为 4
      level = 0; // 层数初始化为0  当前跳表层数为0
    }

    ~SkipList() { // 析构
      // 这里应该实现一个递归或迭代的方法来删除所有节点，但为简化起见，省略了
      // 从跳表的头节点开始，调用递归函数释放所有节点
      deleteNodesRecursive(header);
    }

    // 递归释放节点的辅助函数，从给定节点开始释放其后续所有节点（包括不同层的关联节点）
    void deleteNodesRecursive(Node* node) { // 直接递归第0层，析构每个 Node， 由于Node 实现了析构，直接调用 delete node 即可
      if (node == nullptr) {
        return;
      }
      // 先递归释放下一层（next[0]指向的节点）的所有节点
      deleteNodesRecursive(node->next[0]);
      // 释放当前节点的指针数组内存（因为是动态分配的）
      // 释放当前节点本身内存
      delete node;
    }

/*
 *
 * 3                10            18
 * 3  next[1]       10            18
 * 3  next[0]  7    10     11     18
 *
 * */
    // 查找节点
    /*
     * 1 从最高层开始遍历
     * 2 找到第 0 层的小于key 的最后一个节点 x
     * 3 判断 x.next 是否等于key
     * 4 如果等于key，则找到了key
     * 5 如果不等于key，则跳表中没有 key。
     * */

    // 获取最高层 index
    int getMaxLevelId() {
      return level-1;
    }

    Node* search(int key) {
      Node* current = header; // 获取头
      for (int i = getMaxLevelId(); i >= 0; --i) {  // 从最高层开始遍历
        while (current->next[i] != nullptr && current->next[i]->key < key) {
          current = current->next[i]; // 加入找11， 这里current 最后为， 小于11的最后一个节点，集找到第next[0] 中的10节点
        }
      }
      current = current->next[0]; // 最后一层比较实际key值
      if (current != nullptr && current->key == key) { // 判断10.next 的11 是否为要查找的数字， 如果是则返回11节点
        return current;
      }
      return nullptr;
    }

    // 插入节点
/*
 *
 * 3  next[2]       10            18
 * 3  next[1]       10            18
 * 3  next[0]  7    10     11     18
 *
 * */
    /*
     *
     * 1 从最高层开始遍历
     * 2 找到每一层小于 key 的最后一个节点x
     * 3 2中每层的节点x 加入到结合中 update
     * 4 判断第0层的 x.next 是否等于key
     * 5 如果等于key，则已经存在key，则不加入。
     * 6 如果不等于key，继续执行，插入key。
     * 7 获取一个随机层，randHeight
     * 8 如果 randHeight 大于目前跳表层高，则update 集合中 i = level; i < lvl 位置加入 header 节点， 并更新level值
     * 9 update 结合中节点后续插入 key 的节点
     * */
    void insert(int key) {
//      Node* update[MAX_LEVEL + 1]; // 记录需要更新的节点
      vector<Node*> update(MAX_LEVEL, nullptr);
      Node* current = header; // 头

      // 找到每一层需要更新的节点
      for (int i = getMaxLevelId(); i >= 0; --i) { // 从最高层开始遍历每一层  [4]
        while (current->next[i] != nullptr && current->next[i]->key < key) {
          current = current->next[i]; // 加入插入10， 找到小于10 的最后一个节点，即找到找到 next[2] 的3节点， next[1] 的3节点，nex[0] 的 7 节点
        }
        update[i] = current; // 加入集合， 每层应该插入的位置
      }

      current = current->next[0]; // 最后一层比较实际key值

      // 如果key已存在，则不插入新节点（或可以选择更新值）
      if (current != nullptr && current->key == key) { // 如果存在， 则不加入
        return;
      }

      // 创建新节点并设置其forward指针
      int lvl = randomLevel(); // 获取一个随机层， 这里假如获取层高为原来是 3, [0,1,2],  变为现在是5, [0,1,2,3,4]
      if (lvl > level) {  // 如果层高大于现有层高， 则将头结点header 就加入到update 集合
        for (int i = level; i < lvl; ++i) { // 包括level， 不包括 lvl
          update[i] = header;
        }
        level = lvl; // 更新层高
      }

      Node* newNode = new Node(key, level);  // 新建节点， 则有新的层高， 新的层高代表有新的 next 数组
      for (int i = 0; i <= getMaxLevelId(); i++) {    // 遍历每层，将newNode 加入到链表； 先设置newNode-> 后续节点
        newNode->next[i] = update[i]->next[i];   // 再再设置 newNode前面的指针，  ->newNode
        update[i]->next[i] = newNode;
      }
    }

    // 删除节点（简化版，不处理多层删除后的层数减少）
    /*
     * 1 从最高层开始遍历
     * 2 找到每一层 小于 key 的最后一个节点 x， 加入结合update， 并找到要删除的节点 toDelete
     * 3 遍历update， 判断每个x 的next 如果是 toDelete节点，则删除 toDelete节点
     * 4 从最高层开始遍历，尝试减少跳表层数
     *
     * */
    bool deleteNode(int key) {
//      Node* update[MAX_LEVEL];
      vector<Node*> update(MAX_LEVEL, nullptr);
      Node* current = header;
      Node* toDelete = nullptr;

      // 找到每一层需要更新的节点和要删除的节点
      for (int i = getMaxLevelId(); i >= 0; --i) {
        while (current->next[i] != nullptr && current->next[i]->key < key) { // 小于 key 的最后一个节点 x
          current = current->next[i];
        }
        update[i] = current;
        if (current->next[i] != nullptr && current->next[i]->key == key) { // 判断 x 是否为key，如果是则加入结合 toDelete
          toDelete = current->next[i];
        }
      }

      if (toDelete == nullptr) {
        return false; // 未找到要删除的节点
      }

      // 从每一层中删除节点
      for (int i = 0; i <= getMaxLevelId(); i++) {
        if (update[i]->next[i] != toDelete) {
          break; // 提前退出，因为后面的层不会有该节点
        }
        update[i]->next[i] = toDelete->next[i];
      }

      // 尝试减少层数（这里为了简化省略了）
      // ...
      for (int i = getMaxLevelId(); i >= 0; i--) {
        if (header->next[i] == nullptr) {
          level--;
        }
      }

      delete toDelete;
      return true;
    }

    // 打印跳表（用于调试）
    void print() {
      Node* current = header->next[0];
      while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->next[0];
      }
      std::cout << std::endl;
    }
};

int main() {
  SkipList skipList;
  skipList.insert(3);
  skipList.insert(3);
  skipList.insert(6);
  skipList.insert(7);
  skipList.insert(9);
  skipList.insert(12);
  skipList.insert(19);
  skipList.insert(17);
  skipList.insert(26);
  skipList.insert(21);
  skipList.insert(25);

  skipList.print(); // 打印跳表

  skipList.deleteNode(3);
  skipList.print(); // 打印跳表
  skipList.deleteNode(6);
  skipList.print(); // 打印跳表
  skipList.deleteNode(7);
  skipList.print(); // 打印跳表
  skipList.deleteNode(9);
  skipList.print(); // 打印跳表
  skipList.deleteNode(12);
  skipList.print(); // 打印跳表
  skipList.deleteNode(17);
  skipList.print(); // 打印跳表
  skipList.deleteNode(19);
  skipList.print(); // 打印跳表
  skipList.deleteNode(21);
  skipList.print(); // 打印跳表
  skipList.deleteNode(25);
  skipList.print(); // 打印跳表

  return 0;
}