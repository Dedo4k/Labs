#pragma once

class String
{
private:
	char* str;
	int length;
public:
	explicit String();
	explicit String(int size);
	explicit String(const char* s);					
	String(const String& other);					//����������� �����������
	String(String&& other)noexcept;					//����������� ��������
	~String();
	String &operator=(const String& other);			//�������� ������������
	String operator+(const String& other);			//�������� �����������
	String operator+(const char* word);
	int operator-(const String& other);
	friend String operator+(const char* word, const String& other);
	String &operator+=(const String& other);		//�������� ������������
	String &operator+=(const char* word);
	bool operator==(const String& other);			//�������� �����
	bool operator!=(const String& other);			//�������� �� �����
	bool operator>(const String& other);			//������� ������
	bool operator<(const String& other);			//�������� ������
	char& operator[](int index);					//�������� []
	String operator()(int index, int length);		//�������� ��������� ���������
	void Show();
};

