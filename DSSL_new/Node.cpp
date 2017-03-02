#include "StdAfx.h"
#include "Node.h"

Node::Node(void) :_id(0), _next(NULL), _prev(NULL), _value(0), _flag(false){}
Node::~Node(void){}


Node::Node(unsigned int id, std::string _column) : _id(id), _next(NULL), _prev(NULL), _value(0), _name_of_column(_column), _flag(false){}
//////��������� ����
void Node::set_Next(Node* _next){ this->_next = _next; }
Node* Node::get_Next()const{ return _next; }
//////���������� ����
void Node::set_Prev(Node* _prev){ this->_prev = _prev; }
Node* Node::get_Prev()const{ return _prev; }
//////id ����
void Node::set_Id(unsigned int *id){ this->_id = *id; }
unsigned int Node::get_Id()const{ return _id; }
//////�������� ����
void Node::set_Value(double value){ this->_value = value; }
double& Node::get_Value(){ return _value; }
//////��� �������
void Node::set_Name_of_column(std::string &name){ this->_name_of_column = name; }
std::string Node::get_Name_of_column()const{ return _name_of_column; }
//////����������� �������� (1), ���� ��� (0 - �� ���������)
void Node::set_flag(bool value)
{
	this->_flag = value;
}
bool Node::get_flag()const
{ 
	return _flag;
}