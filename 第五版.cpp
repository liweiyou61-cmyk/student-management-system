//#include<iostream>
//#include<string>
//#include<vector>
//#include<algorithm>
//#include<limits>
//#include<sstream>
//#include<fstream>
//#include<exception>
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
//bool parseStudentLine(
//	const string& line,
//	int& id,
//	string& name,
//	int& score)
//{
//	string idText;
//	string scoreText;
//	stringstream stream(line);
//
//	if (!getline(stream, idText, '|') ||
//		!getline(stream, name, '|') ||
//		!getline(stream, scoreText)
//		)
//	{
//		return false;
//	}
//
//	try
//	{
//		id = stoi(idText);
//		score = stoi(scoreText);
//
//	}
//	catch (const exception&)
//	{
//		return false;
//	}
//	if (id <= 0 || name.empty() || score < 0 || score > 100)
//	{
//		return false;
//	}
//
//
//	return true;
//}
//
//bool loadStudentsFromFile(vector<Student>& students, const string& filename)
//{
//	ifstream file(filename);
//
//	if (!file.is_open())
//	{
//		cout << "File not found: " << filename << endl;
//		return false;
//	}
//
//	students.clear();
//
//	string line;
//	int lineNumber = 0;
//	int loadedCount = 0;
//
//	while (getline(file, line))
//	{
//		++lineNumber;
//
//		if (line.empty())
//		{
//			continue;
//		}
//
//		int id;
//		string name;
//		int score;
//
//		if (!parseStudentLine(line, id, name, score))
//		{
//			cout << "Skipped invalid data at line" << lineNumber << endl;
//			continue;
//		}
//
//		Student student(id, name, score);
//
//		if (addNewStudent(students, student))
//		{
//			++loadedCount;
//
//		}
//		else
//		{
//			cout << "Skipped duplicate student ID at line" << lineNumber << endl;
//		}
//	}
//	file.close();
//
//	cout << loadedCount << " students loaded successfully." << endl;
//	return true;
//}
//
//bool saveStudentsToFile(const vector<Student>& students, const string& filename)
//{
//	ofstream file(filename);
//
//	if (!file.is_open())
//	{
//		cout << "Failed to open file: " << filename << endl;
//		return false;
//	}
//
//	for (const Student& student : students)
//	{
//		file << student.getId() << "|"
//			<< student.getName() << "|"
//			<< student.getScore() << endl;
//	}
//	file.close();
//
//	cout << students.size() << " students saved successfully." << endl;
//
//	return true;
//}
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
//		int choice = readInt("choose(0-6): ");
//		if (choice >= 0 && choice <= 6)
//		{
//			return choice;
//		}
//
//		cout << "Invalid choice.Pleade enter a number from 0 to 6." << endl;
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
//		getline(cin >> ws, name);
//
//		if (!name.empty())
//		{
//			return name;
//		}
//		cout << "Name cannot be empty." << endl;
//	}
//}
//
//
//
//
//void handleShowAllStudents(const vector<Student>& students)
//{
//	if (students.empty())
//	{
//		cout << "There are no students." << endl;
//		return;
//	}
//
//	cout << "All students: " << endl;
//	for (const Student& student : students)
//	{
//		student.showInfo();
//	}
//}
//
//void handleFindStudent(const vector<Student>& students)
//{
//	int targetId = readStudentId("Please enter target ID: ");
//	findStudentById(students, targetId);
//}
//
//void handleAddStudent(vector<Student>& students)
//{
//	int id = readNewStudentId(students, "Please input new ID");
//	string name = readName("Please enter new name");
//	int score = readScore("Please input new Score");
//	Student newStudent = { id, name, score };
//	addNewStudent(students, newStudent);
//}
//
//
//void handleUpdateStudentScore(vector<Student>& students)
//{
//	int targetId = readStudentId("Please enter target ID");
//	int newScore = readScore("Please enter new score");
//	updateStudentScore(students, targetId, newScore);
//}
//
//
//void handleRemoveStudent(vector<Student>& students)
//{
//	int targetId = readStudentId("Please enter target ID: ");
//
//	removeStudent(students, targetId);
//}
//
//void handleSaveStudents(const vector<Student>& students, const string& filename)
//{
//	saveStudentsToFile(students, filename);
//}
//
//
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
//	cout << "6. Save student to file" << endl;
//	cout << "0. Exit" << endl;
//
//}
//
//
//
//
//
//
//int main()
//{
//
//	const string studentFile = "C:\\Users\\21263\\Desktop\\student.txt";
//
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
//	loadStudentsFromFile(students, studentFile);
//
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
//			handleShowAllStudents(students);
//
//			break;
//		}
//		case 2:
//		{
//
//			handleFindStudent(students);
//			break;
//		}
//		case 3:
//		{
//			handleAddStudent(students);
//
//			break;
//		}
//		case 4:
//		{
//			handleUpdateStudentScore(students);
//
//			break;
//		}
//		case 5:
//		{
//			handleRemoveStudent(students);
//
//			break;
//		}
//		case 6:
//		{
//			handleSaveStudents(students, studentFile);
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
