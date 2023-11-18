#include "InterfaceUI.h"
#include "InterfaceUI.h"

#include<iostream>
using namespace std;

void InterfaceUI::DefaultChoice()
{
	cout << "没有该选项，请重新输入" << endl;
}
bool InterfaceUI::AgainService()
{
	string ans1;
	cout << "还需要其他服务嘛？" << endl;
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
	cout << "*****     1.添加好友  2.聊天  3.朋友圈  4.设置  5.退出     *****\n";
	cout << "#########################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入添加好友服务" << endl;
			AddFriendInterface(phonenumber);
		}
		case '2':
		{
			cout << "成功进入聊天服务" << endl;
			ChatInterface(phonenumber);
		}
		case '3':
		{
			cout << "成功进入朋友圈服务" << endl;
			PYQInterface(phonenumber);
		}
		case '4':
		{
			cout << "成功进入查看设置服务" << endl;
			SettingInterface(phonenumber);
		}
		case '5':
		{
			cout << "成功退出，欢迎下次再使用" << endl;
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
	cout << "*****     1.通过手机号码添加好友  2.通过昵称添加好友  3.查看朋友列表  4.查看好友请求  5.退出     *****\n";
	cout << "##########################################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入通过手机号码添加好友服务" << endl;
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
			cout << "成功进入通过昵称添加好友服务" << endl;
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
			cout << "成功进入查看好友申请服务" << endl;
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
			cout << "成功进入查看好友请求服务" << endl;
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
	cout << "*****     1.与好友聊天  2.与好友们聊天 3.退出     *****\n";
	cout << "##############################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入与好友聊天（单独）" << endl;
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
			cout << "成功进入与好友们聊天（最多三个人）" << endl;
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
	cout << "*****     1.留言  2.查看聊天记录  3.退出     *****\n";
	cout << "##############################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入留言服务" << endl;
			ChatPersonalOrGroup(phonenumber);
		}
		case '2':
		{
			cout << "成功进入查看聊天记录服务" << endl;
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
	cout << "*****     1.利用手机号查看聊天记录  2.利用昵称查看聊天记录  3.利用关键词查看聊天记录  4.退出     *****\n";
	cout << "####################################################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入利用手机号查看聊天记录服务" << endl;
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
			cout << "成功进入利用昵称查看聊天记录服务" << endl;
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
			cout << "成功进入利用关键词查看聊天记录服务" << endl;
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
	cout << "*****     1.查找某位朋友的聊天记录  2.查找多位朋友的聊天记录  3.退出     *****\n";
	cout << "#########################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2, ans3;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入查找某位朋友的聊天记录" << endl;
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
			cout << "成功进入查找多位朋友的聊天记录" << endl;
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
	cout << "*****     1.查看朋友圈  2.查看某个人的朋友圈  3.退出     *****\n";
	cout << "##########################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入查看朋友圈 " << endl;
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
			cout << "成功进入查看某位好友的朋友圈 " << endl;
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
	cout << "*****     1.查看自己的朋友圈  2.管理自己的朋友圈  3.退出     *****\n";
	cout << "##########################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case'1':
		{
			cout << "成功进入查看自己的朋友圈" << endl;
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
			cout << "成功进入管理自己的朋友圈" << endl;
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
	cout << "*****     1.查看自己的朋友圈  2.查看好友的朋友圈  3.退出     *****\n";
	cout << "##########################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
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
	cout << "*****     1.发布朋友圈  2.查看朋友圈  3.退出     *****\n";
	cout << "##########################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入发布朋友圈服务" << endl;
			//d.MomentPublish(phonenumber); //发布朋友圈
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
			cout << "成功进入查看朋友圈服务" << endl;
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
	cout << "*****     1.设置通过什么样的方式搜寻自己  2.设定通过好友请求的方式  3.更改自己的设置  4.退出     *****\n";
	cout << "#########################################################################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	//Account a;
	char choice;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入设置通过什么样的方式搜寻自己" << endl;
			AddFriendMethod(phonenumber);
		}
		case'2':
		{
			cout << "成功进入设定通过好友请求的方式" << endl;
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
			cout << "更改自己的设置" << endl;
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
	cout << "*****     1.能不能通过手机号码寻找  2.能不能通过用户名寻找  3.能不能通过手机号码和用户名寻找  4.退出     *****\n";
	cout << "#############################################################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
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
	cout << "*****     1.修改密码  2.修改昵称  3.修改朋友圈能不能被别人可见  4.退出     *****\n";
	cout << "##################################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
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
			//这里是个函数
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
			//这里是个函数
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
			//这里是个函数
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
	cout << "*****     1.注册账户  2.登陆账户  3.退出     *****\n";
	cout << "####################################################################\n\n";
	cout << "请选择您要进入的服务" << endl;
	char choice;
	string ans1, ans2;
	cout << "请选择您想要进入的服务" << endl;
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "成功进入注册账户服务" << endl;
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
			cout << "成功进入登录账户服务" << endl;
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
			cout << "成功退出，欢迎下次再使用" << endl;
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
