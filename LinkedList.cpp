/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : LinkedList.cpp
Description : Functionality for LinkedList.h
Author : Angus Parsons
Mail : angus.parsons@mds.ac.nz
**************************************************************************/

#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList(std::string NameIn)
{
	Head = nullptr;
	Tail = nullptr;
	Size = 0;
	Name = NameIn;
}

LinkedList::~LinkedList()
{
	/*
	Node* DeleteNode = Head;
	Node* Next = nullptr;
	if (Size > 1)
	{
		while (DeleteNode != Tail)
		{			
			std::cout << DeleteNode->Value << std::endl;
			Next = DeleteNode->GetNext();
			delete DeleteNode;
			DeleteNode = Next;
		}
	}
	else
	{
		delete DeleteNode;
	}*/
}

void LinkedList::IncrementNodePosition(int StartingPos)
{
	Node* IncrementNode = GetNode(StartingPos);
	for (int i = 0; i < Size and IncrementNode->Next != nullptr; i++)
	{
		IncrementNode->Position++;
		IncrementNode = IncrementNode->Next;
	}
	IncrementNode->Position++;
	IncrementNode = IncrementNode->Next;
}

void LinkedList::InsertHead(Node* NewNode)
{
	if (Head != nullptr)
	{
		NewNode->SetNext(Head);
	}
	Head = NewNode;
	Size++;
	if (Size == 2)
	{
		(Head->Next)->SetNext(nullptr);
		Tail = Head->Next;
	}
	IncrementNodePosition(1);
	Head->Position = 1;
}

void LinkedList::InsertTail(Node* NewNode)
{
	if (Size > 0)
	{
		if (Tail != nullptr)
		{
			NewNode->SetPrevious(Tail);
			Tail->SetNext(NewNode);
			Tail = NewNode;
		}
		else
		{
			Tail = NewNode;
		}
	}
	else
	{
		Head = NewNode;
	}
	Size++;
	if (Size == 2)
	{
		if (Head != nullptr)
		{
			Head->SetNext(Tail);
			Tail->SetPrevious(Head);
		}
	}
	else if (Size > 2)
	{
		Node* Prev = Tail->Previous;
		Prev->SetNext(Tail);
	}
	NewNode->Position = Tail->Previous->Position + 1;
	
}
void LinkedList::InsertBody(Node* NewNode, int PositionIn)
{
	/*
	if (PositionIn <= Size + 1)
	{
		Node* NewNode = new Node(KeyIn);
		NewNode->SetValue(ValueIn);

		//find the position to insert the new node
		Node* Current = NewNode;
		if (Head != nullptr)
		{
			Node* Current = Head;
		}
		else
		{
			Head = Current;
		}
		int CurrentPosition = 1;
		if (Size > 1)
		{
			while (CurrentPosition < PositionIn - 1 and Current->Next != nullptr)
			{
				std::cout << Current << std::endl;;
				Current = Current->Next;
				std::cout << Current;
				CurrentPosition++;
			}
			
			//insert the node
			if (Current->Next != nullptr)
			{
				NewNode->SetNext(Current->Next);
			}
			if (Current->Previous != nullptr)
			{
				NewNode->SetPrevious(Current->Previous);
			}
			Current->~Node();
			Size++;
		}
		else if (Size == 1)
		{
			Head->SetNext(NewNode);
			NewNode->SetPrevious(Head);
			NewNode->SetNext(nullptr);
			Tail = NewNode;
			Size++;
		}
	}
	else
	{
		std::cout << "That position is out of range" << std::endl;
	}*/
	if (PositionIn <= Size + 1)
	{
		if (Head == nullptr)
		{
			InsertHead(NewNode);
			return;
		}

		if (Size == 1)
		{
			InsertTail(NewNode);
			return;
		}
		else
		{
			NewNode->Previous = nullptr;
			NewNode->Next = Head;
		}
		if (PositionIn == Tail->Position + 1)
		{
			InsertTail(NewNode);
			return;
		}
		PlaceNodeFoward(NewNode, PositionIn);
		NewNode->Position = PositionIn - 1;
		IncrementNodePosition(PositionIn);
	}
}

void LinkedList::DeleteHead()
{
	if (Size > 0)
	{
		Node* NodeHead = Head->Next;
		delete Head;
		Head = NodeHead;
		if (Head != nullptr)
		{
			Head->Previous = (nullptr);
		}
		Size--;
	}
}

void LinkedList::DeleteTail()
{
	if (Head != nullptr)
	{
		Node* NodeTail = nullptr;
		if (Tail->Previous != Head)
		{
			NodeTail = Tail->Previous;
		}
		Tail->Previous->Next = NodeTail;
		delete Tail;
		Tail = NodeTail;
		if (Tail != nullptr)
		{
			Tail->SetNext(nullptr);
		}
		Size--;
	}
}

void LinkedList::DeleteBody(int PositionIn)
{
	if (PositionIn < 0 or PositionIn > Size or Size == 0)
	{
		std::cout << "Invalid Position" << std::endl;
		return;
	}

	if (PositionIn == 1)
	{
		DeleteHead();
	}
	else if (GetNode(PositionIn) == Tail)
	{
		DeleteTail();
	}
	else
	{
		Node* Current = Head;
		while (Current->Next != nullptr and Current->Position != PositionIn)
		{
			Current = Current->Next;
		}
		if (Current->Previous != nullptr)
		{
			Current->Previous->Next = Current->Next;
		}
		if (Current->Next != nullptr)
		{
			Current->Next->Previous = Current->Previous;
		}
		delete Current;
		Size--;
	}
}

Node* LinkedList::GetNode(int PositionIn)
{
	Node* Current = new Node(-1);
	if (PositionIn < 0 || PositionIn > Size || Size == 0)
	{
		std::cout << "List::GetNode - Node index is out of bounds or list is empty" << std::endl;
		return Current;
	}
	Current = Head;
	int CurrentPosition = 1;
	while (CurrentPosition < PositionIn and Current->Next != nullptr)
	{
		Current = Current->Next;
		CurrentPosition++;
	}
	return Current;
}

Node* LinkedList::FindNode(int KeyIn)
{
	if (Size == 0)
	{
		throw "cList::FindNode - Cannot search an empty list";
	}
	Node* Current = Head;
	while (Current->Next != nullptr)
	{
		if (Current->Key == KeyIn)
		{
			return Current;
		}
		Current = Current->Next;
	}
	return nullptr;
}


bool LinkedList::NodeExists(int KeyIn)
{
	return FindNode(KeyIn) != nullptr;
}


void LinkedList::SwapNodes(Node* Node1, Node* Node2)
{
	bool Node1Exists = (Node1 != nullptr) ? true : false;
	bool Node2Exists = (Node2 != nullptr) ? true : false;
	if (Node1Exists and Node2Exists)
	{
		Node* FillerNode = new Node(-1);
		FillerNode->Position = Node1->Position;
		FillerNode->Previous = Node1->Previous;
		FillerNode->Next = Node1->Next;

		bool Next1Exists = (Node1->Next != nullptr) ? true : false;
		bool Next2Exists = (Node2->Next != nullptr) ? true : false;

		bool Prev1Exists = (Node1->Previous != nullptr) ? true : false;
		bool Prev2Exists = (Node2->Previous != nullptr) ? true : false;

		if (Head == Node1)
		{
			Head = Node2;
		}
		else if (Head == Node2)
		{
			Head = Node1;
		}
		else if (Tail == Node1)
		{
			Tail = Node2;
		}
		else if (Tail == Node2)
		{
			Tail = Node1;
		}

		if (Node1->Next != Node2 and Node2->Next != Node1) //NOT adjacent
		{
			if (Prev1Exists)
			{
				(Node1->Previous)->Next = Node2;
			}
			if (Prev2Exists)
			{
				(Node2->Previous)->Next = Node1;
			}
		
			if (Next1Exists)
			{
				(Node1->Next)->Previous = Node2;
			}
			if (Next2Exists)
			{
				(Node2->Next)->Previous = Node1;
			}
			Node1->Next = (Node2->Next);
			Node2->Next = (FillerNode->Next);

			Node1->Previous = (Node2->Previous);
			Node2->Previous = (FillerNode->Previous);
		}
		else if (Next1Exists and Node1->Next == Node2)
		{
			if (Prev1Exists)
			{
				(Node1->Previous)->Next = Node2;
			}
			if (Next2Exists)
			{
				(Node2->Next)->Previous = Node1;
			}

			Node1->Next = (Node2->Next);
			Node2->Next = Node1;

			Node1->Previous = Node2;
			Node2->Previous = (FillerNode->Previous);
		}
		else if (Next2Exists) //Node2-> == Node1
		{
			if (Prev2Exists)
			{
				(Node2->Previous)->Next = Node1;
			}
			if (Next1Exists)
			{
				(Node1->Next)->Previous = Node2;
			}

			Node1->Next = Node2;
			Node2->Next = (FillerNode->Next);

			Node1->Previous = (Node2->Previous);
			Node2->Previous = Node1;
		}
		Node1->Position = (Node2->Position);
		Node2->Position = (FillerNode->Position);
	}
	else
	{
		std::cout << "one or both nodes do not exist" << std::endl;
	}
}

void LinkedList::PlaceNodeBack(Node* Node, int PositionIn)
{
	while (Node->Position != PositionIn)
	{
		SwapNodes(Node, Node->Previous);
	}
}

void LinkedList::PlaceNodeFoward(Node* Node, int Position)
{
	while (GetNode(Position) != Node)
	{
		SwapNodes(Node->Next, Node);
	}
}

void LinkedList::PrintList()
{
	if (Size > 0)
	{
		Node* HeadNode = Head;
		std::cout << std::endl;
		while (HeadNode->Next != nullptr)
		{
			HeadNode->PrintNodeDetails();
			std::cout << std::endl;
			HeadNode = HeadNode->Next;
		}
		HeadNode->PrintNodeDetails();
		std::cout << std::endl;
		
	}
}

void LinkedList::NodeDetails()
{
	system("cls");
	Node* HeadNode = Head;
	while (HeadNode->Next != nullptr)
	{
		std::cout << "Node:     " << HeadNode->Key << std::endl <<
					 "Value:    " << HeadNode->Value << std::endl <<
					 "Position: " << HeadNode->Position << std::endl <<
			         "Next:     " << HeadNode->Next << std::endl << 
			         "Current:  " << HeadNode << std::endl << 
			         "Previous: " << HeadNode->Previous << std::endl << std::endl;
		HeadNode = HeadNode->Next;
	}
	std::cout << "Node:     " << HeadNode->Key << std::endl <<
		"Value:    " << HeadNode->Value << std::endl <<
		"Position: " << HeadNode->Position << std::endl <<
		"Next:     " << HeadNode->Next << std::endl <<
		"Current:  " << HeadNode << std::endl <<
		"Previous: " << HeadNode->Previous << std::endl << std::endl;
	std::cout << std::endl;
}

bool LinkedList::Sorted()
{
	Node* HeadNode = Head;
	while (HeadNode->Next != nullptr)
	{
		if (HeadNode->Value > (HeadNode->Next)->Value)
		{
			return false;
		}
		HeadNode = HeadNode->Next;
	}
	if ((Tail->Previous)->Value > Tail->Value)
	{
		std::cout << (Tail->Previous)->Value << Tail->Value;
		return false;
	}
	return true;
}
#include <fstream>
void LinkedList::SaveToFile(std::string Path)
{
	std::ofstream File;
	File.open(Path);
	if (Size > 0)
	{

		Node* HeadNode = Head;
		File << "NAME // TYPE // PRICE // QUANTITY \n";
		while (HeadNode->Next != nullptr)
		{
			File << HeadNode->Name << " // " << HeadNode->Type << " // " << HeadNode->Price << " // " << HeadNode->Quantity << "\n";
			HeadNode = HeadNode->Next;
		}
		File << HeadNode->Name << " // " << HeadNode->Type << " // " << HeadNode->Price << " // " << HeadNode->Quantity;
	}
	File.close();
}