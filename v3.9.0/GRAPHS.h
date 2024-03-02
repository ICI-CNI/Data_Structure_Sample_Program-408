#ifndef GRAPHS_H
#define GRAPHS_H
//此处不需要#include任何文件，头文件由TABLE.h提供
//此处不需要使用using std::，因为已经在TABLE.h中声明过

template<typename Type>
class GRAPH
{
private:
	template<typename Type>
	friend class LIST;
	template<typename Type>
	friend class TREE;

	//共用数据区
	//【翻译对照】：下面将弧arc和边edge统称为line，数组表示法简称为array，邻接表简称为listA，十字链表/邻接多重表简称为listB
	bool SILENCE = true;//控制析构函数，复制构造函数，重载赋值运算符的调试输出，默认不输出
	bool graph_initialized;//true表示图已初始化，false表示图未初始化。一旦这个参数被置为true，则意味着图中不存在任何错误
	bool graph_directed;//true为有向图，false为无向图
	bool graph_weighted;//true为带权图，false为无权图，只有1个顶点的图只可以是无权图
	long long line_num;//弧或边的数量
	long long vertex_num;//顶点个数
	bool* vertex_visited;//顶点是否被访问
	Type* vertex_content;//顶点所存储的信息
	LIST<char>** vertex_id;//顶点的唯一标识符

	//【重要】：每个对象都同时具备下面三种表示法，而非三选一
	//数组表示法
	struct array_line
	{
		long double line_weight;//弧或边的权重
		bool line_exist;//是否存在这条弧或边
		bool line_visited;//弧或边是否被访问
		Type line_content;//弧或边存储的信息
	};
	array_line** array_matrix;//图的邻接矩阵

	//邻接表
	//对于无向图，邻接表必须出现(A-B,B-A)重复边。邻接多重表与之相反，一定不能出现(A-B,B-A)重复边
	//对于有向图，邻接表不一定出现(A-B,B-A)重复边
	struct listA_line
	{
		long long vertex;//下一个顶点的序号
		struct listA_line* line;//指向下一条弧或边
		long double line_weight;//弧或边的权重
		bool line_visited;//弧或边是否被访问
		Type line_content;//弧或边存储的信息
	};
	listA_line** vertex_first;//指向该顶点的下一个顶点

	//十字链表，邻接多重表
	//(1,2)：1是弧尾，2是弧头，(1,3)是弧尾相同的下一条弧。假如是无向图，(1,3)是下一条依附于顶点1的边
	struct listB_line
	{
		long long vertex_A;//若为有向图，表示弧尾顶点的序号；若为无向图，表示该边依附的第一个顶点的序号
		long long vertex_B;//若为有向图，表示弧头顶点的序号；若为无向图，表示该边依附的第二个顶点的序号
		struct listB_line* line_A;//若为有向图，指向弧尾相同的下一条弧；若为无向图，指向下一条依附于vertex_A的边
		struct listB_line* line_B;//若为有向图，指向弧头相同的下一条弧；若为无向图，指向下一条依附于vertex_B的边
		long double line_weight;//弧或边的权重
		bool line_visited;//弧或边是否被访问
		Type line_content;//弧或边存储的信息
	};
	listB_line** vertex_firstA;//若为有向图，指向以该顶点为弧尾的第一条弧；若为无向图，指向第一条依附于该顶点的边
	listB_line** vertex_firstB;//若为有向图，指向以该顶点为弧头的第一条弧；若为无向图，该指针为空指针

	//基本功能
	void array_2_listA();//将邻接矩阵转换为邻接表
	void array_2_listB();//将邻接矩阵转换为十字链表或邻接多重表

public:
	//基本功能
	explicit GRAPH();//默认构造函数
	explicit GRAPH(const bool DIRECTED, const bool WEIGHTED, const bool HELP);//默认构造函数
	~GRAPH();//默认析构函数
	GRAPH& operator=(const GRAPH& x);//重载赋值运算符
	GRAPH(const GRAPH& x);//复制构造函数

	//第七章：图
	void Info() const;//输出图的全部信息
	void Display_01() const;//输出邻接矩阵，边或弧用1表示，其余元素均为0
	void Display_2() const;//输出邻接表
	void Display_3() const;//输出十字链表或邻接多重表
	void Display_weight() const;//以邻接矩阵格式输出边的权值
	void DFS() const;//深度优先搜索，使用邻接表存储结构
	void DFS_LE() const;//低效深度优先搜索，使用十字链表/邻接多重表存储结构
	void BFS() const;//广度优先搜索，使用邻接表存储结构
	void BFS_LE() const;//低效广度优先搜索，使用十字链表/邻接多重表存储结构
	void Silence_T();//开启调试输出
	void Silence_F();//关闭调试输出
	void Repair_GRAPH();//将未初始化的图转换为已初始化的空图
	void Clear_GRAPH();//将已初始化的图清空，变成空图
	void Add_vertex();//增加一个结点
	void Delete_vertex();//删除一个结点
	void Add_line();//增加一条弧或边
	void Delete_line();//删除一条弧或边
	bool Connected() const;//判断图是否连通
	bool S_Connected() const;//判断图是否强连通
	bool Weighted() const;//判断图是否为带权图
	void Add_weight();//向图中的所有边加上权值
	bool Has_cycles() const;//判断图中有无环（有向图/无向图通用）
	GRAPH Prim() const;//Prim算法
	GRAPH Kruskal() const;//Kruskal算法
	void Dijkstra() const;//Dijkstra算法
	void Floyd() const;//Floyd算法
	LIST<long long> Topo_sort(const bool output) const;//拓扑排序
};

template<typename Type>
GRAPH<Type>::GRAPH()
{
	graph_initialized = false;
	graph_directed = false;
	graph_weighted = false;
	line_num = -1;
	vertex_num = -1;
	vertex_visited = nullptr;
	vertex_content = nullptr;
	array_matrix = nullptr;
	vertex_first = nullptr;
	vertex_firstA = nullptr;
	vertex_firstB = nullptr;
	vertex_id = nullptr;

	return;
}

template<typename Type>
GRAPH<Type>::GRAPH(const bool DIRECTED, const bool WEIGHTED, const bool HELP)
{
	graph_initialized = false;
	graph_directed = DIRECTED;//必须在这里初始化该变量，否则下面调用array_2_listB函数时会出错
	graph_weighted = WEIGHTED;//必须在这里初始化该变量，否则该函数的if语句无法正常工作
	line_num = -1;
	vertex_num = -1;
	vertex_visited = nullptr;
	vertex_content = nullptr;
	array_matrix = nullptr;
	vertex_first = nullptr;
	vertex_firstA = nullptr;
	vertex_firstB = nullptr;
	vertex_id = nullptr;

	if (strcmp(typeid(Type).name(), typeid(bool).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(char).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(char8_t).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned char).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(signed char).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__int8).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(char16_t).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__int16).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(short).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned short).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(wchar_t).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__wchar_t).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(char32_t).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(float).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__int32).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(int).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned int).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(double).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__int64).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long double).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned long long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned __int64).name()) != 0)
	{
		cout << "\033[1;31m【错误】程序目前不支持创建此类型的图\033[0m" << endl;
		cout << "\033[1;31m【错误】无法正确创建图，析构函数将被调用\033[0m" << endl;
		this->~GRAPH();
		return;
	}
	if (HELP == true)
	{
		cout << "请仔细阅读下列输入规则：" << endl;
		cout << "【总则】：先输入非重复的顶点序列，再输入非重复的弧/边序列。如果输入有误，图不会被构建，并将被删除" << endl;
		cout << "不要输入任何非英文字符(如汉字字符)，输入时不要将输入法设置为中文模式，否则可能出现未知错误" << endl;
		cout << endl;
		cout << "【顶点序列的输入规则】：" << endl;
		cout << "1--> 顶点序列将以字符串形式存储，输入的每个顶点名称将被作为该顶点的唯一标识符。因此不允许输入重复的顶点名称" << endl;
		cout << "2--> 顶点序列接受的字符范围是键盘上可以输入的全部英文字符(char类型)。输入中文字符等特殊字符可能会出现未知错误" << endl;
		cout << "3a-> 顶点序列间使用,（英文逗号）分开，转义字符定义为;（英文分号）" << endl;
		cout << "3b-> 如果要输入字符,（英文逗号），请按顺序输入两个字符;（英文分号）,（英文逗号）" << endl;
		cout << "3c-> 如果要输入字符;（英文分号），请按顺序输入两个字符;（英文分号）[（英文左方括号）" << endl;
		cout << "3d-> ;（英文分号）的后面必须是,（英文逗号）[（英文左方括号）中的一个，否则视为错误" << endl;
		cout << "4--> 顶点的名称不允许为空" << endl;
		cout << endl;
		cout << "【弧/边序列的输入规则】" << endl;
		cout << "无权图的弧/边输入格式是:      ,顶点A'顶点B,    带权图的弧/边输入格式是:    ,顶点A'顶点B'权值,    " << endl;
		cout << "1--> 弧/边序列中，不允许出现顶点到自身的弧/边，不允许出现重复的弧/边。对于无向图，(A,B)(B,A)是重复边" << endl;
		cout << "2a-> 弧/边序列使用'（英文撇号,位于键盘ENTER键左边）将顶点A，顶点B分开。转义字符定义为|（英文竖线）" << endl;
		cout << "2b-> 如果要输入字符'（英文撇号），请按顺序输入两个字符|（英文竖线）'（英文撇号）" << endl;
		cout << "2c-> 如果要输入字符|（英文竖线），请按顺序输入两个字符|（英文竖线）]（英文右方括号）" << endl;
		cout << "2d-> |（英文竖线）的后面必须是'（英文撇号）]（英文右方括号）中的一个，否则视为错误" << endl;
		cout << "\033[1;33m如果不愿意使用复杂的转义字符，或者对上面复杂的规则感到困惑，请不要在顶点的名称中使用\033[0m";
		cout << "\033[1;33m,（英文逗号）;（英文分号）'（英文撇号）|（英文竖线）这四个字符\033[0m";
		cout << endl;
	}

	//读取图的顶点
	cout << "【提示】请按照规则输入图的顶点序列：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		cout << "\033[1;33m【警告】输入流的长度为0，已创建一个空图\033[0m" << endl;
		line_num = 0;
		vertex_num = 0;
		graph_initialized = true;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}
	bool BAD_INPUT = false;
	int ERROR_TYPE = 0;//0代表无错误

	//按逗号分割顶点序列，注意只输入一个顶点是合法的
	LIST<long long> input_pos(3);
	input_pos += 0;
	if (input[0] == ',')
	{
		BAD_INPUT = true;
		ERROR_TYPE = 1;
	}
	if (BAD_INPUT == false)
	{
		for (long long i = 1; i <= input.Listlength() - 1; i++)
		{
			if (input[i] == ',' && input[i - 1] != ';')
			{
				input_pos += (i - 1);
				input_pos += (i + 1);
			}
		}
		input_pos += input.Listlength() - 1;
		long long check_A = 0;
		long long check_B = 1;
		while (check_B <= input_pos.Listlength() - 1)
		{
			if (input_pos[check_A] > input_pos[check_B])
			{
				BAD_INPUT = true;
				ERROR_TYPE = 2;
				break;
			}
			check_A = check_A + 2;
			check_B = check_B + 2;
		}
	}

	//下面是同时改变循环终止条件和计数器变量的示例程序。输出结果：(1,10),(3,9),(5,8),(7,7)
	/*
	long long x = 10;
	for (long long i = 1; i <= x; i++)
	{
		cout << i << "     " << x << endl;
		x = x - 1;
		i = i + 1;
	}
	*/
	//还原转义字符
	if (BAD_INPUT == false)
	{
		vertex_num = input_pos.Listlength() / 2;//顶点个数
		//vertex_id(结构指针数组)的定义是    LIST<char>** vertex_id   。下面↓的初始化语句只能这么写，否则出莫名其妙的错误
		//input_pos的最短长度是2（只输入一个顶点时）
		vertex_id = new LIST<char>*[vertex_num];
		long long start_pos = 0;
		for (long long i = 1; i <= vertex_num; i++)
		{
			long long start = input_pos[start_pos];
			long long length = input_pos[start_pos + 1] - input_pos[start_pos] + 1;
			vertex_id[i - 1] = new LIST<char>(3);
			*vertex_id[i - 1] = input.Substring(start + 1, length);
			start_pos = start_pos + 2;
		}
		for (long long i = 1; i <= vertex_num; i++)
		{
			if (vertex_id[i - 1]->Getelement(vertex_id[i - 1]->Listlength()) == ';')//顶点名称的最后一个字符是;
			{
				BAD_INPUT = true;
				ERROR_TYPE = 3;
				break;
			}
			for (long long i1 = vertex_id[i - 1]->Listlength() - 1; i1 >= 1; i1--)
			{
				if (vertex_id[i - 1]->Getelement(i1) == ';')
				{
					if (vertex_id[i - 1]->Getelement(i1 + 1) == ',')
						vertex_id[i - 1]->Listdelete(i1);
					else if (vertex_id[i - 1]->Getelement(i1 + 1) == '[')
						vertex_id[i - 1]->Listdelete(i1 + 1);
					else
					{
						BAD_INPUT = true;
						ERROR_TYPE = 3;
						break;
					}
				}
			}
			if (BAD_INPUT == true)
				break;
		}
	}
	input.Clearlist();
	input_pos.Clearlist();

	//将顶点排序，并检验是否有重复名称
	if (BAD_INPUT == false)
	{
		String_sort(vertex_id, vertex_num);
		for (long long i = 1; i <= vertex_num - 1; i++)
		{
			if (*vertex_id[i - 1] == *vertex_id[i])
			{
				BAD_INPUT = true;
				ERROR_TYPE = 4;
				break;
			}
		}
	}

	//读取图的弧或边
	bool LINE_EMPTY = false;
	if (BAD_INPUT == false)
	{
		cout << "\033[1;32m【提示】输入的顶点序列正确无误，共输入  \033[0m" << vertex_num;
		cout << "\033[1;32m  个不重复的顶点\033[0m" << endl << endl;
		if (vertex_num == 1)
		{
			if (DIRECTED == true)
				cout << "\033[1;33m由于只输入了1个顶点，创建的图将没有任何弧\033[0m" << endl;
			else
				cout << "\033[1;33m由于只输入了1个顶点，创建的图将没有任何边\033[0m" << endl;
			LINE_EMPTY = true;
		}
		else
		{
			if (DIRECTED == true)
				cout << "【提示】请按照规则输入图的弧：" << endl;
			else
				cout << "【提示】请按照规则输入图的边：" << endl;
			cin >> input;
			if (input.Listlength() == 0)
			{
				LINE_EMPTY = true;
				cout << "\033[1;33m【警告】输入流的长度为0，\033[0m";
				if (DIRECTED == true)
					cout << "\033[1;33m创建的图会没有任何弧\033[0m" << endl;
				else
					cout << "\033[1;33m创建的图会没有任何边\033[0m" << endl;
			}
		}
	}

	//将弧/边序列按照顶点成对分割，并校验是否有错误。注意只输入一条弧/边是合法的
	if (BAD_INPUT == false && LINE_EMPTY == false)
	{
		input_pos += 0;
		if (input[0] == ',')
		{
			BAD_INPUT = true;
			ERROR_TYPE = 5;
		}
		if (BAD_INPUT == false)
		{
			for (long long i = 1; i <= input.Listlength() - 1; i++)
			{
				if (input[i] == ',' && input[i - 1] != ';')
				{
					input_pos += (i - 1);
					input_pos += (i + 1);
				}
			}
			input_pos += input.Listlength() - 1;
			long long check_A = 0;
			long long check_B = 1;
			while (check_B <= input_pos.Listlength() - 1)
			{
				if (input_pos[check_A] > input_pos[check_B])
				{
					BAD_INPUT = true;
					ERROR_TYPE = 6;
					break;
				}
				check_A = check_A + 2;
				check_B = check_B + 2;
			}
			//原理：若输入12,,34，input_pos的值为0 1 3 2 4 5，从而发现存在内容为空的弧或边
		}
	}

	//还原分割顶点对时使用的转义字符;（英文分号）
	LIST<char>** first_split = nullptr;
	if (BAD_INPUT == false && LINE_EMPTY == false)
	{
		line_num = input_pos.Listlength() / 2;//弧或边的条数
		//input_pos的最短长度是2（只输入一个顶点时）
		first_split = new LIST<char>*[line_num];
		long long start_pos = 0;
		for (long long i = 1; i <= line_num; i++)
		{
			long long start = input_pos[start_pos];
			long long length = input_pos[start_pos + 1] - input_pos[start_pos] + 1;
			first_split[i - 1] = new LIST<char>(3);
			*first_split[i - 1] = input.Substring(start + 1, length);
			start_pos = start_pos + 2;
		}
		for (long long i = 1; i <= line_num; i++)
		{
			if (first_split[i - 1]->Getelement(first_split[i - 1]->Listlength()) == ';')//顶点名称的最后一个字符是;
			{
				BAD_INPUT = true;
				ERROR_TYPE = 7;
				break;
			}
			for (long long i1 = first_split[i - 1]->Listlength() - 1; i1 >= 1; i1--)
			{
				if (first_split[i - 1]->Getelement(i1) == ';')
				{
					if (first_split[i - 1]->Getelement(i1 + 1) == ',')
						first_split[i - 1]->Listdelete(i1);
					else if (first_split[i - 1]->Getelement(i1 + 1) == '[')
						first_split[i - 1]->Listdelete(i1 + 1);
					else
					{
						BAD_INPUT = true;
						ERROR_TYPE = 7;
						break;
					}
				}
			}
			if (BAD_INPUT == true)
				break;
		}
	}
	input.Clearlist();
	input_pos.Clearlist();

	//将一次分割后的弧或边序列排序，并检验是否有重复的弧或边
	if (BAD_INPUT == false && LINE_EMPTY == false)
	{
		String_sort(first_split, line_num);
		for (long long i = 1; i <= line_num - 1; i++)
		{
			if (*first_split[i - 1] == *first_split[i])
			{
				BAD_INPUT = true;
				ERROR_TYPE = 8;
				break;
			}
		}
	}

	//初始化邻接矩阵和弧/边的结构。注意即使图没有任何弧/边，也必须初始化
	if (BAD_INPUT == false)
	{
		array_matrix = new array_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
		{
			array_matrix[i - 1] = new array_line[vertex_num];
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				array_matrix[i - 1][i1 - 1].line_weight = 0.0;
				array_matrix[i - 1][i1 - 1].line_exist = false;
				array_matrix[i - 1][i1 - 1].line_visited = false;
				array_matrix[i - 1][i1 - 1].line_content = static_cast<Type>(0);
			}
		}
		vertex_first = new listA_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_first[i - 1] = nullptr;
		vertex_firstA = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_firstA[i - 1] = nullptr;
		if (DIRECTED == true)
		{
			vertex_firstB = new listB_line * [vertex_num];
			for (long long i = 1; i <= vertex_num; i++)
				vertex_firstB[i - 1] = nullptr;
		}
	}

	//一次分割结束后，将每条弧或边的两个顶点分开，并还原顶点名称
	if (BAD_INPUT == false && LINE_EMPTY == false)
	{
		if (graph_weighted == true)
		{
			LIST<char> line_A(3);
			LIST<char> line_B(3);
			LIST<char> line_C(3);
			LIST<long long> split_pos(3);
			for (long long i = 1; i <= line_num; i++)
			{
				//扫描分割点
				if (first_split[i - 1]->Getelement(1) == '\'')//弧或边的第一个顶点名称为空
				{
					BAD_INPUT = true;
					ERROR_TYPE = 9;
					break;
				}
				split_pos += 1;
				for (long long i1 = 2; i1 <= first_split[i - 1]->Listlength(); i1++)
				{
					if (first_split[i - 1]->Getelement(i1) == '\'' && first_split[i - 1]->Getelement(i1 - 1) != '|')
					{
						split_pos += (i1 - 1);
						split_pos += (i1 + 1);
					}
				}
				split_pos += first_split[i - 1]->Listlength();
				if (split_pos.Listlength() != 6)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 7;
					break;
				}
				long long check_A = 0;
				long long check_B = 1;
				while (check_B <= split_pos.Listlength() - 1)
				{
					if (split_pos[check_A] > split_pos[check_B])
					{
						BAD_INPUT = true;
						ERROR_TYPE = 7;
						break;
					}
					check_A = check_A + 2;
					check_B = check_B + 2;
				}
				if (BAD_INPUT == true)
					break;
				long long length_A = split_pos[1];
				long long length_B = split_pos[3] - split_pos[2] + 1;
				long long length_C = split_pos[5] - split_pos[4] + 1;
				line_A = first_split[i - 1]->Substring(1, length_A);
				line_B = first_split[i - 1]->Substring(split_pos[2], length_B);
				if (line_A == line_B)//过滤掉类似v1'v1'1,v1'v1'2的输入
				{
					BAD_INPUT = true;
					ERROR_TYPE = 4;
					break;
				}
				line_C = first_split[i - 1]->Substring(split_pos[4], length_C);
				char* converted_char = line_C.Char_array(false);
				long double converted = strtold(converted_char, nullptr);
				delete[] converted_char;
				split_pos.Clearlist();
				if (converted <= 0)//输入的权值 <= 0
				{
					BAD_INPUT = true;
					ERROR_TYPE = 13;
					break;
				}

				//还原两个顶点的名称
				for (long long i1 = line_A.Listlength() - 1; i1 >= 1; i1--)
				{
					if (line_A[i1 - 1] == '|')
					{
						if (line_A[i1] == '\'')
							line_A.Listdelete(i1);
						else if (line_A[i1] == ']')
							line_A.Listdelete(i1 + 1);
						else
						{
							BAD_INPUT = true;
							ERROR_TYPE = 7;
							break;
						}
					}
				}
				if (BAD_INPUT == true)
					break;
				for (long long i1 = line_B.Listlength() - 1; i1 >= 1; i1--)
				{
					if (line_B[i1 - 1] == '|')
					{
						if (line_B[i1] == '\'')
							line_B.Listdelete(i1);
						else if (line_B[i1] == ']')
							line_B.Listdelete(i1 + 1);
						else
						{
							BAD_INPUT = true;
							ERROR_TYPE = 7;
							break;
						}
					}
				}
				if (BAD_INPUT == true)
					break;

				//写入图的邻接矩阵
				long long pos_A = -1;
				for (long long i1 = 1; i1 <= vertex_num; i1++)
				{
					if (*vertex_id[i1 - 1] == line_A)
						pos_A = i1;
				}
				long long pos_B = -1;
				for (long long i1 = 1; i1 <= vertex_num; i1++)
				{
					if (*vertex_id[i1 - 1] == line_B)
						pos_B = i1;
				}
				if (pos_A == -1 || pos_B == -1)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 12;
					break;
				}
				//若没有此语句，输入类似v1'v2'1,v1'v2'5.5的序列后程序会崩溃
				if (array_matrix[pos_A - 1][pos_B - 1].line_exist == true)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 8;
					break;
				}
				array_matrix[pos_A - 1][pos_B - 1].line_exist = true;
				array_matrix[pos_A - 1][pos_B - 1].line_weight = converted;

				//无向图(A-B,B-A)重复边检测
				if (array_matrix[pos_B - 1][pos_A - 1].line_exist == true && DIRECTED == false)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 8;
					break;
				}
			}
		}
		else
		{
			LIST<char> line_A(3);
			LIST<char> line_B(3);
			for (long long i = 1; i <= line_num; i++)
			{
				//将两个顶点分开
				if (first_split[i - 1]->Getelement(1) == '\'')//弧或边的第一个顶点名称为空
				{
					BAD_INPUT = true;
					ERROR_TYPE = 9;
					break;
				}
				int split_count = 0;
				long long line_split_pos = 0;
				for (long long i1 = 2; i1 <= first_split[i - 1]->Listlength(); i1++)//顶点数量计数
				{
					if (first_split[i - 1]->Getelement(i1) == '\'' && first_split[i - 1]->Getelement(i1 - 1) != '|')
					{
						split_count = split_count + 1;
						line_split_pos = i1;
					}
				}
				if (line_split_pos == first_split[i - 1]->Listlength())//弧或边的第二个顶点名称为空
				{
					BAD_INPUT = true;
					ERROR_TYPE = 9;
					break;
				}
				if (split_count > 1)//弧或边的顶点数量>=3
				{
					BAD_INPUT = true;
					ERROR_TYPE = 10;
					break;
				}
				if (split_count == 0)//弧或边只有一个顶点
				{
					BAD_INPUT = true;
					ERROR_TYPE = 11;
					break;
				}
				long long length_A = line_split_pos - 1;
				long long length_B = first_split[i - 1]->Listlength() - line_split_pos;
				line_A = first_split[i - 1]->Substring(1, length_A);//弧或边的第一顶点
				line_B = first_split[i - 1]->Substring(line_split_pos + 1, length_B);//弧或边的第二顶点
				if (line_A == line_B)//过滤掉类似v1'v1的输入
				{
					BAD_INPUT = true;
					ERROR_TYPE = 4;
					break;
				}

				//还原两个顶点的名称
				for (long long i1 = line_A.Listlength() - 1; i1 >= 1; i1--)
				{
					if (line_A[i1 - 1] == '|')
					{
						if (line_A[i1] == '\'')
							line_A.Listdelete(i1);
						else if (line_A[i1] == ']')
							line_A.Listdelete(i1 + 1);
						else
						{
							BAD_INPUT = true;
							ERROR_TYPE = 7;
							break;
						}
					}
				}
				if (BAD_INPUT == true)
					break;
				for (long long i1 = line_B.Listlength() - 1; i1 >= 1; i1--)
				{
					if (line_B[i1 - 1] == '|')
					{
						if (line_B[i1] == '\'')
							line_B.Listdelete(i1);
						else if (line_B[i1] == ']')
							line_B.Listdelete(i1 + 1);
						else
						{
							BAD_INPUT = true;
							ERROR_TYPE = 7;
							break;
						}
					}
				}
				if (BAD_INPUT == true)
					break;

				//写入图的邻接矩阵
				long long pos_A = -1;
				for (long long i1 = 1; i1 <= vertex_num; i1++)
				{
					if (*vertex_id[i1 - 1] == line_A)
						pos_A = i1;
				}
				long long pos_B = -1;
				for (long long i1 = 1; i1 <= vertex_num; i1++)
				{
					if (*vertex_id[i1 - 1] == line_B)
						pos_B = i1;
				}
				if (pos_A == -1 || pos_B == -1)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 12;
					break;
				}
				array_matrix[pos_A - 1][pos_B - 1].line_exist = true;

				//无向图(A-B,B-A)重复边检测
				if (array_matrix[pos_B - 1][pos_A - 1].line_exist == true && DIRECTED == false)
				{
					BAD_INPUT = true;
					ERROR_TYPE = 8;
					break;
				}
			}
		}
	}

	//释放申请的临时空间
	if (first_split != nullptr)
	{
		for (long long i = 1; i <= line_num; i++)
			first_split[i - 1]->~LIST();
		delete[] first_split;
	}

	//将图的邻接矩阵转换为十字链表，邻接多重表
	if (BAD_INPUT == false && LINE_EMPTY == false)
		array_2_listB();

	//将图的邻接矩阵转换为邻接表
	if (BAD_INPUT == false && LINE_EMPTY == false)
		array_2_listA();

	//初始化图的其余部分。注意即使图没有任何弧/边，也必须初始化
	if (BAD_INPUT == false)
	{
		vertex_visited = new bool[vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_visited[i - 1] = false;
		vertex_content = new Type[vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_content[i - 1] = static_cast<Type>(0);
		if (LINE_EMPTY == true)
			line_num = 0;
		graph_initialized = true;//在这行代码后，图将被视为没有任何错误

		if (DIRECTED == true)
			cout << "\033[1;32m【提示】输入的弧序列正确无误，共输入  \033[0m" << line_num;
		else
			cout << "\033[1;32m【提示】输入的边序列正确无误，共输入  \033[0m" << line_num;
		if (DIRECTED == true)
			cout << "\033[1;32m  条不重复的弧\033[0m" << endl;
		else
			cout << "\033[1;32m  条不重复的边\033[0m" << endl;
		cout << "\033[1;32m【提示】所有输入内容均正确，图已成功构建\033[0m" << endl << endl;
	}

	//错误类型提示
	if (BAD_INPUT == true)
	{
		if (ERROR_TYPE == 1)
			cout << "\033[1;31m【错误】第一个顶点的名称不存在，图无法构建且将被删除\033[0m" << endl;
		if (ERROR_TYPE == 2)
			cout << "\033[1;31m【错误】存在名字为空的顶点，图无法构建且将被删除\033[0m" << endl;
		if (ERROR_TYPE == 3)
			cout << "\033[1;31m【错误】转义字符的使用有误，图无法构建且将被删除\033[0m" << endl;
		if (ERROR_TYPE == 4)
			cout << "\033[1;31m【错误】存在名称重复的顶点，图无法构建且将被删除\033[0m" << endl;
		if (ERROR_TYPE == 5)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，第一条弧的内容为空，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，第一条边的内容为空，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 6)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，存在内容为空的弧，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，存在内容为空的边，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 7)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 8)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，存在重复的弧，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，存在重复的边，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 9)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，某条弧存在名字为空的顶点，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，某条边存在名字为空的顶点，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 10)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，某条弧的顶点数量>=3，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，某条边的顶点数量>=3，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 11)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中，某条弧只有一个顶点，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，某条边只有一个顶点，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 12)
		{
			if (DIRECTED == true)
				cout << "\033[1;31m【错误】输入的弧序列中存在一个与顶点序列中任何顶点均不同的顶点，图无法构建且将被删除\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中存在一个与顶点序列中任何顶点均不同的顶点，图无法构建且将被删除\033[0m" << endl;
		}
		if (ERROR_TYPE == 13)
			cout << "\033[1;31m【错误】输入的权值<=0，注意权值可以是小数但必须>0\033[0m" << endl;

		if (HELP == false)
			cout << "\033[1; 33m【提示】如果不清楚错误出现的原因，请打开帮助(将HELP参数设置为true)\033[0m" << endl << endl;
		this->~GRAPH();
	}
	return;
}

template<typename Type>
GRAPH<Type>::~GRAPH()
{
	if (SILENCE == false)
		cout << "【提示】GRAPH类的析构函数被调用" << endl;

	//删除邻接矩阵
	if (array_matrix != nullptr)
	{
		for (long long i = 1; i <= vertex_num; i++)
			delete[] array_matrix[i - 1];
		delete[] array_matrix;
		array_matrix = nullptr;
	}

	//删除十字链表/邻接多重表
	//只有一种情况下，当函数运行到此处时，graph_initialized为false：图未成功构建，并在默认构造函数内调用析构函数
	//若不加该判断条件，图未成功构建时若调用析构函数，程序会崩溃
	if (graph_initialized == true && vertex_firstA != nullptr)
	{
		if (graph_directed == true)
		{
			//每条弧都只会被访问1次
			for (long long i = 1; i <= vertex_num; i++)
			{
				listB_line* line_out = vertex_firstA[i - 1];
				while (line_out != nullptr)
				{
					listB_line* line_delete = line_out;
					line_out = line_out->line_A;
					delete line_delete;
				}
			}
		}
		else
		{
			//每条边都只会被访问2次
			listB_line** listB_delete = new listB_line * [line_num];
			long long delete_count = 0;
			for (long long i = 1; i <= vertex_num; i++)
			{
				listB_line* line_out = vertex_firstA[i - 1];
				while (line_out != nullptr)
				{
					if (line_out->line_visited == false)
					{
						line_out->line_visited = true;
						listB_delete[delete_count] = line_out;
						delete_count = delete_count + 1;
					}
					if (line_out->vertex_A == i)
						line_out = line_out->line_A;
					else
						line_out = line_out->line_B;
				}
			}
			for (long long i = 1; i <= line_num; i++)
				delete listB_delete[i - 1];
			delete[] listB_delete;
		}
	}
	//若把这些语句放在括号内，当graph_initialized为false时有可能内存泄漏（delete空指针是安全的）
	delete[] vertex_firstA;
	vertex_firstA = nullptr;
	delete[] vertex_firstB;
	vertex_firstB = nullptr;

	//删除邻接表
	if (vertex_first != nullptr)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			while (vertex_first[i - 1] != nullptr)
			{
				listA_line* listA_delete = vertex_first[i - 1];
				vertex_first[i - 1] = vertex_first[i - 1]->line;
				delete listA_delete;
			}
		}
		delete[] vertex_first;
		vertex_first = nullptr;
	}

	//删除顶点标识符
	if (vertex_id != nullptr)
	{
		for (long long i = 1; i <= vertex_num; i++)
			vertex_id[i - 1]->~LIST();
		delete[] vertex_id;
		vertex_id = nullptr;
	}

	//重置图的其他内容
	if (vertex_visited != nullptr)
	{
		delete[] vertex_visited;
		vertex_visited = nullptr;
	}
	if (vertex_content != nullptr)
	{
		delete[] vertex_content;
		vertex_content = nullptr;
	}
	vertex_num = -1;
	line_num = -1;
	graph_directed = false;
	graph_weighted = false;
	graph_initialized = false;
	return;
}

template<typename Type>
GRAPH<Type>& GRAPH<Type>::operator=(const GRAPH& x)
{
	if (x.graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return *this;
	}
	if (SILENCE == false)
		cout << "【提示】GRAPH类的重载的赋值运算符被调用" << endl;
	if (this == &x)
		return *this;
	this->~GRAPH();
	if (x.vertex_num == 0)
	{
		//空图要特殊处理
		vertex_num = x.vertex_num;
		line_num = x.line_num;
		graph_directed = x.graph_directed;
		graph_weighted = x.graph_weighted;
		graph_initialized = x.graph_initialized;
		return *this;
	}

	graph_initialized = x.graph_initialized;
	graph_directed = x.graph_directed;
	graph_weighted = x.graph_weighted;
	line_num = x.line_num;
	vertex_num = x.vertex_num;
	vertex_visited = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = x.vertex_visited[i - 1];
	vertex_content = new Type[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_content[i - 1] = x.vertex_content[i - 1];
	vertex_id = new LIST<char>*[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		//不可以用临时变量+复制构造函数，因为临时变量在括号外会被析构掉
		vertex_id[i - 1] = new LIST<char>(3);
		*vertex_id[i - 1] = *x.vertex_id[i - 1];
	}

	array_matrix = new array_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		array_matrix[i - 1] = new array_line[vertex_num];
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			array_matrix[i - 1][i1 - 1].line_weight = x.array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix[i - 1][i1 - 1].line_exist = x.array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix[i - 1][i1 - 1].line_visited = x.array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix[i - 1][i1 - 1].line_content = x.array_matrix[i - 1][i1 - 1].line_content;
		}
	}

	vertex_first = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_first[i - 1] = nullptr;
	listA_line** last_vertex = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		last_vertex[i - 1] = nullptr;
	for (long long i = 1; i <= vertex_num; i++)
	{
		listA_line* line_ptr = x.vertex_first[i - 1];
		while (line_ptr != nullptr)
		{
			listA_line* new_line = new listA_line;
			new_line->line = nullptr;
			new_line->line_content = line_ptr->line_content;
			new_line->line_visited = line_ptr->line_visited;
			new_line->line_weight = line_ptr->line_weight;
			new_line->vertex = line_ptr->vertex;
			if (vertex_first[i - 1] == nullptr)
				vertex_first[i - 1] = new_line;
			if (last_vertex[i - 1] != nullptr)
				last_vertex[i - 1]->line = new_line;
			last_vertex[i - 1] = new_line;
			line_ptr = line_ptr->line;
		}
	}
	delete[] last_vertex;

	vertex_firstA = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_firstA[i - 1] = nullptr;
	if (graph_directed == true)
	{
		vertex_firstB = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_firstB[i - 1] = nullptr;
	}
	array_2_listB();

	return *this;
}

template<typename Type>
GRAPH<Type>::GRAPH(const GRAPH& x)
{
	if (x.graph_initialized == false)
	{
		graph_initialized = false;
		graph_directed = false;
		graph_weighted = false;
		line_num = -1;
		vertex_num = -1;
		vertex_visited = nullptr;
		vertex_content = nullptr;
		array_matrix = nullptr;
		vertex_first = nullptr;
		vertex_firstA = nullptr;
		vertex_firstB = nullptr;
		vertex_id = nullptr;
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (SILENCE == false)
		cout << "【提示】GRAPH类的复制构造函数被调用" << endl;
	if (x.vertex_num == 0)
	{
		//空图要特殊处理
		vertex_num = x.vertex_num;
		line_num = x.line_num;
		graph_directed = x.graph_directed;
		graph_weighted = x.graph_weighted;
		graph_initialized = x.graph_initialized;
		return;
	}

	graph_initialized = x.graph_initialized;
	graph_directed = x.graph_directed;
	graph_weighted = x.graph_weighted;
	line_num = x.line_num;
	vertex_num = x.vertex_num;
	vertex_visited = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = x.vertex_visited[i - 1];
	vertex_content = new Type[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_content[i - 1] = x.vertex_content[i - 1];
	vertex_id = new LIST<char>*[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		//不可以用临时变量+复制构造函数，因为临时变量在括号外会被析构掉
		vertex_id[i - 1] = new LIST<char>(3);
		*vertex_id[i - 1] = *x.vertex_id[i - 1];
	}

	array_matrix = new array_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		array_matrix[i - 1] = new array_line[vertex_num];
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			array_matrix[i - 1][i1 - 1].line_weight = x.array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix[i - 1][i1 - 1].line_exist = x.array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix[i - 1][i1 - 1].line_visited = x.array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix[i - 1][i1 - 1].line_content = x.array_matrix[i - 1][i1 - 1].line_content;
		}
	}

	vertex_first = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_first[i - 1] = nullptr;
	listA_line** last_vertex = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		last_vertex[i - 1] = nullptr;
	for (long long i = 1; i <= vertex_num; i++)
	{
		listA_line* line_ptr = x.vertex_first[i - 1];
		while (line_ptr != nullptr)
		{
			listA_line* new_line = new listA_line;
			new_line->line = nullptr;
			new_line->line_content = line_ptr->line_content;
			new_line->line_visited = line_ptr->line_visited;
			new_line->line_weight = line_ptr->line_weight;
			new_line->vertex = line_ptr->vertex;
			if (vertex_first[i - 1] == nullptr)
				vertex_first[i - 1] = new_line;
			if (last_vertex[i - 1] != nullptr)
				last_vertex[i - 1]->line = new_line;
			last_vertex[i - 1] = new_line;
			line_ptr = line_ptr->line;
		}
	}
	delete[] last_vertex;

	vertex_firstA = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_firstA[i - 1] = nullptr;
	if (graph_directed == true)
	{
		vertex_firstB = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			vertex_firstB[i - 1] = nullptr;
	}
	array_2_listB();

	return;
}

template<typename Type>
void GRAPH<Type>::array_2_listA()
{
	if (array_matrix == nullptr)
	{
		cout << "\033[1;31m【错误】邻接矩阵不存在，无法将邻接矩阵转换为邻接表\033[0m" << endl;
		return;
	}

	listA_line** last_vertex = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		last_vertex[i - 1] = nullptr;
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)//弧尾或边的第一个顶点
		{
			for (long long i1 = 1; i1 <= vertex_num; i1++)//弧头或边的第二个顶点
			{
				if (array_matrix[i - 1][i1 - 1].line_exist == true)
				{
					listA_line* line_temp = new listA_line;
					line_temp->line = nullptr;
					line_temp->line_content = static_cast<Type>(0);
					line_temp->line_visited = false;
					line_temp->line_weight = array_matrix[i - 1][i1 - 1].line_weight;
					line_temp->vertex = i1;
					if (last_vertex[i - 1] != nullptr)
						last_vertex[i - 1]->line = line_temp;
					last_vertex[i - 1] = line_temp;
					if (vertex_first[i - 1] == nullptr)
						vertex_first[i - 1] = line_temp;
				}
			}
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)//弧尾或边的第一个顶点
		{
			for (long long i1 = 1; i1 <= vertex_num; i1++)//弧头或边的第二个顶点
			{
				if (array_matrix[i - 1][i1 - 1].line_exist == true)
				{
					listA_line* line_temp = new listA_line;
					line_temp->line = nullptr;
					line_temp->line_content = static_cast<Type>(0);
					line_temp->line_visited = false;
					line_temp->line_weight = array_matrix[i - 1][i1 - 1].line_weight;
					line_temp->vertex = i1;
					if (last_vertex[i - 1] != nullptr)
						last_vertex[i - 1]->line = line_temp;
					last_vertex[i - 1] = line_temp;
					if (vertex_first[i - 1] == nullptr)
						vertex_first[i - 1] = line_temp;

					line_temp = new listA_line;
					line_temp->line = nullptr;
					line_temp->line_content = static_cast<Type>(0);
					line_temp->line_visited = false;
					line_temp->line_weight = array_matrix[i - 1][i1 - 1].line_weight;
					line_temp->vertex = i;
					if (last_vertex[i1 - 1] != nullptr)
						last_vertex[i1 - 1]->line = line_temp;
					last_vertex[i1 - 1] = line_temp;
					if (vertex_first[i1 - 1] == nullptr)
						vertex_first[i1 - 1] = line_temp;
				}
			}
		}
	}

	//释放临时内存
	delete[] last_vertex;
	return;
}

template<typename Type>
void GRAPH<Type>::array_2_listB()
{
	if (array_matrix == nullptr)
	{
		cout << "\033[1;31m【错误】邻接矩阵不存在，无法将邻接矩阵转换为十字链表或邻接多重表\033[0m" << endl;
		return;
	}

	listB_line** next_line = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		next_line[i - 1] = nullptr;
	listB_line** next_column = nullptr;
	if (graph_directed == true)
	{
		next_column = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			next_column[i - 1] = nullptr;
	}

	for (long long i = 1; i <= vertex_num; i++)//弧尾或边的第一个顶点
	{
		for (long long i1 = 1; i1 <= vertex_num; i1++)//弧头或边的第二个顶点
		{
			if (array_matrix[i - 1][i1 - 1].line_exist == true)
			{
				listB_line* line_temp = new listB_line;
				line_temp->vertex_A = i;
				line_temp->vertex_B = i1;
				line_temp->line_content = array_matrix[i - 1][i1 - 1].line_content;
				line_temp->line_visited = array_matrix[i - 1][i1 - 1].line_visited;
				line_temp->line_weight = array_matrix[i - 1][i1 - 1].line_weight;
				line_temp->line_A = nullptr;
				line_temp->line_B = nullptr;
				//注意：初始化十字链表/邻接多重表顶点结点的代码不通用
				if (graph_directed == true)
				{
					if (vertex_firstA[i - 1] == nullptr)
						vertex_firstA[i - 1] = line_temp;
					if (vertex_firstB[i1 - 1] == nullptr)
						vertex_firstB[i1 - 1] = line_temp;
				}
				else
				{
					if (vertex_firstA[i - 1] == nullptr)
						vertex_firstA[i - 1] = line_temp;
					if (vertex_firstA[i1 - 1] == nullptr)
						vertex_firstA[i1 - 1] = line_temp;
				}

				//注意：初始化十字链表弧结点/邻接多重表边结点的代码不通用
				if (graph_directed == true)
				{
					if (next_line[i - 1] != nullptr)
						next_line[i - 1]->line_A = line_temp;
					next_line[i - 1] = line_temp;
					if (next_column[i1 - 1] != nullptr)
						next_column[i1 - 1]->line_B = line_temp;
					next_column[i1 - 1] = line_temp;
				}
				else
				{
					if (next_line[i - 1] != nullptr)
					{
						if (next_line[i - 1]->vertex_A == i)
							next_line[i - 1]->line_A = line_temp;
						else
							next_line[i - 1]->line_B = line_temp;
					}
					next_line[i - 1] = line_temp;
					if (next_line[i1 - 1] != nullptr)
					{
						if (next_line[i1 - 1]->vertex_A == i1)
							next_line[i1 - 1]->line_A = line_temp;
						else
							next_line[i1 - 1]->line_B = line_temp;
					}
					next_line[i1 - 1] = line_temp;
				}
			}
		}
	}

	//释放临时内存
	delete[] next_line;
	if (next_column != nullptr)
		delete[] next_column;
	return;
}

template<typename Type>
void GRAPH<Type>::Info() const
{
	cout << "【提示】图的基本信息：" << endl;
	if (graph_initialized == false)
	{
		cout << "【是否已初始化】：否" << endl;
		return;
	}
	else
		cout << "【是否已初始化】：是" << endl;
	if (graph_directed == true)
		cout << "【图的类型】：有向图" << endl;
	else
		cout << "【图的类型】：无向图" << endl;
	cout << "【顶点数量】：" << vertex_num << endl;
	if (graph_directed == true)
		cout << "【弧的数量】：" << line_num << endl;
	else
		cout << "【边的数量】：" << line_num << endl;
	if (vertex_num == 0)
		return;//空图

	cout << "【图的邻接矩阵（边或弧用1表示，其余元素均为0）】：" << endl;
	Display_01();
	cout << "【图的邻接表】：" << endl;
	Display_2();
	if (graph_directed == true)
		cout << "【图的十字链表】：" << endl;
	else
		cout << "【图的邻接多重表】：" << endl;
	Display_3();
	if (Weighted() == true)
	{
		cout << "【边的权值（邻接矩阵格式）】：" << endl;
		Display_weight();
	}
	cout << "【深度优先遍历序列】：";
	DFS();
	cout << "【广度优先遍历序列】：";
	BFS();
	if (graph_directed == false)
	{
		if (Connected() == true)
			cout << "【是否为连通图】：是" << endl;
		else
			cout << "【是否为连通图】：否" << endl;
	}
	else
	{
		if (S_Connected() == true)
			cout << "【是否为强连通图】：是" << endl;
		else
			cout << "【是否为强连通图】：否" << endl;
	}
	if (Weighted() == true)
		cout << "【是否为带权图】：是" << endl;
	else
		cout << "【是否为带权图】：否" << endl;
	if (Has_cycles() == true)
		cout << "【图中是否有环】：是" << endl;
	else
		cout << "【图中是否有环】：否" << endl;


	return;
}

template<typename Type>
void GRAPH<Type>::Display_01() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出邻接矩阵\033[0m" << endl;
		return;
	}
	if (array_matrix == nullptr)
	{
		cout << "\033[1;31m【错误】邻接矩阵不存在，无法输出邻接矩阵\033[0m" << endl;
		return;
	}

	//无向图的邻接矩阵一定是对称矩阵，所以需要特殊处理无向图的输出
	if (graph_directed == false)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Vertex " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				cout << array_matrix[i - 1][i1 - 1].line_exist + array_matrix[i1 - 1][i - 1].line_exist << "  ";
			cout << endl;
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Vertex " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				cout << array_matrix[i - 1][i1 - 1].line_exist << "  ";
			cout << endl;
		}
	}

	return;
}

template<typename Type>
void GRAPH<Type>::Display_2() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出邻接表\033[0m" << endl;
		return;
	}
	if (vertex_first == nullptr)
	{
		cout << "\033[1;31m【错误】邻接表不存在，无法输出邻接表\033[0m" << endl;
		return;
	}

	for (long long i = 1; i <= vertex_num; i++)
	{
		listA_line* line_out = vertex_first[i - 1];
		cout << *vertex_id[i - 1] << " -> ";
		while (line_out != nullptr)
		{
			cout << *vertex_id[line_out->vertex - 1];
			line_out = line_out->line;
			if (line_out != nullptr)
				cout << " -- ";
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void GRAPH<Type>::Display_3() const
{
	if (graph_initialized == false)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】图未初始化，无法输出十字链表\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】图未初始化，无法输出邻接多重表\033[0m" << endl;
		return;
	}
	if (vertex_firstA == nullptr)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】十字链表不存在，无法输出十字链表\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】邻接多重表不存在，无法输出邻接多重表\033[0m" << endl;
		return;
	}

	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			listB_line* line_out = vertex_firstA[i - 1];
			cout << *vertex_id[i - 1] << " -> ";
			while (line_out != nullptr)
			{
				cout << *vertex_id[line_out->vertex_A - 1] << " -- " << *vertex_id[line_out->vertex_B - 1] << "  ";
				line_out = line_out->line_A;
			}
			cout << endl;
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			listB_line* line_out = vertex_firstA[i - 1];
			cout << *vertex_id[i - 1] << " -> ";
			while (line_out != nullptr)
			{
				cout << *vertex_id[line_out->vertex_A - 1] << " -- " << *vertex_id[line_out->vertex_B - 1] << "  ";
				if (line_out->vertex_A == i)
					line_out = line_out->line_A;
				else
					line_out = line_out->line_B;
			}
			cout << endl;
		}
	}
	return;
}

template<typename Type>
void GRAPH<Type>::Display_weight() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法以邻接矩阵格式输出边的权值\033[0m" << endl;
		return;
	}
	if (array_matrix == nullptr)
	{
		cout << "\033[1;31m【错误】邻接矩阵不存在，无法以邻接矩阵格式输出边的权值\033[0m" << endl;
		return;
	}

	//无向图的邻接矩阵一定是对称矩阵，所以需要特殊处理无向图的输出
	if (graph_directed == false)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Weight " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				cout << array_matrix[i - 1][i1 - 1].line_weight + array_matrix[i1 - 1][i - 1].line_weight << "  ";
			cout << endl;
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Weight " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				cout << array_matrix[i - 1][i1 - 1].line_weight << "  ";
			cout << endl;
		}
	}

	return;
}

template<typename Type>
void GRAPH<Type>::DFS() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出图的深度优先遍历序列\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << *vertex_id[0] << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法输出图的深度优先遍历序列\033[0m" << endl;
		return;
	}

	//使用邻接矩阵遍历时，时间复杂度为O(顶点数^2)，使用邻接表遍历时，时间复杂度为O(顶点数+弧或边的数量)
	//所以这里使用邻接表遍历图
	struct stack_search
	{
		long long vertex_pos;
		struct stack_search* next;
	};

	for (long long i = 1; i <= vertex_num; i++)
	{
		if (vertex_visited[i - 1] == false)
		{
			vertex_visited[i - 1] = true;
			cout << *vertex_id[i - 1] << "  ";
			if (vertex_first[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				continue;
			//运行到这里时stack_head一定是nullptr，所以省略选择分支
			stack_search* stack_head = new stack_search;
			stack_head->vertex_pos = i;
			stack_head->next = nullptr;
			while (stack_head != nullptr)
			{
				long long vertex_A = stack_head->vertex_pos;
				//while前的代码相当于《数据结构》中的FirstAdjVex函数
				listA_line* i_line = vertex_first[vertex_A - 1];
				long long i_scan = i_line->vertex;

				while (i_scan >= 0)
				{
					if (vertex_visited[i_scan - 1] == false)
					{
						vertex_visited[i_scan - 1] = true;
						cout << *vertex_id[i_scan - 1] << "  ";
						//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
						if (vertex_first[i_scan - 1] != nullptr)
						{
							//运行到这里时，stack_head一定不是nullptr。省略判断语句
							stack_search* stack_new = new stack_search;
							stack_new->vertex_pos = i_scan;
							stack_new->next = stack_head;
							stack_head = stack_new;
						}
						break;//运行到这里时i_scan非零
					}
					else
					{
						//下面的代码相当于《数据结构》中的NextAdjVex函数
						i_line = i_line->line;
						if (i_line != nullptr)
							i_scan = i_line->vertex;
						else
							i_scan = -1;
					}
				}
				if (i_scan >= 0)
					continue;
				if (stack_head->next == nullptr)
				{
					delete stack_head;
					stack_head = nullptr;
				}
				else
				{
					stack_search* stack_delete = stack_head;
					stack_head = stack_head->next;
					delete stack_delete;
				}
			}
		}
	}
	cout << endl;

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	return;
}

template<typename Type>
void GRAPH<Type>::DFS_LE() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出图的深度优先遍历序列\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << *vertex_id[0] << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法输出图的深度优先遍历序列\033[0m" << endl;
		return;
	}

	struct stack_search
	{
		long long vertex_pos;
		struct stack_search* next;
	};

	for (long long i = 1; i <= vertex_num; i++)
	{
		if (vertex_visited[i - 1] == false)
		{
			vertex_visited[i - 1] = true;
			cout << *vertex_id[i - 1] << "  ";
			if (vertex_firstA[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				continue;
			//运行到这里时stack_head一定是nullptr，所以省略选择分支
			stack_search* stack_head = new stack_search;
			stack_head->vertex_pos = i;
			stack_head->next = nullptr;
			while (stack_head != nullptr)
			{
				long long vertex_A = stack_head->vertex_pos;
				//while前的代码相当于《数据结构》中的FirstAdjVex函数
				listB_line* i_line = vertex_firstA[vertex_A - 1];
				long long i_scan = -1;
				if (graph_directed == true || i_line->vertex_A == vertex_A)
					i_scan = i_line->vertex_B;
				else
					i_scan = i_line->vertex_A;

				while (i_scan >= 0)
				{
					if (vertex_visited[i_scan - 1] == false)
					{
						vertex_visited[i_scan - 1] = true;
						cout << *vertex_id[i_scan - 1] << "  ";
						//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
						if (vertex_firstA[i_scan - 1] != nullptr)
						{
							//运行到这里时，stack_head一定不是nullptr。省略判断语句
							stack_search* stack_new = new stack_search;
							stack_new->vertex_pos = i_scan;
							stack_new->next = stack_head;
							stack_head = stack_new;
						}
						break;//运行到这里时i_scan非零
					}
					else
					{
						//下面的代码相当于《数据结构》中的NextAdjVex函数
						if (graph_directed == true)
						{
							if (i_line->line_A != nullptr)
							{
								i_line = i_line->line_A;
								i_scan = i_line->vertex_B;
							}
							else
								i_scan = -1;
						}
						else
						{
							if (i_line->vertex_A == vertex_A)
								i_line = i_line->line_A;
							else
								i_line = i_line->line_B;
							if (i_line != nullptr)
							{
								if (i_line->vertex_A == vertex_A)
									i_scan = i_line->vertex_B;
								else
									i_scan = i_line->vertex_A;
							}
							else
								i_scan = -1;
						}
					}
				}
				if (i_scan >= 0)
					continue;

				if (stack_head->next == nullptr)
				{
					delete stack_head;
					stack_head = nullptr;
				}
				else
				{
					stack_search* stack_delete = stack_head;
					stack_head = stack_head->next;
					delete stack_delete;
				}
			}
		}
	}
	cout << endl;

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	return;
}

template<typename Type>
void GRAPH<Type>::BFS() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出图的广度优先遍历序列\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << *vertex_id[0] << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法输出图的广度优先遍历序列\033[0m" << endl;
		return;
	}

	//使用邻接矩阵遍历时，时间复杂度为O(顶点数^2)，使用邻接表遍历时，时间复杂度为O(顶点数+弧或边的数量)
	//所以这里使用邻接表遍历图
	//【注意】：这不是普通的队列，在本函数中不需要prior指针
	struct queue_search
	{
		long long vertex_pos;
		struct queue_search* next;
	};

	for (long long i = 1; i <= vertex_num; i++)
	{
		if (vertex_visited[i - 1] == false)
		{
			vertex_visited[i - 1] = true;
			cout << *vertex_id[i - 1] << "  ";
			if (vertex_first[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				continue;
			//运行到这里时queue_head一定是nullptr，所以省略选择分支
			queue_search* queue_head = new queue_search;
			queue_head->vertex_pos = i;
			queue_head->next = nullptr;
			queue_search* queue_tail = queue_head;
			while (queue_head != nullptr)
			{
				long long vertex_A = queue_head->vertex_pos;
				if (queue_head->next == nullptr)
				{
					delete queue_head;
					queue_head = nullptr;
					queue_tail = nullptr;
				}
				else
				{
					queue_search* queue_delete = queue_head;
					queue_head = queue_head->next;
					delete queue_delete;
				}

				//while前的代码相当于《数据结构》中的FirstAdjVex函数
				listA_line* i_line = vertex_first[vertex_A - 1];
				long long i_scan = i_line->vertex;
				while (i_scan >= 0)
				{
					if (vertex_visited[i_scan - 1] == false)
					{
						vertex_visited[i_scan - 1] = true;
						cout << *vertex_id[i_scan - 1] << "  ";
						//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
						if (vertex_first[i_scan - 1] != nullptr)
						{
							if (queue_head == nullptr)
							{
								queue_head = new queue_search;
								queue_head->vertex_pos = i_scan;
								queue_head->next = nullptr;
								queue_tail = queue_head;
							}
							else
							{
								queue_tail->next = new queue_search;
								queue_tail->next->vertex_pos = i_scan;
								queue_tail->next->next = nullptr;
								queue_tail = queue_tail->next;
							}
						}
					}
					//下面的代码相当于《数据结构》中的NextAdjVex函数
					i_line = i_line->line;
					if (i_line != nullptr)
						i_scan = i_line->vertex;
					else
						i_scan = -1;
				}
			}
		}
	}
	cout << endl;

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	return;
}

template<typename Type>
void GRAPH<Type>::BFS_LE() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法输出图的广度优先遍历序列\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << *vertex_id[0] << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法输出图的广度优先遍历序列\033[0m" << endl;
		return;
	}

	//【注意】：这不是普通的队列，在本函数中不需要prior指针
	struct queue_search
	{
		long long vertex_pos;
		struct queue_search* next;
	};

	for (long long i = 1; i <= vertex_num; i++)
	{
		if (vertex_visited[i - 1] == false)
		{
			vertex_visited[i - 1] = true;
			cout << *vertex_id[i - 1] << "  ";
			if (vertex_firstA[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				continue;
			//运行到这里时queue_head一定是nullptr，所以省略选择分支
			queue_search* queue_head = new queue_search;
			queue_head->vertex_pos = i;
			queue_head->next = nullptr;
			queue_search* queue_tail = queue_head;
			while (queue_head != nullptr)
			{
				long long vertex_A = queue_head->vertex_pos;
				if (queue_head->next == nullptr)
				{
					delete queue_head;
					queue_head = nullptr;
					queue_tail = nullptr;
				}
				else
				{
					queue_search* queue_delete = queue_head;
					queue_head = queue_head->next;
					delete queue_delete;
				}

				//while前的代码相当于《数据结构》中的FirstAdjVex函数
				listB_line* i_line = vertex_firstA[vertex_A - 1];
				long long i_scan = -1;
				if (graph_directed == true || i_line->vertex_A == vertex_A)
					i_scan = i_line->vertex_B;
				else
					i_scan = i_line->vertex_A;
				while (i_scan >= 0)
				{
					if (vertex_visited[i_scan - 1] == false)
					{
						vertex_visited[i_scan - 1] = true;
						cout << *vertex_id[i_scan - 1] << "  ";
						//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
						if (vertex_firstA[i_scan - 1] != nullptr)
						{
							if (queue_head == nullptr)
							{
								queue_head = new queue_search;
								queue_head->vertex_pos = i_scan;
								queue_head->next = nullptr;
								queue_tail = queue_head;
							}
							else
							{
								queue_tail->next = new queue_search;
								queue_tail->next->vertex_pos = i_scan;
								queue_tail->next->next = nullptr;
								queue_tail = queue_tail->next;
							}
						}
					}
					//下面的代码相当于《数据结构》中的NextAdjVex函数
					if (graph_directed == true)
					{
						if (i_line->line_A != nullptr)
						{
							i_line = i_line->line_A;
							i_scan = i_line->vertex_B;
						}
						else
							i_scan = -1;
					}
					else
					{
						if (i_line->vertex_A == vertex_A)
							i_line = i_line->line_A;
						else
							i_line = i_line->line_B;
						if (i_line != nullptr)
						{
							if (i_line->vertex_A == vertex_A)
								i_scan = i_line->vertex_B;
							else
								i_scan = i_line->vertex_A;
						}
						else
							i_scan = -1;
					}
				}
			}
		}
	}
	cout << endl;

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	return;
}

template<typename Type>
void GRAPH<Type>::Silence_T()
{
	SILENCE = true;
	return;
}

template<typename Type>
void GRAPH<Type>::Silence_F()
{
	SILENCE = false;
	return;
}

template<typename Type>
void GRAPH<Type>::Repair_GRAPH()
{
	//将未初始化的图转换为已初始化的空图
	if (graph_initialized == true)
	{
		cout << "\033[1;31m【错误】图已初始化，无需修复\033[0m" << endl;
		return;
	}
	this->~GRAPH();
	//析构函数执行后vertex_num和line_num均为-1，graph_initialized为false，graph_directed和graph_weighted均为false
	//所以此处不需要改动graph_directed和graph_weighted
	vertex_num = 0;
	line_num = 0;
	graph_initialized = true;
	return;
}

template<typename Type>
void GRAPH<Type>::Clear_GRAPH()
{
	//将已初始化的图清空，变成空图
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}
	this->~GRAPH();
	//析构函数执行后vertex_num和line_num均为-1，graph_initialized为false，graph_directed和graph_weighted均为false
	//所以此处不需要改动graph_directed和graph_weighted
	vertex_num = 0;
	line_num = 0;
	graph_initialized = true;
	return;
}

template<typename Type>
void GRAPH<Type>::Add_vertex()
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}

	cout << "【提示】请输入要新增的顶点的名称：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		cout << "\033[1;31m【错误】输入流的长度为0，无法新增结点\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}
	if (vertex_num == 0)
	{
		vertex_num = 1;
		vertex_visited = new bool[vertex_num];
		vertex_visited[0] = false;
		vertex_content = new Type[vertex_num];
		vertex_content[0] = static_cast<Type>(0);
		array_matrix = new array_line * [vertex_num];
		array_matrix[0] = new array_line[vertex_num];
		array_matrix[0][0].line_weight = 0.0;
		array_matrix[0][0].line_exist = false;
		array_matrix[0][0].line_visited = false;
		array_matrix[0][0].line_content = static_cast<Type>(0);
		vertex_first = new listA_line * [vertex_num];
		vertex_first[0] = nullptr;
		vertex_firstA = new listB_line * [vertex_num];
		vertex_firstA[0] = nullptr;
		if (graph_directed == true)
		{
			vertex_firstB = new listB_line * [vertex_num];
			vertex_firstB[0] = nullptr;
		}
		vertex_id = new LIST<char>*[vertex_num];
		vertex_id[0] = new LIST<char>(3);
		*vertex_id[0] = input;
		return;
	}
	long long pos = -1;
	for (long long i = 1; i <= vertex_num; i++)
	{
		if (*vertex_id[i - 1] == input)
		{
			pos = i;
			break;
		}
	}
	if (pos != -1)
	{
		cout << "\033[1;31m【错误】该结点已存在，无法新增结点\033[0m" << endl;
		return;
	}
	vertex_num = vertex_num + 1;

	bool* vertex_visited1 = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
		vertex_visited1[i - 1] = vertex_visited[i - 1];
	vertex_visited1[vertex_num - 1] = false;
	delete[] vertex_visited;
	vertex_visited = vertex_visited1;

	Type* vertex_content1 = new Type[vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
		vertex_content1[i - 1] = vertex_content[i - 1];
	vertex_content1[vertex_num - 1] = static_cast<Type>(0);
	delete[] vertex_content;
	vertex_content = vertex_content1;

	array_line** array_matrix1 = new array_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		array_matrix1[i - 1] = new array_line[vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
	{
		for (long long i1 = 1; i1 <= vertex_num - 1; i1++)
		{
			array_matrix1[i - 1][i1 - 1].line_weight = array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix1[i - 1][i1 - 1].line_exist = array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix1[i - 1][i1 - 1].line_visited = array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix1[i - 1][i1 - 1].line_content = array_matrix[i - 1][i1 - 1].line_content;
		}
		array_matrix1[i - 1][vertex_num - 1].line_weight = 0.0;
		array_matrix1[i - 1][vertex_num - 1].line_exist = false;
		array_matrix1[i - 1][vertex_num - 1].line_visited = false;
		array_matrix1[i - 1][vertex_num - 1].line_content = static_cast<Type>(0);
	}
	for (long long i = 1; i <= vertex_num; i++)
	{
		array_matrix1[vertex_num - 1][i - 1].line_weight = 0.0;
		array_matrix1[vertex_num - 1][i - 1].line_exist = false;
		array_matrix1[vertex_num - 1][i - 1].line_visited = false;
		array_matrix1[vertex_num - 1][i - 1].line_content = static_cast<Type>(0);
	}
	for (long long i = 1; i <= vertex_num - 1; i++)
		delete[] array_matrix[i - 1];
	delete[] array_matrix;
	array_matrix = array_matrix1;

	listA_line** vertex_first1 = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
		vertex_first1[i - 1] = vertex_first[i - 1];
	vertex_first1[vertex_num - 1] = nullptr;
	delete[] vertex_first;
	vertex_first = vertex_first1;

	listB_line** vertex_firstA1 = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
		vertex_firstA1[i - 1] = vertex_firstA[i - 1];
	vertex_firstA1[vertex_num - 1] = nullptr;
	delete[] vertex_firstA;
	vertex_firstA = vertex_firstA1;

	if (graph_directed == true)
	{
		listB_line** vertex_firstB1 = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num - 1; i++)
			vertex_firstB1[i - 1] = vertex_firstB[i - 1];
		vertex_firstB1[vertex_num - 1] = nullptr;
		delete[] vertex_firstB;
		vertex_firstB = vertex_firstB1;
	}

	LIST<char>** vertex_id1 = new LIST<char>*[vertex_num];
	for (long long i = 1; i <= vertex_num - 1; i++)
		vertex_id1[i - 1] = vertex_id[i - 1];
	vertex_id1[vertex_num - 1] = new LIST<char>(3);
	*vertex_id1[vertex_num - 1] = input;
	delete[] vertex_id;
	vertex_id = vertex_id1;

	return;
}

template<typename Type>
void GRAPH<Type>::Delete_vertex()
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图中顶点的数量为0，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		//只有一个顶点时，无需输入顶点名称
		//备份变量
		bool this_silence = SILENCE;
		bool this_directed = graph_directed;
		//重置其它部分
		this->~GRAPH();
		Repair_GRAPH();
		//还原变量
		SILENCE = this_silence;
		graph_directed = this_directed;
		//只有1个顶点的图只可以是无权图。所以不备份也不还原graph_weighted变量
		return;
	}

	cout << "【提示】请输入要删除的顶点的名称：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		cout << "\033[1;31m【错误】输入流的长度为0，无法删除顶点\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}
	long long pos = -1;
	for (long long i = 1; i <= vertex_num; i++)
	{
		if (*vertex_id[i - 1] == input)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
	{
		cout << "\033[1;31m【错误】该顶点不存在，无法删除顶点\033[0m" << endl;
		return;
	}

	//若为有向图，对于所有以待删除结点为弧头的弧，记录这些弧的弧尾结点编号；若为无向图，记录所有与待删除结点有连接的结点的编号
	LIST<long long> vertex_orderA(3);
	//若为有向图，对于所有以待删除结点为弧尾的弧，记录这些弧的弧头结点编号；若为无向图，该线性表为空
	LIST<long long> vertex_orderB(3);
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			if (array_matrix[i - 1][pos - 1].line_exist == true)
				vertex_orderA += i;
			if (array_matrix[pos - 1][i - 1].line_exist == true)
				vertex_orderB += i;
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			if (array_matrix[pos - 1][i - 1].line_exist == true)
				vertex_orderA += i;
			else if (array_matrix[i - 1][pos - 1].line_exist == true)
				vertex_orderA += i;
		}
	}

	//更改邻接矩阵
	array_line** array_matrix1 = new array_line * [vertex_num - 1];
	for (long long i = 1; i <= vertex_num - 1; i++)
		array_matrix1[i - 1] = new array_line[vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
	{
		for (long long i1 = 1; i1 <= pos - 1; i1++)
		{
			array_matrix1[i - 1][i1 - 1].line_weight = array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix1[i - 1][i1 - 1].line_exist = array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix1[i - 1][i1 - 1].line_visited = array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix1[i - 1][i1 - 1].line_content = array_matrix[i - 1][i1 - 1].line_content;
		}
		for (long long i1 = pos + 1; i1 <= vertex_num; i1++)
		{
			array_matrix1[i - 1][i1 - 2].line_weight = array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix1[i - 1][i1 - 2].line_exist = array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix1[i - 1][i1 - 2].line_visited = array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix1[i - 1][i1 - 2].line_content = array_matrix[i - 1][i1 - 1].line_content;
		}
	}
	for (long long i = pos + 1; i <= vertex_num; i++)
	{
		for (long long i1 = 1; i1 <= pos - 1; i1++)
		{
			array_matrix1[i - 2][i1 - 1].line_weight = array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix1[i - 2][i1 - 1].line_exist = array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix1[i - 2][i1 - 1].line_visited = array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix1[i - 2][i1 - 1].line_content = array_matrix[i - 1][i1 - 1].line_content;
		}
		for (long long i1 = pos + 1; i1 <= vertex_num; i1++)
		{
			array_matrix1[i - 2][i1 - 2].line_weight = array_matrix[i - 1][i1 - 1].line_weight;
			array_matrix1[i - 2][i1 - 2].line_exist = array_matrix[i - 1][i1 - 1].line_exist;
			array_matrix1[i - 2][i1 - 2].line_visited = array_matrix[i - 1][i1 - 1].line_visited;
			array_matrix1[i - 2][i1 - 2].line_content = array_matrix[i - 1][i1 - 1].line_content;
		}
	}
	for (long long i = 1; i <= vertex_num; i++)
		delete[] array_matrix[i - 1];
	delete[] array_matrix;
	array_matrix = array_matrix1;

	//更改邻接表
	//删除所有以待删除结点为弧头/第一结点的弧或边
	for (long long i = 1; i <= vertex_orderA.Listlength(); i++)
	{
		long long temp = vertex_orderA[i - 1];
		if (vertex_first[temp - 1]->vertex == pos)
		{
			listA_line* line_delete = vertex_first[temp - 1];
			vertex_first[temp - 1] = vertex_first[temp - 1]->line;
			delete line_delete;
		}
		else
		{
			listA_line* line_temp = vertex_first[temp - 1];
			while (line_temp->line->vertex != pos)
				line_temp = line_temp->line;
			listA_line* line_delete = line_temp->line;
			line_temp->line = line_temp->line->line;
			delete line_delete;
		}
	}
	//删除所有以待删除结点为弧尾/第二结点的弧或边
	listA_line* line_temp = vertex_first[pos - 1];
	while (line_temp != nullptr)
	{
		listA_line* line_delete = line_temp;
		line_temp = line_temp->line;
		delete line_delete;
	}
	listA_line** vertex_first1 = new listA_line * [vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
		vertex_first1[i - 1] = vertex_first[i - 1];
	for (long long i = pos + 1; i <= vertex_num; i++)
		vertex_first1[i - 2] = vertex_first[i - 1];
	delete[] vertex_first;
	vertex_first = vertex_first1;
	//更改待删除结点后的全部结点的序号。如果不进行这步，图的顶点编号会出错
	for (long long i = 1; i <= vertex_num - 1; i++)
	{
		listA_line* line_tempX = vertex_first[i - 1];
		while (line_tempX != nullptr)
		{
			if (line_tempX->vertex > pos)
				line_tempX->vertex = line_tempX->vertex - 1;
			line_tempX = line_tempX->line;
		}
	}

	//更改十字链表和邻接多重表
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_orderA.Listlength(); i++)
		{
			long long temp = vertex_orderA[i - 1];
			if (vertex_firstA[temp - 1]->vertex_B == pos)
			{
				listB_line* line_delete = vertex_firstA[temp - 1];
				vertex_firstA[temp - 1] = vertex_firstA[temp - 1]->line_A;
				delete line_delete;
			}
			else
			{
				listB_line* line_tempX = vertex_firstA[temp - 1];
				while (line_tempX->line_A->vertex_B != pos)
					line_tempX = line_tempX->line_A;
				listB_line* line_delete = line_tempX->line_A;
				line_tempX->line_A = line_tempX->line_A->line_A;
				delete line_delete;
			}
		}
		for (long long i = 1; i <= vertex_orderB.Listlength(); i++)
		{
			long long temp = vertex_orderB[i - 1];
			if (vertex_firstB[temp - 1]->vertex_A == pos)
			{
				listB_line* line_delete = vertex_firstB[temp - 1];
				vertex_firstB[temp - 1] = vertex_firstB[temp - 1]->line_B;
				delete line_delete;
			}
			else
			{
				listB_line* line_tempX = vertex_firstB[temp - 1];
				while (line_tempX->line_B->vertex_A != pos)
					line_tempX = line_tempX->line_B;
				listB_line* line_delete = line_tempX->line_B;
				line_tempX->line_B = line_tempX->line_B->line_B;
				delete line_delete;
			}
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_orderA.Listlength(); i++)
		{
			long long temp = vertex_orderA[i - 1];
			if (vertex_firstA[temp - 1]->vertex_A == pos)
			{
				listB_line* line_delete = vertex_firstA[temp - 1];
				vertex_firstA[temp - 1] = vertex_firstA[temp - 1]->line_B;
				delete line_delete;
			}
			else if (vertex_firstA[temp - 1]->vertex_B == pos)
			{
				listB_line* line_delete = vertex_firstA[temp - 1];
				vertex_firstA[temp - 1] = vertex_firstA[temp - 1]->line_A;
				delete line_delete;
			}
			else
			{
				listB_line* line_tempX = vertex_firstA[temp - 1];
				while (true)
				{
					if (line_tempX->vertex_A == temp)
					{
						if (line_tempX->line_A->vertex_A == pos)
						{
							listB_line* line_delete = line_tempX->line_A;
							line_tempX->line_A = line_tempX->line_A->line_B;
							delete line_delete;
							break;
						}
						else if (line_tempX->line_A->vertex_B == pos)
						{
							listB_line* line_delete = line_tempX->line_A;
							line_tempX->line_A = line_tempX->line_A->line_A;
							delete line_delete;
							break;
						}
						else
							line_tempX = line_tempX->line_A;
					}
					else
					{
						if (line_tempX->line_B->vertex_A == pos)
						{
							listB_line* line_delete = line_tempX->line_B;
							line_tempX->line_B = line_tempX->line_B->line_B;
							delete line_delete;
							break;
						}
						else if (line_tempX->line_B->vertex_B == pos)
						{
							listB_line* line_delete = line_tempX->line_B;
							line_tempX->line_B = line_tempX->line_B->line_A;
							delete line_delete;
							break;
						}
						else
							line_tempX = line_tempX->line_B;
					}
				}
			}
		}
	}
	listB_line** vertex_firstA1 = new listB_line * [vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
		vertex_firstA1[i - 1] = vertex_firstA[i - 1];
	for (long long i = pos + 1; i <= vertex_num; i++)
		vertex_firstA1[i - 2] = vertex_firstA[i - 1];
	delete[] vertex_firstA;
	vertex_firstA = vertex_firstA1;
	if (graph_directed == true)
	{
		listB_line** vertex_firstB1 = new listB_line * [vertex_num - 1];
		for (long long i = 1; i <= pos - 1; i++)
			vertex_firstB1[i - 1] = vertex_firstB[i - 1];
		for (long long i = pos + 1; i <= vertex_num; i++)
			vertex_firstB1[i - 2] = vertex_firstB[i - 1];
		delete[] vertex_firstB;
		vertex_firstB = vertex_firstB1;
	}
	//更改待删除结点后的全部结点的序号。如果不进行这步，图的顶点编号会出错
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num - 1; i++)
		{
			listB_line* line_tempX = vertex_firstA[i - 1];
			while (line_tempX != nullptr)
			{
				if (line_tempX->vertex_A > pos)
					line_tempX->vertex_A = line_tempX->vertex_A - 1;
				if (line_tempX->vertex_B > pos)
					line_tempX->vertex_B = line_tempX->vertex_B - 1;
				line_tempX = line_tempX->line_A;
			}
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num - 1; i++)
		{
			listB_line* line_tempX = vertex_firstA[i - 1];
			while (line_tempX != nullptr)
			{
				long long compare = -1;
				if (i < pos)
					compare = i;
				else
					compare = i + 1;
				if (line_tempX->vertex_A == compare)
				{
					if (line_tempX->vertex_A > pos)
						line_tempX->vertex_A = line_tempX->vertex_A - 1;
					line_tempX = line_tempX->line_A;
				}
				else
				{
					if (line_tempX->vertex_B > pos)
						line_tempX->vertex_B = line_tempX->vertex_B - 1;
					line_tempX = line_tempX->line_B;
				}
			}
		}
	}

	bool* vertex_visited1 = new bool[vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
		vertex_visited1[i - 1] = vertex_visited[i - 1];
	for (long long i = pos + 1; i <= vertex_num; i++)
		vertex_visited1[i - 2] = vertex_visited[i - 1];
	delete[] vertex_visited;
	vertex_visited = vertex_visited1;

	Type* vertex_content1 = new Type[vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
		vertex_content1[i - 1] = vertex_content[i - 1];
	for (long long i = pos + 1; i <= vertex_num; i++)
		vertex_content1[i - 2] = vertex_content[i - 1];
	delete[] vertex_content;
	vertex_content = vertex_content1;

	LIST<char>** vertex_id1 = new LIST<char>*[vertex_num - 1];
	for (long long i = 1; i <= pos - 1; i++)
	{
		vertex_id1[i - 1] = new LIST<char>(3);
		*vertex_id1[i - 1] = *vertex_id[i - 1];
	}
	for (long long i = pos + 1; i <= vertex_num; i++)
	{
		vertex_id1[i - 2] = new LIST<char>(3);
		*vertex_id1[i - 2] = *vertex_id[i - 1];
	}
	for (long long i = 1; i <= vertex_num; i++)
		vertex_id[i - 1]->~LIST();
	delete[] vertex_id;
	vertex_id = vertex_id1;

	if (graph_directed == true)
	{
		line_num = line_num - vertex_orderA.Listlength();
		line_num = line_num - vertex_orderB.Listlength();
	}
	else
		line_num = line_num - vertex_orderA.Listlength();
	vertex_num = vertex_num - 1;
	if (vertex_num == 1)
		graph_weighted = false;//只有1个顶点的图只可以是无权图

	return;
}

template<typename Type>
void GRAPH<Type>::Add_line()
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (vertex_num <= 1)
	{
		cout << "\033[1;31m【错误】图中顶点的数量少于2，无法执行任何操作\033[0m" << endl;
		return;
	}

	if (graph_directed == true)
		cout << "【提示】请以  顶点A'顶点B  格式输入要插入的弧（输入规则与默认构造函数相同）：" << endl;
	else
		cout << "【提示】请以  顶点A'顶点B  格式输入要插入的边（输入规则与默认构造函数相同）：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】输入流的长度为0，无法新增弧\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】输入流的长度为0，无法新增边\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}

	//若为带权图，需要额外输入新增的弧或边的权值
	long double new_weight = 0.0;
	if (graph_weighted == true)
	{
		LIST<char> input_x(3);
		cout << "【提示】由于图是带权图，需要额外输入新增的弧或边的权值。权值可以是小数但必须>0： ";
		bool input_success = false;
		while (input_success == false)
		{
			char STREAM_TEMP = '\0';
			cin.get(STREAM_TEMP);
			if ((int)STREAM_TEMP == 10)//输入流长度为0
			{
				cout << "\033[1;31m【错误】输入流长度为0，注意权值可以是小数但必须>0。请重新输入权值： \033[0m";
				continue;
			}
			do
			{
				input_x += STREAM_TEMP;
				input_x.Smart_expand();
				cin.get(STREAM_TEMP);
			} while ((int)STREAM_TEMP != 10);
			char* converted_char = input_x.Char_array(false);
			new_weight = strtold(converted_char, nullptr);
			delete[] converted_char;
			input_x.Clearlist();
			if (new_weight <= 0)
				cout << "\033[1;31m【错误】输入的权值<=0，注意权值可以是小数但必须>0。请重新输入权值： \033[0m";
			else
				input_success = true;
		}
	}

	//将两个顶点分开
	LIST<char> line_A(3);
	LIST<char> line_B(3);
	if (input.Getelement(1) == '\'')//弧或边的第一个顶点名称为空
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】弧的第一个顶点名称为空，无法新增弧\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】边的第一个顶点名称为空，无法新增边\033[0m" << endl;
		return;
	}
	int split_count = 0;
	long long line_split_pos = 0;
	for (long long i1 = 2; i1 <= input.Listlength(); i1++)//顶点数量计数
	{
		if (input.Getelement(i1) == '\'' && input.Getelement(i1 - 1) != '|')
		{
			split_count = split_count + 1;
			line_split_pos = i1;
		}
	}
	if (line_split_pos == input.Listlength())//弧或边的第二个顶点名称为空
	{
		cout << "\033[1;31m【错误】弧或边的第二个顶点名称为空，无法新增弧或边\033[0m" << endl;
		return;
	}
	if (split_count > 1)//弧或边的顶点数量>=3
	{
		cout << "\033[1;31m【错误】输入的弧或边序列中，某条弧或边的顶点数量>=3，无法新增弧或边\033[0m" << endl;
		return;
	}
	if (split_count == 0)//弧或边只有一个顶点
	{
		cout << "\033[1;31m【错误】弧或边只有一个顶点，无法新增弧或边\033[0m" << endl;
		return;
	}
	long long length_A = line_split_pos - 1;
	long long length_B = input.Listlength() - line_split_pos;
	line_A = input.Substring(1, length_A);//弧或边的第一顶点
	line_B = input.Substring(line_split_pos + 1, length_B);//弧或边的第二顶点

	//还原两个顶点的名称
	for (long long i1 = line_A.Listlength() - 1; i1 >= 1; i1--)
	{
		if (line_A[i1 - 1] == '|')
		{
			if (line_A[i1] == '\'')
				line_A.Listdelete(i1);
			else if (line_A[i1] == ']')
				line_A.Listdelete(i1 + 1);
			else
			{
				cout << "\033[1;31m【错误】输入的弧或边序列中，转义字符的使用有误，无法新增弧或边\033[0m" << endl;
				return;
			}
		}
	}
	for (long long i1 = line_B.Listlength() - 1; i1 >= 1; i1--)
	{
		if (line_B[i1 - 1] == '|')
		{
			if (line_B[i1] == '\'')
				line_B.Listdelete(i1);
			else if (line_B[i1] == ']')
				line_B.Listdelete(i1 + 1);
			else
			{
				cout << "\033[1;31m【错误】输入的弧或边序列中，转义字符的使用有误，无法新增弧或边\033[0m" << endl;
				return;
			}
		}
	}

	//写入图的邻接矩阵
	long long pos_A = -1;
	for (long long i1 = 1; i1 <= vertex_num; i1++)
	{
		if (*vertex_id[i1 - 1] == line_A)
			pos_A = i1;
	}
	long long pos_B = -1;
	for (long long i1 = 1; i1 <= vertex_num; i1++)
	{
		if (*vertex_id[i1 - 1] == line_B)
			pos_B = i1;
	}
	if (pos_A == -1 || pos_B == -1)
	{
		cout << "\033[1;31m【错误】输入的弧或边序列中存在一个与顶点序列中任何顶点均不同的顶点，无法新增弧或边\033[0m" << endl;
		return;
	}
	if (array_matrix[pos_A - 1][pos_B - 1].line_exist == true)
	{
		cout << "\033[1;31m【错误】该弧或边已存在\033[0m" << endl;
		return;
	}
	//无向图(A-B,B-A)重复边检测
	if (array_matrix[pos_B - 1][pos_A - 1].line_exist == true && graph_directed == false)
	{
		cout << "\033[1;31m【错误】输入的弧或边序列中，存在重复的弧或边，无法新增弧或边\033[0m" << endl;
		return;
	}
	array_matrix[pos_A - 1][pos_B - 1].line_exist = true;
	array_matrix[pos_A - 1][pos_B - 1].line_weight = new_weight;
	line_num = line_num + 1;

	//邻接表
	//有向图只插入A-B
	listA_line* lineA_addA = new listA_line;
	lineA_addA->vertex = pos_B;
	lineA_addA->line = nullptr;
	lineA_addA->line_weight = new_weight;
	lineA_addA->line_visited = false;
	lineA_addA->line_content = static_cast<Type>(0);
	if (vertex_first[pos_A - 1] == nullptr)
		vertex_first[pos_A - 1] = lineA_addA;
	else
	{
		listA_line* lineA_ptr = vertex_first[pos_A - 1];
		while (lineA_ptr->line != nullptr)
			lineA_ptr = lineA_ptr->line;
		lineA_ptr->line = lineA_addA;
	}
	if (graph_directed == false)
	{
		//插入A-B,B-A
		listA_line* lineA_addB = new listA_line;
		lineA_addB->vertex = pos_A;
		lineA_addB->line = nullptr;
		lineA_addB->line_weight = new_weight;
		lineA_addB->line_visited = false;
		lineA_addB->line_content = static_cast<Type>(0);
		if (vertex_first[pos_B - 1] == nullptr)
			vertex_first[pos_B - 1] = lineA_addB;
		else
		{
			listA_line* lineB_ptr = vertex_first[pos_B - 1];
			while (lineB_ptr->line != nullptr)
				lineB_ptr = lineB_ptr->line;
			lineB_ptr->line = lineA_addB;
		}
	}

	//十字链表和邻接多重表
	listB_line* lineB_add = new listB_line;
	lineB_add->vertex_A = pos_A;
	lineB_add->vertex_B = pos_B;
	lineB_add->line_A = nullptr;
	lineB_add->line_B = nullptr;
	lineB_add->line_weight = new_weight;
	lineB_add->line_visited = false;
	lineB_add->line_content = static_cast<Type>(0);
	if (graph_directed == true)
	{
		if (vertex_firstA[pos_A - 1] == nullptr)
			vertex_firstA[pos_A - 1] = lineB_add;
		else
		{
			listB_line* line_ptr = vertex_firstA[pos_A - 1];
			while (line_ptr->line_A != nullptr)
				line_ptr = line_ptr->line_A;
			line_ptr->line_A = lineB_add;
		}
		if (vertex_firstB[pos_B - 1] == nullptr)
			vertex_firstB[pos_B - 1] = lineB_add;
		else
		{
			listB_line* line_ptr = vertex_firstB[pos_B - 1];
			while (line_ptr->line_B != nullptr)
				line_ptr = line_ptr->line_B;
			line_ptr->line_B = lineB_add;
		}
	}
	else
	{
		if (vertex_firstA[pos_A - 1] == nullptr)
			vertex_firstA[pos_A - 1] = lineB_add;
		else
		{
			listB_line* line_ptr = vertex_firstA[pos_A - 1];
			int found = 2;
			while (found != 0)
			{
				if (line_ptr->vertex_A == pos_A && line_ptr->line_A != nullptr)
				{
					line_ptr = line_ptr->line_A;
					found = -1;
				}
				else if (line_ptr->vertex_B == pos_A && line_ptr->line_B != nullptr)
				{
					line_ptr = line_ptr->line_B;
					found = 1;
				}
				else
					found = 0;
			}
			if (line_ptr->vertex_A == pos_A)
				line_ptr->line_A = lineB_add;
			else
				line_ptr->line_B = lineB_add;
		}
		if (vertex_firstA[pos_B - 1] == nullptr)
			vertex_firstA[pos_B - 1] = lineB_add;
		else
		{
			listB_line* line_ptr = vertex_firstA[pos_B - 1];
			int found = 2;
			while (found != 0)
			{
				if (line_ptr->vertex_A == pos_B && line_ptr->line_A != nullptr)
				{
					line_ptr = line_ptr->line_A;
					found = -1;
				}
				else if (line_ptr->vertex_B == pos_B && line_ptr->line_B != nullptr)
				{
					line_ptr = line_ptr->line_B;
					found = 1;
				}
				else
					found = 0;
			}
			if (line_ptr->vertex_A == pos_B)
				line_ptr->line_A = lineB_add;
			else
				line_ptr->line_B = lineB_add;
		}
	}
	return;
}

template<typename Type>
void GRAPH<Type>::Delete_line()
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (vertex_num <= 1)
	{
		cout << "\033[1;31m【错误】图中顶点的数量少于2，无法执行任何操作\033[0m" << endl;
		return;
	}

	if (graph_directed == true)
		cout << "【提示】请以  顶点A'顶点B  格式输入要删除的弧（输入规则与默认构造函数相同）：" << endl;
	else
		cout << "【提示】请以  顶点A'顶点B  格式输入要删除的边（输入规则与默认构造函数相同）：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】输入流的长度为0，无法删除弧\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】输入流的长度为0，无法删除边\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}

	//将两个顶点分开
	LIST<char> line_A(3);
	LIST<char> line_B(3);
	if (input.Getelement(1) == '\'')//弧或边的第一个顶点名称为空
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】弧的第一个顶点名称为空，无法删除弧\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】边的第一个顶点名称为空，无法删除边\033[0m" << endl;
		return;
	}
	int split_count = 0;
	long long line_split_pos = 0;
	for (long long i1 = 2; i1 <= input.Listlength(); i1++)//顶点数量计数
	{
		if (input.Getelement(i1) == '\'' && input.Getelement(i1 - 1) != '|')
		{
			split_count = split_count + 1;
			line_split_pos = i1;
		}
	}
	if (line_split_pos == input.Listlength())//弧或边的第二个顶点名称为空
	{
		cout << "\033[1;31m【错误】弧或边的第二个顶点名称为空，无法删除弧或边\033[0m" << endl;
		return;
	}
	if (split_count > 1)//弧或边的顶点数量>=3
	{
		cout << "\033[1;31m【错误】输入的弧或边序列中，某条弧或边的顶点数量>=3，无法删除弧或边\033[0m" << endl;
		return;
	}
	if (split_count == 0)//弧或边只有一个顶点
	{
		cout << "\033[1;31m【错误】弧或边只有一个顶点，无法删除弧或边\033[0m" << endl;
		return;
	}
	long long length_A = line_split_pos - 1;
	long long length_B = input.Listlength() - line_split_pos;
	line_A = input.Substring(1, length_A);//弧或边的第一顶点
	line_B = input.Substring(line_split_pos + 1, length_B);//弧或边的第二顶点

	//还原两个顶点的名称
	for (long long i1 = line_A.Listlength() - 1; i1 >= 1; i1--)
	{
		if (line_A[i1 - 1] == '|')
		{
			if (line_A[i1] == '\'')
				line_A.Listdelete(i1);
			else if (line_A[i1] == ']')
				line_A.Listdelete(i1 + 1);
			else
			{
				cout << "\033[1;31m【错误】输入的弧或边序列中，转义字符的使用有误，无法删除弧或边\033[0m" << endl;
				return;
			}
		}
	}
	for (long long i1 = line_B.Listlength() - 1; i1 >= 1; i1--)
	{
		if (line_B[i1 - 1] == '|')
		{
			if (line_B[i1] == '\'')
				line_B.Listdelete(i1);
			else if (line_B[i1] == ']')
				line_B.Listdelete(i1 + 1);
			else
			{
				cout << "\033[1;31m【错误】输入的弧或边序列中，转义字符的使用有误，无法删除弧或边\033[0m" << endl;
				return;
			}
		}
	}

	//写入图的邻接矩阵
	long long pos_A = -1;
	for (long long i1 = 1; i1 <= vertex_num; i1++)
	{
		if (*vertex_id[i1 - 1] == line_A)
			pos_A = i1;
	}
	long long pos_B = -1;
	for (long long i1 = 1; i1 <= vertex_num; i1++)
	{
		if (*vertex_id[i1 - 1] == line_B)
			pos_B = i1;
	}
	if (pos_A == -1 || pos_B == -1)
	{
		cout << "\033[1;31m【错误】输入的弧或边序列中存在一个与顶点序列中任何顶点均不同的顶点，无法删除弧或边\033[0m" << endl;
		return;
	}
	//无向图(A-B,B-A)重复边检测
	if (array_matrix[pos_B - 1][pos_A - 1].line_exist == true && graph_directed == false)
	{
		long long temp = pos_A;
		pos_A = pos_B;
		pos_B = temp;
	}
	if (array_matrix[pos_A - 1][pos_B - 1].line_exist == false)
	{
		cout << "\033[1;31m【错误】该弧或边不存在\033[0m" << endl;
		return;
	}
	array_matrix[pos_A - 1][pos_B - 1].line_weight = 0.0;
	array_matrix[pos_A - 1][pos_B - 1].line_exist = false;
	array_matrix[pos_A - 1][pos_B - 1].line_visited = false;
	array_matrix[pos_A - 1][pos_B - 1].line_content = static_cast<Type>(0);
	line_num = line_num - 1;

	//邻接表
	//有向图只删除一个结点
	if (vertex_first[pos_A - 1]->vertex == pos_B)
	{
		listA_line* line_delete = vertex_first[pos_A - 1];
		vertex_first[pos_A - 1] = vertex_first[pos_A - 1]->line;
		delete line_delete;
	}
	else
	{
		listA_line* line_temp = vertex_first[pos_A - 1];
		while (line_temp->line->vertex != pos_B)
			line_temp = line_temp->line;
		listA_line* line_delete = line_temp->line;
		line_temp->line = line_temp->line->line;
		delete line_delete;
	}
	if (graph_directed == false)
	{
		//无向图要删除两个结点
		if (vertex_first[pos_B - 1]->vertex == pos_A)
		{
			listA_line* line_delete = vertex_first[pos_B - 1];
			vertex_first[pos_B - 1] = vertex_first[pos_B - 1]->line;
			delete line_delete;
		}
		else
		{
			listA_line* line_temp = vertex_first[pos_B - 1];
			while (line_temp->line->vertex != pos_A)
				line_temp = line_temp->line;
			listA_line* line_delete = line_temp->line;
			line_temp->line = line_temp->line->line;
			delete line_delete;
		}
	}

	//十字链表和邻接多重表
	//这里有一个非常坑人的地方，对每条弧或边的两个结点，都要验证两个结点=要删除的弧或边的两个结点。不可以只验证一个
	if (graph_directed == true)
	{
		listB_line* line_delete = nullptr;
		//vertex_firstA[pos_A - 1]->vertex_A == pos_A恒成立。这里只验证第二个顶点
		if (vertex_firstA[pos_A - 1]->vertex_B == pos_B)
		{
			line_delete = vertex_firstA[pos_A - 1];
			vertex_firstA[pos_A - 1] = vertex_firstA[pos_A - 1]->line_A;
		}
		else
		{
			listB_line* line_tempA = vertex_firstA[pos_A - 1];
			//line_tempA->line_A->vertex_A == pos_A恒成立。这里只验证第二个顶点
			while (line_tempA->line_A->vertex_B != pos_B)
				line_tempA = line_tempA->line_A;
			line_delete = line_tempA->line_A;
			line_tempA->line_A = line_tempA->line_A->line_A;
		}
		//vertex_firstB[pos_B - 1]->vertex_B == pos_B恒成立。这里只验证第二个顶点
		if (vertex_firstB[pos_B - 1]->vertex_A == pos_A)
			vertex_firstB[pos_B - 1] = vertex_firstB[pos_B - 1]->line_B;
		else
		{
			listB_line* line_tempB = vertex_firstB[pos_B - 1];
			//line_tempB->line_B->vertex_B == pos_B恒成立。这里只验证第二个顶点
			while (line_tempB->line_B->vertex_A != pos_A)
				line_tempB = line_tempB->line_B;
			line_tempB->line_B = line_tempB->line_B->line_B;
		}
		delete line_delete;
	}
	else
	{
		listB_line* line_delete = nullptr;
		if (vertex_firstA[pos_A - 1]->vertex_A == pos_A && vertex_firstA[pos_A - 1]->vertex_B == pos_B)
		{
			line_delete = vertex_firstA[pos_A - 1];
			vertex_firstA[pos_A - 1] = vertex_firstA[pos_A - 1]->line_A;
		}
		else if (vertex_firstA[pos_A - 1]->vertex_B == pos_A && vertex_firstA[pos_A - 1]->vertex_A == pos_B)
		{
			line_delete = vertex_firstA[pos_A - 1];
			vertex_firstA[pos_A - 1] = vertex_firstA[pos_A - 1]->line_B;
		}
		else
		{
			listB_line* line_tempA = vertex_firstA[pos_A - 1];
			while (true)
			{
				if (line_tempA->vertex_A == pos_A)
				{
					if (line_tempA->line_A->vertex_A == pos_A && line_tempA->line_A->vertex_B == pos_B)
					{
						line_delete = line_tempA->line_A;
						line_tempA->line_A = line_tempA->line_A->line_A;
						break;
					}
					else if (line_tempA->line_A->vertex_B == pos_A && line_tempA->line_A->vertex_A == pos_B)
					{
						line_delete = line_tempA->line_A;
						line_tempA->line_A = line_tempA->line_A->line_B;
						break;
					}
					else
						line_tempA = line_tempA->line_A;
				}
				else
				{
					if (line_tempA->line_B->vertex_A == pos_A && line_tempA->line_B->vertex_B == pos_B)
					{
						line_delete = line_tempA->line_B;
						line_tempA->line_B = line_tempA->line_B->line_A;
						break;
					}
					else if (line_tempA->line_B->vertex_B == pos_A && line_tempA->line_B->vertex_A == pos_B)
					{
						line_delete = line_tempA->line_B;
						line_tempA->line_B = line_tempA->line_B->line_B;
						break;
					}
					else
						line_tempA = line_tempA->line_B;
				}
			}
		}
		if (vertex_firstA[pos_B - 1]->vertex_A == pos_B && vertex_firstA[pos_B - 1]->vertex_B == pos_A)
			vertex_firstA[pos_B - 1] = vertex_firstA[pos_B - 1]->line_A;
		else if (vertex_firstA[pos_B - 1]->vertex_B == pos_B && vertex_firstA[pos_B - 1]->vertex_A == pos_A)
			vertex_firstA[pos_B - 1] = vertex_firstA[pos_B - 1]->line_B;
		else
		{
			listB_line* line_tempB = vertex_firstA[pos_B - 1];
			while (true)
			{
				if (line_tempB->vertex_A == pos_B)
				{
					if (line_tempB->line_A->vertex_A == pos_B && line_tempB->line_A->vertex_B == pos_A)
					{
						line_tempB->line_A = line_tempB->line_A->line_A;
						break;
					}
					else if (line_tempB->line_A->vertex_B == pos_B && line_tempB->line_A->vertex_A == pos_A)
					{
						line_tempB->line_A = line_tempB->line_A->line_B;
						break;
					}
					else
						line_tempB = line_tempB->line_A;
				}
				else
				{
					if (line_tempB->line_B->vertex_A == pos_B && line_tempB->line_B->vertex_B == pos_A)
					{
						line_tempB->line_B = line_tempB->line_B->line_A;
						break;
					}
					else if (line_tempB->line_B->vertex_B == pos_B && line_tempB->line_B->vertex_A == pos_A)
					{
						line_tempB->line_B = line_tempB->line_B->line_B;
						break;
					}
					else
						line_tempB = line_tempB->line_B;
				}
			}
		}
		delete line_delete;
	}
	return;
}

template<typename Type>
bool GRAPH<Type>::Connected() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法判断图是否连通\033[0m" << endl;
		return false;
	}
	if (graph_directed == true)
	{
		cout << "\033[1;31m【错误】只有无向图存在“连通”的概念，请不要对有向图使用本函数\033[0m" << endl;
		return false;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法判断图是否连通\033[0m" << endl;
		return false;
	}
	if (vertex_num == 1)
		return true;
	//运行至此处时，图的顶点数量>=2
	if (line_num < vertex_num - 1)
		return false;
	if (vertex_first[0] == nullptr)//没有邻接顶点的顶点不能进行下一步
		return false;

	struct stack_search
	{
		long long vertex_pos;
		struct stack_search* next;
	};

	vertex_visited[0] = true;
	long long vertex_count = 1;
	stack_search* stack_head = new stack_search;
	stack_head->vertex_pos = 1;
	stack_head->next = nullptr;
	while (stack_head != nullptr)
	{
		long long vertex_A = stack_head->vertex_pos;
		//while前的代码相当于《数据结构》中的FirstAdjVex函数
		listA_line* i_line = vertex_first[vertex_A - 1];
		long long i_scan = i_line->vertex;

		while (i_scan >= 0)
		{
			if (vertex_visited[i_scan - 1] == false)
			{
				vertex_visited[i_scan - 1] = true;
				vertex_count = vertex_count + 1;
				//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
				if (vertex_first[i_scan - 1] != nullptr)
				{
					//运行到这里时，stack_head一定不是nullptr。省略判断语句
					stack_search* stack_new = new stack_search;
					stack_new->vertex_pos = i_scan;
					stack_new->next = stack_head;
					stack_head = stack_new;
				}
				break;//运行到这里时i_scan非零
			}
			else
			{
				//下面的代码相当于《数据结构》中的NextAdjVex函数
				i_line = i_line->line;
				if (i_line != nullptr)
					i_scan = i_line->vertex;
				else
					i_scan = -1;
			}
		}
		if (i_scan >= 0)
			continue;
		if (stack_head->next == nullptr)
		{
			delete stack_head;
			stack_head = nullptr;
		}
		else
		{
			stack_search* stack_delete = stack_head;
			stack_head = stack_head->next;
			delete stack_delete;
		}
	}

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;

	if (vertex_count == vertex_num)
		return true;
	else
		return false;
}

template<typename Type>
bool GRAPH<Type>::S_Connected() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法判断图是否强连通\033[0m" << endl;
		return false;
	}
	if (graph_directed == false)
	{
		cout << "\033[1;31m【错误】仅有向图存在“强连通”的概念，请不要对无向图使用本函数\033[0m" << endl;
		return false;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法判断图是否强连通\033[0m" << endl;
		return false;
	}
	if (vertex_num == 1)
		return true;
	//运行至此处时，图的顶点数量>=2
	if (line_num < vertex_num)//有n个顶点的强连通图最少有n条边
		return false;
	if (vertex_first[0] == nullptr)//没有邻接顶点的顶点不能进行下一步
		return false;
	//本函数使用Kosaraju算法

	struct stack_search
	{
		long long vertex_pos;
		struct stack_search* next;
	};

	vertex_visited[0] = true;
	long long vertex_count = 1;
	stack_search* stack_head = new stack_search;
	stack_head->vertex_pos = 1;
	stack_head->next = nullptr;
	while (stack_head != nullptr)
	{
		long long vertex_A = stack_head->vertex_pos;
		//while前的代码相当于《数据结构》中的FirstAdjVex函数
		listA_line* i_line = vertex_first[vertex_A - 1];
		long long i_scan = i_line->vertex;

		while (i_scan >= 0)
		{
			if (vertex_visited[i_scan - 1] == false)
			{
				vertex_visited[i_scan - 1] = true;
				vertex_count = vertex_count + 1;
				//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
				if (vertex_first[i_scan - 1] != nullptr)
				{
					//运行到这里时，stack_head一定不是nullptr。省略判断语句
					stack_search* stack_new = new stack_search;
					stack_new->vertex_pos = i_scan;
					stack_new->next = stack_head;
					stack_head = stack_new;
				}
				break;//运行到这里时i_scan非零
			}
			else
			{
				//下面的代码相当于《数据结构》中的NextAdjVex函数
				i_line = i_line->line;
				if (i_line != nullptr)
					i_scan = i_line->vertex;
				else
					i_scan = -1;
			}
		}
		if (i_scan >= 0)
			continue;
		if (stack_head->next == nullptr)
		{
			delete stack_head;
			stack_head = nullptr;
		}
		else
		{
			stack_search* stack_delete = stack_head;
			stack_head = stack_head->next;
			delete stack_delete;
		}
	}

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	if (vertex_count != vertex_num)
		return false;
	vertex_count = 0;

	//反转所有弧
	listA_line** vertex_first_x = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		vertex_first_x[i - 1] = nullptr;
	listA_line** last_vertex = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		last_vertex[i - 1] = nullptr;
	for (long long i = 1; i <= vertex_num; i++)
	{
		listA_line* line_scan = vertex_first[i - 1];
		while (line_scan != nullptr)
		{
			listA_line* line_temp = new listA_line;
			line_temp->line = nullptr;
			line_temp->line_content = static_cast<Type>(0);
			line_temp->line_visited = false;
			line_temp->line_weight = line_scan->line_weight;
			line_temp->vertex = i;
			if (last_vertex[line_scan->vertex - 1] != nullptr)
				last_vertex[line_scan->vertex - 1]->line = line_temp;
			last_vertex[line_scan->vertex - 1] = line_temp;
			if (vertex_first_x[line_scan->vertex - 1] == nullptr)
				vertex_first_x[line_scan->vertex - 1] = line_temp;
			line_scan = line_scan->line;
		}
	}
	delete[] last_vertex;

	//再次进行DFS遍历
	//vertex_first_x已被正确初始化。请忽略一些安全软件在这里误报的“内存未初始化”错误
	if (vertex_first_x[0] != nullptr)//没有邻接顶点的顶点不能进行下一步
	{
		vertex_visited[0] = true;
		vertex_count = 1;
		stack_head = new stack_search;
		stack_head->vertex_pos = 1;
		stack_head->next = nullptr;
		while (stack_head != nullptr)
		{
			long long vertex_A = stack_head->vertex_pos;
			//while前的代码相当于《数据结构》中的FirstAdjVex函数
			listA_line* i_line = vertex_first_x[vertex_A - 1];
			long long i_scan = i_line->vertex;

			while (i_scan >= 0)
			{
				if (vertex_visited[i_scan - 1] == false)
				{
					vertex_visited[i_scan - 1] = true;
					vertex_count = vertex_count + 1;
					//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
					if (vertex_first_x[i_scan - 1] != nullptr)
					{
						//运行到这里时，stack_head一定不是nullptr。省略判断语句
						stack_search* stack_new = new stack_search;
						stack_new->vertex_pos = i_scan;
						stack_new->next = stack_head;
						stack_head = stack_new;
					}
					break;//运行到这里时i_scan非零
				}
				else
				{
					//下面的代码相当于《数据结构》中的NextAdjVex函数
					i_line = i_line->line;
					if (i_line != nullptr)
						i_scan = i_line->vertex;
					else
						i_scan = -1;
				}
			}
			if (i_scan >= 0)
				continue;
			if (stack_head->next == nullptr)
			{
				delete stack_head;
				stack_head = nullptr;
			}
			else
			{
				stack_search* stack_delete = stack_head;
				stack_head = stack_head->next;
				delete stack_delete;
			}
		}
		//遍历结束后必须把顶点重置为没有访问过的状态
		for (long long i = 1; i <= vertex_num; i++)
			vertex_visited[i - 1] = false;
	}

	//释放内存
	for (long long i = 1; i <= vertex_num; i++)
	{
		while (vertex_first_x[i - 1] != nullptr)
		{
			listA_line* listA_delete = vertex_first_x[i - 1];
			vertex_first_x[i - 1] = vertex_first_x[i - 1]->line;
			delete listA_delete;
		}
	}
	delete[] vertex_first_x;

	if (vertex_count == vertex_num)
		return true;
	else
		return false;
}

template<typename Type>
bool GRAPH<Type>::Weighted() const
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法判断图是否为带权图\033[0m" << endl;
		return false;
	}

	return graph_weighted;
}

template<typename Type>
void GRAPH<Type>::Add_weight()
{
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法给图中的所有边加上权值\033[0m" << endl;
		return;
	}
	if (graph_weighted == true)
	{
		cout << "\033[1;31m【错误】图已被转化为带权图，无法再次给该图加上权值\033[0m" << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法给图中的所有边加上权值\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << "\033[1;31m【错误】图中只有一个结点，无法给图中的所有边加上权值\033[0m" << endl;
		return;
	}

	//读取权值，并向邻接矩阵写入权值
	cout << "【提示】请以  ,顶点A'顶点B'权值,  格式输入所有权值（输入规则与默认构造函数相同）：" << endl;
	LIST<char> input(3);
	cin >> input;
	if (input.Listlength() == 0)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】输入流的长度为0，无法向图中的弧新增权值\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】输入流的长度为0，无法向图中的边新增权值\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}

	//将弧/边序列按照顶点成对分割，并校验是否有错误
	if (input[0] == ',')
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】输入的弧序列中，第一条弧的内容为空，无法向图中的弧新增权值\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】输入的边序列中，第一条边的内容为空，无法向图中的边新增权值\033[0m" << endl;
		return;
	}
	LIST<long long> input_pos(3);
	input_pos += 0;
	for (long long i = 1; i <= input.Listlength() - 1; i++)
	{
		if (input[i] == ',' && input[i - 1] != ';')
		{
			input_pos += (i - 1);
			input_pos += (i + 1);
		}
	}
	input_pos += input.Listlength() - 1;
	long long check_A = 0;
	long long check_B = 1;
	while (check_B <= input_pos.Listlength() - 1)
	{
		if (input_pos[check_A] > input_pos[check_B])
		{
			if (graph_directed == true)
				cout << "\033[1;31m【错误】输入的弧序列中，存在内容为空的弧，无法向图中的弧新增权值\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，存在内容为空的边，无法向图中的边新增权值\033[0m" << endl;
			return;
		}
		check_A = check_A + 2;
		check_B = check_B + 2;
	}

	//还原分割顶点对时使用的转义字符;（英文分号）
	if (input_pos.Listlength() / 2 != line_num)
	{
		if (graph_directed == true)
			cout << "\033[1;31m【错误】输入的弧的数量与图中弧的数量不同，无法向图中的弧新增权值\033[0m" << endl;
		else
			cout << "\033[1;31m【错误】输入的边的数量与图中边的数量不同，无法向图中的边新增权值\033[0m" << endl;
		return;
	}
	bool BAD_INPUT = false;
	LIST<char>** first_split = new LIST<char>*[line_num];
	long long start_pos = 0;
	for (long long i = 1; i <= line_num; i++)
	{
		long long start = input_pos[start_pos];
		long long length = input_pos[start_pos + 1] - input_pos[start_pos] + 1;
		first_split[i - 1] = new LIST<char>(3);
		*first_split[i - 1] = input.Substring(start + 1, length);
		start_pos = start_pos + 2;
	}
	for (long long i = 1; i <= line_num; i++)
	{
		if (first_split[i - 1]->Getelement(first_split[i - 1]->Listlength()) == ';')//顶点名称的最后一个字符是;
		{
			if (graph_directed == true)
				cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
			else
				cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
			BAD_INPUT = true;
			break;
		}
		for (long long i1 = first_split[i - 1]->Listlength() - 1; i1 >= 1; i1--)
		{
			if (first_split[i - 1]->Getelement(i1) == ';')
			{
				if (first_split[i - 1]->Getelement(i1 + 1) == ',')
					first_split[i - 1]->Listdelete(i1);
				else if (first_split[i - 1]->Getelement(i1 + 1) == '[')
					first_split[i - 1]->Listdelete(i1 + 1);
				else
				{
					if (graph_directed == true)
						cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
					else
						cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
					BAD_INPUT = true;
					break;
				}
			}
		}
		if (BAD_INPUT == true)
			break;
	}
	input.Clearlist();
	input_pos.Clearlist();

	//将一次分割后的弧或边序列排序，并检验是否有重复的弧或边
	if (BAD_INPUT != true)
	{
		String_sort(first_split, line_num);
		for (long long i = 1; i <= line_num - 1; i++)
		{
			if (*first_split[i - 1] == *first_split[i])
			{
				if (graph_directed == true)
					cout << "\033[1;31m【错误】输入的弧序列中，存在重复的弧，无法向图中的弧新增权值\033[0m" << endl;
				else
					cout << "\033[1;31m【错误】输入的边序列中，存在重复的边，无法向图中的边新增权值\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}
		}
	}

	//一次分割结束后，将每条弧或边的两个顶点分开，并还原顶点名称
	if (BAD_INPUT != true)
	{
		LIST<char> line_A(3);
		LIST<char> line_B(3);
		LIST<char> line_C(3);
		LIST<long long> split_pos(3);
		for (long long i = 1; i <= line_num; i++)
		{
			//扫描分割点
			if (first_split[i - 1]->Getelement(1) == '\'')//弧或边的第一个顶点名称为空
			{
				if (graph_directed == true)
					cout << "\033[1;31m【错误】输入的弧序列中，某条弧存在名字为空的顶点，无法向图中的弧新增权值\033[0m" << endl;
				else
					cout << "\033[1;31m【错误】输入的边序列中，某条边存在名字为空的顶点，无法向图中的边新增权值\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}
			split_pos += 1;
			for (long long i1 = 2; i1 <= first_split[i - 1]->Listlength(); i1++)
			{
				if (first_split[i - 1]->Getelement(i1) == '\'' && first_split[i - 1]->Getelement(i1 - 1) != '|')
				{
					split_pos += (i1 - 1);
					split_pos += (i1 + 1);
				}
			}
			split_pos += first_split[i - 1]->Listlength();
			if (split_pos.Listlength() != 6)
			{
				if (graph_directed == true)
					cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
				else
					cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}
			long long check_A_X = 0;
			long long check_B_X = 1;
			while (check_B_X <= split_pos.Listlength() - 1)
			{
				if (split_pos[check_A_X] > split_pos[check_B_X])
				{
					if (graph_directed == true)
						cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
					else
						cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
					BAD_INPUT = true;
					break;
				}
				check_A_X = check_A_X + 2;
				check_B_X = check_B_X + 2;
			}
			if (BAD_INPUT == true)
				break;
			long long length_A = split_pos[1];
			long long length_B = split_pos[3] - split_pos[2] + 1;
			long long length_C = split_pos[5] - split_pos[4] + 1;
			line_A = first_split[i - 1]->Substring(1, length_A);
			line_B = first_split[i - 1]->Substring(split_pos[2], length_B);
			if (line_A == line_B)//过滤掉类似v1'v1'1,v1'v1'2的输入
			{
				BAD_INPUT = true;
				cout << "\033[1;31m【错误】存在名称重复的顶点。本函数无法继续运行，将退出\033[0m" << endl;
				break;
			}
			line_C = first_split[i - 1]->Substring(split_pos[4], length_C);
			char* converted_char = line_C.Char_array(false);
			long double converted = strtold(converted_char, nullptr);
			delete[] converted_char;
			split_pos.Clearlist();
			if (converted <= 0)//输入的权值 <= 0
			{
				cout << "\033[1;31m【错误】输入的权值<=0，注意权值可以是小数但必须>0。本函数无法继续运行，将退出\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}

			//还原两个顶点的名称
			for (long long i1 = line_A.Listlength() - 1; i1 >= 1; i1--)
			{
				if (line_A[i1 - 1] == '|')
				{
					if (line_A[i1] == '\'')
						line_A.Listdelete(i1);
					else if (line_A[i1] == ']')
						line_A.Listdelete(i1 + 1);
					else
					{
						if (graph_directed == true)
							cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
						else
							cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
						BAD_INPUT = true;
						break;
					}
				}
			}
			if (BAD_INPUT == true)
				break;
			for (long long i1 = line_B.Listlength() - 1; i1 >= 1; i1--)
			{
				if (line_B[i1 - 1] == '|')
				{
					if (line_B[i1] == '\'')
						line_B.Listdelete(i1);
					else if (line_B[i1] == ']')
						line_B.Listdelete(i1 + 1);
					else
					{
						if (graph_directed == true)
							cout << "\033[1;31m【错误】输入的弧序列中，转义字符的使用有误，无法向图中的弧新增权值\033[0m" << endl;
						else
							cout << "\033[1;31m【错误】输入的边序列中，转义字符的使用有误，无法向图中的边新增权值\033[0m" << endl;
						BAD_INPUT = true;
						break;
					}
				}
			}
			if (BAD_INPUT == true)
				break;

			//写入图的邻接矩阵
			long long pos_A = -1;
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (*vertex_id[i1 - 1] == line_A)
					pos_A = i1;
			}
			long long pos_B = -1;
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (*vertex_id[i1 - 1] == line_B)
					pos_B = i1;
			}
			if (pos_A == -1 || pos_B == -1)
			{
				if (graph_directed == true)
					cout << "\033[1;31m【错误】输入的弧序列中存在一个与顶点序列中任何顶点均不同的顶点，无法向图中的弧新增权值\033[0m" << endl;
				else
					cout << "\033[1;31m【错误】输入的边序列中存在一个与顶点序列中任何顶点均不同的顶点，无法向图中的边新增权值\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}
			if (array_matrix[pos_B - 1][pos_A - 1].line_exist == true && graph_directed == false)
			{
				long long temp = pos_A;
				pos_A = pos_B;
				pos_B = temp;
			}
			if (array_matrix[pos_A - 1][pos_B - 1].line_exist == false)
			{
				cout << "\033[1;31m【错误】输入的某条弧或边在图中不存在。本函数无法继续运行，将退出\033[0m" << endl;
				BAD_INPUT = true;
				break;
			}
			array_matrix[pos_A - 1][pos_B - 1].line_weight = converted;
		}
	}

	//释放申请的临时空间
	for (long long i = 1; i <= line_num; i++)
		first_split[i - 1]->~LIST();
	delete[] first_split;
	if (BAD_INPUT == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				array_matrix[i - 1][i1 - 1].line_weight = 0.0;
		}
		return;
	}

	//邻接表
	for (long long i = 1; i <= vertex_num; i++)
	{
		listA_line* line_scan = vertex_first[i - 1];
		while (line_scan != nullptr)
		{
			line_scan->line_weight = array_matrix[i - 1][line_scan->vertex - 1].line_weight;
			line_scan = line_scan->line;
		}
	}

	//十字链表和邻接多重表
	if (graph_directed == true)
	{
		//每条弧都只会被访问1次
		for (long long i = 1; i <= vertex_num; i++)
		{
			listB_line* line_scan = vertex_firstA[i - 1];
			while (line_scan != nullptr)
			{
				line_scan->line_weight = array_matrix[line_scan->vertex_A - 1][line_scan->vertex_B - 1].line_weight;
				line_scan = line_scan->line_A;
			}
		}
	}
	else
	{
		//每条边都只会被访问2次
		for (long long i = 1; i <= vertex_num; i++)
		{
			listB_line* line_scan = vertex_firstA[i - 1];
			while (line_scan != nullptr)
			{
				if (line_scan->line_weight == 0.0)
					line_scan->line_weight = array_matrix[line_scan->vertex_A - 1][line_scan->vertex_B - 1].line_weight;
				if (line_scan->vertex_A == i)
					line_scan = line_scan->line_A;
				else
					line_scan = line_scan->line_B;
			}
		}
	}

	graph_weighted = true;
	return;
}

template<typename Type>
bool GRAPH<Type>::Has_cycles() const
{
	//"输出图中所有的环"是一个非常复杂的数学问题，目前没有能力解决。这个函数只能用于判断图中有无环
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法判断图中有无环\033[0m" << endl;
		return false;
	}
	if (graph_directed == false && vertex_num <= 2)//无向图的环至少包含3个顶点
		return false;
	if (graph_directed == true && vertex_num <= 1)//有向图的环至少包含2个顶点（根据教材的定义，本程序不允许输入含有自环的图）
		return false;

	//DFS,BFS都可以用于判断图中是否有环。这里选择DFS算法
	//无环的图（有向图，无向图）可能不连通。如果无向图的任意连通分量中存在环，则无向图中存在环（有向图同理）
	struct stack_search
	{
		long long vertex_pos;
		struct stack_search* next;
	};
	bool cycle = false;
	int* status = new int[vertex_num]();//初始化为0
	//status = -1:该顶点已被访问过（灰色）; status = 0:该顶点未被访问（白色）; status = 1:该顶点的所有邻接顶点均被访问过（黑色）

	if (graph_directed == false)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			if (vertex_visited[i - 1] == false)
			{
				vertex_visited[i - 1] = true;
				status[i - 1] = -1;
				if (vertex_first[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				{
					status[i - 1] = 1;
					continue;
				}
				//运行到这里时stack_head一定是nullptr，所以省略选择分支
				stack_search* stack_head = new stack_search;
				stack_head->vertex_pos = i;
				stack_head->next = nullptr;
				while (stack_head != nullptr)
				{
					long long vertex_A = stack_head->vertex_pos;
					//while前的代码相当于《数据结构》中的FirstAdjVex函数
					listA_line* i_line = vertex_first[vertex_A - 1];
					long long i_scan = i_line->vertex;//下一个顶点的序号

					while (i_scan >= 0)
					{
						if (vertex_visited[i_scan - 1] == false)
						{
							vertex_visited[i_scan - 1] = true;
							status[i_scan - 1] = -1;
							//（仅限无向图）运行到这里时，vertex_first[i_scan - 1]一定非空。这里省略判断语句
							//运行到这里时，stack_head一定不是nullptr。省略判断语句
							stack_search* stack_new = new stack_search;
							stack_new->vertex_pos = i_scan;
							stack_new->next = stack_head;
							stack_head = stack_new;
							break;//运行到这里时i_scan非零
						}
						else
						{
							//（仅适用于无向图）当stack_head->next为nullptr时，status[i_scan - 1]必定为1
							//所以这里不需要判断stack_head->next是否为空，请忽略此处的报错
							if (status[i_scan - 1] == -1 && stack_head->next->vertex_pos != i_scan)
								cycle = true;
							//下面的代码相当于《数据结构》中的NextAdjVex函数
							i_line = i_line->line;
							if (i_line != nullptr)
								i_scan = i_line->vertex;
							else
							{
								status[vertex_A - 1] = 1;
								i_scan = -1;
							}
						}
					}
					if (i_scan >= 0)
						continue;
					if (stack_head->next == nullptr)
					{
						delete stack_head;
						stack_head = nullptr;
					}
					else
					{
						stack_search* stack_delete = stack_head;
						stack_head = stack_head->next;
						delete stack_delete;
					}
				}
				//运行到这里时，stack_head为nullptr，栈为空
				if (cycle == true)
					break;
			}
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			if (vertex_visited[i - 1] == false)
			{
				vertex_visited[i - 1] = true;
				status[i - 1] = -1;
				if (vertex_first[i - 1] == nullptr)//没有邻接顶点的顶点不能进行下一步
				{
					status[i - 1] = 1;
					continue;
				}
				//运行到这里时stack_head一定是nullptr，所以省略选择分支
				stack_search* stack_head = new stack_search;
				stack_head->vertex_pos = i;
				stack_head->next = nullptr;
				while (stack_head != nullptr)
				{
					long long vertex_A = stack_head->vertex_pos;
					//while前的代码相当于《数据结构》中的FirstAdjVex函数
					listA_line* i_line = vertex_first[vertex_A - 1];
					long long i_scan = i_line->vertex;//下一个顶点的序号

					while (i_scan >= 0)
					{
						if (vertex_visited[i_scan - 1] == false)
						{
							vertex_visited[i_scan - 1] = true;
							//若没有下面的判断语句，有向图中(A->B)边的B顶点在本函数中会导致指针i_line变为nullptr，从而使程序错误
							if (vertex_first[i_scan - 1] != nullptr)
							{
								//运行到这里时，stack_head一定不是nullptr。省略判断语句
								stack_search* stack_new = new stack_search;
								stack_new->vertex_pos = i_scan;
								stack_new->next = stack_head;
								stack_head = stack_new;
								status[i_scan - 1] = -1;
							}
							else
								status[i_scan - 1] = 1;
							break;//运行到这里时i_scan非零
						}
						else
						{
							//（仅适用于有向图）从已被访问过的顶点指向已被访问过的顶点，则图中有环
							//运行到这里时，status[vertex_A - 1]一定为-1。省略判断语句
							if (status[i_scan - 1] == -1)
								cycle = true;
							//下面的代码相当于《数据结构》中的NextAdjVex函数
							i_line = i_line->line;
							if (i_line != nullptr)
								i_scan = i_line->vertex;
							else
							{
								status[vertex_A - 1] = 1;
								i_scan = -1;
							}
						}
					}
					if (i_scan >= 0)
						continue;
					if (stack_head->next == nullptr)
					{
						delete stack_head;
						stack_head = nullptr;
					}
					else
					{
						stack_search* stack_delete = stack_head;
						stack_head = stack_head->next;
						delete stack_delete;
					}
				}
				//运行到这里时，stack_head为nullptr，栈为空
				if (cycle == true)
					break;
			}
		}
	}

	//遍历结束后必须把顶点重置为没有访问过的状态
	for (long long i = 1; i <= vertex_num; i++)
		vertex_visited[i - 1] = false;
	delete[] status;
	return cycle;
}

template<typename Type>
GRAPH<Type> GRAPH<Type>::Prim() const
{
	GRAPH<Type> TEMP;//调用无参数版本的默认构造函数
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，Prim算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (graph_directed == true)
	{
		cout << "\033[1;31m【错误】只有无向图存在“连通”的概念，请不要对有向图使用Prim算法\033[0m" << endl;
		return TEMP;
	}
	if (Weighted() == false)
	{
		cout << "\033[1;31m【错误】图是无权图，Prim算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，Prim算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (vertex_num == 1)
	{
		cout << "\033[1;31m【错误】图只有一个顶点，Prim算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	//运行至此处时，图的顶点数量>=2
	if (Connected() == false)//对非连通图使用本函数，程序会崩溃
	{
		cout << "\033[1;31m【错误】图不是连通图，Prim算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}

	//如果顶点A与顶点B在一个集合内，定义A到B的距离是0.0
	//如果顶点A与顶点B不在一个集合内且AB之间没有路径，定义A到B的距离是-1.0
	struct close_edge
	{
		long long vertex;
		long double low_cost;
	};
	close_edge* manage = new close_edge[vertex_num];
	manage[0].vertex = 1;
	manage[0].low_cost = 0.0;
	for (long long i = 2; i <= vertex_num; i++)
	{
		manage[i - 1].vertex = 1;
		long double sum_temp = array_matrix[0][i - 1].line_weight + array_matrix[i - 1][0].line_weight;
		if (sum_temp <= 0)
			manage[i - 1].low_cost = -1.0;
		else
			manage[i - 1].low_cost = sum_temp;
	}

	//邻接矩阵
	TEMP.array_matrix = new array_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		TEMP.array_matrix[i - 1] = new array_line[vertex_num];
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			TEMP.array_matrix[i - 1][i1 - 1].line_weight = 0.0;
			TEMP.array_matrix[i - 1][i1 - 1].line_exist = false;
			TEMP.array_matrix[i - 1][i1 - 1].line_visited = false;
			TEMP.array_matrix[i - 1][i1 - 1].line_content = static_cast<Type>(0);
		}
	}
	for (long long i = 1; i <= vertex_num - 1; i++)
	{
		long long start_pos = 1;
		long double min_cost = -1;
		for (start_pos = 1; start_pos <= vertex_num; start_pos++)
		{
			if (manage[start_pos - 1].low_cost > 0)
			{
				min_cost = manage[start_pos - 1].low_cost;
				break;
			}
		}
		long long min = start_pos;
		long long min_vertex = manage[start_pos - 1].vertex;
		for (long long i1 = start_pos + 1; i1 <= vertex_num; i1++)
		{
			if (manage[i1 - 1].low_cost > 0 && manage[i1 - 1].low_cost < min_cost)
			{
				min_cost = manage[i1 - 1].low_cost;
				min = i1;
				min_vertex = manage[i1 - 1].vertex;
			}
		}

		TEMP.array_matrix[min_vertex - 1][min - 1].line_exist = true;
		TEMP.array_matrix[min_vertex - 1][min - 1].line_weight = array_matrix[min_vertex - 1][min - 1].line_weight +
			array_matrix[min - 1][min_vertex - 1].line_weight;
		TEMP.array_matrix[min_vertex - 1][min - 1].line_visited = array_matrix[min_vertex - 1][min - 1].line_visited +
			array_matrix[min - 1][min_vertex - 1].line_visited;
		TEMP.array_matrix[min_vertex - 1][min - 1].line_content = array_matrix[min_vertex - 1][min - 1].line_content +
			array_matrix[min - 1][min_vertex - 1].line_content;
		manage[min - 1].low_cost = 0;
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			if (manage[i1 - 1].low_cost <= 0 && manage[i1 - 1].low_cost != -1.0)//两个顶点在同一个集合内
				continue;
			long double sum_temp = array_matrix[min - 1][i1 - 1].line_weight + array_matrix[i1 - 1][min - 1].line_weight;
			if (sum_temp <= 0)//两个顶点之间没有边
				continue;
			//运行到此处时，顶点i1和顶点min不在同一个集合内，且顶点i1和顶点min之间有边连接

			if (manage[i1 - 1].low_cost == -1.0 || sum_temp < manage[i1 - 1].low_cost)
			{
				manage[i1 - 1].vertex = min;
				manage[i1 - 1].low_cost = sum_temp;
			}
		}
	}
	delete[] manage;

	//初始化其余部分
	TEMP.graph_initialized = graph_initialized;
	TEMP.graph_directed = graph_directed;
	TEMP.graph_weighted = graph_weighted;
	TEMP.line_num = vertex_num - 1;
	TEMP.vertex_num = vertex_num;
	TEMP.vertex_visited = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_visited[i - 1] = vertex_visited[i - 1];
	TEMP.vertex_content = new Type[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_content[i - 1] = vertex_content[i - 1];
	TEMP.vertex_id = new LIST<char>*[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		//不可以用临时变量+复制构造函数，因为临时变量在括号外会被析构掉
		TEMP.vertex_id[i - 1] = new LIST<char>(3);
		*TEMP.vertex_id[i - 1] = *vertex_id[i - 1];
	}

	//邻接表
	TEMP.vertex_first = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_first[i - 1] = nullptr;
	TEMP.array_2_listA();

	//十字链表和邻接多重表
	TEMP.vertex_firstA = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_firstA[i - 1] = nullptr;
	if (graph_directed == true)
	{
		TEMP.vertex_firstB = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			TEMP.vertex_firstB[i - 1] = nullptr;
	}
	TEMP.array_2_listB();

	return TEMP;
}

template<typename Type>
GRAPH<Type> GRAPH<Type>::Kruskal() const
{
	GRAPH<Type> TEMP;//调用无参数版本的默认构造函数
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，Kruskal算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (graph_directed == true)
	{
		cout << "\033[1;31m【错误】只有无向图存在“连通”的概念，请不要对有向图使用Kruskal算法\033[0m" << endl;
		return TEMP;
	}
	if (Weighted() == false)
	{
		cout << "\033[1;31m【错误】图是无权图，Kruskal算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，Kruskal算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	if (vertex_num == 1)
	{
		cout << "\033[1;31m【错误】图只有一个顶点，Kruskal算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}
	//运行至此处时，图的顶点数量>=2
	if (Connected() == false)//对非连通图使用本函数，程序会崩溃
	{
		cout << "\033[1;31m【错误】图不是连通图，Kruskal算法无法继续运行，并将退出\033[0m" << endl;
		return TEMP;
	}

	//使用堆排序，以权值为关键词对边进行排序
	struct line_sort
	{
		long long line;
		long long column;
		long double weight;
	};
	line_sort* line_manage = new line_sort[line_num];
	long long line_count = 0;
	for (long long i = 1; i <= vertex_num; i++)
	{
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			if (array_matrix[i - 1][i1 - 1].line_exist == true)
			{
				line_manage[line_count].line = i;
				line_manage[line_count].column = i1;
				line_manage[line_count].weight = array_matrix[i - 1][i1 - 1].line_weight;
				line_count = line_count + 1;
			}
		}
	}

	long long interval_length = line_num;//待排序区间的长度
	//此处offset = a-1 = 1-1 = 0
	long long offset = 0;//偏移量，每个elements数组的下标要加上此数值
	//在以顺序表形式存储的二叉树中，某个结点的下标*2是该结点的左孩子（若存在），下标*2+1是该结点的右孩子（若存在）
	//此时结点的下标必须从1（根结点）开始编号。再次强调，必须从1（根结点）开始编号
	for (long long i = interval_length / 2; i > 0; i--)
	{
		long long temp_line = line_manage[offset + i - 1].line;
		long long temp_column = line_manage[offset + i - 1].column;
		long double temp_weight = line_manage[offset + i - 1].weight;//保存该非叶子结点的值
		long long scan = i;//当前正在处理的结点位置
		for (long long j = 2 * i; j <= interval_length; j = j * 2)
		{
			if (j < interval_length && line_manage[offset + j - 1].weight <= line_manage[offset + j].weight)
				j = j + 1;//若该非叶子结点的左子树存在且该非叶子结点的左子树 <= 右子树，则j=该非叶子结点的右子树
			if (temp_weight > line_manage[offset + j - 1].weight)
				break;//该非叶子结点的值 > 该非叶子结点全部子树的值
			line_manage[offset + scan - 1].line = line_manage[offset + j - 1].line;
			line_manage[offset + scan - 1].column = line_manage[offset + j - 1].column;
			line_manage[offset + scan - 1].weight = line_manage[offset + j - 1].weight;//正在处理的结点的值等于该结点的左/右子树的值
			scan = j;//更新下一轮循环中，开始处理的结点的位置
		}
		line_manage[offset + scan - 1].line = temp_line;
		line_manage[offset + scan - 1].column = temp_column;
		line_manage[offset + scan - 1].weight = temp_weight;//退出循环时，还原双亲结点的值
	}
	for (long long i = interval_length; i > 1; i--)
	{
		long long tempx_line = line_manage[offset + 0].line;
		long long tempx_column = line_manage[offset + 0].column;
		long double tempx_weight = line_manage[offset + 0].weight;
		line_manage[offset + 0].line = line_manage[offset + i - 1].line;
		line_manage[offset + 0].column = line_manage[offset + i - 1].column;
		line_manage[offset + 0].weight = line_manage[offset + i - 1].weight;
		line_manage[offset + i - 1].line = tempx_line;
		line_manage[offset + i - 1].column = tempx_column;
		line_manage[offset + i - 1].weight = tempx_weight;

		long long temp_line = line_manage[offset + 0].line;
		long long temp_column = line_manage[offset + 0].column;
		long double temp_weight = line_manage[offset + 0].weight;//保存根结点的值
		long long scan = 1;//当前正在处理的结点位置
		for (long long j = 2; j <= i - 1; j = j * 2)
		{
			if (j < i - 1 && line_manage[offset + j - 1].weight <= line_manage[offset + j].weight)
				j = j + 1;//若该非叶子结点的左子树存在且该非叶子结点的左子树 <= 右子树，则j=该非叶子结点的右子树
			if (temp_weight > line_manage[offset + j - 1].weight)
				break;//该非叶子结点的值 > 该非叶子结点全部子树的值
			line_manage[offset + scan - 1].line = line_manage[offset + j - 1].line;
			line_manage[offset + scan - 1].column = line_manage[offset + j - 1].column;
			line_manage[offset + scan - 1].weight = line_manage[offset + j - 1].weight;//正在处理的结点的值等于该结点的左/右子树的值
			scan = j;//更新下一轮循环中，开始处理的结点的位置
		}
		line_manage[offset + scan - 1].line = temp_line;
		line_manage[offset + scan - 1].column = temp_column;
		line_manage[offset + scan - 1].weight = temp_weight;//退出循环时，还原根结点的值
	}

	//初始化邻接矩阵
	TEMP.array_matrix = new array_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		TEMP.array_matrix[i - 1] = new array_line[vertex_num];
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			TEMP.array_matrix[i - 1][i1 - 1].line_weight = 0.0;
			TEMP.array_matrix[i - 1][i1 - 1].line_exist = false;
			TEMP.array_matrix[i - 1][i1 - 1].line_visited = false;
			TEMP.array_matrix[i - 1][i1 - 1].line_content = static_cast<Type>(0);
		}
	}

	//初始化并查集
	long long* mfset = new long long[vertex_num];
	//根结点存储子集中所含成员数目的负值
	for (long long i = 1; i <= vertex_num; i++)
		mfset[i - 1] = -1;

	//邻接矩阵
	long long add_count = 0;
	for (long long i = 1; i <= line_num; i++)
	{
		if (add_count == vertex_num - 1)
			break;
		//取一条边
		long long vertex_x = line_manage[i - 1].line;
		long long vertex_x1 = vertex_x;
		long long vertex_y = line_manage[i - 1].column;
		long long vertex_y1 = vertex_y;
		//寻找根结点
		while (mfset[vertex_x - 1] > 0)
			vertex_x = mfset[vertex_x - 1];
		while (mfset[vertex_y - 1] > 0)
			vertex_y = mfset[vertex_y - 1];
		if (vertex_x == vertex_y)
			continue;//两个结点的根结点相同，不需要新增边
		//写入邻接矩阵
		add_count = add_count + 1;
		TEMP.array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_exist = true;
		TEMP.array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_weight =
			array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_weight;
		TEMP.array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_visited =
			array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_visited;
		TEMP.array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_content =
			array_matrix[vertex_x1 - 1][vertex_y1 - 1].line_content;

		//合并两棵树。运行到这里时，vertex_x和vertex_y都是根结点
		long long new_root = -1;
		if (mfset[vertex_x - 1] > mfset[vertex_y - 1])//x的成员比y少
		{
			mfset[vertex_y - 1] = mfset[vertex_y - 1] + mfset[vertex_x - 1];
			mfset[vertex_x - 1] = vertex_y;
			new_root = vertex_y;
		}
		else
		{
			mfset[vertex_x - 1] = mfset[vertex_x - 1] + mfset[vertex_y - 1];
			mfset[vertex_y - 1] = vertex_x;
			new_root = vertex_x;
		}
		//压缩路径
		if (mfset[vertex_x1 - 1] < 0)
			continue;
		else
		{
			while (mfset[vertex_x1 - 1] != new_root)
			{
				long long backup = mfset[vertex_x1 - 1];
				mfset[vertex_x1 - 1] = new_root;
				vertex_x1 = backup;
			}
		}
		if (mfset[vertex_y1 - 1] < 0)
			continue;
		else
		{
			while (mfset[vertex_y1 - 1] != new_root)
			{
				long long backup = mfset[vertex_y1 - 1];
				mfset[vertex_y1 - 1] = new_root;
				vertex_y1 = backup;
			}
		}
	}

	//释放内存
	delete[] mfset;
	delete[] line_manage;

	//初始化其余部分
	TEMP.graph_initialized = graph_initialized;
	TEMP.graph_directed = graph_directed;
	TEMP.graph_weighted = graph_weighted;
	TEMP.line_num = vertex_num - 1;
	TEMP.vertex_num = vertex_num;
	TEMP.vertex_visited = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_visited[i - 1] = vertex_visited[i - 1];
	TEMP.vertex_content = new Type[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_content[i - 1] = vertex_content[i - 1];
	TEMP.vertex_id = new LIST<char>*[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		//不可以用临时变量+复制构造函数，因为临时变量在括号外会被析构掉
		TEMP.vertex_id[i - 1] = new LIST<char>(3);
		*TEMP.vertex_id[i - 1] = *vertex_id[i - 1];
	}

	//邻接表
	TEMP.vertex_first = new listA_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_first[i - 1] = nullptr;
	TEMP.array_2_listA();

	//十字链表和邻接多重表
	TEMP.vertex_firstA = new listB_line * [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		TEMP.vertex_firstA[i - 1] = nullptr;
	if (graph_directed == true)
	{
		TEMP.vertex_firstB = new listB_line * [vertex_num];
		for (long long i = 1; i <= vertex_num; i++)
			TEMP.vertex_firstB[i - 1] = nullptr;
	}
	TEMP.array_2_listB();

	return TEMP;
}

template<typename Type>
void GRAPH<Type>::Dijkstra() const
{
	//注意：Dijkstra算法对无向图和有向图均适用
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行Dijkstra算法\033[0m" << endl;
		return;
	}
	if (Weighted() == false)
	{
		cout << "\033[1;31m【错误】图是无权图，无法执行Dijkstra算法\033[0m" << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法执行Dijkstra算法\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << "\033[1;33m【警告】图中只有一个顶点，对该图执行Dijkstra算法没有意义\033[0m" << endl;
		cout << "该顶点当然可以到达其自身" << endl;
		return;
	}

	cout << "【提示】请输入起始顶点的名称：" << endl;
	LIST<char> input(0);
	if (input.Listlength() == 0)
	{
		cout << "\033[1;31m【错误】输入流的长度为0，输入的起始顶点名称无效，无法执行Dijkstra算法\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}
	long long pos = -1;
	for (long long i = 1; i <= vertex_num; i++)
	{
		if (*vertex_id[i - 1] == input)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
	{
		cout << "\033[1;31m【错误】输入的起始顶点不存在，无法执行Dijkstra算法\033[0m" << endl;
		return;
	}
	input.Clearlist();

	long double* distance = new long double[vertex_num];
	//权值可以是小数但必须>0。所以在下面的代码中，用距离为0指代距离为无穷远
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
			distance[i - 1] = array_matrix[pos - 1][i - 1].line_weight;
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
			distance[i - 1] = array_matrix[pos - 1][i - 1].line_weight + array_matrix[i - 1][pos - 1].line_weight;
	}
	bool* finished = new bool[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		finished[i - 1] = false;
	finished[pos - 1] = true;
	long long* pre = new long long[vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
	{
		if (distance[i - 1] == 0)
			pre[i - 1] = -1;
		else
			pre[i - 1] = pos;
	}

	bool all_visited = true;
	for (long long i = 1; i <= vertex_num - 1; i++)
	{
		long double distance_min = LDBL_MAX;
		long long distance_pos = -1;
		for (long long i1 = 1; i1 <= vertex_num; i1++)
		{
			if (finished[i1 - 1] == true)
				continue;
			if (distance[i1 - 1] <= 0)
				continue;
			if (distance[i1 - 1] < distance_min)
			{
				distance_min = distance[i1 - 1];
				distance_pos = i1;
			}
		}

		if (distance_pos != -1)
		{
			finished[distance_pos - 1] = true;
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (finished[i1 - 1] == true)
					continue;
				long double old_new = -1.0;
				if (graph_directed == true)
					old_new = array_matrix[distance_pos - 1][i1 - 1].line_weight;
				else
					old_new = array_matrix[distance_pos - 1][i1 - 1].line_weight +
					array_matrix[i1 - 1][distance_pos - 1].line_weight;
				if (old_new <= 0)
					continue;

				if (distance[i1 - 1] <= 0 || distance_min + old_new < distance[i1 - 1])
				{
					distance[i1 - 1] = distance_min + old_new;
					pre[i1 - 1] = distance_pos;
				}
			}
		}
		else
			all_visited = false;
	}

	if (all_visited == false)
	{
		cout << "\033[1;33m【警告】无法从输入的顶点访问所有的顶点，程序仍将输出起始顶点到所有可访问到的顶点的距离，\033[0m";
		cout << "\033[1;33m但请再次检查输入的图是否有误\033[0m" << endl;
	}
	cout << "该顶点到各个顶点的距离和路径：" << endl;
	for (long long i = 1; i <= vertex_num; i++)
	{
		cout << *vertex_id[pos - 1] << " -> " << *vertex_id[i - 1] << " :";
		if (distance[i - 1] == 0)
		{
			if (i == pos)
				cout << "该顶点当然可以到达其自身" << endl;
			else
				cout << "不可达" << endl;
			continue;
		}
		else
			cout << "路径长度为" << distance[i - 1] << endl;

		LIST<long long> TEMP(3);
		TEMP += i;
		long long previous = pre[i - 1];
		while (previous != -1)
		{
			TEMP += previous;
			previous = pre[previous - 1];
		}
		cout << "最短路径: " << *vertex_id[pos - 1] << " -> ";
		for (long long i1 = TEMP.Listlength() - 1; i1 >= 2; i1--)
			cout << *vertex_id[TEMP.Getelement(i1) - 1] << " -> ";
		cout << *vertex_id[TEMP.Getelement(1) - 1] << endl;
	}

	delete[] distance;
	delete[] finished;
	delete[] pre;
	return;
}

template<typename Type>
void GRAPH<Type>::Floyd() const
{
	//注意：Floyd算法对无向图和有向图均适用
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法执行Floyd算法\033[0m" << endl;
		return;
	}
	if (Weighted() == false)
	{
		cout << "\033[1;31m【错误】图是无权图，无法执行Floyd算法\033[0m" << endl;
		return;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】图是空图，无法执行Floyd算法\033[0m" << endl;
		return;
	}
	if (vertex_num == 1)
	{
		cout << "\033[1;33m【警告】图中只有一个顶点，对该图执行Floyd算法没有意义\033[0m" << endl;
		cout << "每一对顶点之间的最短路径长度:" << endl;
		cout << "Vertex 1:  0" << endl;
		return;
	}

	long double** distance = new long double* [vertex_num];
	for (long long i = 1; i <= vertex_num; i++)
		distance[i - 1] = new long double[vertex_num];
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				distance[i - 1][i1 - 1] = array_matrix[i - 1][i1 - 1].line_weight;
	}
	else
	{
		//初始化无向图的距离矩阵时，不可只初始化为上三角矩阵（下三角全是0）。否则后面的代码会出错
		for (long long i = 1; i <= vertex_num; i++)
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				distance[i - 1][i1 - 1] = array_matrix[i - 1][i1 - 1].line_weight + array_matrix[i1 - 1][i - 1].line_weight;
	}

	//i,i1,i2的顺序不可互换
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (distance[i1 - 1][i - 1] <= 0)
					continue;
				for (long long i2 = 1; i2 <= vertex_num; i2++)
				{
					if (i1 == i2)
						continue;
					if (distance[i - 1][i2 - 1] <= 0)
						continue;
					if (distance[i1 - 1][i2 - 1] == 0 ||
						distance[i1 - 1][i - 1] + distance[i - 1][i2 - 1] < distance[i1 - 1][i2 - 1])
						distance[i1 - 1][i2 - 1] = distance[i1 - 1][i - 1] + distance[i - 1][i2 - 1];
				}
			}
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (distance[i1 - 1][i - 1] <= 0)
					continue;
				for (long long i2 = i1 + 1; i2 <= vertex_num; i2++)
				{
					if (i1 == i2)
						continue;
					if (distance[i - 1][i2 - 1] <= 0)
						continue;
					if (distance[i1 - 1][i2 - 1] == 0 ||
						distance[i1 - 1][i - 1] + distance[i - 1][i2 - 1] < distance[i1 - 1][i2 - 1])
						distance[i1 - 1][i2 - 1] = distance[i1 - 1][i - 1] + distance[i - 1][i2 - 1];
				}
			}
		}
	}

	cout << "每一对顶点之间的最短路径长度:" << endl;
	if (graph_directed == true)
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Vertex " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
				cout << distance[i - 1][i1 - 1] << "  ";
			cout << endl;
		}
	}
	else
	{
		for (long long i = 1; i <= vertex_num; i++)
		{
			cout << "Vertex " << i << ":  ";
			for (long long i1 = 1; i1 <= vertex_num; i1++)
			{
				if (i <= i1)
					cout << distance[i - 1][i1 - 1] << "  ";
				else
					cout << distance[i1 - 1][i - 1] << "  ";
			}
			cout << endl;
		}
	}

	for (long long i = 1; i <= vertex_num; i++)
		delete[] distance[i - 1];
	delete[] distance;
	return;
}

template<typename Type>
LIST<long long> GRAPH<Type>::Topo_sort(const bool output) const
{
	//入度=0的顶点不唯一的有向无环图可以被拓扑排序。同理，有很多顶点但没有任何弧的有向图可以被拓扑排序
	//本算法中，若使用邻接矩阵，时间复杂度为O(顶点数^2)；若使用邻接表，时间复杂度为O(顶点数+弧或边的数量)
	LIST<long long> TEMP(2);
	if (graph_initialized == false)
	{
		cout << "\033[1;31m【错误】图未初始化，无法进行拓扑排序\033[0m" << endl;
		return TEMP;
	}
	if (graph_directed == false)
	{
		cout << "\033[1;31m【错误】无法对无向图拓扑排序\033[0m" << endl;
		return TEMP;
	}
	if (vertex_num == 0)
	{
		cout << "\033[1;31m【错误】无法对空图拓扑排序\033[0m" << endl;
		return TEMP;
	}
	TEMP.Repair(0);
	if (vertex_num == 1)
	{
		if (output == true)
			cout << "拓扑排序的结果：" << *vertex_id[0] << endl;
		TEMP.ListinsertR(1, 1);
		return TEMP;
	}

	struct stack_vertex
	{
		long long vertex;
		struct stack_vertex* next;
	};
	TEMP.Listexpand(vertex_num);
	long long* output_print = nullptr;
	if (output == true)
		output_print = new long long[vertex_num];

	//计算初始状态下所有顶点的入度，并将所有入度为0的顶点入栈
	long long* indegree = new long long[vertex_num]();//初始化为0
	long long i = 1;
	for (i; i <= vertex_num; i++)
	{
		listA_line* scan = vertex_first[i - 1];
		if (scan == nullptr)
			continue;
		while (scan != nullptr)
		{
			indegree[scan->vertex - 1] = indegree[scan->vertex - 1] + 1;
			scan = scan->line;
		}
	}
	stack_vertex* stack_head = nullptr;
	for (i = 1; i <= vertex_num; i++)
	{
		if (indegree[i - 1] == 0)
		{
			stack_head = new stack_vertex;
			stack_head->vertex = i;
			stack_head->next = nullptr;
			break;
		}
	}
	for (i = i + 1; i <= vertex_num; i++)
	{
		if (indegree[i - 1] == 0)
		{
			stack_vertex* stack_new = new stack_vertex;
			stack_new->vertex = i;
			stack_new->next = stack_head;
			stack_head = stack_new;
		}
	}

	long long count = 0;
	while (stack_head != nullptr)
	{
		long long p_vertex = stack_head->vertex;
		TEMP.ListinsertR(TEMP.Listlength(), p_vertex);
		if (output == true)
			output_print[count] = p_vertex;
		count = count + 1;
		//必须先出栈再入栈，顺序不可以颠倒
		if (stack_head->next == nullptr)
		{
			delete stack_head;
			stack_head = nullptr;
		}
		else
		{
			stack_vertex* stack_delete = stack_head;
			stack_head = stack_head->next;
			delete stack_delete;
		}

		listA_line* scan = vertex_first[p_vertex - 1];
		while (scan != nullptr)
		{
			indegree[scan->vertex - 1] = indegree[scan->vertex - 1] - 1;
			if (indegree[scan->vertex - 1] == 0)
			{
				if (stack_head == nullptr)
				{
					stack_head = new stack_vertex;
					stack_head->vertex = scan->vertex;
					stack_head->next = nullptr;
				}
				else
				{
					stack_vertex* stack_new = new stack_vertex;
					stack_new->vertex = scan->vertex;
					stack_new->next = stack_head;
					stack_head = stack_new;
				}
			}
			scan = scan->line;
		}
	}

	if (count != vertex_num)
	{
		cout << "\033[1;31m【错误】有向图中有环，无法对有环的有向图拓扑排序\033[0m" << endl;
		TEMP.~LIST();//调用析构函数后，TEMP会变得和LIST<Type> TEMP(2)一样
	}
	else if (output == true)
	{
		cout << "拓扑排序的结果：";
		for (i = 1; i <= vertex_num - 1; i++)
			cout << *vertex_id[output_print[i - 1] - 1] << " -> ";
		cout << *vertex_id[output_print[vertex_num - 1] - 1];
		cout << endl;
	}
	delete[] indegree;
	delete[] output_print;
	return TEMP;
}

#endif