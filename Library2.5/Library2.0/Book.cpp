#include "stdafx.h" 
#include"Book.h" 
#include<string>


Book::Book()
{
	strcpy(ID, "");
	strcpy(ISBN, "");
	strcpy(name, "");
	strcpy(author, "");
	type = 0;
	strcpy(publishing, "");
	price = 0.0;
	currentCount=0;
	oCount=0;
	reserve = 0;
	isExist=true;
}

Book::Book(char* id, char* isbn, char * Name,char* Author,int Type, char* Publishing, double Price,int Count)
{
	strcpy(ID, id);
	strcpy(ISBN, isbn);
	strcpy(name, Name);
	strcpy(author, Author);
	type = Type;
	strcpy(publishing, Publishing);
	price = Price;
	currentCount = Count;
	oCount = Count;
	reserve = 0;
	isExist = true;
}