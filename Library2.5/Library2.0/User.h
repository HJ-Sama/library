#pragma once

#include<string>
class User
{
private:char userAccount[9];         //�˺�
		char userPassword[17];       //����
		char userName[9];            //����
		char userClass[31];          //�༶
		char userEmail[31];          //����
		int bookNum;             //�ɽ��������
		int reservationNum;
		int Status;
public:
	//�õ�˽�г�Ա
	char *getUserAccount()
	{
		return userAccount;
	};
	char *getUserPassword()
	{
		return userPassword;
	};
	char *getUserName()
	{
		return userName;
	};
	char *getUserClass()
	{
		return userClass;
	};
	char *getUserEmail()
	{
		return userEmail;
	};
	int getBookNum()
	{
		return bookNum;
	};
	int getStatus()
	{
		return Status;
	};
	int getreservationNum() {
		return reservationNum;
	}

	//�޸�����ֵ
	void setUserAccount(char account[9]) { strcpy(userAccount , account);  }
	void setUserPassword(char password[17])
	{
		strcpy(userPassword, password);
	};
	void setUserName(char name[9])
	{
		strcpy(userName, name);
	};
	void setUserClass(char Class[31])
	{
		strcpy(userClass, Class);
	};
	void setUserEmail(char email[31])
	{
		strcpy(userEmail, email);
	};
	void setBookNum(int num)
	{
		bookNum=num;
	};
	void setStatus(int status)
	{
		Status = status;
	}
	void setReservationNum(int num) { reservationNum = num; }

	User();                                  //���βι���
	void Clear();
};
class Admin
{
private:

};