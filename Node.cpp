/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : Node.cpp
Description : Functionality for Node.h
Author : Angus Parsons
Mail : angus.parsons@mds.ac.nz
**************************************************************************/


#include "Node.h"

Node::Node(int KeyIn)
{
	Key = KeyIn;
	Next = nullptr;
	Previous = nullptr;
	Value = 0;
	Position = 0;
	Name = "";
	Type = "";
	Price = 0;
	Quantity = 0;
}

Node::Node(int KeyIn, std::string NameIn, std::string TypeIn, float PriceIn, int QuantityIn)
{
	Key = KeyIn;
	Next = nullptr;
	Previous = nullptr;
	Value = 0;
	Position = 0;
	Name = NameIn;
	Type = TypeIn;
	Price = PriceIn;
	Quantity = QuantityIn;
}

Node::~Node()
{
	Key = 0;
	Next = nullptr;
	Previous = nullptr;
	Value = 0;
}


void Node::SetValue(float ValueIn)
{
	Value = ValueIn;
}


void Node::SetNext(Node* InputNext)
{
	Next = InputNext;
}


void Node::SetPrevious(Node* InputPrevious)
{
	Previous = InputPrevious;
}

void Node::PrintNodeDetails()
{
	std::cout << "Name: " << Name << std::endl;
	std::cout << "Type: " << Type << std::endl;
	std::cout << "Price: " << Price << std::endl;
	std::cout << "Quantity: " << Quantity << std::endl;
}