cmake_minimum_required(VERSION 3.16)
project(oj)

set(CMAKE_CXX_STANDARD 14)

add_executable(oj main.cpp)

#0-50
add_executable(oj01 oj50/01滑动窗口最大值.cpp)
add_executable(oj02 oj50/02在字符串中找到连续最长的数字串.cpp)
add_executable(oj03 oj50/03路灯照明问题.cpp)
add_executable(oj04 oj50/04字符统计并重排.cpp)
add_executable(oj05 oj50/05TLV解析.cpp)
add_executable(oj06 oj50/06数组去重和排序.cpp)
add_executable(oj07 oj50/07字符串筛选排序.cpp)
add_executable(oj08 oj50/08停车场车辆统计.cpp)
add_executable(oj09 oj50/09绘图机器.cpp)
add_executable(oj10 oj50/10最大时间.cpp)
add_executable(oj11 oj50/11第k个排列.cpp)
add_executable(oj12 oj50/12拼接url.cpp)
add_executable(oj13 oj50/13非严格递增连续数字序列.cpp)
add_executable(oj14 oj50/14数字涂色.cpp)
add_executable(oj14_2 oj50/14_2数字涂色_并查集.cpp)
add_executable(oj15 oj50/15数组拼接.cpp)
add_executable(oj16 oj50/16整数对最小和.cpp)
add_executable(oj17 oj50/17相对开音节.cpp)
add_executable(oj18 oj50/18喊7的次数重排.cpp)
add_executable(oj19 oj50/19勾股数元组.cpp)
add_executable(oj20 oj50/20_火星文计算.cpp)
add_executable(oj20_2 oj50/20火星文计算2.cpp)
add_executable(oj21 oj50/21最远足迹.cpp)
add_executable(oj22 oj50/22字符串序列判定.cpp)
add_executable(oj23 oj50/23按身高体重排序.cpp)
add_executable(oj24 oj50/24找车位.cpp)
add_executable(oj25 oj50/25考勤信息.cpp)
add_executable(oj26 oj50/26快递运输.cpp)
add_executable(oj27 oj50/27计算最大乘积.cpp)
add_executable(oj28 oj50/28全排列.cpp)
add_executable(oj29 oj50/29组成最大数.cpp)
add_executable(oj30 oj50/30检查是否存在满足条件的数字组合.cpp)
add_executable(oj31 oj50/31素数之积.cpp)
add_executable(oj32 oj50/32字符串变换最小字符串.cpp)
add_executable(oj33 oj50/33找出经过特定点的路径长度.cpp)
add_executable(oj34 oj50/34ABR车路协同场景.cpp)
add_executable(oj35 oj50/35解密犯罪时间.cpp)
add_executable(oj36 oj50/36水仙花数.cpp)
add_executable(oj37 oj50/37字符串排序.cpp)
add_executable(oj38 oj50/38全量已占用字符集.cpp)
add_executable(oj39 oj50/39秘钥格式化.cpp)
add_executable(oj40 oj50/40数字字符串组合倒序.cpp)
add_executable(oj41 oj50/41查找接口成功率最优时间段.cpp)
add_executable(oj42 oj50/42GPU算力问题.cpp)
add_executable(oj43 oj50/43找终点.cpp)
add_executable(oj44 oj50/44最大花费金额.cpp)
add_executable(oj45 oj50/45分糖果.cpp)
add_executable(oj46 oj50/46猴子爬山.cpp)
add_executable(oj47 oj50/47WeiAreATeam.cpp)
add_executable(oj48 oj50/48寻找身高相近的小朋友.cpp)
add_executable(oj49 oj50/49数组组成最小数字.cpp)
add_executable(oj49_2 oj50/49_2.cpp)
add_executable(oj50 oj50/50最长密码.cpp)

#51-100
add_executable(oj56 oj100/56构成正方形的数量.cpp)
add_executable(oj58 oj100/58运维日志排序.cpp)
add_executable(oj59 oj100/59磁盘容量排序.cpp)
add_executable(oj64 oj100/64报数游戏.cpp)
add_executable(oj65 oj100/65高矮个子排队.cpp)
add_executable(oj66 oj100/66新工号中数字的最短长度.cpp)
add_executable(oj67 oj100/67消消乐游戏.cpp)
add_executable(oj74 oj100/74分班问题.cpp)
add_executable(oj76 oj100/76最左冗余覆盖子串.cpp)
add_executable(oj87 oj100/87英文输入法.cpp)
add_executable(oj91 oj100/91找最小数.cpp)
add_executable(oj92 oj100/92免单统计.cpp)
add_executable(oj92_2 oj100/92免单统计2.cpp)
add_executable(oj97 oj100/97预定酒店.cpp)

# 101-150
add_executable(oj102 oj150/102简单的压缩算法.cpp)
add_executable(oj106 oj150/106计算网络信号强度.cpp)
add_executable(oj109 oj150/109机房布局.cpp)
add_executable(oj113 oj150/113九宫格案件输入.cpp)
add_executable(oj113_2 oj150/113九宫格按键输入2.cpp)
add_executable(oj116 oj150/116货币单位换算.cpp)
add_executable(oj119 oj150/119满足条件的最长子串长11.cpp)
add_executable(oj128 oj150/128判断一组不等式是否满足约束并输出最大差.cpp)
add_executable(oj130 oj150/130最多获得的短信条数.cpp)
add_executable(oj136 oj150/136最大报酬.cpp)
add_executable(oj143 oj150/143羊狼农夫过河.cpp)
add_executable(oj149 oj150/149区间交叠问题.cpp)

# 151-200
add_executable(oj161 oj200/161机器人可活动的最大网格点数目.cpp)
add_executable(oj162 oj200/162过滤组合字符串.cpp)
add_executable(oj163 oj200/163日志首次上报最多积分日志采集系统.cpp)
add_executable(oj164 oj200/164字符串重新排序.cpp)
add_executable(oj165 oj200/165字符串重新排序2.cpp)
add_executable(oj166 oj200/166单向链表中间节点.cpp)
add_executable(oj172 oj200/172优秀学员统计.cpp)
add_executable(oj174 oj200/174猜字谜.cpp)
add_executable(oj176 oj200/176查找充电设备组合.cpp)

# 201-250
add_executable(oj201 oj250/201实力差距最小总和最佳对手.cpp)
add_executable(oj211 oj250/211最优资源分配芯片资源占用.cpp)
add_executable(oj212 oj250/212找数字找等值元素.cpp)
add_executable(oj215 oj250/215斗地主之顺子.cpp)
add_executable(oj216 oj250/216打印任务排序.cpp)
add_executable(oj219 oj250/219矩阵相交的面积.cpp)
add_executable(oj222 oj250/222ipv4地址转换.cpp)
add_executable(oj224 oj250/224欢乐的周末.cpp)
add_executable(oj225 oj250/225最少交换次数.cpp)
add_executable(oj228 oj250/228最大社交距离.cpp)
add_executable(oj228_2 oj250/228_2最大社交距离.cpp)
add_executable(oj231 oj250/231vlan资源池.cpp)
add_executable(oj233 oj250/233字符串分割.cpp)
add_executable(oj237 oj250/237一种字符串压缩表示的解压.cpp)
add_executable(oj239 oj250/239计算疫情扩散时间.cpp)
add_executable(oj246 oj250/246报文解压缩.cpp)

# 251-300
add_executable(oj253 oj300/253响应报文时间.cpp)
add_executable(oj266 oj300/266任务最优调度.cpp)
add_executable(oj268 oj300/268演唱会计算最多能观看机场演出.cpp)
add_executable(oj273 oj300/273内存资源分配.cpp)
add_executable(oj277 oj300/277导师请吃火锅.cpp)
add_executable(oj278 oj300/278关联子串.cpp)
add_executable(oj280 oj300/280数大雁.cpp)
add_executable(oj281 oj300/281热点网站统计.cpp)
add_executable(oj283 oj300/283单词接龙.cpp)
add_executable(oj284 oj300/284学生方阵.cpp)
add_executable(oj291 oj300/291整数编码.cpp)
add_executable(oj293 oj300/293宜居星球改造计划.cpp)
add_executable(oj296 oj300/296补活未成活胡杨.cpp)
add_executable(oj299 oj300/299选修课.cpp)
add_executable(oj300 oj300/300出租车计费靠谱的车.cpp)


# 301-350
add_executable(oj304 oj350/304最长的交替连续方波信号.cpp)
add_executable(oj308 oj350/308数组二叉树.cpp)
add_executable(oj310 oj350/310分隔数组的最大差值.cpp)
add_executable(oj311 oj350/311MELON的难题.cpp)
add_executable(oj319 oj350/319战场索敌.cpp)
add_executable(oj320 oj350/320最佳植树距离.cpp)
add_executable(oj328 oj350/328回复数字序列.cpp)
add_executable(oj332 oj350/332寻找最大价值的矿堆.cpp)
add_executable(oj341 oj350/341荒岛求生.cpp)
add_executable(oj344 oj350/344计算最近的数.cpp)
add_executable(oj345 oj350/345数字序列比大小.cpp)
add_executable(oj346s oj350/346金字塔.cpp)

# 351 - 400
add_executable(oj362 oj400/362转骰子.cpp)
add_executable(oj371 oj400/371增强的strstr.cpp)
add_executable(oj374 oj400/374字符串化繁为简.cpp)
add_executable(oj376 oj400/376通过软盘拷贝文件.cpp)
add_executable(oj392 oj400/392树状结构查询.cpp)
add_executable(oj397 oj400/397最长子字符串的长度.cpp)
add_executable(oj398 oj400/398转盘寿司.cpp)

# 401 - 450
add_executable(oj405 oj450/405游戏分组.cpp)
add_executable(oj409 oj450/409传递悄悄话.cpp)
add_executable(oj412 oj450/412学生排名智能成绩表.cpp)
add_executable(oj423 oj450/423计算三叉树的高度.cpp)
add_executable(oj424 oj450/424虚拟游戏理财.cpp)
add_executable(oj428 oj450/428连续字母长度.cpp)
add_executable(oj431 oj450/431跳马问题.cpp)
add_executable(oj451 oj450/451手机app防沉迷系统.cpp)

# 451 - 500
add_executable(oj453 oj500/453跳格子小明跳格子.cpp)
add_executable(oj454 oj500/454生成哈夫曼树.cpp)
add_executable(oj455 oj500/455螺旋数字矩阵.cpp)
add_executable(oj456 oj500/456分披萨.cpp)
add_executable(oj460 oj500/460模拟目录管理功能.cpp)
add_executable(oj468 oj500/468可以处理的最大任务数.cpp)
add_executable(oj474 oj500/474推荐多样性.cpp)
add_executable(oj476 oj500/476矩阵匹配数组中第k大的数中的最小值.cpp)
add_executable(oj482 oj500/482加密算法特殊的加密算法.cpp)
add_executable(oj483 oj500/483中文分词模拟器.cpp)
add_executable(oj487 oj500/487流浪地球.cpp)


# 501 550
add_executable(oj526 oj550/526数字游戏.cpp)
add_executable(oj548 oj550/548最大数.cpp)

# 算法
add_executable(01skiplist suanfa_1000/01skiplist.cpp)
add_executable(02skiplist suanfa_1000/02skiplist.cpp)
add_executable(suanfa_1000_03 suanfa_1000/03字符串截取.cpp)

add_executable(suanfa_1000_04 suanfa_1000/04项目分析duckdb.cpp)
# 链接 Boost::filesystem 库到可执行文件
target_link_libraries(suanfa_1000_04 PRIVATE boost_filesystem)

add_executable(suanfa_1000_05 suanfa_1000/05aries恢复.cpp)
add_executable(suanfa_1000_duckdb_parse suanfa_1000/duckdb/parseConfig.cpp)
add_executable(suanfa_1000_duckdb_log suanfa_1000/duckdb/log.cpp)