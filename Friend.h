#pragma once
class Friend
{
public:
	bool BoolNotFriend(string& phonenumber_re, string& phonenumber_se);
	int NotFriend(string& phonenumber_re, string& phonenumber_se);
	void AddFriend(string &phonenumber, char& index);
	void FriendList(string& phonenumber); //查找好友
	void AcceptDeleteFriend(string& phonenumber); //若同意则1 若删除则-1
};

