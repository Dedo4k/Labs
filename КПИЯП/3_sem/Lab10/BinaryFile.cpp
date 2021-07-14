#include "BinaryFile.h"


template<typename T>
BinaryFile<T>::BinaryFile(const string name) : File(name) { }

template<typename T>
bool BinaryFile<T>::openToInput()
{
	this->FileStream.open(this->fileName, ios::out | ios::binary);
	if (!this->FileStream) {
		cout << endl << "File Error" << endl;
		return false;
	}
	return true;
}

template<typename T>
bool BinaryFile<T>::openToOutput()
{
	this->FileStream.open(this->fileName, ios::in | ios::binary);
	if (!this->FileStream) {
		cout << endl << "File Error" << endl;
		return false;
	}
	return true;
}

template<typename T>
inline void BinaryFile<T>::rewindFile()
{
	this->FileStream.seekg(0, ios::beg);
	this->FileStream.clear();
	//this->fileIStream.clear();
	//this->fileOStream.clear();
}

template<typename T>
inline void BinaryFile<T>::inputToFile(T& Object)
{
	this->FileStream << Object;
}

template<typename T>
inline void BinaryFile<T>::outputToFile(T& Object)
{
	this->FileStream >> Object;
}

template<typename T>
inline bool BinaryFile<T>::endFile()
{
	if (this->FileStream.eof())
		return true;
	else
		return false;
}

template<typename T>
inline BinaryFile<T>::~BinaryFile()
{
	this->FileStream.close();
}
