#pragma once
class Array
{
private:
	int* ms;
	int size;
public:
	Array();								//�����������
	Array(int size);						//����������� � �����������
	Array(const Array& other);				//����������� ������������
	~Array();								//����������
	void add();								//������� ���������� �������� � ������
	void show();							//������� ������ ��������� �������
	//int getSize();						//������� ��������� ������� �������
	//int getMs(int i);						//������� ��������� �������� �������
	Array operator&(const Array& b);		//������� �����������
	Array &operator=(const Array& b);		//������� ������������
	Array crossing(Array& b);
};

