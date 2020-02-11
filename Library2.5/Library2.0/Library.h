#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include"Manager.h"
#include <iomanip>
#include<cstring>
using namespace std;
int StrToInt(const char* str)//�ַ�������ת��������  
{
	if (str == NULL || *str == '\0')
	{
		return 0;
	}
	long long ID = 0;
	int sign = 1;
	while (*str == ' ')//�����ո������  
	{
		str++;
	}
	if (*str == '+')//������+����ʾ������  
	{
		str++;
	}
	else if (*str == '-')//������-����ʾ�Ǹ���  
	{
		str++;
		sign = -1;
	}
	while (*str != '\0')
	{
		if (*str >= '0'&&*str <= '9')
		{
			ID = ID * 10 + (*str - '0')*sign;
			if (ID >= INT_MAX)
			{
				return INT_MAX;
			}
			else if (ID <= INT_MIN)
			{
				return INT_MIN;
			}
		}
		else
		{
			break;
		}
		str++;
	}
	return (int)ID;//ע�⽫����ֵת��Ϊint��  
}

char * getNowTime() {
	char bTime[26] = { 0 };                    //����ʱ��
	time_t nowTime = time(NULL);
	tm * pbTime = localtime(&nowTime);
	strftime(bTime, 26, "%Y-%m-%d %H:%M:%S", pbTime);
	return bTime;
}
char * getSReturnTime() {
	char sTime[26] = { 0 };                    //Ӧ����ʱ��, Ĭ��һ����30 * 24 * 3600
	time_t snowTime = time(NULL) + 1*60;
	tm * psTime = localtime(&snowTime);
	strftime(sTime, 26, "%Y-%m-%d %H:%M:%S", psTime);
	return sTime;
}
bool OutTime(char s[])
{
	char now[26];
	strcpy(now, getNowTime());
	for (int n = 0; n < sizeof(now); n++)
	{
		if (now[n] > s[n])
		{
			return true;
		}
		if (now[n] < s[n])
			return false;
	}
	
}


User user;
vector<Record> record;                  //ר�Ź�����ʹ�õĶ�̬����, ÿ�����г�ʼ��ʱ����Ϊ 0
vector<Record> historyRecord;           //Ϊ������ʷ��¼׼��
vector<Record> reservationRecord;
vector<Book> bookVector;                         //��ȡ���鼮
vector<Book> changedBooks;                        //ɾ�����鼮
vector<Book> searchResult;
vector<User> users;
vector<User> userSearchResult;

class Library
{
private:
	BookManager bm;
	ReaderManager um;
	RecordManager rm;
public:
	int Login()
	{
		char Account[9] = "";					//������˻�
		char Input[17] = "";					//���������
		int choice2;   //��ʼ����ѡ��
		int k = 0;
		cout << "\n\t\t\t �� ӭ �� �� ͼ �� �� �� �� ϵ ͳ!" << endl;
		cout << "\n\t\t\t���ڲ��ԣ�����Ա�û���admin������666" << endl;
		do
		{
			cout << "\t\t\t ** 1. �� ¼ **" << endl;
			cout << "\t\t\t ** 2. ע �� **" << endl;
			cout << "\t\t\t ** 0. �� �� **" << endl;
			cout << "\t\t\t �� ѡ ��: ";
			cin >> choice2;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> choice2;
			}
			switch (choice2)
			{
			case 1:
			{
				TotalUser = um.LoadFromFile(&users, 1, 100);
				cout << "�������û���" << endl;
				cout << "����" << endl << "00000001" << endl;
				cin >> Account;
				if (strcmp(admin, Account) == 0)
				{
					cout << "����������" << endl;
					cin >> Input;
					if (strcmp(adminpass, Input) == 0)
					{
						cout << "����Ա��¼�ɹ�" << endl;
						EnterManagerDesk();
						break;
					}
					else
					{
						cout << "�� �� �� ��" << endl;
						break;
					}
				}
				um.Search(users, userSearchResult, Account);
				if (TotalUser > users.size())//��Ҫ���������ļ�
				{
					int n = TotalUser / users.size();
					if (TotalUser % 100 == 0)n--;
					for (int i = 0; i < n; i++)
					{
						int newStart = StrToInt(users.back().getUserAccount()) + 1;
						users.clear();
						um.LoadFromFile(&users, newStart, 100);
						um.Search(users, userSearchResult, Account);
					}
				}
				users.clear();
				if (userSearchResult.empty())
				{
					cout << "û �� �� �� ������ �� �� �� �� ��" << endl;
					break;
				}

				cout << "����������" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> Input;
				if (strcmp(userSearchResult[0].getUserPassword(), Input) == 0)
				{
					k = 0;
					cout << "\t\t\t �� ¼ �� ������ ӭ �� ��" << endl;
					strcpy(cAccount, Account);
					user.setUserAccount(userSearchResult[0].getUserAccount());
					user.setUserClass(userSearchResult[0].getUserClass());
					user.setUserEmail(userSearchResult[0].getUserEmail());
					user.setUserName(userSearchResult[0].getUserName());
					user.setUserPassword(userSearchResult[0].getUserPassword());
					user.setBookNum(userSearchResult[0].getBookNum());
					user.setReservationNum(userSearchResult[0].getreservationNum());
					user.setStatus(userSearchResult[0].getStatus());

					userSearchResult.clear();
					EnterUserDesk();
				}
				else
				{
					cout << "�� �� �� ��" << endl;
					userSearchResult.clear();
					k++;
					cout << "������" << 3 - k << "�ε�½����" << endl;
					if (k >= 3)
					{
						cout << "���ѳ�����¼�������ޣ�ϵͳ�Զ��˳�!" << endl;
						return 1;
					}
					continue;
				}
			}
			break;
			case 2:
			{
				int cc;
				cout << "\t\t\t ȷ �� Ҫ ע �� ��" << endl;
				cout << "\t\t\t ** 1. ȷ �� **" << endl;
				cout << "\t\t\t ** 2. ȡ �� **" << endl;
				cin >> cc;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> cc;
				}
				switch (cc)
				{
				case 1:
				{int newID = 0;
				if (um.Add(1, &newID))
				{
					cout << "\t\t\t ע �� �� ������ �� �� ϵ ͳ" << endl;
					sprintf(cAccount, "%08d", newID);
					cout << "\t\t\t �� �� �� �� Ϊ  " << cAccount;
					cout << "\t �� ʼ �� �� Ϊ  " << dPassword << endl;
					cout << "\t\t\t �� �� �� �� �� �� �� �� �� �� �� �� �� Ϣ" << endl;
					user.setUserAccount(cAccount);
					user.setUserPassword(dPassword);
					EnterUserDesk();
				}
				}
				break;
				case 2:
					break;
				default:
					cout << "ֻ �� �� �� 1��2   " << "�� �� �� �� �� �� ��:" << endl;
				}
				break;
			}
			case 0:
				return 1;
			default:
				cout << "ֻ �� �� �� 0��1��2   " << "�� �� �� �� �� �� ��:" << endl;
			}
		} while (choice2 != 0);
		return 1;

	}
	void EnterManagerDesk()
	{
		char choice;
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
			cout << "\t\t\t** 1.�� �� �� Ϣ �� �� **\n" << endl;
			cout << "\t\t\t** 2.ͼ �� �� Ϣ �� �� **\n" << endl;
			cout << "\t\t\t** 0.  �� ��  **" << endl;
			cout << "\t\t\t ��ѡ��";
			cin >> choice;
			switch (choice)
			{
			case '1':
				EnterManagerUser();
				break;
			case '2':
				EnterManagerBook();
				break;
			case '0':
				cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
				cout << "\t\t\t** 1.ȷ��  **" << endl;
				cout << "\t\t\t** 2.ȡ��  **" << endl;
				int i;
				cin >> i;
				if (i == 1)
				{
					return;
				}
				else if (i == 2) choice = ' ';
				else cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
				break;
			default:
				break;
			}


		} while (choice != '0');

	}

	void EnterUserDesk()
	{
#pragma region getRecordCountOfFile

		FILE * fp;
		if ((fp = fopen(recordPath, "r+")) == NULL) {
			cout << "can't open this file!!" << endl;
			exit(0);
		}
		long size = 0;
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		recordCountOfFile = size / sizeof(struct Record);
		fclose(fp);

#pragma endregion

#pragma region getUserPosition
		int count = 0;
		while (1) {

			rm.LoadFromFile(&record, recordPath, 1, count * sizeof(Record), 0);
			if (record.empty())exit(0);
			if (strcmp(record[0].userID, cAccount) == 0) {
				break;
			}
			record.clear();
			count++;
			//�������ж�, �����ǰ�û�û�н��ļ�¼(���ļ��в����и��û���IDʱ)
			if (count >= recordCountOfFile) {
				if (count == 1)count = 0;
				rm.UpdateRecord(record, count, cAccount,recordPath,userMaxBook);
				rm.UpdateRecord(historyRecord, count * 2, cAccount,historyRecordPath,userMaxBook*2);
				rm.UpdateRecord(reservationRecord, (count % 2) + 2, cAccount, reservationRecordPath, userMaxBook % 2 + 2);
				break;
			}
		}
		userPosition = count;
		record.clear();
#pragma endregion
#pragma region getUAllRecords
		rm.LoadFromFile(&record, recordPath, 5, userPosition * sizeof(Record), 0);
		rm.LoadFromFile(&reservationRecord, reservationRecordPath, 3, ((userPosition % 2) + 2) * sizeof(Record), 0);
		for (int i = 0; i < 5-user.getBookNum(); i++)
		{
			if (!record[i].enabled)
			{
				char s[26];
				strcpy(s, record[i].sReturnBookTime);
				if (OutTime(s)) {
					user.setStatus(0);
				}
			}
		}
		for (int i = 0; i < 3-user.getreservationNum(); i++)
		{
			if (!reservationRecord[i].enabled)
			{
				char s[26];
				strcpy(s, reservationRecord[i].sReturnBookTime);
				if (OutTime(s)) {
					cout << "\t\t* * * * �� �� Ԥ Լ �� ¼ �� �� �� �� * �� �� �� �� �� Ԥ Լ �� ¼ * * *" << endl;
				}
			}
		}
#pragma endregion
		int choice;   //�û�����ѡ��
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
			cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n\n";
			if (user.getStatus() == 0)
			{
				cout << "\t\t* * * * �� �� �� �� �� �� �� �� * * * *\n" << endl;
				cout << "\t\t* * * * �� �� �� �� �� �� �� ͼ �� * * * *\n" << endl;
				cout << "\t\t* * * * �� �� �� �� �� �� ѯ �� �� Ա * * * *\n" << endl;
			}
			cout << "\t\t\t** 1.�� �� �� Ϣ **\n" << endl;
			cout << "\t\t\t** 2.�� �� �� ¼ **\n" << endl;
			cout << "\t\t\t** 3.�� ʷ �� ¼ **\n" << endl;
			cout << "\t\t\t** 4.�� �� Ԥ Լ ͼ �� **\n" << endl;
			cout << "\t\t\t** 5.Ԥ Լ �� ¼ **\n" << endl;
			cout << "\t\t\t** 0.  �� ��  **\n" << endl;
			cout << "\t\t\t ��ѡ��";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				EnterUserInfo();
				break;
			case 2:
				EnterUserRecord();
				break;
			case 3:
				EnterUserHistoryRecord();
				break;
			case 4:
				EnterUserSearchBook();
				break;
			case 5:
				EnterUserReservationRecord();
				break;
			case 0:
				int cc;
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> cc;
					}
					if (cc == 1)
					{
						strcpy(cAccount, "");
						user.Clear();
						break;
					}

					else if (cc == 2) {
						choice = -1; break;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
				break;
			}
		} while (choice != 0);
	}
	void EnterUserInfo()
	{
		vector<User> user1;
		int choice;   //�û�����ѡ��
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****";
			cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n\n";
			um.Show(user);
			cout << "\t\t\t**** ����Ҫ�޸ģ���ѡ��" << endl;
			cout << "\t\t\t**** 1.�޸ĸ�����Ϣ��9.�޸�����,0Ϊ����" << endl;
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\t\tֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> choice;
			}
			switch (choice)
			{
			case 1: 
				cout << "\t\t�Ƿ�ȷ���޸�,ȷ��������1��ȡ������0:" << endl;
				int a;
				cin >> a;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> choice;
				}
				if (a == 1)
				{
					if (um.Change(user))
					{
						cout << "\t\t ** �� �� �� �� **" << endl;
					}
					else
					{
						cout << " �� �� ʧ �� " << endl;
					}
				}
				else if (a == 0)
				{
				}
				else {
					cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
				}
				break;
			case 9:
				int c;
				do {
					cout << endl << "\t\t\t** �� ѡ �� 1.�� ��   0.�� ��  **" << endl;
					cin >> c;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> choice;
						cin.clear();
						cin.sync();
					}
					if (c == 1) {
					p100:
						getchar();
						char p1[30];
						cout << endl << "\t\t\t** �� �� �� �� �� ��   **" << endl;
						cin.get(p1, 30);
						if (strlen(p1) >= passwordLength)
						{
							cout << "�����������ȣ�����������..." << endl;
							goto p100;
						}
						//��������, �ж���û�пո�, �пո�ʱ, ��������
						int i = 0;
						bool status = false;
						while (p1[i]) {
							if (p1[i] == ' ') {
								cout << "�����к��пո�, ����������..." << endl;
								status = true;
								break;
							}
							i++;
						}
						if (status) {
							goto p100;
						}
						getchar();
						cout << "\t\t\t** �� �� �� �� �� �� �� �� ȷ ��   **" << endl;
						char p2[passwordLength];
						cin.get(p2, passwordLength);
						if (strcmp(p1, p2) == 0)
						{
							cout << "\t\t\t** ȷ �� �� �� �� ��1.ȷ�� 2.���� **" << endl;
							int i;
							cin >> i;
							if (i == 1)
							{
								um.userChangePassword(user, p2);
								//l1.RefreshFile(userInfo, 1, (StrToInt(currentAccount) % 100) - 1);
								cout << "\t\t\t** �� �� �� �� �� �� !!! **" << endl;
								user1.push_back(user);
								um.RefreshUser(user1);
								return;
							}
							else if (i == 2) break;
							else cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						}
						else
						{
							cout << "\t\t******** �� �� �� �� �� �� �� ͬ���� �� �� �� ��  ********" << endl;
						}
					}
				} while (c != 0);
				break;
			case 0:
				cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
				cout << "\t\t\t** 1.ȷ��  **" << endl;
				cout << "\t\t\t** 2.ȡ��  **" << endl;
				int i;
				cin >> i;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> choice;
				}
				if (i == 1)
				{
				}
				else if (i == 2) choice =-1;
				else cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
				break;
			default:
				cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
				break;
			}
		} while (choice != 0);
		um.RefreshUser(user);
	}
	void EnterUserSearchBook()
	{
		if (user.getStatus() == 1)
		{
			record.clear();
			rm.LoadFromFile(&record, recordPath, 5, userPosition * sizeof(Record), 0);
#pragma region judge
			
			for (int i = 0; i < 5; i++)
			{
				if (!record[i].enabled)
				{
					char s[26];
					strcpy(s, record[i].sReturnBookTime);
					if (OutTime(s)) {
						user.setStatus(0);
					}
					
				}
			}
#pragma endregion
			reservationRecord.clear();
			rm.LoadFromFile(&reservationRecord, reservationRecordPath, 3, ((userPosition % 2) + 2) * sizeof(Record), 0);


			int c1;
			do {
				if (bookVector.empty())
					TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
				cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
				cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n";
				cout << "\n\t\t\t**** �� �� ͼ �� �� �� ****\n";
				
				cout << "\n\t\t\t**** 1.   ��  ��  **" << endl;
				cout << "\n\t\t\t**** 2.   ��  ��  ȫ  ��  **" << endl;
				cout << "\n\t\t\t**** 0.   ��  ��  **" << endl;
				cin >> c1;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> c1;
				}
				switch (c1)
				{
				case 1:
				{
					char sISBN[14];
					char sname[17];
					char sauthor[17];
					char spublishing[21];
					int c2;
					int page = 1;

					cout << "\n\t\t\t**** �� �� �� �� �� �� Ϣ�� �� �� �� ʹ �� ��#�� �� **" << endl;
#pragma region input
					cout << "\n\t\t\t**** 1. �� �� ��**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sname;
					cout << "\n\t\t\t**** 2. ISBN ��**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sISBN;
					cout << "\n\t\t\t**** 3. �� �� ��**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sauthor;
					cout << "\n\t\t\t**** 4. �� �� �� ��**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> spublishing;
#pragma endregion
					if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
					{
						int c2;
						int page = 1;		//��ǰҳ��
						do
						{
							int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) -1) : (TotalBook / 20);
							cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
							bm.Show(bookVector, page);
							cout << "\n\t**** 1. �� ��      **" << endl;
							cout << "\n\t**** 4. Ԥ Լ      **" << endl;
							cout << "\n\t**** 2. �� һ ҳ   **";
							cout << "\t**** 3. �� һ ҳ   **";
							cout << "\t**** 0. �� ��   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> c2;
							}

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									int c3;
									cout << "\n\t**** �� �� �� �� �� �� �� �� ��  **" << endl;
									cin >> c3;
									while (c3<1 || c3>bookVector.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "������Ų���ȷ������������" << endl;
										cin >> c3;
									}
									if (bookVector[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
											cout << "\t\t\t** ȷ �� �� �� �� �� �� ��  **" << endl;
											cout << "\t\t\t** 1.ȷ��  **" << endl;
											cout << "\t\t\t** 2.ȡ��  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{

												bm.Change(bookVector, c3, -1, changedBooks);
												rm.Add(record, cAccount, bookVector[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  �� �� �� �� �� **" << endl;

											}
											else if (cc == 2);
											else
											{
												cout << " ����ȷ����1��2ѡ��" << endl;
											}
										}
										else
										{
											cout << "\t\t\t**  �� �� �� �� �� �� �� �㣬�� �� ��**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� ��**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  �� �� �� �� �� �� �� �� **" << endl;
								}
							}	
							if (c2 == 2)
							{				
								if (page <= limit)
								{
									page++;
									if (((page - 1) % 5) == 0)
									{
										int newStart = StrToInt(bookVector.back().getID()) + 1;
										if (!changedBooks.empty())
										{
											bm.Refresh(changedBooks);
											changedBooks.clear();
										}
										bookVector.clear();
										bm.LoadFromFile(&bookVector, newStart, 100);
									}
								}
								else
								{
									cout << "�� �� �� �� �� һ ҳ ��" << endl;
								}
							}
							if (c2 == 3)
							{
								if (page != 1)
								{
									if (((page - 1) % 5) == 0)
									{
										int newStart = StrToInt(bookVector.front().getID()) - 100;
										if (!changedBooks.empty())
										{
											bm.Refresh(changedBooks);
											changedBooks.clear();
										}
										bookVector.clear();
										bm.LoadFromFile(&bookVector, newStart, 100);
									}
									page--;
								}
								else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
							}
							if (c2 == 4)
							{
								if (user.getreservationNum() > 0)
								{
									int c3;
									cout << "\n\t**** �� �� �� �� Ԥ Լ �� �� ��  **" << endl;
									cin >> c3;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> c3;
									}
									while (c3<1 || c3>bookVector.size())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "������Ų���ȷ������������" << endl;
										cin >> c3;
									}
									int cc;
									cout << "\t\t\t** ȷ �� Ԥ Լ �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> cc;
									}
									if (cc == 1)
									{
										if (bookVector[c3 - 1].getStatus())
										{
											bm.Change(bookVector, c3, -1, changedBooks);
											rm.Add(reservationRecord, cAccount, bookVector[c3 - 1], userMaxReservation);
											user.setReservationNum(user.getreservationNum() - 1);
											cout << user.getreservationNum() << endl;
											cout << "\t\t\t**  Ԥ Լ �� �� **" << endl;
										}
										else
										{
											cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� Ԥ Լ**" << endl;
										}

									}
									else if (cc == 2);
									else
									{
										cout << " ����ȷ����1��2ѡ��" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  Ԥ Լ �� �� �� �� �� ��**" << endl;
								}
							}
							if (c2 == 0)
							{
								int cc;
								do {
									cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> cc;
									}
									if (cc == 1)
										break;
									else if (cc == 2) {
										c2 = -1; break;
									}
									else {
										cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
									}
								} while (cc != 1 || cc != 2);
							}
						} while (c2 != 0);
						bm.Refresh(changedBooks);
						changedBooks.clear();
						break;
					}		
					
					bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
					if (TotalBook > bookVector.size())//��Ҫ���������ļ�
					{
						int n = TotalBook / bookVector.size();
						if (TotalBook % 100 == 0)n--;
						for (int i = 0; i < n; i++)
						{
							int newStart = StrToInt(bookVector.back().getID()) + 1;
							bookVector.clear();
							bm.LoadFromFile(&bookVector, newStart, 100);
							bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
						}
					}
					bookVector.clear();

					if (searchResult.empty())
					{
						cout << "\n\t**** û �� �� �� �� �� ͼ ��   **" << endl;
					}
					else
					{	
						int nLimit = searchResult.size() / numOfOnePage;
						do
						{
							number0:
							cout << "\n\t**** �� ǰ����" << page << "ҳ" << "  һ�� " << searchResult.size() << "��" << endl;
							bm.Show(searchResult, page);
							cout << "\n\t**** 1. �� ��      **" << endl;
							cout << "\n\t**** 4. Ԥ Լ      **" << endl;
							cout << "\n\t**** 2. �� һ ҳ   **";
							cout << "\t**** 3. �� һ ҳ   **";
							cout << "\t**** 0. �� ��   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> c2;
							}
							//�˴�Ӧ�ж϶����Ƿ���Ȩ�޽���

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									int c3;
									cout << "\n\t**** �� �� �� �� �� �� �� �� ��  **" << endl;
									cin >> c3;
									while (c3<1 || c3>searchResult.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "������Ų���ȷ������������" << endl;
										cin >> c3;
									}
									if (searchResult[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
										confirm1:
											cout << "\t\t\t** ȷ �� �� �� �� �� �� ��  **" << endl;
											cout << "\t\t\t** 1.ȷ��  **" << endl;
											cout << "\t\t\t** 2.ȡ��  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{
												bm.Change(searchResult, c3, -1, changedBooks);
												rm.Add(record, cAccount, searchResult[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  �� �� �� �� �� **" << endl;
											}
											else if (cc == 2);
											else
											{
												cout << " ����ȷ����1��2ѡ��" << endl;
												goto confirm1;
											}
										}
										else
										{
											cout << "\t\t\t**  �� �� �� �� �� �� �� �㣬�� �� ��**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� ��**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  �� �� �� �� �� �� �� ��**" << endl;
								}
							}
							if (c2 == 2)
							{
								int limit = (searchResult.size() % 20 == 0) ? ((searchResult.size() / 20) - 1) : (searchResult.size() / 20);
								if (page <= limit)
								{
									page++;
								}
								else
								{
									cout << "�� �� �� �� �� һ ҳ ��" << endl;
								}
							}
							if (c2 == 3)
							{
								if (page != 1)
								{
									page--;
								}
								else cout << "\n\t****  �� �� �� �� һ ҳ ��    **" << endl;
							}
							if (c2 == 4)
							{
								if (user.getreservationNum() > 0)
								{
									int c3;
									cout << "\n\t**** �� �� �� �� Ԥ Լ �� �� ��  **" << endl;
									cin >> c3;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> c3;
									}
									while (c3<1 || c3>searchResult.size())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "������Ų���ȷ������������" << endl;
										cin >> c3;
									}
									int cc;
									cout << "\t\t\t** ȷ �� Ԥ Լ �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> cc;
									}
									if (cc == 1)
									{
										if (searchResult[c3 - 1].getStatus())
										{
												bm.Change(searchResult, c3, -1, changedBooks);
												rm.Add(reservationRecord, cAccount, searchResult[c3 - 1], userMaxReservation);
												user.setReservationNum(user.getreservationNum() - 1);
												cout << "\t\t\t**  Ԥ Լ �� �� **" << endl;
										}
										else
										{
											cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� Ԥ Լ**" << endl;
										}

									}
									else if (cc == 2);
									else
									{
										cout << " ����ȷ����1��2ѡ��" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  Ԥ Լ �� �� �� �� �� ��**" << endl;
								}
							}
							if (c2 == 0);
						} while (c2 != 0);
					}	
				}
				searchResult.clear();
				bookVector.clear();
				bm.Refresh(changedBooks);
				changedBooks.clear();
				break;
				case 2:
					{
						int c2;
						int page = 1;		//��ǰҳ��
						do
						{
							int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20)-1 ) : (TotalBook / 20);
							cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
							bm.Show(bookVector, page);
							cout << "\n\t**** 1. �� ��      **" << endl;
							cout << "\n\t**** 4. Ԥ Լ      **" << endl;
							cout << "\n\t**** 2. �� һ ҳ   **";
							cout << "\t**** 3. �� һ ҳ   **";
							cout << "\t**** 0. �� ��   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> c2;
							}

							//�˴�Ӧ�ж϶����Ƿ���Ȩ�޽���

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									
									int c3;
									cout << "\n\t**** �� �� �� �� �� �� �� �� ��  **" << endl;
									cin >> c3;
								
									while (c3<1 || c3>bookVector.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "������Ų���ȷ������������" << endl;
										cin >> c3;
									}
									if (bookVector[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
										confirm3:
											cout << "\t\t\t** ȷ �� �� �� �� �� �� ��  **" << endl;
											cout << "\t\t\t** 1.ȷ��  **" << endl;
											cout << "\t\t\t** 2.ȡ��  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{

												bm.Change(bookVector, c3, -1, changedBooks);
												rm.Add(record, cAccount, bookVector[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  �� �� �� �� �� **" << endl;
											}
											else if (cc == 2);
											else
											{
												cout << " ����ȷ����1��2ѡ��" << endl;
												goto confirm3;
											}
										}
										else
										{
											cout << "\t\t\t**  �� �� �� �� �� �� �� �㣬�� �� ��**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� ��**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  �� �� �� �� �� �� �� �� **" << endl;
								}
							}
							if (c2 == 2)
							{
								if (page <= limit)
								{
									page++;
									if (((page - 1) % 5) == 0)
									{
										int newStart = StrToInt(bookVector.back().getID()) + 1;
										if (!changedBooks.empty())
										{
											bm.Refresh(changedBooks);
											changedBooks.clear();
										}
										bookVector.clear();
										bm.LoadFromFile(&bookVector, newStart, 100);
									}
								}
								else
								{
									cout << "�� �� �� �� �� һ ҳ ��" << endl;
								}
							}
							if (c2 == 3)
							{
								if (page != 1)
								{
									if (((page - 1) % 5) == 0)
									{
										int newStart = StrToInt(bookVector.front().getID()) - 100;
										if (!changedBooks.empty())
										{
											bm.Refresh(changedBooks);
											changedBooks.clear();
										}
										bookVector.clear();
										bm.LoadFromFile(&bookVector, newStart, 100);
									}
									page--;
								}
								else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
							}
							if (c2 == 4)
							{
								int c3;
								cout << "\n\t**** �� �� �� �� Ԥ Լ �� �� ��  **" << endl;
								cin >> c3;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> c3;
								}
								while (c3<1 || c3>bookVector.size())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "������Ų���ȷ������������" << endl;
									cin >> c3;
								}
								int cc;
								cout << "\t\t\t** ȷ �� Ԥ Լ �� �� �� �� ��  **" << endl;
								cout << "\t\t\t** 1.ȷ��  **" << endl;
								cout << "\t\t\t** 2.ȡ��  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> cc;
								}
								if (cc == 1)
								{
									if (bookVector[c3 - 1].getStatus())
									{

										if (user.getreservationNum()>0)
										{
											bm.Change(bookVector, c3, -1, changedBooks);
											rm.Add(reservationRecord, cAccount, bookVector[c3 - 1], userMaxReservation);
											user.setReservationNum(user.getreservationNum() - 1);
											cout << "\t\t\t**  Ԥ Լ �� �� **" << endl;
										}
										else
										{
											cout << "\t\t\t**  Ԥ Լ �� �� �� �� �� ��**" << endl;
										}
									}
									else
									{
										cout << "\t\t\t**  �� �� �� �� �� �ڣ��� �� Ԥ Լ**" << endl;
									}

								}
								else if (cc == 2);
								else
								{
									cout << " ����ȷ����1��2ѡ��" << endl;
								}
							}
							if (c2 == 0)
							{
								int cc;
								do {
									cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> cc;
									}
									if (cc == 1)
										break;
									else if (cc == 2) {
										c2 = -1; break;
									}
									else {
										cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
									}
								} while (cc != 1 || cc != 2);
							}
						} while (c2 != 0);
					}
					bm.Refresh(changedBooks);
					changedBooks.clear();
					break;
				case 0:
					int cc;
					do {
						cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							if (!bookVector.empty())
								bookVector.clear();
							break;
						}
						else if (cc == 2) {
							c1 = -1;
							break;
						}
						else {
							cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
				}
			} while (c1 != 0);
			um.RefreshUser(user);
			
			rm.UpdateRecord(record, userPosition, cAccount,recordPath,userMaxBook);
			rm.UpdateRecord(reservationRecord, (userPosition % 2) + 2, cAccount, reservationRecordPath, 3);
		}
		else
		{
			cout << "\t\t\t** �� �� �� �� �� �� ��  **" << endl;
			cout << "\t\t\t** �� �� �� �� �� ͼ ��  **" << endl;
		}

	}

	void EnterUserRecord()
	{
		record.clear();
		rm.LoadFromFile(&record, recordPath, 5, userPosition * sizeof(Record), 0);
		historyRecord.clear();
		rm.LoadFromFile(&historyRecord, historyRecordPath, 10, 2 * userPosition * sizeof(Record), 0);
#pragma region judge
	
		for (int i = 0; i < 5- user.getBookNum(); i++)
		{
			if (!record[i].enabled)
			{
				char s[26];
				strcpy(s, record[i].sReturnBookTime);
				if (OutTime(s)) {
					user.setStatus(0);
				}
			}
		}
#pragma endregion

		int choice;   
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n";
			cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n";
			cout << "\n\t\t\t**** �� �� �� �� �� ¼****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "���";
			cout << "** " << setw(8) << "ͼ��ID";
			cout << "** " << setw(30) << "����";
			cout << "** " << setw(20) << "��������";
			cout << "** " << setw(20) << "Ӧ������" << endl;
			rm.Show(record);
			if (user.getBookNum() == 5)
			{
				cout << "\n\t\t\t**** �� �� �� �� ¼****\n\n" << endl;
				break;
			}
			else
			{
				vector<int> pos;
				for (int i = 0; i < record.size(); i++)
				{
					if (!record[i].enabled)
					{
						if (OutTime(record[i].sReturnBookTime))
						{
							pos.push_back(i + 1);
						}
					}
				}
				if (!pos.empty())
				{
					for(int i=0;i<pos.size();i++)
					cout << "\t\t* * * * �� �� Ϊ "<<  pos[i] << " �� �� �� �� �� �� ���� �� �� �� �� * * * *" << endl;
					cout << "\t\t\t****  �� �� �� �� �� �� �� �� ��  **" << endl;
				}
				cout << "\t\t\t** 1.  �� ��  **" << endl;
				cout << "\t\t\t** 0.  �� ��  **" << endl;
				cout << "\t\t\t ��ѡ��";
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> choice;
				}
				switch (choice)
				{
				case 1:
					int c2;
					do
					{
						cout << "\n\t\t\t****  �� �� �� �� �� �� �� �� Ӧ ͼ ��  **" << endl;
						cout << "\n\t\t\t****  �� �� �� 0 �� ��  **" << endl;
						cin.clear();
						cin.ignore(100, '\n');
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c2;
						}
						if (c2<1 || c2>record.size())
						{
							cout << "\t\t****** ����ȷ�������******" << endl;
						}
						else if (!record[c2 - 1].enabled)
						{
							int cc;
							cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								
								char time[26];
								strcpy(time, getNowTime());
								strcpy(record[c2 - 1].returnBookTime, time);
								bm.LoadFromFile(&bookVector, StrToInt(record[c2 - 1].bookID),1);	
								bm.Change(bookVector, 1, 1, changedBooks);
								rm.Delete(record, historyRecord, c2, cAccount);
								user.setBookNum(user.getBookNum()+1);
								if (!pos.empty())
								{
									for (int i = 0; i < pos.size(); i++)
									{
										if (c2 == pos[i])
										{
											pos.erase(pos.begin()+i);
											cout << "\t\t* * * * �� �� �� �� ͼ �� �� �� �� �� * * * *" << endl;
											cout << "\t\t* * * * �� �� �� �� ͼ �� �� �� �� �� һ �� �� Ϊ �� �� * * * *" << endl;
											user.setBookNum(user.getBookNum() - 1);
											cout << "\t\t* * * * �� �� ǰ �� �� �� ͼ �� �� �� Ϊ "<< user.getBookNum() << " �� * * * *" << endl;
											cout << "\t\t* * * * �� �� �� �� �� �� �� �� �� �� ѯ �� �� Ա * * * *" << endl;
										}
									}
									if (pos.empty())
									{
										cout << "\n\t*** * * * �� �� �� �� ȫ �� �� �� �� ������ �� �� �� �� �� * * * ***" << endl;
										cout << "\t*** * * * ֮ �� �� �� ʱ �� �飬 �� �� �� �� ϰ �� * * * ***\n" << endl;
										user.setStatus(1);
									}
									else
									{
										cout << "\n\t\t* * * * �� �� û �� �� �� �� �� �� �� ͼ ��* * * *\n" << endl;
										
									}
								}
								pos.clear();
								break;
								
							}
							else if (cc == 2);
							else
							{
								cout << " ����ȷ����1��2ѡ��" << endl;
							}
						}
						else {
							cout << "�� �� ȷ �� �� �� ��"<<endl;
						}

					} while (c2 != 0);
					break;
				case 0:
					int cc;
					do {
						cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)		//�˳���ˢ���ļ�
						{	
							break;
						}
						else if (cc == 2) {
							choice = -1; break;
						}
						else {
							cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
					break;
				}
			}
		} while (choice != 0);
		um.RefreshUser(user);
		bm.Refresh(changedBooks);
		bookVector.clear();
		changedBooks.clear();
		rm.UpdateRecord(record, userPosition, cAccount, recordPath, userMaxBook);
		rm.UpdateRecord(historyRecord, userPosition * 2, cAccount, historyRecordPath, userMaxBook * 2);

	}
	





	void EnterUserHistoryRecord()
	{
		int choice;
		historyRecord.clear();
		rm.LoadFromFile(&historyRecord, historyRecordPath, 10, 2 * userPosition * sizeof(Record), 0);
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
			cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n\n";
			cout << "\n\t\t\t**** �� �� �� ʷ �� ¼****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "���";
			cout << "** " << setw(8) << "ͼ��ID";
			cout << "** " << setw(30) << "����";
			cout << "** " << setw(20) << "��������";
			cout << "** " << setw(20) << "Ӧ������";
			cout << "** " << setw(20) << "�黹����" << endl;
			rm.ShowHistory(historyRecord);
			cout << "\t\t\t** 0.  �� ��  **" << endl;
			cout << "\t\t\t ��ѡ��";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> choice;
			}
			switch (choice)
			{
			case 0:
				int cc;
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						break;
					else if (cc == 2) {
						choice = -1; break;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
				break;
			}
		} while (choice != 0);
	}
	void EnterUserReservationRecord() {
		record.clear();
		rm.LoadFromFile(&record, recordPath, 5, userPosition * sizeof(Record), 0);

		reservationRecord.clear();
		rm.LoadFromFile(&reservationRecord, reservationRecordPath, 3, ((userPosition%2)+2 )* sizeof(Record), 0);
		int choice;
#pragma region judge

		vector<int> pos;
		for (int i = 0; i < reservationRecord.size(); i++)
		{
			if (!reservationRecord[i].enabled)
			{
				char s[26];
				strcpy(s, reservationRecord[i].sReturnBookTime);
				if (OutTime(s)) {
					cout << "\t\t* * * * �� �� Ԥ Լ �� ¼ �� �� �� �� * * * *" << endl;
					pos.push_back(i + 1);
				}
			}
		}
#pragma endregion

		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n";
			cout << "\n\t\t\t**** �� ǰ �� ����" << cAccount << "  ****\n";
			cout << "\n\t\t\t**** �� �� Ԥ Լ �� ¼****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "���";
			cout << "** " << setw(8) << "ͼ��ID";
			cout << "** " << setw(30) << "����";
			cout << "** " << setw(20) << "ԤԼ����";                     //ʹ��borrowTime
			cout << "** " << setw(20) << "ʧЧ����" << endl;             //ʹ��SReturnTime

			rm.Show(reservationRecord);                                  //                          
			
			if (user.getreservationNum() == 3)
			{
				cout << "\n\t\t\t**** �� Ԥ Լ �� ¼****\n\n" << endl;
				break;
			}
			else 
			{
				if (!pos.empty())
				{			
					for (int i = 0; i < pos.size(); i++)
					{
						bm.LoadFromFile(&bookVector, StrToInt(reservationRecord[0].bookID), 1);
						bm.Change(bookVector, 1, 1, changedBooks);
						bm.Refresh(changedBooks);
						bookVector.clear();
						changedBooks.clear();
						user.setReservationNum(user.getreservationNum()+1);
						reservationRecord.erase(reservationRecord.begin());
						
						cout << "\t\t* * * * �� �� Ϊ " << pos[i] << " �� Ԥ Լ �� �� �� ��  * * * *" << endl;
					}
					pos.clear();
					cout << "\t\t\t****  �� �� �� �� �� Ч �� Ԥ Լ �� ¼  **" << endl;
					rm.Show(reservationRecord);
				}

				cout << "\t\t\t** 1.  �� ��  **" << endl;
				cout << "\t\t\t** 0.  �� ��  **" << endl;
				cout << "\t\t\t ��ѡ��";
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
					cin >> choice;
				}
				switch (choice)
				{
				case 1:
					if (user.getreservationNum() == 3)
					{
						cout << "\n\t\t\t**** �� Ԥ Լ �� ¼****\n\n" << endl;
					}
					else
					{
						if (user.getBookNum() > 0)
						{
							int c2;
							do
							{
								cout << "\n\t\t\t****  �� �� �� �� �� �� �� �� Ӧ ͼ ��  **" << endl;
								cout << "\n\t\t\t****  �� �� �� 0 �� ��  **" << endl;
								cin.clear();
								cin.ignore(100, '\n');
								cin >> c2;          //��Ӧ�����
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> c2;
								}
								if (c2 < 1 || c2 > reservationRecord.size())
								{
									cout << "\t\t****** �� �� ȷ �� �� �� ��******" << endl;
								}
								else if (!reservationRecord[c2 - 1].enabled)
								{
									int cc;
									//
									cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> cc;
									}
									if (cc == 1)
									{
										//��ѡ����ԤԼ����
										char time[26];
										strcpy(time, getNowTime());
										strcpy(reservationRecord[c2 - 1].borrowBookTime, time);
										strcpy(time, getSReturnTime());
										strcpy(reservationRecord[c2 - 1].sReturnBookTime, time);

										rm.Delete(reservationRecord, record, c2, cAccount);
										user.setBookNum(user.getBookNum() - 1);
										user.setReservationNum(user.getreservationNum() + 1);

										break;


									}
									else if (cc == 2);
									else
									{
										cout << " ����ȷ����1��2ѡ��" << endl;
									}
								}
								else {
									cout << " û �� Ԥ Լ �� ¼" << endl;
								}

							} while (c2 != 0);
						}
						else
						{
							cout << " �� �� �� �� �� �� �� ��" << endl;
						}
					}	
					break;
				case 0:
					int cc;
					do {
						cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)		//�˳���ˢ���ļ�
						{
							break;
						}
						else if (cc == 2) {
							choice = -1; break;
						}
						else {
							cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
					break;
				}
			}
			
			

		} while (choice != 0);
		um.RefreshUser(user);
		bookVector.clear();
		rm.UpdateRecord(record, userPosition, cAccount, recordPath,5);
		rm.UpdateRecord(reservationRecord, (userPosition % 2) + 2, cAccount, reservationRecordPath,3);
		reservationRecord.clear();
	}
	void EnterManagerBook();
	void EnterManagerUser();

	void AddBook();
	void DeleteBook();
	void CorrectBook();
	};


void Library::EnterManagerUser()
	{
		int choice;   //����ѡ��
		char input[17];
		int c1;
		do {
			if (users.empty())
				TotalUser = um.LoadFromFile(&users, 1, 100);
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
			
			cout << "\n\t\t\t**** �� �� �� �� �� �� ****\n";
			
			cout << "\n\t\t\t**** 1. �� �� �� �� �� ��  **" << endl;
			cout << "\n\t\t\t**** 5. �� �� ȫ ��  **" << endl;
			cout << "\n\t\t\t**** 0.   ��  ��  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> c1;
			}
			switch (c1)
			{
			case 1:
			{
				int c2;
				int page = 1;
				cout << "\n\t\t\t**** 1. �� �� �� �� �� ��**" << endl;
				cout << "����" << endl << "00000001" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> input;
				um.Search(users, userSearchResult, input);
				if (TotalUser > users.size())//��Ҫ���������ļ�
				{
					int n = TotalUser / users.size();
					if (TotalUser % 100 == 0)n--;
					for (int i = 0; i < n; i++)
					{
						int newStart = StrToInt(users.back().getUserAccount()) + 1;
						users.clear();
						um.LoadFromFile(&users, newStart, 100);
						um.Search(users, userSearchResult, input);
					}
				}
				users.clear();
				if (userSearchResult.empty())
				{
					cout << "û �� �� �� ������ �� �� �� �� ��" << endl;
					break;
				}

				do
				{
					um.Show(userSearchResult[0]);
					cout << "\n\t**** 1. �� �� �� ��   **";
					cout << "\n\t**** 2. �� �� �� ��   **";
					cout << "\n\t**** 3. �� �� �� �� �� ��   **";
					cout << "\n\t**** 4. �� �� �� ��   **";
					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c1;
					}

					if (c2 == 1)
					{
						int cc;
							cout << "\t\t\t** ȷ �� �� �� �� �� �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								userSearchResult[0].setUserPassword(dPassword);
								cout << "\n\t****  �� �� �� �� �� ��  **" << endl;
								um.RefreshUser(userSearchResult[0]);
							}
							else if (cc == 2);
							else
							{
								cout << " ����ȷ����1��2ѡ��" << endl;
							}
					
					}
					if (c2 == 2)
					{
						int cc;
						cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setStatus(1);
							cout << "\n\t****  �� �� �� �� �� ��  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " ����ȷ����1��2ѡ��" << endl;
						}
					
					}
					if (c2 == 3)
					{
						int cc;
						cout << "\t\t\t** ȷ �� �� �� �� �� �� �� �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setBookNum(5);
							cout << "\n\t****  �� �� �� �� �� �� �� ��  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " ����ȷ����1��2ѡ��" << endl;
						}
					
					}
					if (c2 == 4)
					{
						int cc;
						cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setStatus(0);
							cout << "\n\t****  �� �� �� �� �� ��  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " ����ȷ����1��2ѡ��" << endl;
						}
					
					}
					if (c2 == 0) {
						
						userSearchResult.clear();
					}
				} while (c2 != 0);
			}
			break;
			case 5:
			{
				vector<User> changedUsers;
				int c2;
				int page = 1;		//��ǰҳ��
				do
				{
					cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << TotalUser / 20 + 1 << "ҳ " << "  һ�� " << TotalUser << "��" << endl;
					um.Show(users, page);
					cout << "\n\t**** 2. �� һ ҳ   **";
					cout << "\t**** 3. �� һ ҳ   **";
					cout << "\t**** 0. �� ��   **" << endl;

					cout << "\n\t**** 4. �� �� �� ��   **";
					cout << "\n\t**** 5. �� �� �� ��   **";
					cout << "\t**** 6. �� �� �� �� �� ��   **";
					cout << "\n\t**** 7. �� �� �� ��   **";


					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c1;
					}

					int limit = (TotalUser % 20 == 0) ? ((TotalUser / 20) - 1) : (TotalUser / 20);
					if (c2 == 2)
					{
						if (page <= limit)
						{
							page++;
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(users.back().getUserAccount()) + 1;
								if (!changedUsers.empty())
								{
									um.RefreshUser(changedUsers);
									changedUsers.clear();
								}
								users.clear();
								um.LoadFromFile(&users, newStart, 100);
							}
						}
						else
						{
							cout << "�� �� �� �� �� һ ҳ ��" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(users.front().getUserAccount()) - 100;
								if (!changedUsers.empty())
								{
									um.RefreshUser(changedUsers);
									changedUsers.clear();
								}
								changedBooks.clear();
								um.LoadFromFile(&users, newStart, 100);
							}
							page--;
						}
						else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
					}
					if (c2 == 4)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "������Ų���ȷ������������" << endl;
							cin >> c3;
						}
						int cc;
						cout << "\t\t\t** ȷ �� �� �� �� �� �� �� �� �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							users[c3 - 1].setUserPassword(dPassword);
							cout << "\n\t****  �� �� �� �� �� ��  **" << endl;
							changedUsers.push_back(users[c3 - 1]);
						}
						else if (cc == 2);
						else
						{
							cout << " ����ȷ����1��2ѡ��" << endl;
						}			
					}
					if (c2 == 5)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "������Ų���ȷ������������" << endl;
							cin >> c3;
						}
						if (users[c3 - 1].getStatus() == 0)
						{
							int cc;
							cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								users[c3 - 1].setStatus(1);
								cout << "\n\t****  �� �� �� ��  **" << endl;
								changedUsers.push_back(users[c3 - 1]);
							}
							else if (cc == 2);
							else
							{
								cout << " ����ȷ����1��2ѡ��" << endl;
							}
						}
						else cout << "\n\t****  �� �� �� δ �� ��  **" << endl;
					}
					if (c2 == 6)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "������Ų���ȷ������������" << endl;
							cin >> c3;
						}
						int cc;
						cout << "\t\t\t** ȷ �� �� �� �� �� �� �� �� �� �� ��  �� ��  **" << endl;
						cout << "\t\t\t** 1.ȷ��  **" << endl;
						cout << "\t\t\t** 2.ȡ��  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							users[c3 - 1].setBookNum(5);
							cout << "\n\t****  �� �� �� �� �� �� �� �� **" << endl;
							changedUsers.push_back(users[c3 - 1]);
						}
						else if (cc == 2);
						else
						{
							cout << " ����ȷ����1��2ѡ��" << endl;
						}
					}
					if (c2 == 7)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "������Ų���ȷ������������" << endl;
							cin >> c3;
						}
						if (users[c3 - 1].getStatus() == 1)
						{
							int cc;
							cout << "\t\t\t** ȷ �� �� �� �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								users[c3 - 1].setStatus(0);
								cout << "\n\t****  �� �� �� ��  **" << endl;
								changedUsers.push_back(users[c3 - 1]);
							}
							else if (cc == 2);
							else
							{
								cout << " ����ȷ����1��2ѡ��" << endl;
							}
						}
						else cout << "\n\t****  �� �� �� �� �� ��  **" << endl;
					}
					if (c2 == 0) {

					}
				} while (c2 != 0);
				um.RefreshUser(changedUsers);
				users.clear();
				changedUsers.clear();
			}	
			break;
			case 0:
				int cc;
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> cc;
					}
					if (cc == 1)
					{
						if (!bookVector.empty())
							bookVector.clear();
						break;
					}
					else if (cc == 2) {
						c1 = -1;
						break;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** ����ȷ����1-6��0ѡ��******" << endl;
			}
		} while (c1 != 0);
	}

void Library::EnterManagerBook()
	{
		int choice;
		do
		{
			cout << "\n\t\t\t**** ͼ �� �� �� ϵ ͳ****\n\n";
			cout << "\t\t\t** 1.�� �� ͼ �� **\n" << endl;
			cout << "\t\t\t** 2.ɾ �� ͼ �� **\n" << endl;
			cout << "\t\t\t** 3.�� �� ͼ �� **\n" << endl;
			cout << "\t\t\t** 4.�� �� �� �� ͼ �� **\n" << endl;
			cout << "\t\t\t** 0.  ����  **" << endl;
			cout << "\t\t\t ��ѡ��";
			cin >> choice;
			switch (choice)
			{
			case 1:
				AddBook();
				break;
			case 2:
				DeleteBook();
				break;
			case 3:
				CorrectBook();
				break;
			case 4:
			{
				int c2;
				int page = 1;		//��ǰҳ��
				if (bookVector.empty())
					TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
				do
				{
					cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << TotalBook / 20 + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 2. �� һ ҳ   **";
					cout << "\t**** 3. �� һ ҳ   **";
					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c2;
					}

					int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
					if (c2 == 2)
					{
						if (page <= limit)
						{
							page++;
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.back().getID()) + 1;
								if (!changedBooks.empty())
								{
									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
						}
						else
						{
							cout << "�� �� �� �� �� һ ҳ ��" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.front().getID()) - 100;
								if (!changedBooks.empty())
								{
									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
							page--;
						}
						else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
					}
					if (c2 == 0)
					{
						int cc;
						do {
							cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
								break;
							else if (cc == 2) {
								c2 = -1; break;
							}
							else {
								cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
							}
						} while (cc != 1 || cc != 2);
					}
				} while (c2 != 0);
			}
				break;
			case 0:
				cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
				cout << "\t\t\t** 1.ȷ��  **" << endl;
				cout << "\t\t\t** 2.ȡ��  **" << endl;
				int i;
				cin >> i;
				if (i == 1)
				{
					return;
				}
				else if (i == 2) choice = ' ';
				else cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
				break;
			default:
				break;
			}
		} while (choice != '0');
	}

void Library::AddBook()
	{
		bool isLegal(char a[], int len);
		int choice = -1;
		int c1 = -1;
		do {
			static char name[30], author[17], publishing[21], ISBN[18];
			int type;
			double price;
			int count;
			searchResult.clear();
			bookVector.clear();
			TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
			cout << "��������Ҫ��ӵ������Ϣ �� 0 �� ��" << endl;
			cout << "������ISBN��" << " ע �� ���� ȷ �� I S B N �� �� ȷ " << endl;
			cin >> ISBN;
			if (strcmp(ISBN, "0") == 0)
				return;
			string s1(ISBN);
			while (s1.find('#') != string::npos)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout <<  "ISBN �� �� �� �� �ڡ�#��" << "�� �� �� �� �� :" << endl;
				cin >> ISBN;
				s1 = ISBN;
			}			
			bm.Search(bookVector, &searchResult, ISBN);
			if (TotalBook > bookVector.size())//��Ҫ���������ļ�
			{
				int n = TotalBook / bookVector.size();
				if (TotalBook % 100 == 0)n--;
				for (int i = 0; i < n; i++)
				{
					int newStart = StrToInt(bookVector.back().getID()) + 1;
					bookVector.clear();
					bm.LoadFromFile(&bookVector, newStart, 100);
					bm.Search(bookVector, &searchResult, ISBN);
				}
			}
			bookVector.clear();
			if (searchResult.empty())
			{
				cout << "�� �� �� �� �� �� Ϣ " << endl;
				do {
					cout << "�� �� �� �� ����" << endl;
					cin >> name;
				} while (!isLegal(name, sizeof(name)));
				do {
					cout << "�� �� �� �� �ߣ�" << endl;
					cin >> author;
				} while (!isLegal(author, sizeof(author)));

				cout << "�� ѡ �� ͼ �� �� ��" << endl;
				for (int i = 0; i < 22; i++)
				{
					if (i % 6 == 0)cout << endl;
					cout.setf(ios::left);
					cout << "** " << setw(4) << i + 1 << " **";
					cout << setw(20) << bookKind[i];
				}
				cout << "\n�� �� �� �� �ţ�" << endl;
				cin >> type;	
				while (type < -2 || type>22|| cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					 cout << " �� �� ��ֻ �� �� �� �� �� ��  ֻ �� Ϊ 1 -- 2 2 " << endl;
					cin >> type;
				}
				type--;
				do {
					cout << "�� �� �� �� �� �磺" << endl;
					cin >> publishing;
				} while (!isLegal(publishing, sizeof(publishing)));
				
				cout << "�� �� �� �� ��" << endl;
				cin >> price;
				while (price<=0 || cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� ��:" << endl;
					cin >> price;
				}
				cout << "�� �� �� �� ����" << endl;
				cin >> count;
				while (count <1|| cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� ��:" << endl;
					cin >> count;		
				}

				//ȷ������ͼ��
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						char tID[9];
						sprintf(tID, "%08d", TotalBook + 1);
						Book temp(tID, ISBN, name, author, type, publishing, price, count);
						bm.Add(temp);
						cout << "\t\t\t**  �� �� �� �� **" << endl;
					}
					return;
					case 2:
						break;
					default:
						cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (choice != 2);
			}
			else
			{
				if (searchResult[0].getStatus())
				{
					int inputNum = 0;
					cout << "\t\t\t** �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** �� �� �� Ҫ �� �� �� �� ��  **" << endl;
					cin >> inputNum;
					while (inputNum < 1||cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� ��:" << endl;
						cin >> inputNum;
					}

					searchResult[0].setoCount(searchResult[0].getOCount() + inputNum);
					//change��ֻ�޸��˵�ǰ������δ�޸Ĺݲ�����
					bm.Change(searchResult, 1, inputNum, changedBooks);
					//ȷ������ͼ��
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> choice;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
						bm.Refresh(changedBooks);
						cout << "\t\t\t** �� �� �� ��   **" << endl;
						return;
					case 2:
						break;
					default:
						cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						break;
					}
				}
				else
				{
					cout << "\t\t\t** �� �� �� Ϣ �� �ڣ��� �� �� ɾ ��  **" << endl;
					cout << "\t\t\t** �� �� Ҫ �� �� �� �� ���� �� �� ���� **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> choice;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
					{int inputNum = 0;
					cout << "\t\t\t** �� �� �� ͼ �� �� �� ��  **" << endl;
					cin >> inputNum;
					while (cin.fail() || inputNum < 1)
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << " �� �� ��ֻ �� �� �� �� �� �� �� �� ֻ �� �� ��  �� �� 1" << endl;
						cout << "�� �� �� �� �� �� ��:" << endl;
						cin >> inputNum;
					}
					searchResult[0].setStatus(true);
					searchResult[0].setoCount(inputNum);
					searchResult[0].setCurrentCount(inputNum);
					bm.Refresh(changedBooks);
					cout <<"\t\t\t**  �� �� �� �� �� �� **" << endl;
					}
					return;
					case 2:
						break;
					default:
						cout << "\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
						break;
					}
				}
			}
		} while (c1 != 0);

	}

void Library::DeleteBook()
	{
		int c1;
		char input[17];
		//�˴����ɾ��ͼ��Ĵ���
		do {
		page4:
			bookVector.clear();
			searchResult.clear();
			TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
			cout << "\n\t\t\t**** 1. �� ��  **" << endl;
			cout << "\n\t\t\t**** 2. �� �� ȫ ��  **" << endl;
			cout << "\n\t\t\t**** 0.   ��  ��  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> c1;
			}
			switch (c1)
			{
			case 1:
			{
				char sISBN[14];
				char sname[17];
				char sauthor[17];
				char spublishing[21];
				int c2;
				int page = 1;
				cout << "\n\t\t\t**** �� �� �� �� �� �� Ϣ�� �� �� �� ʹ �� �� # �� �� **" << endl;
#pragma region input
				cout << "\n\t\t\t**** 1. �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sname;
				cout << "\n\t\t\t**** 2. ISBN ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sISBN;
				cout << "\n\t\t\t**** 3. �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sauthor;
				cout << "\n\t\t\t**** 4. �� �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> spublishing;
#pragma endregion
				if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
				{
					do
					{
						int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
						cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ "<<"  һ�� " << TotalBook << "��" << endl;
						bm.ManagerShow(bookVector, page);
						cout << "\n\t**** 1. ɾ �� ��      **" << endl;
						cout << "\n\t**** 2. �� һ ҳ   **";
						cout << "\t**** 3. �� һ ҳ   **";
						cout << "\t**** 0. �� ��   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c2;
						}
						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** �� �� �� �� ɾ �� �� �� �� ��  **" << endl;
							cin >> c3;					
							
							while (c3<1 || c3>bookVector.size()|| cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << " �� �� �� �� ȷ �� �� ��" << endl;
								cin >> c3;
							}
							if (bookVector[c3 - 1].getStatus())
							{
								if (bookVector[c3 - 1].getCurrentCount() == bookVector[c3 - 1].getOCount())
								{
									bm.Delete(bookVector, c3, changedBooks);
									bm.Refresh(changedBooks);
									cout << "\n\t**** * * �� �� ɾ ��  * * ****" << endl;
									changedBooks.clear();
								}
								else
								{
									cout << "\n\t**** * *  �� �� Ŀ ǰ �� �� ������ �� ɾ ��  * * ****" << endl;
								}

							}
							else
							{
								cout << "\n\t**** * *  �� �� �� �� �� �� �ڣ��� �� ɾ ��  * * ****" << endl;
							}

						}
						if (c2 == 2)
						{
							
							if (page <= limit)
							{
								page++;
								if (((page - 1) % 5) == 0)
								{
									int newStart = StrToInt(bookVector.back().getID()) + 1;
									if (!changedBooks.empty())
									{

										bm.Refresh(changedBooks);
										changedBooks.clear();
									}
									bookVector.clear();
									bm.LoadFromFile(&bookVector, newStart, 100);
								}
							}
							else
							{
								cout << "�� �� �� �� �� һ ҳ ��" << endl;
							}
						}
						if (c2 == 3)
						{
							if (page != 1)
							{
								if (((page - 1) % 5) == 0)
								{
									int newStart = StrToInt(bookVector.front().getID()) - 100;
									if (!changedBooks.empty())
									{
										bm.Refresh(changedBooks);
										changedBooks.clear();
									}
									bookVector.clear();
									bm.LoadFromFile(&bookVector, newStart, 100);
								}
								page--;
							}
							else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
						}
						if (c2 == 0)
						{
							int cc;
							do
							{
								cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
								cout << "\t\t\t** 1.ȷ��  **" << endl;
								cout << "\t\t\t** 2.ȡ��  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> cc;
								}
								if (cc == 1)
								{
									break;
								}
								else if (cc == 2) {
									c2 = -1;
									goto page4;
								}
								else {
									cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
								}
							} while (cc != 1 || cc != 2);
						}
					} while (c2 != 0);
				}
				bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
				if (TotalBook > bookVector.size())//��Ҫ���������ļ�
				{
					int n = TotalBook / bookVector.size();
					for (int i = 0; i < n; i++)
					{
						int newStart = StrToInt(bookVector.back().getID()) + 1;
						bookVector.clear();
						bm.LoadFromFile(&bookVector, newStart, 100);
						bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
					}
				}
				bookVector.clear();
				do
				{
					
					cout << "\n\t**** �� ǰ����" << page << "ҳ" << "  һ�� " << searchResult.size() << "��" << endl;
					bm.ManagerShow(searchResult, page);
					cout << "\n\t**** 1. ɾ �� ��      **" << endl;
					cout << "\n\t**** 2. �� һ ҳ   **";
					cout << "\t**** 3. �� һ ҳ   **";
					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c2;
					}
					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� ɾ �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (c3<1 || c3>searchResult.size()|| cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << " �� �� �� �� ȷ �� �� ��" << endl;
							cin >> c3;
						}
						if (searchResult[c3 - 1].getStatus())
						{
							if (searchResult[c3 - 1].getCurrentCount() == searchResult[c3 - 1].getOCount())
							{
								bm.Delete(searchResult, c3, changedBooks);
								bm.Refresh(changedBooks);
								cout << "\n\t**** * * �� �� ɾ ��  * * ****" << endl;
								changedBooks.clear();
							}
							else
							{
								cout << "\n\t**** * *  �� �� Ŀ ǰ �� �� ������ �� ɾ ��  * * ****" << endl;
							}

						}
						else
						{
							cout << "\n\t**** * *  �� �� �� �� �� �� �ڣ��� �� ɾ ��  * * ****" << endl;
						}

					}

					if (c2 == 2)
					{
						int limit = (searchResult.size() % 20 == 0) ? ((searchResult.size() / 20) - 1) : (searchResult.size() / 20);
						if (page <= limit)
						{
							page++;
						}
						else
						{
							cout << "�� �� �� �� �� һ ҳ ��" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							page--;
						}
						else cout << "\n\t****  �� �� �� �� һ ҳ ��    **" << endl;
					}
					if (c2 == 0)
					{
						int cc;
						do
						{
							cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								break;
							}
							else if (cc == 2) {
								c2 = -1;
								goto page4;
							}
							else {
								cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
							}
						} while (cc != 1 || cc != 2);
					}
				} while (c2 != 0);
			}
			searchResult.clear();
			bookVector.clear();
			break;
			case 2:
			{
				int c2;
				int page = 1;		//��ǰҳ��
				do
				{
				page5:
					int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
					cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 1. ɾ ��    **" << " * * ע �⣺�� ͼ �� �� ǰ �� �� ������ �� �� ɾ ��  * * " << endl;
					cout << "\n\t**** 2. �� һ ҳ   **";
					cout << "\t**** 3. �� һ ҳ   **";
					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c2;
					}

					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� ɾ �� �� �� �� ��  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>bookVector.size()||cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << " �� �� �� �� ȷ �� �� �� " << endl;
							cin >> c3;
						}
						if (bookVector[c3 - 1].getStatus())
						{
							if (bookVector[c3 - 1].getCurrentCount() == bookVector[c3 - 1].getOCount())
							{
								bm.Delete(bookVector, c3, changedBooks);
								bm.Refresh(changedBooks);
								cout << "\n\t**** * * �� �� ɾ ��  * * ****" << endl;
								changedBooks.clear();
							}
							else
							{
								cout << "\n\t**** * *  �� �� Ŀ ǰ �� �� ������ �� ɾ ��  * * ****" << endl;
							}

						}
						else
						{
							cout << "\n\t**** * *  �� �� �� �� �� �� �ڣ��� �� ɾ ��  * * ****" << endl;
						}

					}
					if (c2 == 2)
					{
						
						if (page <= limit)
						{
							page++;
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.back().getID()) + 1;
								if (!changedBooks.empty())
								{

									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
						}
						else
						{
							cout << "�� �� �� �� �� һ ҳ ��" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.front().getID()) - 100;
								if (!changedBooks.empty())
								{
									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
							page--;
						}
						else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
					}
					if (c2 == 0) {
						int cc;
						do
						{
							cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								break;
							}
							else if (cc == 2) {
								c1 = -1;
								goto page5;
							}
							else {
								cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
							}
						} while (cc != 1 || cc != 2);
					}
				} while (c2 != 0);
			}
			break;
			case 0:
			{
				int cc;
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						return;
					else if (cc == 2) {
						c1 = -1;
						goto page4;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (cc != 1 || cc != 2);
			}
			break;
			default:
				break;
			}
		} while (c1 != 0);
	}

void Library::CorrectBook()
	{
	bool isLegal(char a[], int len);
		int c1;
		char input[17];
		vector<Book> searchResult;
		do {
		page6:
			searchResult.clear();
			bookVector.clear();
			TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
			cout << "\n\t\t\t**** 1. �� ��  **" << endl;
			cout << "\n\t\t\t**** 2. �� �� ȫ ��  **" << endl;
			cout << "\n\t\t\t**** 0.   ��  ��  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
				cin >> c1;
			}
			switch (c1)
			{
			case 1:
			{
				char sISBN[14];
				char sname[17];
				char sauthor[17];
				char spublishing[21];
				int c2;
				int page = 1;

				cout << "\n\t\t\t**** �� �� �� �� �� �� Ϣ�� �� �� �� ʹ �� ��#�� �� **" << endl;
#pragma region input
				cout << "\n\t\t\t**** 1. �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sname;
				cout << "\n\t\t\t**** 2. ISBN ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sISBN;
				cout << "\n\t\t\t**** 3. �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sauthor;
				cout << "\n\t\t\t**** 4. �� �� �� ��**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> spublishing;
#pragma endregion
				if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
				{
					int c2;
					int page = 1;		//��ǰҳ��
					do
					{
					page2:
						int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
						cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
						bm.ManagerShow(bookVector, page);
						cout << "\n\t**** 1. �� �� �� �� �� Ϣ      **" << endl;
						cout << "\n\t**** 2. �� һ ҳ   **";
						cout << "\t**** 3. �� һ ҳ   **";
						cout << "\t**** 0. �� ��   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c2;
						}

						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** �� �� �� �� �� �� �� �� �� ��  �� 0 �� ��**" << endl;
							cin >> c3;
							while (cin.fail() || c3<0 || c3>bookVector.size())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� �� �� Χ �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> c3;
							}
							if (c3 == 0)goto page2;
							if (bookVector[c3 - 1].getStatus())
							{
#pragma region input
								static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
								int ctype, cprice, cocount;
								do {
									cout << "\n\t**** �� �� �� �� �� ISBN  �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
									cin >> cisbn;
								} while (!isLegal(cisbn, sizeof(cisbn)));
								if (strcmp(cisbn, "0") == 0)goto page2;
								else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn,bookVector[c3-1].getISBN());

								do {
									cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
									cin >> cname;
								} while (!isLegal(cname, sizeof(cname)));

								if (strcmp(cname, "0") == 0)goto page2;
								else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

								do {
									cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ� -1 Ϊ �� �� ��  **" << endl;
									cin >> cauthor;
								} while (!isLegal(cauthor, sizeof(cauthor)));	
								if (strcmp(cauthor, "0") == 0)goto page2;
								else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
								cout << "\n\t**** �� �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;
								
								cin >> cpublishing;
								if (strcmp(cpublishing, "0") == 0)goto page2;
								else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
								cout << "\n\t**** �� ѡ �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;
								for (int i = 0; i < 22; i++)
								{
									if (i % 6 == 0)cout << endl;
									cout.setf(ios::left);
									cout << "** " << setw(4) << i + 1 << " **";
									cout << setw(20) << bookKind[i];
								}
								cout << "\n�� �� �� �� �ţ�" << endl;
								cin >> ctype;
								while (ctype < -1 || ctype>22||cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << " �� �� �� ȷ �� Χ �� ѡ �� �� �� ���� �� �� �� ��" << endl;
									cin >> ctype;
								}
								if (ctype == 0)goto page2;
								else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
								else ctype--;

								cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;
							
								cin >> cprice;
								while (cin.fail()||cprice<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� :" << endl;
									cin >> cprice;
								}
								if (cprice == 0)goto page2;
								else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
								input2:
								cout << "\n\t**** �� �� �� Ҫ �� �� �� �� �� �� �� �� �� �� �� �� 0 �� �أ� -1000 Ϊ �� �� ��  **" << endl;
								cout << "\n\t**** ���� �� �� �� �� ������ �� �� �� �� ����  **" << endl;
								
								cin >> cocount;
								while (cin.fail()||cocount<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> cocount;
								}
								if (cocount == 0)goto page2;
								else if (cocount == -1000)cocount = 0;
#pragma endregion
								if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
								{
									cout << "\n\t**** �� �� �� �� �� �� �� **" << endl;
									goto input2;
								}
								else
								{
								confirm2:
									cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
									cout << "\t\t\t** 1.ȷ��  **" << endl;
									cout << "\t\t\t** 2.ȡ��  **" << endl;
									int choice;
									cin >> choice;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> choice;
									}
									switch (choice)
									{
									case 1:
										bm.ChangeAll(bookVector, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
										cout << "\t\t\t** �� �� �� ��  **" << endl;
										cout << "\t\t\t** �� �� �� ͼ �� �� Ϣ �� ��  **" << endl;
										bm.Show(changedBooks);
										bm.Refresh(changedBooks);
										int c4;
										cout << "\t\t\t** �� �� 1 �� �� **" << endl;
										cin >> c4;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
											cin >> c4;
										}
										while (c4 != 1)
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "ֻ �� �� �� 1   " << "�� �� �� �� �� :" << endl;
											cin >> c4;
										}
										changedBooks.clear();
										goto page2;
									case 2:
										goto page2;
									default:
										cout << "\t\t\t** �� �� ȷ �� �� 1 �� 2  **" << endl;
										goto confirm2;
									}
								}
							}
							else
							{
								cout << "\n\t**** �� �� �� �� �� ɾ �� ���� �� �� ��  **" << endl;
							}

						}

						if (c2 == 2)
						{
							if (page <= limit)
							{
								page++;
								if (((page - 1) % 5) == 0)
								{
									int newStart = StrToInt(bookVector.back().getID()) + 1;
									if (!changedBooks.empty())
									{
										bm.Refresh(changedBooks);
										changedBooks.clear();
									}
									bookVector.clear();
									bm.LoadFromFile(&bookVector, newStart, 100);
								}
							}
							else
							{
								cout << "�� �� �� �� �� һ ҳ ��" << endl;
							}
						}
						if (c2 == 3)
						{
							if (page != 1)
							{
								if (((page - 1) % 5) == 0)
								{
									int newStart = StrToInt(bookVector.front().getID()) - 100;
									if (!changedBooks.empty())
									{
										bm.Refresh(changedBooks);
										changedBooks.clear();
									}
									bookVector.clear();
									bm.LoadFromFile(&bookVector, newStart, 100);
								}
								page--;
							}
							else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
						}

						if (c2 == 0)
						{
							int cc;
							do {
								cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
								cout << "\t\t\t** 1.ȷ��  **" << endl;
								cout << "\t\t\t** 2.ȡ��  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> cc;
								}
								if (cc == 1)
									break;
								else if (cc == 2) {
									c2 = -1; break;
								}
								else {
									cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
								}
							} while (cc != 1 || cc != 2);
						}
					} while (c2 != 0);
					break;
				}
				
				bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
				if (TotalBook > bookVector.size())//��Ҫ���������ļ�
				{
					int n = TotalBook / bookVector.size();
					if (TotalBook % 100 == 0)n--;
					for (int i = 0; i < n; i++)
					{
						int newStart = StrToInt(bookVector.back().getID()) + 1;
						bookVector.clear();
						bm.LoadFromFile(&bookVector, newStart, 100);
						bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
					}
				}
				bookVector.clear();

				if (searchResult.empty())
				{
					cout << "\n\t**** û �� �� �� �� �� ͼ ��   **" << endl;
				}
				else
				{
					int nPage = 1;
					int n2 = 1;
					int nStart;
					int nLimit = searchResult.size() / numOfOnePage;
					do
					{
					page1:
						cout << "\n\t**** �� ǰ����" << page << "ҳ" << "  һ ��  " << searchResult.size() << " �� " << endl;
						bm.ManagerShow(searchResult, page);
						cout << "\n\t**** 1. �� ��     **" << endl;
						cout << "\n\t**** 2. �� һ ҳ   **";
						cout << "\t**** 3. �� һ ҳ   **";
						cout << "\t**** 0. �� ��   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c1;
						}
						//�˴�Ӧ�ж϶����Ƿ���Ȩ�޽���

						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** �� �� �� �� �� �� �� �� �� �� �� �� 0 �� ��  **" << endl;
							cin >> c3;
							while (cin.fail()|| c3<0 || c3>searchResult.size())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� �� �� Χ �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> c3;
							}
							if (c3 == 0)goto page1;
							if (searchResult[c3 - 1].getStatus())
							{
#pragma region input
								static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
								int ctype, cprice, cocount;
								do {
									cout << "\n\t**** �� �� �� �� �� ISBN  �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
									cin >> cisbn;
								} while (!isLegal(cisbn, sizeof(cisbn)));
								if (strcmp(cisbn, "0") == 0)goto page1;
								else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn, bookVector[c3 - 1].getISBN());

								do {
									cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
									cin >> cname;
								} while (!isLegal(cname, sizeof(cname)));

								if (strcmp(cname, "0") == 0)goto page1;
								else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

								do {
									cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ� -1 Ϊ �� �� ��  **" << endl;
									cin >> cauthor;
								} while (!isLegal(cauthor, sizeof(cauthor)));
								if (strcmp(cauthor, "0") == 0)goto page1;
								else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
								cout << "\n\t**** �� �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;

								cin >> cpublishing;
								if (strcmp(cpublishing, "0") == 0)goto page1;
								else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
								cout << "\n\t**** �� ѡ �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;
								for (int i = 0; i < 22; i++)
								{
									if (i % 6 == 0)cout << endl;
									cout.setf(ios::left);
									cout << "** " << setw(4) << i + 1 << " **";
									cout << setw(20) << bookKind[i];
								}
								cout << "\n�� �� �� �� �ţ�" << endl;
								cin >> ctype;
								while (ctype < -1 || ctype>22 || cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << " �� �� �� ȷ �� Χ �� ѡ �� �� �� ���� �� �� �� ��" << endl;
									cin >> ctype;
								}
								if (ctype == 0)goto page1;
								else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
								else ctype--;

								cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;

								cin >> cprice;
								while (cin.fail() || cprice<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� :" << endl;
									cin >> cprice;
								}
								if (cprice == 0)goto page1;
								else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
							input1:
								cout << "\n\t**** �� �� �� Ҫ �� �� �� �� �� �� �� �� �� �� �� �� 0 �� �أ� -1000 Ϊ �� �� ��  **" << endl;
								cout << "\n\t**** ���� �� �� �� �� ������ �� �� �� �� ����  **" << endl;

								cin >> cocount;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> cocount;
								}
								if (cocount == 0)goto page1;
								else if (cocount == -1000)cocount = 0;
								if (searchResult[c3 - 1].getCurrentCount() + cocount < 0)
								{
									cout << "\n\t**** �� �� �� �� �� �� �� **" << endl;
									goto input1;
								}
#pragma endregion
								confirm1:
										cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
										cout << "\t\t\t** 1.ȷ��  **" << endl;
										cout << "\t\t\t** 2.ȡ��  **" << endl;
										int choice;
										cin >> choice;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
											cin >> choice;
										}
										switch (choice)
										{
										case 1:
											bm.ChangeAll(searchResult, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
											cout << "\t\t\t** �� �� �� ��  **" << endl;
											cout << "\t\t\t** �� �� �� ͼ �� �� Ϣ �� ��  **" << endl;
											bm.Show(changedBooks);
											bm.Refresh(changedBooks);
											int c4;
											cout << "\t\t\t** �� �� 1 �� �� **" << endl;
											cin >> c4;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
												cin >> c4;
											}
											while (c4 != 1)
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "ֻ �� �� �� 1   " << "�� �� �� �� �� :" << endl;
												cin >> c4;
											}
											changedBooks.clear();
											goto page1;
										case 2:
											goto page1;
										default:
											cout << "\t\t\t** �� �� ȷ �� �� 1 �� 2  **" << endl;
											goto confirm1;
										}

							}
							else {
								cout << "\n\t**** �� �� �� �� �� ɾ �� ���� �� �� ��  **" << endl;
							}
						}
					
						if (c2 == 2)
						{
							int limit = (searchResult.size() % 20 == 0) ? ((searchResult.size() / 20) - 1) : (searchResult.size() / 20);
							if (page <= limit)
							{
								page++;
							}
							else
							{
								cout << "�� �� �� �� �� һ ҳ ��" << endl;
							}
						}
						if (c2 == 3)
						{
							if (page != 1)
							{
								page--;
							}
							else cout << "\n\t****  �� �� �� �� һ ҳ ��    **" << endl;
						}
						if (c2 == 0) {
							searchResult.clear();
						}
					} while (c2 != 0);
				}
			}
			searchResult.clear();
			bookVector.clear();
			break;
			case 2:
			{
				int c2;
				int page = 1;		//��ǰҳ��
				do
				{
				page3:
					int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
					cout << "\n\t**** �� ǰ����" << page << "ҳ" << " һ�� " << limit + 1 << "ҳ " << "  һ�� " << TotalBook << "��" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 1. �� �� ��      **" << endl;
					cout << "\n\t**** 2. �� һ ҳ   **";
					cout << "\t**** 3. �� һ ҳ   **";
					cout << "\t**** 0. �� ��   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> c2;
					}

					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** �� �� �� �� �� �� �� �� �� ��  �� 0 �� ��**" << endl;
						cin >> c3;
						while (cin.fail()|| c3<0 || c3>bookVector.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "ֻ �� �� �� �� �� �� Χ �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
							cin >> c3;
						}
						if (c3 == 0)goto page3;
						if (bookVector[c3 - 1].getStatus())
						{
#pragma region input
							static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
							int ctype, cprice, cocount;
							do {
								cout << "\n\t**** �� �� �� �� �� ISBN  �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
								cin >> cisbn;
							} while (!isLegal(cisbn, sizeof(cisbn)));
							if (strcmp(cisbn, "0") == 0)goto page3;
							else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn, bookVector[c3 - 1].getISBN());

							do {
								cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� �� **" << endl;
								cin >> cname;
							} while (!isLegal(cname, sizeof(cname)));

							if (strcmp(cname, "0") == 0)goto page3;
							else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

							do {
								cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ� -1 Ϊ �� �� ��  **" << endl;
								cin >> cauthor;
							} while (!isLegal(cauthor, sizeof(cauthor)));
							if (strcmp(cauthor, "0") == 0)goto page3;
							else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
							cout << "\n\t**** �� �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;

							cin >> cpublishing;
							if (strcmp(cpublishing, "0") == 0)goto page3;
							else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
							cout << "\n\t**** �� ѡ �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;
							for (int i = 0; i < 22; i++)
							{
								if (i % 6 == 0)cout << endl;
								cout.setf(ios::left);
								cout << "** " << setw(4) << i + 1 << " **";
								cout << setw(20) << bookKind[i];
							}
							cout << "\n�� �� �� �� �ţ�" << endl;
							cin >> ctype;
							while (ctype < -1 || ctype>22 || cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << " �� �� �� ȷ �� Χ �� ѡ �� �� �� ���� �� �� �� ��" << endl;
								cin >> ctype;
							}
							if (ctype == 0)goto page3;
							else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
							else ctype--;

							cout << "\n\t**** �� �� �� �� �� �� �� �� 0 �� �أ�-1 Ϊ �� �� ��  **" << endl;

							cin >> cprice;
							while (cin.fail() || cprice<-1)
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� :" << endl;
								cin >> cprice;
							}
							if (cprice == 0)goto page3;
							else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
						input3:
							cout << "\n\t**** �� �� �� Ҫ �� �� �� �� �� �� �� �� �� �� �� �� 0 �� �أ� -1000 Ϊ �� �� ��  **" << endl;
							cout << "\n\t**** ���� �� �� �� �� ������ �� �� �� �� ����  **" << endl;

							cin >> cocount;
							while (cin.fail() )
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cocount;
							}
							if (cocount == 0)goto page3;
							else if (cocount == -1000)cocount = 0;
							if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
							{
								cout << "\n\t**** �� �� �� �� �� �� �� **" << endl;
								goto input3;
							}
#pragma endregion
							if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
							{
								cout << "\n\t**** �� �� �� �� �� �� �� **" << endl;
								goto page3;
							}
							else
							{
							confirm3:
								cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
								cout << "\t\t\t** 1.ȷ��  **" << endl;
								cout << "\t\t\t** 2.ȡ��  **" << endl;
								int choice;
								cin >> choice;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
									cin >> choice;
								}
								switch (choice)
								{
								case 1:
									bm.ChangeAll(bookVector, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
									cout << "\t\t\t** �� �� �� ��  **" << endl;
									cout << "\t\t\t** �� �� �� ͼ �� �� Ϣ �� ��  **" << endl;
									bm.Show(changedBooks);
									bm.Refresh(changedBooks);
									int c4;
									cout << "\t\t\t** �� �� 1 �� �� **" << endl;
									cin >> c4;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
										cin >> c4;
									}
									while (c4 != 1)
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "ֻ �� �� �� 1   " << "�� �� �� �� �� :" << endl;
										cin >> c4;
									}
									changedBooks.clear();
									goto page3;
								case 2:
									goto page3;
								default:
									cout << "\t\t\t** �� �� ȷ �� �� 1 �� 2  **" << endl;
									goto confirm3;
								}
							}
						}
						else
						{
							cout << "\n\t**** �� �� �� �� �� ɾ �� ���� �� �� ��  **" << endl;
						}

					}
					if (c2 == 2)
					{
						
						if (page <= limit)
						{
							page++;
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.back().getID()) + 1;
								if (!changedBooks.empty())
								{

									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
						}
						else
						{
							cout << "�� �� �� �� �� һ ҳ ��" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							if (((page - 1) % 5) == 0)
							{
								int newStart = StrToInt(bookVector.front().getID()) - 100;
								if (!changedBooks.empty())
								{
									bm.Refresh(changedBooks);
									changedBooks.clear();
								}
								bookVector.clear();
								bm.LoadFromFile(&bookVector, newStart, 100);
							}
							page--;
						}
						else cout << "\n\t****  �Ѿ��ǵ�һҳ��    **" << endl;
					}
					if (c2 == 0) {
						int cc;
						do
						{
							cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
							cout << "\t\t\t** 1.ȷ��  **" << endl;
							cout << "\t\t\t** 2.ȡ��  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								break;
							}
							else if (cc == 2) {
								c1 = -1;
								goto page3;
							}
							else {
								cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
							}
						} while (cc != 1 || cc != 2);
					}
				} while (c2 != 0);
				bookVector.clear();
			}
			break;
			case 0:
			{
				int cc;
				do {
					cout << "\t\t\t** ȷ �� �� �� �� ��  **" << endl;
					cout << "\t\t\t** 1.ȷ��  **" << endl;
					cout << "\t\t\t** 2.ȡ��  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "ֻ �� �� �� �� ��   " << "�� �� �� �� �� �� ��:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						return;
					else if (cc == 2) {
						c1 = -1;
						goto page6;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** ����ȷ����1��2ѡ��  **" << endl;
					}
				} while (cc != 1 || cc != 2);
			}
			break;
			default:
				break;
			}
		} while (c1 != 0);

	}

