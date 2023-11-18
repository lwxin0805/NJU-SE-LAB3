#include "InterfaceUI.h"
#include "InterfaceUI.h"

#include<iostream>
using namespace std;

void InterfaceUI::DefaultChoice()
{
	cout << "û�и�ѡ�����������" << endl;
}
bool InterfaceUI::AgainService()
{
	string ans1;
	cout << "����Ҫ���������" << endl;
	cout << "yes/no" << endl;
	cin >> ans1;
	if (ans1 == "yes")
	{
		return true;
	}
	else
	{
		return false;
	}
}
void InterfaceUI::MainMenu(string& phonenumber)
{
	cout << "#########################################################################\n";
	cout << "*****     1.��Ӻ���  2.����  3.����Ȧ  4.����  5.�˳�     *****\n";
	cout << "#########################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ�������Ӻ��ѷ���" << endl;
			AddFriendInterface(phonenumber);
		}
		case '2':
		{
			cout << "�ɹ������������" << endl;
			ChatInterface(phonenumber);
		}
		case '3':
		{
			cout << "�ɹ���������Ȧ����" << endl;
			PYQInterface(phonenumber);
		}
		case '4':
		{
			cout << "�ɹ�����鿴���÷���" << endl;
			SettingInterface(phonenumber);
		}
		case '5':
		{
			cout << "�ɹ��˳�����ӭ�´���ʹ��" << endl;
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::AddFriendInterface(string& phonenumber)
{
	cout << "##########################################################################################\n";
	cout << "*****     1.ͨ���ֻ�������Ӻ���  2.ͨ���ǳ���Ӻ���  3.�鿴�����б�  4.�鿴��������  5.�˳�     *****\n";
	cout << "##########################################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ�����ͨ���ֻ�������Ӻ��ѷ���" << endl;
			char index = '1';
			//b.AddFriend(phonenumber, index);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ�����ͨ���ǳ���Ӻ��ѷ���" << endl;
			char index = '2';
			//b.AddFriend(phonenumber, index);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			cout << "�ɹ�����鿴�����������" << endl;
			//b.FriendList(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '4':
		{
			cout << "�ɹ�����鿴�����������" << endl;
			//b.AcceptDeleteFriend(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '5':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::ChatPersonalOrGroup(string& phonenumber)
{
	cout << "##############################################################################\n";
	cout << "*****     1.���������  2.����������� 3.�˳�     *****\n";
	cout << "##############################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ�������������죨������" << endl;
			//c.SendMessage(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case'2':
		{
			cout << "�ɹ���������������죨��������ˣ�" << endl;
			//c.SendMessagePeoples(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::ChatInterface(string& phonenumber)
{
	void SendMessage();
	void SendMessagePeoples();
	void CheckHistory();
	cout << "##############################################################################\n";
	cout << "*****     1.����  2.�鿴�����¼  3.�˳�     *****\n";
	cout << "##############################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ��������Է���" << endl;
			ChatPersonalOrGroup(phonenumber);
		}
		case '2':
		{
			cout << "�ɹ�����鿴�����¼����" << endl;
			ChatHistoryOneOrGroup(phonenumber);
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::ChatHistoryInterface(string& phonenumber, char& index1)
{
	cout << "####################################################################################################\n";
	cout << "*****     1.�����ֻ��Ų鿴�����¼  2.�����ǳƲ鿴�����¼  3.���ùؼ��ʲ鿴�����¼  4.�˳�     *****\n";
	cout << "####################################################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ����������ֻ��Ų鿴�����¼����" << endl;
			char index2 = '1';
			//c.CheckHistory(phonenumber, index1, index2);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ����������ǳƲ鿴�����¼����" << endl;
			char index2 = '2';
			//c.CheckHistory(phonenumber, index1, index2);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			cout << "�ɹ��������ùؼ��ʲ鿴�����¼����" << endl;
			char index2 = '3';
			//c.CheckHistory(phonenumber, index1, index2);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '4':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::ChatHistoryOneOrGroup(string& phonenumber)
{
	cout << "#########################################################################\n";
	cout << "*****     1.����ĳλ���ѵ������¼  2.���Ҷ�λ���ѵ������¼  3.�˳�     *****\n";
	cout << "#########################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ��������ĳλ���ѵ������¼" << endl;
			char index = '1';
			ChatHistoryInterface(phonenumber, index);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ�������Ҷ�λ���ѵ������¼" << endl;
			char index = '2';
			ChatHistoryInterface(phonenumber, index);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
			DefaultChoice();
		}
	}
}
void InterfaceUI::CheckPYQOneOrMany(string& phonenumber)
{
	cout << "##########################################################################\n";
	cout << "*****     1.�鿴����Ȧ  2.�鿴ĳ���˵�����Ȧ  3.�˳�     *****\n";
	cout << "##########################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ�����鿴����Ȧ " << endl;
			//d.MomentCheckAll(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ�����鿴ĳλ���ѵ�����Ȧ " << endl;
			//d.MomentOneFriend(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::CheckPYQOne(string& phonenumber)
{
	cout << "##########################################################################\n";
	cout << "*****     1.�鿴�Լ�������Ȧ  2.�����Լ�������Ȧ  3.�˳�     *****\n";
	cout << "##########################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case'1':
		{
			cout << "�ɹ�����鿴�Լ�������Ȧ" << endl;
			//d.MomentMe(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case'2':
		{
			cout << "�ɹ���������Լ�������Ȧ" << endl;
			//d.MomentSet(phonenumber);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}

		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::CheckPYQ(string& phonenumber)
{
	cout << "##########################################################################\n";
	cout << "*****     1.�鿴�Լ�������Ȧ  2.�鿴���ѵ�����Ȧ  3.�˳�     *****\n";
	cout << "##########################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			CheckPYQOne(phonenumber);
		}
		case '2':
		{
			CheckPYQOneOrMany(phonenumber);
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::PYQInterface(string& phonenumber)
{
	cout << "##########################################################\n";
	cout << "*****     1.��������Ȧ  2.�鿴����Ȧ  3.�˳�     *****\n";
	cout << "##########################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ����뷢������Ȧ����" << endl;
			//d.MomentPublish(phonenumber); //��������Ȧ
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ�����鿴����Ȧ����" << endl;
			CheckPYQ(phonenumber);
		}
		case '3':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::SettingInterface(string& phonenumber)
{
	cout << "#########################################################################################################################\n";
	cout << "*****     1.����ͨ��ʲô���ķ�ʽ��Ѱ�Լ�  2.�趨ͨ����������ķ�ʽ  3.�����Լ�������  4.�˳�     *****\n";
	cout << "#########################################################################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	//Account a;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ���������ͨ��ʲô���ķ�ʽ��Ѱ�Լ�" << endl;
			AddFriendMethod(phonenumber);
		}
		case'2':
		{
			cout << "�ɹ������趨ͨ����������ķ�ʽ" << endl;
			char x = '6';
			//a.Change(phonenumber, x);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case'3':
		{
			cout << "�����Լ�������" << endl;
			PersonalSetting(phonenumber);
		}
		case '4':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::AddFriendMethod(string& phonenumber)
{
	cout << "#############################################################################################################\n";
	cout << "*****     1.�ܲ���ͨ���ֻ�����Ѱ��  2.�ܲ���ͨ���û���Ѱ��  3.�ܲ���ͨ���ֻ�������û���Ѱ��  4.�˳�     *****\n";
	cout << "#############################################################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	//Account a;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{

			char x = '3';
			//a.Change(phonenumber, x);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}

		}
		case'2':
		{
			char x = '4';
			//a.Change(phonenumber, x);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case'3':
		{
			char x = '5';
			//a.Change(phonenumber, x);
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '4':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}
}
void InterfaceUI::PersonalSetting(string& phonenumber)
{
	cout << "##################################################################################\n";
	cout << "*****     1.�޸�����  2.�޸��ǳ�  3.�޸�����Ȧ�ܲ��ܱ����˿ɼ�  4.�˳�     *****\n";
	cout << "##################################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			char x = '2';
			//a.Change(phonenumber, x);
			//�����Ǹ�����
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}

		}
		case'2':
		{
			char x = '1';
			//a.Change(phonenumber, x);
			//�����Ǹ�����
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case'3':
		{
			char x = '7';
			//a.Change(phonenumber, x);
			//�����Ǹ�����
			if (AgainService()) //true;
			{
				MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '4':
		{
			MainMenu(phonenumber);
			break;
		}
		default:
		{
			DefaultChoice();
		}
		}
	}

}
void InterfaceUI::MainInterface()
{
	//Account chat;
	cout << "####################################################################\n";
	cout << "*****     1.ע���˻�  2.��½�˻�  3.�˳�     *****\n";
	cout << "####################################################################\n\n";
	cout << "��ѡ����Ҫ����ķ���" << endl;
	char choice;
	string ans1, ans2;
	cout << "��ѡ������Ҫ����ķ���" << endl;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "�ɹ�����ע���˻�����" << endl;
			//chat.Register();
			if (AgainService()) //true;
			{
				MainInterface();
			}
			else
			{
				break;
			}
		}
		case '2':
		{
			cout << "�ɹ������¼�˻�����" << endl;
			//string phonenumber = chat.Login();
			if (AgainService()) //true;
			{
				//MainMenu(phonenumber);
			}
			else
			{
				break;
			}
		}
		case '3':
		{
			cout << "�ɹ��˳�����ӭ�´���ʹ��" << endl;
			break;
		}
		default:
		{
			DefaultChoice();
			break;
		}
		}
	}
}
