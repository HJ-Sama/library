#pragma once
#include "stdafx.h"  
#include<iostream>
#include<vector>
#include"Library.h"
#include"windows.h"
#include<stdlib.h>
using namespace std;
void addBookTest()
{
	vector<Book> t;
	for (int i = 1; i <= 100; i++)
	{
		char a[9];
		sprintf(a , "%08d", i);
		char b[] = "7-5618-0795-3";
		char c[] = "计算机基础实用教程";
		char d[] = "张天侠";
		char e[] = "天津大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 101; i <= 200; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5027-3535-6";
		char c[] = "计算机基础与应用";
		char d[] = "马淑华等";
		char e[] = "海洋出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 201; i <= 300; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "978-7-5612-5439-4";
		char c[] = "2D / 3D计算机绘图教程";
		char d[] = "王淑侠";
		char e[] = "西北工业大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 301; i <= 400; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-302-06074-6";
		char c[] = "3D Flash制作技术";
		char d[] = "曹春海";
		char e[] = "清华大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 401; i <= 500; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 501; i <= 600; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "中图I561. 4";
		char c[] = "200个趣味数学故事";
		char d[] = "享利. E. 杜登尼";
		char e[] = "湖南人民出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 601; i <= 700; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5084-0755-5";
		char c[] = "3dsmax4创作效果百例";
		char d[] = "张冶, 周田朋";
		char e[] = "中国水利水电出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 701; i <= 800; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7302027668";
		char c[] = "离散数学结构";
		char d[] = "Bernard,Kolman";
		char e[] = "清华大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 801; i <= 900; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5046-3201-5";
		char c[] = "2.16米天文望远镜工程文集";
		char d[] = "苏定强";
		char e[] = "中国科学技术出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 901; i <= 1000; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1001; i <= 1100; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5618-0795-3";
		char c[] = "计算机基础实用教程";
		char d[] = "张天侠";
		char e[] = "天津大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1101; i <= 1200; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "978-7-5612-5439-4";
		char c[] = "2D / 3D计算机绘图教程";
		char d[] = "王淑侠";
		char e[] = "西北工业大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}

	for (int i = 1201; i <= 1300; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1301; i <= 1400; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1401; i <= 1500; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7302027668";
		char c[] = "离散数学结构";
		char d[] = "Bernard,Kolman";
		char e[] = "清华大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1501; i <= 1600; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1601; i <= 1700; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	BookManager m1;
	m1.SaveToFile(t);
}
void addBookTest1()
{
	vector<Book> t;
	for (int i = 1; i <= 16; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5618-0795-3";
		char c[] = "计算机基础实用教程";
		char d[] = "张天侠";
		char e[] = "天津大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 17; i <= 32; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5027-3535-6";
		char c[] = "计算机基础与应用";
		char d[] = "马淑华等";
		char e[] = "海洋出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 33; i <= 48; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "978-7-5612-5439-4";
		char c[] = "2D / 3D计算机绘图教程";
		char d[] = "王淑侠";
		char e[] = "西北工业大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 49; i <= 64; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-302-06074-6";
		char c[] = "3D Flash制作技术";
		char d[] = "曹春海";
		char e[] = "清华大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 65; i <= 80; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 81; i <= 96; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "中图I561. 4";
		char c[] = "200个趣味数学故事";
		char d[] = "享利. E. 杜登尼";
		char e[] = "湖南人民出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 97; i <= 120; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5084-0755-5";
		char c[] = "3dsmax4创作效果百例";
		char d[] = "张冶, 周田朋";
		char e[] = "中国水利水电出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 121; i <= 180; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7302027668";
		char c[] = "离散数学结构";
		char d[] = "Bernard,Kolman";
		char e[] = "清华大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 181; i <= 260; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5046-3201-5";
		char c[] = "2.16米天文望远镜工程文集";
		char d[] = "苏定强";
		char e[] = "中国科学技术出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	/*for (int i = 901; i <= 1000; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1001; i <= 1100; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5618-0795-3";
		char c[] = "计算机基础实用教程";
		char d[] = "张天侠";
		char e[] = "天津大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1101; i <= 1200; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "978-7-5612-5439-4";
		char c[] = "2D / 3D计算机绘图教程";
		char d[] = "王淑侠";
		char e[] = "西北工业大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}

	for (int i = 1201; i <= 1300; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1301; i <= 1400; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "9787810648110";
		char c[] = "5年高考3年模拟(高二数学.下)";
		char d[] = "曲一线";
		char e[] = "首都师范大学出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1501; i <= 1600; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}
	for (int i = 1601; i <= 1700; i++)
	{
		char a[9];
		sprintf(a, "%08d", i);
		char b[] = "7-5407-0335-0";
		char c[] = "5种暧昧:第八期毕业作品";
		char d[] = "鲁迅文学院";
		char e[] = "漓江出版社";
		int f = i;
		double g = 20.0;
		int h = 30;
		Book b1(a, b, c, d, f, e, g, h);
		t.push_back(b1);
	}*/
	BookManager m1;
	m1.SaveToFile(t);
}
bool checkFile()
{
	FILE *fp;
	fp = fopen("./users.txt","r");
	if (!fp)
	{
		fp = fopen("./users.txt", "w");
		fp = fopen("./record.txt", "w");
		fp = fopen("./historyRecord.txt", "w");
		fp = fopen("./reservationRecord.txt", "w");
		cout << "\n User 信 息 文 件 不 存 在"<<endl;
		cout << "\n 相 关 文 件 已 经 被 重 置" << endl;
		cout << "\n 损 失 信 息 无 法 找 回" << endl;
		return false;
	}
	fp = fopen("./record.txt", "r");
	if (!fp)
	{
		fp = fopen("./users.txt", "w");
		fp = fopen("./record.txt", "w");
		fp = fopen("./historyRecord.txt", "w");
		fp = fopen("./reservationRecord.txt", "w");
		cout << "\n Record 信 息 文 件 不 存 在" << endl;
		cout << "\n 相 关 文 件 已 经 被 重 置" << endl;
		cout << "\n 损 失 信 息 无 法 找 回" << endl;
		return false;
	}
	fp = fopen("./historyRecord.txt", "r");
	if (!fp)
	{
		fp = fopen("./users.txt", "w");
		fp = fopen("./record.txt", "w");
		fp = fopen("./historyRecord.txt", "w");
		fp = fopen("./reservationRecord.txt", "w");
		cout << "\n HistoryRecord 信 息 文 件 不 存 在" << endl;
		cout << "\n 相 关 文 件 已 经 被 重 置" << endl;
		cout << "\n 损 失 信 息 无 法 找 回" << endl;
		return false;
	}
	fp = fopen("./reservationRecord.txt", "r");
	if (!fp)
	{
		fp = fopen("./users.txt", "w");
		fp = fopen("./record.txt", "w");
		fp = fopen("./historyRecord.txt", "w");
		fp = fopen("./reservationRecord.txt", "w");
		cout << "\n ReservationRecord 信 息 文 件 不 存 在" << endl;
		cout << "\n 相 关 文 件 已 经 被 重 置" << endl;
		cout << "\n 损 失 信 息 无 法 找 回" << endl;
		return false;
	}

	return true;
}
int main()
{
	system("mode con cols=175 lines=35");//改变宽高
	//system("color fc");//改变颜色
	//addBookTest1();
	if (!checkFile()) {
		cout << " 相 关 文 件 不 全 ， 已 经 重 新 建 立 "<<endl;
	}

	Library l1;
	l1.Login();
	//l1.EnterUserDesk();
	//l1.EnterManagerDesk();

	return 0;
}
