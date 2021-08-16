#pragma once
#include<string>
using std::string;
class Person
{
protected:
	string name;
	int age;
public:
	Person();
	Person(string n);
	string getname();
	void setname(string n);
};
