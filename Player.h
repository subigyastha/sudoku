#pragma once
#include"Person.h"
#include"Mtime.h"
#include<fstream>

using namespace std;

class Player :public Person
{
protected:
	float Time;//time
	int Difficulty;//difficulty solved
public:
	Player();
	Player(string n, float time, int dificulty);

	Mtime getTime();
	string getDifficulty();
	void setTime(float f);
	void writeToFile(string name, string level, Mtime time,bool &once);
	void setDifficluty(int n);
	
};