#pragma once
#include"Book.h"
#include"Record.h"
#include"User.h"


const static int bookVectorMax = 100;
const static int userVectorMax = 100;
const static int numOfOnePage = 20;


const static int userMaxBook = 5;
const static int userMaxReservation = 3;
const static int accountLength = 9;			//�û�������
const static int passwordLength = 17;		//���볤��
static char dPassword[passwordLength] = "123456";		//Ĭ������
const static char userInfoPath[] = "./users.txt";	//�û��˻���Ϣ·��
const static char bookInfoPath[] = "./Books.txt";		//ͼ����Ϣ·��

const static char recordPath[] = "./record.txt";			 //�û�δ����ļ�¼�ļ�·��
const static char historyRecordPath[] = "./historyRecord.txt";     //�û�(�ѻ���)����ʷ��¼���ļ�·��
const static char reservationRecordPath[] = "./reservationRecord.txt";


static string bookKind[22] =
{
	"����ë��","��ѧ���ڽ�","����ѧ����","���Ρ�����","����","����","�Ŀƽ���",
	"���ԡ�����","��ѧ","����","��ʷ������","��Ȼ��ѧ����","�����ѧ�ͻ�ѧ","����ѧ�������ѧ",
	"�����ѧ","ҽҩ������","ũҵ��ѧ","��ҵ����","��ͨ����","���ա�����","������ѧ����ȫ��ѧ",
	"�ۺ���ͼ��"
};
//static int reservationRecordCountOfPer = 0;

static int recordCountOfFile = 0;
//static int recordCountOfPer = 0;
//���浱ǰ userID ���ļ��е�λ��
static int userPosition = 0;
static int TotalBook = 0;			//book�ļ����鱾����
static int TotalUser = 0;
static char  cAccount[9] = "00000001";
static char admin[] = "admin";
static char adminpass[] = "666";


class BookManager 
{
public:

	 int LoadFromFile(vector<Book> *bookVector,int startID,int n);
	 void SaveToFile(vector<Book> bookVector);		//�������ļ�β����ļ�
	 void Add(Book book) ;		//���һ�����飨֮ǰû�У�����֮ǰҪ�ж�
	 void Delete(vector<Book > &bookVector,int n, vector<Book> &changedBooks);
	 void Search(vector<Book> bookVector, vector<Book> *searchResult,  char name[], char ISBN[], char author[], char publishing[]);
	 void Search(vector<Book> bookVector, vector<Book> *searchResult, char ISBN[]);
	 void Change(vector<Book > &bookVector, int n, int changeCCount,vector<Book> &changedBooks);//�˷���ֻ���ڸı�����
	 void Show(vector<Book> bookVector,int count);	//������ʾ�̶���С��book������
	 void Show(vector<Book> bookVector);
	 void ManagerShow(vector<Book> bookVector, int count);
	 void ChangeAll(vector<Book > &bookVector, vector<Book> &changedBooks, int n, char isbn[], char name[], char author[], char publishing[], int type, double price, int OCount);
	 void Refresh(vector<Book> changedBooks);			//���ڽ��޸Ĺ�����Ϣ�����ļ�
};
class ReaderManager
{
public:
	int LoadFromFile(vector<User> *users, int startID, int n);  //���ļ���vector��
	void SaveToFile(vector<User> &bookVector);        //���ļ�
	bool Add( int n, int *newID);
	void Delete();
	void Search(vector<User> bookVector, vector<User> &searchResult, char * uID);
	void userChangePassword(User &user, char * npassword);     //�޸�����
	void userChangeName(User &user);         //�޸�����
	void userChangeClass(User &user);        //�޸İ༶
	void userChangeEmail(User &user);        //�޸�����
	void Show(User user);                    //��ʾ������Ϣ
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
