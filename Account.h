#pragma once
#include<iostream>
#include<string>
using namespace std;
class Account
{
public:
	void Rewrite();
	bool CheckPassword(string& password);
	void Register();
	string Login();
	void Change(string& phonenumber, char& index); //¸ü¸ÄÉèÖÃ
};