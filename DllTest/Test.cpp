#include "Test.h"

void Test::ReadDataFile(char* address)
{
	char temp[255]; //�ӽ� ���� ��ġ
	char tempAddress[255] = "/test.txt";
	strcpy_s(temp, address); //���ڿ� ���縦 ���ؼ�
	strcat_s(temp, tempAddress); //�ؽ�Ʈ�� �ִ� ���� ����Ƽ ���� ��ġ + ���� �̸� ��ġ��
	ifstream fin(temp); // �����б�
	
	if (!fin.is_open()) //�����б� �����ϸ�
		number= -1;
	fin >> number; //���Ͽ� �ִ� ���� ����

	if (fin.is_open()) //������ �����ִٸ�
		fin.close(); //���� ����
}

void Test::PrintNumber(int* number)
{
	number[0] = this->number; //number���� ��ȯ���� �ּҰ����� ��ȯ�ϴ¹��
}

Test::Test(char* address)
{
	ReadDataFile(address); //�����ڷ� ���������� �б�
}

///exturn���� ����� �Լ�
Test* TEST1ReadDataFile(char* address)
{
	return new Test(address); //�׽�Ʈ Ŭ������ �����ϰ� this ����Ʈ�� ���� ���ؼ� ���Ͻ�����
}

void TEST1PrintNumber(Test* pPoint, int* number)
{
	pPoint->PrintNumber(number); // pPoint �� ��ǻ� test Ŭ������ this ����Ʈ ��Ȱ�� ��
}

