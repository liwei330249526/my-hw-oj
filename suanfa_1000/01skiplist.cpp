#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stdint.h"

const int MAX_LEVEL = 4; // 跳表的最大层数

/*
 *   节点有pre指针，和next指针， 跳表节点有有pre 指针数组， next指针数组
 *  forward[5]      [0]
 *                  [1]
 *                  [2]
 *                  [3]
 *                  [4]
 *                  [5]
 * */
struct Node { // 节点
    int key;  // key
    Node** forward; // 指向下一层节点的指针数组

    Node(int k, int lvl) : key(k) { // 节点构造
      forward = new Node*[lvl + 1]; // 有4层， 则forward 有 5
      for (int i = 0; i <= lvl; ++i) { // 遍历数组每个，赋值为null
        forward[i] = nullptr;
      }
    }

    ~Node() { // 析构，delete 数组
      delete[] forward;
    }
};

class SkipList {  // 跳表
private:
    Node* header; // 跳表的头节点，不存储实际数据
    int level; // 当前跳表的层数

    // 随机生成层数
    int randomLevel() {
      int lvl = 0;
      while (rand() < RAND_MAX / 2 && lvl < MAX_LEVEL) { // 循环，如果随机数在小于最大值一半，概率上应为 0.5; 则层数+1； 直到不满足条件
        ++lvl;                                            // 所以层数为1， 概率0.5; 层数为2， 概率为0.25； 层数为3， 概率为0.125; 一次类推。
      }
      return lvl;
    }

public:
    SkipList() {
      srand(time(nullptr)); // 初始化随机数生成器
      header = new Node(INT32_MIN, MAX_LEVEL); // 头节点，key设为最小整数； 头节点
      level = 0; // 层数初始化为0
    }

    ~SkipList() {
      // 这里应该实现一个递归或迭代的方法来删除所有节点，但为简化起见，省略了
      delete header;
    }
/*
 *
 * 3                10            18
 * 3  next[1]       10            18
 * 3  next[0]  7    10     11     18
 *
 * */
    // 查找节点
    Node* search(int key) {
      Node* current = header; // 获取头
      for (int i = level; i >= 0; --i) {  // 从最高层开始遍历
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
          current = current->forward[i]; // 加入找11， 这里current 最后为， 小于11的最后一个节点，集找到第next[0] 中的10节点
        }
      }
      current = current->forward[0]; // 最后一层比较实际key值
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
    void insert(int key) {
      Node* update[MAX_LEVEL + 1]; // 记录需要更新的节点
      Node* current = header; // 头

      // 找到每一层需要更新的节点
      for (int i = level; i >= 0; --i) { // 从最高层开始遍历每一层
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
          current = current->forward[i]; // 加入插入10， 找到小于10 的最后一个节点，即找到找到 next[2] 的3节点， next[1] 的3节点，nex[0] 的 7 节点
        }
        update[i] = current; // 加入集合， 每层应该插入的位置
      }

      current = current->forward[0]; // 最后一层比较实际key值

      // 如果key已存在，则不插入新节点（或可以选择更新值）
      if (current != nullptr && current->key == key) { // 如果存在， 则不加入
        return;
      }

      // 创建新节点并设置其forward指针
      int lvl = randomLevel(); // 获取一个随机层， 这里假如获取层高为3
      if (lvl > level) {  // 如果层高大于现有层高， 则将头结点header 就加入到update 集合
        for (int i = level + 1; i <= lvl; ++i) {
          update[i] = header;
        }
        level = lvl; // 更新层高
      }

      Node* newNode = new Node(key, lvl);  // 新建节点， 则有新的层高， 新的层高代表有新的 forward 数组
      for (int i = 0; i <= lvl; ++i) {    // 遍历每层，将newNode 加入到链表； 先设置newNode-> 后续节点
        newNode->forward[i] = update[i]->forward[i];   // 再再设置 newNode前面的指针，  ->newNode
        update[i]->forward[i] = newNode;
      }
    }

    // 删除节点（简化版，不处理多层删除后的层数减少）
    bool deleteNode(int key) {
      Node* update[MAX_LEVEL + 1];
      Node* current = header;
      Node* toDelete = nullptr;

      // 找到每一层需要更新的节点和要删除的节点
      for (int i = level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
          current = current->forward[i];
        }
        update[i] = current;
        if (current->forward[i] != nullptr && current->forward[i]->key == key) {
          toDelete = current->forward[i];
        }
      }

      if (toDelete == nullptr) {
        return false; // 未找到要删除的节点
      }

      // 从每一层中删除节点
      for (int i = 0; i <= level; ++i) {
        if (update[i]->forward[i] != toDelete) {
          break; // 提前退出，因为后面的层不会有该节点
        }
        update[i]->forward[i] = toDelete->forward[i];
      }

      // 尝试减少层数（这里为了简化省略了）
      // ...

      delete toDelete;
      return true;
    }

    // 打印跳表（用于调试）
    void print() {
      Node* current = header->forward[0];
      while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->forward[0];
      }
      std::cout << std::endl;
    }
};

int main() {
  SkipList skipList;
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

  return 0;
}