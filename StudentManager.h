#pragma once

#include<string>

#include<vector>

#include "Student.h"

enum class AddStudentResult
{
	Success,
	DuplicateId,
	InvalidStudentData
};

enum class UpdateScoreResult
{
	Success,
	StudentNotFound,
	InvalidScore
};

enum class RemoveStudentResult
{
	Success,
	StudentNotFound
};

class StudentManager
{
private:
	std::vector<Student> students;

	int findStudentIndex(int targetId) const;

	bool parseStudentLine(
		const std::string& line,
		int& id,
		std::string& name,
		int& score
	)const;

public:
	const std::vector<Student>& getStudents() const;

	const Student* findStudentById(int targetId) const;

	AddStudentResult addNewStudent(const Student& newStudent);

	UpdateScoreResult updateStudentScore(
		int targetId,
		int newScore
	);

	RemoveStudentResult removeStudent(int targetId);

	void sortStudentsByScoreDescending();

	bool loadStudentsFromFile(const std::string& filename);

	bool saveStudentsToFile(const std::string& filename) const;
};