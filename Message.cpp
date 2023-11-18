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
		if (input == data_info->username && index == '1') //���ֻ���
		{
			output = data_info->phonenumber;
			break;
		}
		else if (input == data_info->phonenumber && index == '2')  //������
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
	cout << "���������뷢����Ϣ�Ķ���" << endl;
	cout << "�ֻ��ţ�" << endl;
	cin >> phonenumber_receiver;
	char z = '2';
	//����ǲ�������?
	while (true)
	{
		if (d.BoolNotFriend(phonenumber, phonenumber_receiver)) //true��������
		{
			cout << "�������뷢�͵���Ϣ" << endl;
			cin >> message_str;
			System::MessageOneData messageOne;
			messageOne.phonenumber_sender = phonenumber;
			messageOne.username_sender = FindNameAndPhone(phonenumber,z);
			messageOne.phonenumber_receiver = phonenumber_receiver;
			messageOne.username_receiver = FindNameAndPhone(phonenumber_receiver,z);
			messageOne.content = message_str;
			system.WriteMessageOne(messageOne);
			cout << "���Ƿ��뷢����Ϣ������?" << endl;
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
		else //friend =false ��������
		{
			cout << "���ǻ��������ѣ����Բ��ܷ�����Ϣ" << endl;
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
	cout << "���������뷢����Ϣ�Ķ�����" << endl;
	cout << "�ֻ���1��" << endl;
	cin >> phonenumber_receiver1;
	cout << "�ֻ���2��" << endl;
	cin >> phonenumber_receiver2;
	while (true)
	{
		if (d.BoolNotFriend(phonenumber, phonenumber_receiver1) && d.BoolNotFriend(phonenumber, phonenumber_receiver2) && d.BoolNotFriend(phonenumber_receiver1, phonenumber_receiver2)) //true��������
		{
			cout << "�������뷢�͵���Ϣ" << endl;
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
			cout << "���Ƿ��뷢����Ϣ��������?" << endl;
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
		else //friend =false ��������
		{
			cout << "���˲�����ĺ��ѣ����Բ��ܷ���Ⱥ�ĸ�����" << endl;
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
	case'1': //ĳλ����
	{
		switch (index2)
		{
		case'1': //�ֻ���
		{
			cout << "��������Ѱ�������¼���ֻ���" << endl;
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
				cout << "��û����Ӹ��ֻ���Ϊ����" << endl;
			}
			break;
		}
		case'2': //�ǳ�
		{
			cout << "��������Ѱ�������¼���ǳ�" << endl;
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
				cout << "��û����Ӹ��ǳ�Ϊ����" << endl;
			}
			break;
		}
		case'3': //�ؼ���
		{
			cout << "��������Ѱ�������¼�Ĺؼ���" << endl;
			cin >> input1;
			friend_yes = true;
			find=system.ReadMessageOneHighlight(phonenumber, input1);
			const vector<System::MessageOneData*>& message = system.GetMyMessageHighlightOne();
			break;
		}
		}
		if (!find && friend_yes)
		{
			cout << "û�������¼" << endl;
		}
		break;
	}
	case'2': //ĳ������
		switch (index2)
		{
		case'1': //�ֻ���
		{
			cout << "��������Ѱ�������¼���ֻ���" << endl;
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
				cout << "��û���������1λ�ֻ���Ϊ����" << endl;
			}
			break;
		}
		case'2': //�ǳ�
		{
			cout << "��������Ѱ�������¼���ǳ�" << endl;
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
				cout << "��û���������1λ�ǳ�Ϊ����" << endl;
			}
			break;
		}
		case'3': //�ؼ���
		{
			cout << "��������Ѱ�������¼�Ĺؼ���" << endl; //�ص���Ҫ���Լ��ھ���
			cin >> input1;
			find = true;
			friend_yes = false;
			int x = system.ReadMessageGroupHighlight(phonenumber, input1);
			const vector<System::MessageGroupData*>& message = system.GetMyMessageHighlightGroup();
			if (x == 2)
			{
				cout << "û�������¼" << endl;
			}
			else if (x == 0)
			{
				cout << "��������һλ�����Ѳ��Ǻ��ѹ�ϵ" << endl;
			}
			break;
		}
		}
		if (!find&& friend_yes)
		{
			cout << "û�������¼" << endl;
		}
		break;
	}
}
