#include "Account.h"

// Imp
Account::Account(unsigned int id, string first, string last)
{
	pID = id;
	pNameFirst = first;
	pNameLast = last;

	pFunds[0] = new Fund("Money Market");
	pFunds[1] = new Fund("Prime Money Market");
	pFunds[2] = new Fund("Long-Term Bond");
	pFunds[3] = new Fund("Short-Term Bond");
	pFunds[4] = new Fund("500 Index Fund");
	pFunds[5] = new Fund("Capital Value Fund");
	pFunds[6] = new Fund("Growth Equity Fund");
	pFunds[7] = new Fund("Growth Index Fund");
	pFunds[8] = new Fund("Value Fund");
	pFunds[9] = new Fund("Stock Index Fund");
	
}

Account::~Account()
{

}

bool Account::Deposit(int fund, unsigned int amount)
{
	string status = "D " + to_string(pID) + to_string(fund) + " " + to_string(amount);

	if (HDeposit(fund, amount))
	{
		// Success
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		// Fail
		pFunds[fund]->Record(status + " (FAILED)");
		return false;
	}
}

bool Account::Withdraw(int fund, unsigned int amount)
{
	string status = "W " + to_string(pID) + to_string(fund) + " " + to_string(amount);

	if (HWithdraw(fund, amount))
	{
		// Success
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		// Fail
		pFunds[fund]->Record(status + " (FAILED)");
		return false;
	}
}

bool Account::SendTransfer(unsigned int fund, unsigned int amount, unsigned int destID)
{
	if (HWithdraw(fund, amount))
	{
		// Print SUCCESS MESSAGE
		return true;
	}
	else
	{
		// PRINT FAIL MESSAGE
		return false;
	}
}

bool Account::RecieveTransfer(unsigned int fund, unsigned int amount, unsigned int sourceID)
{
	if (HDeposit(fund, amount))
	{
		// Print SUCCESS MESSAGE
		return true;
	}
	else
	{
		// PRINT FAIL MESSAGE
		return false;
	}
}

void Account::getHistory(unsigned int id, int fund) const
{
	vector<string> temp;

	if (fund == -1)
	{
		cout << "Transaction History for " + getName() + " By Fund." << endl;
		for (int i = 0; i < 10; i++)
		{
			temp = pFunds[i]->getRecord();

			cout << pFunds[i]->getName() + ": $"; 
			cout << pFunds[i]->getBalance() << endl;

			for (auto it = temp.begin(); it < temp.end(); it++)
			{
				cout << "  " + *it << endl;
			}
		}
	}
	else
	{
		cout << "Transaction History for " + getName();
		cout << pFunds[fund]->getName() << endl;
	}
}

string Account::getName() const
{
	return pNameLast + " " + pNameFirst;
}

unsigned int Account::getID() const
{
	return pID;
}
// Private Members [CHECK FOR BUG]
bool Account::FundCoverage(int fund, int amount)
{
	int altFund;

	// Logic to control what fund to borrow from
	switch (fund)
	{
	case 0:
		altFund = 1;
		break;
	case 1:
		altFund = 0;
		break;
	case 2:
		altFund = 3;
		break;
	case 3:
		altFund = 2;
		break;
	default:
		return false;
	}

	// Check to see what the balance would be in advance
	int balance = pFunds[fund]->getBalance() - amount;

	// If it is negative, try to borrow from the other fund
	if (balance < 0)
	{
		// Peek at the balance in the alt Fund, we do not want to
		// Withdraw() from the fund before we are sure we can commit
		if (pFunds[altFund]->getBalance() >= abs(balance))
		{
			// We are good to withdraw from the fund now to cover
			// the first fund. Deposit into the first fund
			if (pFunds[altFund]->Withdraw(abs(balance)))
			{
				// If withdraw was successful
				pFunds[fund]->Deposit(abs(balance));
			}
			else
			{
				// Withdraw failed
				return false;
			}

			// Complete the withdraw
			return pFunds[fund]->Withdraw(amount);
		}
	}
	else
	{
		// Fund has enough money in it. Withdraw as per normal
		return pFunds[fund]->Withdraw(amount);
	}
	return true;
}

// Helper members so I can implement transfer as a series of withdraws or deposits
// without having to reimplement the FundCoverage setup logic in transfer methods
bool Account::HDeposit(int fund, unsigned int amount)
{
	// Check to see if the fund number is valid
	if (fund >= 0 && fund < 9)
	{
		// Deposit into this fund
		pFunds[fund]->Deposit(amount);

		// Success
		return true;
	}
	else
	{
		// Failure
		return false;
	}
}

bool Account::HWithdraw(int fund, unsigned int amount)
{
	// Validate Input
	// I assume that all input from file is good, but I want to protect
	// against bad input here if this member is called without reading
	// from file
	if (fund <= 0 || fund > 9)
	{
		cout << "ERROR: Fund Input Out of Range" << endl;
		return false;
	}

	// Handle edge cases
	if (fund == 0)
	{
		FundCoverage(fund, amount);
	}
	else if (fund == 1)
	{
		FundCoverage(fund, amount);
	}
	else if (fund == 2)
	{
		FundCoverage(fund, amount);
	}
	else if (fund == 3)
	{
		FundCoverage(fund, amount);
	}

	// Default case
	else
	{
		if (pFunds[fund]->Withdraw(amount))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

// Operator overloads
bool Account::operator==(const Account &other) const
{
	if (this->getID() == other.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::operator<(const Account &other) const
{
	if (this->getID() < other.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}