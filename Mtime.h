#pragma once
#include <SFML\Graphics.hpp>
class Mtime
{
private:
	float mytime;
	int hour, minute, second;
public:
	Mtime();
	Mtime(float f);
	void settime(float f);
	void gettime();
	int Rsecond();
	int Rminute();
	int Rhour();
};