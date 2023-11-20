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
{ //NotFriend���true����Ҫ�������
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
				cout << "�Ѿ��Ǻ�������" << endl;
				friend_alr = true;
				return 1;
			}
			else if (friend_info->friend_add == 0 && phonenumber_re == friend_info->phonenumber_sender && phonenumber_se == friend_info->phonenumber_receiver) //��������
			{
				cout << "�Ѿ�������������� �����ظ���" << endl;
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
		case'1': //�ֻ���
		{
			cout << "��������Ӻ��ѵ��ֻ���" << endl;
			cin >> input;
			//����Not FriendҪ�ǲ������Ѳſ��� ���� ���� ҪС��0 (�������Ѳſ��Է���)
			int x = NotFriend(phonenumber_re, input);
			if (x < 0)
			{
				for (auto& user : user_data)
				{
					if (user->phonenumber == input && user->accept == 1 && user->phonefind == 1) //Ĭ��ͨ�� + �ܱ��ҵ��ſ���
					{
						cout << "Ĭ��ͨ��..." << endl;
						ans_str = " ";
						gotphone = true;
						addalr = true;
					}
					else if (user->phonenumber == input && user->accept == false && user->phonefind == 1) //��Ҫ�ش�����+ �ܱ��ҵ��ſ���
					{
						cout << "��Է���������ش�������ܼ���Ϊ����" << endl;
						cout << user->question << endl;
						cin >> ans_str;
						cout << "���ڷ����������..." << endl;
						haventadd = true;
						gotphone = true;
					}
					else if (user->phonenumber == input && user->phonefind == 0) //����Ӻ���
					{
						cout << "�Է������˱��˲���ͨ���ֻ�����Ѱ" << endl;
						gotphone = true;
						break;
					}
					if (addalr) //Ҫֱ������
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
				cout << "�Ҳ������ֻ���" << endl;
			}
			break;
		}
		case'2': //�ǳ�
		{
			cout << "��������Ӻ��ѵ��ǳ�" << endl;
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
					if (user->phonenumber == usertophone && user->accept == 1 && user->usernamefind == 1) //Ĭ��ͨ��
					{
						cout << "Ĭ��ͨ��..." << endl;
						ans_str = " ";
						gotphone = true;
						addalr = true;
					}
					else if (user->phonenumber == usertophone && user->accept == false && user->usernamefind == 1) //��Ҫ�ش�����
					{
						cout << "��Է���������ش�������ܼ���Ϊ����" << endl;
						cout << user->question << endl;
						cin >> ans_str;
						cout << "���ڷ����������..." << endl;
						haventadd = true;
						gotphone = true;
					}
					else if (user->phonenumber == usertophone && user->usernamefind == 0) //����Ӻ���
					{
						cout << "�Է������˱��˲���ͨ���ǳ���Ѱ" << endl;
						gotphone = true;
						break;
					}
					if (addalr) //Ҫֱ������
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
				cout << "�Ҳ������ǳ�" << endl;
			}
			break;
		}
	}
}
void Friend::FriendList(string& phonenumber_re) //�鿴�����б�+����ɾ����
{
	string ans,delete_str,ans2;
	System system;
	system.ReadFriendList();
	const vector<System::FriendData*>& data = system.GetMyFriend();
	system.ReadUserInfo();
	const vector<System::UserData*>& user_data = system.GetMyData();
	string input, ans_str, usertophone;
	cout << "���������ĺ�����:" << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	for (auto& friend_info : data)
	{ //1�Ǻ���
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
	cout << "����û����ɾ���ĺ���?" << endl;
	cout << "yes = �� / no = û��" << endl;
	cin >> ans;
	bool delete_friend = false;
	bool cantfind = true;
	if (ans == "yes")
	{
		cout << "��������ɾ���ĺ��ѵ��ֻ���" << endl;
		while (true)
		{
			cin >> delete_str;
			for (auto& friend_info : data)
			{
				if ((phonenumber_re == friend_info->phonenumber_receiver || phonenumber_re == friend_info->phonenumber_sender) && (delete_str == friend_info->phonenumber_receiver || delete_str == friend_info->phonenumber_sender) && friend_info->friend_add == 1)
				{
					cout << "ȷ���Ƿ�ɾ����" << endl;
					cout << "yes = �� / no = ����" << endl;
					cin >> ans2;
					if (ans2 == "yes")
					{
						cout << "���ɹ�ɾ����Ϊ���ѣ�" << endl;
						friend_info->friend_add = -1;
						delete_friend = true;
						cantfind = false;
						break;
					}
				}
			}
			if (cantfind)
			{
				cout << "�������˵��ֻ��������⣬�����������룺" << endl;
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
void Friend::AcceptDeleteFriend(string& phonenumber) //�鿴�������� �ȼ�����
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
		{ //�������Ǳ��˼ӵģ���������receiver Ȼ��friend_add=0�Ƿ������󵫻�û����
			cout << friend_info->phonenumber_sender << "��Ҫ�����Ϊ����" << endl;
			cout << "�����������⣺" << friend_info->question << endl;
			cout << "�������Ļش�" << friend_info->answer << endl;
			cout << "�������Ƿ�ͬ��" << endl;
			cout << "yes = ͬ�� / no = ��ͬ��" << endl;
			cin >> ans;
			if (ans == "yes")
			{
				friend_info->friend_add = 1;
				cout << "����ͬ����Ϊ����" << endl;
				acceptornot = true;
				noone = false;
			}
			else 
			{
				friend_info->friend_add = -1;
				cout << "���Ѿܾ���Ϊ����" << endl;
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
		cout << "û�������Ϊ����" << endl;
	}
}