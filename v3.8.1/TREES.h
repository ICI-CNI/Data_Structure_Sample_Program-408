#ifndef TREES_H
#define TREES_H
//此处不需要#include任何文件，头文件由TABLE.h提供
//此处不需要使用using std::，因为已经在TABLE.h中声明过

template<typename Type>
class TREE
{
private:
	template<typename Type>
	friend class LIST;//将线性表作为树的友元
	template<typename Type>
	friend class GRAPH;

	bool SILENCE = true;//控制析构函数，复制构造函数，重载赋值运算符的调试输出，默认不输出

	//二叉树
	struct bitree
	{
		struct bitree* lchild;
		bool ltag;//如果为false，lchild指示结点的左孩子，如果为true，lchild指示结点的前驱
		long double weight;//（赫夫曼树）该节点的权值
		Type data;
		struct bitree* parent;
		bool rtag;//如果为false，rchild指示结点的右孩子，如果为true，rchild指示结点的后驱
		struct bitree* rchild;
	};
	//判断结点是否有子树时，请使用正确的判断条件（以左子树为例，右子树同理）：
	//若ltag=true或者lchild=nullptr，则左子树为空
	//若ltag=false并且lchild不等于nullptr，则左子树非空

	struct tree_manage
	{
		struct bitree* root;//指向二叉树的根节点
		bool tree;//如果为true，这棵二叉树是使用二叉链表作为存储结构的树（孩子兄弟表示法），或者用类似方法存储的森林
		//如果为0，这棵二叉树是未被线索化的二叉树，如果为1，是先序线索二叉树
		//如果为2，是中序线索二叉树，如果为3，是后序线索二叉树
		int thread;
		//对应先序/中序/后序线索二叉树的第一个结点和最后一个结点
		struct bitree* head;
		struct bitree* tail;
		bool Huffman;//如果为false，这棵树不是赫夫曼树，如果为true，这棵树是赫夫曼树
	};
	tree_manage* tree_m;

public:
	//基本功能
	explicit TREE(const bool Huffman, const int type, const bool Tree, const bool help);//默认构造函数
	~TREE();//默认析构函数
	TREE& operator=(const TREE& x);//重载赋值运算符
	TREE(const TREE& x);//复制构造函数

	//第六章：树和二叉树
	void Silence_T();//开启调试输出
	void Silence_F();//关闭调试输出
	void Preorder() const;//先序遍历二叉树
	void Inorder() const;//中序遍历二叉树
	void Inorder_nostack() const;//中序遍历二叉树，使用parent域，不使用栈
	void Postorder_A() const;//更好的后序遍历算法，栈中所有结点都是当前结点的祖先
	void Postorder_B() const;//后序遍历二叉树
	void Level() const;//层序遍历二叉树
	void Tree_thread(const int order);//二叉树线索化
	void Tree_nonthread();//二叉树去线索化
	int Tree_thread_type() const;//返回二叉树被线索化的类型
	void Convert_tree();//将二叉树标记为使用二叉链表作为存储结构的树或者森林
	void Convert_nontree();//将用二叉链表作为存储结构的树或者森林标记为普通的二叉树
	long long Num_leaf() const;//叶子结点的数量（二叉树/树/森林）
	long long Num_nonleaf() const;//非叶子结点的数量（二叉树/树/森林）
	void Cleartree();//将二叉树清空
	void Repairtree();//若树不存在(tree_m=nullptr)，创建一棵空树。若树存在，不执行任何操作。该函数不可代替Cleartree函数
	long long Depth() const;//二叉树的深度（二叉树/树/森林）
	bool Complete() const;//二叉树是否为完全二叉树
	void Info() const;//输出二叉树的全部信息
	void ExchangeLR();//交换二叉树所有结点的左右子树
	long long Max_level_node() const;//二叉树每层结点数的最大值
	Type L_C_A(const long long a, const long long b) const;//二叉树两个结点的最小公共祖先，a/b是层序序列下两个结点的编号
	void Longest_path() const;//输出二叉树中最长的路径（若有多条，输出叶子结点最靠左的那条）
	void Print_Preorder(const bool guide) const;//以凹入表形式打印二叉树（可选是否打印辅助线）（二叉树/树/森林）
	void Print_Inorder() const;//树状打印二叉树，不可以打印树/森林，不支持打印辅助线
	void Print_arithmetic() const;//按照算术表达式形式打印二叉树
	long long Degree() const;//返回树或二叉树的度（二叉树/树/森林）
	void Huffman_create();//创建一个赫夫曼树
	long double W_P_L() const;//计算赫夫曼树的带权路径长度
	template<typename Type>
	friend bool Similar(const TREE<Type>& a, const TREE<Type>& b);//判断二叉树是否相似（结点结构相同但是值可以不同）
};

template<typename Type>
TREE<Type>::TREE(const bool Huffman, const int type, const bool Tree, const bool help)
{
	//不可能使用中序序列和先序序列/后序序列创建一棵树。因为当树中有重复元素时，创建出的树可能不唯一。
	//比如，无法根据先序序列666666666，中序序列666666666创建出一棵唯一的树。
	//唯一的方法是输入树的遍历序列，并用约定好的符号表示空的子树。
	tree_m = nullptr;
	//使用白名单来确定输入的类型在不在本程序支持的范围内
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
		cout << "\033[1;31m【错误】程序目前不支持创建此类型的树\033[0m" << endl;
		tree_m = nullptr;
		cout << "\033[1;31m【错误】无法正确创建树，析构函数将被调用\033[0m" << endl;
		this->~TREE();
		return;
	}
	//生成非赫夫曼树时，输入的help，Tree和Type参数才有实际作用
	//生成赫夫曼树时，无论输入的Tree变量是什么，二叉树的tree域都是false。此时允许向type变量提供任何参数，
	//   且程序不会输出任何帮助信息
	if (Huffman == true)
	{
		Huffman_create();
		return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】输入的二叉树遍历序列的编号有错误，无法进行创建二叉树的操作，默认构造函数将退出\033[0m" << endl;
		return;
	}
	if (help == true)
	{
		cout << "请仔细阅读下列输入规则：" << endl;
		cout << "需要按照先序序列或层序序列输入一棵树。输入的字符（包括表示空子树的字符）必须不多不少可以构成一棵树，并且不能有错误" << endl;
		cout << "如果输入的序列不能构成一棵树，或者输入的序列多于或少于构成一棵树所必需的序列，树不会被构建，并将被删除" << endl;
		cout << endl;
		cout << "如果要输入非char数据，转义字符是2" << endl;
		cout << "1-->如果要输入空子树，请输入数字0" << endl;
		cout << "2-->如果要输入数字0，请按顺序输入两个数字2，0" << endl;
		cout << "3-->如果要输入数字2，请按顺序输入两个数字2，5" << endl;
		cout << "2后面必须是0或者5中的一个，否则视为错误" << endl;
		cout << endl;
		cout << "如果要输入char或类char数据，转义字符是;（英文分号）" << endl;
		cout << "1-->如果要输入空子树，请输入字符.（英文句点）" << endl;
		cout << "2-->如果要输入字符.（英文句点），请按顺序输入两个字符;（英文分号）.（英文句点）" << endl;
		cout << "3-->如果要输入字符;（英文分号），请按顺序输入两个字符;（英文分号）,（英文逗号）" << endl;
		cout << ";（英文分号）后面必须是.（英文句点）或者,（英文逗号）中的一个，否则视为错误" << endl;
		cout << endl;
	}

	if (type == 0)
		cout << "【提示】请按照先序序列输入一棵树：" << endl;
	if (type == 1)
		cout << "【提示】请按照层序序列输入一棵树：" << endl;
	LIST<Type> input(1);
	if (input.Listlength() == 0)
	{
		tree_m = new tree_manage;
		tree_m->root = nullptr;
		tree_m->tree = Tree;
		tree_m->thread = 0;
		tree_m->head = nullptr;
		tree_m->tail = nullptr;
		tree_m->Huffman = false;
		cout << "\033[1;33m【警告】输入流的长度为0，已创建一棵空树\033[0m" << endl;
		//此处不需要主动调用LIST类的析构函数。LIST类的析构函数会被自动调用
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		int order;
		struct tree_generate* next;
	};
	//这里不能在type=0时不创建队头指针与队尾指针，或者在type=1时不创建栈顶指针。
	//如果选择性地创建指针，程序无法在下面的do-while循环中通过编译
	tree_generate* tree_stack_top = nullptr;
	tree_generate* tree_queue_head = nullptr;
	tree_generate* tree_queue_tail = nullptr;
	bool badinput = false;
	int badtype = 0;
	struct LIST<Type>::node* scan = input.ptr1->first;
	long long scan_num = 1;
	tree_m = new tree_manage;
	tree_m->root = nullptr;
	tree_m->tree = Tree;
	tree_m->thread = 0;
	tree_m->head = nullptr;
	tree_m->tail = nullptr;
	tree_m->Huffman = false;

	do
	{
		bool nulltree = false;
		Type data_input = static_cast<Type>(0);
		if (scan != nullptr)//输入流没有意外地提前结束（能读取到字符）
		{
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
			{
				if (scan->element != static_cast<Type>('.') && scan->element != static_cast<Type>(';'))
				{
					nulltree = false;
					data_input = static_cast<Type>(scan->element);
				}
				if (scan->element == static_cast<Type>('.'))//空子树
				{
					nulltree = true;
					data_input = static_cast<Type>(0);
				}
				if (scan->element == static_cast<Type>(';') && scan->next == nullptr)//转义字符
				{
					nulltree = true;
					badinput = true;
					badtype = 3;
					data_input = static_cast<Type>(0);
				}
				if (scan->element == static_cast<Type>(';') && scan->next != nullptr)//转义字符
				{
					if (scan->next->element != static_cast<Type>('.') && scan->next->element != static_cast<Type>(','))
					{
						nulltree = true;
						badinput = true;
						badtype = 3;
						data_input = static_cast<Type>(0);
					}
					if (scan->next->element == static_cast<Type>('.'))
					{
						nulltree = false;
						data_input = static_cast<Type>('.');
						scan = scan->next;
						scan_num = scan_num + 1;
					}
					if (scan->next->element == static_cast<Type>(','))
					{
						nulltree = false;
						data_input = static_cast<Type>(';');
						scan = scan->next;
						scan_num = scan_num + 1;
					}
				}
				scan = scan->next;
				scan_num = scan_num + 1;
			}
			else//非char数据
			{
				if (scan->element != static_cast<Type>(0) && scan->element != static_cast<Type>(2))
				{
					nulltree = false;
					data_input = static_cast<Type>(scan->element);
				}
				if (scan->element == static_cast<Type>(0))//空子树
				{
					nulltree = true;
					data_input = static_cast<Type>(0);
				}
				if (scan->element == static_cast<Type>(2) && scan->next == nullptr)//转义字符
				{
					nulltree = true;
					badinput = true;
					badtype = 4;
					data_input = static_cast<Type>(0);
				}
				if (scan->element == static_cast<Type>(2) && scan->next != nullptr)//转义字符
				{
					if (scan->next->element != static_cast<Type>(0) && scan->next->element != static_cast<Type>(5))
					{
						nulltree = true;
						badinput = true;
						badtype = 4;
						data_input = static_cast<Type>(0);
					}
					if (scan->next->element == static_cast<Type>(0))
					{
						nulltree = false;
						data_input = static_cast<Type>(0);
						scan = scan->next;
						scan_num = scan_num + 1;
					}
					if (scan->next->element == static_cast<Type>(5))
					{
						nulltree = false;
						data_input = static_cast<Type>(2);
						scan = scan->next;
						scan_num = scan_num + 1;
					}
				}
				scan = scan->next;
				scan_num = scan_num + 1;
			}
		}
		else//输入流意外地提前结束
		{
			nulltree = true;
			badinput = true;
			badtype = 1;
			data_input = static_cast<Type>(0);
		}

		if (nulltree == true)//结点为空
		{
			if ((type == 0 && tree_stack_top == nullptr) ||
				(type == 1 && tree_queue_head == nullptr && tree_queue_tail == nullptr))//正在处理根结点
			{
				cout << "\033[1;33m【警告】输入流的第一个字符要求创建一个空结点。已创建一棵空树\033[0m" << endl;
				break;
			}
			else
			{
				if (type == 0)//使用先序序列创建二叉树
				{
					tree_generate* tree_stack_backup = tree_stack_top;
					tree_stack_top = tree_stack_top->next;
					//由于lchild，rchild域在结点生成的时候已被赋值为nullptr，这里没有必要再次将其赋值为nullptr
					delete tree_stack_backup;
				}
				if (type == 1)//使用层序序列创建二叉树
				{
					if (tree_queue_head == tree_queue_tail)//如果只有一个结点
					{
						delete tree_queue_head;
						tree_queue_head = nullptr;
						tree_queue_tail = nullptr;
					}
					else
					{
						tree_generate* tree_queue_temp = tree_queue_head;
						tree_queue_head = tree_queue_head->next;
						delete tree_queue_temp;
					}
				}
			}
		}
		else//结点非空
		{
			if ((type == 0 && tree_stack_top == nullptr) ||
				(type == 1 && tree_queue_head == nullptr && tree_queue_tail == nullptr))//正在处理根结点
			{
				bitree* tree_temp = new bitree;
				tree_m->root = tree_temp;
				tree_temp->lchild = nullptr;
				tree_temp->ltag = false;
				tree_temp->weight = 0;
				tree_temp->data = data_input;
				tree_temp->parent = nullptr;
				tree_temp->rtag = false;
				tree_temp->rchild = nullptr;
				if (type == 0)//使用先序序列创建二叉树
				{
					tree_generate* tree_stack_backup_R = new tree_generate;
					tree_stack_backup_R->treeptr = tree_temp;
					tree_stack_backup_R->order = 1;//右子树先入栈
					tree_stack_backup_R->next = tree_stack_top;
					tree_stack_top = tree_stack_backup_R;
					tree_generate* tree_stack_backup_L = new tree_generate;
					tree_stack_backup_L->treeptr = tree_temp;
					tree_stack_backup_L->order = -1;//左子树后入栈
					tree_stack_backup_L->next = tree_stack_top;
					tree_stack_top = tree_stack_backup_L;
				}
				if (type == 1)//使用层序序列创建二叉树
				{
					//左子树先进入队列，此处不需要按照队列是否为空分类讨论，因为正在处理根结点，队列必然为空
					tree_generate* tree_queue_L = new tree_generate;
					tree_queue_L->treeptr = tree_temp;
					tree_queue_L->order = -1;
					tree_queue_L->next = nullptr;
					tree_queue_head = tree_queue_L;
					tree_queue_tail = tree_queue_L;
					//右子树后进入队列，此处不需要按照队列是否为空分类讨论，因为左子树已插入，队列必然非空
					tree_generate* tree_queue_R = new tree_generate;
					tree_queue_R->treeptr = tree_temp;
					tree_queue_R->order = 1;
					tree_queue_R->next = nullptr;
					tree_queue_tail->next = tree_queue_R;
					tree_queue_tail = tree_queue_tail->next;
				}
			}
			else//正在处理的不是根结点
			{
				//无论type取值如何，必须创建以下两个指针，否则无法通过编译
				tree_generate* tree_stack_backup = tree_stack_top;
				tree_generate* tree_queue_backup = tree_queue_head;
				if (type == 0)
					tree_stack_top = tree_stack_top->next;
				if (type == 1)
				{
					if (tree_queue_head == tree_queue_tail)//如果队列中只有一个元素
					{
						tree_queue_head = nullptr;
						tree_queue_tail = nullptr;
					}
					else
						tree_queue_head = tree_queue_head->next;
				}
				bitree* tree_temp = new bitree;
				tree_temp->lchild = nullptr;
				tree_temp->ltag = false;
				tree_temp->weight = 0;
				tree_temp->data = data_input;
				if (type == 0)
					tree_temp->parent = tree_stack_backup->treeptr;
				if (type == 1)
					tree_temp->parent = tree_queue_backup->treeptr;
				tree_temp->rtag = false;
				tree_temp->rchild = nullptr;
				if (type == 0)
				{
					if (tree_stack_backup->order == -1)
						tree_stack_backup->treeptr->lchild = tree_temp;
					if (tree_stack_backup->order == 1)
						tree_stack_backup->treeptr->rchild = tree_temp;
					delete tree_stack_backup;
					tree_generate* tree_stack_backup_R = new tree_generate;
					tree_stack_backup_R->treeptr = tree_temp;
					tree_stack_backup_R->order = 1;//右子树先入栈
					tree_stack_backup_R->next = tree_stack_top;
					tree_stack_top = tree_stack_backup_R;
					tree_generate* tree_stack_backup_L = new tree_generate;
					tree_stack_backup_L->treeptr = tree_temp;
					tree_stack_backup_L->order = -1;//左子树后入栈
					tree_stack_backup_L->next = tree_stack_top;
					tree_stack_top = tree_stack_backup_L;
				}
				if (type == 1)
				{
					if (tree_queue_backup->order == -1)
						tree_queue_backup->treeptr->lchild = tree_temp;
					if (tree_queue_backup->order == 1)
						tree_queue_backup->treeptr->rchild = tree_temp;
					delete tree_queue_backup;
					tree_generate* tree_queue_L = new tree_generate;
					tree_queue_L->treeptr = tree_temp;
					tree_queue_L->order = -1;//左子树先进入队列
					tree_queue_L->next = nullptr;
					if (tree_queue_head == nullptr && tree_queue_tail == nullptr)//队列为空
					{
						tree_queue_head = tree_queue_L;
						tree_queue_tail = tree_queue_L;
					}
					else
					{
						tree_queue_tail->next = tree_queue_L;
						tree_queue_tail = tree_queue_tail->next;
					}
					tree_generate* tree_queue_R = new tree_generate;
					tree_queue_R->treeptr = tree_temp;
					tree_queue_R->order = 1;//右子树后进入队列
					tree_queue_R->next = nullptr;
					tree_queue_tail->next = tree_queue_R;//左子树已进入队列，队列一定非空
					tree_queue_tail = tree_queue_tail->next;
				}
			}
		}
	} while ((type == 0 && tree_stack_top != nullptr) ||
		(type == 1 && tree_queue_head != nullptr && tree_queue_tail != nullptr));
	if (scan != nullptr)//输入流仍未结束
	{
		badinput = true;
		badtype = 2;
	}

	if (badinput == true)
	{
		if (badtype == 1)
			cout << "\033[1;31m【错误】输入的序列少于构成一棵树所必需的序列，树将被销毁\033[0m" << endl;
		if (badtype == 2)
			cout << "\033[1;31m【错误】输入的序列多于构成一棵树所必需的序列，树将被销毁\033[0m" << endl;
		if (badtype == 3)
		{
			cout << "\033[1;31m【错误】输入流存在错误，转义字符;（英文分号）后面的字符不是\033[0m" << endl;
			cout << "\033[1;31m\t.（英文句点）,（英文逗号）中的任何一个字符。树将被销毁\033[0m" << endl;
		}
		if (badtype == 4)
			cout << "\033[1;31m【错误】输入流存在错误，转义字符2后面的数字不是0，5中的任何一个数字。树将被销毁\033[0m" << endl;
		if (help == false)
			cout << "\033[1; 33m【提示】如果不清楚错误出现的原因，请打开帮助(将help参数设置为true)\033[0m" << endl;
		this->~TREE();
	}
	return;
}

template<typename Type>
TREE<Type>::~TREE()
{
	if (SILENCE == false)
		cout << "【提示】TREE类的析构函数被调用" << endl;
	if (tree_m == nullptr)
		return;
	if (tree_m->root == nullptr)
	{
		delete tree_m;
		tree_m = nullptr;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
		delete tree_stack_backup;
	}
	delete tree_m;
	tree_m = nullptr;
	return;
}

template<typename Type>
TREE<Type>& TREE<Type>::operator=(const TREE& x)
{
	if (x.tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法执行任何操作\033[0m" << endl;
		return *this;
	}
	if (x.tree_m->thread != 0 && x.tree_m->thread != 1 && x.tree_m->thread != 2 && x.tree_m->thread != 3)
	{
		cout << "\033[1;31m【错误】树被线索化为错误的类型，无法执行赋值操作\033[0m" << endl;
		return *this;
	}
	if (SILENCE == false)
		cout << "【提示】TREE类的重载的赋值运算符被调用" << endl;
	if (this == &x)
		return *this;
	this->~TREE();

	tree_m = new tree_manage;
	tree_m->root = nullptr;
	tree_m->tree = x.tree_m->tree;
	tree_m->thread = 0;//这里必须置为0，否则将来对其线索化时会出错
	//此处不可以将head，tail域赋值，否则会出错。需要单独调用线索化二叉树的函数
	tree_m->Huffman = x.tree_m->Huffman;
	if (x.tree_m->root == nullptr)
	{
		tree_m->head = nullptr;
		tree_m->tail = nullptr;
		return *this;
	}

	struct tree_generate
	{
		bitree* treeptrA;//指向赋值号左边的二叉树结点
		bitree* treeptrB;//指向赋值号右边的二叉树结点
		struct tree_generate* next;
	};
	tree_m->root = new bitree;
	tree_m->root->lchild = nullptr;
	tree_m->root->ltag = false;
	tree_m->root->weight = x.tree_m->root->weight;
	tree_m->root->data = x.tree_m->root->data;
	tree_m->root->parent = nullptr;
	tree_m->root->rtag = false;
	tree_m->root->rchild = nullptr;
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptrA = tree_m->root;
	tree_stack_top->treeptrB = x.tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptrB->rchild != nullptr && tree_stack_backup->treeptrB->rtag == false)//右子树先入栈
		{
			bitree* temp = new bitree;
			temp->lchild = nullptr;
			temp->ltag = false;
			temp->weight = tree_stack_backup->treeptrB->rchild->weight;
			temp->data = tree_stack_backup->treeptrB->rchild->data;
			temp->parent = tree_stack_backup->treeptrA;
			temp->rtag = false;
			temp->rchild = nullptr;
			tree_stack_backup->treeptrA->rchild = temp;
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptrA = temp;
			tree_stack_R->treeptrB = tree_stack_backup->treeptrB->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptrB->lchild != nullptr && tree_stack_backup->treeptrB->ltag == false)//左子树后入栈
		{
			bitree* temp = new bitree;
			temp->lchild = nullptr;
			temp->ltag = false;
			temp->weight = tree_stack_backup->treeptrB->lchild->weight;
			temp->data = tree_stack_backup->treeptrB->lchild->data;
			temp->parent = tree_stack_backup->treeptrA;
			temp->rtag = false;
			temp->rchild = nullptr;
			tree_stack_backup->treeptrA->lchild = temp;
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptrA = temp;
			tree_stack_L->treeptrB = tree_stack_backup->treeptrB->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	//若x只有一个结点，根据线索化函数，x无法被线索化，x的thread域一定为0
	if (x.tree_m->thread != 0)//x已被线索化，x的结点数一定大于1
		Tree_thread(x.tree_m->thread);
	return *this;
}

template<typename Type>
TREE<Type>::TREE(const TREE& x)
{
	if (x.tree_m == nullptr)
	{
		tree_m = nullptr;
		cout << "\033[1;31m【错误】树不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (x.tree_m->thread != 0 && x.tree_m->thread != 1 && x.tree_m->thread != 2 && x.tree_m->thread != 3)
	{
		tree_m = nullptr;
		cout << "\033[1;31m【错误】树被线索化为错误的类型，无法执行复制构造操作\033[0m" << endl;
		return;
	}
	if (SILENCE == false)
		cout << "【提示】TREE类的复制构造函数被调用" << endl;

	tree_m = new tree_manage;
	tree_m->root = nullptr;
	tree_m->tree = x.tree_m->tree;
	tree_m->thread = 0;//这里必须置为0，否则将来对其线索化时会出错
	//此处不可以将head，tail域赋值，否则会出错。需要单独调用线索化二叉树的函数
	tree_m->Huffman = x.tree_m->Huffman;
	if (x.tree_m->root == nullptr)
	{
		tree_m->head = nullptr;
		tree_m->tail = nullptr;
		return;
	}

	struct tree_generate
	{
		bitree* treeptrA;//指向赋值号左边的二叉树结点
		bitree* treeptrB;//指向赋值号右边的二叉树结点
		struct tree_generate* next;
	};
	tree_m->root = new bitree;
	tree_m->root->lchild = nullptr;
	tree_m->root->ltag = false;
	tree_m->root->weight = x.tree_m->root->weight;
	tree_m->root->data = x.tree_m->root->data;
	tree_m->root->parent = nullptr;
	tree_m->root->rtag = false;
	tree_m->root->rchild = nullptr;
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptrA = tree_m->root;
	tree_stack_top->treeptrB = x.tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptrB->rchild != nullptr && tree_stack_backup->treeptrB->rtag == false)//右子树先入栈
		{
			bitree* temp = new bitree;
			temp->lchild = nullptr;
			temp->ltag = false;
			temp->weight = tree_stack_backup->treeptrB->rchild->weight;
			temp->data = tree_stack_backup->treeptrB->rchild->data;
			temp->parent = tree_stack_backup->treeptrA;
			temp->rtag = false;
			temp->rchild = nullptr;
			tree_stack_backup->treeptrA->rchild = temp;
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptrA = temp;
			tree_stack_R->treeptrB = tree_stack_backup->treeptrB->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptrB->lchild != nullptr && tree_stack_backup->treeptrB->ltag == false)//左子树后入栈
		{
			bitree* temp = new bitree;
			temp->lchild = nullptr;
			temp->ltag = false;
			temp->weight = tree_stack_backup->treeptrB->lchild->weight;
			temp->data = tree_stack_backup->treeptrB->lchild->data;
			temp->parent = tree_stack_backup->treeptrA;
			temp->rtag = false;
			temp->rchild = nullptr;
			tree_stack_backup->treeptrA->lchild = temp;
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptrA = temp;
			tree_stack_L->treeptrB = tree_stack_backup->treeptrB->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	//若x只有一个结点，根据线索化函数，x无法被线索化，x的thread域一定为0
	if (x.tree_m->thread != 0)//x已被线索化，x的结点数一定大于1
		Tree_thread(x.tree_m->thread);
	return;
}

template<typename Type>
void TREE<Type>::Silence_T()
{
	SILENCE = true;
	return;
}

template<typename Type>
void TREE<Type>::Silence_F()
{
	SILENCE = false;
	return;
}

template<typename Type>
void TREE<Type>::Preorder() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;
	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
			cout << tree_stack_backup->treeptr->data;
		else
			cout << tree_stack_backup->treeptr->data << "   ";
		if (tree_m->Huffman == true)
		{
			Huffman_output* Huffman_queue_new = new Huffman_output;
			Huffman_queue_new->weight = tree_stack_backup->treeptr->weight;
			if (Huffman_queue_head == nullptr)
			{
				Huffman_queue_new->prior = nullptr;
				Huffman_queue_new->next = nullptr;
				Huffman_queue_head = Huffman_queue_new;
				Huffman_queue_tail = Huffman_queue_new;
			}
			else
			{
				Huffman_queue_new->prior = Huffman_queue_tail;
				Huffman_queue_tail->next = Huffman_queue_new;
				Huffman_queue_new->next = nullptr;
				Huffman_queue_tail = Huffman_queue_new;
			}
		}
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【先序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Inorder() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = nullptr;
	bitree* temp = tree_m->root;
	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;

	while (temp != nullptr || tree_stack_top != nullptr)
	{
		if (temp != nullptr)
		{
			tree_generate* tree_stack_backup = new tree_generate;
			tree_stack_backup->next = tree_stack_top;
			tree_stack_backup->treeptr = temp;
			tree_stack_top = tree_stack_backup;
			if (temp->ltag == true || temp->lchild == nullptr)//左子树为空
				temp = nullptr;
			else
				temp = temp->lchild;
		}
		else
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			temp = tree_stack_backup->treeptr;
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
				cout << temp->data;
			else
				cout << temp->data << "   ";
			if (tree_m->Huffman == true)
			{
				Huffman_output* Huffman_queue_new = new Huffman_output;
				Huffman_queue_new->weight = temp->weight;
				if (Huffman_queue_head == nullptr)
				{
					Huffman_queue_new->prior = nullptr;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_head = Huffman_queue_new;
					Huffman_queue_tail = Huffman_queue_new;
				}
				else
				{
					Huffman_queue_new->prior = Huffman_queue_tail;
					Huffman_queue_tail->next = Huffman_queue_new;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_tail = Huffman_queue_new;
				}
			}
			tree_stack_top = tree_stack_top->next;
			if (temp->rtag == true || temp->rchild == nullptr)//右子树为空
				temp = nullptr;
			else
				temp = temp->rchild;
			delete tree_stack_backup;
		}
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【中序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Inorder_nostack() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;
	bool visit_node = true;
	bitree* current = tree_m->root;
	bitree* pre = current;
	while (true)
	{
		if (visit_node == true)
		{
			while (current->lchild != nullptr && current->ltag == false)//左子树存在
				current = current->lchild;
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
				cout << current->data;
			else
				cout << current->data << "   ";
			if (tree_m->Huffman == true)
			{
				Huffman_output* Huffman_queue_new = new Huffman_output;
				Huffman_queue_new->weight = current->weight;
				if (Huffman_queue_head == nullptr)
				{
					Huffman_queue_new->prior = nullptr;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_head = Huffman_queue_new;
					Huffman_queue_tail = Huffman_queue_new;
				}
				else
				{
					Huffman_queue_new->prior = Huffman_queue_tail;
					Huffman_queue_tail->next = Huffman_queue_new;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_tail = Huffman_queue_new;
				}
			}
			if (current->rchild != nullptr && current->rtag == false)//右子树存在
			{
				current = current->rchild;
				continue;
			}
			else
			{
				visit_node = false;
				continue;
			}
		}
		else//需要访问双亲
		{
			pre = current;
			current = current->parent;
			if (pre == current->lchild)//从左子树返回
			{
				if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
					cout << current->data;
				else
					cout << current->data << "   ";
				if (tree_m->Huffman == true)
				{
					Huffman_output* Huffman_queue_new = new Huffman_output;
					Huffman_queue_new->weight = current->weight;
					if (Huffman_queue_head == nullptr)
					{
						Huffman_queue_new->prior = nullptr;
						Huffman_queue_new->next = nullptr;
						Huffman_queue_head = Huffman_queue_new;
						Huffman_queue_tail = Huffman_queue_new;
					}
					else
					{
						Huffman_queue_new->prior = Huffman_queue_tail;
						Huffman_queue_tail->next = Huffman_queue_new;
						Huffman_queue_new->next = nullptr;
						Huffman_queue_tail = Huffman_queue_new;
					}
				}
				if (current->rchild != nullptr && current->rtag == false)//右子树存在
				{
					visit_node = true;
					current = current->rchild;
					continue;
				}
				else
				{
					if (current == tree_m->root)
						break;
					else
						continue;//访问双亲
				}
			}
			else//从右子树返回
			{
				if (current == tree_m->root)
					break;
				else
					continue;//访问双亲
			}
		}
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【中序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Postorder_A() const
{
	//这个函数与中序非递归遍历函数很像
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = nullptr;
	bitree* current = tree_m->root;
	bitree* pre = nullptr;
	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;

	while (current != nullptr || tree_stack_top != nullptr)
	{
		if (current != nullptr)
		{
			tree_generate* tree_stack_backup = new tree_generate;
			tree_stack_backup->next = tree_stack_top;
			tree_stack_backup->treeptr = current;
			tree_stack_top = tree_stack_backup;
			if (current->ltag == true || current->lchild == nullptr)//左子树为空
				current = nullptr;
			else
				current = current->lchild;
		}
		else
		{
			current = tree_stack_top->treeptr;
			if ((current->rchild != nullptr && current->rtag == false) &&
				current->rchild != pre)
				current = current->rchild;
			else
			{
				tree_generate* tree_stack_delete = tree_stack_top;
				current = tree_stack_delete->treeptr;
				tree_stack_top = tree_stack_top->next;
				if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
					strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
					cout << current->data;
				else
					cout << current->data << "   ";
				if (tree_m->Huffman == true)
				{
					Huffman_output* Huffman_queue_new = new Huffman_output;
					Huffman_queue_new->weight = current->weight;
					if (Huffman_queue_head == nullptr)
					{
						Huffman_queue_new->prior = nullptr;
						Huffman_queue_new->next = nullptr;
						Huffman_queue_head = Huffman_queue_new;
						Huffman_queue_tail = Huffman_queue_new;
					}
					else
					{
						Huffman_queue_new->prior = Huffman_queue_tail;
						Huffman_queue_tail->next = Huffman_queue_new;
						Huffman_queue_new->next = nullptr;
						Huffman_queue_tail = Huffman_queue_new;
					}
				}
				pre = current;
				current = nullptr;
				delete tree_stack_delete;
			}
		}
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【后序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Postorder_B() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;
	bitree* current = nullptr;
	bitree* pre = nullptr;
	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;

	while (tree_stack_top != nullptr)
	{
		current = tree_stack_top->treeptr;
		if (((current->lchild == nullptr || current->ltag == true)
			&& (current->rchild == nullptr || current->rtag == true)) ||
			(current->ltag == false && current->lchild != nullptr && pre == current->lchild) ||
			(current->rtag == false && current->rchild != nullptr && pre == current->rchild))
		{
			//如果当前结点没有左子树且当前结点没有右子树 或者
			//当前结点存在左子树且前一个访问的结点是当前结点的左子树 或者
			//当前结点存在右子树且前一个访问的结点是当前结点的右子树
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
				cout << current->data;
			else
				cout << current->data << "   ";
			if (tree_m->Huffman == true)
			{
				Huffman_output* Huffman_queue_new = new Huffman_output;
				Huffman_queue_new->weight = current->weight;
				if (Huffman_queue_head == nullptr)
				{
					Huffman_queue_new->prior = nullptr;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_head = Huffman_queue_new;
					Huffman_queue_tail = Huffman_queue_new;
				}
				else
				{
					Huffman_queue_new->prior = Huffman_queue_tail;
					Huffman_queue_tail->next = Huffman_queue_new;
					Huffman_queue_new->next = nullptr;
					Huffman_queue_tail = Huffman_queue_new;
				}
			}
			tree_generate* tree_stack_backup = tree_stack_top;
			tree_stack_top = tree_stack_top->next;
			pre = current;
			delete tree_stack_backup;
		}
		else
		{
			if (current->rchild != nullptr && current->rtag == false)//右子树先入栈
			{
				tree_generate* tree_stack_backup = new tree_generate;
				tree_stack_backup->next = tree_stack_top;
				tree_stack_backup->treeptr = current->rchild;
				tree_stack_top = tree_stack_backup;
			}
			if (current->lchild != nullptr && current->ltag == false)//左子树后入栈
			{
				tree_generate* tree_stack_backup = new tree_generate;
				tree_stack_backup->next = tree_stack_top;
				tree_stack_backup->treeptr = current->lchild;
				tree_stack_top = tree_stack_backup;
			}
		}
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【后序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Level() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出任何元素\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出任何元素\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	struct Huffman_output
	{
		long double weight;
		struct Huffman_output* prior;
		struct Huffman_output* next;
	};
	Huffman_output* Huffman_queue_head = nullptr;
	Huffman_output* Huffman_queue_tail = nullptr;

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
			cout << tree_queue_backup->treeptr->data;
		else
			cout << tree_queue_backup->treeptr->data << "   ";
		if (tree_m->Huffman == true)
		{
			Huffman_output* Huffman_queue_new = new Huffman_output;
			Huffman_queue_new->weight = tree_queue_backup->treeptr->weight;
			if (Huffman_queue_head == nullptr)
			{
				Huffman_queue_new->prior = nullptr;
				Huffman_queue_new->next = nullptr;
				Huffman_queue_head = Huffman_queue_new;
				Huffman_queue_tail = Huffman_queue_new;
			}
			else
			{
				Huffman_queue_new->prior = Huffman_queue_tail;
				Huffman_queue_tail->next = Huffman_queue_new;
				Huffman_queue_new->next = nullptr;
				Huffman_queue_tail = Huffman_queue_new;
			}
		}
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树先进入队列
		{
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
		}
		if (tree_queue_backup == nullptr)
			return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)//右子树后进入队列
		{
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}
	cout << endl;

	if (tree_m->Huffman == true)
	{
		cout << "【层序序列下每个结点的权值】：";
		while (Huffman_queue_head != nullptr)
		{
			cout << Huffman_queue_head->weight << "   ";
			if (Huffman_queue_head == Huffman_queue_tail)
			{
				delete Huffman_queue_head;
				Huffman_queue_head = nullptr;
				Huffman_queue_tail = nullptr;
			}
			else
			{
				Huffman_output* Huffman_queue_delete = Huffman_queue_head;
				Huffman_queue_head->next->prior = nullptr;
				Huffman_queue_head = Huffman_queue_head->next;
				delete Huffman_queue_delete;
			}
		}
		cout << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Tree_thread(const int order)
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法进行线索化操作\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法进行线索化操作\033[0m" << endl;
		return;
	}
	if (tree_m->thread != 0)
	{
		cout << "\033[1;31m【错误】树已经被线索化，请将其去线索化后再进行线索化操作\033[0m" << endl;
		return;
	}
	if (tree_m->root->lchild == nullptr && tree_m->root->rchild == nullptr)
	{
		cout << "\033[1;31m【错误】树只有一个结点，无法进行线索化操作\033[0m" << endl;
		return;
	}
	//如果为1，是先序线索二叉树，如果为2，是中序线索二叉树，如果为3，是后序线索二叉树
	if (order != 1 && order != 2 && order != 3)
	{
		cout << "\033[1;31m【错误】输入的线索化类型有错误，无法进行线索化操作\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	bitree* pre = nullptr;
	bitree* current = nullptr;

	if (order == 1)//先序线索二叉树
	{
		tree_m->thread = 1;
		tree_generate* tree_stack_top = new tree_generate;
		tree_stack_top->treeptr = tree_m->root;
		tree_stack_top->next = nullptr;
		while (tree_stack_top != nullptr)
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			tree_stack_top = tree_stack_top->next;
			if (current == nullptr)//读取的是第一个结点
			{
				current = tree_stack_backup->treeptr;
				tree_m->head = current;
			}
			else//读取的不是第一个结点
			{
				pre = current;
				current = tree_stack_backup->treeptr;
				if (pre->rchild == nullptr)
				{
					pre->rtag = true;
					pre->rchild = current;
				}
				if (current->lchild == nullptr)
				{
					current->ltag = true;
					current->lchild = pre;
				}
			}
			if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
			{
				tree_generate* tree_stack_R = new tree_generate;
				tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
				tree_stack_R->next = tree_stack_top;
				tree_stack_top = tree_stack_R;
			}
			if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
			{
				tree_generate* tree_stack_L = new tree_generate;
				tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
				tree_stack_L->next = tree_stack_top;
				tree_stack_top = tree_stack_L;
			}
			delete tree_stack_backup;
		}
		tree_m->tail = current;
		cout << "【提示】二叉树已被先序线索化" << endl;
	}
	if (order == 2)//中序线索二叉树
	{
		tree_m->thread = 2;
		tree_generate* tree_stack_top = nullptr;
		bitree* temp = tree_m->root;
		while (temp != nullptr || tree_stack_top != nullptr)
		{
			if (temp != nullptr)
			{
				tree_generate* tree_stack_backup = new tree_generate;
				tree_stack_backup->next = tree_stack_top;
				tree_stack_backup->treeptr = temp;
				tree_stack_top = tree_stack_backup;
				if (temp->ltag == true || temp->lchild == nullptr)//左子树为空
					temp = nullptr;
				else
					temp = temp->lchild;
			}
			else
			{
				tree_generate* tree_stack_backup = tree_stack_top;
				temp = tree_stack_backup->treeptr;
				if (current == nullptr)//读取的是第一个结点
				{
					current = tree_stack_backup->treeptr;
					tree_m->head = current;
				}
				else//读取的不是第一个结点
				{
					pre = current;
					current = tree_stack_backup->treeptr;
					if (pre->rchild == nullptr)
					{
						pre->rtag = true;
						pre->rchild = current;
					}
					if (current->lchild == nullptr)
					{
						current->ltag = true;
						current->lchild = pre;
					}
				}
				tree_stack_top = tree_stack_top->next;
				if (temp->rtag == true || temp->rchild == nullptr)//右子树为空
					temp = nullptr;
				else
					temp = temp->rchild;
				delete tree_stack_backup;
			}
		}
		tree_m->tail = current;
		cout << "【提示】二叉树已被中序线索化" << endl;
	}
	if (order == 3)//后续线索二叉树
	{
		tree_m->thread = 3;
		tree_generate* tree_stack_top = new tree_generate;
		tree_stack_top->treeptr = tree_m->root;
		tree_stack_top->next = nullptr;
		bitree* currentX = nullptr;
		bitree* preX = nullptr;
		while (tree_stack_top != nullptr)
		{
			currentX = tree_stack_top->treeptr;
			if (((currentX->lchild == nullptr || currentX->ltag == true)
				&& (currentX->rchild == nullptr || currentX->rtag == true)) ||
				(currentX->ltag == false && currentX->lchild != nullptr && preX == currentX->lchild) ||
				(currentX->rtag == false && currentX->rchild != nullptr && preX == currentX->rchild))
			{
				//如果当前结点没有左子树且当前结点没有右子树 或者
				//当前结点存在左子树且前一个访问的结点是当前结点的左子树 或者
				//当前结点存在右子树且前一个访问的结点是当前结点的右子树
				if (current == nullptr)//读取的是第一个结点
				{
					current = tree_stack_top->treeptr;
					tree_m->head = current;
				}
				else//读取的不是第一个结点
				{
					pre = current;
					current = tree_stack_top->treeptr;
					if (pre->rchild == nullptr)
					{
						pre->rtag = true;
						pre->rchild = current;
					}
					if (current->lchild == nullptr)
					{
						current->ltag = true;
						current->lchild = pre;
					}
				}
				tree_generate* tree_stack_backup = tree_stack_top;
				tree_stack_top = tree_stack_top->next;
				preX = currentX;
				delete tree_stack_backup;
			}
			else
			{
				if (currentX->rchild != nullptr && currentX->rtag == false)//右子树先入栈
				{
					tree_generate* tree_stack_backup = new tree_generate;
					tree_stack_backup->next = tree_stack_top;
					tree_stack_backup->treeptr = currentX->rchild;
					tree_stack_top = tree_stack_backup;
				}
				if (currentX->lchild != nullptr && currentX->ltag == false)//左子树后入栈
				{
					tree_generate* tree_stack_backup = new tree_generate;
					tree_stack_backup->next = tree_stack_top;
					tree_stack_backup->treeptr = currentX->lchild;
					tree_stack_top = tree_stack_backup;
				}
			}
		}
		tree_m->tail = current;
		cout << "【提示】二叉树已被后序线索化" << endl;
	}
	return;
}

template<typename Type>
void TREE<Type>::Tree_nonthread()
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法进行去线索化操作\033[0m" << endl;
		return;
	}
	tree_m->thread = 0;
	tree_m->head = nullptr;
	tree_m->tail = nullptr;
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法进行去线索化操作\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr)//左子树为空
		{
			tree_stack_backup->treeptr->ltag = false;
			tree_stack_backup->treeptr->lchild = nullptr;
		}
		if (tree_stack_backup->treeptr->rtag == true || tree_stack_backup->treeptr->rchild == nullptr)//右子树为空
		{
			tree_stack_backup->treeptr->rtag = false;
			tree_stack_backup->treeptr->rchild = nullptr;
		}
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	return;
}

template<typename Type>
int TREE<Type>::Tree_thread_type() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出二叉树被线索化的类型\033[0m" << endl;
		return static_cast<int>(10);
	}
	if (tree_m->thread != 0 && tree_m->thread != 1 && tree_m->thread != 2 && tree_m->thread != 3)
	{
		cout << "\033[1;31m【错误】二叉树被线索化为错误的类型，无法输出二叉树被线索化的类型\033[0m" << endl;
		return static_cast<int>(10);
	}
	return tree_m->thread;
}

template<typename Type>
void TREE<Type>::Convert_tree()
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法将二叉树标记为使用二叉链表作为存储结构的树或者森林\033[0m" << endl;
		return;
	}
	if (tree_m->tree == true)
	{
		cout << "\033[1;31m【错误】二叉树已被标记为使用二叉链表作为存储结构的树或者森林，无需再次进行相同的操作\033[0m" << endl;
		return;
	}
	tree_m->tree = true;
	return;
}

template<typename Type>
void TREE<Type>::Convert_nontree()
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法将用二叉链表作为存储结构的树或者森林标记为普通的二叉树\033[0m" << endl;
		return;
	}
	if (tree_m->tree == false)
	{
		cout << "\033[1;31m【错误】用二叉链表作为存储结构的树或者森林已被标记为普通的二叉树，无需再次进行相同的操作\033[0m" << endl;
		return;
	}
	tree_m->tree = false;
	return;
}

template<typename Type>
long long TREE<Type>::Num_leaf() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算叶子结点的数量\033[0m" << endl;
		return static_cast<long long>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法计算叶子结点的数量\033[0m" << endl;
		return static_cast<long long>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;
	long long count = 0;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if ((tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
			(tree_stack_backup->treeptr->rtag == true || tree_stack_backup->treeptr->rchild == nullptr) &&
			tree_m->tree == false)
			count = count + 1;//左右子树都为空
		if ((tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
			tree_m->tree == true)
			count = count + 1;//左子树为空
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	return count;
}

template<typename Type>
long long TREE<Type>::Num_nonleaf() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算非叶子结点的数量\033[0m" << endl;
		return static_cast<long long>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法计算非叶子结点的数量\033[0m" << endl;
		return static_cast<long long>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;
	long long count = 0;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (((tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false) ||
			(tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)) &&
			tree_m->tree == false)
			count = count + 1;//右子树非空或左子树非空
		if ((tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false) &&
			tree_m->tree == true)
			count = count + 1;//左子树非空
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	return count;
}

template<typename Type>
void TREE<Type>::Cleartree()
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法执行清空操作\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		tree_m->tree = false;
		tree_m->thread = 0;
		tree_m->head = nullptr;
		tree_m->tail = nullptr;
		tree_m->Huffman = false;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
	}
	tree_m->root = nullptr;
	tree_m->tree = false;
	tree_m->thread = 0;
	tree_m->head = nullptr;
	tree_m->tail = nullptr;
	tree_m->Huffman = false;
	return;
}

template<typename Type>
void TREE<Type>::Repairtree()
{
	if (tree_m == nullptr)
	{
		tree_m = new tree_manage;
		tree_m->root = nullptr;
		tree_m->tree = false;
		tree_m->thread = 0;
		tree_m->head = nullptr;
		tree_m->tail = nullptr;
		tree_m->Huffman = false;
	}
	else
		cout << "\033[1;31m【错误】树已存在，无需执行修复操作。注意：该函数不可代替Cleartree函数\033[0m" << endl;
	return;
}

template<typename Type>
long long TREE<Type>::Depth() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算树的深度\033[0m" << endl;
		return static_cast<long long>(0);
	}
	if (tree_m->root == nullptr)
		return static_cast<long long>(0);

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	long long depth = 1;//二叉树的深度
	bitree* rear = tree_queue_tail->treeptr;//指向当前层次的最后一个结点

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr && tree_m->tree == false)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树先进入队列
		{
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
		}
		if (tree_queue_backup == nullptr)
			return static_cast<long long>(0);//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)//右子树后进入队列
		{
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			if (tree_queue_head->treeptr == rear)
			{
				rear = tree_queue_tail->treeptr;
				depth = depth + 1;
			}
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}

	if (tree_m->tree == true)
	{
		if (tree_m->root->rchild != nullptr && tree_m->root->rtag == false)//根结点存在右子树
		{
			bitree* temp = tree_m->root->rchild;
			do
			{
				tree_generate* tree_queue_L = new tree_generate;
				tree_queue_L->treeptr = temp;
				tree_queue_L->next = nullptr;
				if (tree_queue_tail != nullptr)
				{
					tree_queue_tail->next = tree_queue_L;
					tree_queue_tail = tree_queue_tail->next;
				}
				else
				{
					tree_queue_tail = tree_queue_L;
					tree_queue_head = tree_queue_L;
				}
				if (temp->rchild != nullptr && temp->rtag == false)//temp有右子树
					temp = temp->rchild;
				else
				{
					rear = temp;
					temp = nullptr;
				}
			} while (temp != nullptr);
		}
	}
	while (tree_queue_head != nullptr && tree_queue_tail != nullptr && tree_m->tree == true)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树进入队列
		{
			bitree* temp = tree_queue_backup->treeptr->lchild;
			do
			{
				tree_generate* tree_queue_L = new tree_generate;
				tree_queue_L->treeptr = temp;
				tree_queue_L->next = nullptr;
				if (tree_queue_tail != nullptr)
				{
					tree_queue_tail->next = tree_queue_L;
					tree_queue_tail = tree_queue_tail->next;
				}
				else
				{
					tree_queue_tail = tree_queue_L;
					tree_queue_head = tree_queue_L;
				}
				if (temp->rchild != nullptr && temp->rtag == false)//temp有右子树
					temp = temp->rchild;
				else
					temp = nullptr;
			} while (temp != nullptr);
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			if (tree_queue_head->treeptr == rear)
			{
				rear = tree_queue_tail->treeptr;
				depth = depth + 1;
			}
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}
	return depth;
}

template<typename Type>
bool TREE<Type>::Complete() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法判断树是否为完全二叉树\033[0m" << endl;
		return false;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法判断树是否为完全二叉树\033[0m" << endl;
		return false;
	}

	//判断一棵树是否为满二叉树的算法：
	//1.该树通过了下面代码的检测，即这棵树是完全二叉树
	//2.进行层序扫描时，扫描到的最后一个结点是根结点的最靠右的子树
	//（只需要在本函数基础上加一丁点判定代码即可）
	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	bool child_finish = false;
	bool complete = true;

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (tree_queue_backup->treeptr->ltag == true || tree_queue_backup->treeptr->lchild == nullptr)
		{
			//若左子树为空
			child_finish = true;//此后在层序遍历的过程中，如果需要将任何子树加入队列，则不是完全二叉树
		}
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)
		{
			//若左子树非空，左子树先进入队列
			if (child_finish == true)//在已经被标记为“没有更多子树”的情况下再次出现子树，即二叉树不是完全二叉树
			{
				complete = false;
				while (tree_queue_head != tree_queue_tail)
				{
					tree_generate* tree_queue_temp = tree_queue_head;
					tree_queue_head = tree_queue_head->next;
					delete tree_queue_temp;
				}
				delete tree_queue_head;
				tree_queue_head = nullptr;
				tree_queue_tail = nullptr;
				break;//将队列手动清空后退出循环
			}
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
		}
		if (tree_queue_backup == nullptr)
			return false;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rtag == true || tree_queue_backup->treeptr->rchild == nullptr)
		{
			//若右子树为空
			child_finish = true;//此后在层序遍历的过程中，如果需要将任何子树加入队列，则不是完全二叉树
		}
		if (tree_queue_backup == nullptr)
			return false;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)
		{
			//若右子树非空，右子树后进入队列
			if (child_finish == true)//在已经被标记为“没有更多子树”的情况下再次出现子树，即二叉树不是完全二叉树
			{
				complete = false;
				while (tree_queue_head != tree_queue_tail)
				{
					tree_generate* tree_queue_temp = tree_queue_head;
					tree_queue_head = tree_queue_head->next;
					delete tree_queue_temp;
				}
				delete tree_queue_head;
				tree_queue_head = nullptr;
				tree_queue_tail = nullptr;
				break;//将队列手动清空后退出循环
			}
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}
	return complete;
}

template<typename Type>
void TREE<Type>::Info() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出树的任何信息\033[0m" << endl;
		return;
	}
	cout << endl;
	cout << "【提示】二叉树的基本信息：" << endl;
	if (tree_m->root == nullptr)
		cout << "【树是否存在】：否" << endl;
	else
		cout << "【树是否存在】：是" << endl;
	if (tree_m->tree == true)
		cout << "【树的类型】：使用二叉链表作为存储结构的树（孩子兄弟表示法），或者用类似方法存储的森林" << endl;
	else
		cout << "【树的类型】：二叉树" << endl;
	if (tree_m->root == nullptr)
		cout << "\033[1;31m【错误】树不存在，无法输出树的线索化信息\033[0m" << endl;
	else
	{
		if (tree_m->thread != 0 && tree_m->thread != 1 && tree_m->thread != 2 && tree_m->thread != 3)
			cout << "\033[1;31m【是否线索化】：二叉树被线索化为错误的类型，无法输出二叉树被线索化的类型\033[0m" << endl;
		if (tree_m->thread == 0)
			cout << "【是否线索化】：否" << endl;
		if (tree_m->thread == 1)
		{
			cout << "【是否线索化】：是" << endl;
			cout << "【线索化的类型】:先序线索化     【第一个结点的值】：" << tree_m->head->data;
			cout << "     【最后一个结点的值】：" << tree_m->tail->data << endl;
		}
		if (tree_m->thread == 2)
		{
			cout << "【是否线索化】：是" << endl;
			cout << "【线索化的类型】:中序线索化     【第一个结点的值】：" << tree_m->head->data;
			cout << "     【最后一个结点的值】：" << tree_m->tail->data << endl;
		}
		if (tree_m->thread == 3)
		{
			cout << "【是否线索化】：是" << endl;
			cout << "【线索化的类型】:后序线索化     【第一个结点的值】：" << tree_m->head->data;
			cout << "     【最后一个结点的值】：" << tree_m->tail->data << endl;
		}
	}
	if (tree_m->Huffman == true)
	{
		cout << "【是否为赫夫曼树】：是" << endl;
		if (tree_m->root != nullptr)
			cout << "【树的带权路径长度】：" << W_P_L() << endl;
	}
	else
		cout << "【是否为赫夫曼树】：否" << endl;

	if (tree_m->root != nullptr)
	{
		cout << endl;
		cout << "【提示】二叉树的更多信息：" << endl;
		cout << "【先序序列】：";
		Preorder();
		cout << "【中序序列】：";
		Inorder();
		cout << "【后序序列】：";
		Postorder_B();
		cout << "【层序序列】：";
		Level();
		cout << "【叶子结点的数量】：" << Num_leaf() << endl;
		cout << "【非叶子结点的数量】：" << Num_nonleaf() << endl;
		cout << "【二叉树的深度】：" << Depth() << endl;
		if (Complete() == true)
			cout << "【是否为完全二叉树】：是" << endl;
		else
			cout << "【是否为完全二叉树】：否" << endl;
		cout << "【二叉树每层结点数的最大值】：" << Max_level_node() << endl;
		cout << "【二叉树最长路径下每个结点的值】：";
		Longest_path();
		cout << "【树的度】：" << Degree() << endl;
	}
	else
	{
		cout << "\033[1;31m【错误】树为空，无法输出树的更多相关信息\033[0m" << endl;
	}
	cout << endl;
	return;
}

template<typename Type>
void TREE<Type>::ExchangeLR()
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法进行任何操作\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法进行任何操作\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		bitree* temp = tree_stack_backup->treeptr->lchild;
		tree_stack_backup->treeptr->lchild = tree_stack_backup->treeptr->rchild;
		tree_stack_backup->treeptr->rchild = temp;
		delete tree_stack_backup;
	}
	return;
}

template<typename Type>
long long TREE<Type>::Max_level_node() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算二叉树每层结点数的最大值\033[0m" << endl;
		return static_cast<long long>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法计算二叉树每层结点数的最大值\033[0m" << endl;
		return static_cast<long long>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	long long width = 0;//二叉树当前层次（从第二层开始）的结点数量
	long long max_width = 1;//二叉树每个层次的最大结点数量
	bitree* rear = tree_queue_tail->treeptr;//指向当前层次的最后一个结点

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树先进入队列
		{
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
			width = width + 1;
		}
		if (tree_queue_backup == nullptr)
			return static_cast<long long>(0);//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)//右子树后进入队列
		{
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
			width = width + 1;
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			if (tree_queue_head->treeptr == rear)//某一层已扫描完成
			{
				rear = tree_queue_tail->treeptr;
				if (width > max_width)
					max_width = width;
				width = 0;
			}
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}
	return max_width;
}

template<typename Type>
Type TREE<Type>::L_C_A(const long long a, const long long b) const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算最小公共祖先\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法计算最小公共祖先\033[0m" << endl;
		return static_cast<Type>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	bitree* target_A = nullptr;
	bitree* target_B = nullptr;
	long long count = 1;

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if (a == count)
			target_A = tree_queue_backup->treeptr;
		if (b == count)
			target_B = tree_queue_backup->treeptr;
		if (target_A != nullptr && target_B != nullptr)//若已找到两个目标结点，则清空队列并返回
		{
			while (tree_queue_head != tree_queue_tail)
			{
				tree_generate* tree_queue_temp = tree_queue_head;
				tree_queue_head = tree_queue_head->next;
				delete tree_queue_temp;
			}
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
			continue;
		}
		count = count + 1;
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树先进入队列
		{
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
		}
		if (tree_queue_backup == nullptr)
			return static_cast<Type>(0);//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)//右子树后进入队列
		{
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}

	if (target_A == nullptr)
	{
		cout << "\033[1;31m【错误】输入的第一个序号错误，无法找到第一个序号对应的结点，无法计算最小公共祖先\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (target_B == nullptr)
	{
		cout << "\033[1;31m【错误】输入的第二个序号错误，无法找到第二个序号对应的结点，无法计算最小公共祖先\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (a == b)
		return target_A->data;

	//根据二叉树的性质，给出任意两个结点，一定存在这两个结点的最小公共祖先
	//算法基于的原理：二叉树中，结点A的祖先在后序遍历序列中的位置一定在结点A的后面。
	//寻找最小公共祖先的基本思路：
	//定义C为指向目标结点A的祖先的指针。按照后序序列遍历二叉树时，设某次循环中被访问的结点是E。
	//		若E的左孩子存在且左孩子是A，或者E的右孩子存在且右孩子是A，则E是A的祖先，令C=E。
	//同理，定义D为指向目标结点B的祖先的指针。用相同方法在遍历过程中找到B的祖先F。令D=F。
	//如果发现C=D，则目标结点AB的最小共同祖先是C（或者D）。
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = tree_m->root;
	tree_stack_top->next = nullptr;
	bitree* current = nullptr;
	bitree* pre = nullptr;
	bitree* target_A_anc = target_A;//结点A的祖先
	bitree* target_B_anc = target_B;//结点B的祖先

	while (tree_stack_top != nullptr)
	{
		current = tree_stack_top->treeptr;
		if (((current->lchild == nullptr || current->ltag == true)
			&& (current->rchild == nullptr || current->rtag == true)) ||
			(current->ltag == false && current->lchild != nullptr && pre == current->lchild) ||
			(current->rtag == false && current->rchild != nullptr && pre == current->rchild))
		{
			//如果当前结点没有左子树且当前结点没有右子树 或者
			//当前结点存在左子树且前一个访问的结点是当前结点的左子树 或者
			//当前结点存在右子树且前一个访问的结点是当前结点的右子树
			if (current->rchild != nullptr && current->rtag == false && current->rchild == target_A_anc)
				target_A_anc = current;//当前结点存在右子树且右子树是结点A的祖先
			if (current->lchild != nullptr && current->ltag == false && current->lchild == target_A_anc)
				target_A_anc = current;//当前结点存在左子树且左子树是结点A的祖先
			if (current->rchild != nullptr && current->rtag == false && current->rchild == target_B_anc)
				target_B_anc = current;//当前结点存在右子树且右子树是结点B的祖先
			if (current->lchild != nullptr && current->ltag == false && current->lchild == target_B_anc)
				target_B_anc = current;//当前结点存在左子树且左子树是结点B的祖先
			if (target_A_anc == target_B_anc)
			{
				//找到最小公共结点
				while (tree_stack_top != nullptr)
				{
					tree_generate* tree_stack_delete = tree_stack_top;
					tree_stack_top = tree_stack_top->next;
					delete tree_stack_delete;
				}
				continue;
			}
			tree_generate* tree_stack_backup = tree_stack_top;
			tree_stack_top = tree_stack_top->next;
			pre = current;
			delete tree_stack_backup;
		}
		else
		{
			if (current->rchild != nullptr && current->rtag == false)//右子树先入栈
			{
				tree_generate* tree_stack_backup = new tree_generate;
				tree_stack_backup->next = tree_stack_top;
				tree_stack_backup->treeptr = current->rchild;
				tree_stack_top = tree_stack_backup;
			}
			if (current->lchild != nullptr && current->ltag == false)//左子树后入栈
			{
				tree_generate* tree_stack_backup = new tree_generate;
				tree_stack_backup->next = tree_stack_top;
				tree_stack_backup->treeptr = current->lchild;
				tree_stack_top = tree_stack_backup;
			}
		}
	}
	return target_A_anc->data;
}

template<typename Type>
void TREE<Type>::Longest_path() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出二叉树中最长的路径\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出二叉树中最长的路径\033[0m" << endl;
		return;
	}

	//有两种基本算法，算法的时间复杂度相似
	//方法A的基本原理（使用Postorder_A函数）：
	//  1.进行后序遍历时，工作栈的深度就是当前结点的深度
	//  2.遍历到某个元素时，从栈底到栈顶输出全部元素，刚好是该元素从根结点开始的全部祖先
	//  3.对于后序遍历时访问到的每一个结点，若当前栈顶深度大于记录到的历史最大栈顶深度，则清空最大深度栈，
	//    并将当前栈中的全部内容复制到最大深度栈
	//  4.完整进行一次后序遍历后，从栈底到栈顶输出最大深度栈中的全部元素，就得到从根结点开始的最长路径
	//起始条件：
	//    开始时，栈顶深度为0，最大栈顶深度为1，最大深度栈中只有根节点
	//时间复杂度：
	//    只进行一次后序遍历，就可以得到最长路径（比Postorder_B函数的时间复杂度小）
	//方法A的基本原理（使用Postorder_B函数）：
	//  1.在进行后序遍历时，如果触发下面这条路径：当前结点存在左子树且前一个访问的结点是当前结点的左子树  或者
	//    当前结点存在右子树且前一个访问的结点是当前结点的右子树，栈顶深度-1
	//  2.若对某个结点执行过进栈操作（无论将左子树进栈还是将右子树进栈），则栈顶深度+1
	//  3.在进行后序遍历的任何其它情况下，栈顶深度不变化
	//  4.对于后序遍历时访问到的每一个结点，若当前栈顶深度大于记录到的历史最大栈顶深度，则清空最大深度栈，
	//    并将当前栈中的全部内容复制到最大深度栈
	//  5.完整进行一次后序遍历后，从保存的最大深度栈开始，再进行一次后序遍历。输出最深节点的全部祖先后，遍历停止。
	//    （注意第二次遍历的停止条件其实就是遍历完成。因为根节点一定是最后一个被访问的结点）
	//  6.该方法可以保证当最长路径不唯一时，输出的是叶子结点最靠左的一条
	//  7.同理，不止层序遍历，后序遍历也可以用于计算二叉树的深度
	//起始条件：
	//    开始时，根节点入栈，栈顶深度为1，最大栈顶深度为1，最大深度栈中只有根节点
	//时间复杂度：
	//  1.首次后序遍历，找到最大深度栈（进行一次完整的遍历）
	//  2.第二次后序遍历，从最大深度栈开始遍历，直到输出全部祖先（或者遍历完成）（进行一次不完整的遍历）
	//方法B的时间复杂度：
	//  1.层序遍历，找到指向最深结点的指针（进行一次完整的遍历）
	//  2.后序遍历，从头开始，直到输出该指针的全部祖先（或者遍历完成）（进行一次完整的遍历，访问结点的次数比方法A第二步更多）
	//本函数采用方法A（使用Postorder_A函数）
	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* prior;//指向栈顶方向
		struct tree_generate* next;//指向栈底方向
	};
	tree_generate* tree_stack_head = nullptr;
	tree_generate* tree_stack_tail = nullptr;
	long long current_stack_depth = 0;
	tree_generate* max_stack_head = new tree_generate;
	max_stack_head->treeptr = tree_m->root;
	max_stack_head->prior = nullptr;
	max_stack_head->next = nullptr;
	tree_generate* max_stack_tail = max_stack_head;
	long long max_stack_depth = 1;
	bitree* current = tree_m->root;
	bitree* pre = nullptr;

	while (current != nullptr || tree_stack_head != nullptr)
	{
		if (current != nullptr)
		{
			//当前结点入栈
			tree_generate* tree_stack_new = new tree_generate;
			tree_stack_new->treeptr = current;
			tree_stack_new->prior = nullptr;
			tree_stack_new->next = tree_stack_head;
			if (tree_stack_head == nullptr)
			{
				tree_stack_head = tree_stack_new;
				tree_stack_tail = tree_stack_new;
			}
			else
			{
				tree_stack_head->prior = tree_stack_new;
				tree_stack_head = tree_stack_new;
			}
			current_stack_depth = current_stack_depth + 1;
			//若当前栈顶深度大于记录到的历史最大栈顶深度
			if (current_stack_depth > max_stack_depth)
			{
				max_stack_depth = current_stack_depth;
				while (max_stack_tail != nullptr)//清空最大深度栈
				{
					tree_generate* max_stack_delete = max_stack_tail;
					max_stack_tail = max_stack_tail->prior;
					delete max_stack_delete;
				}
				//将当前栈中的全部内容复制到最大深度栈
				tree_generate* tree_stack_copy = tree_stack_tail;
				tree_generate* max_stack_new = new tree_generate;
				max_stack_new->treeptr = tree_stack_copy->treeptr;
				max_stack_new->prior = nullptr;
				max_stack_new->next = nullptr;
				max_stack_head = max_stack_new;
				max_stack_tail = max_stack_new;
				tree_stack_copy = tree_stack_copy->prior;
				if (tree_stack_copy == nullptr)
					return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
				for (long long i = 2; i <= current_stack_depth; i++)
				{
					max_stack_new = new tree_generate;
					max_stack_new->treeptr = tree_stack_copy->treeptr;
					max_stack_new->next = max_stack_head;
					max_stack_new->prior = nullptr;
					max_stack_head->prior = max_stack_new;
					max_stack_head = max_stack_new;
					tree_stack_copy = tree_stack_copy->prior;
				}
			}
			if (current->ltag == true || current->lchild == nullptr)//左子树为空
				current = nullptr;
			else
				current = current->lchild;
		}
		else
		{
			current = tree_stack_head->treeptr;
			if ((current->rchild != nullptr && current->rtag == false) &&
				current->rchild != pre)
				current = current->rchild;
			else
			{
				pre = tree_stack_head->treeptr;
				current = nullptr;
				tree_generate* tree_stack_delete = tree_stack_head;
				tree_stack_head = tree_stack_head->next;
				delete tree_stack_delete;
				current_stack_depth = current_stack_depth - 1;
			}
		}
	}

	while (max_stack_tail != nullptr)
	{
		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
			cout << max_stack_tail->treeptr->data;
		else
			cout << max_stack_tail->treeptr->data << "   ";
		tree_generate* max_stack_delete = max_stack_tail;
		max_stack_tail = max_stack_tail->prior;
		delete max_stack_delete;
	}
	cout << endl;
	return;
}

template<typename Type>
void TREE<Type>::Print_Preorder(const bool guide) const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法打印二叉树\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法打印二叉树\033[0m" << endl;
		return;
	}

	//带有打印辅助线的输出格式模仿自Windows系统命令提示符的TREE命令
	//以下是打印辅助线版本的函数介绍（二叉树/树/森林通用）：
	//函数的基本原理：以凹入表形式打印二叉树时，从上到下刚好是一棵树的先序遍历序列。所以使用先序遍历
	//函数在打印节点元素值之前只会输出四种字符：├─，└─，│ 和空格。节点元素值左边的字符（若存在）只能是├─和└─
	//   ，其它位置的字符（若存在）只能是│ 和空格
	//函数不修改先序遍历使用的工作栈。函数引入了输出栈，包括symbol域（该输出哪个符号），next域和prior域。
	//   函数不需要记录工作栈和输出栈的栈顶深度
	//函数的起始条件是：输出栈为空，工作栈中只有根结点（二叉树），输出栈中只有├─元素，工作栈中只有根结点（树/森林）
	//函数将先序遍历的时序修改为：（保存当前栈顶指针）-->（若栈顶指针指向的元素存在左子树或右子树，
	//   则在栈顶指针的下一个位置将子树入栈）-->（A步）-->（B步）-->（C步）-->（进行一次退栈操作）
	//   注意这里的入栈操作不是普通的入栈操作（新元素放到栈顶），而是将新元素放到栈顶的下面
	//A步：打印输出栈+本次循环中访问的元素
	//   这里需要从栈底向栈顶打印（使用prior域）。栈顶紧贴着本次循环中访问的元素
	//B步：退栈
	//   1.若栈顶元素是└─，将其替换为空格。
	//   2.若栈顶元素是├─，将其替换为│ 。
	//   3.若栈顶元素是空格，且当前访问的结点没有子结点，则连续出栈直到栈顶元素不是空格或者栈为空。
	//C步：进栈
	//   1.若当前结点有多于一个子树，将├─进栈。
	//   2.若当前节点只有一个子树，将└─入栈。
	//   3.若当前结点没有子树，且工作栈中要访问的下一个结点存在，则将栈顶元素出栈。
	//        若工作栈中要访问的下一个结点有右兄弟，将├─入栈。否则将└─入栈
	//以下是不打印辅助线版本的函数的介绍（二叉树/树/森林通用）：
	//不使用输出栈，在工作栈中加一个depth域记录访问的每一个结点的深度即可。将子结点入栈时，子节点的深度＝当前结点深度+1
	//如果是树/森林，只有将左子树入栈时子节点的深度＝当前结点深度+1。否则子节点的深度＝当前结点深度
	if (guide == true)//打印辅助线
	{
		//初始化工作栈
		struct tree_generate
		{
			bitree* treeptr;
			struct tree_generate* next;
		};
		tree_generate* tree_stack_top = new tree_generate;
		tree_stack_top->treeptr = tree_m->root;
		tree_stack_top->next = nullptr;

		//初始化输出栈
		struct tree_output
		{
			int symbol;
			struct tree_output* prior;
			struct tree_output* next;
		};
		tree_output* output_stack_top = nullptr;
		tree_output* output_stack_tail = nullptr;

		cout << "【提示】以凹入表形式打印二叉树如下所示（使用辅助线）：" << endl;
		//如果是森林
		if (tree_m->tree == true && tree_m->root->rchild != nullptr && tree_m->root->rtag == false)
		{
			cout << endl << "森林的虚拟根结点" << endl;
			output_stack_top = new tree_output;
			output_stack_top->symbol = 1;
			output_stack_top->prior = nullptr;
			output_stack_top->next = nullptr;
			output_stack_tail = output_stack_top;
		}
		while (tree_stack_top != nullptr)
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
			{
				tree_generate* tree_stack_R = new tree_generate;
				tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
				tree_stack_R->next = tree_stack_top->next;
				tree_stack_top->next = tree_stack_R;
			}
			if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
			{
				tree_generate* tree_stack_L = new tree_generate;
				tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
				tree_stack_L->next = tree_stack_top->next;
				tree_stack_top->next = tree_stack_L;
			}

			//A步:打印输出栈+本次循环中访问的元素
			tree_output* output_temp = output_stack_tail;
			while (output_temp != nullptr)
			{
				if (output_temp->symbol == 1)
					cout << "├─";
				if (output_temp->symbol == 2)
					cout << "└─";
				if (output_temp->symbol == 3)
					cout << "│ ";
				if (output_temp->symbol == 4)
					cout << "  ";
				output_temp = output_temp->prior;
			}
			cout << tree_stack_backup->treeptr->data << endl;

			//B步：退栈
			if (output_stack_top != nullptr && output_stack_top->symbol == 2)
				output_stack_top->symbol = 4;
			if (output_stack_top != nullptr && output_stack_top->symbol == 1)
				output_stack_top->symbol = 3;
			while ((output_stack_top != nullptr && output_stack_top->symbol == 4 &&
				(tree_stack_backup->treeptr->rtag == true || tree_stack_backup->treeptr->rchild == nullptr) &&
				(tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
				tree_m->tree == false) ||
				(output_stack_top != nullptr && output_stack_top->symbol == 4 &&
					(tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
					tree_m->tree == true))
			{
				//若输出栈非空，栈顶元素是空格，当前结点没有子结点，则连续出栈直到栈顶元素不是空格或者栈为空
				//如果树没有子结点，则树的左子树为空
				if (output_stack_top == output_stack_tail)
				{
					delete output_stack_top;
					output_stack_top = nullptr;
					output_stack_tail = nullptr;
				}
				else
				{
					tree_output* output_delete = output_stack_top;
					output_stack_top = output_stack_top->next;
					delete output_delete;
				}
			}

			//C步：进栈
			if (((tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false) &&
				(tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false) &&
				tree_m->tree == false) ||
				((tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false) &&
					(tree_stack_backup->treeptr->lchild->rchild != nullptr &&
						tree_stack_backup->treeptr->lchild->rtag == false) &&
					tree_m->tree == true))
			{
				//当前结点有多于一个子树
				//如果树的一个结点有多于一个子树，则这个结点有左子树，且这个结点的左子树有右子树
				tree_output* output_new = new tree_output;
				output_new->symbol = 1;
				output_new->next = output_stack_top;
				if (output_stack_top != nullptr)
					output_stack_top->prior = output_new;
				else
					output_stack_tail = output_new;
				output_stack_top = output_new;
				output_stack_top->prior = nullptr;
			}
			if (((/**/((tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false) &&
				(tree_stack_backup->treeptr->rtag == true || tree_stack_backup->treeptr->rchild == nullptr)) ||
				((tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
					(tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false))/**/)
				&& tree_m->tree == false) ||
				((tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false) &&
					(tree_stack_backup->treeptr->lchild->rtag == true ||
						tree_stack_backup->treeptr->lchild->rchild == nullptr)
					&& tree_m->tree == true))
			{
				//只有一个子树
				//如果树的一个结点只有一个子树，则这个结点有左子树，且这个结点的左子树没有右子树
				tree_output* output_new = new tree_output;
				output_new->symbol = 2;
				output_new->next = output_stack_top;
				if (output_stack_top != nullptr)
					output_stack_top->prior = output_new;
				else
					output_stack_tail = output_new;
				output_stack_top = output_new;
				output_stack_top->prior = nullptr;
			}
			if (((tree_stack_backup->treeptr->rtag == true || tree_stack_backup->treeptr->rchild == nullptr) &&
				(tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
				tree_stack_backup->next != nullptr && tree_m->tree == false) ||
				((tree_stack_backup->treeptr->ltag == true || tree_stack_backup->treeptr->lchild == nullptr) &&
					tree_stack_backup->next != nullptr && tree_m->tree == true))
			{
				//当前结点没有子树，工作栈中要访问的下一个结点存在
				//如果树的一个结点没有子树，则这个结点没有左子树
				if (output_stack_top == output_stack_tail)
				{
					delete output_stack_top;
					output_stack_top = nullptr;
					output_stack_tail = nullptr;
				}
				else
				{
					tree_output* output_delete = output_stack_top;
					output_stack_top = output_stack_top->next;
					delete output_delete;
				}
				tree_output* output_new = new tree_output;
				bitree* visit_next = tree_stack_backup->next->treeptr;//工作栈中要访问的下一个结点
				//此处若不使用parent域，则只能遍历整棵树
				if ((visit_next->parent->rchild != nullptr && visit_next->parent->rtag == false &&
					visit_next->parent->lchild != nullptr && visit_next->parent->ltag == false &&
					visit_next->parent->lchild == visit_next &&
					tree_m->tree == false) ||
					(visit_next->rchild != nullptr && visit_next->rtag == false &&
						tree_m->tree == true))
					output_new->symbol = 1;//要访问的下一个节点有右兄弟
				else
					output_new->symbol = 2;
				output_new->next = output_stack_top;
				if (output_stack_top != nullptr)
					output_stack_top->prior = output_new;
				else
					output_stack_tail = output_new;
				output_stack_top = output_new;
				output_stack_top->prior = nullptr;
			}

			tree_stack_top = tree_stack_top->next;
			delete tree_stack_backup;
		}
	}
	else//不打印辅助线
	{
		struct tree_generate
		{
			bitree* treeptr;
			long long depth;
			struct tree_generate* next;
		};
		tree_generate* tree_stack_top = new tree_generate;
		tree_stack_top->treeptr = tree_m->root;
		tree_stack_top->depth = 0;
		tree_stack_top->next = nullptr;

		cout << "【提示】以凹入表形式打印二叉树如下所示（不使用辅助线）：" << endl;
		while (tree_stack_top != nullptr)
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			tree_stack_top = tree_stack_top->next;
			for (long long i = 1; i <= tree_stack_backup->depth; i++)
				cout << "  ";
			cout << tree_stack_backup->treeptr->data << endl;
			if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
			{
				tree_generate* tree_stack_R = new tree_generate;
				tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
				if (tree_m->tree == false)
					tree_stack_R->depth = tree_stack_backup->depth + 1;
				else
					tree_stack_R->depth = tree_stack_backup->depth;
				tree_stack_R->next = tree_stack_top;
				tree_stack_top = tree_stack_R;
			}
			if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
			{
				tree_generate* tree_stack_L = new tree_generate;
				tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
				tree_stack_L->depth = tree_stack_backup->depth + 1;
				tree_stack_L->next = tree_stack_top;
				tree_stack_top = tree_stack_L;
			}
			delete tree_stack_backup;
		}
	}
	cout << endl;
	return;
}

template<typename Type>
void TREE<Type>::Print_Inorder() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法打印二叉树\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法打印二叉树\033[0m" << endl;
		return;
	}
	if (tree_m->tree == true)
	{
		cout << "\033[1;31m【错误】本函数不支持打印树或森林\033[0m" << endl;
		return;
	}

	struct tree_generate
	{
		bitree* treeptr;
		long long depth;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = nullptr;
	bitree* temp = tree_m->root;
	long long current_depth = 0;
	tree_generate* output_stack_top = nullptr;

	while (temp != nullptr || tree_stack_top != nullptr)
	{
		if (temp != nullptr)
		{
			tree_generate* tree_stack_backup = new tree_generate;
			tree_stack_backup->treeptr = temp;
			tree_stack_backup->depth = current_depth;
			tree_stack_backup->next = tree_stack_top;
			tree_stack_top = tree_stack_backup;
			if (temp->ltag == true || temp->lchild == nullptr)//左子树为空
				temp = nullptr;
			else
			{
				temp = temp->lchild;
				current_depth = current_depth + 1;
			}
		}
		else
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			temp = tree_stack_backup->treeptr;
			current_depth = tree_stack_top->depth;
			tree_generate* output_new = new tree_generate;
			output_new->treeptr = temp;
			output_new->depth = tree_stack_backup->depth;
			output_new->next = output_stack_top;
			output_stack_top = output_new;
			tree_stack_top = tree_stack_top->next;
			if (temp->rtag == true || temp->rchild == nullptr)//右子树为空
				temp = nullptr;
			else
			{
				current_depth = current_depth + 1;
				temp = temp->rchild;
			}
			delete tree_stack_backup;
		}
	}

	cout << "【提示】按树状打印二叉树：" << endl;
	while (output_stack_top != nullptr)
	{
		for (long long i = 1; i <= output_stack_top->depth; i++)
			cout << "  ";
		cout << output_stack_top->treeptr->data << endl;
		tree_generate* output_delete = output_stack_top;
		output_stack_top = output_stack_top->next;
		delete output_delete;
	}
	return;
}

template<typename Type>
void TREE<Type>::Print_arithmetic() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法打印二叉树\033[0m" << endl;
		return;
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法打印二叉树\033[0m" << endl;
		return;
	}

	//算法基本原理：在中序序列两端加两个虚拟根结点，深度与根结点相同
	//设两个变量分别存储当前遍历到的结点深度，和上次遍历到的结点深度
	//开始条件：上个结点深度=1（虚拟根结点），当前结点深度=1（第一次循环，根结点入栈时深度=1）
	//当遍历到任何结点时：
	//   若当前结点深度=1，上个结点深度=1，不操作
	//   若当前结点深度<上一结点深度，打印（上一结点深度-当前结点深度-1）个右括号
	//              >               （当前结点深度-上一结点深度-1）个左括号
	//   若当前结点深度-1=上一结点深度，当前结点无左子树，且当前结点有右子树，则打印1个左括号
	//当前结点深度不可能=上一结点深度。虚拟根结点除外
	//先打印括号，再输出节点元素值
	//遍历结束，退出循环时，若当前结点（循环中访问到的最后一个结点）深度为1，不进行任何操作。否则打印（当前结点深度-2）个右括号
	struct tree_generate
	{
		bitree* treeptr;
		long long depth;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = nullptr;
	bitree* temp = tree_m->root;
	long long current_depth = 1;
	long long pre_depth = 1;

	cout << "【提示】按照算术表达式形式打印二叉树：" << endl;
	while (temp != nullptr || tree_stack_top != nullptr)
	{
		if (temp != nullptr)
		{
			tree_generate* tree_stack_backup = new tree_generate;
			tree_stack_backup->treeptr = temp;
			tree_stack_backup->depth = current_depth;
			tree_stack_backup->next = tree_stack_top;
			tree_stack_top = tree_stack_backup;
			if (temp->ltag == true || temp->lchild == nullptr)//左子树为空
				temp = nullptr;
			else
			{
				temp = temp->lchild;
				current_depth = current_depth + 1;
			}
		}
		else
		{
			tree_generate* tree_stack_backup = tree_stack_top;
			temp = tree_stack_backup->treeptr;
			current_depth = tree_stack_top->depth;
			if (current_depth != 1 || pre_depth != 1)
			{
				if (current_depth < pre_depth)
				{
					for (long long i = 1; i <= pre_depth - current_depth - 1; i++)
						cout << ")";
				}
				if (current_depth > pre_depth)
				{
					for (long long i = 1; i <= current_depth - pre_depth - 1; i++)
						cout << "(";
				}
				if (current_depth - 1 == pre_depth && (temp->ltag == true || temp->lchild == nullptr) &&
					(temp->rchild != nullptr && temp->rtag == false))
					cout << "(";
			}
			cout << temp->data;
			pre_depth = current_depth;
			tree_stack_top = tree_stack_top->next;
			if (temp->rtag == true || temp->rchild == nullptr)//右子树为空
				temp = nullptr;
			else
			{
				current_depth = current_depth + 1;
				temp = temp->rchild;
			}
			delete tree_stack_backup;
		}
	}

	if (current_depth > 1)
	{
		for (long long i = 1; i <= current_depth - 2; i++)
			cout << ")";
	}
	cout << endl;
	return;
}

template<typename Type>
long long TREE<Type>::Degree() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法输出树的度\033[0m" << endl;
		return static_cast<long long>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法输出树的度\033[0m" << endl;
		return static_cast<long long>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	long long tree_degree_max = 0;//如果只有根结点，则度为0

	if (tree_m->tree == false)//是二叉树
	{
		tree_generate* tree_stack_top = new tree_generate;
		tree_stack_top->treeptr = tree_m->root;
		tree_stack_top->next = nullptr;
		while (tree_stack_top != nullptr)
		{
			long long tree_degree = 0;
			tree_generate* tree_stack_backup = tree_stack_top;
			tree_stack_top = tree_stack_top->next;
			if (tree_stack_backup->treeptr->rchild != nullptr && tree_stack_backup->treeptr->rtag == false)//右子树先入栈
			{
				tree_degree = tree_degree + 1;
				tree_generate* tree_stack_R = new tree_generate;
				tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
				tree_stack_R->next = tree_stack_top;
				tree_stack_top = tree_stack_R;
			}
			if (tree_stack_backup->treeptr->lchild != nullptr && tree_stack_backup->treeptr->ltag == false)//左子树后入栈
			{
				tree_degree = tree_degree + 1;
				tree_generate* tree_stack_L = new tree_generate;
				tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
				tree_stack_L->next = tree_stack_top;
				tree_stack_top = tree_stack_L;
			}
			if (tree_degree > tree_degree_max)
				tree_degree_max = tree_degree;
			if (tree_degree_max == 2)
			{
				//二叉树的度最大为2，如果度已经是2，则清空栈并退出
				while (tree_stack_top != nullptr)
				{
					tree_generate* tree_stack_delete = tree_stack_top;
					tree_stack_top = tree_stack_top->next;
					delete tree_stack_delete;
				}
				continue;
			}
			delete tree_stack_backup;
		}
	}
	else//不是二叉树
	{
		tree_generate* tree_queue_head = new tree_generate;
		tree_queue_head->treeptr = tree_m->root;
		tree_queue_head->next = nullptr;
		tree_generate* tree_queue_tail = tree_queue_head;

		if (tree_m->root->rchild != nullptr && tree_m->root->rtag == false)//根结点存在右子树
		{
			bitree* temp = tree_m->root->rchild;
			do
			{
				tree_generate* tree_queue_L = new tree_generate;
				tree_queue_L->treeptr = temp;
				tree_queue_L->next = nullptr;
				if (tree_queue_tail != nullptr)
				{
					tree_queue_tail->next = tree_queue_L;
					tree_queue_tail = tree_queue_tail->next;
				}
				else
				{
					tree_queue_tail = tree_queue_L;
					tree_queue_head = tree_queue_L;
				}
				if (temp->rchild != nullptr && temp->rtag == false)//temp有右子树
					temp = temp->rchild;
				else
					temp = nullptr;
			} while (temp != nullptr);
		}
		while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
		{
			tree_generate* tree_queue_backup = tree_queue_head;
			if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树进入队列
			{
				bitree* temp = tree_queue_backup->treeptr->lchild;
				long long tree_degree = 0;
				do
				{
					tree_degree = tree_degree + 1;
					tree_generate* tree_queue_L = new tree_generate;
					tree_queue_L->treeptr = temp;
					tree_queue_L->next = nullptr;
					if (tree_queue_tail != nullptr)
					{
						tree_queue_tail->next = tree_queue_L;
						tree_queue_tail = tree_queue_tail->next;
					}
					else
					{
						tree_queue_tail = tree_queue_L;
						tree_queue_head = tree_queue_L;
					}
					if (temp->rchild != nullptr && temp->rtag == false)//temp有右子树
						temp = temp->rchild;
					else
						temp = nullptr;
				} while (temp != nullptr);
				if (tree_degree > tree_degree_max)
					tree_degree_max = tree_degree;
			}
			if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
			{
				delete tree_queue_head;
				tree_queue_head = nullptr;
				tree_queue_tail = nullptr;
			}
			else
			{
				tree_generate* tree_queue_temp = tree_queue_head;
				tree_queue_head = tree_queue_head->next;
				delete tree_queue_temp;
			}
		}
	}
	return tree_degree_max;
}

template<typename Type>
void TREE<Type>::Huffman_create()
{
	if (tree_m != nullptr)
	{
		cout << "\033[1;33m【警告】该对象已拥有一棵树。你应该通过默认构造函数调用本函数\033[0m" << endl;
		cout << "\033[1;33m【警告】如果你只是想创建赫夫曼树，请单独创建一个对象，通过默认构造函数调用本函数\033[0m" << endl;
		cout << "\033[1;33m【警告】如果你要继续创建赫夫曼树，本函数会将目前存在的树彻底销毁\033[0m" << endl;
		cout << "\033[1;33m【警告】如果你确认要销毁目前存在的树并创建赫夫曼树，请只输入一个小写英文字母y\033[0m" << endl;
		cout << "\033[1;33m【警告】如果要退出，请输入任何其它字符，或按enter键\033[0m" << endl;
		LIST<char> input(1);
		if (input.Listlength() != 1 || input.Getelement(1) != 'y')
		{
			cout << "\033[1;33m【警告】你已放弃创建赫夫曼树。本函数将退出\033[0m" << endl;
			return;
		}
		else
		{
			cout << "\033[1;33m【警告】你已确定要继续创建赫夫曼树。目前存在的树将被销毁\033[0m" << endl;
			this->~TREE();
		}
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* prior;
		struct tree_generate* next;
	};
	tree_m = new tree_manage;
	tree_m->root = nullptr;
	tree_m->tree = false;
	tree_m->thread = 0;
	tree_m->head = nullptr;
	tree_m->tail = nullptr;
	tree_m->Huffman = true;
	cout << "【提示】正在创建一棵赫夫曼树。请输入所有权值（允许小数）:" << endl;
	LIST<long double> input(1);
	if (input.Min() < 0)
	{
		cout << "\033[1;31m【错误】不能出现小于0的权值。无法创建赫夫曼树，函数将退出\033[0m" << endl;
		this->~TREE();
		return;
	}
	if (input.Listlength() == 0)
	{
		cout << "\033[1;33m【警告】输入流长度为0，已创建一棵空树。函数将退出\033[0m" << endl;
		return;
	}
	tree_generate* tree_stack_top = nullptr;
	struct LIST<long double>::node* scan = input.ptr1->first;
	for (long long i = 1; i <= input.Listlength(); i++)
	{
		tree_generate* tree_stack_new = new tree_generate;
		tree_stack_new->treeptr = new bitree;
		tree_stack_new->treeptr->lchild = nullptr;
		tree_stack_new->treeptr->ltag = false;
		tree_stack_new->treeptr->weight = scan->element;
		tree_stack_new->treeptr->data = static_cast<Type>(0);
		tree_stack_new->treeptr->parent = nullptr;
		tree_stack_new->treeptr->rtag = false;
		tree_stack_new->treeptr->rchild = nullptr;
		tree_stack_new->next = tree_stack_top;
		if (tree_stack_top != nullptr)
			tree_stack_top->prior = tree_stack_new;
		tree_stack_new->prior = nullptr;
		tree_stack_top = tree_stack_new;
		scan = scan->next;
	}
	if (tree_stack_top == nullptr)
		return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
	if (input.Listlength() == 1)
	{
		tree_m->root = tree_stack_top->treeptr;
		delete tree_stack_top;
		return;
	}

	if (tree_stack_top == nullptr)
		return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
	while (tree_stack_top->next != nullptr)
	{
		tree_generate* min = tree_stack_top;
		tree_generate* sub_min = tree_stack_top;
		tree_generate* tree_scan = tree_stack_top->next;
		if (tree_scan->treeptr->weight < tree_stack_top->treeptr->weight)
			min = tree_scan;
		else
			sub_min = tree_scan;
		tree_scan = tree_scan->next;
		while (tree_scan != nullptr)
		{
			if (tree_scan->treeptr->weight < min->treeptr->weight)
			{
				sub_min = min;
				min = tree_scan;
			}
			if ((tree_scan->treeptr->weight > min->treeptr->weight) &&
				(tree_scan->treeptr->weight < sub_min->treeptr->weight))
				sub_min = tree_scan;
			tree_scan = tree_scan->next;
		}
		bitree* root_create = new bitree;
		root_create->lchild = min->treeptr;
		root_create->ltag = false;
		root_create->weight = min->treeptr->weight + sub_min->treeptr->weight;
		root_create->data = static_cast<Type>(0);
		root_create->parent = nullptr;
		root_create->rtag = false;
		root_create->rchild = sub_min->treeptr;
		sub_min->treeptr->parent = root_create;
		min->treeptr->parent = root_create;
		sub_min->treeptr = root_create;
		//循环到此处时，栈中至少有两个元素
		if (min->prior == nullptr)//min是栈顶元素
		{
			min->next->prior = nullptr;
			tree_stack_top = tree_stack_top->next;
		}
		if (min->next == nullptr)//min是栈底元素
			min->prior->next = nullptr;
		if (min->prior != nullptr && min->next != nullptr)
		{
			min->prior->next = min->next;
			min->next->prior = min->prior;
		}
		delete min;
	}
	tree_m->root = tree_stack_top->treeptr;
	delete tree_stack_top;
	return;
}

template<typename Type>
long double TREE<Type>::W_P_L() const
{
	if (tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】树不存在，无法计算树的带权路径长度\033[0m" << endl;
		return static_cast<long double>(0);
	}
	if (tree_m->Huffman == false)
	{
		cout << "\033[1;31m【错误】这不是赫夫曼树，无法计算树的带权路径长度\033[0m" << endl;
		return static_cast<long double>(0);
	}
	if (tree_m->root == nullptr)
	{
		cout << "\033[1;31m【错误】树为空，无法计算树的带权路径长度\033[0m" << endl;
		return static_cast<long double>(0);
	}

	struct tree_generate
	{
		bitree* treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->treeptr = tree_m->root;
	tree_queue_head->next = nullptr;
	tree_generate* tree_queue_tail = tree_queue_head;
	long long depth = 1;//二叉树的深度
	bitree* rear = tree_queue_tail->treeptr;//指向当前层次的最后一个结点
	long double wpl_sum = 0;

	while (tree_queue_head != nullptr && tree_queue_tail != nullptr)
	{
		tree_generate* tree_queue_backup = tree_queue_head;
		if ((tree_queue_backup->treeptr->ltag == true || tree_queue_backup->treeptr->lchild == nullptr) &&
			(tree_queue_backup->treeptr->rtag == true || tree_queue_backup->treeptr->rchild == nullptr))
			wpl_sum = wpl_sum + tree_queue_backup->treeptr->weight * (depth - 1);
		if (tree_queue_backup->treeptr->lchild != nullptr && tree_queue_backup->treeptr->ltag == false)//左子树先进入队列
		{
			tree_generate* tree_queue_L = new tree_generate;
			tree_queue_L->treeptr = tree_queue_backup->treeptr->lchild;
			tree_queue_L->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_L;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_L;
				tree_queue_head = tree_queue_L;
			}
		}
		if (tree_queue_backup == nullptr)
			return static_cast<long long>(0);//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		if (tree_queue_backup->treeptr->rchild != nullptr && tree_queue_backup->treeptr->rtag == false)//右子树后进入队列
		{
			tree_generate* tree_queue_R = new tree_generate;
			tree_queue_R->treeptr = tree_queue_backup->treeptr->rchild;
			tree_queue_R->next = nullptr;
			if (tree_queue_tail != nullptr)
			{
				tree_queue_tail->next = tree_queue_R;
				tree_queue_tail = tree_queue_tail->next;
			}
			else
			{
				tree_queue_tail = tree_queue_R;
				tree_queue_head = tree_queue_R;
			}
		}
		if (tree_queue_head == tree_queue_tail)//队列中只有一个元素
		{
			delete tree_queue_head;
			tree_queue_head = nullptr;
			tree_queue_tail = nullptr;
		}
		else
		{
			if (tree_queue_head->treeptr == rear)
			{
				rear = tree_queue_tail->treeptr;
				depth = depth + 1;
			}
			tree_generate* tree_queue_temp = tree_queue_head;
			tree_queue_head = tree_queue_head->next;
			delete tree_queue_temp;
		}
	}
	return wpl_sum;
}

template<typename Type>
bool Similar(const TREE<Type>& a, const TREE<Type>& b)
{
	if (&a == &b)
		return true;
	//认为a，b不相同
	if (a.tree_m == nullptr || b.tree_m == nullptr)
	{
		cout << "\033[1;31m【错误】至少有一棵树不存在，无法判断两棵树是否相似\033[0m" << endl;
		return false;
	}
	//认为a，b的tree_m结点都存在
	bool type_correct = true;
	if (a.tree_m->thread != 0 && a.tree_m->thread != 1 && a.tree_m->thread != 2 && a.tree_m->thread != 3)
		type_correct = false;
	if (b.tree_m->thread != 0 && b.tree_m->thread != 1 && b.tree_m->thread != 2 && b.tree_m->thread != 3)
		type_correct = false;//thread只能是0，1，2，3
	if (a.tree_m->thread == 0 && (a.tree_m->head != nullptr || a.tree_m->tail != nullptr))
		type_correct = false;
	if (b.tree_m->thread == 0 && (b.tree_m->head != nullptr || b.tree_m->tail != nullptr))
		type_correct = false;//若thread=0，则head，tail必须都为nullptr
	if (a.tree_m->thread != 0 && (a.tree_m->head == nullptr || a.tree_m->tail == nullptr))
		type_correct = false;
	if (b.tree_m->thread != 0 && (b.tree_m->head == nullptr || b.tree_m->tail == nullptr))
		type_correct = false;//若thread不等于0，则head，tail必须都不是nullptr
	if (a.tree_m->thread != 0 && b.tree_m->thread != 0 &&
		(a.tree_m->head == a.tree_m->tail || a.tree_m->head == b.tree_m->head || a.tree_m->head == b.tree_m->tail ||
			a.tree_m->tail == b.tree_m->head || a.tree_m->tail == b.tree_m->tail || b.tree_m->head == b.tree_m->tail))
		type_correct = false;//若ab的head，tail指针均存在，则两棵树的四个指针一定指向四个不同的地点
	if (type_correct == false)
	{
		cout << "\033[1;31m【错误】至少有一棵树的类型出错，无法判断两棵树是否相似\033[0m" << endl;
		return false;
	}
	//认为a，b的类型没有任何形式的错误
	if (a.tree_m->root != nullptr && b.tree_m->root == nullptr)
		return false;
	if (a.tree_m->root == nullptr && b.tree_m->root != nullptr)
		return false;
	if (a.tree_m->root == nullptr && b.tree_m->root == nullptr)
	{
		if (a.tree_m->tree != b.tree_m->tree)
			return false;
		if (a.tree_m->thread != 0 || b.tree_m->thread != 0)
			return false;
		if (a.tree_m->head != nullptr || a.tree_m->tail != nullptr)
			return false;
		if (b.tree_m->head != nullptr || b.tree_m->tail != nullptr)
			return false;
		if (a.tree_m->Huffman != b.tree_m->Huffman)
			return false;
		return true;
	}
	if (a.tree_m->root == b.tree_m->root)
	{
		cout << "\033[1;31m【错误】出现严重错误，两棵树的根节点指针指向同一个结点\033[0m" << endl;
		return false;
	}
	//认为a，b的tree_m结点都存在，a,b类型无错误，且root位都非空
	if (a.tree_m->tree != b.tree_m->tree)
		return false;
	if (a.tree_m->thread != b.tree_m->thread)
		return false;
	if (a.tree_m->Huffman != b.tree_m->Huffman)
		return false;
	//认为a，b的tree_m结点都存在，a,b类型无错误，root位都非空，且除了root，head，tail域都相同

	struct tree_generate
	{
		struct TREE<Type>::bitree* treeptrA;
		struct TREE<Type>::bitree* treeptrB;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptrA = a.tree_m->root;
	tree_stack_top->treeptrB = b.tree_m->root;
	tree_stack_top->next = nullptr;
	bool tree_similiar = true;

	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if ((tree_stack_backup->treeptrB->rchild != nullptr && tree_stack_backup->treeptrB->rtag == false) &&
			(tree_stack_backup->treeptrA->rtag == true || tree_stack_backup->treeptrA->rchild == nullptr))
			//B存在右子树 但是 A不存在右子树
			tree_similiar = false;
		if ((tree_stack_backup->treeptrA->rchild != nullptr && tree_stack_backup->treeptrA->rtag == false) &&
			(tree_stack_backup->treeptrB->rtag == true || tree_stack_backup->treeptrB->rchild == nullptr))
			//B不存在右子树 但是 A存在右子树
			tree_similiar = false;
		if ((tree_stack_backup->treeptrB->lchild != nullptr && tree_stack_backup->treeptrB->ltag == false) &&
			(tree_stack_backup->treeptrA->ltag == true || tree_stack_backup->treeptrA->lchild == nullptr))
			//B存在左子树 但是 A不存在左子树
			tree_similiar = false;
		if ((tree_stack_backup->treeptrA->lchild != nullptr && tree_stack_backup->treeptrA->ltag == false) &&
			(tree_stack_backup->treeptrB->ltag == true || tree_stack_backup->treeptrB->lchild == nullptr))
			//B不存在左子树 但是 A存在左子树
			tree_similiar = false;
		//B的左子树与A的左子树要么都存在要么都不存在；B的右子树与A的右子树要么都存在要么都不存在
		if (a.tree_m->head == tree_stack_backup->treeptrA && b.tree_m->head != tree_stack_backup->treeptrB)
			tree_similiar = false;
		if (a.tree_m->head != tree_stack_backup->treeptrA && b.tree_m->head == tree_stack_backup->treeptrB)
			tree_similiar = false;
		if (a.tree_m->tail == tree_stack_backup->treeptrA && b.tree_m->tail != tree_stack_backup->treeptrB)
			tree_similiar = false;
		if (a.tree_m->tail != tree_stack_backup->treeptrA && b.tree_m->tail == tree_stack_backup->treeptrB)
			tree_similiar = false;
		//若head域或tail域存在，则一定一一对应
		if (tree_similiar == false)
		{
			while (tree_stack_top != nullptr)//清空栈，退出循环
			{
				tree_generate* tree_stack_delete = tree_stack_top;
				tree_stack_top = tree_stack_top->next;
				delete tree_stack_delete;
			}
			continue;
		}
		if (tree_stack_backup->treeptrB->rchild != nullptr && tree_stack_backup->treeptrB->rtag == false)//右子树先入栈
		{
			//B存在右子树，则由上面的逻辑判断，A一定也存在右子树
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptrA = tree_stack_backup->treeptrA->rchild;
			tree_stack_R->treeptrB = tree_stack_backup->treeptrB->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptrB->lchild != nullptr && tree_stack_backup->treeptrB->ltag == false)//左子树后入栈
		{
			//B存在左子树，则由上面的逻辑判断，A一定也存在左子树
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptrA = tree_stack_backup->treeptrA->lchild;
			tree_stack_L->treeptrB = tree_stack_backup->treeptrB->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup;
	}
	if (tree_similiar == true)
		return true;
	else
		return false;
}

#endif