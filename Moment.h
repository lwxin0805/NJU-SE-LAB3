#pragma once
class Moment
{
public:
	bool CheckIfMomentSeen(string& phonenumber);
	void MomentCheckAll(string& phonenumber);
	void MomentOneFriend(string& phonenumber);
	void MomentMe(string& phonenumber);
	void MomentPublish(string& phonenumber); //发布朋友圈
	bool MomentCheck(string& phonenumber); //查看朋友圈 (输入手机号)
	void MomentComment(string& phonenumber,int& index); //评论(Comment.txt)
	void MomentSet(string& phonenumber); //删除评论&&仅自己可见 (Comment.txt & Moment.txt)
	void MomentLike(int& index);
};

