#include "InterfaceUI.h"
#include "Account.h"
#include "Message.h"
#include "Moment.h"
#include "Friend.h"
#include "System.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<cctype> 
#include<string>
using namespace std;
bool Account::CheckPassword(string& password)
{
	bool has_upper = false, has_lower = false, has_digit = false;
	for (char c : password) //ѭ������newpassword
	{
		if (isupper(c))
		{
			has_upper = true;
		}
		else if (islower(c))
		{
			has_lower = true;
		}
		else if (isdigit(c))
		{
			has_digit = true;
		}
	}
	if (has_upper && has_lower && has_digit) //ȫ��true
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Account::Register() 
{
	System system;
	system.ReadUserInfo();
	string phonenumber_re, username_re, password_re, question_re = " ";
	bool phonefind_re = true, usernamefind_re = true, accept_re = true; //�ֻ��ҵ����ǳ��ҵ���Ĭ��ͨ��
	cout << "�����������ֻ�����" << endl;
	cout << "ע�� �ֻ�����Ҫ11λ �������ֲ���Ϊ0" << endl;
	while (true)
	{
		cin >> phonenumber_re;
		bool not_register = false;
		if (phonenumber_re.size() != 11 || phonenumber_re[0] == '0')
		{
			cout << "�ֻ���������������������" << endl;
			continue; // �ص�whileѭ��
		}
		//�鿴�ļ�
		const vector<System::UserData*>& data = system.GetMyData();
		for (const auto& user : data)
		{
			if (user->phonenumber == phonenumber_re) //���û�ҵ��򷵻� string::npos
			{
				cout << "���ֻ����ѱ�ע�ᣬ����������" << endl;
				not_register = true;
				continue; //�ص�whileѭ��
			}
		}
		if (not_register==false) //�����һֱѭ��ֱ��������һ��û��ע������ֻ��ŲŻ�break
		{
			break;
		}
	}
	//�ֻ�����û��ע�ᣬ���Լ���ע��
	string doublepassword; //������֤
	cout << "��������������" << endl;
	cout << "ע�� ����Ҫ����8λ�����������Сд��ĸ������" << endl;
	bool is_firstpassword = false,is_secondpassword=false; //�������������Ϊ������
	while (true)
	{
		cin >> password_re;
		if (password_re.size() < 8)
		{
			cout << "���볤�Ȳ��㣬����������" << endl;
			continue;
		}
		if (CheckPassword(password_re)) //������ȷ
		{
			is_firstpassword = true; //Ȼ���������
			while (true)
			{
				cout << "�������������" << endl;
				cin >> doublepassword;
				if (password_re != doublepassword)
				{
					cout << "���������������һ����������벻һ��" << endl;
					continue;
				}
				else
				{
					cout << "�������óɹ���" << endl;
					is_firstpassword = true;
					is_secondpassword = true;
					break;
				}
			}
		}
		else
		{
			cout << "���ڰ�ȫ���⣬������������һ���µ�����" << endl;
			continue;
		}
		if (is_firstpassword && is_secondpassword)
		{
			break; 
		}
	}
	cout << "�����������õ��û���" << endl;
	cin >> username_re;
	int code;
	while (true)
	{
		srand((unsigned)time(NULL)); //����ʱ�����ӣ���֤ÿ���������ͬ
		int rand_num = rand() % 9000 + 1000; //����1000~9999֮�������
		cout << "������λ�������֤�룺" << rand_num << endl;
		cout << "��������������֤��" << endl;
		cin >> code;
		if (rand_num == code)
		{
			cout << "ע��ɹ���" << endl;
			break;
		}
		else
		{
			cout << "��֤�벻һ��" << endl;
			continue;
		}
	}
	System::UserData userData;
	userData.phonenumber = phonenumber_re;
	userData.username = username_re;
	userData.password = password_re;
	userData.phonefind = 1;
	userData.usernamefind = 1;
	userData.moment = 1;
	userData.accept = 1;
	userData.question = question_re;
	system.WriteUserInfo(userData);
}
string Account::Login()
{
	System system;
	system.ReadUserInfo();
	InterfaceUI interface;
	string phonenumber_re,password_re,password_re2; //�����Phonenumber������ֵ��
	cout << "��ӭ�����û���¼����" << endl;
	cout << "���������ֻ��ţ�" << endl;
	bool vertification = false,phone_vertification=false;
	while (true)
	{
		cin >> phonenumber_re;
		cout << "�������������룺" << endl;
		cin >> password_re;
		const vector<System::UserData*>& data = system.GetMyData();
		for (const auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				phone_vertification = true;
				if (password_re == user->password)
				{
					cout << "��½�ɹ���" << endl;
					vertification = true;
					interface.MainMenu(phonenumber_re);
					break; //break for��
				}
				else
				{
					cout << "�����������������" << endl;
					while (true)
					{
						cin >> password_re2;
						if (user->password == password_re2)
						{
							cout << "��½�ɹ���" << endl;
							vertification = true;
							interface.MainMenu(phonenumber_re);
							break;
						}
						else
						{
							cout << "�����д�������������" << endl;
							continue;
						}
					}
				}
			}
			if (vertification)
			{
				break;
			}
		}
		if (!phone_vertification)
		{
			cout << "�ֻ�����δ��ע��" << endl;
			cout << "�������������ֻ��ţ�" << endl;
			continue;
		}
	}
	return phonenumber_re;
}
void Account::Rewrite()
{
	System system;
	system.ReadUserInfo();
	const vector<System::UserData*>& data = system.GetMyData();
	ofstream clear_file("UserInfo.txt");
	clear_file.close();
	for (const auto& u : data)
	{
		system.WriteUserInfo(*u);;
	}
}
void Account::Change(string& phonenumber_re, char& index) //�������ѡ���Ǹ���ʲô
{
	System system;
	system.ReadUserInfo();
	const vector<System::UserData*>& data = system.GetMyData();
	string input, doublepassword,question_str;
	switch (index)
	{
	case '1': //�޸�username
	{
		cout << "����������ĵ��û�����" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				cout << "�û���������ϣ�" << endl;
				user->username = input;
				Rewrite();
				break;
			}
		}
		break;
	}
	case '2': //�޸�password
	{

		cout << "������������ĵ����룺" << endl;
		cout << "ע�� ����Ҫ����8λ�����������Сд��ĸ������" << endl;
		bool is_firstpassword = false, is_secondpassword = false; //�������������Ϊ������
		while (true)
		{
			cin >> input;
			if (input.size() < 8)
			{
				cout << "���볤�Ȳ��㣬����������" << endl;
				continue;
			}
			if (CheckPassword(input)) //������ȷ
			{
				is_firstpassword = true; //Ȼ���������
				while (true)
				{
					cout << "�������������" << endl;
					cin >> doublepassword;
					if (input != doublepassword)
					{
						cout << "���������������һ����������벻һ��" << endl;
						continue;
					}
					else
					{
						is_secondpassword = true;
						break;
					}
				}
			}
			else
			{
				cout << "���ڰ�ȫ���⣬������������һ���µ�����" << endl;
				continue;
			}
			if (is_firstpassword && is_secondpassword)
			{
				break;
			}
		}
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				cout << "������³ɹ���" << endl;
				user->password = input;
				/*ofstream clear_file("UserInfo.txt");
				clear_file.close();
				for (const auto& u : data)
				{
					system.WriteUserInfo(*u);;
				}*/
				Rewrite();
				break;
			}
		}
		break;
	}
	case '3': //�޸�phonefind
	{
		cout << "�Ƿ�����ñ���ͨ���ֻ���Ѱ������" << endl;
		cout << "yes = �ñ�����ͨ���ֻ���Ѱ���� / no = �ñ��˲���ͨ���ֻ���Ѱ����" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "�����û���ʹ���ֻ���Ѱ������" << endl;
					user->phonefind = 1;
				}
				else if (input == "no")
				{
					cout << "�����û�����ʹ���ֻ���Ѱ������" << endl;
					user->phonefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '4': //�޸�userfind
	{
		cout << "�Ƿ�����ñ���ͨ���ǳ�Ѱ������" << endl;
		cout << "yes = �ñ�����ͨ���ǳ�Ѱ���� / no = �ñ��˲���ͨ���ǳ�Ѱ����" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "�����û���ʹ���ǳ�Ѱ����" << endl;
					user->usernamefind = 1;
				}
				else if (input == "no")
				{
					cout << "�����û�����ʹ���ǳ�Ѱ������" << endl;
					user->usernamefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '5': //�޸�phonefind&usernamefind
	{
		cout << "�Ƿ�����ñ���ͨ���ֻ���Ѱ������" << endl;
		cout << "�Ƿ�����ñ���ͨ���ǳ�Ѱ������" << endl;
		cout << "yes = �ñ�����ͨ���ֻ��ź��ǳ�Ѱ���� / no = �ñ��˲���ͨ���ֻ��ź��ǳ�Ѱ����" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "�����û���ʹ���ֻ��ź��ǳ�Ѱ����" << endl;
					user->phonefind = 1;
					user->usernamefind = 1;
				}
				else if (input == "no")
				{
					cout << "�����û�����ʹ���ֻ��ź��ǳ�Ѱ������" << endl;
					user->phonefind = 0;
					user->usernamefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '6': //�޸ĺ���
	{
		cout << "�Ƿ�����ñ�������ش��������ֱ�Ӽ�������" << endl;
		cout << "yes = Ĭ���Զ�ͨ�� / no = ��ش����������" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "���Ľ��������˲���Ҫ�ش�����������ܼ�����" << endl;
					cout << "��֮ǰ���õ����⽫�Զ�ɾ��" << endl;
					question_str = " ";
					user->accept = 1;
					user->question = question_str;
				}
				else if (input == "no")
				{
					cout << "���Ľ�����������Ҫ�ش�����������ܼ�����" << endl;
					cout << "���������������" << endl;
					cin >> question_str;
					user->accept = 0;
					user->question = question_str;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '7': //����Ȧ��������?
	{
		cout << "����Ȧ�Ա��˿ɼ���" << endl;
		cout << "yes = �Ա��˿ɼ� / no = ���Լ��ɼ�" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes") //�Ա��˿ɼ�����1
				{
					cout << "���Ľ������������Ѷ��ܿ����������Ȧ��" << endl;
					user->moment = 1;
				}
				else if (input == "no")
				{
					cout << "���Ľ������������Ȧ�����ѹر���" << endl;
					user->moment = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	default:
	{
		cout << "û�и�ѡ������˳�" << endl;
		return;
	}
	}
}