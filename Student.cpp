#include "Student.h"

#include<iostream>
#include<stdexcept>

Student::Student(
	int studentId,
	const std::string& studentName,
	int studentScore)
	: id(studentId),
	name(studentName),
	score(studentScore)
{
	if (!isValidId(id))
	{
		throw std::invalid_argument("Student Id must be greater than 0.");
	}
	if (!isValidName(name))
	{
		throw std::invalid_argument("Student name cannot be empty.");
	}
	if (!isValidScore(score))
	{
		throw std::invalid_argument("Student score must be between 0 and 100.");
	}
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

bool Student::isValidScore(int score)
{
	return score >= 0 && score <= 100;
}

bool Student::isValidId(int id)
{
	return id > 0;
}

bool Student::isValidName(const std::string& name)
{
	return !name.empty();
}

bool Student::setScore(int newScore)
{
	if (!isValidScore(newScore))
	{
		return false;
	}
	score = newScore;
	return true;
}

std::ostream& operator<<(std::ostream& out, const Student& student)
{
	out << "Id: " << student.id
		<< " Name: " << student.name
		<< " Score: " << student.score;

	return out;
}









