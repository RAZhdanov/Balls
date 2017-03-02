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
	Node* _next; //следующий узел
	Node* _prev; //предыдущий узел
	unsigned int _id; //id узла
	std::string _name_of_column; //имя колонки
	double _value; //значение узла
	bool _flag; //исследуемый параметр (1), либо нет (0 - по умолчанию)
};