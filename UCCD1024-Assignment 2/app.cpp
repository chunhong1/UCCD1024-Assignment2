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
bool isDuplicate(BST*, Student&, BTNode*);
int MainMenu();
void center(string);

const char* STUDENT_INFO_FILE = "student.txt";

int main() {
	BST t1;
	type student;
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

			system("pause");
			break;
		case 2:
			if (!t1.deepestNodes())
				cout << "The BST is empty." << endl;

			system("pause");
			break;
		case 3:
			int order, source;
			cout << "Enter order (1-for ascending, 2-for descending):";
			cin >> order;
			if (order != 1 && order != 2) {
				cout << "Invalid order value. Please enter 1-for ascending or 2-for descending." << endl;
				return false;
			}
			cout << "Enter source (1-for screen, 2-for file):";
			cin >> source;
			if (source != 1 && source != 2) {
				cout << "Invalid source value. Please enter 1-for screen or 2-for file." << endl;
				return false;
			}
			if (t1.display(order, source)) {
				cout << "BST has been displayed." << endl;
			}
			else {
				cout << "Failed to display BST." << endl;
			}
			system("pause");
			break;
		case 4:
			cout << "Please enter Student ID you would like to create a cloned subtree for:";
			cin >> student.id;
			if (!t1.CloneSubtree(t1, student)) {
				cout << "Cannot clone subtree" << endl;
			}
			system("pause");

			break;
		case 5:
			if (!t1.printLevelNodes()) 
			{
				cout << "The BST is empty" << endl;;
			}
			
			system("pause");
			break;

		case 6:
			if (t1.printPath()) {
				cout << "Print Path successful." << endl;
			}
			else {
				cout << "BST is empty." << endl;
			}

			system("pause");

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

		//check for duplicate
		if(!isDuplicate(t1, student, t1->root))
			t1->insert(student);
	}
	in.close();
	return true;
}

bool isDuplicate(BST* tree, Student& student, BTNode* cur)
{
	if (tree->empty())
		return false;

	if (cur == NULL)
		return false;

	if (cur->item.id == student.id) {
		return true;
	}

	bool left_found = isDuplicate(tree, student, cur->left);
	bool right_found = isDuplicate(tree, student, cur->right);


	return left_found||right_found;
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