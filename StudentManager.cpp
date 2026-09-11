#include "StudentManager.h"

#include<algorithm>
#include<sstream>
#include<exception>
#include<fstream>

const std::vector<Student>& StudentManager::getStudents() const
{
	return students;
}

int StudentManager::findStudentIndex(int targetId) const
{
	auto it = std::find_if(
	    students.begin(),
		students.end(),
		[targetId](const Student& student)
		{
			return student.getId() == targetId;
		});

	if (it == students.end())
	{
		return -1;
	}
	return static_cast<int>(it - students.begin());

}

void StudentManager::sortStudentsByScoreDescending()
{
	std::sort(students.begin(),
		students.end(),
		[](const Student& a, const Student& b)
		{
			return a.getScore() > b.getScore();
		});
}





AddStudentResult StudentManager::addNewStudent(const Student& newStudent)
{
	
	if (findStudentIndex(newStudent.getId()) != -1)
	{
		return AddStudentResult::DuplicateId;
	}
	
	students.push_back(newStudent);
	return AddStudentResult::Success;
}


UpdateScoreResult StudentManager::updateStudentScore(int targetId, int newScore)
{
	int index = findStudentIndex(targetId);
	if (index == -1)
	{
		return UpdateScoreResult::StudentNotFound;
	}
	if (!Student::isValidScore(newScore))
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

	if (!Student::isValidId(id) || !Student::isValidName(name)|| !Student::isValidScore(score))
	{
		return false;
	}

	return true;
}




LoadStudentsResult StudentManager::loadStudentsFromFile(const std::string& filename)
{
	LoadStudentsResult result;
	std::ifstream file(filename);

	if (!file.is_open())
	{
		return result;
	}

	result.fileOpened = true;
	students.clear();
	std::string line;
	

	while (std::getline(file, line))
	{

		if (line.empty())
		{
			continue;
		}
		int id;
		std::string name;
		int score;

		if (!parseStudentLine(line, id, name, score))
		{
			++result.invalidLineCount;
			continue;
	    }

		Student student(id, name, score);

		AddStudentResult addResult =
			addNewStudent(student);

		switch (addResult)
		{
		case AddStudentResult::Success:
			++result.loadedCount;
			break;

		case AddStudentResult::DuplicateId:
			
			++result.duplicateIdCount;
			break;
		}

	}

	return result;
}


bool StudentManager::saveStudentsToFile(const std::string& filename) const
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		return false;
	}

	for (const Student& student : students)
	{ 
		file << student.getId() << "|"
			<< student.getName() << "|"
			<< student.getScore() <<"\n";
	}

	return file.good();
}









