#include <iostream>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stdint.h"

constexpr int MAX_LEVEL = 32; // 最大32层
constexpr double P_FACTOR = 0.25;

struct SkiplistNode {
    int val; // 值
    vector<SkiplistNode *> forward; // 前向指针
    SkiplistNode(int _val, int _maxLevel = MAX_LEVEL) : val(_val), forward(_maxLevel, nullptr) {

    }
};

class Skiplist {
private:
    SkiplistNode * head;
    int level;
    mt19937 gen{random_device{}()};
    uniform_real_distribution<double> dis;

public:
    Skiplist(): head(new SkiplistNode(-1)), level(0), dis(0, 1) {

    }

    bool search(int target) {
      SkiplistNode *curr = this->head;
      for (int i = level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < target) {
          curr = curr->forward[i];
        }
      }
      curr = curr->forward[0];
      /* 检测当前元素的值是否等于 target */
      if (curr && curr->val == target) {
        return true;
      }
      return false;
    }

    void add(int num) {
      vector<SkiplistNode *> update(MAX_LEVEL, head);
      SkiplistNode *curr = this->head;
      for (int i = level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
          curr = curr->forward[i];
        }
        update[i] = curr;
      }
      int lv = randomLevel();
      level = max(level, lv);
      SkiplistNode *newNode = new SkiplistNode(num, lv);
      for (int i = 0; i < lv; i++) {
        /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
      }
    }

    bool erase(int num) {
      vector<SkiplistNode *> update(MAX_LEVEL, nullptr);
      SkiplistNode *curr = this->head;
      for (int i = level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
          curr = curr->forward[i];
        }
        update[i] = curr;
      }
      curr = curr->forward[0];
      /* 如果值不存在则返回 false */
      if (!curr || curr->val != num) {
        return false;
      }
      for (int i = 0; i < level; i++) {
        if (update[i]->forward[i] != curr) {
          break;
        }
        /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
        update[i]->forward[i] = curr->forward[i];
      }
      delete curr;
      /* 更新当前的 level */
      while (level > 1 && head->forward[level - 1] == nullptr) {
        level--;
      }
      return true;
    }

    int randomLevel() {
      int lv = 1;
      /* 随机生成 lv */
      while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
        lv++;
      }
      return lv;
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
  Skiplist skipList;
  skipList.add(3);
  skipList.add(6);
  skipList.add(7);
  skipList.add(9);
  skipList.add(12);
  skipList.add(19);
  skipList.add(17);
  skipList.add(26);
  skipList.add(21);
  skipList.add(25);

  skipList.print(); // 打印跳表

  skipList.erase(3);
  skipList.print(); // 打印跳表

  return 0;
}
