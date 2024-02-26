#### 声明
【注意】本项目来源于Gitee上的同名项目，Gitee上的该项目已永久停更。此项目从今开始只在GitHub进行
- 我创建这个项目的目的是复习数据结构的知识点，并且帮助（如果真的有人看这个项目的话）别人复习数据结构的知识点。本人与任何培训机构没有任何利益关系，该程序由我独自完成，没有一行代码是从网上或者别的地方搬来的。
- 本示例程序的全部函数列表位于“Wiki”页面。由于更新不及时，可能有极个别函数被遗漏
- 请再次注意：这是一个完全不求回报的非营利性项目！

#### 程序介绍
本程序在Windows11系统下的Microsoft Visual Studio 2022环境中编写。使用其他系统或者其他编译器可能出现一些编译错误。编译前必须将所有.h和.cpp文件加入项目中，否则会报错。
- 本程序唯一参考教材：《数据结构（C语言版）》清华大学出版社；作者：严蔚敏，吴伟民
- 本程序参考书籍：《C++ Primer Plus（第六版）中文版》2012年7月第1版，人民邮电出版社

#### 程序结构
- main.cpp:用于测试各种功能的测试用主程序文件
- TABLE.h:线性表/链表的C++类模板头文件（由于C++的性质，类模板的程序部分也在这个文件中）
- TREES.h:树的C++类模板头文件（由于C++的性质，类模板的程序部分也在这个文件中）
- GRAPHS.h:图的C++类模板头文件（由于C++的性质，类模板的程序部分也在这个文件中）
- 算法设计题完成情况.txt:记录《数据结构》课后习题的完成情况
- 备忘录.txt:记录一些有意义的信息

#### 程序文件使用方法
1.  将全部.h文件和.cpp文件导入到项目中
2.  编译项目，得到可执行文件
3.  运行可执行文件

#### 重要提示
1.  不要擅自更改除了main.cpp外的任何其他文件。如果要调用不同的函数，请更改main.cpp文件
2.  如果想了解程序运行的基本原理，请查看除了main.cpp外的文件
3.  如果要修改main.cpp外的文件，请备份原文件
4.  如果编译器或一些安全软件指出程序有取消对NULL指针的引用/内存泄漏问题，则大概率属于误报。Visual Studio 2022指出了触发这些错误的具体条件，不过经过理论分析，这些条件在程序运行中没有任何被触发的可能。⚠️⚠️⚠️但是！如果你在使用过程中发现了程序确实有（编译器或安全软件未指出）严重缺陷，尤其是内存泄露问题或冗余代码，请务必提出issue，并附上相应的触发条件。我对发现程序缺陷的人表示感谢！⚠️⚠️⚠️

#### 程序特性
1.  TABLE.h，TREES.h，GRAPHS.h文件是类模板文件。“模板”意味着它可以创建以下具体类型的对象：bool，char，char8_t，unsigned char，signed char，__int8，char16_t，__int16，short，unsigned short，wchar_t，__wchar_t，char32_t，float，__int32，int，unsigned int，long，unsigned long，double，__int64，long double，long long，unsigned long long，unsigned __int64
2.  TABLE.h文件（类模板文件）实现了自构建，可以调用自身的方法创建该类的对象（对于任何上述种类的数据）
3.  程序具有应对非法输入流的基本保护机制，如果输入流无法被转换为目标类型，程序不会崩溃
4.  TABLE.h中所有的函数，例如复制构造函数，插入函数，排序函数，程序均以线性表/链表的形式分别实现。TABLE.h的一半是专门处理线性表的代码，另一半是专门处理链表的代码。
5.  GRAPHS.h中几乎所有的函数，例如默认构造函数，删除某个节点的函数，深度优先遍历函数，都以邻接表/十字链表或邻接多重表的形式分别实现。相关函数中，约30%是处理邻接表的代码，约30%是处理十字链表的代码，约40%是处理邻接多重表的代码。

#### 已实现的功能
1.  《数据结构》第二章线性表，第三章栈和队列，第四章串，第六章树，第七章图，第九章查找，第十章内部排序的全部基本操作（未实现书中一元多项式，离散时间模拟等拓展操作）
2.  C++类中除了类继承的大部分基本操作
3.  C++标准string类的（除了查找的）几乎全部操作

#### 后续版本即将实现的功能（不保证实现顺序）
暂无
