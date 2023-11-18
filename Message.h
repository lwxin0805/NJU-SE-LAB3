#pragma once
class Message
{
public:
	string FindNameAndPhone(string& input, char& index);
	void CheckHistory(string& phonenumber, char& index1, char& index2);
	void SendMessage(string& phonenumber);
	void SendMessagePeoples(string& phonenumber);
};

