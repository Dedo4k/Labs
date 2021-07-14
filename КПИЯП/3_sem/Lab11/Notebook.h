#pragma once
#include "Portable.h"

class Notebook : public Portable
{
private:
	string graphicCard;
	int GCmodel;
	double weight;
public:
	Notebook();
	~Notebook();
	friend istream& operator>>(istream& in, Notebook& notebook);
	friend ostream& operator<<(ostream& out, Notebook& notebook);
	friend fstream& operator>>(fstream& in, Notebook& notebook);
	friend fstream& operator<<(fstream& out, Notebook& notebook);
	friend ifstream& operator>>(ifstream& in, Notebook& notebook);
	friend ofstream& operator<<(ofstream& out, Notebook& notebook);
	bool operator==(Notebook notebook);
	bool operator>(Notebook notebook);
	bool operator<(const Notebook& cmp)const
	{
		return brand < cmp.brand;
	}
	//bool operator<(Notebook notebook);
	void shapka();
	void setGraphicCard(string graphicCard);
	string getGraphicCard();
	void setGCmodel(int GCmodel);
	void getProc() {};
	int getGCmodel();
	void setWeight(double weight);
	double getWeight();
};