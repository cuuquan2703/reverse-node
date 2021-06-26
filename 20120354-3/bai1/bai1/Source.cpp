#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
#include<string>

struct date
{
	int day;
	int month;
	int year;
};

using namespace std;

void input_dates(date& key)
{
	int n = 0;
	cout << "Enter number of elements: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "-Day: "; cin >> key.day;
		cout << "-Month: "; cin >> key.month;
		cout << "-Year: "; cin >> key.year;
		cout << endl;
	};
}

void writefile(const char* path)
{
	FILE* fin;
	fin = fopen(path, "wb");
	date key;
	if (fin != NULL)
	{
		int n = 0;
		cout << "Enter number of elements: "; cin >> n; fwrite(&n, sizeof(int), 1, fin);
		date* arr = new date[n];
		for (int i = 0; i < n; i++)
		{
			cout << "-Day: "; cin >> arr[i].day;
			cout << "-Month: "; cin >> arr[i].month;
			cout << "-Year: "; cin >> arr[i].year;
			cout << endl;
		};
		fwrite(arr, sizeof(date), n, fin);
	}
	else {
		cout << "Cannot save" << endl;
	}
	fclose(fin);
}
void readfile(const char* path)
{
	FILE* fout;
	fout = fopen(path, "rb");

	if (fout != NULL)
	{
		int n;
		date newest_day;
		fseek(fout, 0L, SEEK_SET); fread(&n, sizeof(int), 1, fout); cout << "Newestday: "<< endl;
		fseek(fout, (n-1)  * sizeof(date)+sizeof(int), SEEK_SET); fread(&newest_day, sizeof(date), 1, fout);
		cout << newest_day.day << "/" << newest_day.month << "/" << newest_day.year << endl;
	}
	else {
		cout << "Cannot load" << endl;
	};
	fclose(fout);
}


int main_menu()
{
	system("cls");
	cout << "1.Enter an array of dates" << endl;
	cout << "2.Load an array of dates" << endl;
	cout << "3.Exit" << endl;
	return 3;
}
int _COMMAND(int cmt) {
	bool check;
	int n;
	do {
		cout << "Your choice : ";
		cin >> n;
		check = cin.fail();
		if (check == true)
		{
			cin.clear();
			cin.ignore();
		}
	} while (check == true || n > cmt || n < 0);
	return n;
};
int sub_menu_1()
{
	system("cls");
	char* path = const_cast<char*>("input.bin");
	writefile(path);
	return 1;
}
int sub_menu_2()
{
	system("cls");
	char* path = const_cast<char*>("input.bin");
	readfile(path);
	return 2;
}

int run_mainmenu(int n)
{
	if (n == 1)
	{
		sub_menu_1();
		system("pause");
	}
	else if (n == 2)
	{
		sub_menu_2();
		system("pause");
	}
	else
		return 3;
}

int main() 
{
	int check = 0;
	do
	{
		check = run_mainmenu(_COMMAND(main_menu()));

	} while (check != 3);
	return 0;
}