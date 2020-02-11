#ifndef BOOK_H		//��ֹ�ظ�����
#define BOOK_H
#include<string>
using namespace std;

class Book
{
private:
	char ID[9];
	char ISBN[18];
	char name[30];
	char author[17];
	int type;
	char publishing[21];
	double price;
	int currentCount;//��ǰ����
	int oCount;//ԭ������
	int reserve;
	bool isExist;
public:
	
	char* getID() { return ID; }
	char* getISBN() { return ISBN; }
	char* getName() { return name; }
	char* getAuthor() { return author; }
	int	getType() { return type; }
	char* getPublishing() { return publishing; }
	double getPrice() { return price; }
	int getCurrentCount(){ return currentCount; }
	int getOCount() { return oCount; }
	int getReserve() { return reserve; }
	bool getStatus() { return isExist; }

	void setISBN(char *isbn) { strcpy(ISBN, isbn); }
	void setName(char *Name) { strcpy(name, Name); }
	void setAuthor(char *Author) { strcpy(author, Author); }
	void setType(int Type) { type = Type; }
	void setPublishing(char *Publishing) { strcpy(publishing, Publishing); }
	void setPrice(double Price) { price= Price; }
	void setCurrentCount(int count) { currentCount = count; }
	void setoCount(int count) { oCount = count; };
	void setStatus(bool exist) { isExist = exist; }
	Book();
	Book(char* id, char* isbn, char * Name, char* Author,int Type, char* Publishing, double Price, int Count);
};


#endif
