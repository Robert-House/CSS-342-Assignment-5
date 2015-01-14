#include "Fund.h"

Fund::Fund(string name)
{
	pBalance = 0;
	pName = name;

}

Fund::~Fund()
{
	
}

bool Fund::Deposit(unsigned int amount)
{
	// No limits to the size of the deposit
	pBalance += (int)amount;
	return true;
}

bool Fund::Withdraw(unsigned int amount)
{
	if (amount > pBalance)
	{
		return false;
	}
	else
	{
		pBalance -= amount;
		return true;
	}

	
}

bool Fund::Record(string record)
{
	pRecord.push_back(record);
	return true;
}

vector<string> Fund::getRecord()
{
	return pRecord;
}

int Fund::getBalance() const
{
	return pBalance;
}

string Fund::getName() const
{
	return pName;
}