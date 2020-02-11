
#pragma once

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;



struct Record {                                //借书记录
	char userID[9];                           //用户ID
	char bookID[20];                           //书的编号
	char bookName[30];                         //书名
	char borrowBookTime[26];                   //借书时间
	char sReturnBookTime[26];                  //应还书时间, 默认一个月
	char returnBookTime[26];                   //还书时间
	bool enabled=true;							//为ture代表未使用
};
