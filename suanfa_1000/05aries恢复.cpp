#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// 定义日志记录类型
enum LogType {
    START,
    WRITE,
    COMMIT,
    ABORT
};

// 定义日志记录结构体
struct LogRecord {
    int transactionId;
    LogType type;
    std::string dataItem;
    std::string oldValue;
    std::string newValue;

    LogRecord(int id, LogType t) : transactionId(id), type(t) {}
    LogRecord(int id, LogType t, const std::string& item, const std::string& oldVal, const std::string& newVal)
            : transactionId(id), type(t), dataItem(item), oldValue(oldVal), newValue(newVal) {}
};

// 定义数据库类
class Database {
private:
    std::vector<LogRecord> logs;
    std::unordered_map<int, bool> transactionStatus; // true: commit, false: abort
    std::unordered_map<std::string, std::string> data;  // key value
    int checkpointIndex;

    // 重做操作
    void redo(const LogRecord& record) { // 重做，如果是write， 则执行重做，将 newValue 写入data
      if (record.type == WRITE) {
        data[record.dataItem] = record.newValue;
        std::cout << "Redo: Set " << record.dataItem << " to " << record.newValue << std::endl;
      }
    }

    // 回滚操作
    void undo(const LogRecord& record) { // 回滚，如果是write， 将oldValue 写入data
      if (record.type == WRITE) {
        data[record.dataItem] = record.oldValue;
        std::cout << "Undo: Set " << record.dataItem << " to " << record.oldValue << std::endl;
        // 写入补偿日志
        logs.emplace_back(record.transactionId, LogType::ABORT, record.dataItem, record.newValue, record.oldValue);
      }
    }

public:
    Database() : checkpointIndex(-1) {}

    // 开始事务
    void startTransaction(int transactionId) { // 开始事务，写入start 日志
      logs.emplace_back(transactionId, START);
      std::cout << "Transaction " << transactionId << " started." << std::endl;
    }

    // 写操作
    void write(int transactionId, const std::string& dataItem, const std::string& oldValue, const std::string& newValue) {
      logs.emplace_back(transactionId, WRITE, dataItem, oldValue, newValue);
      std::cout << "Transaction " << transactionId << " wrote " << dataItem << " from " << oldValue << " to " << newValue << std::endl;
      // 数据脏页可刷盘，这里简化处理
      data[dataItem] = newValue;
    }

    // 提交事务
    void commitTransaction(int transactionId) { // 提交事务，写commit 日志， 设置事务为commit
      logs.emplace_back(transactionId, COMMIT);
      transactionStatus[transactionId] = true;
      std::cout << "Transaction " << transactionId << " committed." << std::endl;
    }

    // 中止事务
    void abortTransaction(int transactionId) {
      for (auto it = logs.rbegin(); it != logs.rend(); ++it) {
        if (it->transactionId == transactionId && it->type == WRITE) {
          undo(*it);
        }
      }
      logs.emplace_back(transactionId, ABORT);
      transactionStatus[transactionId] = false;
      std::cout << "Transaction " << transactionId << " aborted." << std::endl;
    }

    // 设置检查点
    void setCheckpoint() { // 设置检查点
      checkpointIndex = logs.size() - 1;
      std::cout << "Checkpoint set at log index " << checkpointIndex << std::endl;
    }

    // 恢复过程
    void recover() {
      std::unordered_map<int, bool> redoTransactions;
      std::unordered_map<int, bool> undoTransactions;

      // 分析阶段
      for (const auto& record : logs) { // 遍历所有log
        if (record.type == START) {
          if (std::find_if(logs.begin(), logs.end(), [&](const LogRecord& r) { // 如果事务有start 且有 commit 或 abort
              return r.transactionId == record.transactionId && (r.type == COMMIT || r.type == ABORT);
          }) != logs.end()) {
            redoTransactions[record.transactionId] = true; // 则标记为redo
          } else {
            undoTransactions[record.transactionId] = true; // 否则标记为undo
          }
        }
      }

      // 重做阶段
      for (const auto& record : logs) { // 遍历所有redo 日志， 执行redo
        if (redoTransactions.count(record.transactionId) > 0) {
          redo(record);
        }
      }

      // 回滚阶段
      for (auto it = logs.rbegin(); it != logs.rend(); ++it) { // 遍历所有回滚日志，执行回滚
        if (undoTransactions.count(it->transactionId) > 0) {
          undo(*it);
        }
      }

      // 写入回滚完成日志
      for (const auto& pair : undoTransactions) { // 执行完回滚后，加入abort 日志
        logs.emplace_back(pair.first, ABORT);
        std::cout << "Transaction " << pair.first << " fully aborted during recovery." << std::endl;
      }
    }
};

int main() {
  Database db;

  // 模拟事务执行
  db.startTransaction(1);
  db.write(1, "X", "oldX", "newX");
  db.commitTransaction(1);

  db.startTransaction(2);
  db.write(2, "Y", "oldY", "newY");
  // 模拟故障，事务 2 未提交
  // db.commitTransaction(2);

  db.setCheckpoint();

  // 进行恢复
  db.recover();

  return 0;
}