#include "InterfaceUI.h"
#include "Account.h"
#include "Message.h"
#include "Moment.h"
#include "Friend.h"
#include "System.h"
#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
using namespace std;
Friend z;

void System:: ReadUserInfo()
{
	ifstream check_file("UserInfo.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber, username, password, question;
		int phonefind, usernamefind, accept, moment;
		iss >> phonenumber >> username >> password >> phonefind >> usernamefind >>  moment>>accept >> question ;
		UserData* userData = new UserData{ phonenumber, username, password, phonefind, usernamefind,  moment , accept, question  };
		MyData.push_back(userData);
	}
}
const vector<System::UserData*>& System::GetMyData() const
{
	return MyData;
}
void System::WriteUserInfo(const UserData& userData)
{
	ofstream user_file("UserInfo.txt", ios::app);
	if (user_file.is_open())
	{
		user_file << userData.phonenumber << " " << userData.username << " "
				<< userData.password << " " << userData.phonefind << " "
				<< userData.usernamefind << " " << userData.moment <<" " << userData.accept << " "
				<< userData.question << endl;
	}
	user_file.close();
}

void System::ReadFriendList()
{
	ifstream check_file("FriendList.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber_sender,username_sender,phonenumber_receiver,username_receiver, question, answer;
		int friend_add;
		iss >> phonenumber_sender>>username_sender >> phonenumber_receiver >> username_receiver >> friend_add >> question >> answer;
		FriendData* friendData = new FriendData{ phonenumber_sender , username_sender , phonenumber_receiver, username_receiver ,friend_add, question ,answer };
		MyFriend.push_back(friendData);
	}
}
const vector<System::FriendData*>& System::GetMyFriend() const
{
	return MyFriend;
}
void System::WriteFriendList(const FriendData& friendData)
{
	ofstream friend_file("FriendList.txt", ios::app);
	if (friend_file.is_open())
	{
		friend_file << friendData.phonenumber_sender << " " << friendData.username_sender << " " << friendData.phonenumber_receiver << " " << friendData.username_receiver << " " << friendData.friend_add << " " << friendData.question << " " << friendData.answer<<endl;
	}
	friend_file.close();
}

void System::ReadMessageOne()
{
	ifstream check_file("MessageOne.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber_sender, username_sender, phonenumber_receiver, username_receiver, content;
		iss >> phonenumber_sender >> username_sender >> phonenumber_receiver >> username_receiver >> content;
		MessageOneData* messageOne = new MessageOneData{ phonenumber_sender , username_sender , phonenumber_receiver, username_receiver ,content };
		MyMessageOne.push_back(messageOne);
	}
}
const vector<System::MessageOneData*>& System::GetMyMessageOne() const
{
	return MyMessageOne;
}
void System::WriteMessageOne(const MessageOneData& messageOne)
{
	ofstream message_file("MessageOne.txt", ios::app);
	if (message_file.is_open())
	{
		message_file << messageOne.phonenumber_sender << " " << messageOne.username_sender << " " << messageOne.phonenumber_receiver << " " << messageOne.username_receiver << " " << messageOne.content <<  endl;
	}
	message_file.close();
}

void System::ReadMessageGroup()
{
	ifstream check_file("MessageGroup.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber_sender, username_sender, phonenumber_receiverA, username_receiverA, phonenumber_receiverB, username_receiverB, content;
		iss >> phonenumber_sender >> username_sender >> phonenumber_receiverA >> username_receiverA >> phonenumber_receiverB >> username_receiverB >> content;
		MessageGroupData* messageGroup = new MessageGroupData{ phonenumber_sender , username_sender , phonenumber_receiverA , username_receiverA , phonenumber_receiverB , username_receiverB ,content };
		MyMessageGroup.push_back(messageGroup);
	}
}
const vector<System::MessageGroupData*>& System::GetMyMessageGroup() const
{
	return MyMessageGroup;
}
void System::WriteMessageGroup(const MessageGroupData& messageGroup)
{
	ofstream message_file("MessageGroup.txt", ios::app);
	if (message_file.is_open())
	{
		message_file << messageGroup.phonenumber_sender << " " << messageGroup.username_sender << " " << messageGroup.phonenumber_receiverA << " " << messageGroup.username_receiverA << " " << messageGroup.phonenumber_receiverB  << " " << messageGroup.username_receiverB <<" " << messageGroup.content << endl;
	}
	message_file.close();
}

bool System::ReadMessageOneHighlight(string& phonenumber_re, string& highlight) //他跟sender要是朋友?
{
	bool got = false;
	ifstream check_file("MessageOne.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber_sender, username_sender ,phonenumber_receiver,username_receiver, chat;
		iss >> phonenumber_sender >> username_sender >> phonenumber_receiver >> username_receiver >>  chat;
		MessageOneData* chatHighlight = new MessageOneData{ phonenumber_sender , username_sender,phonenumber_receiver,username_receiver, chat };
		if ((phonenumber_re == phonenumber_sender || phonenumber_re == phonenumber_receiver) && z.BoolNotFriend(phonenumber_sender,phonenumber_receiver))
		{
			if (laji.find(highlight) != string::npos)
			{
				cout << chatHighlight->phonenumber_sender << ":" << chatHighlight->content << endl;
				got = true;
				MyMessageHighlightOne.push_back(chatHighlight);
			}
		}
	}
	check_file.close();
	if (got)
	{
		return true;
	}
	else
	{
		return false;
	}
}
const vector<System::MessageOneData*>& System::GetMyMessageHighlightOne() const
{
	return MyMessageHighlightOne;
}

int System::ReadMessageGroupHighlight(string& phonenumber_re, string& highlight)
{
	int x = 0; //其中一个不是朋友
	bool got = false;
	ifstream check_file("MessageGroup.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		string phonenumber_sender,username_sender,phonenumber_receiverA,username_receiverA,phonenumber_receiverB,username_receiverB,content;
		iss >> phonenumber_sender>> username_sender>> phonenumber_receiverA>>username_receiverA>>phonenumber_receiverB>>username_receiverB>> content;
		MessageGroupData* chatHighlight = new MessageGroupData{ phonenumber_sender,username_sender,phonenumber_receiverA,username_receiverA,phonenumber_receiverB,username_receiverB,content };
		if ((phonenumber_re == phonenumber_sender || phonenumber_re == phonenumber_receiverA|| phonenumber_re == phonenumber_receiverB) && z.BoolNotFriend(phonenumber_sender, phonenumber_receiverA)&& z.BoolNotFriend(phonenumber_sender, phonenumber_receiverB)&& z.BoolNotFriend(phonenumber_receiverA, phonenumber_receiverB))
		{
			x = 2;//是朋友
			if (laji.find(highlight) != string::npos)
			{
				cout << chatHighlight->phonenumber_sender << ", " << chatHighlight->phonenumber_receiverA << ", " << chatHighlight->phonenumber_receiverB << ":" <<  chatHighlight->content << endl;
				x = 1;//是朋友且有聊天记录
				MyMessageHighlightGroup.push_back(chatHighlight);
			}
		}
	}
	check_file.close();
	return x;
}
const vector<System::MessageGroupData*>& System::GetMyMessageHighlightGroup() const
{
	return MyMessageHighlightGroup;
}

void System::ReadMoment()
{
	ifstream check_file("Moment.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		int index,visible,likecount;
		string phonenumber,content;
		iss >> index >> phonenumber >> content >> visible >> likecount;
		MomentData* momentData = new MomentData{ index , phonenumber , content ,visible ,likecount };
		MyMoment.push_back(momentData);
	}
}
const vector<System::MomentData*>& System::GetMyMoment() const
{
	return MyMoment;
}
void System::WriteMoment(const MomentData& momentData)
{
	ofstream moment_file("Moment.txt", ios::app);
	if (moment_file.is_open())
	{
		moment_file << momentData.index << " " << momentData.phonenumber << " " << momentData.content << " " << momentData.visible << " " << momentData.likecount << endl;
	}
	moment_file.close();
}

int System::FindNumber()
{
	int count = 0;
	ifstream check_file("Moment.txt");
	string laji;
	while (getline(check_file, laji)) //走到最后一行就直接returncount
	{
		count++;
	}
	return count;
}

void System::ReadComment()
{
	ifstream check_file("Comment.txt");
	string laji;
	while (getline(check_file, laji))
	{
		istringstream iss(laji);
		int index, visible;
		string phonenumber, content;
		iss >> index >> phonenumber >> content >> visible ;
		CommentData* commentData = new CommentData{ index , phonenumber , content ,visible };
		MyComment.push_back(commentData);
	}
}
const vector<System::CommentData*>& System::GetMyComment() const
{
	return MyComment;
}
void System::WriteComment(const CommentData& commentData)
{
	ofstream comment_file("Comment.txt", ios::app);
	if (comment_file.is_open())
	{
		comment_file << commentData.index << " " << commentData.phonenumber << " " << commentData.content << " " << commentData.visible <<  endl;
	}
	comment_file.close();
}