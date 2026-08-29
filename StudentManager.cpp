#include "StudentManager.h"

#include<algorithm>
#include<sstream>
#include<exception>
#include<fstream>
#include<iostream>

const std::vector<Student>& StudentManager::getStudents() const
{
	return students;
}

int StudentManager::findStudentIndex(int targetId) const
{
	auto it = lower_bound(
	    students.begin(),
		students.end(),
		targetId,
		[](const Student& student, int targetId)
		{
			return student.getId() < targetId;
		});

	if (it != students.end() && it->getId() == targetId)
	{
		return static_cast<int>(it - students.begin());
	}
	return -1;

}


AddStudentResult StudentManager::addNewStudent(const Student& newStudent)
{
	if (newStudent.getScore() < 0 || newStudent.getScore() > 100)
	{
		return AddStudentResult::InvalidScore;
	}
	
	auto it = lower_bound(
	students.begin(),
		students.end(),
		newStudent.getId(),
		[](const Student& student, int targetId)
		{
			return student.getId() < targetId;
		});

	if (it != students.end() && it->getId() == newStudent.getId())
	{
		return AddStudentResult::DuplicateId;
	}
	
	students.insert(it, newStudent);
	return AddStudentResult::Success;
}


UpdateScoreResult StudentManager::updateStudentScore(int targetId, int newScore)
{
	int index = findStudentIndex(targetId);
	if (index == -1)
	{
		return UpdateScoreResult::StudentNotFound;
	}
	if (newScore < 0 || newScore > 100)
	{
		return UpdateScoreResult::InvalidScore;
	}
	students[index].setScore(newScore);
	return UpdateScoreResult::Success;
}


RemoveStudentResult StudentManager::removeStudent(int targetId)
{
	int index = findStudentIndex(targetId);

	if (index == -1)
	{
		return RemoveStudentResult::StudentNotFound;
	}

	students.erase(students.begin() + index);
	return RemoveStudentResult::Success;
}

const Student* StudentManager::findStudentById(int targetId) const
{
	int index = findStudentIndex(targetId);
	if (index == -1)
	{
		return nullptr;
	}
	return &students[index];
}

bool StudentManager::parseStudentLine(
	const std::string& line,
	int& id,
	std::string& name,
	int& score
)const
{
	std::string idText;
	std::string scoreText;

	std::stringstream stream(line);

	if(!std::getline(stream, idText, '|')||
		!std::getline(stream, name,'|')||
		!std::getline(stream, scoreText))
	{
		return false;
	}

	try
	{
		id = std::stoi(idText);
		score = std::stoi(scoreText);
		
	}
	catch(const std::exception&)
	{
		return false;
	}

	if (id < 0 || name.empty() || score < 0 || score > 100)
	{
		return false;
	}

	return true;
}




bool StudentManager::loadStudentsFromFile(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "File not found: " << filename << std::endl;
		return false;
	}

	students.clear();
	std::string line;
	int lineNumber = 0;
	int loadedCount = 0;

	while (getline(file, line))
	{
		++lineNumber;

		if (line.empty())
		{
			continue;
		}
		int id;
		std::string name;
		int score;

		if (!parseStudentLine(line, id, name, score))
		{
			std::cout << "Skipped data at line: " << lineNumber << std::endl;
	    }

		Student student(id, name, score);

		AddStudentResult result =
			addNewStudent(student);

		switch (result)
		{
		case AddStudentResult::Success:
			++loadedCount;
			break;

		case AddStudentResult::DuplicateId:
			std::cout
				<< "Skipped duplicate student ID at line "
				<< lineNumber << std::endl;
			break;

		case AddStudentResult::InvalidScore:
			std::cout
				<< "Skipped invalid student data at line "
				<< lineNumber << std::endl;
			break;
		}

	}

	file.close();

	std::cout << loadedCount << " students loaded successfully." << std::endl;
	return true;
}


bool StudentManager::saveStudentsToFile(const std::string& filename) const
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
		return false;
	}

	for (const Student& student : students)
	{ 
		file << student.getId() << "|"
			<< student.getName() << "|"
			<< student.getScore() << std::endl;
	}
	file.close();

	std::cout << students.size() << " students saved successfully." << std::endl;
	return true;
}









