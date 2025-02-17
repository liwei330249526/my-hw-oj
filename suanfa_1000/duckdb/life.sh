#!/bin/bash

# 错误日志文件
ERROR_LOG="error.log"

# 读取配置文件
read_config() {
    # 全局变量：在脚本的任何位置定义的变量，脚本内的所有函数都能访问它
    IP=$(grep '^ip=' config.cfg | cut -d'=' -f2) # 读文件，以 ip 开头的行， 以 = 分隔，选取第个字段
    if [ -z "$IP" ]; then
      echo "未在 config.cfg 文件中找到 ip 配置。"
      exit 1
    fi

    PORT=$(grep '^port=' config.cfg | cut -d'=' -f2)
    if [ -z "$PORT" ]; then
      echo "未在 config.cfg 文件中找到 port 配置"
      exit 1
    fi

    TABLE_CONFIGS=$(grep '^schema.tables=' config.cfg | cut -d'=' -f2-) # 选取第二个字段开始到行尾的所有字段
    SCHEMAS_REG_CONFIGS=$(grep '^schemas_reg=' config.cfg | cut -d'=' -f2-)
    SCHEMAS_CONFIGS=$(grep '^schemas=' config.cfg | cut -d'=' -f2-)
}

# 解析生命周期配置
parse_lifecycle() {
   # 局部变量：在函数内部用 local 关键字定义的变量，只能在该函数内部访问。
    local config="$1"
    local IFS=','  # 函数内部的 IFS 变量设定为逗号  ;  <<< 操作符的作用是把一个字符串直接作为标准输入提供给命令; ${config%=*} 是参数扩展操作，它会删除 config 字符串中从等号开始到字符串末尾的部分，从而得到等号左边包含表名的部分。
    read -ra parts <<< "${config%=*}"  # 读取一行， 根据 IFS 的值对这行内容进行分割； -r 选项的作用是防止反斜杠 \ 被当作转义字符处理; -a 选项表示把分割后的结果存储到数组中
    local lifecycle="${config##*=}"  # ${config##*=} 是另一种参数扩展操作，它会删除 config 字符串中从开头到最后一个等号的部分，从而得到等号右边的生命周期信息，例如 10s。
    for part in "${parts[@]}"; do  # 遍历存储表名的数组 parts
          part=$(echo $part | tr -d '[] ')  # 使用 tr 命令删除表名中的方括号和空格

          echo "$part=$lifecycle"
    done
}

test() {
  echo "$TABLE_CONFIGS"
}

# 构建表的生命周期策略
build_lifecycle_strategy() {
  #local 关键字用于声明一个局部变量
  #-A 选项表示声明的是一个关联数组（也叫哈希表或字典）
    local -A strategy
    # 解析配置1

    if [ -n "$TABLE_CONFIGS" ]; then
        while IFS= read -r line; do
            table=$(echo $line | cut -d'=' -f1)
            lifecycle=$(echo $line | cut -d'=' -f2)
            strategy["$table"]="$lifecycle"  # 表名和生命周期存入map
        done < <(parse_lifecycle "$TABLE_CONFIGS")
    fi
#    # 解析配置2
#    if [ -n "$SCHEMAS_REG_CONFIGS" ]; then
#        while IFS= read -r line; do
#            table_reg=$(echo $line | cut -d'=' -f1)
#            lifecycle=$(echo $line | cut -d'=' -f2)
#            for table in $(duckdb -c "SHOW TABLES LIKE '$table_reg'" | tail -n +3 | head -n -2); do  # 根据通配符查询所有表名
#                if [ -z "${strategy[$table]}" ]; then  # 如果不存在配置， 则设置配置
#                    strategy["$table"]="$lifecycle"
#                fi
#            done
#        done < <(parse_lifecycle "$SCHEMAS_REG_CONFIGS")
#    fi
#    # 解析配置3
#    if [ -n "$SCHEMAS_CONFIGS" ]; then
#        while IFS= read -r line; do
#            schema=$(echo $line | cut -d'=' -f1)
#            lifecycle=$(echo $line | cut -d'=' -f2)
#            for table in $(duckdb -c "SHOW TABLES FROM $schema" | tail -n +3 | head -n -2); do  # 根据schema 查询所有表名
#                full_table="$schema.$table"
#                if [ -z "${strategy[$full_table]}" ]; then # 如果不存在配置，则设置配置
#                    strategy["$full_table"]="$lifecycle"
#                fi
#            done
#        done < <(parse_lifecycle "$SCHEMAS_CONFIGS")
#    fi
#    for table in "${!strategy[@]}"; do  # 打印所有策略
#        echo "$table=${strategy[$table]}"
#    done
}

# 删除过期数据
delete_expired_data() {
    local strategy="$1"
    while IFS= read -r line; do
        table=$(echo $line | cut -d'=' -f1)
        lifecycle=$(echo $line | cut -d'=' -f2)
        first_column=$(duckdb -c "PRAGMA table_info($table)" | awk 'NR==3 {print $1}')
        sql="DELETE FROM $table WHERE $first_column < CURRENT_TIMESTAMP - INTERVAL '$lifecycle';"
        duckdb -c "$sql"
    done <<< "$strategy"
}

#SELECT column_name
#  FROM information_schema.columns
#  WHERE table_schema = 'main'
#    AND table_name = 'students'
#  ORDER BY ordinal_position ASC
#  LIMIT 1;

# 主函数
main() {
    read_config
    build_lifecycle_strategy
#    test
#    strategy=$(build_lifecycle_strategy)
#    echo $strategy
#    delete_expired_data "$strategy"
}

main