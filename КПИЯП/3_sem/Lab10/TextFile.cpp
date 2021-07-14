#include "TextFile.h"

template<typename T>
inline TextFile<T>::TextFile(const string name) : File(name) {}

template<typename T>
bool TextFile<T>::openToInput()
{
	this->fileOStream.open(this->fileName, ios::out);
	if (!this->fileOStream) {
		cout << endl << "File Error" << endl;
		return false;
	}
	return true;
}

template<typename T>
bool TextFile<T>::openToOutput()
{
	this->fileIStream.open(this->fileName, ios::in);
	if (!this->fileIStream) {
		cout << endl << "File Error" << endl;
		return false;
	}
	return true;
}

template<typename T>
bool TextFile<T>::openToAdd()
{
	this->fileOStream.open(this->fileName, ios::app | ios::out);
	if (!this->fileOStream) {
		cout << endl << "File Error" << endl;
		return false;
	}
	return true;
}

template<typename T>
void TextFile<T>::rewindFile()
{
	this->fileIStream.seekg(0, ios::beg);
	this->fileOStream.seekp(0, ios::beg);
	this->fileIStream.clear();
	this->fileOStream.clear();
}

template<typename T>
void TextFile<T>::inputToFile(T& Object)
{
	this->fileOStream << Object;
}

template<typename T>
void TextFile<T>::outputToFile(T& Object)
{
	this->fileIStream >> Object;
}

template<typename T>
bool TextFile<T>::endFile()
{
	if (this->fileIStream.eof())
		return true;
	else
		return false;
}

template<typename T>
TextFile<T>::~TextFile()
{
	this->fileIStream.close();
	this->fileOStream.close();
}
