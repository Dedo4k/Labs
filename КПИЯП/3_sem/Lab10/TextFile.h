#pragma once
#include "File.h"

template<typename T>
class TextFile : public File
{
private:
	ifstream fileIStream;
	ofstream fileOStream;
public:
	TextFile(const string name);
	bool openToInput();
	bool openToOutput();
	bool openToAdd();
	void rewindFile();
	void inputToFile(T& Object);
	void outputToFile(T& Object);
	bool endFile();

	~TextFile();
};

