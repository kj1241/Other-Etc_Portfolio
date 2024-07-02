#include "Test.h"

void Test::ReadDataFile(char* address)
{
	char temp[255]; //임시 저장 위치
	char tempAddress[255] = "/test.txt";
	strcpy_s(temp, address); //문자열 복사를 위해서
	strcat_s(temp, tempAddress); //텍스트가 있는 곳의 유니티 절대 위치 + 파일 이름 합치기
	ifstream fin(temp); // 파일읽기
	
	if (!fin.is_open()) //파일읽기 실패하면
		number= -1;
	fin >> number; //파일에 있는 수를 읽음

	if (fin.is_open()) //파일이 열려있다면
		fin.close(); //파일 닫음
}

void Test::PrintNumber(int* number)
{
	number[0] = this->number; //number값을 반환해줌 주소값으로 반환하는방법
}

Test::Test(char* address)
{
	ReadDataFile(address); //생성자로 데이터파일 읽기
}

///exturn으로 선언된 함수
Test* TEST1ReadDataFile(char* address)
{
	return new Test(address); //테스트 클래스를 생성하고 this 포인트를 쓰기 위해서 리턴시켜줌
}

void TEST1PrintNumber(Test* pPoint, int* number)
{
	pPoint->PrintNumber(number); // pPoint 는 사실상 test 클래스의 this 포인트 역활을 함
}

