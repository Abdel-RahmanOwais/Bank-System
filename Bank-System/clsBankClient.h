#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include <iostream>
#include "clsDate.h"
#include <string>
#include <vector>

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDeleted = false;

	string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#") 
	
	{
		
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeToString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName) {
		
		string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream TransferLogFile;

		TransferLogFile.open("TransferLog.txt", ios::out | ios::app); // OUT to remove info when open the file and APP to append info if any info exist.

		if (TransferLogFile.is_open()) {

			TransferLogFile << DataLine << endl;

			TransferLogFile.close();
		}
	}

	/*static stTransferLogin _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogin TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.ClientAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationClientAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.ClientBalance = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.DestinationClientBalance = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}*/

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConvertRecordToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string ClientRecord = "";

		ClientRecord += Client.FirstName + Seperator;
		ClientRecord += Client.LastName + Seperator;
		ClientRecord += Client.Email + Seperator;
		ClientRecord += Client.Phone + Seperator;
		ClientRecord += Client.AccountNumber() + Seperator;
		ClientRecord += Client.PinCode + Seperator;
		ClientRecord += to_string(Client.AccountBalance);

		return ClientRecord;

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream ClientFile;
		ClientFile.open("Clients.txt", ios::in);//read Mode

		if (ClientFile.is_open())
		{

			string Line;
			
			while (getline(ClientFile, Line)) {

			clsBankClient Client = _ConvertLinetoClientObject(Line);
			vClients.push_back(Client);
			}

			ClientFile.close();

		}

		return vClients;

	}
	

	void _AddDataLineToFile(string  DataLine)
	{
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::out | ios::app);

		if (ClientsFile.is_open())
		{

			ClientsFile << DataLine << endl;

			ClientsFile.close();
		}
	}

	static void _SaveClientDataToFile(vector <clsBankClient> Client) {
		fstream ClientFile;

		ClientFile.open("Clients.txt", ios::out);//Overrite

		string DataLine;

		if (ClientFile.is_open()) {

			for (clsBankClient& C : Client) {
				DataLine = _ConvertRecordToLine(C);
				ClientFile << DataLine << endl;
			}

			ClientFile.close();
		}
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> Client) {
		fstream ClientFile;

		ClientFile.open("Clients.txt", ios::out);//Overwrite

		string DataLine;

		if (ClientFile.is_open()) {

			for (clsBankClient& C : Client) {
				
				if (C._MarkForDeleted == false) 
				{
					DataLine = _ConvertRecordToLine(C);
					ClientFile << DataLine << endl;
				}
			}

			ClientFile.close();
		}
	}

	void _Update() {
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}

		}

		_SaveClientDataToFile(_vClients);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertRecordToLine(*this));
	
	}

public:

	struct stTransferLogin
	{
		string DateTime;
		string ClientAccountNumber;
		string DestinationClientAccountNumber;
		double Amount;
		double ClientBalance;
		double DestinationClientBalance;
		string UserName;
	};

	static stTransferLogin ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogin TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.ClientAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationClientAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.ClientBalance = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.DestinationClientBalance = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}

	clsBankClient(enMode Mode, string FirstName, string LastNmae, string Email,
		string Phone, string AccountNumber, string PinCode, double AccountBalance) :
		clsPerson(FirstName, LastNmae, Email, Phone) 
	
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}


	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	//Read Only
	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	/*
	//No UI Related Code Insid Object.

	void Print()
	{
		cout << "\n_____________________________________\n";
		cout << "\n\t  Client Card : ";
		cout << "\n_____________________________________";
		cout << "\nFirstName      : " << FirstName << endl;
		cout << "\nLastName       : " << LastName << endl;
		cout << "\nFull Name      : " << FullName() << endl;
		cout << "\nEmail          : " << Email << endl;
		cout << "\nPhone          : " << Phone << endl;
		cout << "\nAccount Number : " << _AccountNumber << endl;
		cout << "\nPin Code       : " << _PinCode << endl;
		cout << "\nBalance        : " << _AccountBalance << endl;
		cout << "_____________________________________";
	}*/


	static clsBankClient Find(string AccountNumber) {
		vector <clsBankClient> vClients;
		
		fstream ClientData;

		ClientData.open("Clients.txt", ios::in); //Read Mode
	
		if (ClientData.is_open()) {
			string Line;
			while (getline(ClientData, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber) {
					ClientData.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			ClientData.close();
		}

		return _GetEmptyClientObject();
	}
		
	static clsBankClient Find(string AccountNumber, string PinCode) {
		vector <clsBankClient> vClients;
		
		fstream ClientData;

		ClientData.open("Clients.txt", ios::in); //Read Mode
	
		if (ClientData.is_open()) {
			string Line;
			while (getline(ClientData, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					ClientData.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			ClientData.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		
		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFalidEmptyObject = 0, svSucceeded = 1 , svFailedAccountNumberExsit = 2};

	enSaveResults Save() {
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:

			if (IsEmpty()) {

				return enSaveResults::svFalidEmptyObject;

			}

			break;

		case clsBankClient::UpdateMode:
			_Update();

			return enSaveResults::svSucceeded;

			break;

		case clsBankClient::AddNewMode:

			//This will add new record to file or database
			if (clsBankClient::IsClientExist(AccountNumber())) {
				return svFailedAccountNumberExsit;
			}
			else {
				_AddNew();

				//We need to set the mode to update after add new client
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			
				break;
			}
		}

			
	}

	bool Delete() {
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber()) {
				C._MarkForDeleted = true;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}


	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients) {
			
			TotalBalances += Client.AccountBalance;

		}

		return TotalBalances;
	}

	void Deposit(double Amount) {

		_AccountBalance += Amount;

		Save();
	}


	bool Withdraw(double Amount) {

		if (Amount > AccountBalance) {
			return false;
		}
		else 
		{
		_AccountBalance -= Amount;
		Save();
		}
	}
	 
	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance) {
			return false;
		}
		
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);

		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;
	}

	static vector <stTransferLogin> GetTransferLoginList() {
		vector <stTransferLogin> vTransferLog;

		fstream TransferLogFile;

		TransferLogFile.open("TransferLog.txt", ios::in);

		if (TransferLogFile.is_open()) {
			string Line;
			stTransferLogin TransferRecord;

			while (getline(TransferLogFile, Line)) {

				TransferRecord = ConvertTransferLogLineToRecord(Line);

				vTransferLog.push_back(TransferRecord);
			}

			TransferLogFile.close();
		}

		return vTransferLog;
	}

};

