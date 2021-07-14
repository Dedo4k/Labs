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
	void setGraphicCard(string graphicCard);
	string getGraphicCard();
	void setGCmodel(int GCmodel);
	int getGCmodel();
	void setWeight(double weight);
	double getWeight();
};