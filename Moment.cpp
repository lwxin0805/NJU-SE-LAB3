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
void Moment::MomentPublish(string& phonenumber)//发布朋友圈
{
	string input,ans;
	System system;
	system.ReadMoment();
	const vector<System::MomentData*>& data = system.GetMyMoment();
	while (true)
	{
		cout << "输入您想发布的朋友圈（仅文字）" << endl;
		cin >> input;
		System::MomentData momentData;
		momentData.index = system.FindNumber(); //他每次都递增所以我要怎样找?
		momentData.phonenumber = phonenumber;
		momentData.content = input;
		momentData.visible = 1; //1可以被看到 ， 0 不可以被看到
		momentData.likecount = 0;
		system.WriteMoment(momentData);
		cout << "您是否还想发送朋友圈吗?" << endl;
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
	//要是朋友才可以看到别人的朋友圈
	for (const auto& moment : data)
	{
		if (a.BoolNotFriend(phonenumber, moment->phonenumber) && CheckIfMomentSeen(moment->phonenumber)) //为什么进不去...
		{
			if (moment->visible == 1)
			{
				got = true;
				cout << moment->phonenumber << "：" << moment->content << endl;
				cout << "点赞：" << moment->likecount << endl;
				cout << "请问您是否想点赞？" << endl;
				cout << "yes/no" << endl;
				cin >> ans;
				if (ans == "yes")
				{
					MomentLike(moment->index);
				}
				cout << "留言：" << endl;
				for (const auto& comments : comment)
				{
					if (moment->index == comments->index && comments->visible == 1) //留言1才可以被查看
					{
						cout << comments->phonenumber << ":" << comments->content << endl;
					}
				}
				cout << "请问您是否想评论？" << endl;
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
		cout << "没有朋友圈" << endl;
	}
}
bool Moment::MomentCheck(string& phonenumber,char &index) //查看朋友圈 (输入手机号)
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
			//用index
			if (phonenumber == moment->phonenumber )
			{
				got = true;
				cout << moment->phonenumber << "：" << moment->content << endl;
				cout << "点赞：" << moment->likecount << endl;
				cout << "留言：" << endl;
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
			//用index
			if (phonenumber == moment->phonenumber && moment->visible == 1)
			{
				got = true;
				cout << moment->phonenumber << "：" << moment->content << endl;
				cout << "点赞：" << moment->likecount << endl;
				cout << "留言：" << endl;
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
		cout << "没有朋友圈" << endl;
	}
}
void Moment::MomentOneFriend(string& phonenumber)
{
	string input,ans;
	while (true)
	{
		char index = '2';
		cout << "您想查看哪位朋友的朋友圈？" << endl;
		cin >> input;
		if (a.BoolNotFriend(phonenumber, input) && CheckIfMomentSeen(input))//先查看是不是好友? 是朋友才能看朋友圈
		{
			if (!MomentCheck(input,index))
			{
				cout << "没有朋友圈" << endl;
			}
		}
		else if (!a.BoolNotFriend(phonenumber, input))
		{
			cout << "不是好友不能查看他的朋友圈" << endl;
		}
		else if (a.BoolNotFriend(phonenumber, input) && CheckIfMomentSeen(input) == false)
		{
			cout << "他的朋友圈不对你公开" << endl;
		}
		cout << "您还想查看某位朋友的朋友圈吗？" << endl;
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
void Moment::MomentComment(string & phonenumber,int &index) //评论(Comment.txt)
{
	System system;
	string comment;
	cout << "输入您想对这条朋友圈的留言" << endl;
	cin >> comment;
	cout << "评论成功！" << endl;
	System::CommentData comment_input;
	comment_input.index = index;
	comment_input.phonenumber = phonenumber;
	comment_input.content = comment;
	comment_input.visible = 1; //1才可以看
	system.WriteComment(comment_input);
}
void Moment::MomentSet(string& phonenumber) //查看每一个评论
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
			cout << moment->phonenumber << "：" << moment->content << endl;
			cout << "点赞：" << moment->likecount << endl;
			cout << "留言：" << endl;
			for (const auto& comments : comment)
			{
				if (moment->index == comments->index && comments->visible == 1)
				{
					cout << comments->phonenumber << ":" << comments->content << endl;
					cout << "是否要删掉这评论？" << endl;
					cout << "yes/no" << endl;
					cin >> ans1;
					if (ans1 == "yes")
					{
						comments->visible = 0;//被删除
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
			cout << "这条朋友圈要不要设置仅自己可见？" << endl;
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
		if (index == moment->index) //这个就是我要的
		{
			int x = moment->likecount +1;
			moment->likecount = x;
			cout << "点赞成功！" << endl;
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