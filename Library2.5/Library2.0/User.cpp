#include "stdafx.h" 
#include "User.h"
#include <string>

//ÎÞÐÎ²Î
User::User()
{
	strcpy(userAccount, "");
	strcpy(userPassword, "");
	strcpy(userName, "");
	strcpy(userClass, "");
	strcpy(userEmail, "");
	bookNum = 5;
	reservationNum = 3;
	Status = 1;
}


void User::Clear()
{
	strcpy(userAccount, "");
	strcpy(userPassword, "");
	strcpy(userName, "");
	strcpy(userClass, "");
	strcpy(userEmail, "");
	bookNum = 5;
	reservationNum = 3;
	Status = 1;
}