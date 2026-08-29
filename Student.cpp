#include "Student.h"

#include<iostream>

Student::Student(
	int studentId,
	const std::string& studentName,
	int studentScore)
	: id(studentId),
	name(studentName),
	score(studentScore)
{

}

int Student::getId() const
{
	return id;
}

const std::string& Student::getName() const
{
	return name;
}

int Student::getScore() const
{
	return score;
}

bool Student::setScore(int newScore)
{
	if (newScore < 0 || newScore > 100)
	{
		return false;
	}
	score = newScore;
	return true;
}

void Student::showInfo() const
{
	std::cout << "ID: " << id << " Name: " << name << " Score:" << score << std::endl;
}









