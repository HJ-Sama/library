#include "stdafx.h"  
#include<iostream>
#include<fstream>
#include <iomanip>
#include"Manager.h"

bool isLegal(char a[], int len)
{
	if (strlen(a) >= len)
	{
		cout << "超出规定长度，请重新输入：" << endl;
		return false;
	}
	else
		return true;
}

using namespace std;

void BookManager::Add(Book book)
{
	FILE *fp;
	if ((fp = fopen("./Books.txt", "rb+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, 0, 2);
	fwrite(&book, sizeof(Book), 1, fp);
	fclose(fp);
}
int BookManager::LoadFromFile(vector<Book> *bookVector,int startID,int n)
{
	FILE *fp;
	if ((fp = fopen("./Books.txt", "rb+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, 0, 2);
	int len = ftell(fp);    //得到文件中所有文本的长度
	int count = len / sizeof(Book);
	if (count - startID < 0) {  return 0; }
	rewind(fp);     //重新恢复位置指针的位置，回到文件的开头
	fseek(fp,(startID-1)*sizeof(Book),0);
	Book temp;
	if (count - startID < n-1)
	{
		n = count - (count / 100) * 100;
	}
	if (n==100&&count % 100 == 0)n = 100;
	for (int i = 0; i !=  n; i++)
		{
			fread(&temp, sizeof(Book), 1, fp);
			bookVector->push_back(temp);
		}
	fclose(fp);
	return count;
}
void BookManager::SaveToFile(vector<Book> bookVector)
{
	FILE *fp;
	if ((fp = fopen("./Books.txt", "rb+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, 0, 2);
	for (int i = 0; i != bookVector.size(); i++)
	{
		fwrite(&bookVector[i], sizeof(Book), 1, fp);
	}
	fclose(fp);
}
void BookManager::Show(vector<Book> bookVector,int page)
{
	cout.setf(ios::left);
	cout << "** " << setw(6) << "序号";
	cout << "** " << setw(8) << "图书ID";
	cout << "** " << setw(18) << "图书ISBN";
	cout << "** " << setw(30) << "书名";
	cout << "** " << setw(18) << "种类";
	cout << "** " << setw(12) << "可借数量";
	cout << "** " << setw(17) << "作者 ";
	cout << "** " << setw(17) << "出版社 ";
	cout << "** " << setw(6) << "价 格" << endl;
	if (!bookVector.empty())
	{
		if (bookVector.size() <= 100)
		{
			if (page % 5 == 0)page = 5;
			else page = page % 5;
		}
		int start = (page - 1) * 20;
		for (int i = start; i != start + 20; i++) {
			if (i > bookVector.size() - 1)					//若数据不足应停止读取，否则出错
			{
				cout.setf(ios::left);
				cout << "** " << setw(6) << i + 1;
				cout << "** " << setw(8) << " ";
				cout << "** " << setw(18) << " ";
				cout << "** " << setw(30) << " ";
				cout << "** " << setw(18) << " ";
				cout << "** " << setw(12) << " ";
				cout << "** " << setw(17) << " ";
				cout << "** " << setw(17) << " ";
				cout << "** " << setw(6) << " " << endl;
			}
			else {

				if (bookVector[i].getStatus())
				{
					cout.setf(ios::left);
					cout << "** " << setw(6) << i + 1;
					cout << "** " << setw(8) << bookVector[i].getID();
					cout << "** " << setw(18) << bookVector[i].getISBN();
					cout << "** " << setw(30) << bookVector[i].getName();
					int t = bookVector[i].getType();
					t = t % 22;
					cout << "** " << setw(18) << bookKind[t];
					cout << "** " << setw(12) << bookVector[i].getCurrentCount() - bookVector[i].getReserve();
					cout << "** " << setw(17) << bookVector[i].getAuthor();
					cout << "** " << setw(17) << bookVector[i].getPublishing();
					cout << "** " << setw(6) << bookVector[i].getPrice() << endl;
				}
				else
				{
					cout.setf(ios::left);
					cout << "** " << setw(6) << i + 1;
					cout << "** " << setw(8) << bookVector[i].getID();
					cout << "** " << setw(18) << bookVector[i].getISBN();
					cout << "** " << setw(30) << bookVector[i].getName();
					int t = bookVector[i].getType();
					t = t % 22;
					cout << "** " << setw(18) << bookKind[t];
					cout << "** " << setw(12) << "该书不可借";
					cout << "** " << setw(17) << bookVector[i].getAuthor();
					cout << "** " << setw(17) << bookVector[i].getPublishing();
					cout << "** " << setw(6) << bookVector[i].getPrice() << endl;
				}
			}
		}
	}
	else
	{
		cout <<  "没 有 相 关 信 息" << endl;
	}
}
void BookManager::Show(vector<Book> bookVector)
{
	cout.setf(ios::left);
	cout << "** " << setw(6) << "序号";
	cout << "** " << setw(8) << "图书ID";
	cout << "** " << setw(18) << "图书ISBN";
	cout << "** " << setw(30) << "书名";
	cout << "** " << setw(18) << "种类";
	cout << "** " << setw(12) << "可借数量";
	cout << "** " << setw(12) << "馆藏数量";
	cout << "** " << setw(17) << "作者 ";
	cout << "** " << setw(17) << "出版社 ";
	cout << "** " << setw(6) << "价 格" << endl;
	if (!bookVector.empty())
	{
		for (int i = 0; i != bookVector.size(); i++) {
			cout.setf(ios::left);
			cout << "** " << setw(6) << i + 1;
			cout << "** " << setw(8) << bookVector[i].getID();
			cout << "** " << setw(18) << bookVector[i].getISBN();
			cout << "** " << setw(30) << bookVector[i].getName();
			int t = bookVector[i].getType();
			t = t % 22;
			cout << "** " << setw(18) << bookKind[t];
			cout << "** " << setw(12) << bookVector[i].getCurrentCount() - bookVector[i].getReserve();
			cout << "** " << setw(12) << bookVector[i].getOCount();
			cout << "** " << setw(17) << bookVector[i].getAuthor();
			cout << "** " << setw(17) << bookVector[i].getPublishing();
			cout << "** " << setw(6) << bookVector[i].getPrice() << endl;

		}
	}
	else
	{
		cout << "没 有 相 关 信 息" << endl;
	}
}
void BookManager::ManagerShow(vector<Book> bookVector, int page)
{
	cout.setf(ios::left);
	cout << "** " << setw(6) << "序号";
	cout << "** " << setw(8) << "图书ID";
	cout << "** " << setw(18) << "图书ISBN";
	cout << "** " << setw(30) << "书名";
	cout << "** " << setw(18) << "种类";
	cout << "** " << setw(12) << "可借数量";
	cout << "** " << setw(12) << "馆藏数量";
	cout << "** " << setw(17) << "作者 ";
	cout << "** " << setw(17) << "出版社 ";
	cout << "** " << setw(6) << "价 格" << endl;
	if (!bookVector.empty())
	{
		if (bookVector.size() <= 100)
		{
			if (page % 5 == 0)page = 5;
			else page = page % 5;
		}
		int start = (page - 1) * 20;
		for (int i = start; i != start + 20; i++) {
			if (i > bookVector.size() - 1)					//若数据不足应停止读取，否则出错
			{
				cout.setf(ios::left);
				cout << "** " << setw(6) << i + 1;
				cout << "** " << setw(8) << " ";
				cout << "** " << setw(18) << " ";
				cout << "** " << setw(30) << " ";
				cout << "** " << setw(18) << " ";
				cout << "** " << setw(12) << " ";
				cout << "** " << setw(12) << " ";
				cout << "** " << setw(17) << " ";
				cout << "** " << setw(17) << " ";
				cout << "** " << setw(6) << " " << endl;
			}
			else {

				if (bookVector[i].getStatus())
				{
					cout.setf(ios::left);
					cout << "** " << setw(6) << i + 1;
					cout << "** " << setw(8) << bookVector[i].getID();
					cout << "** " << setw(18) << bookVector[i].getISBN();
					cout << "** " << setw(30) << bookVector[i].getName();
					int t = bookVector[i].getType();
					t = t % 22;
					cout << "** " << setw(18) << bookKind[t];
					cout << "** " << setw(12) << bookVector[i].getCurrentCount() - bookVector[i].getReserve();
					cout << "** " << setw(12) << bookVector[i].getOCount();
					cout << "** " << setw(17) << bookVector[i].getAuthor();
					cout << "** " << setw(17) << bookVector[i].getPublishing();
					cout << "** " << setw(6) << bookVector[i].getPrice() << endl;
				}
				else
				{
					cout.setf(ios::left);
					cout << "** " << setw(6) << i + 1;
					cout << "** " << setw(8) << bookVector[i].getID();
					cout << "** " << setw(18) << bookVector[i].getISBN();
					cout << "** " << setw(30) << bookVector[i].getName();
					int t = bookVector[i].getType();
					t = t % 22;
					cout << "** " << setw(18) << bookKind[t];
					cout << "** " << setw(12) << "该书已删除";
					cout << "** " << setw(12) << "该书已删除";
					cout << "** " << setw(17) << bookVector[i].getAuthor();
					cout << "** " << setw(17) << bookVector[i].getPublishing();
					cout << "** " << setw(6) << bookVector[i].getPrice() << endl;
				}
			}
		}
	}
	else
	{
		cout << "没 有 相 关 信 息" << endl;
	}
}
void BookManager::Search(vector<Book> bookVector, vector<Book> *searchResult, char name[], char ISBN[], char author[], char publishing[])
{
	string s1(name);
	string s2(ISBN);
	string s3(author);
	string s4(publishing);
	for (int i = 0; i !=bookVector.size(); i++)
	{
		string n1(bookVector[i].getName());
		string n2(bookVector[i].getISBN());
		string n3(bookVector[i].getAuthor());
		string n4(bookVector[i].getPublishing());
		if ((n1.find(s1) != string::npos && n1 != "#") || (n2.find(s2) != string::npos && n2 != "#") || (n3.find(s3) != string::npos && n3 != "#") || (n4.find(s4) != string::npos && n4 != "#"))
		{
				searchResult->push_back(bookVector[i]);	
				if (searchResult->size() == 100)return;
		}
	}
}
void BookManager::Delete(vector<Book> &bookVector, int n, vector<Book> &changedBooks)
{
	if (bookVector[n - 1].getStatus())
	{
		bookVector[n - 1].setStatus(false);
		changedBooks.push_back(bookVector[n - 1]);
	}
	else
		cout << "该 书 已 不 存 在" << endl;
}
void BookManager::Change(vector<Book> &bookVector, int n,int changeCCount, vector<Book> &changedBooks)//n为要改变的书在容器中的序号，change为改变的数
{
	if (changeCCount > 0)	//加书，还需要更多判断在外部控制
	{
		if(!bookVector[n - 1].getStatus())
		bookVector[n - 1].setStatus(true);
		bookVector[n - 1].setCurrentCount(bookVector[n - 1].getCurrentCount() + changeCCount);
		changedBooks.push_back(bookVector[n - 1]);
	}
	else if (bookVector[n - 1].getStatus())
	{
		if (changeCCount <= 0 && (bookVector[n - 1].getCurrentCount() - bookVector[n - 1].getReserve())>=0)
		{
			bookVector[n - 1].setCurrentCount(bookVector[n - 1].getCurrentCount() + changeCCount);
			changedBooks.push_back(bookVector[n-1]);
		}
		else
		{
			cout << "该 书 现 存 数 量 不 足" << endl;
		}
	}
	else
		cout << "该 书 已 不 存 在" << endl;
}
void BookManager::Refresh(vector<Book> changedBooks)
{
	int StrToInt(const char* str);//函数声明，该函数定义在Library.h
	fstream f;
	f.open("./Books.txt", ios::in |ios::out | ios::binary);
	for (int i = 0; i < changedBooks.size(); i++)
	{
		int offset = (StrToInt(changedBooks[i].getID()) - 1)* sizeof(Book);
		f.seekp(offset,ios::beg);
		f.write((char *)&changedBooks[i], sizeof(Book));
	}
	f.close();
}
void BookManager::Search(vector<Book> bookVector, vector<Book> *searchResult, char ISBN[])
{
	for (int i = 0; i < bookVector.size(); i++)
	{
		if (strcmp(bookVector[i].getISBN(), ISBN) == 0)
		{
			searchResult->push_back(bookVector[i]);
		}
	}
}
void BookManager::ChangeAll(vector<Book > &bookVector, vector<Book> &changedBooks, int n, char isbn[], char name[], char author[], char publishing[], int type, double price, int count)
{
	bookVector[n - 1].setISBN(isbn);
	bookVector[n - 1].setName(name);
	bookVector[n - 1].setAuthor(author);
	bookVector[n - 1].setPublishing(publishing);
	bookVector[n - 1].setType(type);
	bookVector[n - 1].setPrice(price);
	bookVector[n - 1].setCurrentCount(bookVector[n - 1].getCurrentCount() + count);
	bookVector[n - 1].setoCount(bookVector[n - 1].getOCount()+count);
	changedBooks.push_back(bookVector[n - 1]);
}

void RecordManager::LoadFromFile(vector<Record> *record,const char * path, int loadNum, int displacement, int initialPoint)
{
	FILE *fp;
	if ((fp = fopen(path, "r+")) == NULL) {
		cout << "can't open this file!!" << endl;
		exit(0);
	}
	fseek(fp, displacement, initialPoint);
	struct Record r; 
	for (int i = 0; i < loadNum; i++) {	
		//不应该每次都调用sizeof函数, 应该先把数据的长度求出来, 使用
	    fread(&r, sizeof(Record), 1, fp);
		record->push_back(r);
	}
	fclose(fp);
}
void RecordManager::SaveToFile(vector<Record> record1, const char * path, int displacement, int initialPoint)
{
	FILE *fp;
	if ((fp = fopen(path, "r+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, displacement, initialPoint);
	int nSize = record1.empty() ? -1 : static_cast<int>(record1.size());
	for (int i = 0; i < nSize; i++)
	{
		fwrite(&record1[i], sizeof(Record), 1, fp);

	}
	fclose(fp);
	record1.clear();
}
void RecordManager::Add(vector<Record> &record,char* cAccount, Book book,int n)

{
	char * getNowTime();
	char * getSReturnTime();
	for (int i = 0; i < n; i++)
		{
			if (record[i].enabled)
			{
				cout << "write"  <<endl;
				strcpy(record[i].userID, cAccount);
				strcpy(record[i].bookID, book.getID());
				strcpy(record[i].bookName, book.getName());
				char tp[26];
				strcpy(tp, getNowTime());
				strcpy(record[i].borrowBookTime, tp);
				strcpy(tp, getSReturnTime());
				strcpy(record[i].sReturnBookTime, tp);
				record[i].enabled = false;
				break;
			}
		}

}
void RecordManager::Delete(vector<Record> &record, vector<Record> &history,int n, char  *uID)
{
	if (n > record.size() || n < 1|| record[n - 1].enabled)
	{
		cout << "范围不合法" << endl;
	}
	else
	{
		if (!history.back().enabled)	//如果历史记录满了就清除最早的那一项
		{
			
			Record temp;
			strcpy(temp.userID, uID);
			history.erase(history.begin());
			cout << "已清除最早的一条记录" << endl;
			history.push_back(record[n-1]);
			history.back().enabled = false;
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				if (history[i].enabled)
				{
					cout << "write to history" << i << endl;
					strcpy(history[i].userID, record[n - 1].userID);
					strcpy(history[i].bookName, record[n - 1].bookName);
					strcpy(history[i].bookID, record[n - 1].bookID);
					strcpy(history[i].borrowBookTime, record[n - 1].borrowBookTime);
					strcpy(history[i].returnBookTime, record[n - 1].returnBookTime);
					strcpy(history[i].sReturnBookTime, record[n - 1].sReturnBookTime);

					history[i].enabled = false;
					break;
				}
			}
		}
		record.erase(record.begin()+n - 1);
		
	}
	
}

void RecordManager::ShowHistory(vector<Record> record)
{
	
	int nSize = record.empty() ? -1 : static_cast<int>(record.size());
	int count=0;
	cout <<endl<< "-------------------------------------------------------------------------------" << endl;
	if (nSize < 0)
	{
		cout << endl << "---------------您 还 没 有 借 书---------------" << endl;
		return;
	}
	for (int i = 0; i < nSize; i++) {
		if (record[i].enabled)break;
		cout.setf(ios::left);
		cout << "** " << setw(6) << i+1;
		cout << "** " << setw(8) << record[i].bookID ;
		cout << "** " << setw(30) << record[i].bookName ;
		cout << "** " << setw(20) << record[i].borrowBookTime ;
		cout << "** " << setw(20) << record[i].sReturnBookTime ;
		cout << "** " << setw(20) << record[i].returnBookTime << endl;
		count++;
	}
	cout <<endl<< "-------------------------------------------------------------------------------" << endl;
	cout << "                    当前记录条数:   " << count << endl;
}
void RecordManager::Show(vector<Record> record)
{

	int nSize = record.empty() ? -1 : static_cast<int>(record.size());
	int count = 0;
	cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
	if (nSize < 0)
	{
		cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
		return;
	}
	for (int i = 0; i < nSize; i++) {
		if (record[i].enabled)break;
		cout.setf(ios::left);
		cout << "** " << setw(6) << i + 1;
		cout << "** " << setw(8) << record[i].bookID;
		cout << "** " << setw(30) << record[i].bookName;
		cout << "** " << setw(20) << record[i].borrowBookTime;
		cout << "** " << setw(20) << record[i].sReturnBookTime << endl;
		
		count++;
	}
	cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
	cout << "                    当前记录条数:   " << count << endl;
}
void RecordManager::UpdateRecord(vector<Record> &cr,int userpos,char  *uID,const char * path,int limit)
{
	if ( cr.size() <= limit)
	{
		if (cr.size()!= limit)
		{
			Record temp;
			strcpy(temp.userID, uID);
			int count = limit - cr.size();
			for (int i = 0; i < count; i++)
			{
				cr.push_back(temp);
			}
		}
		FILE *fp;
		if ((fp = fopen(path, "r+")) == NULL) {
			cout << "Can't open this file!" << endl;
			exit(0);
		}
		fseek(fp, userpos*sizeof(Record), 0);
		for (int i = 0; i < limit; i++)
		{
			fwrite(&cr[i], sizeof(Record), 1, fp);
		}
		fclose(fp);
		cr.clear();
	}
	else
	{
		cout << "记录达到上限" << endl;
	}
}



int ReaderManager::LoadFromFile(vector<User> *users, int startID, int n)
{
	FILE *fp;
	if ((fp = fopen("./users.txt", "rb+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, 0, 2);                                                         //定位到末尾
	int len = ftell(fp);                                                     //总长度
	int count = len / sizeof(User);  
	if (count - startID < 0) { startID=count; return 0; }
	rewind(fp);     //重新恢复位置指针的位置，回到文件的开头
	fseek(fp, (startID - 1) * sizeof(User), 0);
	User temp;
	if (count - startID < n)
	{
		n = count - (count / 100) * 100;
		
	}
	if (count % 100 == 0)n = 100;
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(User), 1, fp);
		users->push_back(temp);
	}
	fclose(fp);
	return count;
}
void ReaderManager::userChangePassword(User &user,char * npassword)    //修改密码
{
		user.setUserPassword(npassword);
}
void ReaderManager::userChangeName(User &user)       //修改名字
{
	char name1[9] = "";

	cout << "请输入新的姓名：" << endl;
	cin >> name1;
	user.setUserName(name1);
	cout << "修改成功,新的信息如下：" << endl;
}
void ReaderManager::userChangeClass(User &user)      //修改班级
{
	char class1[17] = "";

	cout << "请输入新的班级：" << endl;
	cin >> class1;
	user.setUserClass(class1);
	cout << "修改成功,新的信息如下：" << endl;
}
void ReaderManager::userChangeEmail(User &user)       //修改邮箱
{
	char email1[17] = "";

	cout << "请输入新的邮箱：" << endl;
	cin >> email1;
	user.setUserEmail(email1);
	cout << "修改成功,新的信息如下：" << endl;
}
void ReaderManager::SaveToFile(vector<User> &bookVector)           //存入文件
{
	FILE *fp;
	if ((fp = fopen(userInfoPath, "rb+")) == NULL) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	fseek(fp, 0, 2);
	for (int i = 0; i < bookVector.size(); i++)
	{
		fwrite(&bookVector[i], sizeof(User), 1, fp);
	}
	fclose(fp);
}
void ReaderManager::Show(User user)                      //显示个人信息
{
	cout << "** " << "1.账号 " << user.getUserAccount() << endl;
	cout << "** " << "2.姓名 " << user.getUserName() << endl;
	cout << "** " << "3.班级 " << user.getUserClass() << endl;
	cout << "** " << "4.邮箱 " << user.getUserEmail() << endl;
	if (user.getStatus() == 1)
	{
		int bookNum = user.getBookNum();
		if (user.getBookNum() < 0)bookNum = 0;
		cout << "\n** " << "可 借 书 数 量 " << bookNum << endl;
		cout << "** " << "可 预 约 数 量 " << user.getreservationNum()<< endl;
	}
	
	cout << "\n** " << "账 号 状 态 ";
	if (user.getStatus() == 1)
		cout << "** " << "正常" << endl;
	else
	{
		cout << "** " << "已 冻 结 ， 不 可 借 书" << endl;
		cout << "** " << "请 检 查 借 阅 记 录，查 看 逾 期 图 书" << endl;
		cout << "** " << "有 疑 问 请 咨 询 管 理 员" << endl;
	}

}
void ReaderManager::Show(vector<User> userVector, int page)
{
	cout.setf(ios::left);
	cout << "** " << setw(6) << "序号";
	cout << "** " << setw(10) << "账号";
	cout << "** " << setw(10) << "姓名";
	cout << "** " << setw(9) << "可借数量";
	cout << "** " << setw(10) << "可预约数量";
	cout << "** " << setw(18) << "班级";
	cout << "** " << setw(31) << "邮箱";
	cout << "** " << setw(9) << "账号状态"<<endl;
	if (!userVector.empty())
	{
		if (userVector.size() <= 100)
		{
			if (page % 5 == 0)page = 5;
			else page = page % 5;
		}
		int start = (page - 1) * 20;
		for (int i = start; i != start + 20; i++) {
			if (i > userVector.size() - 1)					//若数据不足应停止读取，否则出错
			{
				cout.setf(ios::left);
				cout << "** " << setw(6) << i + 1;
				cout << "** " << setw(10) << " ";
				cout << "** " << setw(10) << " ";
				cout << "** " << setw(9) << " ";
				cout << "** " << setw(10) << " ";
				cout << "** " << setw(18) << " ";
				cout << "** " << setw(31) << " ";
				cout << "** " << setw(9) << " " << endl;
			}
			else {

					cout.setf(ios::left);
					cout << "** " << setw(6) << i + 1;
					cout << "** " << setw(10) << userVector[i].getUserAccount();
					cout << "** " << setw(10) << userVector[i].getUserName();
					cout << "** " << setw(9) << userVector[i].getBookNum();
					cout << "** " << setw(10) << userVector[i].getreservationNum();
					cout << "** " << setw(18) << userVector[i].getUserClass();
					cout << "** " << setw(31) << userVector[i].getUserEmail();
					if(userVector[i].getStatus()==1)
					cout << "** " << setw(9) << "正常" << endl;
					else
						cout << "** " << setw(6) << "冻结" << endl;

			}
		}
	}
	else
	{
		cout << "没 有 相 关 信 息" << endl;
	}
}
bool ReaderManager::Add(int n,int *newID)
{
	if (n > 0)
	{
	FILE * fp;
	if ((fp = fopen(userInfoPath, "rb+")) == NULL) {
		cout << "can't open this file!!" << endl;
		exit(0);
	}
	long size = 0;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	*newID = size / sizeof(User) + 1;
	User temp;
	char a[9];
	for (int i = 0; i < n; i++)
	{
			sprintf(a, "%08d", *newID + i);
			temp.setUserAccount(a);
			temp.setUserPassword(dPassword);
			fwrite(&temp,sizeof(User),1,fp);
	}
	fclose(fp);
	return true;
	}
	else
	{
		cout << "请正确输入数量" << endl; return false;
	}
}
void ReaderManager::Search(vector<User> bookVector, vector<User> &searchResult, char * uID)
{
	for (int i = 0; i != bookVector.size(); i++)
	{
		if (strcmp(bookVector[i].getUserAccount(), uID)==0)
		{
			searchResult.push_back(bookVector[i]);
			break;
		}
	}
}
void ReaderManager::RefreshUser(vector<User> user1)                         //刷新，即将修改过的存入文件
{
	int StrToInt(const char* str);//函数声明，该函数定义在Library.h

	fstream f;
	f.open("./users.txt", ios::in | ios::out | ios::binary);
	for (int i = 0; i < user1.size(); i++)
	{
		int offset = (StrToInt(user1[i].getUserAccount()) - 1) * sizeof(User);
		f.seekp(offset, ios::beg);
		f.write((char *)&user1[i], sizeof(User));
	}
	f.close();
}
void ReaderManager::RefreshUser(User user1)                         //刷新，即将修改过的存入文件
{
	int StrToInt(const char* str);//函数声明，该函数定义在Library.h
	fstream f;
	f.open("./users.txt", ios::in | ios::out | ios::binary);
	int offset = (StrToInt(user1.getUserAccount()) - 1) * sizeof(User);
	f.seekp(offset, ios::beg);
	f.write((char *)&user1, sizeof(User));
	f.close();
}

bool ReaderManager::Change(User &user)
{
	static char name1[9] = "";
	do {
		cout << "\t\t请输入新的姓名：不修改输入0" << endl;
		cin >> name1;
	} while (!isLegal(name1, sizeof(name1)));


	static char class1[31] = "";
	do {
		cout << "\t\t请输入新的班级：不修改输入0" << endl;
		cin >> class1;
	} while (!isLegal(class1, sizeof(class1)));

	static char email1[31] = "";
	do {
		cout << "\t\t请输入新的邮箱：不修改输入0" << endl;
		cin >> email1;
	} while (!isLegal(email1, sizeof(email1)));

	cout << "\t\t是否确认修改,确认请输入1，取消输入0:" << endl;
	int a;
	cin >> a;
	switch (a)
	{
	case 1:
		
		if (name1 != "0")
			user.setUserName(name1);
		if (class1 != "0")
			user.setUserClass(class1);
		if (email1 != "0")
			user.setUserEmail(email1);
		return true;
	case 0:
		return false;

	}
}