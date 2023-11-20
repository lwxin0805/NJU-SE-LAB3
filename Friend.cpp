#include "InterfaceUI.h"
#include "Account.h"
#include "Message.h"
#include "Moment.h"
#include "Friend.h"
#include "System.h"
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

Message m;
InterfaceUI a;
bool Friend::BoolNotFriend(string& phonenumber_re, string& phonenumber_se)
{
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	bool friend_alr = false;
	for (auto& friend_info : data)
	{
		if ((phonenumber_re == friend_info->phonenumber_receiver || phonenumber_re == friend_info->phonenumber_sender) && (phonenumber_se == friend_info->phonenumber_sender || phonenumber_se == friend_info->phonenumber_receiver) && friend_info->friend_add == 1)
		{
			return true;
		}
	}
	return false;
}
int Friend::NotFriend(string& phonenumber_re, string& phonenumber_se)
{ //NotFriend如果true才需要添加朋友
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	bool friend_alr = false;
	for (auto& friend_info : data)
	{
		if ((phonenumber_re == friend_info->phonenumber_receiver || phonenumber_re == friend_info->phonenumber_sender) &&( phonenumber_se == friend_info->phonenumber_sender || phonenumber_se == friend_info->phonenumber_receiver))
		{
			if (friend_info->friend_add == 1)
			{
				cout << "已经是好朋友啦" << endl;
				friend_alr = true;
				return 1;
			}
			else if (friend_info->friend_add == 0 && phonenumber_re == friend_info->phonenumber_sender && phonenumber_se == friend_info->phonenumber_receiver) //发送请求
			{
				cout << "已经发送请求给他啦 等他回复嘛" << endl;
				friend_alr = true;
				return 0;
			}
		}
	}
	if (!friend_alr)
	{
		return -1;
	}
	return 1;
}
void Friend::AddFriend(string& phonenumber_re, char& index)
{
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	system.ReadUserInfo();
	const vector<System::UserData*>& user_data = system.GetMyData();
	string input, ans_str, usertophone;
	char z = '2';
	bool haventadd = false, gotphone = false, addalr = false;
	switch (index)
	{
		case'1': //手机号
		{
			cout << "输入您想加好友的手机号" << endl;
			cin >> input;
			//现在Not Friend要是不是朋友才可以 所以 就是 要小于0 (不是朋友才可以发送)
			int x = NotFriend(phonenumber_re, input);
			if (x < 0)
			{
				for (auto& user : user_data)
				{
					if (user->phonenumber == input && user->accept == 1 && user->phonefind == 1) //默认通过 + 能被找到才可以
					{
						cout << "默认通过..." << endl;
						ans_str = " ";
						gotphone = true;
						addalr = true;
					}
					else if (user->phonenumber == input && user->accept == false && user->phonefind == 1) //需要回答问题+ 能被找到才可以
					{
						cout << "因对方设置了需回答问题才能加他为好友" << endl;
						cout << user->question << endl;
						cin >> ans_str;
						cout << "正在发送请求给他..." << endl;
						haventadd = true;
						gotphone = true;
					}
					else if (user->phonenumber == input && user->phonefind == 0) //不添加好友
					{
						cout << "对方设置了别人不能通过手机号搜寻" << endl;
						gotphone = true;
						break;
					}
					if (addalr) //要直接输入
					{
						System::FriendData friendData;
						friendData.phonenumber_sender = phonenumber_re;
						friendData.username_sender = m.FindNameAndPhone(phonenumber_re,z);
						friendData.phonenumber_receiver = input;
						friendData.username_receiver = m.FindNameAndPhone(input,z);
						friendData.friend_add = 1;
						friendData.question = user->question;
						friendData.answer = ans_str;
						system.WriteFriendList(friendData);
						break;
					}
					else if (haventadd)
					{
						System::FriendData friendData;
						friendData.phonenumber_sender = phonenumber_re;
						friendData.username_sender = m.FindNameAndPhone(phonenumber_re,z);
						friendData.phonenumber_receiver = input;
						friendData.username_receiver = m.FindNameAndPhone(input,z);
						friendData.friend_add = 0;
						friendData.question = user->question;
						friendData.answer = ans_str;
						system.WriteFriendList(friendData);
						break;
					}
				}
			}
			else if (x >= 0)
			{
				gotphone = true;
			}
			if (!gotphone)
			{
				cout << "找不到此手机号" << endl;
			}
			break;
		}
		case'2': //昵称
		{
			cout << "输入您想加好友的昵称" << endl;
			cin >> input;
			for (auto& user : user_data)
			{
				if (input == user->username)
				{
					usertophone = user->phonenumber;
					break;
				}
			}
			int x = NotFriend(phonenumber_re, usertophone);
			if (x < 0)
			{
				for (auto& user : user_data)
				{
					if (user->phonenumber == usertophone && user->accept == 1 && user->usernamefind == 1) //默认通过
					{
						cout << "默认通过..." << endl;
						ans_str = " ";
						gotphone = true;
						addalr = true;
					}
					else if (user->phonenumber == usertophone && user->accept == false && user->usernamefind == 1) //需要回答问题
					{
						cout << "因对方设置了需回答问题才能加他为好友" << endl;
						cout << user->question << endl;
						cin >> ans_str;
						cout << "正在发送请求给他..." << endl;
						haventadd = true;
						gotphone = true;
					}
					else if (user->phonenumber == usertophone && user->usernamefind == 0) //不添加好友
					{
						cout << "对方设置了别人不能通过昵称搜寻" << endl;
						gotphone = true;
						break;
					}
					if (addalr) //要直接输入
					{
						System::FriendData friendData;
						friendData.phonenumber_sender = phonenumber_re;
						friendData.username_sender = m.FindNameAndPhone(phonenumber_re,z);
						friendData.phonenumber_receiver = usertophone;
						friendData.username_receiver = m.FindNameAndPhone(usertophone,z);
						friendData.friend_add = 1;
						friendData.question = user->question;
						friendData.answer = ans_str;
						system.WriteFriendList(friendData);
						break;
					}
					else if (haventadd)
					{
						System::FriendData friendData;
						friendData.phonenumber_sender = phonenumber_re;
						friendData.username_sender = m.FindNameAndPhone(phonenumber_re,z);
						friendData.phonenumber_receiver = usertophone;
						friendData.username_receiver = m.FindNameAndPhone(usertophone,z);
						friendData.friend_add = 0;
						friendData.question = user->question;
						friendData.answer = ans_str;
						system.WriteFriendList(friendData);
						break;
					}
				}
			}
			else if (x >= 0)
			{
				gotphone = true;
			}
			if (!gotphone)
			{
				cout << "找不到此昵称" << endl;
			}
			break;
		}
	}
}
void Friend::FriendList(string& phonenumber_re) //查看好友列表+可以删除人
{
	string ans,delete_str,ans2;
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	system.ReadUserInfo();
	const vector<System::UserData*>& user_data = system.GetMyData();
	string input, ans_str, usertophone;
	cout << "以下是您的好友们:" << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	for (auto& friend_info : data)
	{ //1是好友
		if ((phonenumber_re == friend_info->phonenumber_receiver || phonenumber_re == friend_info->phonenumber_sender) && friend_info->friend_add == 1)
		{
			if (phonenumber_re == friend_info->phonenumber_receiver)
			{
				cout << friend_info->username_sender;
			}
			if (phonenumber_re == friend_info->phonenumber_sender)
			{
				cout << friend_info->username_receiver;
			}
			cout << endl;
		}
	}
	cout << "你有没有想删除的好友?" << endl;
	cout << "yes = 有 / no = 没有" << endl;
	cin >> ans;
	bool delete_friend = false;
	bool cantfind = true;
	if (ans == "yes")
	{
		cout << "输入您想删除的好友的手机号" << endl;
		while (true)
		{
			cin >> delete_str;
			for (auto& friend_info : data)
			{
				if ((phonenumber_re == friend_info->phonenumber_receiver || phonenumber_re == friend_info->phonenumber_sender) && (delete_str == friend_info->phonenumber_receiver || delete_str == friend_info->phonenumber_sender) && friend_info->friend_add == 1)
				{
					cout << "确定是否删除？" << endl;
					cout << "yes = 是 / no = 不是" << endl;
					cin >> ans2;
					if (ans2 == "yes")
					{
						cout << "您成功删除他为好友！" << endl;
						friend_info->friend_add = -1;
						delete_friend = true;
						cantfind = false;
						break;
					}
				}
			}
			if (cantfind)
			{
				cout << "您输入了的手机号有问题，请您重新输入：" << endl;
				continue;
			}
			if (!cantfind)
			{
				break;
			}
		}
		if (delete_friend)
		{
			ofstream clear_file("FriendList.txt");
			clear_file.close();
			for (const auto& u : data)
			{
				system.WriteFriendList(*u);;
			}
		}
	}
	else
	{
		a.AddFriendInterface(phonenumber_re);
	}
	return;
}
void Friend::AcceptDeleteFriend(string& phonenumber) //查看好友请求 先加朋友
{
	string ans;
	System system;
	bool noone = true;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	for (auto& friend_info : data)
	{
		bool acceptornot = false;
		if (phonenumber == friend_info->phonenumber_receiver && friend_info->friend_add == 0)
		{ //现在我是被人加的，所以我是receiver 然后friend_add=0是发了请求但还没接受
			cout << friend_info->phonenumber_sender << "想要添加您为好友" << endl;
			cout << "这是您的问题：" << friend_info->question << endl;
			cout << "这是他的回答：" << friend_info->answer << endl;
			cout << "请问您是否同意" << endl;
			cout << "yes = 同意 / no = 不同意" << endl;
			cin >> ans;
			if (ans == "yes")
			{
				friend_info->friend_add = 1;
				cout << "您已同意他为好友" << endl;
				acceptornot = true;
				noone = false;
			}
			else 
			{
				friend_info->friend_add = -1;
				cout << "您已拒绝他为好友" << endl;
				acceptornot = true;
				noone = false;
			}
		}
		if (acceptornot)
		{
			ofstream clear_file("FriendList.txt");
			clear_file.close();
			for (const auto& u : data)
			{
				system.WriteFriendList(*u);;
			}
			break;
		}
	}
	if (noone)
	{
		cout << "没人添加您为好友" << endl;
	}
}