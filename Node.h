/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : Node.h
Description : Declarations for Node.cpp
Author : Angus Parsons
Mail : angus.parsons@mds.ac.nz
**************************************************************************/


#pragma once
#include <iostream>
class Node
{
public:
	int Key;
	int Position;
	float Value;
	Node* Next;
	Node* Previous;
	Node(int KeyIn);
	Node(int KeyIn, std::string NameIn, std::string TypeIn, float PriceIn, int QuantityIn);
	~Node();
	void SetValue(float ValueIn);
	void SetNext(Node* InputNext);
	void SetPrevious(Node* InputPrevious);
	void PrintNodeDetails();
	std::string Name;
	std::string Type;
	float Price;
	int Quantity;
};

