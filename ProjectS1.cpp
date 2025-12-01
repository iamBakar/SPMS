#include<iostream>
#include<fstream> 
#include<cctype>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;

// making structures for optimization 
struct Student {
	char name[50];
	string rollNo;
	string section;
	float quiz[3];
	float assignment[2];
	float mids, finals, total, percentage;
	char grade;
};
// setting max marks for each test
int const maxQuiz = 10, maxAssign = 10, maxMids = 30, maxFinals = 50;

// can store upto 100 students 
Student students[100];
int studentCount = 0; // shows number of students
string roll; // to search roll number

// calculate grade
void calculateGrade(Student& student) {
	student.total = student.quiz[0] + student.quiz[1] + student.quiz[2] + student.assignment[0] + student.assignment[1] + student.mids + student.finals;

	float maxMarks = (3 * 10) + (2 * 10) + 30 + 50; // out of 100
	student.percentage = (student.total / maxMarks) * 100;
	if (student.percentage >= 85)
		student.grade = 'A';
	else if (student.percentage >= 70)
		student.grade = 'B';
	else if (student.percentage >= 55)
		student.grade = 'C';
	else if (student.percentage >= 40)
		student.grade = 'D';
	else
		student.grade = 'F';
}

bool isRollValid(string& roll) { // checks validity of entered roll number
	for (int i = 0; i < studentCount; i++) {
		if (roll == students[i].rollNo) {
			cout << "A student of this roll number exists already\n";
			return false;
		}
	}
	if (roll.size() > 4) { // if more than 4 digits then false
		cout << "Invalid!\n";
		return false;
	}
	for (char c : roll) {
		if (!isdigit(c)) { // if not a numeric digit then false
			cout << "Invalid!\n";
			return false;
		}
	}
	return true;
}

bool isNameValid(char sName[]) {
	bool hasAlpha = false;
	for (int i = 0; sName[i] != '\0'; i++) {
		if (isalpha(sName[i])) {
			hasAlpha = true; // to check at least one character, eg " " is invalid as no char is entered
		}
		else if (sName[i] != ' ') { // returns false for everything except spaces 
			return false;
		}
	}
	return hasAlpha;
}

bool isSectionValid(string& section) {
	if (section.length() == 1 && (section[0] >= 'A' && section[0] <= 'F')) { 
		return true;
	}
	return false;
}

//adding a student
void addStudent() {
	Student student;
	string rollNo;
	if (studentCount >= 100) {
		cout << "\nCan not add more students.";
		return;
	}
	cout << "Enter Student Name: ";
	cin.ignore(); // otherwise infinite loop
	cin.getline(student.name, 50);
	while (!isNameValid(student.name)) { // checking name after input
		cout << "Number must not contain numbers or special characters\n";
		cout << "Enter Student Name: ";
		cin.ignore();
		cin.getline(student.name, 50);
	}
	while (true) { // checking roll number after input
		cout << "Enter Roll Number (0-9999): ";
		cin >> rollNo;
		if (!isRollValid(rollNo)) {
			continue;
		}
		student.rollNo = rollNo;
		break;
	}
	cout << "Enter Student Section (A-F): ";
	cin >> student.section;
	student.section[0] = toupper(student.section[0]); // converts to UPPERCASE
	while (!isSectionValid(student.section)) { // checking section after input
		cout << "Invalid input! Must be a single alphabet from A-F\n";
		cout << "Enter Student Section (A-F): ";
		cin >> student.section;
		student.section[0] = toupper(student.section[0]); // again
	}
	for (int i = 0; i < 3; i++) {
	label:
		cout << "Enter marks of Quiz (out of 10) " << i + 1 << ": ";
		cin >> student.quiz[i];
		if (student.quiz[i] < 0 || student.quiz[i] > maxQuiz) {
			cout << "Inavlid!\n";
			goto label;
		}
	}
	for (int i = 0; i < 2; i++) {
	label2:
		cout << "Enter marks of Assignment (out of 10) " << i + 1 << ": ";
		cin >> student.assignment[i];
		if (student.assignment[i] < 0 || student.assignment[i] > maxAssign) {
			cout << "Inavlid!\n";
			goto label2;
		}
	}
	label3:
	cout << "Enter Midterm Marks (out of 30): ";
	cin >> student.mids;
	if (student.mids < 0 || student.mids > maxMids) {
		cout << "Inavlid!\n";
		goto label3;
	}
	label4:
	cout << "Enter Finals Marks (out of 50): ";
	cin >> student.finals;
	if (student.finals < 0 || student.finals > maxFinals) {
		cout << "Inavlid!\n";
		goto label4;
	}
	calculateGrade(student); // calculates percentage 
	students[studentCount++] = student; // adds to the array and count++
	cout << "\nStudent added successfully\n";
}

// to save data in files

void save() {
	fstream student;
	student.open("Student.txt", ios::out, ios:: trunc); // write
	student << studentCount << "\n"; // had to do to match with load function
	if (student.is_open()) {
		for (int i = 0; i < studentCount; i++) {
			student << students[i].rollNo << "|" << students[i].name << "|"
				<< students[i].section << "|" << students[i].quiz[0] << " "
				<< students[i].quiz[1] << " " << students[i].quiz[2] << " "
				<< students[i].assignment[0] << " "
				<< students[i].assignment[1] << " " << students[i].mids << " "
				<< students[i].finals << "\n";
		}
	}
	student.close();
	cout << "Total students: " << studentCount << endl;
	cout << "Saved and exiting!\n";
}

// to load data from files 
//void load() {
//	ifstream student("Student.txt"); // i-fstream to read
//	if (!student) return; // if invalid stream
//	student >> studentCount; // load studenCount (some value) students
//	for (int i = 0; i < studentCount; i++) {
//		student >> students[i].rollNo;
//		student.get(); // consume '|'
//		student.getline(students[i].name, 50, '|'); // read full name with spaces until delimeter
//		student >> students[i].section
//			>> students[i].quiz[0] >> students[i].quiz[1] >> students[i].quiz[2]
//			>> students[i].assignment[0] >> students[i].assignment[1]
//			>> students[i].mids >> students[i].finals;
//
//		calculateGrade(students[i]);
//	}
//	student.close();
//	cout << "Data loaded successfully. Total students: " << studentCount << endl;
//}


/* had to use chatGPT because my load was constantly causing issues whenever i was using
spaces in name. I gave it alot of time but still it was not properly working. GPT added delimeters 
and student.get() to solve the problem */

void load() {
	ifstream student("Student.txt");
	if (!student) {
		cout << "No saved data found.\n";
		return;
	}
	student >> studentCount;
	student.get(); // consume one char

	for (int i = 0; i < studentCount; i++) {
		getline(student, students[i].rollNo, '|');  // rollNo up to '|'
		student.getline(students[i].name, 50, '|'); // name (char[]) up to '|'
		getline(student, students[i].section, '|'); // section up to '|'

		// Read the numbers on the remainder of the line
		student >> students[i].quiz[0]
			>> students[i].quiz[1]
			>> students[i].quiz[2]
			>> students[i].assignment[0]
			>> students[i].assignment[1]
			>> students[i].mids
			>> students[i].finals;

		// Consume the end-of-line
		student.get();
		calculateGrade(students[i]);
	}
	cout << "Data loaded successfully. Total students: " << studentCount << '\n';
}

// this updates the data of an existing student thats why I am using students[array] and not the structure
void updateStudent() { // works on same concept as addStudent() function 
	if (studentCount == 0) {
		cout << "No student data exists.\n";
		return;
	}
		cout << "Enter Roll Number of an existing student (0-9999): ";
		cin >> roll;
	for (int i = 0; i < studentCount; i++) { // this loop checks roll number with all stored students
		if (roll == students[i].rollNo) { // checks if student of such roll number really exists
			cout << "Enter new Student Name: ";
			cin.ignore();
			cin.getline(students[i].name, 50);
			while (!isNameValid(students[i].name)) {
				cout << "Number must not contain numbers or special characters\n";
				cout << "Enter Student Name: ";
				cin.ignore();
				cin.getline(students[i].name, 50);
			}
			cout << "Enter new Student Section (A-F): ";
			cin >> students[i].section;
			while (!isSectionValid(students[i].section)) {
				cout << "Invalid input! Must be a single alphabet from A-F\n";
				cout << "Enter new Student Section (A-F): ";
				cin >> students[i].section;
			}
			for (int j = 0; j < 3; j++) {
			labelQ1:
				cout << "Enter marks of Quiz " << j + 1 << ": ";
				cin >> students[i].quiz[j]; // using j and not i so it does not update marks for diff students
				if (students[i].quiz[j] < 0 || students[i].quiz[j] > 10) {
					cout << "Invalid!\n";
					goto labelQ1;
				}
			}
			for (int j = 0; j < 2; j++) {
			labelQ2:
				cout << "Enter marks of Assignment " << j + 1 << ": ";
				cin >> students[i].assignment[j];
				if (students[i].assignment[j] < 0 || students[i].assignment[j] > 10) {
					cout << "Invalid!\n";
					goto labelQ2;
				}
			}
		labelQ3:
			cout << "Enter new Midterm Marks: ";
			cin >> students[i].mids;
			if (students[i].mids<0 || students[i].mids >30) {
				cout << "Invalid!\n";
				goto labelQ3;
			}
		labelQ4:
			cout << "Enter new Final Marks: ";
			cin >> students[i].finals;
			if (students[i].finals < 0 || students[i].finals > 50) {
				cout << "Invalid!\n";
				goto labelQ4;
			}
			calculateGrade(students[i]);
			cout << "Record updated!\n";
			return;
		}
	}
	cout << "Not Found!\n";
}

void deleteStudent() {
	if (studentCount == 0) {
		cout << "No student data found.\n";
		return;
	}
	cout << "Enter roll number of an existing student: ";
	cin >> roll;
	for (int i = 0; i < studentCount; i++) {
		if (roll == students[i].rollNo) {
			for (int j = i; j < studentCount - 1; j++) { 
				students[j] = students[j + 1]; // shifting 
			}
			studentCount--;
			cout << "Record deleted\n";
			save();
			return;
		}
	}
	cout << "No such student found!\n";
}

void display() {
	if (studentCount == 0) {
		cout << "No student data found.\n";
		return;
	}
	cout << left << setw(10) << "RollNo" << setw(20) << "Name" << setw(10) << "Section"
		<< setw(10) << "Percent" << setw(10) << "Grade" << endl;
	for (int i = 0; i < studentCount; i++) {
		cout << left << setw(10) << students[i].rollNo
			<< setw(20) << students[i].name
			<< setw(10) << students[i].section
			<< setw(10) << fixed << setprecision(2) << students[i].percentage
			<< setw(10) << students[i].grade << endl;
	}
}

void displayDetail() {
	if (studentCount == 0) {
		cout << "No student data found.\n";
		return;
	}
	cout << left << setw(10) << "RollNo" << setw(20) << "Name" << setw(10) << "Section"
		<< setw(10) << "Quiz#1" << setw(10) << "Quiz#2" << setw(10) << "Quiz#3"
		<< setw(15) << "Assignment#1" << setw(15) << "Assignment#2" << setw(10) << "Mids"
		<< setw(10) << "Finals" << endl;
	for (int i = 0; i < studentCount; i++) {
		cout << left << setw(10) << students[i].rollNo
			<< setw(20) << students[i].name
			<< setw(10) << students[i].section
			<< setw(10) << students[i].quiz[0]
			<< setw(10) << students[i].quiz[1] << setw(10) << students[i].quiz[2]
			<< setw(15) << students[i].assignment[0]
			<< setw(15) << students[i].assignment[1]
			<< setw(10) << students[i].mids
			<< setw(10) << students[i].finals << endl;
	}
}

void search() {
	if (studentCount == 0) {
		cout << "No student data found.\n";
		return;
	}
	cout << "Enter roll number of an existing student: ";
	cin >> roll;
	for (int i = 0; i < studentCount; i++) {
		if (roll == students[i].rollNo) {
			cout << "Roll No: " << students[i].rollNo << "\nName: " << students[i].name << "\nSection: "
				<< students[i].section << "\nPercentage: " << students[i].percentage
				<< "\nGrade: " << students[i].grade << endl;
			return;
		}
	}
	cout << "No student exists with such roll number.\n";
}

void sort() { 
	if (studentCount == 0) {
		cout << "No record available\n";
		return;
	}
	for (int i = 0; i < studentCount - 1; i++) {
		for (int j = 0; j < studentCount - i - 1; j++) {
			if (students[j].percentage < students[j + 1].percentage) { // descending order
				swap(students[j], students[j + 1]); // swaps whole student data 
			}
		}
	}
	cout << "Sorted by percentage\n";
}

void classStats() {
	if (studentCount == 0) {
		cout << "No record found!\n";
		return;
	}
	int highest = students[0].percentage, lowest = students[0].percentage, sum = 0;
	for (int i = 0; i < studentCount; i++) {
		sum += students[i].percentage;
		if (students[i].percentage > highest) {
			highest = students[i].percentage;
		}
		if (students[i].percentage < lowest) {
			lowest = students[i].percentage;
		}
	}
	cout << "Highest percentage: " << highest;
	cout << "\nLowest percentage: " << lowest;
	cout << "\nClass average: " << sum / studentCount << endl;
	cout << "Topper:\n";
	// using same setw values as in display function
	cout << left << setw(10) << "RollNo" << setw(20) << "Name" << setw(10) << "Section"
		<< setw(10) << "Percent" << setw(10) << "Grade" << endl; 
	int topper = 0; // to store index in array
	for (int i = 0; i < studentCount; i++) { // to display data of topper
		if (students[i].percentage > students[topper].percentage) {
			topper = i;
		}
	}
	cout << left << setw(10) << students[topper].rollNo
		<< setw(20) << students[topper].name
		<< setw(10) << students[topper].section
		<< setw(10) << fixed << setprecision(2) << students[topper].percentage
		<< setw(10) << students[topper].grade << endl;
}

void quizAvg() {
	if (studentCount == 0) {
		cout << "No student found!\n";
		return;
	}

	double quizSum[3] = { 0 }, assignSum[2] = { 0 }, midsSum = 0, finalSum = 0;
	for (int i = 0; i < studentCount; i++) { // of all stored students 
		for (int j = 0; j < 3; j++) {
			quizSum[j] += students[i].quiz[j]; // sum to find avg, for each quiz 
		}
		for (int k = 0; k < 2; k++) {
			assignSum[k] += students[i].assignment[k]; // sum to find avg, for each assignment 
		}
		midsSum += students[i].mids;
		finalSum += students[i].finals;
	}
	// prinitng
	cout << fixed << setprecision(2);
	for (int j = 0; j < 3; j++) cout << "Quiz " << j + 1 << " average: " << quizSum[j] / studentCount << endl;
	for (int k = 0; k < 2; k++) cout << "Assignment " << k + 1 << " average: " << assignSum[k] / studentCount << endl;
	cout << "Mids average: " << midsSum / studentCount << endl;
	cout << "Finals average: " << finalSum / studentCount << endl;
}


int main() {
	load();
	int choice;
	do {
		cout << "Student Performance Management System (SPMS)\n";
		cout << "Choose one option\n";
		cout << "1. Add a Student\n";
		cout << "2. Update a Student\n";
		cout << "3. Delete a Student\n";
		cout << "4. Display Records Along Percentage and Grade\n";
		cout << "5. Display All Records in Detail\n";
		cout << "6. Search Student by Roll No\n";
		cout << "7. Sort by Percentage\n";
		cout << "8. Class Stats\n";
		cout << "9. Quizzes Average\n";
		cout << "10. Save & Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1: addStudent();
			break;
		case 2: updateStudent();
			break;
		case 3: deleteStudent();
			break;
		case 4:
			display();
			break;
		case 5:
			displayDetail();
			break;
		case 6: search();
			break;
		case 7: sort();
			break;
		case 8: classStats();
			break;
		case 9: quizAvg();
			break;
		case 10: save();
			break;
		default:
			cout << "Invalid choice.\n";
		}
	} while (choice != 10);
}