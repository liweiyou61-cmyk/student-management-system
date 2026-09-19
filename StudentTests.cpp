#include "Student.h"
#include "StudentManager.h"

#include<iostream>
#include<stdexcept>
#include<string>
#include<filesystem>
#include<fstream>

int failureCount = 0;

void check(bool condition, const std::string& testName)
{
	if (condition)
	{
		std::cout << "[PASS] " << testName << std::endl;

	}
	else
	{
		std::cout << "[FAIL] " << testName << std::endl;
		++failureCount;

	}
}


int main()
{
	Student student(1001, "Alice", 95);

	check(
		student.getId() == 1001,
		"Constructor stores the student ID"
	);

	check(
		student.getName() == "Alice",
		"Constructor stores the student name"
	);

	check(
		student.getScore() == 95,
		"Constructor stores the student score"
	);

	bool validResult = student.setScore(88);

	check(
		validResult,
		"setScore accepts a valid score"
	);

	check(
	student.getScore() == 88,
		"setScore changes the score"
	);

	bool invalidResult = student.setScore(101);

	check(
		!invalidResult,
		"setScore rejects an invalid score"
	);

	check(
		student.getScore() == 88,
		"Invalid score does not change the old score"
	);

	bool exceptionThrown = false;

	try
	{
		Student invalidStudent(0, "Bob", 80);
	}

	catch(const std::invalid_argument&)
	{
		exceptionThrown = true;
	}

	check(
		exceptionThrown,
		"Constructor rejects an invalid ID"
	);

		std::cout << "\nTesting StudentManager: " << std::endl;

		StudentManager manager;

		Student alice(2001, "Alice", 90);

		AddStudentResult firstAddResult =
			manager.addNewStudent(alice);

		check(
			firstAddResult == AddStudentResult::Success,
			"Manager accepts a new student"
		);

		check(
		manager.getStudents().size() == 1,
			"Manager stores the new student"
		);

		Student duplicateStudent(2001, "Bob", 70);

		AddStudentResult duplicateResult =
			manager.addNewStudent(duplicateStudent);

		check(
			duplicateResult == AddStudentResult::DuplicateId,
			"Manager rejects a duplicate student ID"
		);

		check(
			manager.getStudents().size() == 1,
			"Duplicate student is not stored"
		);

		const Student* foundStudent =
			manager.findStudentById(2001);

		check(
			foundStudent != nullptr,
			"Manager finds an existing student"
		);

		if (foundStudent != nullptr)
		{
			check(
				foundStudent->getName() == "Alice",
				"Duplicate student does not replace the original student"
			);
		}

		std::cout << "\nTesting score updates:" << std::endl;

		StudentManager updateManager;

		Student carol(3001, "Carol", 75);

		updateManager.addNewStudent(carol);

		UpdateScoreResult successResult =
			updateManager.updateStudentScore(3001, 85);

		check(
			successResult == UpdateScoreResult::Success,
			"Manager reports a successful score update"
		);

		const Student* updatedStudent =
			updateManager.findStudentById(3001);

		check(
			updatedStudent != nullptr,
			"Updated student still exists"
		);

		if (updatedStudent != nullptr)
		{
			check(
				updatedStudent->getScore() == 85,
				"Successful update changes the score"
			);
		}

		UpdateScoreResult invalidScoreResult =
			updateManager.updateStudentScore(3001, 101);

		check(
			invalidScoreResult == UpdateScoreResult::InvalidScore,
			"Manager rejects an invalid new score"
		);

		const Student* studentAfterInvalidUpdate =
			updateManager.findStudentById(3001);

		if (studentAfterInvalidUpdate != nullptr)
		{
			check(
				studentAfterInvalidUpdate->getScore() == 85,
				"Invalid update preserves the old score"
			);
		}

		UpdateScoreResult missingStudentResult =
			updateManager.updateStudentScore(9999, 60);

		check(
			missingStudentResult ==
			UpdateScoreResult::StudentNotFound,
			"Manager reports a missing student"
		);

		check(
			updateManager.getStudents().size() == 1,
			"Updating a missing student does not add a student"
		);


		std::cout << "\nTesting students removal: " << std::endl;
		StudentManager removeManager;

		Student david(4001, "David", 80);
		Student emma(4002, "Emma", 92);

		removeManager.addNewStudent(david);
		removeManager.addNewStudent(emma);

		RemoveStudentResult removeResult =
			removeManager.removeStudent(4001);

		check(removeResult == RemoveStudentResult::Success,
			"Manager reports a successful removal");
		check(removeManager.findStudentById(4001) == nullptr,
			"Removed students can no longer be found");
		check(removeManager.getStudents().size() == 1,
			"Succcessful removal decreases the student count");
		const Student* remainingStudents = removeManager.findStudentById(4002);
		check(remainingStudents != nullptr,
			"Removing one student preserves other students");
		if (remainingStudents != nullptr)
		{
			check(remainingStudents->getName() == "Emma",
				"The correct student remain after removal");

		}

		RemoveStudentResult missingRemoveStudent = removeManager.removeStudent(9999);
		check(missingRemoveStudent == RemoveStudentResult::StudentNotFound,
			"Manager reports a missing student during removal");
		check(removeManager.getStudents().size() == 1,
			"Failed removal does not change the student count");
		check(removeManager.findStudentById(4002) != nullptr,
			"Failed removal does not damage existing students");


		std::cout << "\nTesting score sorting:" << std::endl;

		StudentManager sortManager;

		Student lowScoreStudent(5001, "Low", 60);
		Student highScoreStudent(5002, "High", 95);
		Student middleScoreStudent(5003, "Middle", 80);

		sortManager.addNewStudent(lowScoreStudent);
		sortManager.addNewStudent(highScoreStudent);
		sortManager.addNewStudent(middleScoreStudent);

		sortManager.sortStudentsByScoreDescending();

		const std::vector<Student>& sortedStudents =
			sortManager.getStudents();

		check(sortedStudents.size() == 3,
			"Sorting preserves all students");

		if (sortedStudents.size() == 3)
		{
			check(sortedStudents[0].getScore() == 95,
				"Highest score is placed first");
			check(sortedStudents[1].getScore() == 80,
				"Middle score is placed second");
			check(sortedStudents[2].getScore() == 60,
				"Lowest score is placed last");

		}

		const Student* studentAfterSorting =
			sortManager.findStudentById(5001);

		check(studentAfterSorting != nullptr,
			"Student can still be found after score sorting");

		if (studentAfterSorting != nullptr)
		{
			check(studentAfterSorting->getName() == "Low",
				"Sorting preserves the student data");
		}


		std::cout << "\nTesting file save and load:" << std::endl;

		const std::filesystem::path testFile =
			std::filesystem::temp_directory_path() /
			"student_management_system_test_data.txt";

		std::filesystem::remove(testFile);

		StudentManager saveManager;

		Student frank(6001, "Frank", 78);
		Student gina(6002, "Gina", 91);

		saveManager.addNewStudent(frank);
		saveManager.addNewStudent(gina);

		bool saveResult = saveManager.saveStudentsToFile(testFile.string());

		check(saveResult,
			"Manager saves students to a file");
		check(std::filesystem::exists(testFile),
			"Student data file is created");

		StudentManager loadManager;
		LoadStudentsResult loadResult =
			loadManager.loadStudentsFromFile(testFile.string());

		check(loadResult.fileOpened,
			"Manager opens the saved data file");
		check(loadResult.loadedCount == 2,
			"Manager loads two students");
		check(loadResult.invalidLineCount == 0,
			"Saved file contains no invalid lines");
		check(loadResult.duplicateIdCount == 0,
			"Saved file contains no duplicate IDs");
		check(loadManager.getStudents().size() == 2,
			"Loaded manager contains two students");

		const Student* loadedGina =
			loadManager.findStudentById(6002);

		check(loadedGina != nullptr,
			"Loaded student can be found by ID");
		if (loadedGina != nullptr)
		{
			check(loadedGina->getName() == "Gina" &&
				loadedGina->getScore() == 91,
				"Loaded student data matches saved data");
		}

		std::filesystem::remove(testFile);


		std::cout << "\nTesting invalid file data: " << std::endl;

		const std::filesystem::path invalidDataFile =
			std::filesystem::temp_directory_path() /
			"student_management_sysytem_invalid_data_test.txt";

		std::filesystem::remove(invalidDataFile);

		{
			std::ofstream file(invalidDataFile);

			file << "7001|Henry|88\n";       // 合法
			file << "bad-id|Invalid|90\n";   // 学号不是数字
			file << "7002||75\n";            // 姓名为空
			file << "7003|TooHigh|101\n";    // 成绩超过100
			file << "7001|Duplicate|60\n";   // 与Henry学号重复
		}

		StudentManager invalidLoadManager;

		LoadStudentsResult invalidLoadResult =
			invalidLoadManager.loadStudentsFromFile(
				invalidDataFile.string()
			);

		check(invalidLoadResult.fileOpened,
			"Manager opens a mixed-validity data file");

		check(invalidLoadResult.loadedCount == 1,
			"Manager loads the one valid student");

		check(invalidLoadResult.invalidLineCount == 3,
			"Manager counts three invalid lines");

		check(invalidLoadResult.duplicateIdCount == 1,
			"Manager counts one duplicate ID");

		check(invalidLoadManager.getStudents().size() == 1,
			"Only the valid student is stored");

		const Student* loadedHenry =
			invalidLoadManager.findStudentById(7001);
		check(loadedHenry != nullptr,
			"Valid student is preserved during invalid file loading");

		if (loadedHenry != nullptr)
		{
			check(loadedHenry->getName() == "Henry" &&
				loadedHenry->getScore() == 88,
				"Valid student data is loaded correctly");
		}

		std::filesystem::remove(invalidDataFile);




		if (failureCount == 0)
		{
			std::cout << "\nAll tests passed." << std::endl;
			return 0;
		}

		std::cout << "\n"
			<< failureCount
			<< " test(s) failed."
			<< std::endl;

		return 1;
}