#include "String.h"
#include <cstring>
#include <iostream>
using namespace std;

String::String()
{
	str = nullptr;
	length = 0;
}

String::String(int size)
{
	this->str = new char[size+1];
	length = size;
}

String::String(const char* str)
{
	length = strlen(str);
	this->str = new char[length + 1];
	for (int i = 0; i < length; i++)
		this->str[i] = str[i];
	this->str[length] = '\0';
}

String::String(const String& other)
{
	length = strlen(other.str);
	this->str = new char[length+1];
	for (int i = 0; i < length; i++)
		this->str[i] = other.str[i];
	this->str[length] = '\0';
}

String::String(String&& other)noexcept
{
	this->length = other.length;
	this->str = other.str;
	other.str = nullptr;
}

String::~String()
{
	delete[]str;
}

String& String::operator=(const String& other)
{
	if (this->str)
		delete[]str;
	length = strlen(other.str);
	this->str = new char[length+1];
	for (int i = 0; i < length; i++)
		this->str[i] = other.str[i];
	this->str[length] = '\0';
	return*this;
}

String String::operator+(const String& other)
{
	String temp;
	int j = 0;
	temp.length = strlen(this->str) + strlen(other.str);
	temp.str = new char[temp.length+1];
	for (int i = 0; i < strlen(this->str); i++)
		temp.str[i] = this->str[i];
	for (int i = strlen(this->str); i < temp.length; i++)
	{
		temp.str[i] = other.str[j];
		j++;
	}
	temp.str[temp.length] = '\0';
	return temp;
}

String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

String String::operator+(const char* word)
{
	String temp;
	int j = 0;
	temp.length = strlen(this->str) + strlen(word);
	temp.str = new char[temp.length + 1];
	for (int i = 0; i < strlen(this->str); i++)
		temp.str[i] = this->str[i];
	for (int i = strlen(this->str); i < temp.length; i++)
	{
		temp.str[i] = word[j];
		j++;
	}
	temp.str[temp.length] = '\0';
	return temp;
}

int String::operator-(const String& other)
{
	return this->length-other.length;
}

String operator+(const char* word, const String& other)
{
	String temp;
	int i = 0, j = 0;
	temp.length = strlen(word) + other.length;
	temp.str = new char[temp.length+1];
	for (; i < strlen(word); i++)
		temp.str[i] = word[i];
	for (i, j; i < temp.length; i++, j++)
		temp.str[i] = other.str[j];
	temp.str[temp.length] = '\0';
	return temp;
}

String& String::operator+=(const char* word)
{
	return *this = *this + word;
}

bool String::operator==(const String& other)
{
	if (this->length != other.length)
		return false;
	for (int i = 0; i < this->length; i++)
		if (this->str[i] != other.str[i])
			return false;
	return true;
}

bool String::operator!=(const String& other)
{
	return !(this->operator==(other));
}

bool String::operator>(const String& other)
{
	if (this->length < other.length)
		return false;
	for (int i = 0; i < this->length; i++)
		if (this->str[i] < other.str[i])
			return false;
	return true;
}

bool String::operator<(const String& other)
{
	return !(this->operator>(other));
}

char& String::operator[](int index)
{
	return(this->str[index]);
}

String String::operator()(int index, int length)
{
	String temp(length);
	int j = 0;
	for (int i = index; i < index+length; i++,j++)
	{
		temp.str[j] = this->str[i];
	}
	temp.str[length] = '\0';
	return temp;
}

void String::Show()
{
	if(str)
		cout << str << endl;
}