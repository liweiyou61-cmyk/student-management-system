//#include<iostream>
//#include<string>
//#include<vector>
//#include<algorithm>
//#include<limits>
//
//
//using namespace std;
//
//
//class Student
//{
//private:
//	int Id;
//	string name;
//	int score;
//public:
//	Student(int studentId, const string& studentName, int studentScore)
//		: Id(studentId), name(studentName), score(studentScore)
//	{
//
//	}
//
//	int getId() const
//	{
//		return Id;
//	}
//
//	const string& getName() const
//	{
//		return name;
//	}
//
//	int getScore() const
//	{
//		return score;
//	}
//
//	bool setScore(int newScore)
//	{
//		if (newScore < 0 || newScore > 100)
//		{
//			return false;
//		}
//		score = newScore;
//		return true;
//	}
//
//	void showInfo() const
//	{
//		cout << "Id: " << Id
//			<< "  Name: " << name
//			<< "  Score: " << score << endl;
//	}
//};
//
//
//void findStudentById(const vector<Student>& students, int targetId)
//{
//	auto it = lower_bound(
//		students.begin(),
//		students.end(),
//		targetId,
//		[](const Student& student, int targetId)
//		{
//			return student.getId() < targetId;
//		});
//	if (it != students.end() && it->getId() == targetId)
//	{
//		cout << "Found: " << it->getId() << endl;
//		(*it).showInfo();
//	}
//	else
//	{
//		cout << "Not found: " << targetId << endl;
//	}
//}
//
//int findStudentIndex(const vector<Student>& students, int targetId)
//{
//	auto it = lower_bound(students.begin(), students.end(), targetId,
//		[](const Student& student, int targetId)
//		{
//			return student.getId() < targetId;
//		});
//	if (it != students.end() && it->getId() == targetId)
//	{
//		return static_cast<int>(it - students.begin());
//
//	}
//
//	return -1;
//}
//
//bool addNewStudent(vector<Student>& students, const Student& newStudent)
//{
//	if (newStudent.getScore() < 0 || newStudent.getScore() > 100)
//	{
//		cout << "Invalid score" << endl;
//		return false;
//	}
//	auto it = lower_bound(students.begin(),
//		students.end(),
//		newStudent.getId(),
//		[](const Student& student, int targetId)
//		{
//			return student.getId() < targetId;
//		});
//	if (it != students.end() && it->getId() == newStudent.getId())
//	{
//		cout << "Id already exists" << endl;
//		return false;
//	}
//	else
//	{
//		students.insert(it, newStudent);
//
//		cout << "Student insert successfully" << endl;
//		return true;
//	}
//}
//
//
//
//bool updateStudentScore(vector<Student>& students, int targetId, int newScore)
//{
//	int index = findStudentIndex(students, targetId);
//	if (index == -1)
//	{
//		cout << "Not found: " << targetId << endl;
//		return false;
//	}
//	else
//	{
//		if (students[index].setScore(newScore))
//		{
//
//			cout << "update successfully" << endl;
//			return true;
//		}
//		else
//		{
//			cout << "Invalid score." << endl;
//			return false;
//		}
//	}
//}
//
//bool removeStudent(vector<Student>& students, int targetId)
//{
//	int index = findStudentIndex(students, targetId);
//	if (index == -1)
//	{
//		cout << "The student is not exist." << endl;
//		return false;
//	}
//	else
//	{
//		students.erase(students.begin() + index);
//		cout << "Student remove successfully." << endl;
//		return true;
//	}
//}
//
//int readInt(const string& prompt)
//{
//	int value;
//	while (true)
//	{
//		cout << prompt << endl;
//		if (cin >> value)
//		{
//			return value;
//		}
//
//		cout << "Invalid input.Please enter an integer." << endl;
//
//		cin.clear();
//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	}
//}
//
//int readMenuChoice()
//{
//
//	while (true)
//	{
//		int choice = readInt("choose(0-5): ");
//		if (choice >= 0 && choice <= 5)
//		{
//			return choice;
//		}
//
//		cout << "Invalid choice.Pleade enter a number from 0 to 5." << endl;
//	}
//}
//
//int readStudentId(const string& prompt)
//{
//	while (true)
//	{
//		int id = readInt(prompt);
//		if (id > 0)
//		{
//			return id;
//		}
//		cout << "Student Id must be greater than 0." << endl;
//	}
//}
//
//int readNewStudentId(const vector<Student>& students, const string& prompt)
//{
//	while (true)
//	{
//		int id = readStudentId(prompt);
//		if (findStudentIndex(students, id) != -1)
//		{
//			cout << "Student ID already exists. Please enter another ID." << endl;
//		}
//		else
//		{
//			return id;
//		}
//	}
//}
//
//
//int readScore(const string& prompt)
//{
//	while (true)
//	{
//		int score = readInt(prompt);
//		if (score >= 0 && score <= 100)
//		{
//			return score;
//		}
//		cout << "Invalid score.Please enter a number from 0 to 100." << endl;
//	}
//}
//
//string readName(const string& prompt)
//{
//	string name;
//
//	while (true)
//	{
//		cout << prompt << endl;
//
//		getline(cin>>ws, name);
//
//		if (!name.empty())
//		{
//			return name;
//		}
//		cout << "Name cannot be empty." << endl;
//	}
//}
//
//void showMenu()
//{
//	cout << endl;
//	cout << "===== Student Management System =====" << endl;
//	cout << "1. Show all students" << endl;
//	cout << "2. Find student by ID" << endl;
//	cout << "3. Add student" << endl;
//	cout << "4. Update student score" << endl;
//	cout << "5. Remove student" << endl;
//	cout << "0. Exit" << endl;
//
//}
//
//int main()
//{
//	vector<Student> students = {
//		{1003, "Bob", 85},
//		{1001, "Tom", 90},
//		{1004, "David", 76},
//		{1002, "Alice", 95} };
//
//	sort(students.begin(), students.end(),
//		[](const Student& a, const Student& b)
//		{
//			return a.getId() < b.getId();
//		}
//	);
//
//	while (true)
//	{
//		showMenu();
//		int choice = readMenuChoice();
//
//
//		switch (choice)
//		{
//		case 1:
//		{
//			cout << "All students: " << endl;
//			for (const Student& student : students)
//			{
//				student.showInfo();
//			}
//
//			break;
//		}
//		case 2:
//		{
//
//			int targetId = readStudentId("Please enter target ID: ");
//			findStudentById(students, targetId);
//
//			break;
//		}
//		case 3:
//		{
//			int id = readNewStudentId(students, "Please input new ID");
//			
//			string name = readName("Please enter new name");
//
//			int score = readScore("Please input new Score");
//			Student newStudent = { id, name, score };
//			addNewStudent(students, newStudent);
//
//			break;
//		}
//		case 4:
//		{
//			int targetId = readStudentId("Please enter target ID");
//
//			int newScore = readScore("Please enter new score");
//
//			updateStudentScore(students, targetId, newScore);
//
//			break;
//		}
//		case 5:
//		{
//			int targetId = readStudentId("Please enter target ID");
//
//
//			removeStudent(students, targetId);
//
//			break;
//		}
//		case 0:
//		{
//			cout << "Goodbye!" << endl;
//			return 0;
//		}
//		default:
//		{
//			cout << "Invalid choice." << endl;
//			break;
//		}
//		}
//	}
//
//	return 0;
//}
//
//
