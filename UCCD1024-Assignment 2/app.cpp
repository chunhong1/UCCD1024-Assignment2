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

int main() {

	bool stop = false;
	do {
		system("cls");
		int choice = MainMenu();

		switch (choice) {
		case 1:

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