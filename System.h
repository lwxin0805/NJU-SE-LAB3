#pragma once
#include<vector>
class System
{
public:
	struct UserData
	{
		string phonenumber;
		string username;
		string password;
		int phonefind;
		int usernamefind;
		int moment;
		int accept;
		string question;
	};
	void ReadUserInfo();
	const vector<UserData*>& GetMyData() const;

	struct FriendData
	{
		string phonenumber_sender;
		string username_sender;
		string phonenumber_receiver;
		string username_receiver;
		int friend_add;
		string question;
		string answer;
	};
	void ReadFriendList();
	const vector<FriendData*>& GetMyFriend() const;

	struct MessageOneData
	{
		string phonenumber_sender;
		string username_sender;
		string phonenumber_receiver;
		string username_receiver;
		string content;
	};
	void ReadMessageOne();
	const vector<MessageOneData*>& GetMyMessageOne() const;

	struct MessageGroupData
	{
		string phonenumber_sender;
		string username_sender;
		string phonenumber_receiverA;
		string username_receiverA;
		string phonenumber_receiverB;
		string username_receiverB;
		string content;
	};
	void ReadMessageGroup();
	const vector<MessageGroupData*>& GetMyMessageGroup() const;

	struct MomentData
	{
		int index;
		string phonenumber;
		string content;
		int visible;
		int likecount;
	};
	void ReadMoment();
	const vector<MomentData*>& GetMyMoment() const;

	int FindNumber();

	struct CommentData
	{
		int index;
		string phonenumber;
		string content;
		int visible;
	};
	void ReadComment();
	const vector<CommentData*>& GetMyComment() const;

	void WriteUserInfo(const UserData& userData);
	void WriteFriendList(const FriendData& friendData);
	void WriteMessageOne(const MessageOneData& messageOne);
	void WriteMessageGroup(const MessageGroupData& messageGroup);
	void WriteMoment(const MomentData& momentData);
	void WriteComment(const CommentData& commentData);

	const vector<MessageOneData*>& GetMyMessageHighlightOne() const;
	bool ReadMessageOneHighlight(string& phonenumber_re, string& highlight);

	const vector<MessageGroupData*>& GetMyMessageHighlightGroup() const;
	int ReadMessageGroupHighlight(string& phonenumber_re, string& highlight);
private:
	vector<UserData*>MyData;
	vector<FriendData*>MyFriend;
	vector<MessageOneData*>MyMessageOne;
	vector<MessageOneData*>MyMessageHighlightOne;
	vector<MessageGroupData*>MyMessageGroup;
	vector<MessageGroupData*>MyMessageHighlightGroup;
	vector<CommentData*>MyComment;
	vector<MomentData*>MyMoment;
};

