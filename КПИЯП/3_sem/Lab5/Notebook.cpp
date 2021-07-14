#include "Notebook.h"

Notebook::Notebook()
{
	cout << "Notebook constructor" << endl << endl;
	graphicCard = '\0';
	GCmodel = 0;
	weight = 0.0;
}

Notebook::~Notebook()
{
	cout << endl << "Notebook destructor" << endl;
}

void Notebook::setGraphicCard(string graphicCard)
{
	this->graphicCard = graphicCard;
}

string Notebook::getGraphicCard()
{
	return graphicCard;
}

void Notebook::setGCmodel(int GCmodel)
{
	this->GCmodel = GCmodel;
}

int Notebook::getGCmodel()
{
	return GCmodel;
}

void Notebook::setWeight(double weight)
{
	this->weight = weight;
}

double Notebook::getWeight()
{
	return weight;
}

istream& operator>>(istream& in, Notebook& notebook)
{
	Portable* portable;
	portable = &notebook;
	in >> *(dynamic_cast<Portable*>(portable));
	cout << "Enter graphic card - ";
	in >> notebook.graphicCard;
	cout << "Enter graphic card model - ";
	in >> notebook.GCmodel;
	cout << "Enter weight - ";
	in >> notebook.weight;
	return in;
}

ostream& operator<<(ostream& out, Notebook& notebook)
{
	Portable* portable;
	portable = &notebook;
	out << *(dynamic_cast<Portable*>(portable));
	out << "Graphic card: " << notebook.graphicCard << endl;
	out << "Graphic card model: " << notebook.GCmodel << endl;
	out << "Weight: " << notebook.weight << endl;
	return out;
}