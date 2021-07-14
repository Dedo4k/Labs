#pragma once
#include "File.h"

template<typename T>
class BinaryFile : public File
{
private:
	fstream FileStream;
public:
	BinaryFile(const string = "");
	bool openToInput();
	bool openToOutput();
	void rewindFile();
	void inputToFile(T& Object);
	void outputToFile(T& Object);
	bool endFile();
	~BinaryFile();
};
