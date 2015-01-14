#include <sstream>
#include "Bank.h"

// Implemn
Bank::Bank() {}
Bank::~Bank() {}

int Bank::Withdraw(unsigned int id, unsigned int fund, int amount)
{
	// Create dummy account so we can search through the tree
	Account *dummy = new Account(id, "dummy", "account");

	// Create a temp pointer to hold found object
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->Withdraw(fund, amount);
		return true;
	}
	else
	{
		// Account not found
		// Print Message to console
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		return false;
	}

}

int Bank::Deposit(unsigned int id, unsigned int fund, int amount)
{
	// Create dummy account so we can search through the tree
	Account *dummy = new Account(id, "dummy", "account");

	// Create a temp pointer to hold found object
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->Deposit(fund, amount);
		return true;
	}
	else
	{
		// Account not found
		// Print Message to console
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		return false;
	}
}

bool Bank::Transfer(unsigned int sourceID, unsigned int sourceFund, int amount,
	unsigned int destID, unsigned int destFund)
{
	// Create dummy account so we can search through the tree
	Account *dummy1 = new Account(sourceID, "dummy", "account");

	// Create dummy account so we can search through the tree
	Account *dummy2 = new Account(destID, "dummy", "account");

	// Create temp pointers
	Account *source;
	Account *dest;

	// Check to see if both accounts exist
	if (!pAccounts.Retrieve(*dummy1, source))
	{
		// Throw Error if it returned false
		cout << "ERROR: Account " << sourceID << " does not exist. Transaction refused." << endl;
		return false;
	}
	if (!pAccounts.Retrieve(*dummy2, dest))
	{
		// Throw Error if it returned false
		cout << "ERROR: Account " << destID << " does not exist. Transaction refused." << endl;
		return false;
	}

	// Check for funds in source account
	if (source->SendTransfer(sourceFund, amount, destID))
	{
		// Success
		dest->RecieveTransfer(destFund, amount, sourceID);
		return true;
	}
	else
	{
		// Fail. Nothing was sent
		dest->RecieveTransfer(destFund, 0, sourceID);
		return false;
	}
}

bool Bank::History(unsigned int id, unsigned int fund)
{
	// Create dummy account so we can search through the tree
	Account *dummy = new Account(id, "dummy", "account");

	// Create a temp pointer to hold found object
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->getHistory(id, fund);
		cout << endl;
		return true;
	}
	else
	{
		// Account not found
		// Print Message to console
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		return false;
	}

	return true;
}

bool Bank::Open(string nameFirst, string nameLast, unsigned int id)
{
	Account *newAccount = new Account(id, nameFirst, nameLast);

	// Traverse tree to see if this account has been made
	if (pAccounts.Retrieve(*newAccount, newAccount))
	{
		// If retrieve returns true, the account exists
		// PRINT ERROR
		cout << "ERROR: Account " << id << " is already open. Transaction refused." << endl;
		return false;
	}
	else
	{
		// Account does not exist. Add new account to the tree
		pAccounts.Insert(newAccount);
		return true;
	}
}

bool Bank::AddToQueue(vector<string> command)
{
	pCommandQueue.push(command);
	return true;
}

bool Bank::ProcessQueue()
{
	vector<string> commands;

	while (!pCommandQueue.empty())
	{
		// Get next command
		commands = pCommandQueue.front();

		if (commands[0] == "O")
		{
			Open(commands[2], commands[1], stoi(commands[3]));
		}
		else if (commands[0] == "D")
		{
			Deposit(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		else if (commands[0] == "W")
		{
			Withdraw(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		else if (commands[0] == "T")
		{
			Transfer(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]), 
				stoi(commands[4]), stoi(commands[5]));
		}
		else if (commands[0] == "H")
		{
			if (commands[1].length() == 5)
			{
				History(stoi(commands[1]), stoi(commands[2]));
			}
			else
			{
				History(stoi(commands[1]), -1);
			}
		}

		pCommandQueue.pop();
	}

	cout << endl;
	cout << "Processing Done! Printing final balances" << endl;
	return true;
}

void Bank::Print()
{

}