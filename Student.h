#pragma once
#include<string>
#include<ostream>


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

	static bool isValidId(int id);
	static bool isValidName(const std::string& name);
	static bool isValidScore(int score);

	friend std::ostream& operator<<(std::ostream& out, const Student& student);
	

};