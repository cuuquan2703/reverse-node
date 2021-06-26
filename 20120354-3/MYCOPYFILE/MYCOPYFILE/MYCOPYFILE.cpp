#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
using namespace std;

void writefile(const char* path,char ch)
{
	FILE* fin;
	fin = fopen(path, "ab");
	if (fin != NULL)
	{
		fwrite(&ch,sizeof(char), 1, fin);
	}
	else {
		cout << "Cannot open file" << endl;
	}
	fclose(fin);
}

void readfile(const char* path,const char* filepath)
{
	FILE* fout;
	fout = fopen(path, "rb");
	if (fout != NULL)
	{
		rewind(fout);
		int val = 0;
		do
		{
			char ch;
			fseek(fout, val * sizeof(char), SEEK_SET);
			fread(&ch, sizeof(char), 1, fout);
			writefile(filepath, ch);
			val++;
		} while (!feof(fout));
	}
	else {
		cout << "Cannot open file" << endl;
	};
	fclose(fout);
}


int main(int argc, const char* argv[])
{
	//readfile(argv[1], argv[2]);
	string k = string(argv[1]) + argv[2];
	//cout << k;
	int a = 0, b = 0, c = 0, d = 0;
	a=string(argv[1]).rfind("/");
	b = string(argv[1]).rfind(char(92));
	//cout << a << endl; 
	c = a;
	//cout << b << endl; 
	d = b;
	if (a < b) a = b;
	string str1(string(argv[1]), a + 1, string(argv[1]).length() - (a + 1));
	string str2;
	if (c > 0) str2 = string(argv[2]) + "/" + str1;
	else if (d > 0) str2 = string(argv[2]) + char(92) + str1;
	//cout << str1 << endl;
	cout << str2 << endl;
	char* str3 = new char[string(argv[1]).length() - (a + 1)+1];
	for (int i = 0; i < str2.length(); i++) str3[i] = str2[i];
	readfile(argv[1], str3);
	return 0;
}
