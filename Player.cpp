#include "Player.h"

Player::Player() {

}

Player::Player(string n, float time, int difficulty) :Person(n) {
	
	Time = time;
	Difficulty = difficulty;
}

string Player::getDifficulty() {
	switch (Difficulty)
	{
	case 0:
		return "EASY";
		break;
	case 1:
		return "MEDIUM";
		break;
	case 2:
		return "HARD";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

Mtime Player::getTime() {
	Mtime ReturnTime = Time;
	return ReturnTime;
}

void Player::setDifficluty(int n) {
	Difficulty = n;
}

void Player::setTime(float f) {
	Time = f;
}

void Player::writeToFile(){
	ifstream infile;

}
