/*
	Title: Assignment 4
	Author: Matthew Donoghue
	Objective: To create a basic transaction system to store an array of users each having an array of transaction that can have 1 of three types: withdrawal, deposit, and transfer
	Description:
		Transaction						-parent class that gives basic structure to transaction types to be used in program (NOTE: "ruid" is a variable only for transfers to track the recipient)
		Withdrawal/Deposit/Transfer		-child classes of Transaction with specialized report functions to suit their unique purpose (i.e unique output text)
		User							-main class of function, each user is dynamically created and stored in an array within the main function. Each user also has a dynamic array of transaction pointers
											that will only be created when a new transaction is intialized. Each user has functions for intializing and storing the information for each new transaction and
											a report function to print all transactions performed by that user.
		NewUser()						-a fucntion called by the main function to intialize a new user. It receives the user inputed id and, after the check is preformed in the main function to verify if it exists or not,
											the constructor of the User class is called, sending the inputed id as a parameter
		Menu()							-prints the ui menu; makes main fucntion less cluttered
		Main()							1.initializes variables and array of users pointers
										2.enters main loop, resets all used variables
										3.enters loop to verify active user
											4.receives enetered user id
											5.if there are existing users, scan through all users to check for matching user id
												if match, set user with matching id as active user
												if no match, create new user with entered id
											6.if there are no existing users, create new user with entered id
										7.once user is verified, print menu, ask for user choice of function to perform
										8.based on user choice
											(1 || 2 || 3) call user class functions to create new withdrawal, deposit or transfer
											(4) call user class function to print a report of all transaction by that user
											(5) exit program
*/

#include "stdio.h"
#include "iostream"
using namespace std;

#define NUM_TRANSACTIONS 100
#define NUM_USERS 100

class Transaction
{
public:
	int uid;		//user id associated with transaction
	int ruid;		//variable for transfers to track the recipient user
	int value;		//numerical value of transaction

	Transaction()
	{
		uid = 0;
		ruid = 0;
		value = 0;
	}

	virtual void Report()	//prints the transaction and its associated information
	{
		printf("uid=%d amount=%d\n", uid, value);
	}

};

class Withdrawal : public Transaction
{
public:
	Withdrawal()
	{
		uid = 0;
		value = 0;
		cout << "<new withdrawal>\n";
	}

	void Report()
	{
		printf("Withdrawal: $%d\n", value);
	}
};

class Deposit : public Transaction
{
public:
	Deposit()
	{
		uid = 0;
		value = 0;
		cout << "<new deposit>\n";
	}

	void Report()
	{
		printf("Deposit: $%d\n", value);
	}
};

class Transfer : public Transaction //one user to another
{
public:
	Transfer()
	{
		uid = 0;
		value = 0;
		cout << "<new transfer>\n";
	}
	void Report()
	{
		printf("Transfer: $%d -> User: %d\n", value, ruid);		//this report also shows the recipient user's id
	}
};

class User
{
public:
	int id;
	int numTrans;
	int balance;
	Transaction* t[100];

	User(int s)
	{
		id = s;
		numTrans = 0;
		balance = 0;
		cout << "<new user: " << id << ">\n";
	}

	void NewWithdrawal(int x)
	{
		if (balance - x < 0)
			cout << "Error: Insufficient Funds\n";
		else
		{
			t[numTrans] = new Withdrawal();
			t[numTrans]->uid = id;
			t[numTrans]->value = x;
			balance -= x;
			numTrans++;
			cout << "<transaction complete>\n";
			cout << "<transactions: " << numTrans << ">\n";
		}
	}

	void NewDeposit(int x)
	{
		t[numTrans] = new Deposit();
		t[numTrans]->uid = id;
		t[numTrans]->value = x;
		balance += x;
		numTrans++;
		cout << "<transaction complete>\n";
		cout << "<transactions: " << numTrans << ">\n";
	}

	void NewTransfer(int x, int y)
	{
		if (balance - x < 0)
			cout << "Error: Insufficient Funds\n";
		else
		{
			t[numTrans] = new Transfer();
			t[numTrans]->uid = id;
			t[numTrans]->value = x;
			t[numTrans]->ruid = y;
			balance -= x;
			numTrans++;
			cout << "<transaction complete>\n";
			cout << "<transactions: " << numTrans << ">\n";
		}
	}

	void UserReport()
	{
		if(numTrans == 0)
			cout << "\nTransaction Report: NULL\n";
		else
		{
			cout << "\nTransaction Report:\n";
			for (int i = 0; i < numTrans; i++)
			{
				t[i]->Report();
			}
		}
		cout << "Balance: $" << balance << "\n";
	}

	bool CheckBalance(int x)
	{
		if (balance - x >= 0)
			return true;
		else
			return false;
	}
};

User* NewUser(int s)
{
	User *u = new User(s);
	return u;
}

void Menu()
{
	cout << "\nMENU:\n1. Withdraw Funds\n2. Deposit Funds\n3. Transfer Funds\n4. Print Transaction Report\n5. Exit\nWhat would you like to do?: ";
}

void Divider()
{
	cout << "================================================================================";
}

void main()
{
	int s;					//variable for selecting menu options
	int x;					//variable for miscalaneous input
	int y;					//variable for miscalaneous input
	int id;					//variable to store entered userId
	bool user;				//verifies if a user exits
	int numUsers = 0;		//tracks total users in system
	int targetUser;			//sets active user
	bool end;				//keeps program in loop, will end program if true
	User* u[NUM_USERS];		//initialize array of user pointers to be intialized dynamically
	
	cout << "WELCOME TO TRANSMATT BANK TRANSACTION SYSTEM\n";
	end = false;
	while (end == false)
	{
		//menu and tracking values are reset
		user = false;
		s = x = y = id = targetUser = NULL;
		
		//while there is no active user
		while (user == false)
		{
			cout << "\nPlease enter your 4-digit UserId: ";
			cin >> id;

			//displays how many users exist in system
			cout << "<users: " << numUsers << ">\n";

			//if there are existing users
			if (numUsers > 0)
			{
				//check all exisiting users for entered id
				for (int i = 0; i < numUsers; i++)
				{
					//if entered user id matches existing id, that user is selected as the active user
					if (id == u[i]->id)
					{
						targetUser = i;
						user = true;
						cout << "<user found>\n";
					}
				}

				//if the entered id does not match any existing ids, a new one is created and set as the active user
				if (user == false)
				{
					targetUser = numUsers;
					numUsers++;
					u[targetUser] = NewUser(id);
					cout << "<users: " << numUsers << ">\n";
					user = true;
				}
			}

			//if there are no existing users yet, an initial user is created
			else if (numUsers == 0)
			{
				targetUser = numUsers;
				u[targetUser] = NewUser(id);
				numUsers++;
				cout << "<users: " << numUsers << ">\n";
				cout << "\nWelcome, user: " << u[targetUser]->id << "\n";
				user = true;
			}
		}

		//accessable only once a user is verified 
		Menu(); //prints menu
		cin >> s;

		//user entered options for slecting transaction types, printing a report, or exiting the program
		if (s == 1)
		{
			//asks user for value of transaction
			cout << "How much would you like to Withdraw?: ";
			cin >> x;
			//calls User function to intialize a new withdrawal transaction
			u[targetUser]->NewWithdrawal(x);
		}

		if (s == 2)
		{
			//asks user for value of transaction
			cout << "How much would you like to Deposit?: ";
			cin >> x;
			//calls User function to intialize a new deposit transaction
			u[targetUser]->NewDeposit(x);
		}

		if (s == 3)
		{
			user = false;
			int n;
			while (user == false)
			{
				//asks user for the recipient user id
				cout << "Please enter the 4-digit ID of the user you wish to transfer to (5-exit): ";
				cin >> y;
				if (y == 5)
					end == true;
				else
				{
					for (int i = 0; i < numUsers; i++)
					{
						if (y == u[i]->id)
						{
							cout << "<user found>\n";
							user = true;
							n = i;
						}
					}
					if (user == false)
						cout << "Error: User Not Found\n";
				}
			}
			cout << "How much would you like to Transfer?: ";
			cin >> x;
			//calls User function to intialize a new transfer transaction, transfer function requires additional user id sent as parameter
			if (u[targetUser]->CheckBalance(x) == true)
				u[n]->balance += x;
			u[targetUser]->NewTransfer(x, y);
		}

		if (s == 4)
		{
			//calls active user's report function which then calls each transaction's report
			u[targetUser]->UserReport();
		}

		if (s == 5) //ends program
			end = true;
		Divider();
	}
}