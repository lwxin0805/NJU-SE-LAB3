#include "InterfaceUI.h"
#include "Account.h"
#include "Message.h"
#include "Moment.h"
#include "Friend.h"
#include "System.h"
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;
Friend a;
Account b;

bool Moment::CheckIfMomentSeen(string& phonenumber)
{
	System system;
	system.ReadUserInfo();
	const vector<System::UserData*>& data = system.GetMyData();
	for (const auto& user : data)
	{
		if (user->phonenumber == phonenumber && user->moment == 1)
		{
			return true;
		}
	}
	return false;
}
void Moment::MomentPublish(string& phonenumber)//��������Ȧ
{
	string input,ans;
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	while (true)
	{
		cout << "�������뷢��������Ȧ�������֣�" << endl;
		cin >> input;
		System::MomentData momentData;
		momentData.index = system.FindNumber(); //��ÿ�ζ�����������Ҫ������?
		momentData.phonenumber = phonenumber;
		momentData.content = input;
		momentData.visible = 1; //1���Ա����� �� 0 �����Ա�����
		momentData.likecount = 0;
		system.WriteMoment(momentData);
		cout << "���Ƿ��뷢������Ȧ��?" << endl;
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
}
void Moment::MomentCheckAll(string& phonenumber)
{
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	system.ReadComment();
	const vector<System::CommentData*>& comment = system.GetMyComment();
	string ans,ans1;
	bool got = false;
	//Ҫ�����Ѳſ��Կ������˵�����Ȧ
	for (const auto& moment : data)
	{
		if (a.BoolNotFriend(phonenumber, moment->phonenumber) && CheckIfMomentSeen(moment->phonenumber)) //Ϊʲô����ȥ...
		{
			if (moment->visible == 1)
			{
				got = true;
				cout << moment->phonenumber << "��" << moment->content << endl;
				cout << "���ޣ�" << moment->likecount << endl;
				cout << "�������Ƿ�����ޣ�" << endl;
				cout << "yes/no" << endl;
				cin >> ans;
				if (ans == "yes")
				{
					MomentLike(moment->index);
				}
				cout << "���ԣ�" << endl;
				for (const auto& comments : comment)
				{
					if (moment->index == comments->index && comments->visible == 1) //����1�ſ��Ա��鿴
					{
						cout << comments->phonenumber << ":" << comments->content << endl;
					}
				}
				cout << "�������Ƿ������ۣ�" << endl;
				cout << "yes/no" << endl;
				cin >> ans1;
				if (ans1 == "yes")
				{
					MomentComment(phonenumber, moment->index);
				}
			}
		}
	}
	if (!got)
	{
		cout << "û������Ȧ" << endl;
	}
}
bool Moment::MomentCheck(string& phonenumber,char &index) //�鿴����Ȧ (�����ֻ���)
{
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	system.ReadComment();
	const vector<System::CommentData*>& comment = system.GetMyComment();
	bool got = false;
	switch (index)
	{
	case'1':
	{
		for (const auto& moment : data)
		{
			//��index
			if (phonenumber == moment->phonenumber )
			{
				got = true;
				cout << moment->phonenumber << "��" << moment->content << endl;
				cout << "���ޣ�" << moment->likecount << endl;
				cout << "���ԣ�" << endl;
				for (const auto& comments : comment)
				{
					if (moment->index == comments->index && comments->visible == 1)
					{
						cout << comments->phonenumber << ":" << comments->content << endl;
					}
				}
			}
		}
	}
	case '2':
	{
		for (const auto& moment : data)
		{
			//��index
			if (phonenumber == moment->phonenumber && moment->visible == 1)
			{
				got = true;
				cout << moment->phonenumber << "��" << moment->content << endl;
				cout << "���ޣ�" << moment->likecount << endl;
				cout << "���ԣ�" << endl;
				for (const auto& comments : comment)
				{
					if (moment->index == comments->index && comments->visible == 1)
					{
						cout << comments->phonenumber << ":" << comments->content << endl;
					}
				}
			}
		}
	}
	}
	if (got)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Moment::MomentMe(string& phonenumber)
{
	char index = '1';
	if (!MomentCheck(phonenumber,index))
	{
		cout << "û������Ȧ" << endl;
	}
}
void Moment::MomentOneFriend(string& phonenumber)
{
	string input,ans;
	while (true)
	{
		char index = '2';
		cout << "����鿴��λ���ѵ�����Ȧ��" << endl;
		cin >> input;
		if (a.BoolNotFriend(phonenumber, input) && CheckIfMomentSeen(input))//�Ȳ鿴�ǲ��Ǻ���? �����Ѳ��ܿ�����Ȧ
		{
			if (!MomentCheck(input,index))
			{
				cout << "û������Ȧ" << endl;
			}
		}
		else if (!a.BoolNotFriend(phonenumber, input))
		{
			cout << "���Ǻ��Ѳ��ܲ鿴��������Ȧ" << endl;
		}
		else if (a.BoolNotFriend(phonenumber, input) && CheckIfMomentSeen(input) == false)
		{
			cout << "��������Ȧ�����㹫��" << endl;
		}
		cout << "������鿴ĳλ���ѵ�����Ȧ��" << endl;
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
}
void Moment::MomentComment(string & phonenumber,int &index) //����(Comment.txt)
{
	System system;
	string comment;
	cout << "�����������������Ȧ������" << endl;
	cin >> comment;
	cout << "���۳ɹ���" << endl;
	System::CommentData comment_input;
	comment_input.index = index;
	comment_input.phonenumber = phonenumber;
	comment_input.content = comment;
	comment_input.visible = 1; //1�ſ��Կ�
	system.WriteComment(comment_input);
}
void Moment::MomentSet(string& phonenumber) //�鿴ÿһ������
{
	string ans1;
	bool change = false,change1=false;
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	system.ReadComment();
	const vector<System::CommentData*>& comment = system.GetMyComment();
	for (const auto& moment : data)
	{
		if (phonenumber == moment->phonenumber)
		{
			cout << moment->phonenumber << "��" << moment->content << endl;
			cout << "���ޣ�" << moment->likecount << endl;
			cout << "���ԣ�" << endl;
			for (const auto& comments : comment)
			{
				if (moment->index == comments->index && comments->visible == 1)
				{
					cout << comments->phonenumber << ":" << comments->content << endl;
					cout << "�Ƿ�Ҫɾ�������ۣ�" << endl;
					cout << "yes/no" << endl;
					cin >> ans1;
					if (ans1 == "yes")
					{
						comments->visible = 0;//��ɾ��
						change = true;
					}
					if (change)
					{
						ofstream clear_file("Comment.txt");
						clear_file.close();
						for (const auto& u : comment)
						{
							system.WriteComment(*u);
						}
					}
				}
			}
			cout << "��������ȦҪ��Ҫ���ý��Լ��ɼ���" << endl;
			cout << "yes/no" << endl;
			cin >> ans1;
			if (ans1 == "yes")
			{
				moment->visible = 0;
				change1 = true;
			}
			if (change1)
			{
				ofstream clear_file("Moment.txt");
				clear_file.close();
				for (const auto& u : data)
				{
					system.WriteMoment(*u);
				}
			}
		}
	}
}
void Moment::MomentLike(int& index)
{
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	for (const auto& moment : data)
	{
		if (index == moment->index) //���������Ҫ��
		{
			int x = moment->likecount +1;
			moment->likecount = x;
			cout << "���޳ɹ���" << endl;
			ofstream clear_file("Moment.txt");
			clear_file.close();
			for (const auto& u : data)
			{
				system.WriteMoment(*u);
			}
			break;
		}
	}
}