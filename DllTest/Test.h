#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Test
{
public :
	void ReadDataFile(char* address);
	void PrintNumber(int* number);
	
	Test(char* address);

private:
	string stAddress;
	int number;
};

extern "C" __declspec(dllexport) Test * TEST1ReadDataFile(char* address);
extern "C" __declspec(dllexport) void TEST1PrintNumber(Test * pPoint, int* number);