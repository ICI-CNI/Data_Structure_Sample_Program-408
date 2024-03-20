#ifndef TABLE_H
#define TABLE_H
#include<iostream>	//提供输入，输出功能
#include<fstream>	//提供读取/写入文件的功能
#include<cstdlib>	//提供类型转换等函数
#include<typeinfo>	//能让对象知道自己的数据类型
#include<cmath>		//提供floor等函数，在希尔排序/快速排序中被使用（可能还在其他地方被使用）
#include<climits>	//提供数据类型的范围，在表填充函数中被使用
#include<random>	//生成随机数，在表填充函数中被使用
#include<chrono>	//计算某个函数运行所花费的时间

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::fstream;
using namespace std::chrono;

template<typename Type>
class LIST
{
private:
	template<typename Type>
	friend class TREE;//将树作为线性表的友元，基于线性表构建一棵树
	template<typename Type>
	friend class GRAPH;

	bool SILENCE = true;//控制析构函数，复制构造函数，重载赋值运算符的调试输出，默认不输出
	int type;//0为线性表，1为链表
	static const int TABLE_INIT = 150;
	static const int TABLE_DELTA = TABLE_INIT;

	//线性表
	struct linear
	{
		long long length;
		long long total;
		Type* elements;
	};
	linear* ptr0;

	//链表
	struct node
	{
		struct node* prior;
		Type element;
		struct node* next;
	};
	struct chain_manage
	{
		struct node* first;
		struct node* end;
		long long num_elements;
	};
	chain_manage* ptr1;

	//第十章：内部排序
	//inline关键字在函数定义里，不在这里
	void _D_i_sort_A(const long long a, const long long b);//直接插入排序(内联函数)
	void _D_i_sort_B(node* a, node* b); //(内联函数)
	void _B_i_sort_A(const long long a, const long long b);//折半插入排序(内联函数)
	void _B_i_sort_B(node* a, node* b); //(内联函数)
	void _H_sort_A(const long long a, const long long b);//堆排序(内联函数)
	void _H_sort_B(node* a, node* b);// (内联函数)
	long long _Q_sort_assist_median(const long long a, const long long b) const;//三者取中函数(内联函数)
	node* _Q_sort_assist_median(node* a, node* b, long long num) const; //(内联函数)
	long long _Q_sort_assist_DEPTH(long long a) const;//计算栈的最大深度(内联函数)

public:
	//基本功能
	explicit LIST();//默认构造函数
	explicit LIST(const int a);//默认构造函数
	explicit LIST(const char* a, const int b, const bool WHETHER_FILEPATH);//默认构造函数
	explicit LIST(const Type* a, const long long length, const int b);//默认构造函数
	~LIST();//默认析构函数
	LIST& operator=(const LIST& x);//重载赋值运算符
	LIST(const LIST& x);//复制构造函数

	//第二章：线性表
	void Silence_T();//开启调试输出
	void Silence_F();//关闭调试输出
	void Listinit(const int a);//表的构造函数
	void Listinit(const char* a, const int b, const bool WHETHER_FILEPATH);//表的构造函数
	void Listinit(const Type* a, const long long length, const int b);//表的构造函数
	Type DATA_TYPE_CONVERT(const char* x) const;//将char*数组中存储的数据(char或类char数据除外)强制转换为Type类型
	LIST<int> CAST_INT(const long long start, const long long end) const;//将表的每个元素强制转换为int类型
	void Clearlist();//清空表
	void Clear_resize(const long long a);//清空表，并将表的总大小强制设置为a
	Type Getelement(const long long a) const;//返回特定序号元素的值
	void Listappend(const Type b);//向线性表的后面附加一个元素
	void Listappend(const LIST& b);//向线性表的后面附加一个线性表
	bool Listempty() const;//判断表是否为空
	long long Listlength() const;//返回表的长度
	void ListinsertF(const long long a, const Type b);//向指定位置的前面插入一个元素
	void ListinsertF(const long long a, const LIST& b);//向指定位置的前面插入一个表
	void ListinsertR(const long long a, const Type b);//向指定位置的后面插入一个元素
	void ListinsertR(const long long a, const LIST& b);//向指定位置的后面插入一个表
	void Listexpand(const long long a);//指定未来要插入的元素总量，根据总量强行扩大线性表的total域
	void Smart_expand();//线性表智能扩容函数
	void Listshrink();//缩紧线性表，用于线性表扩容函数的total域设置过大等情况
	void Smart_shrink(const bool clear);//线性表智能缩紧函数
	Type Listdelete(const long long a);//删除指定元素
	void Listdelete(const long long a, const long long b);//删除多个指定元素
	long long Listsize() const;//返回表的大小(total域)
	long long Listcapacity() const;//在不扩充线性表的前提下，线性表的剩余容量(total域-length域)
	void Listresize(const long long a, const Type b);//把表的总大小强制设置为a，多去少补(使用b填充)
	void Listfill(const long long a, const long long b, const Type x);//使用某种模式将表填充到某个大小
	void Update(const long long a, const Type b);//更新特定元素的值
	void Display() const;//输出表的所有元素
	void Output_to_file(const char* PATH, const bool clear) const;//把表的全部元素输出到一个文件中
	void Exchange(const long long a, const long long b);//交换表的两个元素的值
	void Info() const;//输出表的全部信息
	void Typeswitch(const int target);//将表的类型在线性表和链表之间相互转换
	void Repair(const int a);//将类型错误的表转换成类型正确的空表
	int Gettype() const;//返回表的类型
	void Reverse(const long long a, const long long b);//将线性表的一部分颠倒
	Type Max() const;//返回表中元素的最大值
	Type Min() const;//返回表中元素的最小值
	long double Sum() const;//返回表中所有元素的和

	//第三章：栈和队列
	Type Stack_gettop() const;//模仿栈的操作，显示栈顶元素（栈顶元素指表的第一个元素）
	void Stack_push(const Type& a);//模仿栈的操作，将一个元素入栈
	Type Stack_pop();//模仿栈的操作，将一个元素出栈
	Type Queue_gethead() const;//模仿队列的操作，返回队头元素（表的第一个元素）
	Type Queue_gettail() const;//模仿队列的操作，返回队尾元素（表的最后一个元素）
	void Queue_enqueue(const Type& a);//模仿队列的操作，向队尾插入新元素
	Type Queue_dequeue();//模仿队列的操作，删除队头元素

	//第四章：串
	bool Repeat_TF() const;//判断串是否有重复元素
	bool Symmetric_TF() const;//判断串是否对称
	void Clear_copy(const LIST& b);//将原始串清空，并把串b复制到原始串
	void Overwrite(const long long a, const LIST& b);//使用串b覆写掉从原始串的第a位开始的内容
	LIST Substring(const long long a, const long long length) const;//提取子字符串
	bool Compare(const LIST& b) const;//比较两个字符串是否相同
	long long Char_erase(const Type& a);//在字符串中删去特定字符
	long long Char_num(const Type& a) const;//返回字符串中特定字符的总数
	Type* Type_array(const bool help) const;//以数组的形式输出串中的全部内容
	Type* Type_array(const long long a, const long long b, const bool help) const;//以数组的形式输出串中的全部内容
	char* Char_array(const bool help) const;//以char数组的形式输出串中的全部内容
	char* Char_array(const long long a, const long long b, const bool help) const;//以char数组的形式输出串中的全部内容
	long long K_M_P(const LIST& a, const long long start, const long long end) const;//串的模式匹配函数(KMP算法)
	template<typename Type> friend void String_swap(LIST<Type>& a, LIST<Type>& b);//交换两个字符串的内容
	template<typename Type> friend void String_sort(LIST<Type>** a, const long long b);//字符串排序函数
	//LIST<Type>** a前面不可以加const，不然会出错
	template<typename Type> friend bool Same_TF(const LIST<Type>& a, const long long a_start, const long long a_end,
		const LIST<Type>& b, const long long b_start, const long long b_end);//判断两个字符串的一部分是否相同

	//第九章：查找
	long long Seq_search(const Type a);//顺序查找
	LIST<long long> Seq_search_all(const Type a) const;//顺序查找，并输出所有值与待查找的值相同的元素的序号
	long long Bin_search(const Type a);//折半查找
	long long Fibo_search(const Type a);//斐波那契查找
	long long Interp_search(const Type a);//插值查找
	long long STT_search(const Type a, const LIST<long double>& WEIGHT) const;//静态树表查找
	long long AVL_search(const Type a) const;//平衡二叉树查找
	long long B_TREE_search(const Type a, const long long m) const;//B树查找
	long long RB_TREE_search(const Type a) const;//红黑树查找

	//第十章：内部排序
	bool Sort_TF() const;//判断序列是否有序
	void D_i_sort(const int seq);//直接插入排序
	void B_i_sort(const int seq);//折半插入排序
	void Two_i_sort(const int seq);//2路插入排序
	void T_i_sort(const int seq);//表插入排序
	void S_sort(const int seq);//希尔排序
	void B_sort(const int seq);//起泡排序
	void Q_sort(const int seq);//快速排序（内省排序）
	void S_s_sort(const int seq);//简单选择排序
	void T_s_sort(const int seq);//树形选择排序
	void H_sort(const int seq);//堆排序
	void M_sort(const int seq);//归并排序
	void R_sort(const int seq);//基数排序
	void Sort(const int seq);//最好的排序函数 
	void Disarrange();//将序列随机重排

	//运算符重载
	Type operator[](const long long a) const;//重载[]运算符
	void operator+=(const LIST& a);//重载+=运算符
	void operator+=(const Type a);//重载+=运算符
	template<typename Type> friend ostream& operator<<(ostream& os, const LIST<Type>& a);//重载<<运算符
	template<typename Type> friend fstream& operator<<(fstream& fs, const LIST<Type>& a);//重载<<运算符
	template<typename Type> friend istream& operator>>(istream& is, LIST<Type>& a);//重载>>运算符
	template<typename Type> friend fstream& operator>>(fstream& fs, LIST<Type>& a);//重载>>运算符
	template<typename Type> friend bool operator==(const LIST<Type>& a, const LIST<Type>& b);//重载==运算符
	template<typename Type> friend bool operator!=(const LIST<Type>& a, const LIST<Type>& b);//重载!=运算符
	template<typename Type> friend const LIST<Type> operator+(const LIST<Type>& a, const LIST<Type>& b);//重载+运算符
	template<typename Type> friend const LIST<Type> operator+(const LIST<Type>& a, const Type b);//重载+运算符
	//上面两个函数的返回类型必须是const LIST<Type>而非LIST<Type>。否则类似(1+1=2)的无意义语句将成为合法语句
	//上面两个函数的返回类型必须是const LIST<Type>而非const LIST&<Type>，否则将返回不存在的临时对象。此处对复制构造函数的调用不可避免
	//注意：友元函数不可以在()的最后加上const（不对类进行修改）
};

template<typename Type>
LIST<Type>::LIST()
{
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
LIST<Type>::LIST(const int a)
{
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;

	Listinit(a);
	return;
}

template<typename Type>
LIST<Type>::LIST(const char* a, const int b, const bool WHETHER_FILEPATH)
{
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;

	Listinit(a, b, WHETHER_FILEPATH);
	return;
}

template<typename Type>
LIST<Type>::LIST(const Type* a, const long long length, const int b)
{
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;

	Listinit(a, length, b);
	return;
}

template<typename Type>
LIST<Type>::~LIST()
{
	//delete ptr0后，必须手动将指针置为空指针，否则指针会指向之前的地址。释放ptr0后，ptr0的length等三个域
	//仍然存在，并且可以用ptr0->length访问。但是ptr0的三个域会全部变成未初始化的随机数据，尝试读取ptr0->length
	//会使程序崩溃（通常发生于析构函数被意外调用的情况）。ptr1指针同理，其他类的析构函数同理。使用delete后必须将指针手动置为空指针
	if (SILENCE == false)
		cout << "【提示】LIST类的析构函数被调用" << endl;
	if (type == 0)
	{
		delete[] ptr0->elements;
		delete ptr0;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		return;
	}
	if (type == 1)
	{
		if (ptr1 == nullptr)
			return;
		chain_manage* x = ptr1;
		node* x_first = x->first;
		node* x_end = x->end;
		node* temp = x_first;
		while (temp != x_end)
		{
			node* temp1 = temp->next;
			delete temp;
			temp = temp1;
		}
		delete temp;
		delete x;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		return;
	}
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
LIST<Type>& LIST<Type>::operator=(const LIST& x)
{
	if ((x.type == 0 && x.ptr0 == nullptr) || (x.type == 1 && x.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return *this;
	}
	if (SILENCE == false)
		cout << "【提示】LIST类的重载的赋值运算符被调用" << endl;
	if (x.type != 0 && x.type != 1)
	{
		cout << "\033[1;33m【警告】等号右边的表出现类型错误，无法执行赋值操作。重载的赋值运算符函数正在退出\033[0m" << endl;
		return *this;
	}
	if (type != 0 && type != 1)
		cout << "\033[1;33m【警告】等号左边的表出现类型错误，但是等号右边的表类型正常。等号左边的表将被覆盖\033[0m" << endl;
	if (this == &x)
		return *this;
	if (type != x.type)
	{
		if (type == 0)
			cout << "\033[1;33m【警告】等号左边的表是线性表，但是等号右边的表是链表。等号左边的表将被转换成链表\033[0m" << endl;
		if (type == 1)
			cout << "\033[1;33m【警告】等号左边的表是链表，但是等号右边的表是线性表。等号左边的表将被转换成线性表\033[0m" << endl;
	}
	this->~LIST();

	if (x.type == 0)
	{
		type = 0;
		linear* temp = new linear;
		temp->total = x.ptr0->total;
		temp->length = x.ptr0->length;
		Type* T = new Type[x.ptr0->total]();
		memmove_s(T, sizeof(Type) * (x.ptr0->total + 10), x.ptr0->elements, sizeof(Type) * x.ptr0->total);
		temp->elements = T;

		ptr0 = temp;
		ptr1 = nullptr;
	}
	if (x.type == 1)
	{
		type = 1;
		chain_manage* temp_m = new chain_manage;
		temp_m->num_elements = x.ptr1->num_elements;
		node* start = x.ptr1->first;
		node* temp_n = new node;
		temp_n->element = start->element;
		temp_n->next = nullptr;
		temp_n->prior = nullptr;
		temp_m->first = temp_n;
		start = start->next;
		while (start != nullptr)
		{
			node* temp_o = new node;
			temp_o->element = start->element;
			temp_o->next = nullptr;
			temp_o->prior = temp_n;
			temp_n->next = temp_o;
			temp_n = temp_o;
			start = start->next;
		}
		temp_m->end = temp_n;

		ptr0 = nullptr;
		ptr1 = temp_m;
	}
	return *this;
}

template<typename Type>
LIST<Type>::LIST(const LIST& x)
{
	if ((x.type == 0 && x.ptr0 == nullptr) || (x.type == 1 && x.ptr1 == nullptr))
	{
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (SILENCE == false)
		cout << "【提示】LIST类的复制构造函数被调用" << endl;
	if (x.type == 0)
	{
		type = 0;
		linear* temp = new linear;
		temp->total = x.ptr0->total;
		temp->length = x.ptr0->length;
		Type* T = new Type[x.ptr0->total]();
		memmove_s(T, sizeof(Type) * (x.ptr0->total + 10), x.ptr0->elements, sizeof(Type) * x.ptr0->total);
		temp->elements = T;

		ptr0 = temp;
		ptr1 = nullptr;
		return;
	}
	if (x.type == 1)
	{
		type = 1;
		chain_manage* temp_m = new chain_manage;
		temp_m->num_elements = x.ptr1->num_elements;
		node* start = x.ptr1->first;
		node* temp_n = new node;
		temp_n->element = start->element;
		temp_n->next = nullptr;
		temp_n->prior = nullptr;
		temp_m->first = temp_n;
		start = start->next;
		while (start != nullptr)
		{
			node* temp_o = new node;
			temp_o->element = start->element;
			temp_o->next = nullptr;
			temp_o->prior = temp_n;
			temp_n->next = temp_o;
			temp_n = temp_o;
			start = start->next;
		}
		temp_m->end = temp_n;

		ptr0 = nullptr;
		ptr1 = temp_m;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Silence_T()
{
	SILENCE = true;
	return;
}

template<typename Type>
void LIST<Type>::Silence_F()
{
	SILENCE = false;
	return;
}

template<typename Type>
void LIST<Type>::Listinit(const int a)
{
	if (type == 0 || type == 1)
		cout << "\033[1;33m【警告】原始表将被清空！\033[0m" << endl;
	if (type != -1)
		this->~LIST();
	//a=2时，创建一个没有任何参数的空表，用于2路插入排序等特殊用途
	//使用a=2的参数创建对象后需要使用Repair函数将表转换成正确类型

	//使用白名单来确定输入的类型在不在本程序支持的范围内
	//请注意：对象一旦被创建，其类型(Type)无法更改 ！
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
		cout << "\033[1;31m【错误】程序目前不支持创建此类型的表\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}
	if (a == 2)
		return;//注意：type域的值不会被设置为2！！！！！
	if (a == 3)
	{
		Repair(0);
		return;
	}
	if (a == 4)
	{
		Repair(1);
		return;
	}
	if (a != 0 && a != 1)//0为线性表，1为链表
	{
		cout << "\033[1;31m【错误】输入的表的类型有错误\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}

	//运行到这里时，type = -1，ptr0 = nullptr，ptr1 = nullptr;
	if (a == 0)
		Repair(0);
	if (a == 1)
		Repair(1);
	if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
		cout << "【提示】请输入" << typeid(Type).name() << "类型的数据：" << endl;
	else
		cout << "【提示】请输入" << typeid(Type).name() << "类型的数据，使用空格分开相邻的两个数字：" << endl;

	LIST<char> INPUT_STREAM(3);
	bool start_find = false;
	bool end_find = false;
	bool str_finish = false;
	char STREAM_TEMP_A = '\0';
	char STREAM_TEMP_B = '\0';
	cin.get(STREAM_TEMP_A);
	while ((int)STREAM_TEMP_A != 10)
	{
		cin.get(STREAM_TEMP_B);
		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据直接插入
		{
			ListinsertR(Listlength(), static_cast<Type>(STREAM_TEMP_A));
			Smart_expand();
			STREAM_TEMP_A = STREAM_TEMP_B;
			continue;
		}

		if (STREAM_TEMP_A != ' ' && STREAM_TEMP_A != '	')//发现字符串头
		{
			INPUT_STREAM += STREAM_TEMP_A;
			INPUT_STREAM.Smart_expand();
			start_find = true;
		}
		if (start_find == true && (STREAM_TEMP_A == ' ' || STREAM_TEMP_A == '	'))//发现字符串尾
		{
			end_find = true;
		}
		if ((int)STREAM_TEMP_B == 10)//输入流扫描完毕
		{
			end_find = true;
		}
		if (start_find == true && end_find == true)//凑齐了字符串头和字符串尾
		{
			start_find = false;
			end_find = false;
			str_finish = true;
		}
		if (str_finish == true)//凑齐了字符串头和字符串尾
		{
			char* converted_char = INPUT_STREAM.Char_array(false);
			Type converted = DATA_TYPE_CONVERT(converted_char);
			delete[] converted_char;
			ListinsertR(Listlength(), converted);
			Smart_expand();

			str_finish = false;
			INPUT_STREAM.Smart_shrink(true);
		}
		STREAM_TEMP_A = STREAM_TEMP_B;
	}
	if (type == 0)
		Listshrink();
	return;
}

template<typename Type>
void LIST<Type>::Listinit(const char* a, const int b, const bool WHETHER_FILEPATH)
{
	if (type == 0 || type == 1)
		cout << "\033[1;33m【警告】原始表将被清空！\033[0m" << endl;
	if (type != -1)
		this->~LIST();
	//b=2时，创建一个没有任何参数的空表，用于2路插入排序等特殊用途
	//使用b=2的参数创建对象后需要使用Repair函数将表转换成正确类型

	//使用白名单来确定输入的类型在不在本程序支持的范围内
	//请注意：对象一旦被创建，其类型(Type)无法更改 ！
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
		cout << "\033[1;31m【错误】程序目前不支持创建此类型的表\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}
	if (b == 2)
		return;//注意：type域的值不会被设置为2！！！！！
	if (b == 3)
	{
		Repair(0);
		return;
	}
	if (b == 4)
	{
		Repair(1);
		return;
	}
	if (b != 0 && b != 1)//0为线性表，1为链表
	{
		cout << "\033[1;31m【错误】输入的表的类型有错误\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}

	//运行到这里时，type = -1，ptr0 = nullptr，ptr1 = nullptr;
	if (b == 0)
		Repair(0);
	if (b == 1)
		Repair(1);
	fstream file_input;
	if (WHETHER_FILEPATH == true)
	{
		file_input.open(a, std::ios::in | std::ios::out);//文件路径必须使用双\\作为分隔符
		if (!file_input)
		{
			cout << "\033[1;31m【错误】文件路径下的文件无法打开，无法执行任何操作\033[0m" << endl;
			return;
		}
	}
	if (WHETHER_FILEPATH == false)//a不是文件路径
	{
		LIST<char> INPUT_STREAM(3);
		bool start_find = false;
		bool end_find = false;
		bool str_finish = false;
		long long STREAM_COUNT = 0;
		char STREAM_TEMP_A = a[STREAM_COUNT];
		while (STREAM_TEMP_A != '\0')
		{
			STREAM_COUNT = STREAM_COUNT + 1;
			char STREAM_TEMP_B = a[STREAM_COUNT];
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据直接插入
			{
				ListinsertR(Listlength(), static_cast<Type>(STREAM_TEMP_A));
				Smart_expand();
				STREAM_TEMP_A = STREAM_TEMP_B;
				continue;
			}
			if (STREAM_TEMP_A != ' ' && STREAM_TEMP_A != '	')//发现字符串头
			{
				INPUT_STREAM += STREAM_TEMP_A;
				INPUT_STREAM.Smart_expand();
				start_find = true;
			}
			if (start_find == true && (STREAM_TEMP_A == ' ' || STREAM_TEMP_A == '	'))//发现字符串尾
			{
				end_find = true;
			}
			if (STREAM_TEMP_B == '\0')//输入流扫描完毕
			{
				end_find = true;
			}
			if (start_find == true && end_find == true)//凑齐了字符串头和字符串尾
			{
				start_find = false;
				end_find = false;
				str_finish = true;
			}
			if (str_finish == true)//凑齐了字符串头和字符串尾
			{
				char* converted_char = INPUT_STREAM.Char_array(false);
				Type converted = DATA_TYPE_CONVERT(converted_char);
				delete[] converted_char;
				ListinsertR(Listlength(), converted);
				Smart_expand();

				str_finish = false;
				INPUT_STREAM.Smart_shrink(true);
			}
			STREAM_TEMP_A = STREAM_TEMP_B;
		}
	}
	else//a是文件路径
	{
		LIST<char> INPUT_STREAM(3);
		bool start_find = false;
		bool end_find = false;
		bool str_finish = false;
		char STREAM_TEMP_A = '\0';
		char STREAM_TEMP_B = '\0';
		file_input.get(STREAM_TEMP_A);
		while (!file_input.eof())
		{
			file_input.get(STREAM_TEMP_B);
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据直接插入
			{
				ListinsertR(Listlength(), static_cast<Type>(STREAM_TEMP_A));
				Smart_expand();
				STREAM_TEMP_A = STREAM_TEMP_B;
				continue;
			}
			if (STREAM_TEMP_A != ' ' && STREAM_TEMP_A != '	')//发现字符串头
			{
				INPUT_STREAM += STREAM_TEMP_A;
				INPUT_STREAM.Smart_expand();
				start_find = true;
			}
			if (start_find == true && (STREAM_TEMP_A == ' ' || STREAM_TEMP_A == '	'))//发现字符串尾
			{
				end_find = true;
			}
			if ((int)STREAM_TEMP_B == 10)//输入流扫描完毕
			{
				end_find = true;
			}
			if (start_find == true && end_find == true)//凑齐了字符串头和字符串尾
			{
				start_find = false;
				end_find = false;
				str_finish = true;
			}
			if (str_finish == true)//凑齐了字符串头和字符串尾
			{
				char* converted_char = INPUT_STREAM.Char_array(false);
				Type converted = DATA_TYPE_CONVERT(converted_char);
				delete[] converted_char;
				ListinsertR(Listlength(), converted);
				Smart_expand();

				str_finish = false;
				INPUT_STREAM.Smart_shrink(true);
			}
			STREAM_TEMP_A = STREAM_TEMP_B;
		}
		file_input.close();
	}
	if (type == 0)
		Listshrink();
	return;
}

template<typename Type>
void LIST<Type>::Listinit(const Type* a, const long long length, const int b)
{
	if (type == 0 || type == 1)
		cout << "\033[1;33m【警告】原始表将被清空！\033[0m" << endl;
	if (type != -1)
		this->~LIST();
	//b=2时，创建一个没有任何参数的空表，用于2路插入排序等特殊用途
	//使用b=2的参数创建对象后需要使用Repair函数将表转换成正确类型

	//使用白名单来确定输入的类型在不在本程序支持的范围内
	//请注意：对象一旦被创建，其类型(Type)无法更改 ！
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
		cout << "\033[1;31m【错误】程序目前不支持创建此类型的表\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}
	if (b == 2)
		return;//注意：type域的值不会被设置为2！！！！！
	if (b == 3)
	{
		Repair(0);
		return;
	}
	if (b == 4)
	{
		Repair(1);
		return;
	}
	if (b != 0 && b != 1)//0为线性表，1为链表
	{
		cout << "\033[1;31m【错误】输入的表的类型有错误\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		cout << "\033[1;31m【错误】无法正确创建表，析构函数将被调用\033[0m" << endl;
		this->~LIST();
		return;
	}

	//运行到这里时，type = -1，ptr0 = nullptr，ptr1 = nullptr;
	if (b == 0)
	{
		Repair(0);
		Listexpand(length);
	}
	if (b == 1)
		Repair(1);
	for (long long i = 1; i <= length; i++)
		ListinsertR(Listlength(), a[i - 1]);
	return;
}

template<typename Type>
Type LIST<Type>::DATA_TYPE_CONVERT(const char* x) const
{
	if (x == nullptr)
		return static_cast<Type>(0);

	//使用白名单来确定输入的类型在不在本函数支持的范围内
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
		return static_cast<Type>(0);

	//无法对char或类char数据进行转换
	if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据
		return static_cast<Type>(0);

	if (strcmp(typeid(Type).name(), typeid(__int64).name()) == 0)//  __int64，识别名__int64
	{
		__int64 x1 = _atoi64(x);//__int64转换函数
		return static_cast<Type>(x1);
	}
	if (strcmp(typeid(Type).name(), typeid(int).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__int32).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(short).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__int16).name()) == 0)//int或__int32或short或__int16
	{
		//int与__int32的识别名都是int
		//short与__int16的识别名都是short
		//(int或__int32)-->>强制转换-->>(short或__int16)
		int x2 = atoi(x);//int转换函数
		if (strcmp(typeid(Type).name(), typeid(short).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int16).name()) == 0)//short或__int16
		{
			short x3 = static_cast<short>(x2);
			return static_cast<Type>(x3);
		}
		if (strcmp(typeid(Type).name(), typeid(int).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(__int32).name()) == 0)//int或__int32
		{
			return static_cast<Type>(x2);
		}
	}
	if (strcmp(typeid(Type).name(), typeid(long).name()) == 0)//long,识别名long
	{
		long x4 = strtol(x, nullptr, 10);//long转换函数
		return static_cast<Type>(x4);
	}
	if (strcmp(typeid(Type).name(), typeid(unsigned long).name()) == 0)//unsigned long，识别名unsigned long
	{
		unsigned long x5 = strtoul(x, nullptr, 10);//unsigned long转换函数
		return static_cast<Type>(x5);
	}
	if (strcmp(typeid(Type).name(), typeid(long long).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(__int64).name()) == 0)
	{
		//long long与__int64的识别名都是__int64
		long long x6 = strtoll(x, nullptr, 10);//long long转换函数
		return static_cast<Type>(x6);
	}
	if (strcmp(typeid(Type).name(), typeid(unsigned long long).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(unsigned __int64).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(unsigned int).name()) == 0 ||
		strcmp(typeid(Type).name(), typeid(unsigned short).name()) == 0)
	{
		//unsigned long long和unsigned __int64的识别名都是unsigned __int64
		//unsigned int的识别名是unsigned int
		//unsigned short的识别名是unsigned short
		//(unsigned long long或unsigned __int64)-->>强制转换-->>unsigned int
		//(unsigned long long或unsigned __int64)-->>强制转换-->>unsigned short
		unsigned long long x7 = strtoull(x, nullptr, 10);//unsigned long long转换函数
		if (strcmp(typeid(Type).name(), typeid(unsigned int).name()) == 0)//unsigned int
		{
			unsigned int x8 = static_cast<unsigned int>(x7);
			return static_cast<Type>(x8);
		}
		if (strcmp(typeid(Type).name(), typeid(unsigned short).name()) == 0)//unsigned short
		{
			unsigned short x9 = static_cast<unsigned short>(x7);
			return static_cast<Type>(x9);
		}
		if (strcmp(typeid(Type).name(), typeid(unsigned long long).name()) == 0 ||
			strcmp(typeid(Type).name(), typeid(unsigned __int64).name()) == 0)
		{
			//unsigned long long或unsigned __int64
			return static_cast<Type>(x7);
		}
	}
	if (strcmp(typeid(Type).name(), typeid(float).name()) == 0)//float，识别名float
	{
		float x10 = strtof(x, nullptr);//float转换函数
		return static_cast<Type>(x10);
	}
	if (strcmp(typeid(Type).name(), typeid(double).name()) == 0)//double，识别名double
	{
		double x11 = strtod(x, nullptr);//double转换函数
		return static_cast<Type>(x11);
	}
	if (strcmp(typeid(Type).name(), typeid(long double).name()) == 0)//long double,识别名long double
	{
		long double x12 = strtold(x, nullptr);//long double转换函数
		return static_cast<Type>(x12);
	}
	if (strcmp(typeid(Type).name(), typeid(bool).name()) == 0)//bool的识别名是bool
	{
		int x13 = atoi(x);//int转换函数
		bool x_bool = false;
		if (x13 == 0)
			x_bool = false;
		else
			x_bool = true;
		return static_cast<Type>(x_bool);
	}

	return static_cast<Type>(0);
}

template<typename Type>
LIST<int> LIST<Type>::CAST_INT(const long long start, const long long end) const
{
	LIST<int> TEMP(2);
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if (start <= 0 || start > Listlength() || end <= 0 || end > Listlength() || start > end)
	{
		cout << "\033[1;31m【错误】输入的待转换的元素序号范围有错误，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}

	if (type == 0)
	{
		TEMP.Repair(type);
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return TEMP;
		}

		TEMP.Listexpand(end - start + 1);
		for (long long i = start; i <= end; i++)
			TEMP.ListinsertR(TEMP.Listlength(), static_cast<int>(ptr0->elements[i - 1]));
		return TEMP;
	}
	if (type == 1)
	{
		TEMP.Repair(type);
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return TEMP;
		}

		node* scan = ptr1->first;
		long long scan_count = 1;
		while (scan_count < start)
		{
			scan = scan->next;
			scan_count = scan_count + 1;
		}
		for (long long i = start; i <= end; i++)
		{
			TEMP.ListinsertR(TEMP.Listlength(), static_cast<int>(scan->element));
			scan = scan->next;
		}
		return TEMP;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return TEMP;
}

template<typename Type>
void LIST<Type>::Clearlist()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		this->~LIST();
		Repair(0);
		return;
	}
	if (type == 1)
	{
		this->~LIST();
		Repair(1);
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Clear_resize(const long long a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (a == Listlength())
		{
			ptr0->length = 0;
			return;
		}
		if (a < Listlength())
		{
			Listexpand(Listlength() - a);
			ptr0->length = 0;
			return;
		}
		if (a > Listlength())
		{
			ptr0->length = a;
			Listshrink();
			ptr0->length = 0;
			return;
		}
		return;
	}
	if (type == 1)
	{
		this->~LIST();
		Repair(1);
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
Type LIST<Type>::Getelement(const long long a) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)//0为线性表，1为链表
	{
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要输出的元素的序号错误\033[0m" << endl;
			return static_cast<Type>(0);
		}
		return ptr0->elements[a - 1];
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0 || a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要输出的元素的序号错误\033[0m" << endl;
			return static_cast<Type>(0);
		}
		node* temp = nullptr;
		if (a == Listlength())
			temp = ptr1->end;
		else
		{
			temp = ptr1->first;
			long long i = 1;
			while (i != a)
			{
				temp = temp->next;
				i = i + 1;
			}
		}
		return temp->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(0);
}

template<typename Type>
void LIST<Type>::Listappend(const Type b)
{
	*this += b;
	return;
}

template<typename Type>
void LIST<Type>::Listappend(const LIST& b)
{
	*this += b;
	return;
}

template<typename Type>
bool LIST<Type>::Listempty() const
{
	//表为空时返回true，非空时返回false
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return true;
	}

	if (type == 0 || type == 1)
	{
		if (Listlength() == 0)
			return true;
		else
			return false;
	}

	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return true;
}

template<typename Type>
long long LIST<Type>::Listlength() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)//0为线性表，1为链表
	{
		return ptr0->length;
	}
	if (type == 1)
	{
		return ptr1->num_elements;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return -1;
}

template<typename Type>
void LIST<Type>::ListinsertF(const long long a, const Type b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	//假如只有三个元素abc,则序号的范围是1-3,插入结果（只有三种）是Xabc,aXbc,abXc
	if (type == 0)
	{
		if (ptr0->length == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			ptr0->elements[0] = b;
			ptr0->length = ptr0->length + 1;
			return;
		}
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		if (ptr0->length + 1 > ptr0->total)
		{
			long long length = ptr0->length + 1;
			while (ptr0->total < length)
				ptr0->total = ptr0->total + TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}

		long long i = 0;
		for (i = static_cast<long long>(ptr0->length); i >= a; i--)
		{
			ptr0->elements[i] = ptr0->elements[i - 1];
		}
		ptr0->elements[a - 1] = b;
		ptr0->length = ptr0->length + 1;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//线性表为空
		{
			ptr1->num_elements = ptr1->num_elements + 1;
			ptr1->first->element = b;
			return;
		}
		if (a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		node* target = ptr1->first;
		long long i = 1;
		while (i != a)
		{
			target = target->next;
			i = i + 1;
		}
		ptr1->num_elements = ptr1->num_elements + 1;

		if (target->prior == nullptr)
		{
			node* temp = new node;
			temp->element = b;
			temp->next = target;
			temp->prior = nullptr;
			target->prior = temp;
			ptr1->first = temp;
			return;
		}
		node* temp = new node;
		temp->element = b;
		temp->next = target;
		temp->prior = target->prior;
		temp->prior->next = temp;
		target->prior = temp;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::ListinsertF(const long long a, const LIST& b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】作为被插入对象的表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】作为插入对象的表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type != b.type)
	{
		cout << "\033[1;31m【错误】插入对象和被插入对象的类型不同，无法执行任何操作\033[0m" << endl;
		return;
	}
	//假如只有三个元素abc,则序号的范围是1-3,插入结果（只有三种）是Xabc,aXbc,abXc

	if (type == 0)
	{
		if (ptr0->length == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			*this = b;
			return;
		}
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		if (ptr0->length + b.ptr0->length > ptr0->total)
		{
			long long length = ptr0->length + b.ptr0->length;
			while (ptr0->total < length)
				ptr0->total = ptr0->total + TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}

		long long i = 0;
		for (i = static_cast<long long>(ptr0->length); i >= a; i--)
			ptr0->elements[i - 1 + b.ptr0->length] = ptr0->elements[i - 1];
		long long count = a;
		for (i = 1; i <= b.Listlength(); i++)
		{
			ptr0->elements[count - 1] = b.ptr0->elements[i - 1];
			count = count + 1;
		}
		ptr0->length = ptr0->length + b.ptr0->length;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			*this = b;
			return;
		}
		if (a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		node* scan = b.ptr1->first;
		node* target = ptr1->first;
		long long i = 1;
		while (i != a)
		{
			target = target->next;
			i = i + 1;
		}
		ptr1->num_elements = ptr1->num_elements + b.ptr1->num_elements;

		for (i = 1; i <= b.Listlength(); i++)
		{
			if (target->prior == nullptr)
			{
				node* temp = new node;
				temp->element = scan->element;
				temp->next = target;
				temp->prior = nullptr;
				target->prior = temp;
				ptr1->first = temp;
			}
			else
			{
				node* temp = new node;
				temp->element = scan->element;
				temp->next = target;
				temp->prior = target->prior;
				temp->prior->next = temp;
				target->prior = temp;
			}
			scan = scan->next;
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::ListinsertR(const long long a, const Type b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	//假如只有三个元素abc,则序号的范围是1-3,插入结果（只有三种）是aXbc,abXc,abcX
	if (type == 0)
	{
		if (ptr0->length == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			ptr0->elements[0] = b;
			ptr0->length = ptr0->length + 1;
			return;
		}
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		if (ptr0->length + 1 > ptr0->total)
		{
			long long length = ptr0->length + 1;
			while (ptr0->total < length)
				ptr0->total = ptr0->total + TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}

		long long i = 0;
		for (i = static_cast<long long>(ptr0->length); i > a; i--)
		{
			ptr0->elements[i] = ptr0->elements[i - 1];
		}
		ptr0->elements[a] = b;
		ptr0->length = ptr0->length + 1;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//线性表为空
		{
			ptr1->num_elements = ptr1->num_elements + 1;
			ptr1->first->element = b;
			return;
		}
		if (a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		node* target = nullptr;
		if (a == Listlength())
			target = ptr1->end;
		else
		{
			target = ptr1->first;
			long long i = 1;
			while (i != a)
			{
				target = target->next;
				i = i + 1;
			}
		}
		ptr1->num_elements = ptr1->num_elements + 1;
		if (target == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}

		if (target->next == nullptr)
		{
			node* temp = new node;
			temp->element = b;
			temp->next = nullptr;
			temp->prior = target;
			target->next = temp;
			ptr1->end = temp;
			return;
		}
		node* temp = new node;
		temp->element = b;
		temp->next = target->next;
		temp->prior = target;
		temp->next->prior = temp;
		target->next = temp;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::ListinsertR(const long long a, const LIST& b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】作为被插入对象的表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】作为插入对象的表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type != b.type)
	{
		cout << "\033[1;31m【错误】插入对象和被插入对象的类型不同，无法执行任何操作\033[0m" << endl;
		return;
	}
	//假如只有三个元素abc,则序号的范围是1-3,插入结果（只有三种）是aXbc,abXc,abcX

	if (type == 0)
	{
		if (ptr0->length == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			*this = b;
			return;
		}
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		if (ptr0->length + b.ptr0->length > ptr0->total)
		{
			long long length = ptr0->length + b.ptr0->length;
			while (ptr0->total < length)
				ptr0->total = ptr0->total + TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}

		long long i = 0;
		for (i = static_cast<long long>(ptr0->length); i > a; i--)
			ptr0->elements[i - 1 + b.ptr0->length] = ptr0->elements[i - 1];
		long long count = a + 1;
		for (i = 1; i <= b.Listlength(); i++)
		{
			ptr0->elements[count - 1] = b.ptr0->elements[i - 1];
			count = count + 1;
		}
		ptr0->length = ptr0->length + b.ptr0->length;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//线性表为空
		{
			//如果没有这个语句块，程序将无法对空表执行插入
			*this = b;
			return;
		}
		if (a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要插入元素，但是提供的位置序号有误\033[0m" << endl;
			return;
		}
		node* scan = b.ptr1->first;
		node* target = nullptr;
		if (a == Listlength())
			target = ptr1->end;
		else
		{
			target = ptr1->first;
			long long i = 1;
			while (i != a)
			{
				target = target->next;
				i = i + 1;
			}
		}
		ptr1->num_elements = ptr1->num_elements + b.ptr1->num_elements;

		for (long long i = 1; i <= b.Listlength(); i++)
		{
			if (target->next == nullptr)
			{
				node* temp = new node;
				temp->element = scan->element;
				temp->next = nullptr;
				temp->prior = target;
				target->next = temp;
				ptr1->end = temp;
			}
			else
			{
				node* temp = new node;
				temp->element = scan->element;
				temp->next = target->next;
				temp->prior = target;
				temp->next->prior = temp;
				target->next = temp;
			}
			target = target->next;
			scan = scan->next;
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Listexpand(const long long a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (a < 0)
		{
			cout << "\033[1;31m【错误】提供的未来要插入的元素总量有误\033[0m" << endl;
			return;
		}
		if (ptr0->length + a > ptr0->total)
		{
			long long length = ptr0->length + a;
			while (ptr0->total < length)
				ptr0->total = ptr0->total + TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}
		return;
	}
	if (type == 1)
	{
		cout << "【提示】对链表使用扩容函数没有意义，请只对线性表使用此函数" << endl;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Smart_expand()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}

	if (type == 0)
	{
		const long double MAX_DELTA = 1000000.0L;//扩容的增量最大是xx
		const long double MULTIPLE = 0.75;//扩容的增量是原来大小的xx倍
		const long double RE_LIMIT = 0.9;//当元素数量/表长超过xx时，触发自动扩容

		long double current_length = static_cast<long double>(ptr0->length);
		long double current_total = static_cast<long double>(ptr0->total);
		if (current_length / current_total > RE_LIMIT)
		{
			long long delta = 0;
			if (current_total * MULTIPLE > MAX_DELTA)
				delta = static_cast<long long>(MAX_DELTA);
			else
				delta = static_cast<long long>(current_total * MULTIPLE);
			Listexpand(delta);
		}
		return;
	}
	if (type == 1)
		return;
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Listshrink()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if ((ptr0->total - TABLE_DELTA >= TABLE_INIT) && (ptr0->total - TABLE_DELTA >= ptr0->length))
		{
			while ((ptr0->total - TABLE_DELTA >= TABLE_INIT) && (ptr0->total - TABLE_DELTA >= ptr0->length))
				ptr0->total = ptr0->total - TABLE_DELTA;
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (ptr0->length + 1), ptr0->elements, sizeof(Type) * ptr0->length);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}
		return;
	}
	if (type == 1)
	{
		cout << "【提示】对链表使用缩紧函数没有意义，请只对线性表使用此函数" << endl;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Smart_shrink(const bool clear)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	const long double CLEAR_REMAIN = 0.5;
	//在清空原始线性表的选项下，将新的表长改为原来表长的xx倍

	const long double CLEAR_TOTAL_MIN = 500.0;
	//在清空原始线性表的选项下，如果确定要修改表长，但是修改后的表长小于xx，则取消修改操作。
	
	const long double REMAIN = 0.8;
	//在不清空原始线性表的选项下，若元素数量/表长大于等于xx，则不进行任何操作。
	//否则，将新的表长改为原来表长的xx倍（且长度最少为ptr0->length）
	
	const long double TOTAL_MIN = 500.0;
	//在不清空原始线性表的选项下，如果确定要修改表长，但是修改后的表长小于xx，则取消修改操作。

	if (type == 0)
	{
		long double current_length = static_cast<long double>(ptr0->length);
		long double current_total = static_cast<long double>(ptr0->total);
		long long delta = 0;
		if (clear == true)
		{
			delta = static_cast<long long>(current_total * CLEAR_REMAIN);
			if (delta < static_cast<long long>(CLEAR_TOTAL_MIN))	
				Clear_resize(ptr0->total);//新的表长小于临界值，则只清空表(删除全部元素)，表长不变
			else
				Clear_resize(delta);//新的表长大于等于临界值，则清空表，并将表长设为新的表长
			return;
		}
		else
		{
			if (current_length / current_total >= REMAIN)
				return;
			delta = static_cast<long long>(current_total * REMAIN);
			if (delta < ptr0->length)
				delta = ptr0->length;
			if (delta < static_cast<long long>(TOTAL_MIN))
				return;

			long long length_backup = ptr0->length;
			ptr0->length = delta;
			Listshrink();
			ptr0->length = length_backup;
			return;
		}
		return;
	}
	if (type == 1)
	{
		if (clear == true)
			Clearlist();
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
Type LIST<Type>::Listdelete(const long long a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(-1);
	}
	if ((type == 0 && (a <= 0 || a > ptr0->length)) || (type == 1 && (a <= 0 || a > ptr1->num_elements)))
	{
		cout << "\033[1;31m【错误】要删除的元素的序号错误\033[0m" << endl;
		return static_cast<Type>(-1);
	}

	if (type == 0)//0为线性表，1为链表
	{
		Type x = ptr0->elements[a - 1];
		if (a + 1 <= Listlength())
		{
			for (long long i = a + 1; i <= Listlength(); i++)
				ptr0->elements[i - 2] = ptr0->elements[i - 1];
			ptr0->length = ptr0->length - 1;
		}
		else
			ptr0->length = a - 1;
		Listshrink();
		return x;
	}
	if (type == 1)
	{
		node* temp = nullptr;
		if (a == Listlength())
			temp = ptr1->end;
		else
		{
			temp = ptr1->first;
			long long i = 1;
			while (i != a)
			{
				temp = temp->next;
				i = i + 1;
			}
		}
		if (temp == nullptr)
			return static_cast<Type>(-1);//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
		Type x = temp->element;

		if (ptr1->num_elements == 1)//如果只有一个结点
		{
			ptr1->first->element = static_cast<Type>(0);
			ptr1->num_elements = ptr1->num_elements - 1;
			return x;
		}
		if (temp->prior == nullptr && temp->next != nullptr)//如果是第一个结点
		{
			ptr1->first = temp->next;
			ptr1->first->prior = nullptr;
			ptr1->num_elements = ptr1->num_elements - 1;
			delete temp;
			return x;
		}
		if (temp->prior != nullptr && temp->next == nullptr)//如果是最后一个结点
		{
			ptr1->end = temp->prior;
			ptr1->num_elements = ptr1->num_elements - 1;
			temp->prior->next = nullptr;
			delete temp;
			return x;
		}
		if (temp->prior != nullptr && temp->next != nullptr)
		{
			ptr1->num_elements = ptr1->num_elements - 1;
			temp->prior->next = temp->next;
			temp->next->prior = temp->prior;
			delete temp;
			return x;
		}
		return x;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return static_cast<Type>(-1);
}

template<typename Type>
void LIST<Type>::Listdelete(const long long a, const long long b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((type == 0 && (a <= 0 || a > ptr0->length)) || (type == 1 && (a <= 0 || a > ptr1->num_elements)))
	{
		cout << "\033[1;31m【错误】要删除的元素的序号错误\033[0m" << endl;
		return;
	}
	if (a + b - 1 > Listlength())
	{
		cout << "\033[1;33m【警告】要删除的元素的范围超过表的范围\033[0m";
		cout << "\033[1;33m,删除的最后一个元素将被设置为表的最后一个元素\033[0m" << endl;
	}

	if (type == 0)//0为线性表，1为链表
	{
		if (a + b <= Listlength())
		{
			for (long long i = a + b; i <= Listlength(); i++)
				ptr0->elements[i - b - 1] = ptr0->elements[i - 1];
			ptr0->length = ptr0->length - b;
		}
		else
			ptr0->length = a - 1;
		Listshrink();
		return;
	}
	if (type == 1)
	{
		node* temp = nullptr;
		if (a == Listlength())
			temp = ptr1->end;
		else
		{
			temp = ptr1->first;
			long long i = 1;
			while (i != a)
			{
				temp = temp->next;
				i = i + 1;
			}
		}
		if (temp == nullptr)
			return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义

		for (long long i1 = 1; i1 <= b; i1++)
		{
			if (ptr1->num_elements == 1)//如果只有一个结点
			{
				ptr1->first->element = static_cast<Type>(0);
				ptr1->num_elements = ptr1->num_elements - 1;
				return;
			}
			if (temp->prior == nullptr && temp->next != nullptr)//如果是第一个结点
			{
				node* temp_backup = temp->next;
				ptr1->first = temp->next;
				ptr1->first->prior = nullptr;
				ptr1->num_elements = ptr1->num_elements - 1;
				delete temp;
				temp = temp_backup;
				continue;
			}
			if (temp->prior != nullptr && temp->next == nullptr)//如果是最后一个结点
			{
				ptr1->end = temp->prior;
				ptr1->num_elements = ptr1->num_elements - 1;
				temp->prior->next = nullptr;
				delete temp;
				return;
			}
			if (temp->prior != nullptr && temp->next != nullptr)
			{
				node* temp_backup = temp->next;
				ptr1->num_elements = ptr1->num_elements - 1;
				temp->prior->next = temp->next;
				temp->next->prior = temp->prior;
				delete temp;
				temp = temp_backup;
				continue;
			}
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
long long LIST<Type>::Listsize() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
		return ptr0->total;
	if (type == 1)
		return ptr1->num_elements;
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return -1;
}

template<typename Type>
long long LIST<Type>::Listcapacity() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
		return ptr0->total - ptr0->length;
	if (type == 1)
		return 0;
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return -1;
}

template<typename Type>
void LIST<Type>::Listresize(const long long a, const Type b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (Listlength() == a)
		return;

	if (type == 0)
	{
		if (Listlength() < a)
		{
			Listexpand(a - Listlength());
			while (Listlength() < a)
				ListinsertR(Listlength(), b);
		}
		if (Listlength() > a)
			Listdelete(a + 1, Listlength() - a);
		return;
	}
	if (type == 1)
	{
		while (Listlength() < a)
			ListinsertR(Listlength(), b);
		while (Listlength() > a)
			Listdelete(Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Listfill(const long long a, const long long b, const Type x)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (a != 0 && a != 1 && a != 2 && a != 3)
	{
		cout << "\033[1;31m【错误】输入的填充模式有错误，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (b < 0)
	{
		cout << "\033[1;31m【错误】要填充的元素数量有误，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (b == 0)
		return;
	//本函数目前只支持下列类型的对象
	if (strcmp(typeid(Type).name(), typeid(char).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(short).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(float).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(int).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(double).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long double).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long long).name()) != 0)
	{
		cout << "\033[1;31m【错误】本填充函数不支持该对象的数据类型，无法执行任何操作\033[0m" << endl;
		return;
	}

	//注意：与常识相反，最小浮点数这个常量无限接近于0，但是大于0。如FLT_MIN。FLT_MIN不等于-FLT_MAX！！！
	//所以浮点数能取到的最小值是-FLT_MAX，而非FLT_MIN！！！
	
	//注意以下表达式和类似的表达式：
	//static_cast             <float>(LLONG_MAX) = 9.22337e+18（最长的整形转为最短的浮点型不会出问题）
	//static_cast           <short>(LLONG_MAX/2) = -1
	//static_cast         <long long>(LLONG_MAX*2) = -2
	//static_cast<unsigned long long>(LLONG_MAX*2) = 18446744073709551614
	//static_cast         <long long>  (INT_MAX) = 2147483647
	//static_cast<unsigned long long>(1233.802f) = 1233
	//static_cast         <long long>(LLONG_MIN) = -9223372036854775808
	//static_cast<unsigned long long>(LLONG_MAX) = 9223372036854775808（19位数字）
	//注意float的指数位最大可以是38（你应该知道我要说什么.jpg）

	//注意以下表达式和类似的表达式：（结果与常识相反！！！）
	//static_cast         <long long>(FLT_MIN) = 0
	//static_cast<unsigned long long>(FLT_MIN) = 0（最短的浮点型转为最长的整形反而会出大问题）
	//static_cast<unsigned long long>(FLT_MAX) = 0（最短的浮点型转为最长的整形反而会出大问题）
	//static_cast<unsigned long long>(DBL_MIN) = 0
	//static_cast<unsigned long long>(DBL_MAX) = 0

	//正序插入
	if (a == 0)
	{
		if (type == 0)
			Listexpand(b);

		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0)
		{
			long long start = -b / 2 + 79;//大写字母O
			if (start < static_cast<long long>(32))
				start = static_cast<long long>(32);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(126))//波浪号
					start = static_cast<long long>(32);//空格
				else
					start = start + 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(short).name()) == 0)
		{
			long long start = -b / 2;
			if (start < static_cast<long long>(SHRT_MIN))
				start = static_cast<long long>(SHRT_MIN);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(SHRT_MAX))
					start = static_cast<long long>(SHRT_MIN);
				else
					start = start + 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(int).name()) == 0)
		{
			long long start = -b / 2;
			if (start < static_cast<long long>(INT_MIN))
				start = static_cast<long long>(INT_MIN);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(INT_MAX))
					start = static_cast<long long>(INT_MIN);
				else
					start = start + 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(long).name()) == 0)
		{
			long long start = -b / 2;
			if (start < static_cast<long long>(LONG_MIN))
				start = static_cast<long long>(LONG_MIN);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(LONG_MAX))
					start = static_cast<long long>(LONG_MIN);
				else
					start = start + 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(long long).name()) == 0)
		{
			long long start = -b / 2;
			if (start < static_cast<long long>(LLONG_MIN))
				start = static_cast<long long>(LLONG_MIN);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(LLONG_MAX))
					start = static_cast<long long>(LLONG_MIN);
				else
					start = start + 1;
			}
		}

		if ((strcmp(typeid(Type).name(), typeid(float).name()) == 0) ||
			(strcmp(typeid(Type).name(), typeid(double).name()) == 0) ||
			(strcmp(typeid(Type).name(), typeid(long double).name()) == 0))
		{
			std::uniform_real_distribution<float> FLOAT(0, 1);
			std::random_device rd;
			std::default_random_engine e(rd());
			long long start = -b / 2;
			for (long long i = 1; i <= b; i++)
			{
				//插入的数字 = 被强制转为浮点类型的整数初始值 + 0~1之间的随机浮点数
				ListinsertR(Listlength(), static_cast<Type>(start) + static_cast<Type>(FLOAT(e)));
				start = start + 1;
			}
		}
		return;
	}

	//逆序插入
	if (a == 1)
	{
		if (type == 0)
			Listexpand(b);

		if (strcmp(typeid(Type).name(), typeid(char).name()) == 0)
		{
			long long start = b / 2 + 79;//大写字母O
			if (start > static_cast<long long>(126))
				start = static_cast<long long>(126);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(32))//空格
					start = static_cast<long long>(126);//波浪号
				else
					start = start - 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(short).name()) == 0)
		{
			long long start = b / 2;
			if (start > static_cast<long long>(SHRT_MAX))
				start = static_cast<long long>(SHRT_MAX);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(SHRT_MIN))
					start = static_cast<long long>(SHRT_MAX);
				else
					start = start - 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(int).name()) == 0)
		{
			long long start = b / 2;
			if (start > static_cast<long long>(INT_MAX))
				start = static_cast<long long>(INT_MAX);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(INT_MIN))
					start = static_cast<long long>(INT_MAX);
				else
					start = start - 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(long).name()) == 0)
		{
			long long start = b / 2;
			if (start > static_cast<long long>(LONG_MAX))
				start = static_cast<long long>(LONG_MAX);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(LONG_MIN))
					start = static_cast<long long>(LONG_MAX);
				else
					start = start - 1;
			}
		}
		if (strcmp(typeid(Type).name(), typeid(long long).name()) == 0)
		{
			long long start = b / 2;
			if (start > static_cast<long long>(LLONG_MAX))
				start = static_cast<long long>(LLONG_MAX);
			for (long long i = 1; i <= b; i++)
			{
				ListinsertR(Listlength(), static_cast<Type>(start));
				if (start == static_cast<long long>(LLONG_MIN))
					start = static_cast<long long>(LLONG_MAX);
				else
					start = start - 1;
			}
		}

		if ((strcmp(typeid(Type).name(), typeid(float).name()) == 0) ||
			(strcmp(typeid(Type).name(), typeid(double).name()) == 0) ||
			(strcmp(typeid(Type).name(), typeid(long double).name()) == 0))
		{
			std::uniform_real_distribution<float> FLOAT(0, 1);
			std::random_device rd;
			std::default_random_engine e(rd());
			long long start = b / 2;
			for (long long i = 1; i <= b; i++)
			{
				//插入的数字 = 被强制转为浮点类型的整数初始值 + 0~1之间的随机浮点数
				ListinsertR(Listlength(), static_cast<Type>(start) + static_cast<Type>(FLOAT(e)));
				start = start - 1;
			}
		}
		return;
	}

	//随机值插入
	if (a == 2)
	{
		std::bernoulli_distribution BOOL(0.5);
		std::uniform_int_distribution<int> CHAR(32, 126);
		std::uniform_int_distribution<short> SHORT(SHRT_MIN, SHRT_MAX);
		std::uniform_int_distribution<int> INT(INT_MIN, INT_MAX);
		std::uniform_int_distribution<long> LONG(LONG_MIN, LONG_MAX);
		std::uniform_int_distribution<long long> LONGLONG(LLONG_MIN, LLONG_MAX);
		std::uniform_real_distribution<float> FLOAT(FLT_MIN, FLT_MAX);
		std::uniform_real_distribution<double> DOUBLE(DBL_MIN, DBL_MAX);
		std::uniform_real_distribution<long double> LONGDOUBLE(LDBL_MIN, LDBL_MAX);
		std::random_device rd;
		std::default_random_engine e(rd());

		if (type == 0)
			Listexpand(b);
		for (long long i = 1; i <= b; i++)
		{
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0)
				ListinsertR(Listlength(), static_cast<char>(CHAR(e)));
			if (strcmp(typeid(Type).name(), typeid(short).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(SHORT(e)));
			if (strcmp(typeid(Type).name(), typeid(int).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(INT(e)));
			if (strcmp(typeid(Type).name(), typeid(long).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(LONG(e)));
			if (strcmp(typeid(Type).name(), typeid(long long).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(LONGLONG(e)));
			if (strcmp(typeid(Type).name(), typeid(float).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(FLOAT(e) * (BOOL(e) * 2 - 1)));
			if (strcmp(typeid(Type).name(), typeid(double).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(DOUBLE(e)) * static_cast<Type>(BOOL(e) * 2 - 1));
			if (strcmp(typeid(Type).name(), typeid(long double).name()) == 0)
				ListinsertR(Listlength(), static_cast<Type>(LONGDOUBLE(e)) * static_cast<Type>(BOOL(e) * 2 - 1));
		}
		return;
	}

	//特定值插入
	if (a == 3)
	{
		if (type == 0)
			Listexpand(b);
		for (long long i = 1; i <= b; i++)
			ListinsertR(Listlength(), x);
		return;
	}

	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Update(const long long a, const Type b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)//0为线性表，1为链表
	{
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要更新的元素的序号错误\033[0m" << endl;
			return;
		}
		ptr0->elements[a - 1] = b;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0 || a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要更新的元素的序号错误\033[0m" << endl;
			return;
		}
		node* temp = ptr1->first;
		long long i = 1;
		while (i != a)
		{
			temp = temp->next;
			i = i + 1;
		}
		if (temp == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}
		temp->element = b;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Display() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	bool c_tab = true;
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
		c_tab = false;
	}
	if (type == 0)//0为线性表，1为链表
	{
		if (ptr0 == nullptr || ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return;
		}
		long long i = 1;
		for (i = 1; i <= ptr0->length - 1; i++)
		{
			cout << ptr0->elements[i - 1];
			if (c_tab == true)
				cout << "   ";
		}
		cout << ptr0->elements[i - 1];
		cout << endl;
		return;
	}
	if (type == 1)
	{
		if (ptr1 == nullptr || ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return;
		}
		node* start = ptr1->first;
		node* end = ptr1->end;
		while (start != end)
		{
			cout << start->element;
			start = start->next;
			if (c_tab == true)
				cout << "   ";
		}
		cout << start->element << endl;
		return;
	}
	cout << "\033[1;31m【错误】表的类型有错误，无法输出任何信息\033[0m" << endl;
	return;
}

template<typename Type>
void LIST<Type>::Output_to_file(const char* PATH, const bool clear) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}

	fstream output;
	if (clear == true)
		output.open(PATH, std::ios::in | std::ios::out | std::ios::trunc);
	else
		output.open(PATH, std::ios::in | std::ios::out | std::ios::ate);
	if (!output)
	{
		cout << "\033[1;31m【错误】文件路径下的文件无法打开，无法执行任何操作\033[0m" << endl;
		return;
	}

	bool c_tab = true;
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
		c_tab = false;
	}
	if (type == 0)//0为线性表，1为链表
	{
		if (ptr0 == nullptr || ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			output.close();
			return;
		}
		long long i = 1;
		for (i = 1; i <= ptr0->length - 1; i++)
		{
			output << ptr0->elements[i - 1];
			if (c_tab == true)
				output << "   ";
		}
		output << ptr0->elements[i - 1];
		output.close();
		return;
	}
	if (type == 1)
	{
		if (ptr1 == nullptr || ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			output.close();
			return;
		}
		node* start = ptr1->first;
		node* end = ptr1->end;
		while (start != end)
		{
			output << start->element;
			start = start->next;
			if (c_tab == true)
				output << "   ";
		}
		output << start->element;
		output.close();
		return;
	}
	
	cout << "\033[1;31m【错误】表的类型有错误，无法输出任何信息\033[0m" << endl;
	output.close();
	return;
}

template<typename Type>
void LIST<Type>::Exchange(const long long a, const long long b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (a == b)
	{
		cout << "\033[1;31m【错误】要交换的两个元素的序号相同\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】要交换的第一个元素的序号错误\033[0m" << endl;
			return;
		}
		if (b <= 0 || b > ptr0->length)
		{
			cout << "\033[1;31m【错误】要交换的第二个元素的序号错误\033[0m" << endl;
			return;
		}
		Type temp = ptr0->elements[a - 1];
		ptr0->elements[a - 1] = ptr0->elements[b - 1];
		ptr0->elements[b - 1] = temp;
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0 || a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要交换的第一个元素的序号错误\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 0 || b <= 0 || b > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】要交换的第二个元素的序号错误\033[0m" << endl;
			return;
		}
		node* temp_a = ptr1->first;
		long long i = 1;
		while (i != a)
		{
			temp_a = temp_a->next;
			i = i + 1;
		}
		if (temp_a == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}
		node* temp_b = ptr1->first;
		i = 1;
		while (i != b)
		{
			temp_b = temp_b->next;
			i = i + 1;
		}
		if (temp_b == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}
		Type temp = temp_a->element;
		temp_a->element = temp_b->element;
		temp_b->element = temp;
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Info() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		cout << "类型：线性表" << endl;
		cout << "存储的数据的类型：" << typeid(Type).name() << endl;
		cout << "表长：" << ptr0->total << endl;
		cout << "表中的元素数量：" << ptr0->length << endl;
		return;
	}
	if (type == 1)
	{
		cout << "类型：链表" << endl;
		cout << "存储的数据的类型：" << typeid(Type).name() << endl;
		if (ptr1->num_elements == 0)
			cout << "链表的结点数量：1" << endl;
		else
			cout << "链表的结点数量：" << ptr1->num_elements << endl;
		cout << "链表中的元素数量：" << ptr1->num_elements << endl;
		return;
	}
	cout << "\033[1;31m【错误】表的类型有错误，无法输出任何信息\033[0m" << endl;
	return;
}

template<typename Type>
void LIST<Type>::Typeswitch(const int target)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (target != 0 && target != 1)
	{
		cout << "\033[1;31m【错误】输入的表的目标格式有误\033[0m" << endl;
		return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】待转换的表自身的类型有误，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == target)
	{
		cout << "\033[1;31m【错误】待转换的表的类型与目标类型相同，无需执行转换操作\033[0m" << endl;
		return;
	}

	if (target == 0)
	{
		linear* temp = new linear;
		temp->length = ptr1->num_elements;
		temp->total = TABLE_INIT;
		while (temp->total < temp->length)
			temp->total = temp->total + TABLE_DELTA;
		temp->elements = new Type[temp->total]();
		if (temp->length == 0)
		{
			temp->elements[0] = static_cast<Type>(0);
		}
		else
		{
			node* first = ptr1->first;
			node* end = ptr1->end;
			long long i = 0;
			while (first != end)
			{
				temp->elements[i] = first->element;
				first = first->next;
				i = i + 1;
			}
			temp->elements[i] = first->element;
		}

		this->~LIST();
		type = 0;
		ptr0 = temp;
		ptr1 = nullptr;
	}
	if (target == 1)
	{
		chain_manage* temp_m = new chain_manage;
		temp_m->num_elements = ptr0->length;
		node* temp_n = new node;
		temp_m->first = temp_n;
		if (ptr0->length == 0)
			temp_n->element = static_cast<Type>(0);
		else
			temp_n->element = ptr0->elements[0];
		temp_n->prior = nullptr;
		temp_n->next = nullptr;
		for (long long i = 2; i <= ptr0->length; i++)
		{
			node* temp_o = new node;
			temp_o->element = ptr0->elements[i - 1];
			temp_o->next = nullptr;
			temp_o->prior = temp_n;
			temp_n->next = temp_o;
			temp_n = temp_o;
		}
		temp_m->end = temp_n;

		this->~LIST();
		type = 1;
		ptr0 = nullptr;
		ptr1 = temp_m;
	}
}

template<typename Type>
void LIST<Type>::Repair(const int a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0 || type == 1)
	{
		cout << "\033[1;31m【错误】表的类型正确，无需执行修复操作\033[0m" << endl;
		return;
	}
	if (a != 0 && a != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，但是输入的表的目标类型仍然错误，无法执行修复操作\033[0m" << endl;
		return;
	}
	if (a == 0)
	{
		type = 0;
		linear* temp = new linear;
		temp->total = TABLE_INIT;
		temp->length = 0;
		temp->elements = new Type[TABLE_INIT];
		temp->elements[0] = static_cast<Type>(0);
		ptr0 = temp;
		ptr1 = nullptr;
		return;
	}
	if (a == 1)
	{
		type = 1;
		chain_manage* temp_m = new chain_manage;
		temp_m->num_elements = 0;
		node* temp_n = new node;
		temp_n->element = static_cast<Type>(0);
		temp_n->next = nullptr;
		temp_n->prior = nullptr;
		temp_m->end = temp_n;
		temp_m->first = temp_n;
		ptr0 = nullptr;
		ptr1 = temp_m;
		return;
	}
}

template<typename Type>
int LIST<Type>::Gettype() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return 0;
	}
	return type;
}

template<typename Type>
void LIST<Type>::Reverse(const long long a, const long long b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (a > b)
	{
		cout << "\033[1;31m【错误】输入的序号范围有错误\033[0m" << endl;
		return;
	}
	if (a == b)
		return;

	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】线性表是空的\033[0m" << endl;
			return;
		}
		if (a <= 0 || a > ptr0->length)
		{
			cout << "\033[1;31m【错误】输入的序号范围有错误\033[0m" << endl;
			return;
		}
		if (b <= 0 || b > ptr0->length)
		{
			cout << "\033[1;31m【错误】输入的序号范围有错误\033[0m" << endl;
			return;
		}
		long long low = a - 1;
		long long high = b - 1;
		while (low < high)
		{
			Type temp = ptr0->elements[low];
			ptr0->elements[low] = ptr0->elements[high];
			ptr0->elements[high] = temp;
			low = low + 1;
			high = high - 1;
		}
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】链表是空的\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 0 || a <= 0 || a > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】输入的序号范围有错误\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 0 || b <= 0 || b > ptr1->num_elements)
		{
			cout << "\033[1;31m【错误】输入的序号范围有错误\033[0m" << endl;
			return;
		}
		node* low = ptr1->first;
		long long i = 1;
		while (i != a)
		{
			low = low->next;
			i = i + 1;
		}
		if (low == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}
		node* high = low;
		i = a;
		while (i != b)
		{
			high = high->next;
			i = i + 1;
		}
		if (high == nullptr)
		{
			cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
			return;
		}
		
		while (low != high && high->next != low)
		{
			Type temp = low->element;
			low->element = high->element;
			high->element = temp;
			low = low->next;
			high = high->prior;
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
Type LIST<Type>::Max() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<Type>(0);
		}
		if (ptr0->length == 1)
			return ptr0->elements[0];

		Type temp = ptr0->elements[0];
		for (long long i = 2; i <= Listlength(); i++)
		{
			if (ptr0->elements[i - 1] > temp)
				temp = ptr0->elements[i - 1];
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<Type>(0);
		}
		if (ptr1->num_elements == 1)
			return ptr1->first->element;

		node* temp = ptr1->first;
		node* scan = ptr1->first->next;
		while (scan != nullptr)
		{
			if (scan->element > temp->element)
				temp = scan;
			scan = scan->next;
		}
		return temp->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return -1;
}

template<typename Type>
Type LIST<Type>::Min() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<Type>(0);
		}
		if (ptr0->length == 1)
			return ptr0->elements[0];

		Type temp = ptr0->elements[0];
		for (long long i = 2; i <= Listlength(); i++)
		{
			if (ptr0->elements[i - 1] < temp)
				temp = ptr0->elements[i - 1];
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<Type>(0);
		}
		if (ptr1->num_elements == 1)
			return ptr1->first->element;

		node* temp = ptr1->first;
		node* scan = ptr1->first->next;
		while (scan != nullptr)
		{
			if (scan->element < temp->element)
				temp = scan;
			scan = scan->next;
		}
		return temp->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return -1;
}

template<typename Type>
long double LIST<Type>::Sum() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<long double>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<long double>(0);
		}
		if (ptr0->length == 1)
			return static_cast<long double>(ptr0->elements[0]);

		long double sum = 0;
		for (long long i = 1; i <= Listlength(); i++)
		{
			sum = sum + ptr0->elements[i - 1];
		}
		return sum;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return static_cast<long double>(0);
		}
		if (ptr1->num_elements == 1)
			return static_cast<long double>(ptr1->first->element);

		long double sum = 0;
		node* temp = ptr1->first;
		for (long long i = 1; i <= Listlength(); i++)
		{
			sum = sum + temp->element;
			temp = temp->next;
		}
		return sum;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<long double>(0);
}

template<typename Type>
Type LIST<Type>::Stack_gettop() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】栈中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return ptr0->elements[0];
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】栈中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return ptr1->first->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(-1);
}

template<typename Type>
void LIST<Type>::Stack_push(const Type& a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	ListinsertF(1, a);
	return;
}

template<typename Type>
Type LIST<Type>::Stack_pop()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】栈中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		Type temp = Listdelete(1);
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】栈中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		Type temp = Listdelete(1);
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(-1);
}

template<typename Type>
Type LIST<Type>::Queue_gethead() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return ptr0->elements[0];
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return ptr1->first->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(-1);
}

template<typename Type>
Type LIST<Type>::Queue_gettail() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return Getelement(Listlength());
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		return Getelement(Listlength());
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(-1);
}

template<typename Type>
void LIST<Type>::Queue_enqueue(const Type& a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	ListinsertR(Listlength(), a);
	return;
}

template<typename Type>
Type LIST<Type>::Queue_dequeue()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		Type temp = Listdelete(1);
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】队列中没有任何元素\033[0m" << endl;
			return static_cast<Type>(-1);
		}
		Type temp = Listdelete(1);
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(-1);
}

template<typename Type>
bool LIST<Type>::Repeat_TF() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
		return false;
	}
	if (Listlength() == 0 || Listlength() == 1)
		return false;
	if (Listlength() == 2)
	{
		if ((type == 0 && ptr0->elements[0] == ptr0->elements[1]) ||
			(type == 1 && ptr1->first->element == ptr1->end->element))
			return true;
		else
			return false;
	}

	LIST<Type> TEMP = *this;
	TEMP.Sort(0);
	bool REPEAT = false;
	if (type == 0)
	{
		for (long long i = 0; i <= Listlength() - 2; i++)
		{
			if (TEMP.ptr0->elements[i] == TEMP.ptr0->elements[i + 1])
			{
				REPEAT = true;
				break;
			}
		}
		return REPEAT;
	}
	if (type == 1)
	{
		node* scan = TEMP.ptr1->first;
		for (long long i = 0; i <= Listlength() - 2; i++)
		{
			if (scan->element == scan->next->element)
			{
				REPEAT = true;
				break;
			}
			scan = scan->next;
		}
		return REPEAT;
	}
	return false;
}

template<typename Type>
bool LIST<Type>::Symmetric_TF() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return false;
		}

		bool symmetric = true;
		long long start = 0;
		long long end = ptr0->length - 1;
		while (start != end && start - 1 != end)
		{
			if (ptr0->elements[start] == ptr0->elements[end])
			{
				start = start + 1;
				end = end - 1;
			}
			else
			{
				symmetric = false;
				break;
			}
		}
		return symmetric;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return false;
		}

		bool symmetric = true;
		node* start = ptr1->first;
		node* end = ptr1->end;
		while (start != end && start->prior != end)
		{
			if (start->element == end->element)
			{
				start = start->next;
				end = end->prior;
			}
			else
			{
				symmetric = false;
				break;
			}
		}
		return symmetric;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return false;
}

template<typename Type>
void LIST<Type>::Clear_copy(const LIST& b)
{
	*this = b;//这个函数存在的意义是展示调用重载的赋值运算符的方法
	return;
}

template<typename Type>
void LIST<Type>::Overwrite(const long long a, const LIST& b)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】被覆写的串不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】提供覆写内容的串不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((b.type == 0 && b.ptr0->length == 0) || (b.type == 1 && b.ptr1->num_elements == 0))
	{
		cout << "\033[1;31m【错误】提供覆写内容的串为空，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((type == 0 && ptr0->length == 0) || (type == 1 && ptr1->num_elements == 0))
	{
		cout << "\033[1;33m【警告】被覆写的串为空，函数会将提供覆写内容的串整体复制到被覆写的串\033[0m" << endl;
		Clear_copy(b);
		return;
	}
	if (type != b.type)
	{
		cout << "\033[1;31m【错误】两个串的类型不同，进行覆写操作前，请先将其转换为同一类型\033[0m" << endl;
		return;
	}
	if (a <= 0)
	{
		cout << "\033[1;31m【错误】提供的位置序号小于等于0，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((type == 0 && a > ptr0->length) || (type == 1 && a > ptr1->num_elements))
	{
		cout << "\033[1;33m【警告】提供的位置序号大于被覆写的串的元素数量，\033[0m";
		cout << "\033[1;33m函数会将提供覆写内容的串拼接到被覆写的串的后面\033[0m" << endl;
		*this += b;
		return;
	}

	if (type == 0)
	{
		if (a + b.Listlength() - 1 > Listlength())
		{
			long long backup = ptr0->length;
			ptr0->length = a + b.Listlength() - 1;
			bool move = 0;
			while (ptr0->total < ptr0->length)
			{
				ptr0->total = ptr0->total + TABLE_DELTA;
				move = 1;
			}
			if (move == 1)
			{
				Type* T = new Type[ptr0->total]();
				memmove_s(T, sizeof(Type) * (backup + 1), ptr0->elements, sizeof(Type) * backup);
				delete[] ptr0->elements;
				ptr0->elements = T;
			}
		}

		long long pos_backup = a;
		for (long long i = 1; i <= b.Listlength(); i++)
		{
			ptr0->elements[pos_backup - 1] = b.ptr0->elements[i - 1];
			pos_backup = pos_backup + 1;
		}
		return;
	}
	if (type == 1)
	{
		ptr1->num_elements = a + b.Listlength() - 1;
		node* scan_b = b.ptr1->first;
		node* scan = ptr1->first;
		long long scan_num = 1;
		while (scan_num != a)
		{
			scan = scan->next;
			scan_num = scan_num + 1;
		}
		if (scan == nullptr)
			return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义

		for (long long i = 1; i <= b.Listlength(); i++)
		{
			scan->element = scan_b->element;
			scan_b = scan_b->next;
			if (scan->next != nullptr)
				scan = scan->next;
			else
			{
				scan->next = new node;
				scan->next->prior = scan;
				scan->next->next = nullptr;
				scan = scan->next;
				ptr1->end = scan;
			}
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
LIST<Type> LIST<Type>::Substring(const long long a, const long long length) const
{
	LIST<Type> TEMP(2);
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】被提取子串的目标串不存在，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if (a <= 0)
	{
		cout << "\033[1;31m【错误】提供的位置序号小于等于0，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if ((type == 0 && a > ptr0->length) || (type == 1 && a > ptr1->num_elements))
	{
		cout << "\033[1;31m【错误】提供的位置序号大于被提取子串的目标串的长度，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if (a + length - 1 > Listlength())
	{
		cout << "\033[1;33m【警告】要提取的元素的范围超过被提取子串的目标串的合法范围\033[0m";
		cout << "\033[1;33m,提取的最后一个元素将被设置为被提取子串的目标串的最后一个元素\033[0m" << endl;
	}

	if (type == 0)
	{
		TEMP.Repair(type);
		long long end = 0;
		if (a + length - 1 > Listlength())
			end = Listlength();
		else
			end = a + length - 1;
		TEMP.Listexpand(length);

		for (long long i = a; i <= end; i++)
			TEMP.ListinsertR(TEMP.Listlength(), ptr0->elements[i - 1]);
		return TEMP;
	}
	if (type == 1)
	{
		TEMP.Repair(type);
		long long end = 0;
		if (a + length - 1 > Listlength())
			end = Listlength();
		else
			end = a + length - 1;
		node* scan = ptr1->first;
		long long scan_num = 1;
		while (scan_num != a)
		{
			scan = scan->next;
			scan_num = scan_num + 1;
		}
		if (scan == nullptr)
			return TEMP;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义

		for (long long i = a; i <= end; i++)
		{
			TEMP.ListinsertR(TEMP.Listlength(), scan->element);
			scan = scan->next;
		}
		return TEMP;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return TEMP;
}

template<typename Type>
bool LIST<Type>::Compare(const LIST& b) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (*this == b)
		return true;
	else
		return false;
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return false;
}

template<typename Type>
long long LIST<Type>::Char_erase(const Type& a)
{
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<long long>(-1);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return static_cast<long long>(0);
		}

		long long move_num = 0;
		long long loop_times = Listlength() - 1;
		for (long long i = 0; i <= loop_times; i++)
		{
			if (ptr0->elements[i] == a)
			{
				move_num = move_num + 1;
				ptr0->length = ptr0->length - 1;
				if (ptr0->length == 0)
					return move_num;
				else
					continue;
			}
			if (move_num == 0)
				continue;
			else
				ptr0->elements[i - move_num] = ptr0->elements[i];
		}
		Listshrink();
		return move_num;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return static_cast<long long>(0);
		}

		node* temp = ptr1->first;
		long long move_num = 0;
		long long loop_times = Listlength();
		for (long long i = 1; i <= loop_times; i++)
		{
			if (temp->element != a)
			{
				temp = temp->next;
				continue;
			}
			else
				move_num = move_num + 1;
			if (ptr1->num_elements == 1)//如果只有一个结点
			{
				ptr1->first->element = static_cast<Type>(0);
				ptr1->num_elements = ptr1->num_elements - 1;
				return move_num;
			}
			if (temp->prior == nullptr && temp->next != nullptr)//如果是第一个结点
			{
				node* temp_backup = temp->next;
				ptr1->first = temp->next;
				ptr1->first->prior = nullptr;
				ptr1->num_elements = ptr1->num_elements - 1;
				delete temp;
				temp = temp_backup;
				continue;
			}
			if (temp->prior != nullptr && temp->next == nullptr)//如果是最后一个结点
			{
				ptr1->end = temp->prior;
				ptr1->num_elements = ptr1->num_elements - 1;
				temp->prior->next = nullptr;
				delete temp;
				return move_num;
			}
			if (temp->prior != nullptr && temp->next != nullptr)
			{
				node* temp_backup = temp->next;
				ptr1->num_elements = ptr1->num_elements - 1;
				temp->prior->next = temp->next;
				temp->next->prior = temp->prior;
				delete temp;
				temp = temp_backup;
				continue;
			}
		}
		return move_num;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<long long>(-1);
}

template<typename Type>
long long LIST<Type>::Char_num(const Type& a) const
{
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////
	// 【警告】该函数无法处理需要两个字节存储空间的字符（如中文字符）//////////////////////////////////////////////////////////////

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<long long>(-1);
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return static_cast<long long>(0);
		}

		long long move_num = 0;
		for (long long i = 0; i <= Listlength() - 1; i++)
		{
			if (ptr0->elements[i] == a)
				move_num = move_num + 1;
		}
		return move_num;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return static_cast<long long>(0);
		}

		long long move_num = 0;
		node* scan = ptr1->first;
		for (long long i = 0; i <= Listlength() - 1; i++)
		{
			if (scan->element == a)
				move_num = move_num + 1;
			scan = scan->next;
		}
		return move_num;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<long long>(-1);
}

template<typename Type>
Type* LIST<Type>::Type_array(const bool help) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		Type* temp = new Type[Listlength()];
		for (long long i = 1; i <= Listlength(); i++)
			temp[i - 1] = ptr0->elements[i - 1];
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量。请配合Listlength()函数\033[0m";
			cout << "\033[1;33m使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		Type* temp = new Type[Listlength()];
		node* scan = ptr1->first;
		for (long long i = 1; i <= Listlength(); i++)
		{
			temp[i - 1] = scan->element;
			scan = scan->next;
		}
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量。请配合Listlength()函数\033[0m";
			cout << "\033[1;33m使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return nullptr;
}

template<typename Type>
Type* LIST<Type>::Type_array(const long long a, const long long b, const bool help) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (a <= 0 || a > Listlength() || b <= 0 || b > Listlength() || a > b)
	{
		cout << "\033[1;31m【错误】输入的待转换的元素序号范围有错误，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	long long length = b - a + 1;
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		long long offset = a - 1;
		Type* temp = new Type[length];
		for (long long i = 1; i <= length; i++)
			temp[i - 1] = ptr0->elements[offset + i - 1];
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量。请配合Listlength()函数\033[0m";
			cout << "\033[1;33m使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		Type* temp = new Type[length];
		long long scan_num = 1;
		node* scan = ptr1->first;
		while (scan_num < a)
		{
			scan_num = scan_num + 1;
			scan = scan->next;
		}
		for (long long i = 1; i <= length; i++)
		{
			temp[i - 1] = scan->element;
			scan = scan->next;
		}
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量。请配合Listlength()函数\033[0m";
			cout << "\033[1;33m使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return nullptr;
}

template<typename Type>
char* LIST<Type>::Char_array(const bool help) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		char* temp = new char[Listlength() + 1];
		for (long long i = 1; i <= Listlength(); i++)
			temp[i - 1] = static_cast<char>(ptr0->elements[i - 1]);
		temp[Listlength()] = '\0';
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量+1(最后一位是'\\0'字符)。\033[0m";
			cout << "\033[1;33m请配合Listlength()函数使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		char* temp = new char[Listlength() + 1];
		node* scan = ptr1->first;
		for (long long i = 1; i <= Listlength(); i++)
		{
			temp[i - 1] = static_cast<char>(scan->element);
			scan = scan->next;
		}
		temp[Listlength()] = '\0';
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量+1(最后一位是'\\0'字符)。\033[0m";
			cout << "\033[1;33m请配合Listlength()函数使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return nullptr;
}

template<typename Type>
char* LIST<Type>::Char_array(const long long a, const long long b, const bool help) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	if (a <= 0 || a > Listlength() || b <= 0 || b > Listlength() || a > b)
	{
		cout << "\033[1;31m【错误】输入的待转换的元素序号范围有错误，无法执行任何操作\033[0m" << endl;
		return nullptr;
	}
	long long length = b - a + 1;
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		long long offset = a - 1;
		char* temp = new char[length + 1];
		for (long long i = 1; i <= length; i++)
			temp[i - 1] = static_cast<char>(ptr0->elements[offset + i - 1]);
		temp[length] = '\0';
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量+1(最后一位是'\\0'字符)。\033[0m";
			cout << "\033[1;33m请配合Listlength()函数使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】串中没有任何元素\033[0m" << endl;
			return nullptr;
		}

		char* temp = new char[length + 1];
		long long scan_num = 1;
		node* scan = ptr1->first;
		while (scan_num < a)
		{
			scan_num = scan_num + 1;
			scan = scan->next;
		}
		for (long long i = 1; i <= length; i++)
		{
			temp[i - 1] = static_cast<char>(scan->element);
			scan = scan->next;
		}
		temp[length] = '\0';
		if (help == true)
		{
			cout << "\033[1;33m【警告】返回的数组的长度等于串中元素的数量+1(最后一位是'\\0'字符)。\033[0m";
			cout << "\033[1;33m请配合Listlength()函数使用输出的数组，以避免造成数组越界的严重内存错误\033[0m" << endl;
		}
		return temp;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return nullptr;
}

template<typename Type>
long long LIST<Type>::K_M_P(const LIST& a, const long long start, const long long end) const
{
	long long length = end - start + 1;
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】串不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】模式串不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】串的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (a.type != 0 && a.type != 1)
	{
		cout << "\033[1;31m【错误】模式串的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (length <= 0)
	{
		cout << "\033[1;31m【错误】输入的待查找区间的起止位置错误\033[0m" << endl;
		return -1;
	}
	if (a.Listlength() == 0)
	{
		cout << "\033[1;31m【错误】模式串为空，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (start <= 0 || start > Listlength())
	{
		cout << "\033[1;31m【错误】输入的查找起始位置错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (end <= 0 || end > Listlength())
	{
		cout << "\033[1;31m【错误】输入的查找终止位置错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (length < a.Listlength())
		return -1;

	//生成next数组(修正后的)
	Type* transform = a.Type_array(false);
	long long* NEXT = new long long[a.Listlength()];
	long long i = 1;
	long long j = 0;
	NEXT[0] = 0;
	while (i < a.Listlength())
	{
		if (j == 0 || transform[i - 1] == transform[j - 1])
		{
			i = i + 1;
			j = j + 1;
			if (transform[i - 1] != transform[j - 1])
				NEXT[i - 1] = j;
			else
				NEXT[i - 1] = NEXT[j - 1];
		}
		else
			j = NEXT[j - 1];
	}

	//KMP算法
	//假如目标串长度为1000，模式串长度为3，目标串的前三个字符与模式串相同
	//   那么目标串只扫描前三个，即扫描到第一个匹配的位置以后就提前结束循环
	i = start;
	j = 1;
	if (type == 0)
	{
		while (i <= end && j <= a.Listlength())
		{
			if (j == 0 || ptr0->elements[i - 1] == transform[j - 1])
			{
				i = i + 1;
				j = j + 1;
			}
			else
				j = NEXT[j - 1];
		}
		delete[] transform;
		delete[] NEXT;
		if (j > a.Listlength())
			return i - a.Listlength();
		else
			return -1;
	}
	if (type == 1)
	{
		node* i_ptr = ptr1->first;
		long long i_count = 1;
		while (i_count < start)
		{
			i_count = i_count + 1;
			i_ptr = i_ptr->next;
		}

		while (i <= end && j <= a.Listlength())
		{
			if (j == 0 || i_ptr->element == transform[j - 1])
			{
				i = i + 1;
				i_ptr = i_ptr->next;
				j = j + 1;
			}
			else
				j = NEXT[j - 1];
		}
		delete[] transform;
		delete[] NEXT;
		if (j > a.Listlength())
			return i - a.Listlength();
		else
			return -1;
	}
	delete[] transform;
	delete[] NEXT;
	return -1;
}

template<typename Type>
void String_swap(LIST<Type>& a, LIST<Type>& b)
{
	int type_temp = a.type;
	a.type = b.type;
	b.type = type_temp;

	struct LIST<Type>::linear* PTR0 = a.ptr0;
	a.ptr0 = b.ptr0;
	b.ptr0 = PTR0;

	struct LIST<Type>::chain_manage* PTR1 = a.ptr1;
	a.ptr1 = b.ptr1;
	b.ptr1 = PTR1;

	return;
}

template<typename Type>
void String_sort(LIST<Type>** a, const long long b)
{
	//【注意】结构数组的长度b必须正确。本函数无法判断输入值b是否越界。若b的范围错误，函数会发生未知错误
	if (a == nullptr)
	{
		cout << "\033[1;31m【错误】字符串数组不存在\033[0m" << endl;
		return;
	}
	for (long long i = 1; i <= b; i++)
	{
		if (a[i - 1] == nullptr)
		{
			cout << "\033[1;31m【错误】字符串数组中有字符串不存在\033[0m" << endl;
			return;
		}
		if (a[i - 1]->Gettype() != 0)
		{
			if (a[i - 1]->Gettype() == 1)
			{
				cout << "\033[1;31m【错误】字符串数组中存在存储类型是链表的字符串。字符串排序函数需要对字符串进行\033[0m" << endl;
				cout << "\033[1;31m【错误】随机读取，请不要使用链表格式，这会极大减慢程序的运行速度。本函数即将退出\033[0m" << endl;
				return;
			}
			else
			{
				cout << "\033[1;31m【错误】字符串数组中存在类型错误的字符串。本函数无法进行任何操作，并将退出\033[0m" << endl;
				return;
			}
		}
	}
	if (b == 1)
		return;

	struct stack_sort
	{
		long long low;
		long long high;
		long long num;
		struct stack_sort* next;
	};
	stack_sort* stack_manage = new stack_sort;
	stack_manage->low = 1;
	stack_manage->high = b;
	stack_manage->num = 1;
	stack_manage->next = nullptr;

	do
	{
		//一次排序完成后字符串被分为三部分：low_end<=小于枢轴<=low_mid-1      low_mid<=等于枢轴<=high_mid=scan
		//high_mid+1<=大于枢轴<=high_end

		long long low_end = stack_manage->low;
		long long high_end = stack_manage->high;
		long long num = stack_manage->num;
		stack_sort* stack_delete = stack_manage;
		stack_manage = stack_manage->next;
		delete stack_delete;

		bool pivotkey_overrange = false;
		long long pivotkey = 0;
		if (a[low_end - 1]->Listlength() < num)
			pivotkey_overrange = true;
		else
			pivotkey = static_cast<long long>(a[low_end - 1]->Getelement(num));
		long long low_mid = low_end;
		long long high_mid = high_end;
		long long scan = low_end + 1;

		while (scan <= high_mid)
		{
			bool scan_key_overrange = false;
			long long scan_key = 0;
			if (a[scan - 1]->Listlength() < num)
				scan_key_overrange = true;
			else
				scan_key = static_cast<long long>(a[scan - 1]->Getelement(num));

			if ((scan_key_overrange == true && pivotkey_overrange == false) ||
				(scan_key_overrange == false && pivotkey_overrange == false && scan_key < pivotkey))
			{
				//待判断的关键字小于枢轴关键字
				LIST<char>* temp = a[scan - 1];
				a[scan - 1] = a[low_mid - 1];
				a[low_mid - 1] = temp;
				low_mid = low_mid + 1;
				scan = scan + 1;
			}
			else if ((scan_key_overrange == true && pivotkey_overrange == true) ||
				(scan_key_overrange == false && pivotkey_overrange == false && scan_key == pivotkey))
				scan = scan + 1;//待判断的关键字等于枢轴关键字
			else
			{
				//待判断的关键字大于枢轴关键字
				LIST<char>* temp = a[scan - 1];
				a[scan - 1] = a[high_mid - 1];
				a[high_mid - 1] = temp;
				high_mid = high_mid - 1;
			}
		}

		if (low_end < low_mid - 1)
		{
			stack_sort* stack_new = new stack_sort;
			stack_new->low = low_end;
			stack_new->high = low_mid - 1;
			stack_new->num = num;
			stack_new->next = stack_manage;
			stack_manage = stack_new;
		}
		if (pivotkey_overrange == false)
		{
			stack_sort* stack_new = new stack_sort;
			stack_new->low = low_mid;
			stack_new->high = high_mid;
			stack_new->num = num + 1;
			stack_new->next = stack_manage;
			stack_manage = stack_new;
		}
		if (high_mid + 1 < high_end)
		{
			stack_sort* stack_new = new stack_sort;
			stack_new->low = high_mid + 1;
			stack_new->high = high_end;
			stack_new->num = num;
			stack_new->next = stack_manage;
			stack_manage = stack_new;
		}
	} while (stack_manage != nullptr);

	return;
}

template<typename Type>
bool Same_TF(const LIST<Type>& a, const long long a_start, const long long a_end, const LIST<Type>& b,
	const long long b_start, const long long b_end)
{
	if (a.type != 0 && a.type != 1)
	{
		cout << "\033[1;31m【错误】字符串a的类型有错误\033[0m" << endl;
		return false;
	}
	if (b.type != 0 && b.type != 1)
	{
		cout << "\033[1;31m【错误】字符串b的类型有错误\033[0m" << endl;
		return false;
	}
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】字符串a不存在\033[0m" << endl;
		return false;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】字符串b不存在\033[0m" << endl;
		return false;
	}
	if (a_end < a_start || b_end < b_start || a_start < 0 || b_start < 0 ||
		a_end > a.Listlength() - 1 || b_end > b.Listlength() - 1 || a_end - a_start != b_end - b_start)
	{
		cout << "\033[1;31m【错误】输入的起止区间有错误\033[0m" << endl;
		return false;
	}

	struct LIST<Type>::node* a_scan = nullptr;
	struct LIST<Type>::node* b_scan = nullptr;
	if (a.Gettype() == 1)
	{
		long long a_count = 0;
		a_scan = a.ptr1->first;
		while (a_count < a_start)
		{
			a_count = a_count + 1;
			a_scan = a_scan->next;
		}
	}
	if (b.Gettype() == 1)
	{
		long long b_count = 0;
		b_scan = b.ptr1->first;
		while (b_count < b_start)
		{
			b_count = b_count + 1;
			b_scan = b_scan->next;
		}
	}

	for (long long i = 0; i <= a_end - a_start; i++)
	{
		Type a_element = static_cast<Type>(0);
		Type b_element = static_cast<Type>(0);
		if (a.Gettype() == 0)
			a_element = a.ptr0->elements[i + a_start];
		else
		{
			a_element = a_scan->element;//请忽略“取消对NULL指针的引用“，属于误报
			a_scan = a_scan->next;
		}
		if (b.Gettype() == 0)
			b_element = b.ptr0->elements[i + b_start];
		else
		{
			b_element = b_scan->element;//请忽略“取消对NULL指针的引用“，属于误报
			b_scan = b_scan->next;
		}

		if (a_element != b_element)
			return false;
	}
	return true;
}

template<typename Type>
long long LIST<Type>::Seq_search(const Type a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		Type backup = ptr0->elements[Listlength() - 1];
		ptr0->elements[Listlength() - 1] = a;
		long long i = 1;
		while (ptr0->elements[i - 1] != a)
			i = i + 1;
		ptr0->elements[Listlength() - 1] = backup;
		if (i == Listlength() && backup != a)
			return -1;
		return i;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		Type backup = ptr1->end->element;
		ptr1->end->element = a;
		long long i = 1;
		node* scan = ptr1->first;
		while (scan->element != a)
		{
			i = i + 1;
			scan = scan->next;
		}
		ptr1->end->element = backup;
		if (i == Listlength() && backup != a)
			return -1;
		return i;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return -1;
}

template<typename Type>
LIST<long long> LIST<Type>::Seq_search_all(const Type a) const
{
	LIST<long long> TEMP(2);
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return TEMP;
	}
	if (type == 0)
	{
		TEMP.Repair(type);
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return TEMP;
		}

		for (long long i = 1; i <= Listlength(); i++)
		{
			if (ptr0->elements[i - 1] == a)
				TEMP.ListinsertR(TEMP.Listlength(), i);
		}
		return TEMP;
	}
	if (type == 1)
	{
		TEMP.Repair(type);
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return TEMP;
		}

		node* scan = ptr1->first;
		for (long long i = 1; i <= Listlength(); i++)
		{
			if (scan->element == a)
				TEMP.ListinsertR(TEMP.Listlength(), i);
			scan = scan->next;
		}
		return TEMP;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return TEMP;
}

template<typename Type>
long long LIST<Type>::Bin_search(const Type a)
{
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	if (Sort_TF() == false)
	{
		cout << "\033[1;31m【错误】表中的元素并非有序\033[0m" << endl;
		return -1;
	}

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		long long low = 1;
		long long high = Listlength();
		while (low <= high)
		{
			long long mid = (low + high) / 2;
			if (ptr0->elements[mid - 1] == a)
				return mid;
			else
			{
				if (ptr0->elements[mid - 1] > a)
					high = mid - 1;
				else
					low = mid + 1;
			}
		}
		return -1;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		return Seq_search(a);//对链表使用本函数没有意义
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return -1;
}

template<typename Type>
long long LIST<Type>::Fibo_search(const Type a)
{
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	if (Sort_TF() == false)
	{
		cout << "\033[1;31m【错误】表中的元素并非有序\033[0m" << endl;
		return -1;
	}

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		LIST<long long> FIBO(3);
		FIBO.ListinsertR(FIBO.Listlength(), 0);
		FIBO.ListinsertR(FIBO.Listlength(), 1);
		long long FIBO_MAX = 1;
		while (FIBO_MAX <= Listlength())
		{
			FIBO_MAX = FIBO[FIBO.Listlength() - 2] + FIBO[FIBO.Listlength() - 1];
			FIBO.ListinsertR(FIBO.Listlength(), FIBO_MAX);
		}
		
		long long start = 1;
		long long end = Listlength();
		long long u = FIBO.Listlength();
		while (start <= end)
		{
			long long length = end - start + 1;
			while (FIBO[u - 2] > length)
				u = u - 1;
			long long pos = FIBO[u - 2] + start - 1;
			if (ptr0->elements[pos - 1] == a)
				return pos;
			if (ptr0->elements[pos - 1] > a)
				end = pos - 1;
			else
				start = pos + 1;
		}
		return -1;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		return Seq_search(a);//对链表使用本函数没有意义
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return -1;
}

template<typename Type>
long long LIST<Type>::Interp_search(const Type a)
{
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	//此函数可能需要调用seq_search函数，所以不可以加const
	if (Sort_TF() == false)
	{
		cout << "\033[1;31m【错误】表中的元素并非有序\033[0m" << endl;
		return -1;
	}

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		Type min = ptr0->elements[0];
		Type max = ptr0->elements[Listlength() - 1];
		long double min_ld = static_cast<long double>(ptr0->elements[0]);
		long double max_ld = static_cast<long double>(ptr0->elements[Listlength() - 1]);
		if (min >= a)
		{
			if (min == a)
				return 1;
			else
				return -1;
		}//待查找的数一定大于序列的最小值
		if (max <= a)
		{
			if (max == a)
				return Listlength();
			else
				return -1;
		}//待查找的数一定小于序列的最大值
		if (min == max)
			return -1;//序列的最大值一定不等于序列的最小值
		long double pos_ld = (static_cast<long double>(a) - min_ld) / (max_ld - min_ld) * Listlength();
		long long pos = static_cast<long long>(pos_ld);
		if (pos > Listlength())
			pos = Listlength();
		if (pos <= 0)
			pos = 1;//pos的值一定在合法区间内
		if (ptr0->elements[pos - 1] == a)
			return pos;
		if (ptr0->elements[pos - 1] < a)
		{
			pos = pos + 1;
			if (pos > Listlength())
				return -1;
			//此时表中最后一个元素一定不等于(且大于)待查找的元素
			
			Type backup = ptr0->elements[Listlength() - 1];
			ptr0->elements[Listlength() - 1] = a;
			while (ptr0->elements[pos - 1] != a)
				pos = pos + 1;
			ptr0->elements[Listlength() - 1] = backup;
			if (pos == Listlength())
				return -1;
			return pos;
		}
		else
		{
			pos = pos - 1;
			if (pos <= 0)
				return -1;
			//此时表中第一个元素一定不等于(且小于)待查找的元素

			Type backup = ptr0->elements[0];
			ptr0->elements[0] = a;
			while (ptr0->elements[pos - 1] != a)
				pos = pos - 1;
			ptr0->elements[0] = backup;
			if (pos == 1)
				return -1;
			return pos;
		}
		//此处不要加return，否则visual studio会弹出"无法访问的代码"警告
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return -1;
		}

		return Seq_search(a);//对链表使用本函数没有意义
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return -1;
}

template<typename Type>
long long LIST<Type>::STT_search(const Type a, const LIST<long double>& WEIGHT) const
{
	//如果参数列表使用    const LIST& WEIGHT    或者    const LIST<Type>& WEIGHT    ，那么下面这条语句
	//cout << WEIGHT.ptr0->elements[0] << endl;    可以通过编译。如果使用    const LIST<long double>& WEIGHT
	//，那么该语句就不可以通过编译。由于本函数的参数列表必须使用    const LIST<long double>& WEIGHT    ，所以本函数内
	//无法访问WEIGHT对象的private成员。无论WEIGHT前加不加const都是这样。
	if (Sort_TF() == false)
	{
		cout << "\033[1;31m【错误】表中的元素并非有序\033[0m" << endl;
		return -1;
	}
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (WEIGHT.Listlength() == -1)
	{
		//Listlength函数对一切表中有错误的情况均返回-1
		cout << "\033[1;31m【错误】权重表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (WEIGHT.Gettype() != 0 && WEIGHT.Gettype() != 1)
	{
		cout << "\033[1;31m【错误】权重表的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (Listlength() == 0)
	{
		cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
		return -1;
	}
	if (WEIGHT.Listlength() == 0)
	{
		cout << "\033[1;31m【错误】权重表中没有任何元素\033[0m" << endl;
		return -1;
	}
	if (WEIGHT.Listlength() != Listlength())
	{
		cout << "\033[1;31m【错误】权重表的长度和待查找的表的长度不同，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (WEIGHT.Gettype() == 1)
	{
		cout << "\033[1;33m【警告】函数需要对权重表进行随机读取，所以请不要提供链表形式的权重表，否则会极大降低运行速度\033[0m" << endl;
		cout << "\033[1;33m【警告】为了加快速度，函数内部将新建一个临时线性表，并用该线性表存储权重表\033[0m" << endl;
	}

	//计算累计权值和
	LIST<long double> sum_weight(3);
	sum_weight.Listexpand(Listlength());
	if (WEIGHT.Gettype() == 0)
	{
		sum_weight.ListinsertR(1, WEIGHT[0]);
		for (long long i = 2; i <= Listlength(); i++)
			sum_weight.ListinsertR(i - 1, sum_weight[i - 2] + WEIGHT[i - 1]);
	}
	LIST<long double> WEIGHT_A(4);
	if (WEIGHT.Gettype() == 1)
	{
		WEIGHT_A = WEIGHT;
		WEIGHT_A.Typeswitch(0);
		sum_weight.ListinsertR(1, WEIGHT_A[0]);
		for (long long i = 2; i <= Listlength(); i++)
			sum_weight.ListinsertR(i - 1, sum_weight[i - 2] + WEIGHT_A[i - 1]);
	}

	//构建初始树
	//struct TREE<long double>::bitree*  无法通过编译，struct TREE<Type>::bitree*  可以通过编译但是不能使用。
	//所以这里必须手动定义二叉树结点
	struct bitree
	{
		Type data;//元素的值
		long double weight;//权重
		long double sw_weight;//权重和
		long long number;//元素的序号
		struct bitree* parent;
		struct bitree* lchild;
		struct bitree* rchild;
	};
	struct tree_generate
	{
		struct bitree* treeptr;
		struct tree_generate* prior;
		struct tree_generate* next;
	};
	struct stack_generate
	{
		struct bitree* tree_parent;//从栈指向的区间中选出根结点后，该根结点的parent域应当指向的结点
		int LR;//从栈指向的区间中选出根结点后，该根结点是双亲的左孩子（-1）或右孩子（1）或该根结点没有双亲结点（0）
		long double start_weight;//链的前一个结点的累计权值和（sw_l-1）
		struct tree_generate* tree_start;
		struct tree_generate* tree_end;
		struct stack_generate* next;
	};
	stack_generate* stack_head = new stack_generate;
	stack_head->tree_parent = nullptr;
	stack_head->LR = 0;
	stack_head->start_weight = 0;
	stack_head->next = nullptr;
	stack_head->tree_start = new tree_generate;
	stack_head->tree_end = stack_head->tree_start;
	tree_generate* tree_head = stack_head->tree_start;
	tree_generate* tree_end = tree_head;
	tree_end->next = nullptr;
	tree_end->prior = nullptr;
	tree_end->treeptr = new bitree;
	bitree* bitree_ptr = tree_end->treeptr;
	node* this_scan = nullptr;
	if (type == 0)
		bitree_ptr->data = ptr0->elements[0];
	else
	{
		this_scan = ptr1->first;
		bitree_ptr->data = this_scan->element;
	}
	if (WEIGHT.Gettype() == 0)
		bitree_ptr->weight = WEIGHT[0];
	else
		bitree_ptr->weight = WEIGHT_A[0];
	bitree_ptr->sw_weight = sum_weight[0];
	bitree_ptr->number = 1;
	bitree_ptr->lchild = nullptr;
	bitree_ptr->rchild = nullptr;
	bitree_ptr->parent = nullptr;
	for (long long i = 2; i <= sum_weight.Listlength(); i++)
	{
		tree_end->next = new tree_generate;
		tree_end->next->next = nullptr;
		tree_end->next->prior = tree_end;
		tree_end->next->treeptr = new bitree;
		tree_end = tree_end->next;
		bitree_ptr = tree_end->treeptr;
		if (type == 0)
			bitree_ptr->data = ptr0->elements[i - 1];
		else
		{
			this_scan = this_scan->next;
			bitree_ptr->data = this_scan->element;
		}
		if (WEIGHT.Gettype() == 0)
			bitree_ptr->weight = WEIGHT[i - 1];
		else
			bitree_ptr->weight = WEIGHT_A[i - 1];
		bitree_ptr->sw_weight = sum_weight[i - 1];
		bitree_ptr->number = i;
		bitree_ptr->lchild = nullptr;
		bitree_ptr->rchild = nullptr;
		bitree_ptr->parent = nullptr;
	}
	stack_head->tree_end = tree_end;

	//构建次优查找树
	bitree* tree_root = nullptr;//整个二叉树的根结点
	do
	{
		//备份栈顶元素的内容，并删除栈顶元素
		bitree* tree_parent_x = stack_head->tree_parent;
		int LR_x = stack_head->LR;
		long double start_weight_x = stack_head->start_weight;
		tree_generate* tree_start_x = stack_head->tree_start;
		tree_generate* tree_end_x = stack_head->tree_end;
		stack_generate* stack_delete = stack_head;
		stack_head = stack_head->next;
		delete stack_delete;

		//选出根结点
		long double sw_min = tree_start_x->treeptr->sw_weight;
		long double sw_max = tree_end_x->treeptr->sw_weight;
		tree_generate* scan = tree_start_x;
		tree_generate* best = scan;//目前最小的delta-P值对应的结点
		long double best_weight = sw_max - sw_min;//目前最小的delta-P值
		while (scan != nullptr)
		{
			long double prior = start_weight_x;//当前结点的前一个结点的累计权值
			if (scan->prior != nullptr)
				prior = scan->prior->treeptr->sw_weight;
			long double weight = sw_max + start_weight_x - scan->treeptr->sw_weight - prior;//当前结点的delta-P值
			if (weight < 0)
				weight = -weight;
			if (weight < best_weight)
			{
				best_weight = weight;
				best = scan;
			}
			scan = scan->next;
		}
		
		//检查被选为根的关键字的权值是否比与它相邻的关键字的权值小
		if (best->prior == nullptr)
		{
			if (best->next != nullptr)//左为空，右非空
			{
				if (best->next->treeptr->weight > best->treeptr->weight)
					best = best->next;
			}
		}
		else
		{
			if (best->next == nullptr)//左非空，右为空
			{
				if (best->prior->treeptr->weight > best->treeptr->weight)
					best = best->prior;
			}
			else
			{
				//三者中取最大值，分成两组比较
				tree_generate* sub = best->next;
				if (best->prior->treeptr->weight > best->treeptr->weight)
					best = best->prior;
				if (sub->treeptr->weight > best->treeptr->weight)
					best = sub;
			}
		}

		//压栈
		if (best->next != nullptr)//右子树先入栈
		{
			stack_generate* stack_new = new stack_generate;
			stack_new->tree_parent = best->treeptr;
			stack_new->LR = 1;
			stack_new->start_weight = best->treeptr->sw_weight;
			stack_new->tree_start = best->next;
			stack_new->tree_end = tree_end_x;
			stack_new->next = stack_head;
			stack_head = stack_new;
		}
		if (best->prior != nullptr)//左子树后入栈
		{
			stack_generate* stack_new = new stack_generate;
			stack_new->tree_parent = best->treeptr;
			stack_new->LR = -1;
			stack_new->start_weight = start_weight_x;
			stack_new->tree_start = tree_start_x;
			stack_new->tree_end = best->prior;
			stack_new->next = stack_head;
			stack_head = stack_new;
		}
		//断开连接
		if (best->prior != nullptr)
			best->prior->next = nullptr;
		if (best->next != nullptr)
			best->next->prior = nullptr;
		//重构二叉树
		if (LR_x != 0)
		{
			best->treeptr->parent = tree_parent_x;
			if (LR_x == -1)
				tree_parent_x->lchild = best->treeptr;
			if (LR_x == 1)
				tree_parent_x->rchild = best->treeptr;
		}
		else
			tree_root = best->treeptr;
		//卸载tree_generate结点
		delete best;

	} while (stack_head != nullptr);

	//查找
	long long find_number = -1;
	bitree* tree_search = tree_root;
	while (tree_search != nullptr)
	{
		if (tree_search->data == a)
		{
			find_number = tree_search->number;
			break;
		}
		if (tree_search->data > a)
			tree_search = tree_search->lchild;
		else
			tree_search = tree_search->rchild;
	}

	//二叉树析构函数
	struct tree_delete
	{
		struct bitree* treeptr;
		struct tree_delete* next;
	};
	tree_delete* tree_stack_top = new tree_delete;
	tree_stack_top->treeptr = tree_root;
	tree_stack_top->next = nullptr;
	while (tree_stack_top != nullptr)
	{
		tree_delete* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr)//右子树先入栈
		{
			tree_delete* tree_stack_R = new tree_delete;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr)//左子树后入栈
		{
			tree_delete* tree_stack_L = new tree_delete;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
		delete tree_stack_backup;
	}
	
	return find_number;
}

template<typename Type>
long long LIST<Type>::AVL_search(const Type a) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (Listlength() == 0)
	{
		cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
		return -1;
	}

	//初始化AVL树
	struct bitree
	{
		Type data;
		long long BF;
		long long number;
		struct bitree* parent;
		struct bitree* lchild;
		struct bitree* rchild;
	};
	node* scan = nullptr;
	if (type == 1)
		scan = ptr1->first;
	bitree* root = new bitree;
	if (type == 0)
		root->data = ptr0->elements[0];
	else
	{
		root->data = scan->element;
		scan = scan->next;
	}
	root->BF = 0;
	root->number = 1;
	root->parent = nullptr;
	root->lchild = nullptr;
	root->rchild = nullptr;

	//构建AVL树
	for (long long i = 2; i <= Listlength(); i++)
	{
		//查找该元素是否存在
		Type element = 0;
		if (type == 0)
			element = ptr0->elements[i - 1];
		else
		{
			element = scan->element;
			scan = scan->next;
		}
		bitree* tree_search_next = root;
		bitree* tree_search = nullptr;
		bool element_exist = false;
		while (tree_search_next != nullptr)
		{
			if (tree_search_next->data == element)
			{
				element_exist = true;
				break;
			}
			if (tree_search_next->data > element)
			{
				tree_search = tree_search_next;
				tree_search_next = tree_search_next->lchild;
			}
			else
			{
				tree_search = tree_search_next;
				tree_search_next = tree_search_next->rchild;
			}
		}
		if (element_exist == true)
			continue;

		//插入不存在的该元素
		int insert_direction = 0;
		if (tree_search->data > element)
		{
			insert_direction = -1;//向左子树插入
			tree_search->lchild = new bitree;
			tree_search->lchild->BF = 0;
			tree_search->lchild->number = i;
			tree_search->lchild->data = element;
			tree_search->lchild->lchild = nullptr;
			tree_search->lchild->parent = tree_search;
			tree_search->lchild->rchild = nullptr;
		}
		else
		{
			insert_direction = 1;//向右子树插入
			tree_search->rchild = new bitree;
			tree_search->rchild->BF = 0;
			tree_search->rchild->number = i;
			tree_search->rchild->data = element;
			tree_search->rchild->lchild = nullptr;
			tree_search->rchild->parent = tree_search;
			tree_search->rchild->rchild = nullptr;
		}

		//校验并更新BF值
		int rotate = 0;
		do
		{
			if (insert_direction == -1)
				tree_search->BF = tree_search->BF + 1;//向左子树插入
			else
				tree_search->BF = tree_search->BF - 1;//向右子树插入

			if (tree_search->BF == 0)
				break;//+-1后BF变为0，说明插入的结点对BF值造成的影响已结束，不需要再修改tree_search的双亲的BF
			if (tree_search->BF == 2)
			{
				if (tree_search->lchild->BF == 1)
					rotate = 1;//单向右旋平衡处理
				if (tree_search->lchild->BF == -1)
					rotate = 3;//双向旋转（先左后右）平衡处理
				break;
			}
			if (tree_search->BF == -2)
			{
				if (tree_search->rchild->BF == -1)
					rotate = 2;//单向左旋平衡处理
				if (tree_search->rchild->BF == 1)
					rotate = 4;//双向旋转（先右后左）平衡处理
				break;
			}
			//若tree_search->BF为+-1，则继续循环
			if (tree_search->parent != nullptr)
			{
				if (tree_search->parent->lchild == tree_search)
					insert_direction = -1;
				else
					insert_direction = 1;
				tree_search = tree_search->parent;
			}
			else
				break;
		} while (true);
		if (rotate == 0)
			continue;

		//旋转
		if (rotate == 1)//单向右旋平衡处理
		{
			bitree* B = tree_search->lchild;
			bitree* B_R = tree_search->lchild->rchild;
			if (tree_search->parent != nullptr)
			{
				if (tree_search->parent->lchild == tree_search)
					tree_search->parent->lchild = B;
				else
					tree_search->parent->rchild = B;
				B->parent = tree_search->parent;
			}
			else
			{
				root = B;
				B->parent = nullptr;
			}
			B->rchild = tree_search;
			tree_search->parent = B;
			if (B_R != nullptr)
				B_R->parent = tree_search;
			tree_search->lchild = B_R;

			B->BF = 0;
			tree_search->BF = 0;
			continue;
		}
		if (rotate == 2)//单向左旋平衡处理
		{
			bitree* B = tree_search->rchild;
			bitree* B_L = tree_search->rchild->lchild;
			if (tree_search->parent != nullptr)
			{
				if (tree_search->parent->lchild == tree_search)
					tree_search->parent->lchild = B;
				else
					tree_search->parent->rchild = B;
				B->parent = tree_search->parent;
			}
			else
			{
				root = B;
				B->parent = nullptr;
			}
			B->lchild = tree_search;
			tree_search->parent = B;
			if (B_L != nullptr)
				B_L->parent = tree_search;
			tree_search->rchild = B_L;

			B->BF = 0;
			tree_search->BF = 0;
			continue;
		}
		if (rotate == 3)//双向旋转（先左后右）平衡处理
		{
			bitree* B = tree_search->lchild;
			bitree* C = tree_search->lchild->rchild;
			bitree* C_L = C->lchild;
			bitree* C_R = C->rchild;
			if (tree_search->parent != nullptr)
			{
				if (tree_search->parent->lchild == tree_search)
					tree_search->parent->lchild = C;
				else
					tree_search->parent->rchild = C;
				C->parent = tree_search->parent;
			}
			else
			{
				root = C;
				C->parent = nullptr;
			}
			C->lchild = B;
			B->parent = C;
			C->rchild = tree_search;
			tree_search->parent = C;
			if (C_L != nullptr)
				C_L->parent = B;
			B->rchild = C_L;
			if (C_R != nullptr)
				C_R->parent = tree_search;
			tree_search->lchild = C_R;

			if (C->BF == -1)
			{
				tree_search->BF = 0;
				B->BF = 1;
			}
			if (C->BF == 0)
			{
				tree_search->BF = 0;
				B->BF = 0;
			}
			if (C->BF == 1)
			{
				tree_search->BF = -1;
				B->BF = 0;
			}
			C->BF = 0;
			continue;
		}
		if (rotate == 4)//双向旋转（先右后左）平衡处理
		{
			bitree* B = tree_search->rchild;
			bitree* C = tree_search->rchild->lchild;
			bitree* C_L = C->lchild;
			bitree* C_R = C->rchild;
			if (tree_search->parent != nullptr)
			{
				if (tree_search->parent->lchild == tree_search)
					tree_search->parent->lchild = C;
				else
					tree_search->parent->rchild = C;
				C->parent = tree_search->parent;
			}
			else
			{
				root = C;
				C->parent = nullptr;
			}
			C->lchild = tree_search;
			tree_search->parent = C;
			C->rchild = B;
			B->parent = C;
			if (C_L != nullptr)
				C_L->parent = tree_search;
			tree_search->rchild = C_L;
			if (C_R != nullptr)
				C_R->parent = B;
			B->lchild = C_R;

			if (C->BF == -1)
			{
				tree_search->BF = 1;
				B->BF = 0;
			}
			if (C->BF == 0)
			{
				tree_search->BF = 0;
				B->BF = 0;
			}
			if (C->BF == 1)
			{
				tree_search->BF = 0;
				B->BF = -1;
			}
			C->BF = 0;
		}
	}

	//查找
	long long find_number = -1;
	bitree* search = root;
	while (search != nullptr)
	{
		if (search->data == a)
		{
			find_number = search->number;
			break;
		}
		if (search->data > a)
			search = search->lchild;
		else
			search = search->rchild;
	}

	//二叉树析构函数
	struct tree_delete
	{
		struct bitree* treeptr;
		struct tree_delete* next;
	};
	tree_delete* tree_stack_top = new tree_delete;
	tree_stack_top->treeptr = root;
	tree_stack_top->next = nullptr;
	while (tree_stack_top != nullptr)
	{
		tree_delete* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr)//右子树先入栈
		{
			tree_delete* tree_stack_R = new tree_delete;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr)//左子树后入栈
		{
			tree_delete* tree_stack_L = new tree_delete;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
		delete tree_stack_backup;
	}

	return find_number;
}

template<typename Type>
long long LIST<Type>::B_TREE_search(const Type a, const long long m) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (Listlength() == 0)
	{
		cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
		return -1;
	}
	if (m < 2)
	{
		cout << "\033[1;31m【错误】B树的阶不能小于2\033[0m" << endl;
		return -1;
	}
	if (m == 2)
		return AVL_search(a);//m=2时，结点无法分裂为左右两个结点（因为分裂后的左结点一定为空结点）。最终构建的B树是一棵（一根）只有
	//右子树的（木棍）。所以为了提高效率，这里调用平衡二叉树查找函数。

	//初始化B树
	struct B_node
	{
		long long keynum;//结点内现有的关键字的个数
		Type* key;//存储待查找的数，数组长度为m，最多存储m-1个元素
		long long* number;//存储结点的序号，数组长度为m，最多存储m-1个序号
		struct B_node** child;//指向孩子结点，数组长度为m+1，最多存储m个指针
		struct B_node* parent;//指向双亲结点
	};
	node* scan = nullptr;
	if (type == 1)
		scan = ptr1->first;
	B_node* root = new B_node;
	root->keynum = 1;
	root->key = new Type[m];
	if (type == 0)
		root->key[0] = ptr0->elements[0];
	else
	{
		root->key[0] = scan->element;
		scan = scan->next;
	}
	root->number = new long long[m];
	root->number[0] = 1;
	root->child = new B_node * [m + 1];
	root->child[0] = nullptr;
	root->child[1] = nullptr;
	root->parent = nullptr;

	//插入剩下的全部结点
	for (long long i = 2; i <= Listlength(); i++)
	{
		//查找该结点是否存在
		long long element_num = i;
		Type element = static_cast<Type>(0);
		if (type == 0)
			element = ptr0->elements[i - 1];
		else
		{
			element = scan->element;
			scan = scan->next;
		}
		B_node* search_next = root;
		B_node* search = nullptr;
		bool element_found = false;
		while (search_next != nullptr)
		{
			long long stats = -1;
			long long i1 = 1;
			for (i1 = 1; i1 <= search_next->keynum; i1++)
			{
				if (search_next->key[i1 - 1] >= element)
				{
					if (search_next->key[i1 - 1] == element)
					{
						stats = 1;
						break;
					}
					stats = 0;
					break;//扫描到的元素值比待查找的值大，退出循环
				}
			}
			if (i1 > search_next->keynum)
				i1 = i1 - 1;

			if (stats == 1)
			{
				element_found = true;
				break;
			}
			else
			{
				search = search_next;
				if (stats == 0)
					search_next = search_next->child[i1 - 1];
				else
					search_next = search_next->child[i1];
			}
		}
		if (element_found == true)
			continue;

		//该结点不存在，插入该结点
		bool FINISH = false;
		B_node* child_L = nullptr;
		B_node* child_R = nullptr;
		while (FINISH == false)
		{
			//结点插入
			if (search->key[0] > element)
			{
				for (long long i1 = search->keynum; i1 >= 1; i1--)
				{
					search->key[i1] = search->key[i1 - 1];
					search->number[i1] = search->number[i1 - 1];
					search->child[i1 + 1] = search->child[i1];
				}
				search->key[0] = element;
				search->number[0] = element_num;
				search->child[0] = child_L;
				search->child[1] = child_R;
			}
			else
			{
				long long i1 = search->keynum;
				while (search->key[i1 - 1] > element)
				{
					search->key[i1] = search->key[i1 - 1];
					search->number[i1] = search->number[i1 - 1];
					search->child[i1 + 1] = search->child[i1];
					i1 = i1 - 1;
				}
				search->key[i1] = element;
				search->number[i1] = element_num;
				search->child[i1] = child_L;
				search->child[i1 + 1] = child_R;
			}
			search->keynum = search->keynum + 1;
			if (search->keynum <= m - 1)
			{
				FINISH = true;
				continue;
			}

			//结点分裂
			long long NUM_CEIL = 0;
			if (m % 2 != 0)
				NUM_CEIL = (m + 1) / 2;
			else
				NUM_CEIL = m / 2;
			B_node* B_left = search;
			B_node* B_right = new B_node;
			B_left->keynum = NUM_CEIL - 1;
			B_right->keynum = m - NUM_CEIL;
			B_right->key = new Type[m];
			B_right->number = new long long[m];
			long long i1 = 1;
			for (long long i2 = NUM_CEIL + 1; i2 <= m; i2++)
			{
				B_right->key[i1 - 1] = search->key[i2 - 1];
				B_right->number[i1 - 1] = search->number[i2 - 1];
				i1 = i1 + 1;
			}
			B_right->child = new B_node * [m + 1];
			i1 = 1;
			for (long long i2 = NUM_CEIL + 1; i2 <= m + 1; i2++)
			{
				B_right->child[i1 - 1] = search->child[i2 - 1];
				if (search->child[i2 - 1] != nullptr)
					search->child[i2 - 1]->parent = B_right;
				i1 = i1 + 1;
			}

			element = search->key[NUM_CEIL - 1];
			element_num = search->number[NUM_CEIL - 1];
			child_L = B_left;
			child_R = B_right;
			if (search->parent != nullptr)
			{
				B_right->parent = search->parent;
				search = search->parent;
			}
			else
			{
				B_node* newroot = new B_node;
				newroot->keynum = 1;
				newroot->key = new Type[m];
				newroot->key[0] = element;
				newroot->number = new long long[m];
				newroot->number[0] = element_num;
				newroot->child = new B_node * [m + 1];
				newroot->child[0] = child_L;
				newroot->child[1] = child_R;
				newroot->parent = nullptr;
				child_L->parent = newroot;
				child_R->parent = newroot;
				root = newroot;
				FINISH = true;
			}
		}
	}

	//查找
	long long find_num = -1;
	B_node* search = root;
	while (search != nullptr)
	{
		long long stats = -1;
		long long i1 = 1;
		for (i1 = 1; i1 <= search->keynum; i1++)
		{
			if (search->key[i1 - 1] >= a)
			{
				if (search->key[i1 - 1] == a)
				{
					stats = 1;
					break;
				}
				stats = 0;
				break;//扫描到的元素值比待查找的值大，退出循环
			}
		}
		if (i1 > search->keynum)
			i1 = i1 - 1;
		if (stats == 1)
		{
			find_num = search->number[i1 - 1];
			break;
		}
		else
		{
			if (stats == 0)
				search = search->child[i1 - 1];
			else
				search = search->child[i1];
		}
	}

	//删除B树
	struct B_delete
	{
		struct B_node* node;
		struct B_delete* next;
	};
	B_delete* B_delete_head = new B_delete;
	B_delete_head->node = root;
	B_delete_head->next = nullptr;
	while (B_delete_head != nullptr)
	{
		B_delete* B_delete_backup = B_delete_head;
		B_delete_head = B_delete_head->next;
		for (long long i = 1; i <= B_delete_backup->node->keynum + 1; i++)
		{
			if (B_delete_backup->node->child[i - 1] != nullptr)
			{
				B_delete* B_delete_new = new B_delete;
				B_delete_new->node = B_delete_backup->node->child[i - 1];
				B_delete_new->next = B_delete_head;
				B_delete_head = B_delete_new;
			}
		}
		delete[] B_delete_backup->node->child;
		delete[] B_delete_backup->node->key;
		delete[] B_delete_backup->node->number;
		delete B_delete_backup;
	}

	return find_num;
}

template<typename Type>
long long LIST<Type>::RB_TREE_search(const Type a) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】表的类型错误，无法执行任何操作\033[0m" << endl;
		return -1;
	}
	if (Listlength() == 0)
	{
		cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
		return -1;
	}

	//初始化红黑树
	struct rbtree
	{
		Type data;//结点的内容
		bool red;//true为红色;false为黑色
		long long number;//结点的序号
		struct rbtree* parent;
		struct rbtree* lchild;
		struct rbtree* rchild;
	};
	node* scan = nullptr;
	if (type == 1)
		scan = ptr1->first;
	rbtree* root = new rbtree;
	if (type == 0)
		root->data = ptr0->elements[0];
	else
	{
		root->data = scan->element;
		scan = scan->next;
	}
	root->red = false;
	root->number = 1;
	root->parent = nullptr;
	root->lchild = nullptr;
	root->rchild = nullptr;

	//构建红黑树
	//含有重复元素的线性表被视作合法输入
	for (long long i = 2; i <= Listlength(); i++)
	{
		//查找该元素是否存在，并排除掉线性表中重复的元素
		Type element = 0;
		if (type == 0)
			element = ptr0->elements[i - 1];
		else
		{
			element = scan->element;
			scan = scan->next;
		}
		rbtree* tree_search_next = root;
		rbtree* tree_search = nullptr;
		bool element_exist = false;
		while (tree_search_next != nullptr)
		{
			if (tree_search_next->data == element)
			{
				element_exist = true;
				break;
			}
			if (tree_search_next->data > element)
			{
				tree_search = tree_search_next;
				tree_search_next = tree_search_next->lchild;
			}
			else
			{
				tree_search = tree_search_next;
				tree_search_next = tree_search_next->rchild;
			}
		}
		if (element_exist == true)
			continue;

		//插入不存在的该元素
		rbtree* tree_check_pos = nullptr;
		if (tree_search->data > element)
		//取消对 NULL 指针“tree_search”的引用为误报，请忽略
		{
			tree_search->lchild = new rbtree;
			tree_search->lchild->number = i;
			tree_search->lchild->data = element;
			tree_search->lchild->red = true;
			tree_search->lchild->lchild = nullptr;
			tree_search->lchild->parent = tree_search;
			tree_search->lchild->rchild = nullptr;
			tree_check_pos = tree_search->lchild;
		}
		else
		{
			tree_search->rchild = new rbtree;
			tree_search->rchild->number = i;
			tree_search->rchild->data = element;
			tree_search->rchild->red = true;
			tree_search->rchild->lchild = nullptr;
			tree_search->rchild->parent = tree_search;
			tree_search->rchild->rchild = nullptr;
			tree_check_pos = tree_search->rchild;
		}

		//插入后进行检查
		while (true)
		{
			if (tree_check_pos->parent == nullptr)//根结点
			{
				tree_check_pos->red = false;
				break;
			}
			if (tree_check_pos->parent->red == false)//无需做出任何调整
				break;

			//情况分类
			int insert_type = -1;
			if (tree_check_pos->parent == tree_check_pos->parent->parent->lchild)//z.p是z.p.p的左孩子
			{
				if (tree_check_pos->parent->parent->rchild == nullptr ||
					tree_check_pos->parent->parent->rchild->red == false)//z的叔结点y是黑色
				{
					if (tree_check_pos == tree_check_pos->parent->rchild)//z是右孩子
						insert_type = 1;
					else
						insert_type = 2;//z是左孩子
				}
				else
					insert_type = 11;//z的叔结点y是红色
			}
			else
			{
				//z.p是z.p.p的右孩子
				if (tree_check_pos->parent->parent->lchild == nullptr ||
					tree_check_pos->parent->parent->lchild->red == false)//z的叔结点y是黑色
				{
					if (tree_check_pos == tree_check_pos->parent->rchild)//z是右孩子
						insert_type = 3;
					else
						insert_type = 4;//z是左孩子
				}
				else
					insert_type = 12;//z的叔结点y是红色
			}

			//旋转处理
			//指针位置不变
			if (insert_type == 1)
			{
				rbtree* A = tree_check_pos->parent;
				rbtree* C = A->parent;
				rbtree* T2 = tree_check_pos->lchild;
				rbtree* T3 = tree_check_pos->rchild;
				if (T2 != nullptr)
					T2->parent = A;
				if (T3 != nullptr)
					T3->parent = C;
				A->parent = tree_check_pos;
				A->rchild = T2;
				tree_check_pos->parent = C->parent;
				tree_check_pos->lchild = A;
				tree_check_pos->rchild = C;
				C->parent = tree_check_pos;
				C->lchild = T3;

				if (tree_check_pos->parent == nullptr)
					root = tree_check_pos;
				else
				{
					if (tree_check_pos->parent->lchild == C)
						tree_check_pos->parent->lchild = tree_check_pos;
					else
						tree_check_pos->parent->rchild = tree_check_pos;
				}
				tree_check_pos->red = false;
				C->red = true;
				break;
			}
			if (insert_type == 2)
			{
				rbtree* B = tree_check_pos->parent;
				rbtree* C = B->parent;
				rbtree* T3 = B->rchild;
				if (T3 != nullptr)
					T3->parent = C;
				B->rchild = C;
				B->parent = C->parent;
				C->parent = B;
				C->lchild = T3;

				if (B->parent == nullptr)
					root = B;
				else
				{
					if (B->parent->lchild == C)
						B->parent->lchild = B;
					else
						B->parent->rchild = B;
				}
				B->red = false;
				C->red = true;
				break;
			}
			if (insert_type == 3)
			{
				rbtree* B = tree_check_pos->parent;
				rbtree* C = B->parent;
				rbtree* T3 = B->lchild;
				if (T3 != nullptr)
					T3->parent = C;
				B->lchild = C;
				B->parent = C->parent;
				C->parent = B;
				C->rchild = T3;

				if (B->parent == nullptr)
					root = B;
				else
				{
					if (B->parent->lchild == C)
						B->parent->lchild = B;
					else
						B->parent->rchild = B;
				}
				B->red = false;
				C->red = true;
				break;
			}
			if (insert_type == 4)
			{
				rbtree* A = tree_check_pos->parent;
				rbtree* C = A->parent;
				rbtree* T2 = tree_check_pos->rchild;
				rbtree* T3 = tree_check_pos->lchild;
				if (T2 != nullptr)
					T2->parent = A;
				if (T3 != nullptr)
					T3->parent = C;
				A->parent = tree_check_pos;
				A->lchild = T2;
				tree_check_pos->parent = C->parent;
				tree_check_pos->rchild = A;
				tree_check_pos->lchild = C;
				C->parent = tree_check_pos;
				C->rchild = T3;

				if (tree_check_pos->parent == nullptr)
					root = tree_check_pos;
				else
				{
					if (tree_check_pos->parent->lchild == C)
						tree_check_pos->parent->lchild = tree_check_pos;
					else
						tree_check_pos->parent->rchild = tree_check_pos;
				}
				tree_check_pos->red = false;
				C->red = true;
				break;
			}
			//指针位置上移
			if (insert_type == 11)
			{
				tree_check_pos->parent->red = false;
				tree_check_pos->parent->parent->red = true;
				tree_check_pos->parent->parent->rchild->red = false;
				tree_check_pos = tree_check_pos->parent->parent;

				continue;
			}
			if (insert_type == 12)
			{
				tree_check_pos->parent->red = false;
				tree_check_pos->parent->parent->red = true;
				tree_check_pos->parent->parent->lchild->red = false;
				tree_check_pos = tree_check_pos->parent->parent;

				continue;
			}
		}
	}

	//查找
	long long find_number = -1;
	rbtree* search = root;
	while (search != nullptr)
	{
		if (search->data == a)
		{
			find_number = search->number;
			break;
		}
		if (search->data > a)
			search = search->lchild;
		else
			search = search->rchild;
	}

	//二叉树析构函数
	struct tree_delete
	{
		struct rbtree* treeptr;
		struct tree_delete* next;
	};
	tree_delete* tree_stack_top = new tree_delete;
	tree_stack_top->treeptr = root;
	tree_stack_top->next = nullptr;
	while (tree_stack_top != nullptr)
	{
		tree_delete* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr)//右子树先入栈
		//取消对 NULL 指针的引用为误报，请忽略
		{
			tree_delete* tree_stack_R = new tree_delete;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr)//左子树后入栈
		{
			tree_delete* tree_stack_L = new tree_delete;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
		delete tree_stack_backup;
	}

	return find_number;
}

template<typename Type>
bool LIST<Type>::Sort_TF() const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return true;
		}
		if (ptr0->length == 1)
			return true;

		for (long long i = 1; i <= Listlength() - 1; i++)
		{
			if (ptr0->elements[i - 1] > ptr0->elements[i])
				return false;
		}
		return true;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return true;
		}
		if (ptr1->num_elements == 1)
			return true;

		node* scan = ptr1->first;
		for (long long i = 1; i <= Listlength() - 1; i++)
		{
			if (scan->element > scan->next->element)
				return false;
			scan = scan->next;
		}
		return true;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return false;
}

template<typename Type>
void LIST<Type>::D_i_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		_D_i_sort_A(1, Listlength());
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		_D_i_sort_B(ptr1->first, ptr1->end);
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
inline void LIST<Type>::_D_i_sort_A(const long long a, const long long b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	//此算法模仿自C++STL库的sort函数的源代码
	for (long long i = a + 1; i <= b; i++)
	{
		//在此循环中，认为[a,i-1]序列是从小到大有序的
		Type value = ptr0->elements[i - 1];
		if (value < ptr0->elements[a - 1])//待排序的元素比有序序列的第一个(最小)元素还小
		{
			for (long long i1 = i - 1; i1 >= a; i1--)
				ptr0->elements[i1] = ptr0->elements[i1 - 1];
			ptr0->elements[a - 1] = value;
		}
		else//待排序的元素大于等于有序序列的第一个元素
		{
			//待排序元素一定会被插入到有序序列的第一个元素和最后一个元素之间
			//此时while循环只需要进行一次（大小）比较。省去了是否超出界限的检查，可以提升运行速度
			long long order = i - 1;
			while (value < ptr0->elements[order - 1])
			{
				ptr0->elements[order] = ptr0->elements[order - 1];
				order = order - 1;
			}
			ptr0->elements[order] = value;
		}
	}
	return;
}

template<typename Type>
inline void LIST<Type>::_D_i_sort_B(node* a, node* b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	//【注意】：由于链表不能随机读取，这里采取的方法是自创的方法，不是严格意义上的直接插入排序法
	//尽管这两种方法的速度也许差不了多少，但这里还是要使用自创的方法
	//从理论上分析，下面的算法读取总次数的均值与直接插入排序法相仿，但是写入次数的均值远低于直接插入排序法
	//下面的算法没有把元素的值逐个往后移动，而是直接把目标节点剪切到目标地点。这是该算法与直接插入排序法的最大区别
	//【注意】：此算法模仿自C++STL库的sort函数的源代码（只有线性表版本）
	node* scan = a->next;
	node* scan_end = b->next;
	while (scan != scan_end)
	{
		node* target = nullptr;
		if (scan->element < a->element)
			target = a->prior;//可能是nullptr，可能是a的前一个结点
		else
		{
			target = scan->prior;
			while (scan->element < target->element)
				target = target->prior;
		}
		//target指向值<=scan的第一个结点，target若为nullptr，则scan应该被移动到链表的最前面
		if (target == scan->prior)
		{
			scan = scan->next;
			continue;
		}
		node* move = scan;
		scan = scan->next;

		//取下move结点
		if (move == b)
			b = b->prior;
		if (move->next == nullptr)
		{
			ptr1->end = move->prior;
			move->prior->next = nullptr;
		}
		else
		{
			move->prior->next = move->next;
			move->next->prior = move->prior;
		}

		//插入move结点
		if (target == nullptr)
		{
			move->prior = nullptr;
			move->next = ptr1->first;
			ptr1->first->prior = move;
			ptr1->first = move;
		}
		else
		{
			move->next = target->next;
			move->prior = target;
			move->next->prior = move;
			move->prior->next = move;
		}
		if (a->prior == move)
			a = move;
	}
	return;
}

template<typename Type>
void LIST<Type>::B_i_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		_B_i_sort_A(1, Listlength());
		if (seq == 1)//从大到小排序
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		Sort(seq);//二分法查找对于链表无意义
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
inline void LIST<Type>::_B_i_sort_A(const long long a, const long long b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	for (long long i = a + 1; i <= b; i++)
	{
		if (ptr0->elements[i - 1] < ptr0->elements[i - 2])
		{
			long long low = a;
			long long high = i - 1;
			while (low <= high)
			{
				long long middle = (low + high) / 2;
				if (ptr0->elements[i - 1] < ptr0->elements[middle - 1])
					high = middle - 1;
				else
					low = middle + 1;
			}
			Type temp = ptr0->elements[i - 1];
			for (long long i1 = i - 1; i1 >= high + 1; i1--)
				ptr0->elements[i1] = ptr0->elements[i1 - 1];
			ptr0->elements[high] = temp;
		}
	}
	return;
}

template<typename Type>
inline void LIST<Type>::_B_i_sort_B(node* a, node* b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	return;//二分法查找对于链表无意义
}

template<typename Type>
void LIST<Type>::Two_i_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		Type* temp = new Type[ptr0->total]();
		long long head = 1;
		long long tail = 1;
		temp[0] = Getelement(1);
		long long insert_pos = 0;
		for (long long i = 2; i <= ptr0->length; i++)
		{
			Type scan = Getelement(i);
			if (scan >= temp[0])
			{
				tail = tail + 1;
				insert_pos = tail;
				while (temp[insert_pos - 2] > scan)
				{
					temp[insert_pos - 1] = temp[insert_pos - 2];
					temp[insert_pos - 2] = scan;
					insert_pos = insert_pos - 1;
				}
				if (insert_pos == tail)
					temp[insert_pos - 1] = scan;
			}
			else
			{
				if (head == 1)
				{
					head = Listlength();
					temp[head - 1] = scan;
					continue;
				}
				else
					head = head - 1;
				insert_pos = head;
				while (temp[insert_pos] < scan)
				{
					temp[insert_pos - 1] = temp[insert_pos];
					temp[insert_pos] = scan;
					insert_pos = insert_pos + 1;
					if (insert_pos == Listlength())
						break;
				}
				if (insert_pos == head)
					temp[insert_pos - 1] = scan;
			}
		}
		Type* temp1 = new Type[ptr0->total]();
		long long mov_num = head - 1;
		for (long long i = 1; i <= Listlength(); i++)
		{
			long long pos = (i - mov_num + Listlength()) % Listlength();
			if (pos == 0)
				pos = Listlength();
			temp1[pos - 1] = temp[i - 1];
		}
		delete ptr0->elements;
		delete[] temp;
		ptr0->elements = temp1;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		LIST TEMP(2);
		TEMP.Repair(1);
		TEMP.ListinsertF(1, Getelement(1));
		node* scan = ptr1->first->next;
		node* mid = TEMP.ptr1->first;
		node* insert = mid;
		for (long long i = 2; i <= Listlength(); i++)
		{
			insert = mid;
			if (scan->element >= insert->element)
			{
				while (insert->next != nullptr && insert->next->element <= scan->element)
					insert = insert->next;

				TEMP.ptr1->num_elements = TEMP.ptr1->num_elements + 1;
				if (insert->next == nullptr)
				{
					node* XX = new node;
					XX->element = scan->element;
					XX->next = nullptr;
					XX->prior = insert;
					insert->next = XX;
					TEMP.ptr1->end = XX;
				}
				else
				{
					node* XX = new node;
					XX->element = scan->element;
					XX->next = insert->next;
					XX->prior = insert;
					XX->next->prior = XX;
					insert->next = XX;
				}
			}
			else
			{
				while (insert->prior != nullptr && insert->prior->element >= scan->element)
					insert = insert->prior;

				TEMP.ptr1->num_elements = TEMP.ptr1->num_elements + 1;
				if (insert->prior == nullptr)
				{
					node* XX = new node;
					XX->element = scan->element;
					XX->next = insert;
					XX->prior = nullptr;
					insert->prior = XX;
					TEMP.ptr1->first = XX;
				}
				else
				{
					node* XX = new node;
					XX->element = scan->element;
					XX->next = insert;
					XX->prior = insert->prior;
					XX->prior->next = XX;
					insert->prior = XX;
				}
			}
			scan = scan->next;
		}
		*this = TEMP;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::T_i_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		//请忽略Visual Studio在此处发出的以下警告：
		//警告	C6385	正在从 "scan_seq" 读取无效数据
		//警告	C6386	写入 "scan_seq" 时缓冲区溢出
		//经过确认，错误属于误报。发生错误的原因是编译器不够智能，没有正确识别前面if (ptr0->length == 0)
		//和if (ptr0->length == 1)这两条带有return的分支语句。编译器所指出的数组越界错误实际上永远不会发生
		long long* scan_seq = new long long[ptr0->length + 1]();
		scan_seq[0] = 1;
		scan_seq[1] = 0;
		for (long long i = 2; i <= Listlength(); i++)
		{
			long long scan_current = scan_seq[0];
			long long insert_pos = 0;
			while (true)
			{
				if (ptr0->elements[scan_current - 1] > ptr0->elements[i - 1])
				{
					insert_pos = 0;
					break;
				}
				else
				{
					if (scan_seq[scan_current] == 0)
					{
						insert_pos = scan_current;
						break;
					}
					if (ptr0->elements[scan_seq[scan_current] - 1] <= ptr0->elements[i - 1])
					{
						scan_current = scan_seq[scan_current];
						continue;
					}
					else
					{
						insert_pos = scan_current;
						break;
					}
				}
			}
			scan_seq[i] = scan_seq[insert_pos];
			scan_seq[insert_pos] = i;
		}

		long long reshape_scan = scan_seq[0];
		long long reshape_scan_backup = reshape_scan;
		long long reshape_count = 1;
		Type swap = 0;
		while (reshape_count < Listlength())
		{
			while (true)
			{
				if (reshape_scan >= 0)
				{
					reshape_scan_backup = reshape_scan;
					reshape_scan = scan_seq[reshape_scan];
				}
				else
				{
					reshape_scan_backup = reshape_scan;
					reshape_scan = scan_seq[-reshape_scan];
				}
				if (reshape_scan < 0)
					continue;
				else
					break;
			}
			if (reshape_scan_backup < 0)
				reshape_scan_backup = -reshape_scan_backup;

			swap = ptr0->elements[reshape_count - 1];
			ptr0->elements[reshape_count - 1] = ptr0->elements[reshape_scan_backup - 1];
			ptr0->elements[reshape_scan_backup - 1] = swap;
			scan_seq[reshape_scan_backup] = scan_seq[reshape_count];
			scan_seq[reshape_count] = -reshape_scan_backup;
			reshape_count = reshape_count + 1;
		}
		delete[] scan_seq;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		struct chart
		{
			struct node* pointer;
			long long num;
		};
		chart *scan_seq = new chart[ptr1->num_elements + 1];
		scan_seq[0].pointer = nullptr;
		scan_seq[0].num = 1;
		scan_seq[1].pointer = ptr1->first;
		scan_seq[1].num = 0;
		for (long long i = 2; i <= Listlength(); i++)
			scan_seq[i].pointer = scan_seq[i - 1].pointer->next;
		node* i_node = ptr1->first->next;
		for (long long i = 2; i <= Listlength(); i++)
		{
			long long scan_current = scan_seq[0].num;
			long long insert_pos = 0;
			while (true)
			{
				if (scan_seq[scan_current].pointer->element > i_node->element)
				{
					insert_pos = 0;
					break;
				}
				else
				{
					if (scan_seq[scan_current].num == 0)
					{
						insert_pos = scan_current;
						break;
					}
					if (scan_seq[scan_seq[scan_current].num].pointer->element <= i_node->element)
					{
						scan_current = scan_seq[scan_current].num;
						continue;
					}
					else
					{
						insert_pos = scan_current;
						break;
					}
				}
			}
			if (i + 1 > ptr1->num_elements + 1)
				return;//用于避免Visual studio编译器报错“数组越界”。语句本身没有实际意义
			scan_seq[i].num = scan_seq[insert_pos].num;
			scan_seq[insert_pos].num = i;
			i_node = i_node->next;
		}

		long long reshape_scan = scan_seq[0].num;
		long long reshape_scan_backup = reshape_scan;
		long long reshape_count = 1;
		Type swap = 0;
		while (reshape_count < Listlength())
		{
			while (true)
			{
				if (reshape_scan + 1 > ptr1->num_elements + 1)
					return;//用于避免Visual studio编译器报错“数组越界”。语句本身没有实际意义
				if (reshape_scan >= 0)
				{
					reshape_scan_backup = reshape_scan;
					reshape_scan = scan_seq[reshape_scan].num;
				}
				else
				{
					reshape_scan_backup = reshape_scan;
					reshape_scan = scan_seq[-reshape_scan].num;
				}
				if (reshape_scan < 0)
					continue;
				else
					break;
			}
			if (reshape_scan_backup < 0)
				reshape_scan_backup = -reshape_scan_backup;

			if (reshape_count + 1 > ptr1->num_elements + 1)
				return;//用于避免Visual studio编译器报错“数组越界”。语句本身没有实际意义
			swap = scan_seq[reshape_count].pointer->element;
			scan_seq[reshape_count].pointer->element = scan_seq[reshape_scan_backup].pointer->element;
			scan_seq[reshape_scan_backup].pointer->element = swap;
			scan_seq[reshape_scan_backup].num = scan_seq[reshape_count].num;
			scan_seq[reshape_count].num = -reshape_scan_backup;
			reshape_count = reshape_count + 1;
		}
		delete[] scan_seq;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::S_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;
	}

	int increment_num = static_cast<int>(floor(log1p(2 * Listlength()) / log(3)));
	int* increment = new int[increment_num];
	for (int i = increment_num; i >= 1; i--)
		increment[i - 1] = (3 ^ (increment_num - i + 1) - 1) / 2;

	if (type == 0)
	{
		for (int i = 1; i <= increment_num; i++)//希尔排序增量的循环
		{
			long long delta = static_cast<long long>(increment[i - 1]);//当前循环的增量
			for (long long i1 = 1; i1 <= delta; i1++)//对于每个希尔排序增量，用循环处理划分出的每个子序列
			{
				long long group_num = (Listlength() - i1 + 1) / (delta + 1) + 1;//每个子序列的元素数量
				if (group_num == 1)
					continue;
				long long group_end = i1;//每个子序列最后一个元素的序号
				while (group_end + delta <= Listlength())
					group_end = group_end + delta;

				for (long long i2 = i1; i2 <= group_end - delta; i2 = i2 + delta)//循环的次数为每个组中的元素数量-1
				{
					long long target = i2 + delta;
					while (ptr0->elements[target - delta - 1] > ptr0->elements[target - 1])
					{
						Type temp = ptr0->elements[target - delta - 1];
						ptr0->elements[target - delta - 1] = ptr0->elements[target - 1];
						ptr0->elements[target - 1] = temp;
						target = target - delta;
						if (target == i1)
							break;
					}
				}
			}
		}
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		delete[] increment;
		return;
	}
	if (type == 1)
	{
		for (int i = 1; i <= increment_num; i++)//希尔排序增量的循环
		{
			long long delta = static_cast<long long>(increment[i - 1]);//当前循环的增量
			for (long long i1 = 1; i1 <= delta; i1++)//对于每个希尔排序增量，用循环处理划分出的每个子序列
			{
				long long group_num = (Listlength() - i1 + 1) / (delta + 1) + 1;//每个子序列的元素数量
				if (group_num == 1)
					continue;
				long long group_end = i1;//每个子序列最后一个元素的序号
				while (group_end + delta <= Listlength())
					group_end = group_end + delta;

				for (long long i2 = i1; i2 <= group_end - delta; i2 = i2 + delta)//循环的次数为每个组中的元素数量-1
				{
					long long pos_num = 1;//pos始终是target的前一个元素
					node* pos = ptr1->first;
					while (pos_num < i2)
					{
						pos = pos->next;
						pos_num = pos_num + 1;
					}
					node* target = pos;
					long long target_num = pos_num;
					while (target_num < pos_num + delta)
					{
						target = target->next;
						target_num = target_num + 1;
					}

					while (pos->element > target->element)
					{
						Type temp = pos->element;
						pos->element = target->element;
						target->element = temp;
						target = pos;
						target_num = pos_num;
						if (target_num == i1)
							break;
						long long TEMP = pos_num - delta;
						while (pos_num > TEMP)
						{
							pos = pos->prior;
							pos_num = pos_num - 1;
						}
					}
				}
			}
		}
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		delete[] increment;
		return;
	}
	delete[] increment;

	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::B_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}

	//起泡排序函数（从小到大排序）要从后向前扫描，并交换顺序不对的元素。从后向前扫描一次，就能将最小的元素放到数组的第一位。
	//典型例子：（从小到大排序）数组中除了最小的元素均有序排列。假如从后向前扫描，只需要扫描两次。但是从前向后扫描，
	//   扫描次数大于等于两次
	//本起泡排序函数相较普通的起泡排序函数，做了以下改进：
	//1.（设某次扫描时，扫描终点的序号是A）
	//（1）下一次扫描时，将扫描终点设置为A+1，因为第A位是本次扫描中找出的最小值，没有必要比较最小值与其他元素的大小关系。
	//   以此类推，每次扫描结束后，都将扫描终点的序号+1。
	//（2）设在某次扫描中，元素值被改变的全部单元的最小序号是B。那么下次扫描的终点应该是B-1，因为第B位的值被改变，第B位的值可能
	//   小于第B-1位的值。
	//   综合第（1）（2）条，下一次扫描时，新的扫描终点是max(A+1,B-1)。若新的扫描终点的序号等于数组长度，则退出循环
	//2.如果某次扫描中没有移动过元素，则说明数组已排序完成，提前退出循环。
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		bool if_moved = true;
		long long scan_start = Listlength();
		long long scan_end = 1;
		while (if_moved == true)
		{
			if_moved = false;
			long long moved_end = 1;
			for (long long i = scan_start; i >= scan_end + 1; i--)
			{
				if (ptr0->elements[i - 2] > ptr0->elements[i - 1])
				{
					Type temp = ptr0->elements[i - 2];
					ptr0->elements[i - 2] = ptr0->elements[i - 1];
					ptr0->elements[i - 1] = temp;
					if_moved = true;
					moved_end = i - 1;
				}
			}
			moved_end = moved_end - 1;
			scan_end = scan_end + 1;
			if (moved_end > scan_end)
				scan_end = moved_end;
			if (scan_end == Listlength())
				break;
		}

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		bool if_moved = true;
		long long scan_start = Listlength();
		long long scan_end = 1;
		while (if_moved == true)
		{
			if_moved = false;
			long long moved_end = 1;
			node* scan = ptr1->end;
			for (long long i = scan_start; i >= scan_end + 1; i--)
			{
				if (scan->prior->element > scan->element)
				{
					Type temp = scan->element;
					scan->element = scan->prior->element;
					scan->prior->element = temp;
					if_moved = true;
					moved_end = i - 1;
				}
				scan = scan->prior;
			}
			moved_end = moved_end - 1;
			scan_end = scan_end + 1;
			if (moved_end > scan_end)
				scan_end = moved_end;
			if (scan_end == Listlength())
				break;
		}

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::Q_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		return;
	}

	//课后题10.42，计算一个序列的中值记录，目前已知的最快算法是在本快速排序算法上加以改造。
	//设现在需要知道第k个记录是谁。则进行一次快速排序。一次快速排序结束后，若枢轴序号=k，则任务已完成
	//若枢轴序号>k，则下次快速排序只处理枢轴左边的部分，反之只处理枢轴右边的部分。其余的部分与本函数相同（要把改进2，3去掉）

	//本函数不是标准的快速排序函数（本函数其实就是内省排序函数）。本函数在标准的快速排序函数的基础上做了以下改进：
	//改进1：使用“三者取中”的法则选取枢轴记录
	//改进2：一次快速排序后比较得到的两个子序列的长度，先对较短的子序列进行快速排序操作
	//改进3：如果子序列的长度<=阈值，使用插入排序法进行排序，不再使用快速排序法进行排序
	//改进4：使用非递归形式的快速排序函数，以提高运行速度，降低内存占用
	//改进5：一次快速排序结束后，将那些值与枢轴相等的元素放置在枢轴元素旁边（三路快排）（相同元素聚集）
	//改进6：若栈的深度>阈值，则转为堆排序

	struct QSORT_STACK
	{
		long long low;
		node* low_pos;
		long long high;
		node* high_pos;
		long long depth;
		QSORT_STACK* next;
	};
	QSORT_STACK* QSORT_STACK_HEAD = new QSORT_STACK;
	if (type == 0)
	{
		QSORT_STACK_HEAD->low = 1;
		QSORT_STACK_HEAD->low_pos = nullptr;
		QSORT_STACK_HEAD->high = Listlength();
		QSORT_STACK_HEAD->high_pos = nullptr;
		QSORT_STACK_HEAD->depth = 1;
		QSORT_STACK_HEAD->next = nullptr;
	}
	if (type == 1)
	{
		QSORT_STACK_HEAD->low = 1;
		QSORT_STACK_HEAD->low_pos = ptr1->first;
		QSORT_STACK_HEAD->high = Listlength();
		QSORT_STACK_HEAD->high_pos = ptr1->end;
		QSORT_STACK_HEAD->depth = 1;
		QSORT_STACK_HEAD->next = nullptr;
	}
	long long DEPTH = _Q_sort_assist_DEPTH(Listlength());

	do
	{
		long long q_low = QSORT_STACK_HEAD->low;
		node* q_low_pos = QSORT_STACK_HEAD->low_pos;
		long long q_high = QSORT_STACK_HEAD->high;
		node* q_high_pos = QSORT_STACK_HEAD->high_pos;
		long long q_depth = QSORT_STACK_HEAD->depth;
		QSORT_STACK* Q_BACKUP = QSORT_STACK_HEAD;
		QSORT_STACK_HEAD = QSORT_STACK_HEAD->next;
		delete Q_BACKUP;
		long long q_low_backup = q_low;
		node* q_low_pos_backup = q_low_pos;
		long long q_high_backup = q_high;
		node* q_high_pos_backup = q_high_pos;

		if (q_high - q_low + 1 <= 15)
		{
			if (type == 0)
			{
				_D_i_sort_A(q_low, q_high);
				continue;
			}
			if (type == 1)
				_D_i_sort_B(q_low_pos, q_high_pos);
			continue;
		}
		if (q_depth >= DEPTH)
		{
			//99.99%的情况下，堆排序一次都不会被激活。当表含有一百万个元素时，栈深度的阈值是38。
			//对于随机生成的长度为一百万的序列，栈的最大深度在12左右。对于长度为一百万的完全逆序序列，栈的最大深度在15左右。
			if (type == 0)
			{
				_H_sort_A(q_low, q_high);
				continue;
			}
			if (type == 1)
				_H_sort_B(q_low_pos, q_high_pos);
			continue;
		}

		long long pivotkey = 0;
		if (type == 0)
		{
			pivotkey = _Q_sort_assist_median(q_low, q_high);
			//这里必须把枢轴记录与元素序列的第一个元素交换。否则会出错。
			//如果硬是不交换，需要改写进行一次快速排序的代码。可能存在改写方法，但是这里采取的交换元素法更简便。
			Type temp = ptr0->elements[q_low - 1];
			ptr0->elements[q_low - 1] = ptr0->elements[pivotkey - 1];
			ptr0->elements[pivotkey - 1] = temp;
			pivotkey = q_low;
		}
		node* pivotkey_ptr = nullptr;
		if (type == 1)
		{
			pivotkey_ptr = _Q_sort_assist_median(q_low_pos, q_high_pos, q_high - q_low + 1);
			//交换枢轴记录与元素序列的第一个元素
			Type temp = q_low_pos->element;
			q_low_pos->element = pivotkey_ptr->element;
			pivotkey_ptr->element = temp;
			pivotkey = q_low;
			pivotkey_ptr = q_low_pos;
		}

		long long left = q_low;
		node* left_ptr = q_low_pos;
		long long leftlen = 0;
		long long right = q_high;
		node* right_ptr = q_high_pos;
		long long rightlen = 0;
		if (type == 0)
		{
			Type pivotkey_backup = ptr0->elements[pivotkey - 1];
			while (q_low < q_high)
			{
				while (q_low < q_high && ptr0->elements[q_high - 1] >= pivotkey_backup)
				{
					if (ptr0->elements[q_high - 1] == pivotkey_backup)
					{
						Type temp = ptr0->elements[right - 1];
						ptr0->elements[right - 1] = ptr0->elements[q_high - 1];
						ptr0->elements[q_high - 1] = temp;
						right = right - 1;
						rightlen = rightlen + 1;
					}
					q_high = q_high - 1;
				}
				ptr0->elements[q_low - 1] = ptr0->elements[q_high - 1];
				while (q_low < q_high && ptr0->elements[q_low - 1] <= pivotkey_backup)
				{
					if (ptr0->elements[q_low - 1] == pivotkey_backup)
					{
						Type temp = ptr0->elements[left - 1];
						ptr0->elements[left - 1] = ptr0->elements[q_low - 1];
						ptr0->elements[q_low - 1] = temp;
						left = left + 1;
						leftlen = leftlen + 1;
					}
					q_low = q_low + 1;
				}
				ptr0->elements[q_high - 1] = ptr0->elements[q_low - 1];
			}
			ptr0->elements[q_low - 1] = pivotkey_backup;

			//将那些值与枢轴相等的元素放置在枢轴元素旁边
			while (leftlen != 0)
			{
				Type temp = ptr0->elements[left - 2];
				ptr0->elements[left - 2] = ptr0->elements[q_low - 2];
				ptr0->elements[q_low - 2] = temp;
				left = left - 1;
				leftlen = leftlen - 1;
				q_low = q_low - 1;
			}
			while (rightlen != 0)
			{
				Type temp = ptr0->elements[right];
				ptr0->elements[right] = ptr0->elements[q_high];
				ptr0->elements[q_high] = temp;
				right = right + 1;
				rightlen = rightlen - 1;
				q_high = q_high + 1;
			}
		}
		if (type == 1)
		{
			Type pivotkey_backup = pivotkey_ptr->element;
			while (q_low < q_high)
			{
				while (q_low < q_high && q_high_pos->element >= pivotkey_backup)
				{
					if (q_high_pos->element == pivotkey_backup)
					{
						Type temp = right_ptr->element;
						right_ptr->element = q_high_pos->element;
						q_high_pos->element = temp;
						right = right - 1;
						right_ptr = right_ptr->prior;
						rightlen = rightlen + 1;
					}
					q_high = q_high - 1;
					q_high_pos = q_high_pos->prior;
				}
				q_low_pos->element = q_high_pos->element;
				while (q_low < q_high && q_low_pos->element <= pivotkey_backup)
				{
					if (q_low_pos->element == pivotkey_backup)
					{
						Type temp = left_ptr->element;
						left_ptr->element = q_low_pos->element;
						q_low_pos->element = temp;
						left = left + 1;
						left_ptr = left_ptr->next;
						leftlen = leftlen + 1;
					}
					q_low = q_low + 1;
					q_low_pos = q_low_pos->next;
				}
				q_high_pos->element = q_low_pos->element;
			}
			q_low_pos->element = pivotkey_backup;

			//将那些值与枢轴相等的元素放置在枢轴元素旁边
			while (leftlen != 0)
			{
				Type temp = left_ptr->prior->element;
				left_ptr->prior->element = q_low_pos->prior->element;
				q_low_pos->prior->element = temp;
				left = left - 1;
				left_ptr = left_ptr->prior;
				leftlen = leftlen - 1;
				q_low = q_low - 1;
				q_low_pos = q_low_pos->prior;
			}
			while (rightlen != 0)
			{
				Type temp = right_ptr->next->element;
				right_ptr->next->element = q_high_pos->next->element;
				q_high_pos->next->element = temp;
				right = right + 1;
				right_ptr = right_ptr->next;
				rightlen = rightlen - 1;
				q_high = q_high + 1;
				q_high_pos = q_high_pos->next;
			}
		}

		//【注意】：被放置在枢轴元素周围的，值与枢轴元素相等的元素不入栈
		long long q_low_length = q_low - q_low_backup;//两个子序列的长度
		long long q_high_length = q_high_backup - q_high;
		//先对短的子序列进行快速排序，即先将长的子序列入栈
		if (q_low_length < q_high_length)
		{
			//先将右边那个子序列入栈
			if (q_high_length >= 2)//若子序列长度为1，则不可以入栈，否则程序可能会崩溃
			{
				QSORT_STACK* QSORT_STACK_TEMP = new QSORT_STACK;
				QSORT_STACK_TEMP->low = q_high + 1;
				if (type == 0)
					QSORT_STACK_TEMP->low_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->low_pos = q_high_pos->next;
				QSORT_STACK_TEMP->high = q_high_backup;
				if (type == 0)
					QSORT_STACK_TEMP->high_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->high_pos = q_high_pos_backup;
				if (QSORT_STACK_HEAD == nullptr)
					QSORT_STACK_TEMP->depth = 1;
				else
					QSORT_STACK_TEMP->depth = QSORT_STACK_HEAD->depth + 1;
				QSORT_STACK_TEMP->next = QSORT_STACK_HEAD;
				QSORT_STACK_HEAD = QSORT_STACK_TEMP;
			}
			if (q_low_length >= 2)
			{
				QSORT_STACK* QSORT_STACK_TEMP = new QSORT_STACK;
				QSORT_STACK_TEMP->low = q_low_backup;
				if (type == 0)
					QSORT_STACK_TEMP->low_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->low_pos = q_low_pos_backup;
				QSORT_STACK_TEMP->high = q_low - 1;
				if (type == 0)
					QSORT_STACK_TEMP->high_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->high_pos = q_low_pos->prior;
				if (QSORT_STACK_HEAD == nullptr)
					QSORT_STACK_TEMP->depth = 1;
				else
					QSORT_STACK_TEMP->depth = QSORT_STACK_HEAD->depth + 1;
				QSORT_STACK_TEMP->next = QSORT_STACK_HEAD;
				QSORT_STACK_HEAD = QSORT_STACK_TEMP;
			}
		}
		else
		{
			//先将左边那个子序列入栈
			if (q_low_length >= 2)
			{
				QSORT_STACK* QSORT_STACK_TEMP = new QSORT_STACK;
				QSORT_STACK_TEMP->low = q_low_backup;
				if (type == 0)
					QSORT_STACK_TEMP->low_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->low_pos = q_low_pos_backup;
				QSORT_STACK_TEMP->high = q_low - 1;
				if (type == 0)
					QSORT_STACK_TEMP->high_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->high_pos = q_low_pos->prior;
				if (QSORT_STACK_HEAD == nullptr)
					QSORT_STACK_TEMP->depth = 1;
				else
					QSORT_STACK_TEMP->depth = QSORT_STACK_HEAD->depth + 1;
				QSORT_STACK_TEMP->next = QSORT_STACK_HEAD;
				QSORT_STACK_HEAD = QSORT_STACK_TEMP;
			}
			if (q_high_length >= 2)
			{
				QSORT_STACK* QSORT_STACK_TEMP = new QSORT_STACK;
				QSORT_STACK_TEMP->low = q_high + 1;
				if (type == 0)
					QSORT_STACK_TEMP->low_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->low_pos = q_high_pos->next;
				QSORT_STACK_TEMP->high = q_high_backup;
				if (type == 0)
					QSORT_STACK_TEMP->high_pos = nullptr;
				if (type == 1)
					QSORT_STACK_TEMP->high_pos = q_high_pos_backup;
				if (QSORT_STACK_HEAD == nullptr)
					QSORT_STACK_TEMP->depth = 1;
				else
					QSORT_STACK_TEMP->depth = QSORT_STACK_HEAD->depth + 1;
				QSORT_STACK_TEMP->next = QSORT_STACK_HEAD;
				QSORT_STACK_HEAD = QSORT_STACK_TEMP;
			}
		}
	} while (QSORT_STACK_HEAD != nullptr);

	if (seq == 1)//从大到小排序	
		Reverse(1, Listlength());
	return;
}

template<typename Type>
inline long long LIST<Type>::_Q_sort_assist_median(const long long a, const long long b) const
{
	long long c = static_cast<long long>(floor(a + b) / 2);
	Type x = ptr0->elements[a - 1];// x - a
	Type y = ptr0->elements[b - 1];// y - b
	Type z = ptr0->elements[c - 1];// z - c
	if (x < y)//x<y
	{
		if (y < z)//y<z
			return b;//x<y y<z
		else//z<y
		{
			if (x < z)//x<z
				return c;//x<z  z<y
			else//z<x
				return a;//z<x  x<y
		}
	}
	else//y<x
	{
		if (x < z)//x<z
			return a;//y<x  x<z
		else//z<x
		{
			if (y < z)//y<z
				return c;//y<z  z<x
			else//z<y
				return b;//z<y  y<x
		}
	}
}

template<typename Type>
inline LIST<Type>::node* LIST<Type>::_Q_sort_assist_median(node* a, node* b, long long num) const
{
	node* c = b;
	if (num > 20)
	{
		for (int i = 1; i <= 10; i++)
			c = c->prior;
		return c;
	}

	Type x = a->element;//  x - a
	Type y = b->element;//  y - b
	for (int i = 1; i <= num / 2; i++)
		c = c->prior;
	Type z = c->element;//  z - c

	if (x < y)//x<y
	{
		if (y < z)//y<z
			return b;//x<y y<z
		else//z<y
		{
			if (x < z)//x<z
				return c;//x<z  z<y
			else//z<x
				return a;//z<x  x<y
		}
	}
	else//y<x
	{
		if (x < z)//x<z
			return a;//y<x  x<z
		else//z<x
		{
			if (y < z)//y<z
				return c;//y<z  z<x
			else//z<y
				return b;//z<y  y<x
		}
	}
}

template<typename Type>
inline long long LIST<Type>::_Q_sort_assist_DEPTH(long long a) const
{
	long long DEPTH;
	for (DEPTH = 0; a > 1; a >>= 1)
		++DEPTH;
	return DEPTH * 2;
}

template<typename Type>
void LIST<Type>::S_s_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		for (long long i = 1; i <= Listlength() - 1; i++)
		{
			long long min = i;
			for (long long i1 = i + 1; i1 <= Listlength(); i1++)
			{
				if (ptr0->elements[i1 - 1] < ptr0->elements[min - 1])
					min = i1;
			}
			if (min != i)
			{
				Type temp = ptr0->elements[min - 1];
				ptr0->elements[min - 1] = ptr0->elements[i - 1];
				ptr0->elements[i - 1] = temp;
			}
		}

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		node* i_pos = ptr1->first;
		for (long long i = 1; i <= Listlength() - 1; i++)
		{
			node* min_pos = i_pos;
			node* i1_pos = i_pos->next;
			for (long long i1 = i + 1; i1 <= Listlength(); i1++)
			{
				if (i1_pos->element < min_pos->element)
					min_pos = i1_pos;
				i1_pos = i1_pos->next;
			}
			if (min_pos != i_pos)
			{
				Type temp = min_pos->element;
				min_pos->element = i_pos->element;
				i_pos->element = temp;
			}
			i_pos = i_pos->next;
		}

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::T_s_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		return;
	}

	//无论LIST对象使用哪种存储结构（线性表/链表），进行树形选择排序的算法均通用
	//与教科书不同，函数将无穷大定义为二叉树结点的weight域为1（此时data域可以为任何数值）
	struct tree_generate
	{
		struct TREE<Type>::bitree * treeptr;
		struct tree_generate* next;
	};
	tree_generate* tree_stack_head = nullptr;
	node * scan = nullptr;
	if (type == 1 && ptr1 != nullptr)
		scan = ptr1->first;
	for (long long i = 1; i <= Listlength(); i++)
	{
		tree_generate* tree_stack_new = new tree_generate;
		tree_stack_new->next = tree_stack_head;
		tree_stack_new->treeptr = new struct TREE<Type>::bitree;
		tree_stack_new->treeptr->lchild = nullptr;
		tree_stack_new->treeptr->ltag = false;
		tree_stack_new->treeptr->weight = static_cast<long double>(0);
		if (type == 0)
			tree_stack_new->treeptr->data = ptr0->elements[i - 1];
		else
		{
			if (scan == nullptr)
				return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
			//一些安全软件可能在此处误报“内存泄漏”，但请忽略。此return语句理论上永远不会被运行
			tree_stack_new->treeptr->data = scan->element;
			scan = scan->next;
		}
		tree_stack_new->treeptr->parent = nullptr;
		tree_stack_new->treeptr->rtag = false;
		tree_stack_new->treeptr->rchild = nullptr;
		tree_stack_head = tree_stack_new;
	}
	while (tree_stack_head != nullptr && tree_stack_head->next != nullptr)
	{
		tree_generate* tree_stack_scanF = tree_stack_head;
		tree_generate* tree_stack_scanR = tree_stack_scanF->next;
		while (true)
		{
			struct TREE<Type>::bitree* root_new = new struct TREE<Type>::bitree;
			root_new->lchild = tree_stack_scanF->treeptr;
			root_new->ltag = false;
			root_new->weight = static_cast<long double>(0);
			if (tree_stack_scanF->treeptr->data < tree_stack_scanR->treeptr->data)
				root_new->data = tree_stack_scanF->treeptr->data;
			else
				root_new->data = tree_stack_scanR->treeptr->data;
			root_new->parent = nullptr;
			root_new->rtag = false;
			root_new->rchild = tree_stack_scanR->treeptr;
			tree_stack_scanR->treeptr->parent = root_new;
			tree_stack_scanF->treeptr->parent = root_new;
			tree_stack_scanF->treeptr = root_new;
			tree_stack_scanF->next = tree_stack_scanR->next;
			tree_stack_scanF = tree_stack_scanF->next;
			delete tree_stack_scanR;
			if (tree_stack_scanF == nullptr)
				break;//偶数个结点
			tree_stack_scanR = tree_stack_scanF->next;
			if (tree_stack_scanR == nullptr)
			{
				//奇数个结点，单独处理
				struct TREE<Type>::bitree* root_newx = new struct TREE<Type>::bitree;
				root_newx->lchild = tree_stack_scanF->treeptr;
				root_newx->ltag = false;
				root_newx->weight = static_cast<long double>(0);
				root_newx->data = tree_stack_scanF->treeptr->data;
				root_newx->parent = nullptr;
				root_newx->rtag = false;
				root_newx->rchild = nullptr;
				tree_stack_scanF->treeptr->parent = root_newx;
				tree_stack_scanF->treeptr = root_newx;
				break;
			}
		}
	}
	if (tree_stack_head == nullptr)
		return;//用于避免Visual studio编译器报错“取消对null指针的应用”。语句本身没有实际意义
	struct TREE<Type>::bitree* root = tree_stack_head->treeptr;
	delete tree_stack_head;

	long long loop_times = Listlength();
	Clearlist();
	if (type == 0)
		Listexpand(loop_times);
	for (long long i = 1; i <= loop_times; i++)
	{
		ListinsertR(Listlength(), static_cast<Type>(root->data));
		if (i == loop_times)
			break;
		struct TREE<Type>::bitree* tree_scan = root;
		while (tree_scan->lchild != nullptr || tree_scan->rchild != nullptr)
		{
			if (tree_scan->lchild != nullptr && tree_scan->lchild->weight != 1 &&
				tree_scan->lchild->data == tree_scan->data)
			{
				tree_scan = tree_scan->lchild;
				continue;
			}
			if (tree_scan->rchild != nullptr && tree_scan->rchild->weight != 1 &&
				tree_scan->rchild->data == tree_scan->data)
				tree_scan = tree_scan->rchild;
		}
		tree_scan->weight = static_cast<long double>(1);
		while (tree_scan->parent != nullptr)
		{
			if (tree_scan->parent->lchild == tree_scan)
			{
				//是双亲的左子树
				if (tree_scan->parent->rchild == nullptr || tree_scan->parent->rchild->weight == 1 ||
					(tree_scan->parent->rchild->data >= tree_scan->data && tree_scan->weight != 1))
				{
					//自身是双亲的唯一孩子 或 双亲的另一个孩子无穷大 或（自身不是无穷大 且 双亲另一个孩子的值大于等于自身的值）
					tree_scan->parent->data = tree_scan->data;
					tree_scan->parent->weight = tree_scan->weight;
					tree_scan = tree_scan->parent;
					continue;
				}
				tree_scan->parent->data = tree_scan->parent->rchild->data;
				tree_scan->parent->weight = tree_scan->parent->rchild->weight;
				tree_scan = tree_scan->parent;
				continue;
			}
			if (tree_scan->parent->rchild == tree_scan)
			{
				//是双亲的右子树
				if (tree_scan->parent->lchild == nullptr || tree_scan->parent->lchild->weight == 1 ||
					(tree_scan->parent->lchild->data >= tree_scan->data && tree_scan->weight != 1))
				{
					//自身是双亲的唯一孩子 或 双亲的另一个孩子无穷大 或（自身不是无穷大 且 双亲另一个孩子的值大于等于自身的值）
					tree_scan->parent->data = tree_scan->data;
					tree_scan->parent->weight = tree_scan->weight;
					tree_scan = tree_scan->parent;
					continue;
				}
				tree_scan->parent->data = tree_scan->parent->lchild->data;
				tree_scan->parent->weight = tree_scan->parent->lchild->weight;
				tree_scan = tree_scan->parent;
				continue;
			}
		}
	}

	tree_generate* tree_stack_top = new tree_generate;
	tree_stack_top->treeptr = root;
	tree_stack_top->next = nullptr;
	while (tree_stack_top != nullptr)
	{
		tree_generate* tree_stack_backup = tree_stack_top;
		tree_stack_top = tree_stack_top->next;
		if (tree_stack_backup->treeptr->rchild != nullptr)//右子树先入栈
		{
			tree_generate* tree_stack_R = new tree_generate;
			tree_stack_R->treeptr = tree_stack_backup->treeptr->rchild;
			tree_stack_R->next = tree_stack_top;
			tree_stack_top = tree_stack_R;
		}
		if (tree_stack_backup->treeptr->lchild != nullptr)//左子树后入栈
		{
			tree_generate* tree_stack_L = new tree_generate;
			tree_stack_L->treeptr = tree_stack_backup->treeptr->lchild;
			tree_stack_L->next = tree_stack_top;
			tree_stack_top = tree_stack_L;
		}
		delete tree_stack_backup->treeptr;
		delete tree_stack_backup;
	}

	if (seq == 1)//从大到小排序	
		Reverse(1, Listlength());
	return;
}

template<typename Type>
void LIST<Type>::H_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		_H_sort_A(1, Listlength());
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		_H_sort_B(ptr1->first, ptr1->end);
		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
inline void LIST<Type>::_H_sort_A(const long long a, const long long b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	//注意：顺序存储结构下，如果要将元素从小到大排序，需要建立大顶堆（可能与常识相反）
	//在以顺序表形式存储的二叉树中，某个结点的下标*2是该结点的左孩子（若存在），下标*2+1是该结点的右孩子（若存在）
	//此时结点的下标必须从1（根结点）开始编号。再次强调，必须从1（根结点）开始编号
	//二叉树（层序序列）最后一个非叶子结点的编号是结点的总数量/2（只取整数，若有小数则丢弃小数部分）
	long long interval_length = b - a + 1;//待排序区间的长度
	long long offset = a - 1;//偏移量，每个elements数组的下标要加上此数值

	for (long long i = interval_length / 2; i > 0; i--)
	{
		//（层序序列下）从最后一个非叶子结点开始，直到根结点，建立初始堆
		//该算法不交换双亲结点与叶子结点的值，而是先保存双亲结点的值，再使用叶子结点的值覆盖双亲结点的值，最后还原双亲结点的值
		Type temp = ptr0->elements[offset + i - 1];//保存该非叶子结点的值
		long long scan = i;//当前正在处理的结点位置
		for (long long j = 2 * i; j <= interval_length; j = j * 2)
		{
			//开始条件：j是该非叶子结点的左子树        迭代方法：j=j的左子树    终止条件：j不超过数组总长度
			if (j < interval_length && ptr0->elements[offset + j - 1] <= ptr0->elements[offset + j])
				j = j + 1;//若该非叶子结点的左子树存在且该非叶子结点的左子树 <= 右子树，则j=该非叶子结点的右子树
			//注意j < Listlength()意味着j!=Listlength()，即该非叶子结点有两个子树
			if (temp > ptr0->elements[offset + j - 1])
				break;//该非叶子结点的值 > 该非叶子结点全部子树的值
			ptr0->elements[offset + scan - 1] = ptr0->elements[offset + j - 1];//正在处理的结点的值等于该结点的左/右子树的值
			scan = j;//更新下一轮循环中，开始处理的结点的位置
		}
		ptr0->elements[offset + scan - 1] = temp;//退出循环时，还原双亲结点的值
	}
	for (long long i = interval_length; i > 1; i--)
	{
		Type tempx = ptr0->elements[offset + 0];
		ptr0->elements[offset + 0] = ptr0->elements[offset + i - 1];
		ptr0->elements[offset + i - 1] = tempx;
		Type temp = ptr0->elements[offset + 0];//保存根结点的值
		long long scan = 1;//当前正在处理的结点位置
		for (long long j = 2; j <= i - 1; j = j * 2)
		{
			//开始条件：j是该非叶子结点的左子树        迭代方法：j=j的左子树    终止条件：j不超过数组总长度
			if (j < i - 1 && ptr0->elements[offset + j - 1] <= ptr0->elements[offset + j])
				j = j + 1;//若该非叶子结点的左子树存在且该非叶子结点的左子树 <= 右子树，则j=该非叶子结点的右子树
			//注意j < Listlength()意味着j!=Listlength()，即该非叶子结点有两个子树
			if (temp > ptr0->elements[offset + j - 1])
				break;//该非叶子结点的值 > 该非叶子结点全部子树的值
			ptr0->elements[offset + scan - 1] = ptr0->elements[offset + j - 1];//正在处理的结点的值等于该结点的左/右子树的值
			scan = j;//更新下一轮循环中，开始处理的结点的位置
		}
		ptr0->elements[offset + scan - 1] = temp;//退出循环时，还原根结点的值
	}
	return;
}

template<typename Type>
inline void LIST<Type>::_H_sort_B(node* a, node* b)
{
	//【警告】：本函数只对数据进行“从小到大”的排序，且不负责验证输入的待排序范围是否合法
	struct tree_generate
	{
		struct TREE<Type>::bitree* treeptr;
		struct tree_generate* prior;
		struct tree_generate* next;
	};

	//初始化前两个结点
	node* scan = a;
	tree_generate* tree_queue_head = new tree_generate;
	tree_queue_head->next = new tree_generate;
	tree_generate* tree_queue_tail = tree_queue_head->next;
	tree_queue_tail->next = nullptr;
	tree_queue_tail->prior = tree_queue_head;
	tree_queue_head->prior = nullptr;
	tree_generate* tree_queue_notleaf = tree_queue_head;
	tree_queue_head->treeptr = new struct TREE<Type>::bitree;
	tree_queue_tail->treeptr = new struct TREE<Type>::bitree;
	tree_queue_head->treeptr->lchild = tree_queue_tail->treeptr;
	tree_queue_head->treeptr->ltag = false;
	tree_queue_head->treeptr->weight = static_cast<long double>(0);
	tree_queue_head->treeptr->data = scan->element;
	tree_queue_head->treeptr->parent = nullptr;
	tree_queue_head->treeptr->rtag = false;
	tree_queue_head->treeptr->rchild = nullptr;
	scan = scan->next;
	tree_queue_tail->treeptr->lchild = nullptr;
	tree_queue_tail->treeptr->ltag = false;
	tree_queue_tail->treeptr->weight = static_cast<long double>(0);
	tree_queue_tail->treeptr->data = scan->element;
	tree_queue_tail->treeptr->parent = tree_queue_head->treeptr;
	tree_queue_tail->treeptr->rtag = false;
	tree_queue_tail->treeptr->rchild = nullptr;
	scan = scan->next;

	//将剩余所有结点放入二叉树中
	while (scan != b->next)
	{
		if (tree_queue_notleaf->treeptr->lchild != nullptr && tree_queue_notleaf->treeptr->rchild != nullptr)
			tree_queue_notleaf = tree_queue_notleaf->next;
		tree_queue_tail->next = new tree_generate;
		tree_queue_tail->next->next = nullptr;
		tree_queue_tail->next->prior = tree_queue_tail;
		tree_queue_tail = tree_queue_tail->next;
		tree_queue_tail->treeptr = new struct TREE<Type>::bitree;
		tree_queue_tail->treeptr->lchild = nullptr;
		tree_queue_tail->treeptr->ltag = false;
		tree_queue_tail->treeptr->weight = static_cast<long double>(0);
		tree_queue_tail->treeptr->data = scan->element;
		tree_queue_tail->treeptr->parent = tree_queue_notleaf->treeptr;
		tree_queue_tail->treeptr->rtag = false;
		tree_queue_tail->treeptr->rchild = nullptr;
		if (tree_queue_notleaf->treeptr->lchild == nullptr)
			tree_queue_notleaf->treeptr->lchild = tree_queue_tail->treeptr;
		else
			tree_queue_notleaf->treeptr->rchild = tree_queue_tail->treeptr;
		scan = scan->next;
	}

	//建立初始堆
	while (tree_queue_notleaf != nullptr)
	{
		struct TREE<Type>::bitree* compare = tree_queue_notleaf->treeptr;
		while (true)
		{
			if ((compare->lchild != nullptr && compare->rchild == nullptr &&
				compare->data <= compare->lchild->data) ||
				(compare->rchild != nullptr && compare->lchild == nullptr &&
					compare->data <= compare->rchild->data) ||
				(compare->lchild != nullptr && compare->rchild != nullptr &&
					compare->data <= compare->lchild->data &&
					compare->data <= compare->rchild->data) ||
				(compare->lchild == nullptr && compare->rchild == nullptr))
				break;//只有左子树且本体<=左子树 或 只有右子树且本体<=右子树 或 有两个子树且本体<=两个子树 或 没有任何子树
			if ((compare->lchild != nullptr && compare->rchild == nullptr) ||
				((compare->lchild != nullptr && compare->rchild != nullptr) &&
					(compare->lchild->data < compare->rchild->data)))
			{
				//只有左子树 或 有两个子树且左子树小于右子树
				Type temp = compare->data;
				compare->data = compare->lchild->data;
				compare->lchild->data = temp;
				compare = compare->lchild;
				continue;
			}
			if ((compare->rchild != nullptr && compare->lchild == nullptr) ||
				((compare->lchild != nullptr && compare->rchild != nullptr) &&
					(compare->lchild->data >= compare->rchild->data)))
			{
				//只有右子树 或 有两个子树且左子树大于等于右子树
				Type temp = compare->data;
				compare->data = compare->rchild->data;
				compare->rchild->data = temp;
				compare = compare->rchild;
				continue;
			}
		}
		tree_queue_notleaf = tree_queue_notleaf->prior;
	}

	//开始堆排序
	scan = a;
	while (tree_queue_head != tree_queue_tail)//只剩根结点时，对根结点另行特殊处理
	{
		scan->element = tree_queue_head->treeptr->data;
		scan = scan->next;
		tree_queue_head->treeptr->data = tree_queue_tail->treeptr->data;
		//如果Visual studio等编译器报错“取消对null指针的应用”，请忽略
		if (tree_queue_tail->treeptr->parent->lchild == tree_queue_tail->treeptr)
			tree_queue_tail->treeptr->parent->lchild = nullptr;
		else
			tree_queue_tail->treeptr->parent->rchild = nullptr;
		tree_generate* tree_queue_delete = tree_queue_tail;
		tree_queue_tail = tree_queue_tail->prior;
		tree_queue_tail->next = nullptr;
		delete tree_queue_delete->treeptr;
		delete tree_queue_delete;
		struct TREE<Type>::bitree* compare = tree_queue_head->treeptr;
		while (true)
		{
			if ((compare->lchild != nullptr && compare->rchild == nullptr &&
				compare->data <= compare->lchild->data) ||
				(compare->rchild != nullptr && compare->lchild == nullptr &&
					compare->data <= compare->rchild->data) ||
				(compare->lchild != nullptr && compare->rchild != nullptr &&
					compare->data <= compare->lchild->data &&
					compare->data <= compare->rchild->data) ||
				(compare->lchild == nullptr && compare->rchild == nullptr))
				break;//只有左子树且本体<=左子树 或 只有右子树且本体<=右子树 或 有两个子树且本体<=两个子树 或 没有任何子树
			if ((compare->lchild != nullptr && compare->rchild == nullptr) ||
				((compare->lchild != nullptr && compare->rchild != nullptr) &&
					(compare->lchild->data < compare->rchild->data)))
			{
				//只有左子树 或 有两个子树且左子树小于右子树
				Type temp = compare->data;
				compare->data = compare->lchild->data;
				compare->lchild->data = temp;
				compare = compare->lchild;
				continue;
			}
			if ((compare->rchild != nullptr && compare->lchild == nullptr) ||
				((compare->lchild != nullptr && compare->rchild != nullptr) &&
					(compare->lchild->data >= compare->rchild->data)))
			{
				//只有右子树 或 有两个子树且左子树大于等于右子树
				Type temp = compare->data;
				compare->data = compare->rchild->data;
				compare->rchild->data = temp;
				compare = compare->rchild;
				continue;
			}
		}
	}
	scan->element = tree_queue_head->treeptr->data;
	delete tree_queue_head->treeptr;
	delete tree_queue_head;
	return;
}

template<typename Type>
void LIST<Type>::M_sort(const int seq)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		//存在空间复杂度为O(1)的算法。但是流程过于复杂，这里不使用
		//不使用最大有序子列作为初始归并段
		Type* T = new Type[ptr0->total]();
		long long length = 1;//每段的长度
		long long pos = 0;//初始位置
		long long times = 1;//进行归并的次数
		while (length < ptr0->length)
		{
			while (true)
			{
				long long pos_A_start = pos;
				if (pos_A_start > ptr0->length - 1)
					break;
				long long pos_A_end = pos_A_start + length - 1;
				if (pos_A_end >= ptr0->length - 1)
				{
					for (long long i = pos_A_start; i <= ptr0->length - 1; i++)
					{
						if (times % 2 == 1)
							T[i] = ptr0->elements[i];
						else
							ptr0->elements[i] = T[i];
					}
					break;
				}
				long long pos_B_start = pos_A_start + length;
				long long pos_B_end = pos_B_start + length - 1;
				if (pos_B_end >= ptr0->length - 1)
					pos_B_end = ptr0->length - 1;
				pos = pos_B_start + length;

				long long i = pos_A_start;
				long long j = pos_B_start;
				long long k = pos_A_start;
				while ((i <= pos_A_end) && (j <= pos_B_end))
				{
					if (times % 2 == 1)
					{
						if (ptr0->elements[i] < ptr0->elements[j])
						{
							T[k] = ptr0->elements[i];
							k = k + 1;
							i = i + 1;
						}
						else
						{
							T[k] = ptr0->elements[j];
							k = k + 1;
							j = j + 1;
						}
					}
					else
					{
						if (T[i] < T[j])
						{
							ptr0->elements[k] = T[i];
							k = k + 1;
							i = i + 1;
						}
						else
						{
							ptr0->elements[k] = T[j];
							k = k + 1;
							j = j + 1;
						}
					}
				}
				while (i <= pos_A_end)
				{
					if (times % 2 == 1)
						T[k] = ptr0->elements[i];
					else
						ptr0->elements[k] = T[i];
					k = k + 1;
					i = i + 1;
				}
				while (j <= pos_B_end)
				{
					if (times % 2 == 1)
						T[k] = ptr0->elements[j];
					else
						ptr0->elements[k] = T[j];
					k = k + 1;
					j = j + 1;
				}
			}
			times = times + 1;
			pos = 0;
			length = length * 2;
		}
		times = times - 1;
		if (times % 2 == 1)
		{
			delete[] ptr0->elements;
			ptr0->elements = T;
		}
		else
			delete[] T;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		//使用最大有序子列作为初始归并段
		struct chain_stack
		{
			node* ptr;
			struct chain_stack* next;
		};
		chain_stack* chain_top = new chain_stack;
		chain_top->ptr = ptr1->first;
		chain_top->next = nullptr;
		chain_stack* chain_scan = chain_top;
		node* scan = ptr1->first->next;
		while (scan != nullptr)
		{
			chain_scan->next = new chain_stack;
			chain_scan = chain_scan->next;
			chain_scan->ptr = scan;
			chain_scan->next = nullptr;
			while (scan->next != nullptr && scan->element == scan->next->element)
				scan = scan->next;
			scan = scan->next;
		}
		while (chain_top->next != nullptr)//编译器可能误报“取消对NULL指针的引用”错误
		{
			chain_scan = chain_top;
			while (chain_scan != nullptr)
			{
				node* A_start = chain_scan->ptr;
				node* A_end = nullptr;
				node* B_start = nullptr;
				node* B_end = nullptr;

				chain_stack* chain_backup = chain_scan;
				chain_scan = chain_scan->next;
				if (chain_scan == nullptr)
					break;
				else
				{
					A_end = chain_scan->ptr->prior;
					B_start = chain_scan->ptr;
					chain_stack* chain_delete = chain_scan;
					chain_scan = chain_scan->next;
					delete chain_delete;
					chain_backup->next = chain_scan;
					if (chain_scan == nullptr)
						B_end = ptr1->end;
					else
						B_end = chain_scan->ptr->prior;
				}

				node* A_start_backup = A_start->prior;
				node* A_scan = A_start;
				node* B_scan = B_start;
				while (A_scan != A_end->next && B_scan != B_end->next)//编译器可能误报“取消对NULL指针的引用”错误
				{
					if (A_scan->element <= B_scan->element)
						A_scan = A_scan->next;
					else
					{
						node* B_scan_backup = B_scan->next;
						if (B_scan->next == nullptr)
							ptr1->end = B_scan->prior;
						if (B_scan->prior != nullptr)
							B_scan->prior->next = B_scan->next;
						if (B_scan->next != nullptr)
							B_scan->next->prior = B_scan->prior;
						B_scan->prior = A_scan->prior;
						if (A_scan->prior == nullptr)
							ptr1->first = B_scan;
						B_scan->next = A_scan;
						if (A_scan->prior != nullptr)
							A_scan->prior->next = B_scan;
						A_scan->prior = B_scan;
						B_scan = B_scan_backup;
					}
					if (B_scan == nullptr)
						break;
				}
				if (A_start_backup == nullptr)
					chain_backup->ptr = ptr1->first;
				else
					chain_backup->ptr = A_start_backup->next;
			}
		}
		delete chain_top;

		if (seq == 1)//从大到小排序	
			Reverse(1, Listlength());
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
void LIST<Type>::R_sort(const int seq)
{
	// 【警告】尽管存在白名单类型匹配，但是对此函数使用浮点类型数据会无法通过编译//////////////////////////////////////////////////////
	// 【警告】尽管存在白名单类型匹配，但是对此函数使用浮点类型数据会无法通过编译//////////////////////////////////////////////////////
	// 【警告】尽管存在白名单类型匹配，但是对此函数使用浮点类型数据会无法通过编译//////////////////////////////////////////////////////

	// 【警告】尽管存在白名单类型匹配，但是若对此函数使用bool类型数据，编译器会弹出操作类型不安全的警告///////////////////////////////////
	// 【警告】尽管存在白名单类型匹配，但是若对此函数使用bool类型数据，编译器会弹出操作类型不安全的警告///////////////////////////////////
	// 【警告】尽管存在白名单类型匹配，但是若对此函数使用bool类型数据，编译器会弹出操作类型不安全的警告///////////////////////////////////

	// 【警告】在表长达到10000左右后，如果对short对象使用本函数，程序可能在"对负数部分进行基数排序"部分崩溃，原因未知//////////////////////
	// 【警告】在表长达到10000左右后，如果对short对象使用本函数，程序可能在"对负数部分进行基数排序"部分崩溃，原因未知//////////////////////
	// 【警告】在表长达到10000左右后，如果对short对象使用本函数，程序可能在"对负数部分进行基数排序"部分崩溃，原因未知//////////////////////

	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
		type = -1;
		ptr0 = nullptr;
		ptr1 = nullptr;
		return;
	}
	//由于对浮点类型进行排序需要位移操作，但是目前在C++的位移操作上遇到了一些技术困难
	//   所以本基数排序函数暂时不支持对浮点类型和bool类型进行排序
	if (strcmp(typeid(Type).name(), typeid(char).name()) != 0 &&
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
		strcmp(typeid(Type).name(), typeid(__int32).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(int).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned int).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(__int64).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(long long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned long long).name()) != 0 &&
		strcmp(typeid(Type).name(), typeid(unsigned __int64).name()) != 0)
	{
		cout << "\033[1;31m【错误】基数排序函数暂时无法对该类型的数据进行排序\033[0m" << endl;
		return;
	}

	//数据重构
	node* chain_start = nullptr;
	node* chain_end = nullptr;
	if (type == 0)
	{
		chain_start = new node;
		chain_start->prior = nullptr;
		chain_start->next = nullptr;
		chain_start->element = ptr0->elements[0];
		node* chain_scan = chain_start;
		for (long long i = 1; i <= ptr0->length - 1; i++)
		{
			chain_scan->next = new node;
			chain_scan->next->prior = chain_scan;
			chain_scan->next->next = nullptr;
			chain_scan = chain_scan->next;
			chain_scan->element = ptr0->elements[i];
		}
		chain_end = chain_scan;
		delete[] ptr0->elements;
	}
	else
	{
		chain_start = ptr1->first;
		chain_end = ptr1->end;
	}

	//计算最长位数
	int max_length = 1;
	node* chain_scan = chain_start;
	while (chain_scan != nullptr)
	{
		Type temp = chain_scan->element;
		if (temp < 0)
			temp = -temp;
		int scan_length = 1;
		while (temp >= 10)
		{
			temp = temp / 10;
			scan_length = scan_length + 1;
		}
		if (scan_length > max_length)
			max_length = scan_length;
		chain_scan = chain_scan->next;
	}

	//分割负数序列与正数序列
	node* chain_startA = nullptr;//   -
	node* chain_endA = nullptr;
	node* chain_startB = nullptr;//   +
	node* chain_endB = nullptr;
	while (chain_start != nullptr)
	{
		chain_scan = chain_start;
		chain_start = chain_start->next;
		if (chain_start != nullptr)
			chain_start->prior = nullptr;
		chain_scan->next = nullptr;
		if (chain_scan->element < 0)
		{
			if (chain_startA == nullptr)
			{
				chain_startA = chain_scan;
				chain_endA = chain_scan;
			}
			else
			{
				chain_scan->prior = chain_endA;
				chain_endA->next = chain_scan;
				chain_endA = chain_scan;
			}
		}
		else
		{
			if (chain_startB == nullptr)
			{
				chain_startB = chain_scan;
				chain_endB = chain_scan;
			}
			else
			{
				chain_scan->prior = chain_endB;
				chain_endB->next = chain_scan;
				chain_endB = chain_scan;
			}
		}
	}

	//对正数部分进行基数排序
	node** bucket_start = new node*[10];
	for (int i = 0; i <= 9; i++)
		bucket_start[i] = nullptr;
	node** bucket_end = new node*[10];
	for (int i = 0; i <= 9; i++)
		bucket_end[i] = nullptr;
	for (int loop_times = 1; loop_times <= max_length; loop_times++)
	{
		while (chain_startB != nullptr)
		{
			chain_scan = chain_startB;
			chain_startB = chain_startB->next;
			if (chain_startB != nullptr)
				chain_startB->prior = nullptr;
			chain_scan->next = nullptr;
			Type temp = chain_scan->element;
			for (int i = 2; i <= loop_times; i++)
				temp = temp / 10;
			if (bucket_start[temp % 10] == nullptr)
			{
				bucket_start[temp % 10] = chain_scan;
				bucket_end[temp % 10] = chain_scan;
			}
			else
			{
				chain_scan->prior = bucket_end[temp % 10];
				bucket_end[temp % 10]->next = chain_scan;
				bucket_end[temp % 10] = chain_scan;
			}
		}
		for (int i = 0; i <= 9; i++)
		{
			if (bucket_start[i] != nullptr)
			{
				if (chain_startB == nullptr)
				{
					chain_startB = bucket_start[i];
					chain_endB = bucket_end[i];
				}
				else
				{
					chain_endB->next = bucket_start[i];
					bucket_start[i]->prior = chain_endB;
					chain_endB = bucket_end[i];
				}
				bucket_start[i] = nullptr;
				bucket_end[i] = nullptr;
			}
		}
	}
	//对负数部分进行基数排序
	for (int loop_times = 1; loop_times <= max_length; loop_times++)
	{
		while (chain_startA != nullptr)
		{
			chain_scan = chain_startA;
			chain_startA = chain_startA->next;
			if (chain_startA != nullptr)
				chain_startA->prior = nullptr;
			chain_scan->next = nullptr;
			Type temp = chain_scan->element;
			temp = -temp;
			for (int i = 2; i <= loop_times; i++)
				temp = temp / 10;
			int bucket_seq = 9 - (temp % 10);
			if (bucket_start[bucket_seq] == nullptr)
			{
				bucket_start[bucket_seq] = chain_scan;
				bucket_end[bucket_seq] = chain_scan;
			}
			else
			{
				chain_scan->prior = bucket_end[bucket_seq];
				bucket_end[bucket_seq]->next = chain_scan;
				bucket_end[bucket_seq] = chain_scan;
			}
		}
		for (int i = 0; i <= 9; i++)
		{
			if (bucket_start[i] != nullptr)
			{
				if (chain_startA == nullptr)
				{
					chain_startA = bucket_start[i];
					chain_endA = bucket_end[i];
				}
				else
				{
					chain_endA->next = bucket_start[i];
					bucket_start[i]->prior = chain_endA;
					chain_endA = bucket_end[i];
				}
				bucket_start[i] = nullptr;
				bucket_end[i] = nullptr;
			}
		}
	}
	if (chain_startA == nullptr && chain_startB != nullptr)
	{
		chain_start = chain_startB;
		chain_end = chain_endB;
	}
	if (chain_startB == nullptr && chain_startA != nullptr)
	{
		chain_start = chain_startA;
		chain_end = chain_endA;
	}
	if (chain_startA != nullptr && chain_startB != nullptr)
	{
		chain_endA->next = chain_startB;
		chain_startB->prior = chain_endA;
		chain_start = chain_startA;
		chain_end = chain_endB;
	}
	delete[] bucket_start;
	delete[] bucket_end;

	//数据重构
	if (type == 0)
	{
		ptr0->elements = new Type[ptr0->total]();
		long long chain_count = 0;
		while (chain_start != nullptr)
		{
			chain_scan = chain_start;
			chain_start = chain_start->next;
			if (chain_start != nullptr)
				chain_start->prior = nullptr;
			chain_scan->next = nullptr;
			ptr0->elements[chain_count] = chain_scan->element;
			delete chain_scan;
			chain_count = chain_count + 1;
		}
	}
	else
	{
		ptr1->first = chain_start;
		ptr1->end = chain_end;
	}

	if (seq == 1)//从大到小排序	
		Reverse(1, Listlength());
	return;
}

template<typename Type>
void LIST<Type>::Sort(const int seq)
{
	if (Listlength() <= 15)
		D_i_sort(seq);
	else
		Q_sort(seq);
	return;
}

template<typename Type>
void LIST<Type>::Disarrange()
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type == 0)
	{
		if (ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr0->length == 1)
			return;

		std::random_device rd;
		std::default_random_engine e(rd());
		for (long long i = 2; i <= Listlength(); i++)
		{
			std::uniform_int_distribution<long long> LONGLONG(0, i - 1);
			long long num = LONGLONG(e);
			Type temp = ptr0->elements[num];
			ptr0->elements[num] = ptr0->elements[i - 1];
			ptr0->elements[i - 1] = temp;
		}
		return;
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0)//链表为空
		{
			cout << "\033[1;31m【错误】表中没有任何元素\033[0m" << endl;
			return;
		}
		if (ptr1->num_elements == 1)
			return;

		std::random_device rd;
		std::default_random_engine e(rd());
		node* scan = ptr1->first->next;
		for (long long i = 2; i <= Listlength(); i++)
		{
			std::uniform_int_distribution<long long> LONGLONG(0, i - 1);
			long long num = LONGLONG(e);
			node* exchange = scan;
			for (long long i1 = num; i1 > 0; i1--)
				exchange = exchange->prior;

			Type temp = exchange->element;
			exchange->element = scan->element;
			scan->element = temp;
			scan = scan->next;
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	type = -1;
	ptr0 = nullptr;
	ptr1 = nullptr;
	return;
}

template<typename Type>
Type LIST<Type>::operator[](const long long a) const
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return static_cast<Type>(0);
	}
	if (type == 0)//0为线性表，1为链表
	{
		if (a <= -1 || a > ptr0->length - 1)
		{
			cout << "\033[1;31m【错误】要输出的元素的序号错误\033[0m" << endl;
			return static_cast<Type>(0);
		}
		return ptr0->elements[a];
	}
	if (type == 1)
	{
		if (ptr1->num_elements == 0 || a <= -1 || a > ptr1->num_elements - 1)
		{
			cout << "\033[1;31m【错误】要输出的元素的序号错误\033[0m" << endl;
			return static_cast<Type>(0);
		}
		node* temp = nullptr;
		if (a == Listlength() - 1)
			temp = ptr1->end;
		else
		{
			temp = ptr1->first;
			long long i = 0;
			while (i != a)
			{
				temp = temp->next;
				i = i + 1;
			}
		}
		return temp->element;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return static_cast<Type>(0);
}

template<typename Type>
void LIST<Type>::operator+=(const LIST& a)
{
	if ((type == 0 && ptr0 == nullptr) || (type == 1 && ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return;
	}
	if (type != 0 && type != 1)
	{
		cout << "\033[1;31m【错误】'+='号左边的表的类型有错误，无法执行任何操作，正在退出函数\033[0m" << endl;
		return;
	}
	if (a.type != 0 && a.type != 1)
	{
		cout << "\033[1;31m【错误】'+='号右边的表的类型有错误，无法执行任何操作，正在退出函数\033[0m" << endl;
		return;
	}
	if (type != a.type)
	{
		cout << "\033[1;31m【错误】'+='号两边的表的类型不同，";
		if (type == 0)
			cout << "‘+=’号左边的表是线性表，但是";
		if (type == 1)
			cout << "‘+=’号左边的表是链表，但是";
		if (a.type == 0)
			cout << "'+='号右边的表是线性表";
		if (a.type == 1)
			cout << "‘+=’号右边的表是链表";
		cout << "。无法执行任何操作，正在退出函数\033[0m" << endl;
		return;
	}

	if (type == 0)
	{
		if (a.ptr0->length == 0)
			return;
		long long backup = ptr0->length;
		ptr0->length = ptr0->length + a.ptr0->length;
		bool move = 0;
		while (ptr0->total < ptr0->length)
		{
			ptr0->total = ptr0->total + TABLE_DELTA;
			move = 1;
		}
		if (move == 1)
		{
			Type* T = new Type[ptr0->total]();
			memmove_s(T, sizeof(Type) * (backup + 1), ptr0->elements, sizeof(Type) * backup);
			delete[] ptr0->elements;
			ptr0->elements = T;
		}

		long long i = backup;
		for (long long k = 1; k <= a.ptr0->length; k++)
		{
			ptr0->elements[i] = a.ptr0->elements[k - 1];
			i = i + 1;
		}
		return;
	}
	if (type == 1)
	{
		if (a.ptr1->num_elements == 0)
			return;
		long long count = ptr1->num_elements;
		ptr1->num_elements = ptr1->num_elements + a.ptr1->num_elements;

		LIST::node* temp = ptr1->end;
		LIST::node* start = a.ptr1->first;
		LIST::node* end = a.ptr1->end;
		while (start != end)
		{
			LIST::node* temp_x = new LIST::node;
			temp_x->element = start->element;
			temp_x->prior = temp;
			temp->next = temp_x;
			temp = temp->next;
			start = start->next;
		}
		LIST::node* temp_x = new LIST::node;
		temp_x->element = start->element;
		temp_x->prior = temp;
		temp_x->next = nullptr;
		temp->next = temp_x;
		temp = temp->next;
		ptr1->end = temp;

		if (count == 0)
		{
			LIST::node* tempx = ptr1->first;
			LIST::node* tempy = tempx->next;
			tempy->prior = nullptr;
			ptr1->first = tempy;
			delete tempx;
		}
		return;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return;
}

template<typename Type>
void LIST<Type>::operator+=(const Type a)
{
	ListinsertR(Listlength(), a);
	return;
}

template<typename Type>
ostream& operator<<(ostream& os, const LIST<Type>& a)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return os;
	}
	bool c_tab = true;
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
		c_tab = false;
	}
	if (a.type == 0)//0为线性表，1为链表
	{
		if (a.ptr0 == nullptr || a.ptr0->length == 0)
		{
			os << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return os;
		}
		long long i = 1;
		for (i = 1; i <= a.ptr0->length - 1; i++)
		{
			os << a.ptr0->elements[i - 1];
			if (c_tab == true)
				os << "   ";
		}
		os << a.ptr0->elements[i - 1];
		return os;
	}
	if (a.type == 1)
	{
		if (a.ptr1 == nullptr || a.ptr1->num_elements == 0)
		{
			os << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return os;
		}
		struct LIST<Type>::node* start = a.ptr1->first;
		struct LIST<Type>::node* end = a.ptr1->end;
		while (start != end)
		{
			os << start->element;
			start = start->next;
			if (c_tab == true)
				os << "   ";
		}
		os << start->element;
		return os;
	}
	os << "\033[1;31m【错误】表的类型有错误，无法输出任何信息\033[0m" << endl;
	return os;
}

template<typename Type>
fstream& operator<<(fstream& fs, const LIST<Type>& a)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return fs;
	}
	if (!fs)
	{
		cout << "\033[1;31m【错误】文件路径下的文件无法打开，无法执行任何操作\033[0m" << endl;
		return fs;
	}
	bool c_tab = true;
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
		c_tab = false;
	}
	if (a.type == 0)//0为线性表，1为链表
	{
		if (a.ptr0 == nullptr || a.ptr0->length == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return fs;
		}
		long long i = 1;
		for (i = 1; i <= a.ptr0->length - 1; i++)
		{
			fs << a.ptr0->elements[i - 1];
			if (c_tab == true)
				fs << "   ";
		}
		fs << a.ptr0->elements[i - 1];
		return fs;
	}
	if (a.type == 1)
	{
		if (a.ptr1 == nullptr || a.ptr1->num_elements == 0)
		{
			cout << "\033[1;31m【错误】没有可供输出的元素\033[0m" << endl;
			return fs;
		}
		struct LIST<Type>::node* start = a.ptr1->first;
		struct LIST<Type>::node* end = a.ptr1->end;
		while (start != end)
		{
			fs << start->element;
			start = start->next;
			if (c_tab == true)
				fs << "   ";
		}
		fs << start->element;
		return fs;
	}
	cout << "\033[1;31m【错误】表的类型有错误，无法输出任何信息\033[0m" << endl;
	return fs;
}

template<typename Type>
istream& operator>>(istream& is, LIST<Type>& a)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return is;
	}

	if (a.type == 0 || a.type == 1)
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
			cout << "【提示】请输入" << typeid(Type).name() << "类型的数据：" << endl;
		else
			cout << "【提示】请输入" << typeid(Type).name() << "类型的数据，使用空格分开相邻的两个数字：" << endl;

		LIST<char> INPUT_STREAM(3);
		bool start_find = false;
		bool end_find = false;
		bool str_finish = false;
		char STREAM_TEMP_A = '\0';
		char STREAM_TEMP_B = '\0';
		is.get(STREAM_TEMP_A);
		while ((int)STREAM_TEMP_A != 10)
		{
			is.get(STREAM_TEMP_B);
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据直接插入
			{
				a.ListinsertR(a.Listlength(), static_cast<Type>(STREAM_TEMP_A));
				a.Smart_expand();
				STREAM_TEMP_A = STREAM_TEMP_B;
				continue;
			}

			if (STREAM_TEMP_A != ' ' && STREAM_TEMP_A != '	')//发现字符串头
			{
				INPUT_STREAM += STREAM_TEMP_A;
				INPUT_STREAM.Smart_expand();
				start_find = true;
			}
			if (start_find == true && (STREAM_TEMP_A == ' ' || STREAM_TEMP_A == '	'))//发现字符串尾
			{
				end_find = true;
			}
			if ((int)STREAM_TEMP_B == 10)//输入流扫描完毕
			{
				end_find = true;
			}
			if (start_find == true && end_find == true)//凑齐了字符串头和字符串尾
			{
				start_find = false;
				end_find = false;
				str_finish = true;
			}
			if (str_finish == true)//凑齐了字符串头和字符串尾
			{
				char* converted_char = INPUT_STREAM.Char_array(false);
				Type converted = a.DATA_TYPE_CONVERT(converted_char);
				delete[] converted_char;
				a.ListinsertR(a.Listlength(), converted);
				a.Smart_expand();

				str_finish = false;
				INPUT_STREAM.Smart_shrink(true);
			}
			STREAM_TEMP_A = STREAM_TEMP_B;
		}
		if (a.type == 0)
			a.Listshrink();
		return is;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return is;
}

template<typename Type>
fstream& operator>>(fstream& fs, LIST<Type>& a)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return fs;
	}

	if (a.type == 0 || a.type == 1)
	{
		LIST<char> INPUT_STREAM(3);
		bool start_find = false;
		bool end_find = false;
		bool str_finish = false;
		char STREAM_TEMP_A = '\0';
		char STREAM_TEMP_B = '\0';
		fs.get(STREAM_TEMP_A);
		while (!fs.eof())
		{
			fs.get(STREAM_TEMP_B);
			if (strcmp(typeid(Type).name(), typeid(char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char8_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(unsigned char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(signed char).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__int8).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char16_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(__wchar_t).name()) == 0 ||
				strcmp(typeid(Type).name(), typeid(char32_t).name()) == 0)//char或类char数据直接插入
			{
				a.ListinsertR(a.Listlength(), static_cast<Type>(STREAM_TEMP_A));
				a.Smart_expand();
				STREAM_TEMP_A = STREAM_TEMP_B;
				continue;
			}
			if (STREAM_TEMP_A != ' ' && STREAM_TEMP_A != '	')//发现字符串头
			{
				INPUT_STREAM += STREAM_TEMP_A;
				INPUT_STREAM.Smart_expand();
				start_find = true;
			}
			if (start_find == true && (STREAM_TEMP_A == ' ' || STREAM_TEMP_A == '	'))//发现字符串尾
			{
				end_find = true;
			}
			if ((int)STREAM_TEMP_B == 10)//输入流扫描完毕
			{
				end_find = true;
			}
			if (start_find == true && end_find == true)//凑齐了字符串头和字符串尾
			{
				start_find = false;
				end_find = false;
				str_finish = true;
			}
			if (str_finish == true)//凑齐了字符串头和字符串尾
			{
				char* converted_char = INPUT_STREAM.Char_array(false);
				Type converted = a.DATA_TYPE_CONVERT(converted_char);
				delete[] converted_char;
				a.ListinsertR(a.Listlength(), converted);
				a.Smart_expand();

				str_finish = false;
				INPUT_STREAM.Smart_shrink(true);
			}
			STREAM_TEMP_A = STREAM_TEMP_B;
		}
		if (a.type == 0)
			a.Listshrink();
		return fs;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return fs;
}

template<typename Type>
bool operator==(const LIST<Type>& a, const LIST<Type>& b)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (a.type != 0 && a.type != 1)
	{
		cout << "\033[1;31m【错误】'=='号左边的表的类型有错误\033[0m" << endl;
		return false;
	}
	if (b.type != 0 && b.type != 1)
	{
		cout << "\033[1;31m【错误】'=='号右边的表的类型有错误\033[0m" << endl;
		return false;
	}
	if (a.type != b.type)
		return false;
	if (a.type == 0)
	{
		if (a.ptr0->length != b.ptr0->length)
			return false;
		if (a.ptr0->total != b.ptr0->total)
			return false;
		for (long long i = 1; i <= a.ptr0->length; i++)
		{
			if (a.ptr0->elements[i - 1] != b.ptr0->elements[i - 1])
				return false;
		}
		return true;
	}
	if (a.type == 1)
	{
		if (a.ptr1->num_elements != b.ptr1->num_elements)
			return false;
		struct LIST<Type>::node* a_start = a.ptr1->first;
		struct LIST<Type>::node* a_end = a.ptr1->end;
		struct LIST<Type>::node* b_start = b.ptr1->first;
		while (a_start != a_end)
		{
			if (a_start->element != b_start->element)
				return false;
			a_start = a_start->next;
			b_start = b_start->next;
		}
		if (a_start->element != b_start->element)
			return false;
		return true;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return false;
}

template<typename Type>
bool operator!=(const LIST<Type>& a, const LIST<Type>& b)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return false;
	}
	if (a == b)
		return false;
	else
		return true;
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return false;
}

template<typename Type>
const LIST<Type> operator+(const LIST<Type>& a, const LIST<Type>& b)
{
	if ((a.type == 0 && a.ptr0 == nullptr) || (a.type == 1 && a.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return LIST<Type>(2);
	}
	if ((b.type == 0 && b.ptr0 == nullptr) || (b.type == 1 && b.ptr1 == nullptr))
	{
		cout << "\033[1;31m【错误】表不存在，无法执行任何操作\033[0m" << endl;
		return LIST<Type>(2);
	}
	if (a.type != 0 && a.type != 1)
	{
		cout << "\033[1;31m【错误】'+'号左边的表的类型有错误，无法执行任何操作，正在退出函数\033[0m" << endl;
		return LIST<Type>(2);
	}
	if (b.type != 0 && b.type != 1)
	{
		cout << "\033[1;31m【错误】'+'号右边的表的类型有错误，无法执行任何操作，正在退出函数\033[0m" << endl;
		return LIST<Type>(2);
	}
	if (a.type != b.type)
	{
		cout << "\033[1;31m【错误】'+'号两边的表的类型不同，";
		if (a.type == 0)
			cout << "‘+’号左边的表是线性表，但是";
		if (a.type == 1)
			cout << "‘+’号左边的表是链表，但是";
		if (b.type == 0)
			cout << "'+'号右边的表是线性表";
		if (b.type == 1)
			cout << "‘+’号右边的表是链表";
		cout << "。无法执行任何操作，正在退出函数\033[0m" << endl;
		return LIST<Type>(2);
	}

	if (a.type == 0)
	{
		LIST TEMP(a);
		if (b.ptr0->length == 0)
			return TEMP;
		TEMP.ptr0->length = a.ptr0->length + b.ptr0->length;
		bool move = 0;
		while (TEMP.ptr0->total < TEMP.ptr0->length)
		{
			TEMP.ptr0->total = TEMP.ptr0->total + LIST<Type>::TABLE_DELTA;
			move = 1;
		}
		if (move == 1)
		{
			Type* T = new Type[TEMP.ptr0->total]();
			memmove_s(T, sizeof(Type) * (a.ptr0->length + 1), TEMP.ptr0->elements, sizeof(Type) * a.ptr0->length);
			delete[] TEMP.ptr0->elements;
			TEMP.ptr0->elements = T;
		}

		long long i = a.ptr0->length;
		for (long long k = 1; k <= b.ptr0->length; k++)
		{
			TEMP.ptr0->elements[i] = b.ptr0->elements[k - 1];
			i = i + 1;
		}
		return TEMP;
	}
	if (a.type == 1)
	{
		LIST TEMP(a);
		if (b.ptr1->num_elements == 0)
			return TEMP;
		TEMP.ptr1->num_elements = a.ptr1->num_elements + b.ptr1->num_elements;

		struct LIST<Type>::node* temp = TEMP.ptr1->end;
		struct LIST<Type>::node* start = b.ptr1->first;
		struct LIST<Type>::node* end = b.ptr1->end;
		while (start != end)
		{
			struct LIST<Type>::node* temp_x = new struct LIST<Type>::node;
			temp_x->element = start->element;
			temp_x->prior = temp;
			temp->next = temp_x;
			temp = temp->next;
			start = start->next;
		}
		struct LIST<Type>::node* temp_x = new struct LIST<Type>::node;
		temp_x->element = start->element;
		temp_x->prior = temp;
		temp_x->next = nullptr;
		temp->next = temp_x;
		temp = temp->next;
		TEMP.ptr1->end = temp;

		if (a.ptr1->num_elements == 0)
		{
			struct LIST<Type>::node* tempx = TEMP.ptr1->first;
			struct LIST<Type>::node* tempy = tempx->next;
			tempy->prior = nullptr;
			TEMP.ptr1->first = tempy;
			delete tempx;
		}
		return TEMP;
	}
	cout << "\033[1;31m【错误】程序发生原因未知的严重错误，请重新启动程序\033[0m" << endl;
	return LIST<Type>(2);
}

template<typename Type>
const LIST<Type> operator+(const LIST<Type>& a, const Type b)
{
	LIST TEMP(a);
	TEMP += b;
	return TEMP;
}

#endif