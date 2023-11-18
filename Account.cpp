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
	for (char c : password) //循环整个newpassword
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
	if (has_upper && has_lower && has_digit) //全部true
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
	bool phonefind_re = true, usernamefind_re = true, accept_re = true; //手机找到，昵称找到，默认通过
	cout << "请输入您的手机号码" << endl;
	cout << "注意 手机号码要11位 且首数字不能为0" << endl;
	while (true)
	{
		cin >> phonenumber_re;
		bool not_register = false;
		if (phonenumber_re.size() != 11 || phonenumber_re[0] == '0')
		{
			cout << "手机号码有误，请您重新输入" << endl;
			continue; // 回到while循环
		}
		//查看文件
		const vector<System::UserData*>& data = system.GetMyData();
		for (const auto& user : data)
		{
			if (user->phonenumber == phonenumber_re) //如果没找到则返回 string::npos
			{
				cout << "该手机号已被注册，请重新输入" << endl;
				not_register = true;
				continue; //回到while循环
			}
		}
		if (not_register==false) //这里会一直循环直到输入了一个没有注册过的手机号才会break
		{
			break;
		}
	}
	//手机号码没被注册，可以继续注册
	string doublepassword; //二次验证
	cout << "请输入您的密码" << endl;
	cout << "注意 密码要超过8位，必须包含大小写字母和数字" << endl;
	bool is_firstpassword = false,is_secondpassword=false; //密码可以先设置为不可以
	while (true)
	{
		cin >> password_re;
		if (password_re.size() < 8)
		{
			cout << "密码长度不足，请重新输入" << endl;
			continue;
		}
		if (CheckPassword(password_re)) //密码正确
		{
			is_firstpassword = true; //然后这里可以
			while (true)
			{
				cout << "请二次输入密码" << endl;
				cin >> doublepassword;
				if (password_re != doublepassword)
				{
					cout << "二次输入密码跟第一次输入的密码不一样" << endl;
					continue;
				}
				else
				{
					cout << "密码设置成功！" << endl;
					is_firstpassword = true;
					is_secondpassword = true;
					break;
				}
			}
		}
		else
		{
			cout << "由于安全问题，请您重新设置一个新的密码" << endl;
			continue;
		}
		if (is_firstpassword && is_secondpassword)
		{
			break; 
		}
	}
	cout << "输入您想设置的用户名" << endl;
	cin >> username_re;
	int code;
	while (true)
	{
		srand((unsigned)time(NULL)); //设置时间种子，保证每次随机数不同
		int rand_num = rand() % 9000 + 1000; //生成1000~9999之间的数字
		cout << "这是四位随机的验证码：" << rand_num << endl;
		cout << "请您重新输入验证码" << endl;
		cin >> code;
		if (rand_num == code)
		{
			cout << "注册成功！" << endl;
			break;
		}
		else
		{
			cout << "验证码不一致" << endl;
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
	string phonenumber_re,password_re,password_re2; //这里的Phonenumber是来赋值的
	cout << "欢迎来到用户登录界面" << endl;
	cout << "输入您的手机号：" << endl;
	bool vertification = false,phone_vertification=false;
	while (true)
	{
		cin >> phonenumber_re;
		cout << "请输入您的密码：" << endl;
		cin >> password_re;
		const vector<System::UserData*>& data = system.GetMyData();
		for (const auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				phone_vertification = true;
				if (password_re == user->password)
				{
					cout << "登陆成功！" << endl;
					vertification = true;
					interface.MainMenu(phonenumber_re);
					break; //break for的
				}
				else
				{
					cout << "密码错误，请重新输入" << endl;
					while (true)
					{
						cin >> password_re2;
						if (user->password == password_re2)
						{
							cout << "登陆成功！" << endl;
							vertification = true;
							interface.MainMenu(phonenumber_re);
							break;
						}
						else
						{
							cout << "密码有错误，请重新输入" << endl;
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
			cout << "手机号码未被注册" << endl;
			cout << "请您重新输入手机号：" << endl;
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
void Account::Change(string& phonenumber_re, char& index) //这个可以选择是更改什么
{
	System system;
	system.ReadUserInfo();
	const vector<System::UserData*>& data = system.GetMyData();
	string input, doublepassword,question_str;
	switch (index)
	{
	case '1': //修改username
	{
		cout << "输入您想更改的用户名：" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				cout << "用户名更新完毕！" << endl;
				user->username = input;
				Rewrite();
				break;
			}
		}
		break;
	}
	case '2': //修改password
	{

		cout << "请输入您想更改的密码：" << endl;
		cout << "注意 密码要超过8位，必须包含大小写字母和数字" << endl;
		bool is_firstpassword = false, is_secondpassword = false; //密码可以先设置为不可以
		while (true)
		{
			cin >> input;
			if (input.size() < 8)
			{
				cout << "密码长度不足，请重新输入" << endl;
				continue;
			}
			if (CheckPassword(input)) //密码正确
			{
				is_firstpassword = true; //然后这里可以
				while (true)
				{
					cout << "请二次输入密码" << endl;
					cin >> doublepassword;
					if (input != doublepassword)
					{
						cout << "二次输入密码跟第一次输入的密码不一样" << endl;
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
				cout << "由于安全问题，请您重新设置一个新的密码" << endl;
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
				cout << "密码更新成功！" << endl;
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
	case '3': //修改phonefind
	{
		cout << "是否更改让别人通过手机号寻找您？" << endl;
		cout << "yes = 让别人能通过手机号寻找您 / no = 让别人不能通过手机号寻找您" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "其他用户能使用手机号寻找您！" << endl;
					user->phonefind = 1;
				}
				else if (input == "no")
				{
					cout << "其他用户不能使用手机号寻找您！" << endl;
					user->phonefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '4': //修改userfind
	{
		cout << "是否更改让别人通过昵称寻找您？" << endl;
		cout << "yes = 让别人能通过昵称寻找您 / no = 让别人不能通过昵称寻找您" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "其他用户能使用昵称寻找您" << endl;
					user->usernamefind = 1;
				}
				else if (input == "no")
				{
					cout << "其他用户不能使用昵称寻找您！" << endl;
					user->usernamefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '5': //修改phonefind&usernamefind
	{
		cout << "是否更改让别人通过手机号寻找您？" << endl;
		cout << "是否更改让别人通过昵称寻找您？" << endl;
		cout << "yes = 让别人能通过手机号和昵称寻找您 / no = 让别人不能通过手机号和昵称寻找您" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "其他用户能使用手机号和昵称寻找您" << endl;
					user->phonefind = 1;
					user->usernamefind = 1;
				}
				else if (input == "no")
				{
					cout << "其他用户不能使用手机号和昵称寻找您！" << endl;
					user->phonefind = 0;
					user->usernamefind = 0;
				}
				Rewrite();
				break;
			}
		}
		break;
	}
	case '6': //修改好友
	{
		cout << "是否更改让别人无需回答问题就能直接加上您？" << endl;
		cout << "yes = 默认自动通过 / no = 需回答您设的问题" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes")
				{
					cout << "更改结束！别人不需要回答您的问题才能加上您" << endl;
					cout << "您之前设置的问题将自动删除" << endl;
					question_str = " ";
					user->accept = 1;
					user->question = question_str;
				}
				else if (input == "no")
				{
					cout << "更改结束！别人需要回答您的问题才能加上您" << endl;
					cout << "输入您想设的问题" << endl;
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
	case '7': //朋友圈公不公开?
	{
		cout << "朋友圈对别人可见吗？" << endl;
		cout << "yes = 对别人可见 / no = 仅自己可见" << endl;
		cin >> input;
		for (auto& user : data)
		{
			if (phonenumber_re == user->phonenumber)
			{
				if (input == "yes") //对别人可见就是1
				{
					cout << "更改结束！所有朋友都能看到你的朋友圈啦" << endl;
					user->moment = 1;
				}
				else if (input == "no")
				{
					cout << "更改结束！你的朋友圈对朋友关闭啦" << endl;
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
		cout << "没有该选项，即将退出" << endl;
		return;
	}
	}
}