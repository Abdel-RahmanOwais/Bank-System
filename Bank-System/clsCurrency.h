#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
class clsCurrency
{

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float  _Rate;

	static clsCurrency _ConvertCurrencyLineToObject(string Line, string Seperator = "#//#") {
		vector <string> vCurrency;

		vCurrency = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2],
					stod(vCurrency[3]));
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {

		string CurrencyLine = "";
		CurrencyLine += Currency.GetCountry() + Seperator;
		CurrencyLine += Currency.GetCurrencyCode() + Seperator;
		CurrencyLine += Currency.GetCurrencyName() + Seperator;
		CurrencyLine += to_string(Currency.GetRate());
		
		return CurrencyLine;
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile() {
		
		vector <clsCurrency> vCurrency;

		fstream Currencies;
		Currencies.open("Currencies.txt", ios::in);//Read Mode

		if (Currencies.is_open()) {
			string Line;

			while (getline(Currencies, Line))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
				vCurrency.push_back(Currency);
			}

			Currencies.close();
		}

		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency) {
		fstream Currencies;

		Currencies.open("Currencies.txt", ios::out); //Overwirte

		if (Currencies.is_open()) {
			string DataLine;

			for (clsCurrency& C : vCurrency)
			{
				DataLine = _ConverCurrencyObjectToLine(C);

				Currencies << DataLine << endl;
			}



			Currencies.close();
		}

	}

	void _Update() {
		vector <clsCurrency> vCurrency;

		vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : vCurrency) {

			if (C.GetCurrencyCode() == GetCurrencyCode()) {	 
			C = *this;
			break;
			}

		}

		_SaveCurrencyDataToFile(vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string GetCountry() { //Read Only Property
		return _Country;
	}

	string GetCurrencyCode() { //Read Only Property
		return _CurrencyCode;
	}
	
	string GetCurrencyName() { //Read Only Property
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	void SetRate(float Rate) {
		Rate = _Rate;
	}

	float GetRate() {
		return _Rate;
	}

	_declspec(property(get = GetRate, put = SetRate)) float Rate;

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream Currencies;
		Currencies.open("Currencies.txt", ios::in); // Read Mode

		if (Currencies.is_open()) {
			string Line;

			while(getline(Currencies, Line)) 
			{
				clsCurrency C = _ConvertCurrencyLineToObject(Line);

				if (C.GetCurrencyCode() == CurrencyCode)
				{
					Currencies.close();
					return C;
				}

			}

			Currencies.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);

		fstream Currencies;
		Currencies.open("Currencies.txt", ios::in); // Read Mode

		if (Currencies.is_open()) {
			string Line;

			while(getline(Currencies, Line)) 
			{
				clsCurrency C = _ConvertCurrencyLineToObject(Line);

				if (clsString::UpperAllString(C.GetCountry()) == Country)
				{
					Currencies.close();
					return C;
				}

			}

			Currencies.close();
		}

		return _GetEmptyCurrencyObject();
	}
	
	static bool IsCurrencyExistByCode(string CountryCode) {
		clsCurrency C = clsCurrency::FindByCode(CountryCode);

		return (!C.IsEmpty());
	}	
	
	static bool IsCurrencyExistByCountryName(string CountryName) {
		clsCurrency C = clsCurrency::FindByCountry(CountryName);

		return (!C.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}


	double ConvertToUSD(double Amount) {
		return double(Amount / Rate);
	}

	double ConvertToOtherCurrency(double Amount, clsCurrency CurrencyTo) {
		
		double AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo.GetCurrencyCode() == "USD") {
			return AmountInUSD;
		}

		return double(AmountInUSD * CurrencyTo.Rate);
	}

};

