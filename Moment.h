#pragma once
class Moment
{
public:
	bool CheckIfMomentSeen(string& phonenumber);
	void MomentCheckAll(string& phonenumber);
	void MomentOneFriend(string& phonenumber);
	void MomentMe(string& phonenumber);
	void MomentPublish(string& phonenumber); //��������Ȧ
	bool MomentCheck(string& phonenumber); //�鿴����Ȧ (�����ֻ���)
	void MomentComment(string& phonenumber,int& index); //����(Comment.txt)
	void MomentSet(string& phonenumber); //ɾ������&&���Լ��ɼ� (Comment.txt & Moment.txt)
	void MomentLike(int& index);
};

