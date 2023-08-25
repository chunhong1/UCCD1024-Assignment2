#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include   <iomanip>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int Mainmenu();
void center();

int MainMenu();
void center(string);

const char* STUDENT_INFO_FILE = "student.txt";

int main() {
	BST t1;

	bool stop = false;
	do {
		system("cls");
		int choice = MainMenu();

		switch (choice) {
		case 1:
			if (readFile(STUDENT_INFO_FILE, &t1))
				cout << t1.count << " records have been successfully read." << endl;
			else
				cout << STUDENT_INFO_FILE << " is not found." << endl;

			t1.topDownLevelTraversal();

			system("pause");
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;

		case 6:

			break;

		case 7:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			system("pause");


		}
		cin.clear(256, '/n');
		cin.ignore();
	} while (!stop);
	return 0;
}

bool readFile(const char* filename, BST* t1)
{
	ifstream in;
	char text[256];
	Student student;

	in.open(filename);
	

	//return false if the file is not found
	if (!in)
		return false;
	
	while (!in.eof())
	{
		for (int i = 0; i < 3; i++)
			in >> text;

		in >> student.id;

		for (int i = 0; i < 2; i++)
			in >> text;

		in >> student.name;
		in.getline(text, 256);
		strcat_s(student.name, text);

		for (int i = 0; i < 2; i++)
			in >> text;

		in >> student.address;
		in.getline(text, 256);
		strcat_s(student.address, text);

		for (int i = 0; i < 2; i++)
			in >> text;

		in >> student.DOB;

		for (int i = 0; i < 3; i++)
			in >> text;

		in >> student.phone_no;

		for (int i = 0; i < 2; i++)
			in >> text;

		in >> student.course;

		for (int i = 0; i < 2; i++)
			in >> text;

		in >> student.cgpa;

		t1->insert(student);
	}
	in.close();
	return true;
}

void center(string string) {
	const int WIDTH = 115;
	int space = (WIDTH - string.length()) / 2;
	cout << setw(space + string.length()) << string << endl;
}

int MainMenu() {


	int operation;
	center("Binary Search Tree");
	center("Main Menu");
	center("Please select an option:          ");
	center("1. Read Data to BST               ");
	center("2. Print Deepest Nodes            ");
	center("3. Display Student                ");
	center("4. Clone Subtree                  ");
	center("5. Print Level Nodes              ");
	center("6. Print Path                     ");
	center("7. Exit                           ");
	cout << "Enter an operation: ";
	cin >> operation;

	return operation;
}