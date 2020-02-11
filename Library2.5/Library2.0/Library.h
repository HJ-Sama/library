#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include"Manager.h"
#include <iomanip>
#include<cstring>
using namespace std;
int StrToInt(const char* str)//字符型数组转换成整形  
{
	if (str == NULL || *str == '\0')
	{
		return 0;
	}
	long long ID = 0;
	int sign = 1;
	while (*str == ' ')//遇到空格就跳过  
	{
		str++;
	}
	if (*str == '+')//遇到‘+’表示是整数  
	{
		str++;
	}
	else if (*str == '-')//遇到‘-’表示是负数  
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
	return (int)ID;//注意将返回值转换为int型  
}

char * getNowTime() {
	char bTime[26] = { 0 };                    //借书时间
	time_t nowTime = time(NULL);
	tm * pbTime = localtime(&nowTime);
	strftime(bTime, 26, "%Y-%m-%d %H:%M:%S", pbTime);
	return bTime;
}
char * getSReturnTime() {
	char sTime[26] = { 0 };                    //应还书时间, 默认一个月30 * 24 * 3600
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
vector<Record> record;                  //专门供加载使用的动态数组, 每次运行初始化时长度为 0
vector<Record> historyRecord;           //为加载历史记录准备
vector<Record> reservationRecord;
vector<Book> bookVector;                         //读取的书籍
vector<Book> changedBooks;                        //删除的书籍
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
		char Account[9] = "";					//输入的账户
		char Input[17] = "";					//输入的密码
		int choice2;   //初始界面选择
		int k = 0;
		cout << "\n\t\t\t 欢 迎 光 临 图 书 馆 管 理 系 统!" << endl;
		cout << "\n\t\t\t用于测试，管理员用户名admin，密码666" << endl;
		do
		{
			cout << "\t\t\t ** 1. 登 录 **" << endl;
			cout << "\t\t\t ** 2. 注 册 **" << endl;
			cout << "\t\t\t ** 0. 退 出 **" << endl;
			cout << "\t\t\t 请 选 择: ";
			cin >> choice2;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
				cin >> choice2;
			}
			switch (choice2)
			{
			case 1:
			{
				TotalUser = um.LoadFromFile(&users, 1, 100);
				cout << "请输入用户名" << endl;
				cout << "例：" << endl << "00000001" << endl;
				cin >> Account;
				if (strcmp(admin, Account) == 0)
				{
					cout << "请输入密码" << endl;
					cin >> Input;
					if (strcmp(adminpass, Input) == 0)
					{
						cout << "管理员登录成功" << endl;
						EnterManagerDesk();
						break;
					}
					else
					{
						cout << "密 码 错 误" << endl;
						break;
					}
				}
				um.Search(users, userSearchResult, Account);
				if (TotalUser > users.size())//需要遍历整个文件
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
					cout << "没 有 此 用 户，请 检 查 用 户 名" << endl;
					break;
				}

				cout << "请输入密码" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> Input;
				if (strcmp(userSearchResult[0].getUserPassword(), Input) == 0)
				{
					k = 0;
					cout << "\t\t\t 登 录 成 功，欢 迎 您 ！" << endl;
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
					cout << "密 码 错 误" << endl;
					userSearchResult.clear();
					k++;
					cout << "您还有" << 3 - k << "次登陆机会" << endl;
					if (k >= 3)
					{
						cout << "您已超过登录次数上限，系统自动退出!" << endl;
						return 1;
					}
					continue;
				}
			}
			break;
			case 2:
			{
				int cc;
				cout << "\t\t\t 确 认 要 注 册 吗" << endl;
				cout << "\t\t\t ** 1. 确 认 **" << endl;
				cout << "\t\t\t ** 2. 取 消 **" << endl;
				cin >> cc;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
					cin >> cc;
				}
				switch (cc)
				{
				case 1:
				{int newID = 0;
				if (um.Add(1, &newID))
				{
					cout << "\t\t\t 注 册 成 功，已 登 入 系 统" << endl;
					sprintf(cAccount, "%08d", newID);
					cout << "\t\t\t 您 的 账 号 为  " << cAccount;
					cout << "\t 初 始 密 码 为  " << dPassword << endl;
					cout << "\t\t\t 请 尽 快 修 改 密 码 并 完 善 个 人 信 息" << endl;
					user.setUserAccount(cAccount);
					user.setUserPassword(dPassword);
					EnterUserDesk();
				}
				}
				break;
				case 2:
					break;
				default:
					cout << "只 能 输 入 1或2   " << "请 重 新 输 入 数 字:" << endl;
				}
				break;
			}
			case 0:
				return 1;
			default:
				cout << "只 能 输 入 0或1或2   " << "请 重 新 输 入 数 字:" << endl;
			}
		} while (choice2 != 0);
		return 1;

	}
	void EnterManagerDesk()
	{
		char choice;
		do
		{
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
			cout << "\t\t\t** 1.用 户 信 息 管 理 **\n" << endl;
			cout << "\t\t\t** 2.图 书 信 息 管 理 **\n" << endl;
			cout << "\t\t\t** 0.  退 出  **" << endl;
			cout << "\t\t\t 请选择：";
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
				cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
				cout << "\t\t\t** 1.确认  **" << endl;
				cout << "\t\t\t** 2.取消  **" << endl;
				int i;
				cin >> i;
				if (i == 1)
				{
					return;
				}
				else if (i == 2) choice = ' ';
				else cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
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
			//还得做判断, 如果当前用户没有借阅记录(该文件中不含有该用户的ID时)
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
					cout << "\t\t* * * * 您 有 预 约 记 录 已 经 过 期 * 具 体 请 查 看 预 约 记 录 * * *" << endl;
				}
			}
		}
#pragma endregion
		int choice;   //用户界面选择
		do
		{
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
			cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n\n";
			if (user.getStatus() == 0)
			{
				cout << "\t\t* * * * 您 的 账 户 已 被 冻 结 * * * *\n" << endl;
				cout << "\t\t* * * * 请 尽 快 归 还 逾 期 图 书 * * * *\n" << endl;
				cout << "\t\t* * * * 若 有 疑 问 请 咨 询 管 理 员 * * * *\n" << endl;
			}
			cout << "\t\t\t** 1.个 人 信 息 **\n" << endl;
			cout << "\t\t\t** 2.借 阅 记 录 **\n" << endl;
			cout << "\t\t\t** 3.历 史 记 录 **\n" << endl;
			cout << "\t\t\t** 4.借 阅 预 约 图 书 **\n" << endl;
			cout << "\t\t\t** 5.预 约 记 录 **\n" << endl;
			cout << "\t\t\t** 0.  退 出  **\n" << endl;
			cout << "\t\t\t 请选择：";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
					cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
						cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
				break;
			}
		} while (choice != 0);
	}
	void EnterUserInfo()
	{
		vector<User> user1;
		int choice;   //用户界面选择
		do
		{
			cout << "\n\t\t\t**** 图 书 管 理 系 统****";
			cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n\n";
			um.Show(user);
			cout << "\t\t\t**** 若需要修改，请选择：" << endl;
			cout << "\t\t\t**** 1.修改个人信息，9.修改密码,0为返回" << endl;
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\t\t只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
				cin >> choice;
			}
			switch (choice)
			{
			case 1: 
				cout << "\t\t是否确认修改,确认请输入1，取消输入0:" << endl;
				int a;
				cin >> a;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
					cin >> choice;
				}
				if (a == 1)
				{
					if (um.Change(user))
					{
						cout << "\t\t ** 修 改 成 功 **" << endl;
					}
					else
					{
						cout << " 修 改 失 败 " << endl;
					}
				}
				else if (a == 0)
				{
				}
				else {
					cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
				}
				break;
			case 9:
				int c;
				do {
					cout << endl << "\t\t\t** 请 选 择 1.修 改   0.返 回  **" << endl;
					cin >> c;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> choice;
						cin.clear();
						cin.sync();
					}
					if (c == 1) {
					p100:
						getchar();
						char p1[30];
						cout << endl << "\t\t\t** 请 输 入 新 密 码   **" << endl;
						cin.get(p1, 30);
						if (strlen(p1) >= passwordLength)
						{
							cout << "超出给定长度，请重新输入..." << endl;
							goto p100;
						}
						//遍历密码, 判断有没有空格, 有空格时, 重新输入
						int i = 0;
						bool status = false;
						while (p1[i]) {
							if (p1[i] == ' ') {
								cout << "密码中含有空格, 请重新输入..." << endl;
								status = true;
								break;
							}
							i++;
						}
						if (status) {
							goto p100;
						}
						getchar();
						cout << "\t\t\t** 再 次 输 入 新 密 码 以 确 认   **" << endl;
						char p2[passwordLength];
						cin.get(p2, passwordLength);
						if (strcmp(p1, p2) == 0)
						{
							cout << "\t\t\t** 确 认 修 改 吗 ？1.确认 2.返回 **" << endl;
							int i;
							cin >> i;
							if (i == 1)
							{
								um.userChangePassword(user, p2);
								//l1.RefreshFile(userInfo, 1, (StrToInt(currentAccount) % 100) - 1);
								cout << "\t\t\t** 修 改 密 码 成 功 !!! **" << endl;
								user1.push_back(user);
								um.RefreshUser(user1);
								return;
							}
							else if (i == 2) break;
							else cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
						}
						else
						{
							cout << "\t\t******** 两 次 输 入 密 码 不 同，请 重 新 输 入  ********" << endl;
						}
					}
				} while (c != 0);
				break;
			case 0:
				cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
				cout << "\t\t\t** 1.确认  **" << endl;
				cout << "\t\t\t** 2.取消  **" << endl;
				int i;
				cin >> i;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
					cin >> choice;
				}
				if (i == 1)
				{
				}
				else if (i == 2) choice =-1;
				else cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
				break;
			default:
				cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
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
				cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
				cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n";
				cout << "\n\t\t\t**** 检 索 图 书 界 面 ****\n";
				
				cout << "\n\t\t\t**** 1.   检  索  **" << endl;
				cout << "\n\t\t\t**** 2.   查  看  全  部  **" << endl;
				cout << "\n\t\t\t**** 0.   返  回  **" << endl;
				cin >> c1;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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

					cout << "\n\t\t\t**** 请 输 入 相 关 信 息（ 不 填 的 使 用 ‘#’ ） **" << endl;
#pragma region input
					cout << "\n\t\t\t**** 1. 书 名 ：**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sname;
					cout << "\n\t\t\t**** 2. ISBN ：**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sISBN;
					cout << "\n\t\t\t**** 3. 作 者 ：**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> sauthor;
					cout << "\n\t\t\t**** 4. 出 版 社 ：**" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> spublishing;
#pragma endregion
					if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
					{
						int c2;
						int page = 1;		//当前页码
						do
						{
							int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) -1) : (TotalBook / 20);
							cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
							bm.Show(bookVector, page);
							cout << "\n\t**** 1. 借 书      **" << endl;
							cout << "\n\t**** 4. 预 约      **" << endl;
							cout << "\n\t**** 2. 下 一 页   **";
							cout << "\t**** 3. 上 一 页   **";
							cout << "\t**** 0. 返 回   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> c2;
							}

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									int c3;
									cout << "\n\t**** 请 输 入 想 借 书 的 序 号  **" << endl;
									cin >> c3;
									while (c3<1 || c3>bookVector.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "输入序号不正确，请重新输入" << endl;
										cin >> c3;
									}
									if (bookVector[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
											cout << "\t\t\t** 确 认 借 此 本 书 吗 ？  **" << endl;
											cout << "\t\t\t** 1.确认  **" << endl;
											cout << "\t\t\t** 2.取消  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{

												bm.Change(bookVector, c3, -1, changedBooks);
												rm.Add(record, cAccount, bookVector[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  借 书 成 功 ！ **" << endl;

											}
											else if (cc == 2);
											else
											{
												cout << " 请正确输入1或2选择" << endl;
											}
										}
										else
										{
											cout << "\t\t\t**  该 书 可 借 数 量 不 足，不 可 借**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  该 书 已 不 存 在，不 可 借**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  借 书 数 量 已 达 上 限 **" << endl;
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
									cout << "已 经 是 最 后 一 页 了" << endl;
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
								else cout << "\n\t****  已经是第一页了    **" << endl;
							}
							if (c2 == 4)
							{
								if (user.getreservationNum() > 0)
								{
									int c3;
									cout << "\n\t**** 请 输 入 想 预 约 的 序 号  **" << endl;
									cin >> c3;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> c3;
									}
									while (c3<1 || c3>bookVector.size())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "输入序号不正确，请重新输入" << endl;
										cin >> c3;
									}
									int cc;
									cout << "\t\t\t** 确 认 预 约 此 本 书 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
											cout << "\t\t\t**  预 约 成 功 **" << endl;
										}
										else
										{
											cout << "\t\t\t**  该 书 已 不 存 在，不 可 预 约**" << endl;
										}

									}
									else if (cc == 2);
									else
									{
										cout << " 请正确输入1或2选择" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  预 约 数 量 已 达 上 限**" << endl;
								}
							}
							if (c2 == 0)
							{
								int cc;
								do {
									cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> cc;
									}
									if (cc == 1)
										break;
									else if (cc == 2) {
										c2 = -1; break;
									}
									else {
										cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
									}
								} while (cc != 1 || cc != 2);
							}
						} while (c2 != 0);
						bm.Refresh(changedBooks);
						changedBooks.clear();
						break;
					}		
					
					bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
					if (TotalBook > bookVector.size())//需要遍历整个文件
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
						cout << "\n\t**** 没 有 找 到 相 关 图 书   **" << endl;
					}
					else
					{	
						int nLimit = searchResult.size() / numOfOnePage;
						do
						{
							number0:
							cout << "\n\t**** 当 前：第" << page << "页" << "  一共 " << searchResult.size() << "本" << endl;
							bm.Show(searchResult, page);
							cout << "\n\t**** 1. 借 书      **" << endl;
							cout << "\n\t**** 4. 预 约      **" << endl;
							cout << "\n\t**** 2. 下 一 页   **";
							cout << "\t**** 3. 上 一 页   **";
							cout << "\t**** 0. 返 回   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> c2;
							}
							//此处应判断读者是否还有权限借书

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									int c3;
									cout << "\n\t**** 请 输 入 想 借 书 的 序 号  **" << endl;
									cin >> c3;
									while (c3<1 || c3>searchResult.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "输入序号不正确，请重新输入" << endl;
										cin >> c3;
									}
									if (searchResult[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
										confirm1:
											cout << "\t\t\t** 确 认 借 此 本 书 吗 ？  **" << endl;
											cout << "\t\t\t** 1.确认  **" << endl;
											cout << "\t\t\t** 2.取消  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{
												bm.Change(searchResult, c3, -1, changedBooks);
												rm.Add(record, cAccount, searchResult[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  借 书 成 功 ！ **" << endl;
											}
											else if (cc == 2);
											else
											{
												cout << " 请正确输入1或2选择" << endl;
												goto confirm1;
											}
										}
										else
										{
											cout << "\t\t\t**  该 书 可 借 数 量 不 足，不 可 借**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  该 书 已 不 存 在，不 可 借**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  借 书 数 量 已 达 上 限**" << endl;
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
									cout << "已 经 是 最 后 一 页 了" << endl;
								}
							}
							if (c2 == 3)
							{
								if (page != 1)
								{
									page--;
								}
								else cout << "\n\t****  已 经 是 第 一 页 了    **" << endl;
							}
							if (c2 == 4)
							{
								if (user.getreservationNum() > 0)
								{
									int c3;
									cout << "\n\t**** 请 输 入 想 预 约 的 序 号  **" << endl;
									cin >> c3;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> c3;
									}
									while (c3<1 || c3>searchResult.size())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "输入序号不正确，请重新输入" << endl;
										cin >> c3;
									}
									int cc;
									cout << "\t\t\t** 确 认 预 约 此 本 书 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> cc;
									}
									if (cc == 1)
									{
										if (searchResult[c3 - 1].getStatus())
										{
												bm.Change(searchResult, c3, -1, changedBooks);
												rm.Add(reservationRecord, cAccount, searchResult[c3 - 1], userMaxReservation);
												user.setReservationNum(user.getreservationNum() - 1);
												cout << "\t\t\t**  预 约 成 功 **" << endl;
										}
										else
										{
											cout << "\t\t\t**  该 书 已 不 存 在，不 可 预 约**" << endl;
										}

									}
									else if (cc == 2);
									else
									{
										cout << " 请正确输入1或2选择" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  预 约 数 量 已 达 上 限**" << endl;
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
						int page = 1;		//当前页码
						do
						{
							int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20)-1 ) : (TotalBook / 20);
							cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
							bm.Show(bookVector, page);
							cout << "\n\t**** 1. 借 书      **" << endl;
							cout << "\n\t**** 4. 预 约      **" << endl;
							cout << "\n\t**** 2. 下 一 页   **";
							cout << "\t**** 3. 上 一 页   **";
							cout << "\t**** 0. 返 回   **" << endl;
							cin >> c2;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> c2;
							}

							//此处应判断读者是否还有权限借书

							if (c2 == 1)
							{
								if (user.getBookNum() > 0)
								{
									
									int c3;
									cout << "\n\t**** 请 输 入 想 借 书 的 序 号  **" << endl;
									cin >> c3;
								
									while (c3<1 || c3>bookVector.size()|| cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "输入序号不正确，请重新输入" << endl;
										cin >> c3;
									}
									if (bookVector[c3 - 1].getStatus())
									{
										if (bookVector[c3 - 1].getCurrentCount() > 0)
										{
											int cc;
										confirm3:
											cout << "\t\t\t** 确 认 借 此 本 书 吗 ？  **" << endl;
											cout << "\t\t\t** 1.确认  **" << endl;
											cout << "\t\t\t** 2.取消  **" << endl;
											cin >> cc;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
												cin >> cc;
											}
											if (cc == 1)
											{

												bm.Change(bookVector, c3, -1, changedBooks);
												rm.Add(record, cAccount, bookVector[c3 - 1], userMaxBook);
												user.setBookNum(user.getBookNum() - 1);
												cout << "\t\t\t**  借 书 成 功 ！ **" << endl;
											}
											else if (cc == 2);
											else
											{
												cout << " 请正确输入1或2选择" << endl;
												goto confirm3;
											}
										}
										else
										{
											cout << "\t\t\t**  该 书 可 借 数 量 不 足，不 可 借**" << endl;
										}
										
									}
									else
									{
										cout << "\t\t\t**  该 书 已 不 存 在，不 可 借**" << endl;
									}
								}
								else
								{
									cout << "\t\t\t**  借 书 数 量 已 达 上 限 **" << endl;
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
									cout << "已 经 是 最 后 一 页 了" << endl;
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
								else cout << "\n\t****  已经是第一页了    **" << endl;
							}
							if (c2 == 4)
							{
								int c3;
								cout << "\n\t**** 请 输 入 想 预 约 的 序 号  **" << endl;
								cin >> c3;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> c3;
								}
								while (c3<1 || c3>bookVector.size())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "输入序号不正确，请重新输入" << endl;
									cin >> c3;
								}
								int cc;
								cout << "\t\t\t** 确 认 预 约 此 本 书 吗 ？  **" << endl;
								cout << "\t\t\t** 1.确认  **" << endl;
								cout << "\t\t\t** 2.取消  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
											cout << "\t\t\t**  预 约 成 功 **" << endl;
										}
										else
										{
											cout << "\t\t\t**  预 约 数 量 已 达 上 限**" << endl;
										}
									}
									else
									{
										cout << "\t\t\t**  该 书 已 不 存 在，不 可 预 约**" << endl;
									}

								}
								else if (cc == 2);
								else
								{
									cout << " 请正确输入1或2选择" << endl;
								}
							}
							if (c2 == 0)
							{
								int cc;
								do {
									cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> cc;
									}
									if (cc == 1)
										break;
									else if (cc == 2) {
										c2 = -1; break;
									}
									else {
										cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
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
						cout << "\t\t\t** 确 认 返 回 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
							cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
				}
			} while (c1 != 0);
			um.RefreshUser(user);
			
			rm.UpdateRecord(record, userPosition, cAccount,recordPath,userMaxBook);
			rm.UpdateRecord(reservationRecord, (userPosition % 2) + 2, cAccount, reservationRecordPath, 3);
		}
		else
		{
			cout << "\t\t\t** 你 已 经 不 能 借 书  **" << endl;
			cout << "\t\t\t** 请 归 还 逾 期 图 书  **" << endl;
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
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n";
			cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n";
			cout << "\n\t\t\t**** 用 户 借 阅 记 录****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "序号";
			cout << "** " << setw(8) << "图书ID";
			cout << "** " << setw(30) << "书名";
			cout << "** " << setw(20) << "借书日期";
			cout << "** " << setw(20) << "应还日期" << endl;
			rm.Show(record);
			if (user.getBookNum() == 5)
			{
				cout << "\n\t\t\t**** 无 借 阅 记 录****\n\n" << endl;
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
					cout << "\t\t* * * * 序 号 为 "<<  pos[i] << " 的 书 已 经 逾 期 ，请 尽 快 归 还 * * * *" << endl;
					cout << "\t\t\t****  您 的 账 户 已 经 被 冻 结  **" << endl;
				}
				cout << "\t\t\t** 1.  还 书  **" << endl;
				cout << "\t\t\t** 0.  退 出  **" << endl;
				cout << "\t\t\t 请选择：";
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
					cin >> choice;
				}
				switch (choice)
				{
				case 1:
					int c2;
					do
					{
						cout << "\n\t\t\t****  请 输 入 序 号 归 还 相 应 图 书  **" << endl;
						cout << "\n\t\t\t****  或 输 入 0 返 回  **" << endl;
						cin.clear();
						cin.ignore(100, '\n');
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c2;
						}
						if (c2<1 || c2>record.size())
						{
							cout << "\t\t****** 请正确输入序号******" << endl;
						}
						else if (!record[c2 - 1].enabled)
						{
							int cc;
							cout << "\t\t\t** 确 认 归 还 此 本 书 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
											cout << "\t\t* * * * 您 归 还 的 图 书 已 经 逾 期 * * * *" << endl;
											cout << "\t\t* * * * 您 的 可 借 图 书 已 经 减 少 一 本 作 为 惩 罚 * * * *" << endl;
											user.setBookNum(user.getBookNum() - 1);
											cout << "\t\t* * * * 您 当 前 的 可 借 图 书 数 量 为 "<< user.getBookNum() << " 本 * * * *" << endl;
											cout << "\t\t* * * * 如 需 解 除 逾 期 惩 罚 请 咨 询 管 理 员 * * * *" << endl;
										}
									}
									if (pos.empty())
									{
										cout << "\n\t*** * * * 您 已 归 还 全 部 逾 期 书 籍，账 户 已 经 解 冻 * * * ***" << endl;
										cout << "\t*** * * * 之 后 请 按 时 还 书， 养 成 良 好 习 惯 * * * ***\n" << endl;
										user.setStatus(1);
									}
									else
									{
										cout << "\n\t\t* * * * 您 还 没 有 归 还 所 有 逾 期 图 书* * * *\n" << endl;
										
									}
								}
								pos.clear();
								break;
								
							}
							else if (cc == 2);
							else
							{
								cout << " 请正确输入1或2选择" << endl;
							}
						}
						else {
							cout << "请 正 确 输 入 序 号"<<endl;
						}

					} while (c2 != 0);
					break;
				case 0:
					int cc;
					do {
						cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)		//退出并刷新文件
						{	
							break;
						}
						else if (cc == 2) {
							choice = -1; break;
						}
						else {
							cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
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
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
			cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n\n";
			cout << "\n\t\t\t**** 用 户 历 史 记 录****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "序号";
			cout << "** " << setw(8) << "图书ID";
			cout << "** " << setw(30) << "书名";
			cout << "** " << setw(20) << "借书日期";
			cout << "** " << setw(20) << "应还日期";
			cout << "** " << setw(20) << "归还日期" << endl;
			rm.ShowHistory(historyRecord);
			cout << "\t\t\t** 0.  退 出  **" << endl;
			cout << "\t\t\t 请选择：";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
				cin >> choice;
			}
			switch (choice)
			{
			case 0:
				int cc;
				do {
					cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						break;
					else if (cc == 2) {
						choice = -1; break;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
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
					cout << "\t\t* * * * 您 有 预 约 记 录 已 经 过 期 * * * *" << endl;
					pos.push_back(i + 1);
				}
			}
		}
#pragma endregion

		do
		{
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n";
			cout << "\n\t\t\t**** 当 前 用 户：" << cAccount << "  ****\n";
			cout << "\n\t\t\t**** 用 户 预 约 记 录****\n\n";
			cout.setf(ios::left);
			cout << "** " << setw(6) << "序号";
			cout << "** " << setw(8) << "图书ID";
			cout << "** " << setw(30) << "书名";
			cout << "** " << setw(20) << "预约日期";                     //使用borrowTime
			cout << "** " << setw(20) << "失效日期" << endl;             //使用SReturnTime

			rm.Show(reservationRecord);                                  //                          
			
			if (user.getreservationNum() == 3)
			{
				cout << "\n\t\t\t**** 无 预 约 记 录****\n\n" << endl;
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
						
						cout << "\t\t* * * * 序 号 为 " << pos[i] << " 的 预 约 已 经 过 期  * * * *" << endl;
					}
					pos.clear();
					cout << "\t\t\t****  已 经 清 除 无 效 的 预 约 记 录  **" << endl;
					rm.Show(reservationRecord);
				}

				cout << "\t\t\t** 1.  借 书  **" << endl;
				cout << "\t\t\t** 0.  退 出  **" << endl;
				cout << "\t\t\t 请选择：";
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
					cin >> choice;
				}
				switch (choice)
				{
				case 1:
					if (user.getreservationNum() == 3)
					{
						cout << "\n\t\t\t**** 无 预 约 记 录****\n\n" << endl;
					}
					else
					{
						if (user.getBookNum() > 0)
						{
							int c2;
							do
							{
								cout << "\n\t\t\t****  请 输 入 序 号 借 阅 相 应 图 书  **" << endl;
								cout << "\n\t\t\t****  或 输 入 0 返 回  **" << endl;
								cin.clear();
								cin.ignore(100, '\n');
								cin >> c2;          //相应的序号
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> c2;
								}
								if (c2 < 1 || c2 > reservationRecord.size())
								{
									cout << "\t\t****** 请 正 确 输 入 序 号******" << endl;
								}
								else if (!reservationRecord[c2 - 1].enabled)
								{
									int cc;
									//
									cout << "\t\t\t** 确 认 借 阅 此 本 书 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									cin >> cc;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> cc;
									}
									if (cc == 1)
									{
										//借选定的预约的书
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
										cout << " 请正确输入1或2选择" << endl;
									}
								}
								else {
									cout << " 没 有 预 约 记 录" << endl;
								}

							} while (c2 != 0);
						}
						else
						{
							cout << " 借 书 达 到 最 大 数 量" << endl;
						}
					}	
					break;
				case 0:
					int cc;
					do {
						cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)		//退出并刷新文件
						{
							break;
						}
						else if (cc == 2) {
							choice = -1; break;
						}
						else {
							cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
						}
					} while (cc != 1 || cc != 2);
					break;
				default:
					cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
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
		int choice;   //界面选择
		char input[17];
		int c1;
		do {
			if (users.empty())
				TotalUser = um.LoadFromFile(&users, 1, 100);
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
			
			cout << "\n\t\t\t**** 管 理 用 户 界 面 ****\n";
			
			cout << "\n\t\t\t**** 1. 按 用 户 名 检 索  **" << endl;
			cout << "\n\t\t\t**** 5. 查 看 全 部  **" << endl;
			cout << "\n\t\t\t**** 0.   返  回  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
				cin >> c1;
			}
			switch (c1)
			{
			case 1:
			{
				int c2;
				int page = 1;
				cout << "\n\t\t\t**** 1. 请 输 入 用 户 名**" << endl;
				cout << "例：" << endl << "00000001" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> input;
				um.Search(users, userSearchResult, input);
				if (TotalUser > users.size())//需要遍历整个文件
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
					cout << "没 有 此 用 户，请 检 查 用 户 名" << endl;
					break;
				}

				do
				{
					um.Show(userSearchResult[0]);
					cout << "\n\t**** 1. 重 置 密 码   **";
					cout << "\n\t**** 2. 解 冻 账 号   **";
					cout << "\n\t**** 3. 解 除 逾 期 惩 罚   **";
					cout << "\n\t**** 4. 冻 结 账 号   **";
					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> c1;
					}

					if (c2 == 1)
					{
						int cc;
							cout << "\t\t\t** 确 认 重 置 此 用 户 密 码 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								userSearchResult[0].setUserPassword(dPassword);
								cout << "\n\t****  重 置 密 码 成 功  **" << endl;
								um.RefreshUser(userSearchResult[0]);
							}
							else if (cc == 2);
							else
							{
								cout << " 请正确输入1或2选择" << endl;
							}
					
					}
					if (c2 == 2)
					{
						int cc;
						cout << "\t\t\t** 确 认 解 冻 此 用 户 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setStatus(1);
							cout << "\n\t****  解 冻 账 号 成 功  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " 请正确输入1或2选择" << endl;
						}
					
					}
					if (c2 == 3)
					{
						int cc;
						cout << "\t\t\t** 确 认 解 除 此 用 户 逾 期 惩 罚 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setBookNum(5);
							cout << "\n\t****  解 除 逾 期 惩 罚 成 功  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " 请正确输入1或2选择" << endl;
						}
					
					}
					if (c2 == 4)
					{
						int cc;
						cout << "\t\t\t** 确 认 解 冻 此 用 户 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							userSearchResult[0].setStatus(0);
							cout << "\n\t****  冻 结 账 号 成 功  **" << endl;
							um.RefreshUser(userSearchResult[0]);
						}
						else if (cc == 2);
						else
						{
							cout << " 请正确输入1或2选择" << endl;
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
				int page = 1;		//当前页码
				do
				{
					cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << TotalUser / 20 + 1 << "页 " << "  一共 " << TotalUser << "个" << endl;
					um.Show(users, page);
					cout << "\n\t**** 2. 下 一 页   **";
					cout << "\t**** 3. 上 一 页   **";
					cout << "\t**** 0. 返 回   **" << endl;

					cout << "\n\t**** 4. 重 置 密 码   **";
					cout << "\n\t**** 5. 解 冻 账 号   **";
					cout << "\t**** 6. 解 除 逾 期 惩 罚   **";
					cout << "\n\t**** 7. 冻 结 账 号   **";


					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
							cout << "已 经 是 最 后 一 页 了" << endl;
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
						else cout << "\n\t****  已经是第一页了    **" << endl;
					}
					if (c2 == 4)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 操 作 序 号  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "输入序号不正确，请重新输入" << endl;
							cin >> c3;
						}
						int cc;
						cout << "\t\t\t** 确 认 重 置 此 用 户 密 码 吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							users[c3 - 1].setUserPassword(dPassword);
							cout << "\n\t****  重 置 密 码 成 功  **" << endl;
							changedUsers.push_back(users[c3 - 1]);
						}
						else if (cc == 2);
						else
						{
							cout << " 请正确输入1或2选择" << endl;
						}			
					}
					if (c2 == 5)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 操 作 序 号  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "输入序号不正确，请重新输入" << endl;
							cin >> c3;
						}
						if (users[c3 - 1].getStatus() == 0)
						{
							int cc;
							cout << "\t\t\t** 确 认 解 冻 此 用 户 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								users[c3 - 1].setStatus(1);
								cout << "\n\t****  解 冻 成 功  **" << endl;
								changedUsers.push_back(users[c3 - 1]);
							}
							else if (cc == 2);
							else
							{
								cout << " 请正确输入1或2选择" << endl;
							}
						}
						else cout << "\n\t****  该 用 户 未 冻 结  **" << endl;
					}
					if (c2 == 6)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 操 作 序 号  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "输入序号不正确，请重新输入" << endl;
							cin >> c3;
						}
						int cc;
						cout << "\t\t\t** 确 认 解 除 此 用 户 的 逾 期 惩 罚  吗 ？  **" << endl;
						cout << "\t\t\t** 1.确认  **" << endl;
						cout << "\t\t\t** 2.取消  **" << endl;
						cin >> cc;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> cc;
						}
						if (cc == 1)
						{
							users[c3 - 1].setBookNum(5);
							cout << "\n\t****  解 除 逾 期 惩 罚 成 功 **" << endl;
							changedUsers.push_back(users[c3 - 1]);
						}
						else if (cc == 2);
						else
						{
							cout << " 请正确输入1或2选择" << endl;
						}
					}
					if (c2 == 7)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 操 作 序 号  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>users.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "输入序号不正确，请重新输入" << endl;
							cin >> c3;
						}
						if (users[c3 - 1].getStatus() == 1)
						{
							int cc;
							cout << "\t\t\t** 确 认 冻 结 此 用 户 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> cc;
							}
							if (cc == 1)
							{
								users[c3 - 1].setStatus(0);
								cout << "\n\t****  冻 结 成 功  **" << endl;
								changedUsers.push_back(users[c3 - 1]);
							}
							else if (cc == 2);
							else
							{
								cout << " 请正确输入1或2选择" << endl;
							}
						}
						else cout << "\n\t****  该 用 户 已 冻 结  **" << endl;
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
					cout << "\t\t\t** 确 认 返 回 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
						cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
					}
				} while (cc != 1 || cc != 2);
				break;
			default:
				cout << "\t\t****** 请正确输入1-6或0选择******" << endl;
			}
		} while (c1 != 0);
	}

void Library::EnterManagerBook()
	{
		int choice;
		do
		{
			cout << "\n\t\t\t**** 图 书 管 理 系 统****\n\n";
			cout << "\t\t\t** 1.增 加 图 书 **\n" << endl;
			cout << "\t\t\t** 2.删 除 图 书 **\n" << endl;
			cout << "\t\t\t** 3.修 改 图 书 **\n" << endl;
			cout << "\t\t\t** 4.查 看 所 有 图 书 **\n" << endl;
			cout << "\t\t\t** 0.  返回  **" << endl;
			cout << "\t\t\t 请选择：";
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
				int page = 1;		//当前页码
				if (bookVector.empty())
					TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
				do
				{
					cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << TotalBook / 20 + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 2. 下 一 页   **";
					cout << "\t**** 3. 上 一 页   **";
					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
							cout << "已 经 是 最 后 一 页 了" << endl;
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
						else cout << "\n\t****  已经是第一页了    **" << endl;
					}
					if (c2 == 0)
					{
						int cc;
						do {
							cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> cc;
							}
							if (cc == 1)
								break;
							else if (cc == 2) {
								c2 = -1; break;
							}
							else {
								cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
							}
						} while (cc != 1 || cc != 2);
					}
				} while (c2 != 0);
			}
				break;
			case 0:
				cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
				cout << "\t\t\t** 1.确认  **" << endl;
				cout << "\t\t\t** 2.取消  **" << endl;
				int i;
				cin >> i;
				if (i == 1)
				{
					return;
				}
				else if (i == 2) choice = ' ';
				else cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
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
			cout << "请输入需要添加的书的信息 或 0 返 回" << endl;
			cout << "请输入ISBN：" << " 注 意 ：请 确 保 I S B N 的 正 确 " << endl;
			cin >> ISBN;
			if (strcmp(ISBN, "0") == 0)
				return;
			string s1(ISBN);
			while (s1.find('#') != string::npos)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout <<  "ISBN 中 不 能 存 在‘#’" << "请 重 新 输 入 :" << endl;
				cin >> ISBN;
				s1 = ISBN;
			}			
			bm.Search(bookVector, &searchResult, ISBN);
			if (TotalBook > bookVector.size())//需要遍历整个文件
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
				cout << "添 加 新 书 的 信 息 " << endl;
				do {
					cout << "请 输 入 书 名：" << endl;
					cin >> name;
				} while (!isLegal(name, sizeof(name)));
				do {
					cout << "请 输 入 作 者：" << endl;
					cin >> author;
				} while (!isLegal(author, sizeof(author)));

				cout << "请 选 择 图 书 类 型" << endl;
				for (int i = 0; i < 22; i++)
				{
					if (i % 6 == 0)cout << endl;
					cout.setf(ios::left);
					cout << "** " << setw(4) << i + 1 << " **";
					cout << setw(20) << bookKind[i];
				}
				cout << "\n请 输 入 序 号：" << endl;
				cin >> type;	
				while (type < -2 || type>22|| cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					 cout << " 警 告 ：只 能 输 入 数 字 且  只 能 为 1 -- 2 2 " << endl;
					cin >> type;
				}
				type--;
				do {
					cout << "请 输 入 出 版 社：" << endl;
					cin >> publishing;
				} while (!isLegal(publishing, sizeof(publishing)));
				
				cout << "请 输 入 价 格：" << endl;
				cin >> price;
				while (price<=0 || cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 正 数   " << "请 重 新 输 入:" << endl;
					cin >> price;
				}
				cout << "请 输 入 数 量：" << endl;
				cin >> count;
				while (count <1|| cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "只 能 输 入 正 数   " << "请 重 新 输 入:" << endl;
					cin >> count;		
				}

				//确认增加图书
				do {
					cout << "\t\t\t** 确 认 添 加 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						char tID[9];
						sprintf(tID, "%08d", TotalBook + 1);
						Book temp(tID, ISBN, name, author, type, publishing, price, count);
						bm.Add(temp);
						cout << "\t\t\t**  添 加 成 功 **" << endl;
					}
					return;
					case 2:
						break;
					default:
						cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
					}
				} while (choice != 2);
			}
			else
			{
				if (searchResult[0].getStatus())
				{
					int inputNum = 0;
					cout << "\t\t\t** 该 书 已 存 在  **" << endl;
					cout << "\t\t\t** 请 输 入 要 添 加 的 数 量  **" << endl;
					cin >> inputNum;
					while (inputNum < 1||cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 正 数   " << "请 重 新 输 入:" << endl;
						cin >> inputNum;
					}

					searchResult[0].setoCount(searchResult[0].getOCount() + inputNum);
					//change中只修改了当前数量，未修改馆藏数量
					bm.Change(searchResult, 1, inputNum, changedBooks);
					//确认增加图书
					cout << "\t\t\t** 确 认 添 加 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> choice;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
						bm.Refresh(changedBooks);
						cout << "\t\t\t** 添 加 成 功   **" << endl;
						return;
					case 2:
						break;
					default:
						cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
						break;
					}
				}
				else
				{
					cout << "\t\t\t** 该 书 信 息 存 在，但 已 被 删 除  **" << endl;
					cout << "\t\t\t** 是 否 要 重 新 添 加 （添 加 数 量） **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> choice;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
					{int inputNum = 0;
					cout << "\t\t\t** 请 输 入 图 书 的 数 量  **" << endl;
					cin >> inputNum;
					while (cin.fail() || inputNum < 1)
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << " 警 告 ：只 能 输 入 数 字 且 数 量 只 能 大 于  等 于 1" << endl;
						cout << "请 重 新 输 入 数 字:" << endl;
						cin >> inputNum;
					}
					searchResult[0].setStatus(true);
					searchResult[0].setoCount(inputNum);
					searchResult[0].setCurrentCount(inputNum);
					bm.Refresh(changedBooks);
					cout <<"\t\t\t**  重 新 添 加 成 功 **" << endl;
					}
					return;
					case 2:
						break;
					default:
						cout << "\t\t\t** 请正确输入1或2选择  **" << endl;
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
		//此处添加删除图书的代码
		do {
		page4:
			bookVector.clear();
			searchResult.clear();
			TotalBook = bm.LoadFromFile(&bookVector, 1, 100);
			cout << "\n\t\t\t**** 1. 检 索  **" << endl;
			cout << "\n\t\t\t**** 2. 查 看 全 部  **" << endl;
			cout << "\n\t\t\t**** 0.   返  回  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
				cout << "\n\t\t\t**** 请 输 入 相 关 信 息（ 不 填 的 使 用 ‘ # ’ ） **" << endl;
#pragma region input
				cout << "\n\t\t\t**** 1. 书 名 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sname;
				cout << "\n\t\t\t**** 2. ISBN ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sISBN;
				cout << "\n\t\t\t**** 3. 作 者 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sauthor;
				cout << "\n\t\t\t**** 4. 出 版 社 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> spublishing;
#pragma endregion
				if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
				{
					do
					{
						int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
						cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 "<<"  一共 " << TotalBook << "本" << endl;
						bm.ManagerShow(bookVector, page);
						cout << "\n\t**** 1. 删 除 书      **" << endl;
						cout << "\n\t**** 2. 下 一 页   **";
						cout << "\t**** 3. 上 一 页   **";
						cout << "\t**** 0. 返 回   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c2;
						}
						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** 请 输 入 想 删 除 书 的 序 号  **" << endl;
							cin >> c3;					
							
							while (c3<1 || c3>bookVector.size()|| cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << " 请 输 入 正 确 的 序 号" << endl;
								cin >> c3;
							}
							if (bookVector[c3 - 1].getStatus())
							{
								if (bookVector[c3 - 1].getCurrentCount() == bookVector[c3 - 1].getOCount())
								{
									bm.Delete(bookVector, c3, changedBooks);
									bm.Refresh(changedBooks);
									cout << "\n\t**** * * 成 功 删 除  * * ****" << endl;
									changedBooks.clear();
								}
								else
								{
									cout << "\n\t**** * *  该 书 目 前 被 借 出，无 法 删 除  * * ****" << endl;
								}

							}
							else
							{
								cout << "\n\t**** * *  该 书 已 经 不 存 在，不 可 删 除  * * ****" << endl;
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
								cout << "已 经 是 最 后 一 页 了" << endl;
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
							else cout << "\n\t****  已经是第一页了    **" << endl;
						}
						if (c2 == 0)
						{
							int cc;
							do
							{
								cout << "\t\t\t** 确 认 返 回 吗 ？  **" << endl;
								cout << "\t\t\t** 1.确认  **" << endl;
								cout << "\t\t\t** 2.取消  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
									cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
								}
							} while (cc != 1 || cc != 2);
						}
					} while (c2 != 0);
				}
				bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
				if (TotalBook > bookVector.size())//需要遍历整个文件
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
					
					cout << "\n\t**** 当 前：第" << page << "页" << "  一共 " << searchResult.size() << "本" << endl;
					bm.ManagerShow(searchResult, page);
					cout << "\n\t**** 1. 删 除 书      **" << endl;
					cout << "\n\t**** 2. 下 一 页   **";
					cout << "\t**** 3. 上 一 页   **";
					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> c2;
					}
					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 删 除 书 的 序 号  **" << endl;
						cin >> c3;
						while (c3<1 || c3>searchResult.size()|| cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << " 请 输 入 正 确 的 序 号" << endl;
							cin >> c3;
						}
						if (searchResult[c3 - 1].getStatus())
						{
							if (searchResult[c3 - 1].getCurrentCount() == searchResult[c3 - 1].getOCount())
							{
								bm.Delete(searchResult, c3, changedBooks);
								bm.Refresh(changedBooks);
								cout << "\n\t**** * * 成 功 删 除  * * ****" << endl;
								changedBooks.clear();
							}
							else
							{
								cout << "\n\t**** * *  该 书 目 前 被 借 出，无 法 删 除  * * ****" << endl;
							}

						}
						else
						{
							cout << "\n\t**** * *  该 书 已 经 不 存 在，不 可 删 除  * * ****" << endl;
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
							cout << "已 经 是 最 后 一 页 了" << endl;
						}
					}
					if (c2 == 3)
					{
						if (page != 1)
						{
							page--;
						}
						else cout << "\n\t****  已 经 是 第 一 页 了    **" << endl;
					}
					if (c2 == 0)
					{
						int cc;
						do
						{
							cout << "\t\t\t** 确 认 返 回 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
								cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
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
				int page = 1;		//当前页码
				do
				{
				page5:
					int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
					cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 1. 删 除    **" << " * * 注 意：若 图 书 当 前 被 借 出，则 不 能 删 除  * * " << endl;
					cout << "\n\t**** 2. 下 一 页   **";
					cout << "\t**** 3. 上 一 页   **";
					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> c2;
					}

					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 删 除 书 的 序 号  **" << endl;
						cin >> c3;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						while (c3<1 || c3>bookVector.size()||cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << " 请 输 入 正 确 的 序 号 " << endl;
							cin >> c3;
						}
						if (bookVector[c3 - 1].getStatus())
						{
							if (bookVector[c3 - 1].getCurrentCount() == bookVector[c3 - 1].getOCount())
							{
								bm.Delete(bookVector, c3, changedBooks);
								bm.Refresh(changedBooks);
								cout << "\n\t**** * * 成 功 删 除  * * ****" << endl;
								changedBooks.clear();
							}
							else
							{
								cout << "\n\t**** * *  该 书 目 前 被 借 出，无 法 删 除  * * ****" << endl;
							}

						}
						else
						{
							cout << "\n\t**** * *  该 书 已 经 不 存 在，不 可 删 除  * * ****" << endl;
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
							cout << "已 经 是 最 后 一 页 了" << endl;
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
						else cout << "\n\t****  已经是第一页了    **" << endl;
					}
					if (c2 == 0) {
						int cc;
						do
						{
							cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
								cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
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
					cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						return;
					else if (cc == 2) {
						c1 = -1;
						goto page4;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
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
			cout << "\n\t\t\t**** 1. 检 索  **" << endl;
			cout << "\n\t\t\t**** 2. 查 看 全 部  **" << endl;
			cout << "\n\t\t\t**** 0.   返  回  **" << endl;
			cin >> c1;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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

				cout << "\n\t\t\t**** 请 输 入 相 关 信 息（ 不 填 的 使 用 ‘#’ ） **" << endl;
#pragma region input
				cout << "\n\t\t\t**** 1. 书 名 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sname;
				cout << "\n\t\t\t**** 2. ISBN ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sISBN;
				cout << "\n\t\t\t**** 3. 作 者 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> sauthor;
				cout << "\n\t\t\t**** 4. 出 版 社 ：**" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> spublishing;
#pragma endregion
				if (strcmp(sISBN, "#") == 0 && strcmp(sname, "#") == 0 && strcmp(sauthor, "#") == 0 && strcmp(spublishing, "#") == 0)
				{
					int c2;
					int page = 1;		//当前页码
					do
					{
					page2:
						int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
						cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
						bm.ManagerShow(bookVector, page);
						cout << "\n\t**** 1. 修 改 书 籍 信 息      **" << endl;
						cout << "\n\t**** 2. 下 一 页   **";
						cout << "\t**** 3. 上 一 页   **";
						cout << "\t**** 0. 返 回   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c2;
						}

						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** 请 输 入 想 修 改 书 的 序 号  或 0 返 回**" << endl;
							cin >> c3;
							while (cin.fail() || c3<0 || c3>bookVector.size())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 合 适 范 围 的 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> c3;
							}
							if (c3 == 0)goto page2;
							if (bookVector[c3 - 1].getStatus())
							{
#pragma region input
								static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
								int ctype, cprice, cocount;
								do {
									cout << "\n\t**** 请 输 入 新 的 ISBN  或 0 返 回，-1 为 不 修 改 **" << endl;
									cin >> cisbn;
								} while (!isLegal(cisbn, sizeof(cisbn)));
								if (strcmp(cisbn, "0") == 0)goto page2;
								else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn,bookVector[c3-1].getISBN());

								do {
									cout << "\n\t**** 请 输 入 新 的 书 名 或 0 返 回，-1 为 不 修 改 **" << endl;
									cin >> cname;
								} while (!isLegal(cname, sizeof(cname)));

								if (strcmp(cname, "0") == 0)goto page2;
								else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

								do {
									cout << "\n\t**** 请 输 入 新 的 作 者 或 0 返 回， -1 为 不 修 改  **" << endl;
									cin >> cauthor;
								} while (!isLegal(cauthor, sizeof(cauthor)));	
								if (strcmp(cauthor, "0") == 0)goto page2;
								else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
								cout << "\n\t**** 请 输 入 新 的 出 版 社 或 0 返 回，-1 为 不 修 改  **" << endl;
								
								cin >> cpublishing;
								if (strcmp(cpublishing, "0") == 0)goto page2;
								else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
								cout << "\n\t**** 请 选 择 新 的 种 类 或 0 返 回，-1 为 不 修 改  **" << endl;
								for (int i = 0; i < 22; i++)
								{
									if (i % 6 == 0)cout << endl;
									cout.setf(ios::left);
									cout << "** " << setw(4) << i + 1 << " **";
									cout << setw(20) << bookKind[i];
								}
								cout << "\n请 输 入 序 号：" << endl;
								cin >> ctype;
								while (ctype < -1 || ctype>22||cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << " 请 在 正 确 范 围 内 选 择 数 字 ，请 重 新 输 入" << endl;
									cin >> ctype;
								}
								if (ctype == 0)goto page2;
								else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
								else ctype--;

								cout << "\n\t**** 请 输 入 新 的 价 格 或 0 返 回，-1 为 不 修 改  **" << endl;
							
								cin >> cprice;
								while (cin.fail()||cprice<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 正 数   " << "请 重 新 输 入 :" << endl;
									cin >> cprice;
								}
								if (cprice == 0)goto page2;
								else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
								input2:
								cout << "\n\t**** 请 输 入 要 增 加 或 者 减 少 的 馆 藏 数 量 或 0 返 回， -1000 为 不 修 改  **" << endl;
								cout << "\n\t**** （增 加 输 入 正 数，减 少 输 入 负 数）  **" << endl;
								
								cin >> cocount;
								while (cin.fail()||cocount<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> cocount;
								}
								if (cocount == 0)goto page2;
								else if (cocount == -1000)cocount = 0;
#pragma endregion
								if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
								{
									cout << "\n\t**** 减 少 的 数 量 过 多 **" << endl;
									goto input2;
								}
								else
								{
								confirm2:
									cout << "\t\t\t** 确 认 修 改 吗 ？  **" << endl;
									cout << "\t\t\t** 1.确认  **" << endl;
									cout << "\t\t\t** 2.取消  **" << endl;
									int choice;
									cin >> choice;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> choice;
									}
									switch (choice)
									{
									case 1:
										bm.ChangeAll(bookVector, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
										cout << "\t\t\t** 修 改 成 功  **" << endl;
										cout << "\t\t\t** 修 改 的 图 书 信 息 如 下  **" << endl;
										bm.Show(changedBooks);
										bm.Refresh(changedBooks);
										int c4;
										cout << "\t\t\t** 输 入 1 继 续 **" << endl;
										cin >> c4;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
											cin >> c4;
										}
										while (c4 != 1)
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "只 能 输 入 1   " << "请 重 新 输 入 :" << endl;
											cin >> c4;
										}
										changedBooks.clear();
										goto page2;
									case 2:
										goto page2;
									default:
										cout << "\t\t\t** 请 正 确 输 入 1 或 2  **" << endl;
										goto confirm2;
									}
								}
							}
							else
							{
								cout << "\n\t**** 该 书 已 经 被 删 除 ，不 能 修 改  **" << endl;
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
								cout << "已 经 是 最 后 一 页 了" << endl;
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
							else cout << "\n\t****  已经是第一页了    **" << endl;
						}

						if (c2 == 0)
						{
							int cc;
							do {
								cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
								cout << "\t\t\t** 1.确认  **" << endl;
								cout << "\t\t\t** 2.取消  **" << endl;
								cin >> cc;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> cc;
								}
								if (cc == 1)
									break;
								else if (cc == 2) {
									c2 = -1; break;
								}
								else {
									cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
								}
							} while (cc != 1 || cc != 2);
						}
					} while (c2 != 0);
					break;
				}
				
				bm.Search(bookVector, &searchResult, sname, sISBN, sauthor, spublishing);
				if (TotalBook > bookVector.size())//需要遍历整个文件
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
					cout << "\n\t**** 没 有 找 到 相 关 图 书   **" << endl;
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
						cout << "\n\t**** 当 前：第" << page << "页" << "  一 共  " << searchResult.size() << " 本 " << endl;
						bm.ManagerShow(searchResult, page);
						cout << "\n\t**** 1. 修 改     **" << endl;
						cout << "\n\t**** 2. 下 一 页   **";
						cout << "\t**** 3. 上 一 页   **";
						cout << "\t**** 0. 返 回   **" << endl;
						cin >> c2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c1;
						}
						//此处应判断读者是否还有权限借书

						if (c2 == 1)
						{
							int c3;
							cout << "\n\t**** 请 输 入 想 修 改 的 书 的 序 号 或 0 返 回  **" << endl;
							cin >> c3;
							while (cin.fail()|| c3<0 || c3>searchResult.size())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 合 适 范 围 的 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> c3;
							}
							if (c3 == 0)goto page1;
							if (searchResult[c3 - 1].getStatus())
							{
#pragma region input
								static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
								int ctype, cprice, cocount;
								do {
									cout << "\n\t**** 请 输 入 新 的 ISBN  或 0 返 回，-1 为 不 修 改 **" << endl;
									cin >> cisbn;
								} while (!isLegal(cisbn, sizeof(cisbn)));
								if (strcmp(cisbn, "0") == 0)goto page1;
								else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn, bookVector[c3 - 1].getISBN());

								do {
									cout << "\n\t**** 请 输 入 新 的 书 名 或 0 返 回，-1 为 不 修 改 **" << endl;
									cin >> cname;
								} while (!isLegal(cname, sizeof(cname)));

								if (strcmp(cname, "0") == 0)goto page1;
								else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

								do {
									cout << "\n\t**** 请 输 入 新 的 作 者 或 0 返 回， -1 为 不 修 改  **" << endl;
									cin >> cauthor;
								} while (!isLegal(cauthor, sizeof(cauthor)));
								if (strcmp(cauthor, "0") == 0)goto page1;
								else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
								cout << "\n\t**** 请 输 入 新 的 出 版 社 或 0 返 回，-1 为 不 修 改  **" << endl;

								cin >> cpublishing;
								if (strcmp(cpublishing, "0") == 0)goto page1;
								else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
								cout << "\n\t**** 请 选 择 新 的 种 类 或 0 返 回，-1 为 不 修 改  **" << endl;
								for (int i = 0; i < 22; i++)
								{
									if (i % 6 == 0)cout << endl;
									cout.setf(ios::left);
									cout << "** " << setw(4) << i + 1 << " **";
									cout << setw(20) << bookKind[i];
								}
								cout << "\n请 输 入 序 号：" << endl;
								cin >> ctype;
								while (ctype < -1 || ctype>22 || cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << " 请 在 正 确 范 围 内 选 择 数 字 ，请 重 新 输 入" << endl;
									cin >> ctype;
								}
								if (ctype == 0)goto page1;
								else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
								else ctype--;

								cout << "\n\t**** 请 输 入 新 的 价 格 或 0 返 回，-1 为 不 修 改  **" << endl;

								cin >> cprice;
								while (cin.fail() || cprice<-1)
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 正 数   " << "请 重 新 输 入 :" << endl;
									cin >> cprice;
								}
								if (cprice == 0)goto page1;
								else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
							input1:
								cout << "\n\t**** 请 输 入 要 增 加 或 者 减 少 的 馆 藏 数 量 或 0 返 回， -1000 为 不 修 改  **" << endl;
								cout << "\n\t**** （增 加 输 入 正 数，减 少 输 入 负 数）  **" << endl;

								cin >> cocount;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> cocount;
								}
								if (cocount == 0)goto page1;
								else if (cocount == -1000)cocount = 0;
								if (searchResult[c3 - 1].getCurrentCount() + cocount < 0)
								{
									cout << "\n\t**** 减 少 的 数 量 过 多 **" << endl;
									goto input1;
								}
#pragma endregion
								confirm1:
										cout << "\t\t\t** 确 认 修 改 吗 ？  **" << endl;
										cout << "\t\t\t** 1.确认  **" << endl;
										cout << "\t\t\t** 2.取消  **" << endl;
										int choice;
										cin >> choice;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(100, '\n');
											cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
											cin >> choice;
										}
										switch (choice)
										{
										case 1:
											bm.ChangeAll(searchResult, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
											cout << "\t\t\t** 修 改 成 功  **" << endl;
											cout << "\t\t\t** 修 改 的 图 书 信 息 如 下  **" << endl;
											bm.Show(changedBooks);
											bm.Refresh(changedBooks);
											int c4;
											cout << "\t\t\t** 输 入 1 继 续 **" << endl;
											cin >> c4;
											while (cin.fail())
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
												cin >> c4;
											}
											while (c4 != 1)
											{
												cin.clear();
												cin.ignore(100, '\n');
												cout << "只 能 输 入 1   " << "请 重 新 输 入 :" << endl;
												cin >> c4;
											}
											changedBooks.clear();
											goto page1;
										case 2:
											goto page1;
										default:
											cout << "\t\t\t** 请 正 确 输 入 1 或 2  **" << endl;
											goto confirm1;
										}

							}
							else {
								cout << "\n\t**** 该 书 已 经 被 删 除 ，不 能 修 改  **" << endl;
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
								cout << "已 经 是 最 后 一 页 了" << endl;
							}
						}
						if (c2 == 3)
						{
							if (page != 1)
							{
								page--;
							}
							else cout << "\n\t****  已 经 是 第 一 页 了    **" << endl;
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
				int page = 1;		//当前页码
				do
				{
				page3:
					int limit = (TotalBook % 20 == 0) ? ((TotalBook / 20) - 1) : (TotalBook / 20);
					cout << "\n\t**** 当 前：第" << page << "页" << " 一共 " << limit + 1 << "页 " << "  一共 " << TotalBook << "本" << endl;
					bm.ManagerShow(bookVector, page);
					cout << "\n\t**** 1. 修 改 书      **" << endl;
					cout << "\n\t**** 2. 下 一 页   **";
					cout << "\t**** 3. 上 一 页   **";
					cout << "\t**** 0. 返 回   **" << endl;
					cin >> c2;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> c2;
					}

					if (c2 == 1)
					{
						int c3;
						cout << "\n\t**** 请 输 入 想 修 改 书 的 序 号  或 0 返 回**" << endl;
						cin >> c3;
						while (cin.fail()|| c3<0 || c3>bookVector.size())
						{
							cin.clear();
							cin.ignore(100, '\n');
							cout << "只 能 输 入 合 适 范 围 的 数 字   " << "请 重 新 输 入 数 字:" << endl;
							cin >> c3;
						}
						if (c3 == 0)goto page3;
						if (bookVector[c3 - 1].getStatus())
						{
#pragma region input
							static char cisbn[14], cname[17], cauthor[17], cpublishing[21];
							int ctype, cprice, cocount;
							do {
								cout << "\n\t**** 请 输 入 新 的 ISBN  或 0 返 回，-1 为 不 修 改 **" << endl;
								cin >> cisbn;
							} while (!isLegal(cisbn, sizeof(cisbn)));
							if (strcmp(cisbn, "0") == 0)goto page3;
							else if (strcmp(cisbn, "-1") == 0)strcpy(cisbn, bookVector[c3 - 1].getISBN());

							do {
								cout << "\n\t**** 请 输 入 新 的 书 名 或 0 返 回，-1 为 不 修 改 **" << endl;
								cin >> cname;
							} while (!isLegal(cname, sizeof(cname)));

							if (strcmp(cname, "0") == 0)goto page3;
							else if (strcmp(cname, "-1") == 0)strcpy(cname, bookVector[c3 - 1].getName());

							do {
								cout << "\n\t**** 请 输 入 新 的 作 者 或 0 返 回， -1 为 不 修 改  **" << endl;
								cin >> cauthor;
							} while (!isLegal(cauthor, sizeof(cauthor)));
							if (strcmp(cauthor, "0") == 0)goto page3;
							else if (strcmp(cauthor, "-1") == 0)strcpy(cauthor, bookVector[c3 - 1].getAuthor());
							cout << "\n\t**** 请 输 入 新 的 出 版 社 或 0 返 回，-1 为 不 修 改  **" << endl;

							cin >> cpublishing;
							if (strcmp(cpublishing, "0") == 0)goto page3;
							else if (strcmp(cpublishing, "-1") == 0)strcpy(cpublishing, bookVector[c3 - 1].getPublishing());
							cout << "\n\t**** 请 选 择 新 的 种 类 或 0 返 回，-1 为 不 修 改  **" << endl;
							for (int i = 0; i < 22; i++)
							{
								if (i % 6 == 0)cout << endl;
								cout.setf(ios::left);
								cout << "** " << setw(4) << i + 1 << " **";
								cout << setw(20) << bookKind[i];
							}
							cout << "\n请 输 入 序 号：" << endl;
							cin >> ctype;
							while (ctype < -1 || ctype>22 || cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << " 请 在 正 确 范 围 内 选 择 数 字 ，请 重 新 输 入" << endl;
								cin >> ctype;
							}
							if (ctype == 0)goto page3;
							else if (ctype == -1)ctype = bookVector[c3 - 1].getType();
							else ctype--;

							cout << "\n\t**** 请 输 入 新 的 价 格 或 0 返 回，-1 为 不 修 改  **" << endl;

							cin >> cprice;
							while (cin.fail() || cprice<-1)
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 正 数   " << "请 重 新 输 入 :" << endl;
								cin >> cprice;
							}
							if (cprice == 0)goto page3;
							else if (cprice == -1)cprice = bookVector[c3 - 1].getPrice();
						input3:
							cout << "\n\t**** 请 输 入 要 增 加 或 者 减 少 的 馆 藏 数 量 或 0 返 回， -1000 为 不 修 改  **" << endl;
							cout << "\n\t**** （增 加 输 入 正 数，减 少 输 入 负 数）  **" << endl;

							cin >> cocount;
							while (cin.fail() )
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
								cin >> cocount;
							}
							if (cocount == 0)goto page3;
							else if (cocount == -1000)cocount = 0;
							if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
							{
								cout << "\n\t**** 减 少 的 数 量 过 多 **" << endl;
								goto input3;
							}
#pragma endregion
							if (bookVector[c3 - 1].getCurrentCount() + cocount < 0)
							{
								cout << "\n\t**** 减 少 的 数 量 过 多 **" << endl;
								goto page3;
							}
							else
							{
							confirm3:
								cout << "\t\t\t** 确 认 修 改 吗 ？  **" << endl;
								cout << "\t\t\t** 1.确认  **" << endl;
								cout << "\t\t\t** 2.取消  **" << endl;
								int choice;
								cin >> choice;
								while (cin.fail())
								{
									cin.clear();
									cin.ignore(100, '\n');
									cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
									cin >> choice;
								}
								switch (choice)
								{
								case 1:
									bm.ChangeAll(bookVector, changedBooks, c3, cisbn, cname, cauthor, cpublishing, ctype, cprice, cocount);
									cout << "\t\t\t** 修 改 成 功  **" << endl;
									cout << "\t\t\t** 修 改 的 图 书 信 息 如 下  **" << endl;
									bm.Show(changedBooks);
									bm.Refresh(changedBooks);
									int c4;
									cout << "\t\t\t** 输 入 1 继 续 **" << endl;
									cin >> c4;
									while (cin.fail())
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
										cin >> c4;
									}
									while (c4 != 1)
									{
										cin.clear();
										cin.ignore(100, '\n');
										cout << "只 能 输 入 1   " << "请 重 新 输 入 :" << endl;
										cin >> c4;
									}
									changedBooks.clear();
									goto page3;
								case 2:
									goto page3;
								default:
									cout << "\t\t\t** 请 正 确 输 入 1 或 2  **" << endl;
									goto confirm3;
								}
							}
						}
						else
						{
							cout << "\n\t**** 该 书 已 经 被 删 除 ，不 能 修 改  **" << endl;
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
							cout << "已 经 是 最 后 一 页 了" << endl;
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
						else cout << "\n\t****  已经是第一页了    **" << endl;
					}
					if (c2 == 0) {
						int cc;
						do
						{
							cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
							cout << "\t\t\t** 1.确认  **" << endl;
							cout << "\t\t\t** 2.取消  **" << endl;
							cin >> cc;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(100, '\n');
								cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
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
								cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
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
					cout << "\t\t\t** 确 认 退 出 吗 ？  **" << endl;
					cout << "\t\t\t** 1.确认  **" << endl;
					cout << "\t\t\t** 2.取消  **" << endl;
					cin >> cc;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(100, '\n');
						cout << "只 能 输 入 数 字   " << "请 重 新 输 入 数 字:" << endl;
						cin >> cc;
					}
					if (cc == 1)
						return;
					else if (cc == 2) {
						c1 = -1;
						goto page6;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t** 请正确输入1或2选择  **" << endl;
					}
				} while (cc != 1 || cc != 2);
			}
			break;
			default:
				break;
			}
		} while (c1 != 0);

	}

