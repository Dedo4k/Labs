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
	String(const String& other);					//конструктор копирования
	String(String&& other)noexcept;					//конструктор переноса
	~String();
	String &operator=(const String& other);			//опреатор присваивания
	String operator+(const String& other);			//оператор складывания
	String operator+(const char* word);
	int operator-(const String& other);
	friend String operator+(const char* word, const String& other);
	String &operator+=(const String& other);		//оператор увеличивания
	String &operator+=(const char* word);
	bool operator==(const String& other);			//оператор равно
	bool operator!=(const String& other);			//оператор не равно
	bool operator>(const String& other);			//опратор больше
	bool operator<(const String& other);			//оператор меньше
	char& operator[](int index);					//оператор []
	String operator()(int index, int length);		//оператор выделения подстроки
	void Show();
};

