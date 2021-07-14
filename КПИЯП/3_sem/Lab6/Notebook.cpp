#include "Notebook.h"
#include "MyExc_Vvod.h"

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

void Notebook::shapka()
{
	cout << endl << "|" << setw(7) << "Brand " << "|" << setw(9) << "Battery " << "|" << setw(14) << "Graphic card " << "|" << setw(9) << "GC model " << "|" << setw(8) << "Weight " << "|" << endl;
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
	bool fl;
	Portable* portable;
	portable = &notebook;
	in >> *(dynamic_cast<Portable*>(portable));
	cout << endl << "Enter graphic card - ";
	notebook.graphicCard = MyExc_Vvod::Check_string(13);
	cout << endl << "Enter graphic card model - ";
	notebook.GCmodel = MyExc_Vvod::Check_int();
	cout << endl << "Enter weight - ";
	notebook.weight = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, Notebook& notebook)
{
	Portable* portable;
	portable = &notebook;
	out << *(dynamic_cast<Portable*>(portable));
	out << "|" << setw(14) << notebook.graphicCard << "|" << setw(9) << notebook.GCmodel << "|" << setw(8) << notebook.weight << "|" << endl;
	return out;
}