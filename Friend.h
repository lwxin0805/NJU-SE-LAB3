#pragma once
class Friend
{
public:
	bool BoolNotFriend(string& phonenumber_re, string& phonenumber_se);
	int NotFriend(string& phonenumber_re, string& phonenumber_se);
	void AddFriend(string &phonenumber, char& index);
	void FriendList(string& phonenumber); //���Һ���
	void AcceptDeleteFriend(string& phonenumber); //��ͬ����1 ��ɾ����-1
};

