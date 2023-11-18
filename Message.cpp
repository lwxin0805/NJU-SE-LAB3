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
Friend d;
string Message::FindNameAndPhone(string& input,char &index)
{
	System system;
	system.ReadUserInfo();
	const vector<System::UserData*>& data = system.GetMyData();
	string output;
	for (auto& data_info : data)
	{
		if (input == data_info->username && index == '1') //找手机号
		{
			output = data_info->phonenumber;
			break;
		}
		else if (input == data_info->phonenumber && index == '2')  //找名字
		{
			output = data_info->username;
			break;
		}
	}
	return output;
}
void Message:: SendMessage(string& phonenumber)
{
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	string phonenumber_receiver,message_str,ans;
	cout << "请输入您想发送信息的对象" << endl;
	cout << "手机号：" << endl;
	cin >> phonenumber_receiver;
	char z = '2';
	//检查是不是朋友?
	while (true)
	{
		if (d.BoolNotFriend(phonenumber, phonenumber_receiver)) //true才是朋友
		{
			cout << "输入您想发送的信息" << endl;
			cin >> message_str;
			System::MessageOneData messageOne;
			messageOne.phonenumber_sender = phonenumber;
			messageOne.username_sender = FindNameAndPhone(phonenumber,z);
			messageOne.phonenumber_receiver = phonenumber_receiver;
			messageOne.username_receiver = FindNameAndPhone(phonenumber_receiver,z);
			messageOne.content = message_str;
			system.WriteMessageOne(messageOne);
			cout << "您是否还想发送信息给他吗?" << endl;
			cout << "yes/no" << endl;
			cin >> ans;
			if (ans == "yes")
			{
				continue;
			}
			else if (ans == "no")
			{
				break;
			}
		}
		else //friend =false 不是朋友
		{
			cout << "你们还不是朋友，所以不能发送信息" << endl;
			break;
		}
	}
}
void Message:: SendMessagePeoples(string& phonenumber)
{
	char z = '2';
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	string phonenumber_receiver1, phonenumber_receiver2, message_str, ans;
	cout << "请输入您想发送信息的对象们" << endl;
	cout << "手机号1：" << endl;
	cin >> phonenumber_receiver1;
	cout << "手机号2：" << endl;
	cin >> phonenumber_receiver2;
	while (true)
	{
		if (d.BoolNotFriend(phonenumber, phonenumber_receiver1) && d.BoolNotFriend(phonenumber, phonenumber_receiver2) && d.BoolNotFriend(phonenumber_receiver1, phonenumber_receiver2)) //true才是朋友
		{
			cout << "输入您想发送的信息" << endl;
			cin >> message_str;
			System::MessageGroupData messageGroup;
			messageGroup.phonenumber_sender = phonenumber;
			messageGroup.username_sender = FindNameAndPhone(phonenumber,z);
			messageGroup.phonenumber_receiverA = phonenumber_receiver1;
			messageGroup.username_receiverA = FindNameAndPhone(phonenumber_receiver1,z);
			messageGroup.phonenumber_receiverB = phonenumber_receiver2;
			messageGroup.username_receiverB = FindNameAndPhone(phonenumber_receiver2,z);
			messageGroup.content = message_str;
			system.WriteMessageGroup(messageGroup);
			cout << "您是否还想发送信息给他们吗?" << endl;
			cout << "yes/no" << endl;
			cin >> ans;
			if (ans == "yes")
			{
				continue;
			}
			else if (ans == "no")
			{
				break;
			}
		}
		else //friend =false 不是朋友
		{
			cout << "有人不是你的好友，所以不能发送群聊给他们" << endl;
			break;
		}
	}
	
}
void Message:: CheckHistory(string &phonenumber, char &index1, char& index2)
{
	System system;
	system.ReadMessageGroup();
	const vector<System::MessageGroupData*>& data_many = system.GetMyMessageGroup();
	system.ReadMessageOne();
	const vector<System::MessageOneData*>& data_one = system.GetMyMessageOne();
	string input1,input2;
	bool friend_yes = false;
	bool find = false;
	switch (index1)
	{
	case'1': //某位朋友
	{
		switch (index2)
		{
		case'1': //手机号
		{
			cout << "输入您想寻找聊天记录的手机号" << endl;
			cin >> input1;
			for (const auto& message_info : data_one)
			{
				if (d.BoolNotFriend(phonenumber, input1))
				{
					friend_yes = true;
					if ((phonenumber == message_info->phonenumber_receiver || phonenumber == message_info->phonenumber_sender )&& (input1 == message_info->phonenumber_sender || input1 == message_info->phonenumber_receiver))
					{
						find = true;
						cout << message_info->phonenumber_sender << " : " << message_info->content << endl;
					}
				}
			}
			if (!friend_yes)
			{
				cout << "您没有添加该手机号为朋友" << endl;
			}
			break;
		}
		case'2': //昵称
		{
			cout << "输入您想寻找聊天记录的昵称" << endl;
			cin >> input1;
			char x = '1';
			string UserToPhone = FindNameAndPhone(input1, x);
			for (const auto& message_info : data_one)
			{
				if (d.BoolNotFriend(phonenumber, UserToPhone))
				{
					friend_yes = true;
					if ((phonenumber == message_info->phonenumber_receiver || phonenumber == message_info->phonenumber_sender) && (input1 == message_info->username_sender || input1 == message_info->username_receiver))
					{
						find = true;
						cout << message_info->phonenumber_sender << " : " << message_info->content << endl;
					}
				}
			}
			if (!friend_yes)
			{
				cout << "您没有添加该昵称为朋友" << endl;
			}
			break;
		}
		case'3': //关键词
		{
			cout << "输入您想寻找聊天记录的关键词" << endl;
			cin >> input1;
			friend_yes = true;
			find=system.ReadMessageOneHighlight(phonenumber, input1);
			const vector<System::MessageOneData*>& message = system.GetMyMessageHighlightOne();
			break;
		}
		}
		if (!find && friend_yes)
		{
			cout << "没有聊天记录" << endl;
		}
		break;
	}
	case'2': //某朋友们
		switch (index2)
		{
		case'1': //手机号
		{
			cout << "输入您想寻找聊天记录的手机号" << endl;
			cin >> input1 >> input2;
			for (const auto& message_info : data_many)
			{

				if (d.BoolNotFriend(phonenumber, input1)&& d.BoolNotFriend(phonenumber, input2)&& d.BoolNotFriend(input2, input1))
				{
					friend_yes = true;
					if ((phonenumber == message_info->phonenumber_receiverA || phonenumber == message_info->phonenumber_receiverB || phonenumber == message_info->phonenumber_sender )&&( input1 == message_info->phonenumber_sender || input1 == message_info->phonenumber_receiverA || input1 == message_info->phonenumber_receiverB )&& (input2 == message_info->phonenumber_sender || input2 == message_info->phonenumber_receiverA || input2 == message_info->phonenumber_receiverB))
					{
						find = true;
						cout << message_info->phonenumber_sender << ", " << message_info->phonenumber_receiverA << ", " << message_info->phonenumber_receiverB << ":" << message_info->content << endl;
					}
				}
			}
			if (!friend_yes)
			{
				cout << "您没有添加最少1位手机号为朋友" << endl;
			}
			break;
		}
		case'2': //昵称
		{
			cout << "输入您想寻找聊天记录的昵称" << endl;
			cin >> input1 >> input2;
			char x = '1';
			string usertophone1 = FindNameAndPhone(input1, x);
			string usertophone2 = FindNameAndPhone(input2, x);
			for (const auto& message_info : data_many)
			{
				if (d.BoolNotFriend(phonenumber, usertophone2) && d.BoolNotFriend(phonenumber, usertophone1) && d.BoolNotFriend(usertophone2, usertophone1))
				{
					friend_yes = true;
					if ((phonenumber == message_info->phonenumber_receiverA || phonenumber == message_info->phonenumber_receiverB || phonenumber == message_info->phonenumber_sender) &&( input1 == message_info->username_sender || input1 == message_info->username_receiverA || input1 == message_info->username_receiverB) && (input2 == message_info->username_sender || input2 == message_info->username_receiverA || input2 == message_info->username_receiverB))
					{
						find = true;
						cout << message_info->phonenumber_sender << ", " << message_info->phonenumber_receiverA << ", " << message_info->phonenumber_receiverB << ":" << message_info->content << endl;
					}
				}
			}
			if (!friend_yes)
			{
				cout << "您没有添加最少1位昵称为朋友" << endl;
			}
			break;
		}
		case'3': //关键词
		{
			cout << "输入您想寻找聊天记录的关键词" << endl; //重点是要有自己在就行
			cin >> input1;
			find = true;
			friend_yes = false;
			int x = system.ReadMessageGroupHighlight(phonenumber, input1);
			const vector<System::MessageGroupData*>& message = system.GetMyMessageHighlightGroup();
			if (x == 2)
			{
				cout << "没有聊天记录" << endl;
			}
			else if (x == 0)
			{
				cout << "其中最少一位好友已不是好友关系" << endl;
			}
			break;
		}
		}
		if (!find&& friend_yes)
		{
			cout << "没有聊天记录" << endl;
		}
		break;
	}
}
