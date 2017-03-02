#pragma once
class Node
{
public:
	Node::Node(void);
	Node(unsigned int id, std::string _name_of_column);
	////
	void set_Next(Node* _next);
	Node* get_Next()const;
	////
	void set_Prev(Node* _prev);
	Node* get_Prev()const;
	////
	void set_Id(unsigned int *id);
	unsigned int get_Id()const;
	////
	void set_Name_of_column(std::string &name);
	std::string get_Name_of_column()const;
	////
	void set_Value(double value);
	double& get_Value();
	////
	void set_flag(bool value);
	bool get_flag()const;
	~Node(void);
private:
	Node* _next; //��������� ����
	Node* _prev; //���������� ����
	unsigned int _id; //id ����
	std::string _name_of_column; //��� �������
	double _value; //�������� ����
	bool _flag; //����������� �������� (1), ���� ��� (0 - �� ���������)
};