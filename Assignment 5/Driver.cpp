#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Bank.h"

using namespace std;

Bank *bank = new Bank();
void ParseFromFile(string path);

int main()
{
	ParseFromFile("BankTrans.txt");
	bank->ProcessQueue();
	bank->Print();
}

void ParseFromFile(string path)
{
	ifstream fin;
	string tempstr = "";
	vector<string> data;

	fin.open(path);

	while (!fin.eof())
	{
		fin >> tempstr;
		data.push_back(tempstr);

		// Crude input. I hate myself for this haha.....
		// This assumes that the input is structured correctly as per the assignment sheet
		if (data[0] == "T")
		{
			// ID1
			fin >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund1
			data.push_back(tempstr.substr(tempstr.length() - 1, 
				tempstr.length() - 1));

			// Amount
			fin >> tempstr;
			data.push_back(tempstr);

			// ID2
			fin >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund2
			data.push_back(tempstr.substr(tempstr.length() - 1,
				tempstr.length() - 1));
		}
		// Open
		else if (data[0] == "O")
		{
			// Last Name
			fin >> tempstr;
			data.push_back(tempstr);

			// First Name
			fin >> tempstr;
			data.push_back(tempstr);

			// ID1
			fin >> tempstr;
			data.push_back(tempstr);
		}
		else if (data[0] == "H")
		{
			// ID1
			fin >> tempstr;

			// Handle wanting to see a specific fund
			if (tempstr.length() == 5)
			{
				data.push_back(tempstr.substr(0, tempstr.length() - 1));

				// Fund1
				data.push_back(tempstr.substr(tempstr.length() - 1,
					tempstr.length() - 1));
			}
			// Handle seeing entire account history
			else
			{
				data.push_back(tempstr);
			}
			
		}
		// Deposit/Withdraw
		else
		{
			// ID1
			fin >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund1
			data.push_back(tempstr.substr(tempstr.length() - 1,
				tempstr.length() - 1));

			// Money
			fin >> tempstr;
			data.push_back(tempstr);
		}

		// Push vector to queue
		bank->AddToQueue(data);

		// Clear vector
		data.clear();
	}
}