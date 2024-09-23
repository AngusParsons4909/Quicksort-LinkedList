/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : LinkedList.h
Description : Declarations for LinkedList.cpp
Author : Angus Parsons
Mail : angus.parsons@mds.ac.nz
**************************************************************************/


#pragma once
#include "Node.h"

class LinkedList
{
protected:
	
public:
	Node* Head; //pointer to head node of the list
	Node* Tail;
	std::string Name;
	int Size; //number of nodes in the list
	LinkedList(std::string NameIn);
	~LinkedList();

	void InsertHead(Node* Node);
	void InsertTail(Node* Node);
	void InsertBody(Node* Node, int PositionIn);

	void DeleteHead();
	void DeleteTail();
	void DeleteBody(int PositionIn);

	Node* GetNode(int PositionIn);
	Node* FindNode(int KeyIn);
	bool NodeExists(int KeyIn);

	void SwapNodes(Node* Node1, Node* Node2);
	void PlaceNodeBack(Node* Node, int Position);
	void PlaceNodeFoward(Node* Node, int Position);
	void PrintList();
	void NodeDetails();
	bool Sorted();

	void IncrementNodePosition(int StartingPos);
	void SaveToFile(std::string Path);
};