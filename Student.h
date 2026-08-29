#pragma once
#include<string>


class Student
{
private:
	int id;
	std::string name;
	int score;
public:
	Student(int StudentId, const std::string& StudentName, int StudentScore);

	int getId() const;

	const std::string& getName() const;

	int getScore() const;

	bool setScore(int newScore);

	void showInfo() const;
	

};