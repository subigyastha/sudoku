#include "Person.h"

Person::Person() {
	name = "no_name";
	age = 0;
}

Person::Person(string n) {
	name = n;
	age = 0;
}

string Person::getname() {
	return name;
}

void Person::setname(string n) {
	if (n.length() == 0)
		name = "no_name";
	else
		name = n;
}