
#pragma once

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;



struct Record {                                //�����¼
	char userID[9];                           //�û�ID
	char bookID[20];                           //��ı��
	char bookName[30];                         //����
	char borrowBookTime[26];                   //����ʱ��
	char sReturnBookTime[26];                  //Ӧ����ʱ��, Ĭ��һ����
	char returnBookTime[26];                   //����ʱ��
	bool enabled=true;							//Ϊture����δʹ��
};
