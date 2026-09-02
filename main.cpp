#include<iostream>
#include<limits>
#include "Student.h"
#include "StudentManager.h"


using namespace std;


int readInt(const string& prompt)
{
	int value;
	while (true)
	{
		cout << prompt << endl;
		if (cin >> value)
		{
			return value;
		}

		cout << "Invalid input.Please enter an integer." << endl;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}



int readMenuChoice()
{

	while (true)
	{
		int choice = readInt("choose(0-7): ");
		if (choice >= 0 && choice <= 7)
		{
			return choice;
		}

		cout << "Invalid choice.Pleade enter a number from 0 to 7." << endl;
	}
}


int readStudentId(const string& prompt)
{
	while (true)
	{
		int id = readInt(prompt);
		if (id > 0)
		{
			return id;
		}
		cout << "Student Id must be greater than 0." << endl;
	}
}


int readNewStudentId(const StudentManager& manager, const string& prompt)
{


	while (true)
	{
		int id = readInt(prompt);

		if (id == 0)
		{
			return 0;
		}
		if (id < 0)
		{
			cout << "Student Id must be greater than 0." << endl;
			continue;
		}

		if (manager.findStudentById(id) != nullptr)
		{
			cout << "Student ID already exists. Please enter another ID." << endl;
			continue;
		}
		else
		{
			return id;
		}
	}
}


int readScore(const string& prompt)
{
	while (true)
	{
		int score = readInt(prompt);
		if (score >= 0 && score <= 100)
		{
			return score;
		}
		cout << "Invalid score.Please enter a number from 0 to 100." << endl;
	}
}


bool readName(const string& prompt, string& name)
{
	

	while (true)
	{
		cout << prompt << endl;

		string input;
		getline(cin >> ws, input);

		if (input == "0")
		{
			return false;
		}
		if (!input.empty())
		{
			name = input;
			return true;
		}
		cout << "Name cannot be empty." << endl;
	}
}

bool readScoreForNewStudent(const string& prompt, int& score)
{
	while (true)
	{
		int input = readInt(prompt);
		if (input == -1)
		{
			return false;
		}
		if (input >= 0 && input <= 100)
		{
			score = input;
			return true;
		}
		cout << "Invalid score. "
			<< "Please enter 0 to 100, or -1 to cancel." << endl;
	}
}

void handleShowAllStudents(const StudentManager& manager)
{
	const vector<Student>& students = manager.getStudents();

	if (students.empty())
	{
		cout << "There are no students." << endl;
		return;
	}

	cout << "All students: " << endl;
	for (const Student& student : students)
	{
		student.showInfo();
	}
}

bool handleSortStudentsByScore(StudentManager& manager)
{
	if (manager.getStudents().empty())
	{
		cout << "There are no students to sort." << endl;
		return false;
	}

	manager.sortStudentsByScoreDescending();
	cout << "Students sorted by score from high to low." << endl;
	handleShowAllStudents(manager);
	return true;
}


void handleFindStudent(const StudentManager& manager)
{
	int targetId = readStudentId("Please enter target ID: ");
	const Student* student = manager.findStudentById(targetId);
	if (student != nullptr)
	{
		cout << "Found: " << endl;
		student->showInfo();
	}
	else
	{
		cout << "Student not found: "<< endl;
	}

}


bool handleAddStudent(StudentManager& manager)
{
	int id = readNewStudentId(manager, "Please input new ID (0 to cancel): ");
	if (id == 0)
	{
		cout << "Add student cancelled." << endl;
		return false;
	}

	string name;
	if (!readName("Please enter new name(0 to cancel): ", name))
	{
		cout << "Added student canceled." << endl;
		return false;
	}

	int score;
	if (!readScoreForNewStudent("Please enter new score 0-100(-1 to cancel): ", score))
	{
		cout << "Add student cancelled." << endl;
		return false;
	}

	Student newStudent = { id, name, score };

	AddStudentResult result = manager.addNewStudent(newStudent);

	if (result == AddStudentResult::Success)
	{
		cout << "Student added successfully." << endl;
		return true;
	}
	else if (result == AddStudentResult::InvalidStudentData)
	{
		cout << "Invalid student data." << endl;
		return false;
	}
	else
	{
		cout << "StudentId already exists." << endl;
		return false;
	}

}
	

bool handleUpdateStudentScore(StudentManager& manager)
{
	int targetId = readStudentId("Please enter target ID");
	int newScore = readScore("Please enter new score");
	UpdateScoreResult result = manager.updateStudentScore(targetId, newScore);

	switch (result)
	{
	case UpdateScoreResult::Success:
	{
		cout << "Score updated successfully." << endl;
		return true;
		
	}
	case UpdateScoreResult::StudentNotFound:
	{
		cout << "Student not found." << endl;
		return false;
		
	}
	case UpdateScoreResult::InvalidScore:
	{
		cout << "Invalid score." << endl;
		return false;
		
	}
	return false;
	}
	return false;
}


bool handleRemoveStudent(StudentManager& manager)
{
	int targetId = readStudentId("Please enter target ID: ");

	RemoveStudentResult result = manager.removeStudent(targetId);

	switch (result)
	{
	case RemoveStudentResult::Success:
	{
		cout << "Student removed successfully." << endl;
		return true;
		
	}
	case RemoveStudentResult::StudentNotFound:
	{
		cout << "Student not found." << endl;
		return false;
		
	}
	return false;
	}
	return false;
}

bool handleSaveStudents(const StudentManager& manager, const string& filename)
{
	
	return manager.saveStudentsToFile(filename);
}


void showMenu()
{
	cout << endl;
	cout << "===== Student Management System =====" << endl;
	cout << "1. Show all students" << endl;
	cout << "2. Find student by ID" << endl;
	cout << "3. Add student" << endl;
	cout << "4. Update student score" << endl;
	cout << "5. Remove student" << endl;
	cout << "6. Save student to file" << endl;
	cout << "7. Sort students by score (high to low)" << endl;
	cout << "0. Exit" << endl;

}







int main()
{

	const string studentFile = "student.txt";

	StudentManager manager;

	manager.loadStudentsFromFile(studentFile);

	bool hasUnsavedChanges = false;

	

	while (true)
	{
		showMenu();
		int choice = readMenuChoice();


		switch (choice)
		{
		case 1:
		{
			handleShowAllStudents(manager);

			break;
		}
		case 2:
		{

			handleFindStudent(manager);
			break;
		}
		case 3:
		{
			if (handleAddStudent(manager))
			{
				hasUnsavedChanges = true;
			}

			break;
		}
		case 4:
		{
			if (handleUpdateStudentScore(manager))
			{
				hasUnsavedChanges = true;
			}

			break;
		}
		case 5:
		{
			if (handleRemoveStudent(manager))
			{
				hasUnsavedChanges = true;
			}

			break;
		}
		case 6:
		{
			if (handleSaveStudents(manager, studentFile))
			{
				hasUnsavedChanges = false;
			}
			break;
		}
		case 7:
		{
			if (handleSortStudentsByScore(manager))
			{
				hasUnsavedChanges = true;
			}
			break;
		}
		case 0:
		{
			if (hasUnsavedChanges)
			{
				char answer;

				cout << "You have unsaved changes. "
					<< "Save before exit? (y/n): ";

				cin >> answer;

				if (answer == 'y' || answer == 'Y')
				{
					if (!handleSaveStudents(manager, studentFile))
					{
						cout << "Save failed. Exit cancelled." << endl;
						break;
					}
				}
			}

			cout << "Goodbye!" << endl;
			return 0;
		}
		default:
		{
			cout << "Invalid choice." << endl;
			break;
		}
		}
	}

	return 0;
}


