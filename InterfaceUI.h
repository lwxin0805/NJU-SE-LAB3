#pragma once
#include<iostream>
#include<string>
using namespace std;
class InterfaceUI
{
public:
	void DefaultChoice();
	bool AgainService();
	void MainInterface();
	void MainMenu(string& phonenumber);
	void AddFriendInterface(string& phonenumber);
	void ChatPersonalOrGroup(string& phonenumber);
	void ChatInterface(string& phonenumber);
	void ChatHistoryOneOrGroup(string& phonenumber);
	void ChatHistoryInterface(string& phonenumber, char& index1);
	void CheckPYQOneOrMany(string& phonenumber);
	void CheckPYQOne(string& phonenumber);
	void CheckPYQ(string& phonenumber);
	void PYQInterface(string& phonenumber);
	void SettingInterface(string& phonenumber);
	void AddFriendMethod(string& phonenumber);
	void PersonalSetting(string& phonenumber);
};

