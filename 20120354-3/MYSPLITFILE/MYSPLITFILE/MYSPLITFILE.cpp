#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
//Lấy kích thước một file
long size_of_file(const char* path)
{
	FILE* f;
	f = fopen(path, "rb");
	rewind(f);
	fseek(f, 0L, SEEK_END);
	long size = ftell(f);
	fclose(f);
	return size;
}
//Tách tên file ra khỏi đường dẫn (ex: "text.txt)
string get_file_name(const char* argv1,const char* argv2)
{
	string k = string(argv1) + argv2;
	//cout << k;
	int a = 0, b = 0, c = 0, d = 0;
	a = string(argv1).rfind("/");
	b = string(argv1).rfind(char(92));
	c = a;
	d = b;
	if (a < b) a = b;
	string str1(string(argv1), a + 1, string(argv1).length() - (a + 1));
	string str2;
	if (c > 0) str2 = string(argv2) + "/" + str1;
	else if (d > 0) str2 = string(argv2) + char(92) + str1;

	//cout << str2 << endl;
	//char* str3 = new char[string(argv1).length() - (a + 1) + 1];
	//for (int i = 0; i < str2.length(); i++) str3[i] = str2[i];
	//char* str3 = new char[str2.length() + 1];
//	strcpy(str3, str2.c_str());
	return str2;
}
//Tạo các tên file thành phần (ex: text.txt.1, text.txt.2,...)
char* get_part_name(const char* argv1, const char* argv2,int i)
{
	string str = get_file_name(argv1, argv2);
	int tem = i;
	string s = to_string(tem);
	char const* chr = s.c_str();
	cout << chr << endl;
	str = str + ".";
	str = str + chr;
	char* part_name = new char[str.length() + 1];
	strcpy(part_name, str.c_str());
	cout << part_name << endl;
	return part_name;
}
//Tạo space bù cho file 
void add_space(const char* path,int a)
{
	FILE* fp = fopen(path, "ab");
	int  tem = a - (size_of_file(path) % 3);
	for (int i = 0; i < tem; i++)
	{
		char  ch = ' ';
		fwrite(&ch, sizeof(char), 1, fp);
	};
	fclose(fp);
}

void numpart(const char* argv1, const char* argv2, int a)
{
	int n = 0;
	long size = size_of_file(argv1);
	n = size / a; cout << n << endl;
	cout << size_of_file(argv1);
	int val = 0;
	add_space(argv1, a);
	for (int i = 0; i < a; i++)
	{
		char* part_name;
		part_name = get_part_name(argv1, argv2, i);
		FILE* fin = fopen(argv1, "rb");
		FILE* fout = fopen(part_name, "wb");
		int w = 0;
		while (w <= n)
		{

			char ch;
			fseek(fin, val * sizeof(char), SEEK_SET);
			fread(&ch, sizeof(char), 1, fin);
			fwrite(&ch, sizeof(char), 1, fout);
			val++;
			w++;
		}
		cout << size_of_file(part_name) << endl;
		fclose(fin);
		fclose(fout);
	}
}

void sizeapart(const char* argv1, const char* argv2, int b)
{
	int n = 0, val = 0;
	long size = size_of_file(argv1);
	n = size / b;
	add_space(argv1, b);
	for (int i = 0; i < n; i++)
	{
		char* part_name;
		part_name = get_part_name(argv1, argv2, i);
		FILE* fin = fopen(argv1, "rb");
		FILE* fout = fopen(part_name, "wb");
		int w = 0;
		while (w <= b)
		{
			char ch;
			fseek(fin, val * sizeof(char), SEEK_SET);
			fread(&ch, sizeof(char), 1, fin);
			fwrite(&ch, sizeof(char), 1, fout);
			val++;
			w++;
		}
		cout << size_of_file(part_name) << endl;
		fclose(fin);
		fclose(fout);
	}
}


int main(int argc, const char* argv[])
{
	int a = 0, b = 0;
	long size = size_of_file(argv[1]);
	if (strcmp(argv[3], "-numpart") == 0)
	{
		a = atoi(argv[4]); cout << a << endl;
		numpart(argv[1], argv[2], a);
	
	}
	else if (strcmp(argv[3], "-sizeapart") == 0)
	{
		b = atoi(argv[4]);
		sizeapart(argv[1], argv[2], b);
	}
	else cout << "Invalid argument" << endl;
	return 0;
}