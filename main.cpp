#include<iostream>
#include"TABLE.h"
#include"GRAPHS.h"
#include"TREES.h"

using namespace std;

void Showtype();
void Sort_test();

int main()
{
	/*
	TREE<char> A1(false, 1, false, true);
	A1.Tree_thread(2);
	A1.Postorder_A();
	A1.Info();
	*/

	//常用层序序列测试集
	//RA.DB.E.C..F.G..H.K..     AB..CDE....      ABE.CFG.D..H....IJ...    12.34....    1..
	//12...    1.234..5..6..      1234567........      -+/a*ef..b-......cd....     1.2.3.4..
	//+-/*/+-abcdefgh................     -.-.-.a..    +*-ab.-....cd....    *+*abc-.......d..

	/*
	LIST<int> A("", 0, false);
	A.Silence_T();
	for (long long i = 1; i <= 100; i++)
	{
		A.Clearlist();
		A.Listfill(2, 100, '1');
		//A.Sort(0);
		if (A.RB_TREE_search(A[i - 1]) != i)
			cout << "no" << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << A.RB_TREE_search(A[i - 1]) << "  " << i << "  " << A[i - 1] << "  " << A.Min() << "  " << A.Max();
		cout << endl;
	}
	cout << endl;
	*/

	
	GRAPH<int> A(true, true, false);
	//for (int a = 1; a <= 6; a++)
		//A.Add_vertex();
	//for (int a = 1; a <= 10; a++)
		//A.Add_line();
	//for (int a = 1; a <= 2; a++)
		//A.Delete_line();
	//for (int a = 1; a <= 1; a++)
		//A.Delete_vertex();
	A.Info();
	A.DFS_LE();
	A.BFS_LE();
	A.~GRAPH();
	A.~GRAPH();
	A.~GRAPH();
	//测试序列：
	//12,3;,,4 5,l;[,ooo     3,2;,;,;,,1       2'1;,,3'[1|']
	//典型错误序列：
	//1,2;;,3
	//无向图示例：
	//v1,v2,v3,v4,v5,v6,v7   v1'v2,v1'v3,v2'v4,v3'v5,v4'v6,v5'v6,v6'v7
	//v1,v2,v7,v4,v5,v6,v3,v8   v1'v2,v1'v3,v2'v4,v2'v5,v4'v8,v5'v8,v3'v6,v3'v7,v6'v7
	//v1,v2,v3,v4,v5   v1'v2,v1'v4,v3'v2,v3'v4,v3'v5,v5'v2
	//v1,v2,v3,v4,v5,v6   v1'v2,v2'v5,v5'v6,v6'v4,v4'v1,v3'v1,v3'v2,v3'v5,v3'v6,v3'v4
	//v1,v2,v3,v4,v5,v6   v1'v2'6,v2'v5'3,v5'v6'6,v6'v4'2,v4'v1'5,v3'v1'1,v3'v2'5,v3'v5'6,v3'v6'4,v3'v4'5
	//有向图示例：
	//v1,v2,v3   v1'v2,v1'v3,v2'v3
	//v1,v2,v3,v4   v1'v2,v1'v3,v3'v1,v3'v4,v4'v2,v4'v1,v4'v3
	//A,B,C,F,E,D   A'B,A'F,C'B,C'E,F'B,F'E,E'A,E'B,D'E,D'C
	//v0,v1,v2,v3,v4,v5    v1'v2'5,v2'v3'50,v4'v3'20,v4'v5'60,v0'v5'100,v0'v4'30,v3'v5'10,v0'v2'10
	//1,2,3,4,5     1'2'10,2'3'1,3'4'4,4'3'6,5'3'9,2'5'2,5'2'3,4'1'7,1'5'5,5'4'2
	//v0,v1,v2     v0'v1'4,v0'v2'11,v1'v0'6,v1'v2'2,v2'v0'3
	//v0,v1,v2     v0'v1'6,v0'v2'13,v1'v0'10,v1'v2'4,v2'v0'5
	

	//字符串排序函数测试集
	//http.hello.com,www.test.com,bos.test.com,www.hello.com,ftp.hello.com,http.test.com,^,edu.princeton.cs,com.apple,
	//edu.princeton.cs,com.cnn,edu.princeton.cs.www,com.goole,edu.uva.cs,edu.princeton.ee,edu.uva.cs,edu.uva.cs,
	//edu.princeton.cs,edu.uva.cs,com.adobe

	//system("cls");

	cout << "\033[1;5;32m【提示】程序的所有代码已执行完毕，按下ENTER键退出程序\033[0m" << endl;
	cin.get();
	return 0;
}

void Showtype()
{
	cout << endl;
	cout << "1 byte:" << endl;
	cout << "bool		" << typeid(bool).name() << endl;
	cout << "char		" << typeid(char).name() << endl;
	cout << "char8_t		" << typeid(char8_t).name() << endl;
	cout << "unsigned char	" << typeid(unsigned char).name() << endl;
	cout << "signed char	" << typeid(signed char).name() << endl;
	cout << "__int8		" << typeid(__int8).name() << endl;
	cout << endl;

	cout << "2 bytes:" << endl;
	cout << "char16_t	" << typeid(char16_t).name() << endl;
	cout << "__int16		" << typeid(__int16).name() << endl;
	cout << "short		" << typeid(short).name() << endl;
	cout << "unsigned short	" << typeid(unsigned short).name() << endl;
	cout << "wchar_t		" << typeid(wchar_t).name() << endl;
	cout << "__wchar_t	" << typeid(__wchar_t).name() << endl;
	cout << endl;

	cout << "4 bytes:" << endl;
	cout << "char32_t	" << typeid(char32_t).name() << endl;
	cout << "float		" << typeid(float).name() << endl;
	cout << "__int32		" << typeid(__int32).name() << endl;
	cout << "int		" << typeid(int).name() << endl;
	cout << "unsigned int	" << typeid(unsigned int).name() << endl;
	cout << "long		" << typeid(long).name() << endl;
	cout << "unsigned long	" << typeid(unsigned long).name() << endl;
	cout << endl;

	cout << "8 bytes:" << endl;
	cout << "double			" << typeid(double).name() << endl;
	cout << "__int64			" << typeid(__int64).name() << endl;
	cout << "long double		" << typeid(long double).name() << endl;
	cout << "long long		" << typeid(long long).name() << endl;
	cout << "unsigned long long	" << typeid(unsigned long long).name() << endl;
	cout << "unsigned __int64	" << typeid(unsigned __int64).name() << endl;
	cout << endl;

	return;
}

void Sort_test()
{
	//排序函数测试代码与测试数据集
	LIST<short> A(3);
	A.Listfill(2, 20, 70);
	LIST<short> B = A;
	bool print = true;
	if (print == true)
		cout << A << endl;
	cout << "************************************SAFE**********LINE************************************" << endl;

	cout << "直接插入排序：" << endl;
	steady_clock::time_point beginTime = steady_clock::now();
	A.D_i_sort(0);//直接插入排序
	steady_clock::time_point endTime = steady_clock::now();
	cout << "直接插入排序运行时间为：" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "折半插入排序：" << endl;
	beginTime = steady_clock::now();
	A.B_i_sort(0);//折半插入排序
	endTime = steady_clock::now();
	cout << "折半插入排序运行时间为：" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "2路插入排序：" << endl;
	beginTime = steady_clock::now();
	A.Two_i_sort(0);//2路插入排序
	endTime = steady_clock::now();
	cout << "2路插入排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "表插入排序：" << endl;
	beginTime = steady_clock::now();
	A.T_i_sort(0);//表插入排序
	endTime = steady_clock::now();
	cout << "表插入排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "希尔排序：" << endl;
	beginTime = steady_clock::now();
	A.S_sort(0);//希尔排序
	endTime = steady_clock::now();
	cout << "希尔排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "起泡排序：" << endl;
	beginTime = steady_clock::now();
	A.B_sort(0);//起泡排序
	endTime = steady_clock::now();
	cout << "起泡排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "快速排序：" << endl;
	beginTime = steady_clock::now();
	A.Q_sort(0);//快速排序
	endTime = steady_clock::now();
	cout << "快速排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "简单选择排序：" << endl;
	beginTime = steady_clock::now();
	A.S_s_sort(0);//简单选择排序
	endTime = steady_clock::now();
	cout << "简单选择排序运行时间为：" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "树形选择排序：" << endl;
	beginTime = steady_clock::now();
	A.T_s_sort(0);//树形选择排序
	endTime = steady_clock::now();
	cout << "树形选择排序运行时间为：" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "堆排序：" << endl;
	beginTime = steady_clock::now();
	A.H_sort(0);//堆排序
	endTime = steady_clock::now();
	cout << "堆排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "归并排序：" << endl;
	beginTime = steady_clock::now();
	A.M_sort(0);//归并排序
	endTime = steady_clock::now();
	cout << "归并排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "基数排序：" << endl;
	beginTime = steady_clock::now();
	//A.R_sort(0);//基数排序
	endTime = steady_clock::now();
	cout << "基数排序运行时间为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "速度基准：" << endl;
	beginTime = steady_clock::now();
	A.Sort(0);//最好的排序函数
	endTime = steady_clock::now();
	cout << "速度基准为：\t" << duration_cast<milliseconds>(endTime - beginTime).count() / 1000 << "秒\t";
	cout << duration_cast<milliseconds>(endTime - beginTime).count() % 1000 << "毫秒\t";
	cout << duration_cast<microseconds>(endTime - beginTime).count() % 1000 << "微秒" << endl;
	if (print == true)
		cout << A;
	A = B;

	cout << "************************************SAFE**********LINE************************************" << endl;
	A.Info();
	//2 1 3           2 3 1
	//5 42 3 2 1 0 -100 -2 -3 -4 -5 -8
	//1 2 3 4 5 -2 6 7 -1 8 9
	//9 8 7 6 5 4 3 2 1 0 -1
	//1 4 6 7 6 6 7 6 8 6 6
	//1 38 65 97 76 13 27 100
	//49 38 65 97 76 13 27 49

	return;
}
