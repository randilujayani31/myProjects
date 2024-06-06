#include <iostream>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;

class Student
{
	private:
    int rollno;
	char name[20];
	char course[20];
	char gender[10];
	int age;
	int stand;

	public:
		char *getName()
		{
			return name;
		}

	int getRollNo()
	{
		return rollno;
	}

	void getData()
	{
		cout << "Student Details\n";

		cout << "Roll No:";
		cin >> rollno;

		cout << "Name:";
		cin >> name;

		cout << "Course:";
		cin >> course;

		cout << "Gender:";
		cin >> gender;

		cout << "Age:";
		cin >> age;

		cout << "Standard:";
		cin >> stand;

		// Open file for writing
		ofstream myfile;
		myfile.open("data.txt", ios::app);

		// Write data to file in table format
		myfile << rollno << "\t" << name << "\t" << course << "\t" << gender << "\t" << age << "\t" << stand << endl;

		// Close file
		myfile.close();

        //here
	}

	void showData()
	{
		ifstream infile;
		infile.open("data.txt");
		if (!infile)
		{
			cerr << "Unable to open file data.txt";
			exit(1);
		}

		cout << setw(15) << "Roll Number" << setw(20) << "Name" <<
			setw(20) << "Course" << setw(10) << "Gender" << setw(5) << "Age" << setw(10) << "Standard" << endl;

		while (infile >> rollno >> name >> course >> gender >> age >> stand)
		{
			cout << setw(15) << rollno << setw(20) << name <<
				setw(20) << course << setw(10) << gender << setw(5) << age << setw(10) << stand << endl;
		}

		infile.close();	// Don't forget to close the file

	}

	void searchByRollNo(int rollNumber)
	{
		ifstream infile;
		infile.open("data.txt");
		if (!infile)
		{
			cerr << "Unable to open file data.txt";
			exit(1);
		}

		bool found = false;

		while (infile >> rollno >> name >> course >> gender >> age >> stand)
		{
			if (rollNumber == rollno)
			{
				found = true;
				cout << "Student Details\n";
				cout << "Roll Number: " << rollno << endl;
				cout << "Name: " << name << endl;
				cout << "Course: " << course << endl;
				cout << "Gender: " << gender << endl;
				cout << "Age: " << age << endl;
				cout << "Standard: " << stand << endl;
				break;
			}
		}

		infile.close();

		if (!found)
		{
			cout << "Student with Roll Number " << rollNumber << " not found." << endl;
		}

		getch();
	}

	void searchByName(const char *searchName)
	{
		ifstream infile;
		infile.open("data.txt");
		if (!infile)
		{
			cerr << "Unable to open file data.txt";
			exit(1);
		}

		bool found = false;

		while (infile >> rollno >> name >> course >> gender >> age)
		{
			if (strcmp(searchName, name) == 0)
			{
				found = true;
				cout << "Student Details\n";
				cout << "Roll Number: " << rollno << endl;
				cout << "Name: " << name << endl;
				cout << "Course: " << course << endl;
				cout << "Gender: " << gender << endl;
				cout << "Age: " << age << endl;
				cout << "Standarad" << stand << endl;
				break;
			}
		}

		infile.close();

		if (!found)
		{
			cout << "Student with name \"" << searchName << "\" not found." << endl;
		}

		getch();
	}

	void modifyByRollNo(int rollNumber)
	{
		fstream file;
		file.open("data.txt", ios:: in | ios::out);
		if (!file)
		{
			cerr << "Unable to open file data.txt";
			exit(1);
		}

		bool found = false;

		while (file >> rollno >> name >> course >> gender >> age>>stand)
		{
			if (rollNumber == rollno)
			{
				found = true;
				cout << "Modify Student Details\n";
				cout << "Roll Number: " << rollno << endl;
				cout << "Name: " << name << endl;
				cout << "Course: " << course << endl;
				cout << "Gender: " << gender << endl;
				cout << "Age: " << age << endl;
				cout<<"Standard: "<<stand<<endl;

				cout << "\nEnter new details:\n";
				cout << "Name:";
				cin >> name;
				cout << "Course:";
				cin >> course;
				cout << "Gender:";
				cin >> gender;
				cout << "Age:";
				cin >> age;
				cout<<"Standard:";
				cin>>stand;

				// Move file pointer back to the beginning of the record
				file.seekp(file.tellg() - streamoff(sizeof(rollno) + sizeof(name) + sizeof(course) + sizeof(gender) + sizeof(age)));
				// Write updated data
				file << setw(10) << rollno << setw(20) << name << setw(20) << course << setw(10) << gender << setw(5) << age;

				break;
			}
		}

		file.close();

		if (!found)
		{
			cout << "Student with Roll Number " << rollNumber << " not found." << endl;
		}

		getch();
	}

	void deleteRecordByRollNo(int rollNumber)
	{
		ifstream infile("data.txt");
		if (!infile)
		{
			cerr << "Unable to open file data.txt";
			exit(1);
		}

		ofstream tempFile("temp.txt");
		if (!tempFile)
		{
			cerr << "Unable to create temporary file temp.txt";
			exit(1);
		}

		bool found = false;

		while (infile >> rollno >> name >> course >> gender >> age>>stand)
		{
			if (rollNumber == rollno)
			{
				found = true;
				cout << "Student Details Deleted:\n";
				cout << "Roll Number: " << rollno << endl;
				cout << "Name: " << name << endl;
				cout << "Course: " << course << endl;
				cout << "Gender: " << gender << endl;
				cout << "Age: " << age << endl;
				cout<<"Standard: "<<stand<<endl;
			}
			else
			{
				tempFile << setw(10) << rollno << setw(20) << name << setw(20) << course << setw(10) << gender << setw(5) << age << setw(10)<< stand<<endl;
			}
		}

		infile.close();
		tempFile.close();

		if (!found)
		{
			cout << "Student with Roll Number " << rollNumber << " not found." << endl;
		}
		else
		{
			remove("data.txt");	// Delete the original file
			rename("temp.txt", "data.txt");	// Rename the temporary file
		}

		getch();
	}
};

class mainclass
{
	public:
		void menu()
		{
			cout << "\nSTUDENT RECORDS\n";
			cout << "===============\n";
			cout << "0.Exit\n";
			cout << "1.Register New Student\n";
			cout << "2.Show All Students\n";
			cout << "3.Search by roll No:\n";
			cout << "4.Search by Name:\n";
			cout << "5.Modify Record:\n";
			cout << "6.Delete Record:\n";

			cout << "Enter your choice:\n";
			maintanor();
		}

	int maintanor()
	{
		int n = 0, ch, rn, i, flag = 0, pos;
		Student s[10];
		//system("cls");
		//menu();
		cin >> ch;
		switch (ch)
		{
			case 1:
				s[n].getData();
				cout << "\nRecord saved successfully...\n";
				getch();
				system("cls");
				getch();
				menu();//now
				break;

			case 2:

				s[n].showData();
				getch();
				system("cls");
				getch();
				menu();
				break;

			case 3:
				cout << "\nEnter roll No. to display:";
				cin >> rn;
				s[n].searchByRollNo(rn);
				getch();
				system("cls");
				getch();
				menu();

				break;
			case 4:
				char searchName[20];
				cout << "\nEnter name to display:";
				cin >> searchName;
				s[n].searchByName(searchName);
				getch();
				system("cls");
				getch();
				menu();
				break;

			case 5:
				int modifyRollNo;
				cout << "\nEnter roll No. to modify:";
				cin >> modifyRollNo;
				s[n].modifyByRollNo(modifyRollNo);
				getch();
				system("cls");
				getch();
				menu();
				break;
			case 6:
				int deleteRollNo;
				cout << "\nEnter roll No. to delete:";
				cin >> deleteRollNo;
				s[n].deleteRecordByRollNo(deleteRollNo);
				getch();
				system("cls");
				getch();
				menu();
				break;

			case 0:
				exit(0);

			default:
				cout << "\nInvalid Choise..\n";
				cout << "\n\nPress any key to continue.....\n";
				getch();
				menu();
		}
	}
};

int main()
{
	//Student s;
	mainclass m;
	m.menu();
	return 0;
}
