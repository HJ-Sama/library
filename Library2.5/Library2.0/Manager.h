#pragma once
#include"Book.h"
#include"Record.h"
#include"User.h"


const static int bookVectorMax = 100;
const static int userVectorMax = 100;
const static int numOfOnePage = 20;


const static int userMaxBook = 5;
const static int userMaxReservation = 3;
const static int accountLength = 9;			//用户名长度
const static int passwordLength = 17;		//密码长度
static char dPassword[passwordLength] = "123456";		//默认密码
const static char userInfoPath[] = "./users.txt";	//用户账户信息路径
const static char bookInfoPath[] = "./Books.txt";		//图书信息路径

const static char recordPath[] = "./record.txt";			 //用户未还书的记录文件路径
const static char historyRecordPath[] = "./historyRecord.txt";     //用户(已还书)的历史记录的文件路径
const static char reservationRecordPath[] = "./reservationRecord.txt";


static string bookKind[22] =
{
	"马列毛邓","哲学、宗教","社会科学总论","政治、法律","军事","经济","文科教体",
	"语言、文字","文学","艺术","历史、地理","自然科学总论","数理科学和化学","天文学、地球科学",
	"生物科学","医药、卫生","农业科学","工业技术","交通运输","航空、航天","环境科学、安全科学",
	"综合性图书"
};
//static int reservationRecordCountOfPer = 0;

static int recordCountOfFile = 0;
//static int recordCountOfPer = 0;
//保存当前 userID 在文件中的位置
static int userPosition = 0;
static int TotalBook = 0;			//book文件中书本总数
static int TotalUser = 0;
static char  cAccount[9] = "00000001";
static char admin[] = "admin";
static char adminpass[] = "666";


class BookManager 
{
public:

	 int LoadFromFile(vector<Book> *bookVector,int startID,int n);
	 void SaveToFile(vector<Book> bookVector);		//用于向文件尾添加文件
	 void Add(Book book) ;		//添加一本新书（之前没有），用之前要判断
	 void Delete(vector<Book > &bookVector,int n, vector<Book> &changedBooks);
	 void Search(vector<Book> bookVector, vector<Book> *searchResult,  char name[], char ISBN[], char author[], char publishing[]);
	 void Search(vector<Book> bookVector, vector<Book> *searchResult, char ISBN[]);
	 void Change(vector<Book > &bookVector, int n, int changeCCount,vector<Book> &changedBooks);//此方法只用于改变数量
	 void Show(vector<Book> bookVector,int count);	//用于显示固定大小的book容器，
	 void Show(vector<Book> bookVector);
	 void ManagerShow(vector<Book> bookVector, int count);
	 void ChangeAll(vector<Book > &bookVector, vector<Book> &changedBooks, int n, char isbn[], char name[], char author[], char publishing[], int type, double price, int OCount);
	 void Refresh(vector<Book> changedBooks);			//用于将修改过的信息存入文件
};
class ReaderManager
{
public:
	int LoadFromFile(vector<User> *users, int startID, int n);  //读文件到vector中
	void SaveToFile(vector<User> &bookVector);        //存文件
	bool Add( int n, int *newID);
	void Delete();
	void Search(vector<User> bookVector, vector<User> &searchResult, char * uID);
	void userChangePassword(User &user, char * npassword);     //修改密码
	void userChangeName(User &user);         //修改姓名
	void userChangeClass(User &user);        //修改班级
	void userChangeEmail(User &user);        //修改邮箱
	void Show(User user);                    //显示个人信息
	void Show(vector<User> userVector, int page);
	bool Change(User &user);
	void RefreshUser(vector<User> user1);
	void RefreshUser(User user1);
};

class RecordManager
{
public:
	void LoadFromFile(vector<Record> *record, const  char * path,int loadNum, int displacement, int initialPoint);
	void SaveToFile(vector<Record> record1, const char * path, int displacement, int initialPoint);
	void Add(vector<Record> &record,  char* cAccount,Book book, int n);
	void Delete(vector<Record> &record, vector<Record> &history,int n, char  *uID);
	void Delete(vector<Record> &record, int n);
	void ShowHistory(vector<Record> record);
	void Show(vector<Record> record);
	void UpdateRecord(vector<Record> &cr, int userpos, char * uID,const char * path, int limit);
	
};
