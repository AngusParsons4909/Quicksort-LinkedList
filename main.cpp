/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : Main.cpp
Description : Main function for console window
Author : Angus Parsons
Mail : angus.parsons@mds.ac.nz
**************************************************************************/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LinkedList.h"

Node* SortSegment(Node* Start, Node* End, LinkedList* List)
{
	int j = Start->Position;
	int i = j - 1;
	int EndPos = End->Position;
	while (j <= EndPos)
	{
		if ((List->GetNode(j))->Value < End->Value)
		{
			i++;
			List->SwapNodes(List->GetNode(j), List->GetNode(i));
		}
		j++;
	}
	i++;
	List->PlaceNodeBack(End, i);
	return List->GetNode(i);
}

void Sort(int StartPos, int EndPos, LinkedList* List)
{
	Node* Start = List->GetNode(StartPos);
	Node* End = List->GetNode(EndPos);

	if (Start != nullptr && End != nullptr && Start != End && Start != End->Next)
	{
		//Partition the list and get the pivot node
		Node* Pivot = SortSegment(Start, End, List);

		if (Pivot != nullptr)
		{
			//sort the left side
			if (Pivot->Position > StartPos)
			{
				Sort(StartPos, Pivot->Position - 1, List);
			}

			//sort the right side
			if (Pivot->Position < EndPos)
			{
				Sort(Pivot->Position + 1, EndPos, List);
			}
		}
	}
}

void ReadFileAndAppendToList(const std::string& Filename, LinkedList* List)
{
	std::ifstream File(Filename);
	std::string Line;

	if (!File.is_open())
	{
		std::cerr << "Could not open the file!" << std::endl;
		return;
	}
	int Counter = 0;
	bool FirstLine = true;
	// Read the file line by line
	while (std::getline(File, Line))
	{
		if (FirstLine)
		{
			FirstLine = false;
			continue;
		}
		
		Counter++;
		
		std::string Name, Type, PriceStr, QuantityStr;
		for (size_t pos = 0; (pos = Line.find("//", pos)) != std::string::npos; pos += 1) {
			Line.replace(pos, 2, "/");
		}
		std::istringstream iss(Line);
		std::getline(iss, Name, '/');
		std::getline(iss, Type, '/');
		std::getline(iss, PriceStr, '/');
		std::getline(iss, QuantityStr, '/');

		Name.erase(0, Name.find_first_not_of(" \t"));
		Name.erase(Name.find_last_not_of(" \t") + 1);
		Type.erase(0, Type.find_first_not_of(" \t"));
		Type.erase(Type.find_last_not_of(" \t") + 1);
		PriceStr.erase(0, PriceStr.find_first_not_of(" \t"));
		PriceStr.erase(PriceStr.find_last_not_of(" \t") + 1);
		
		float Price = std::stof(PriceStr);
		int Quantity = std::stoi(QuantityStr);
		Node* NewNode = new Node(Counter, Name, Type, Price, Quantity);
		if (Counter == 1)
		{
			List->InsertHead(NewNode);
		}
		else
		{
			List->InsertTail(NewNode);
		}
	}

	File.close();
}

int StringToInt(std::string Str)
{
	int Num = static_cast<int>(Str[0]);
	if (Num > 95)
	{
		Num = Num - 32;
	}
	return Num;
}

void UpdateNodeValue(Node* Node, int Case, bool Reverse)
{
	int ReverseNum = 1;
	if (Reverse)
	{
		ReverseNum = -1;
	}
	switch (Case)
	{
	case '1':  // Sort by Price
		Node->Value = (Node->Price * 100) * ReverseNum;  // Scale to avoid floating-point issues
		break;
	case '2':  // Sort by Quantity
		Node->Value = (Node->Quantity) * ReverseNum;
		break;
	case '3':  // Sort by Name (alphabetically)
		Node->Value = (StringToInt(Node->Name)) * ReverseNum;
		break;
	case '4':  // Sort by Type (alphabetically)
		Node->Value = (StringToInt(Node->Type)) * ReverseNum;
		break;
	default:
		std::cerr << "Invalid sort option." << std::endl;
		break;
	}
}


void PrepareForSorting(LinkedList* List, char Case, bool Reverse) {
	Node* CurrentNode = List->GetNode(1);
	while (CurrentNode->Next != nullptr)
	{
		UpdateNodeValue(CurrentNode, Case, Reverse);
		CurrentNode = CurrentNode->Next;
	}
	UpdateNodeValue(CurrentNode, Case, Reverse);
	CurrentNode = CurrentNode->Next;
}

char Menu()
{
	char Choice;
	std::cout << "*1 " << "Display Inventory" << std::endl;
	std::cout << "*2 " << "Sort Inventory" << std::endl;
	std::cout << "*3 " << "Add Item" << std::endl;
	std::cout << "*4 " << "Delete Item" << std::endl;
	std::cout << "*5 " << "Edit Item" << std::endl;
	std::cout << "*6 " << "Load Inventory from File" << std::endl;
	std::cout << "*7 " << "Save Inventory to File" << std::endl;
	std::cout << "*8 " << "Exit" << std::endl;
	std::cout << "What will you choose?" << std::endl;
	std::cout << "Enter Num: ";
	std::cin  >> Choice;
	system("cls");
	return Choice;
}

int main()
{
	LinkedList* List = new LinkedList("Original");
	bool Exit = false;
	char Case;
	char ReverseIn;
	bool Reverse = false;
	int Counter;
	std::string Name;
	std::string Type;
	int Price;
	float Quantity;
	Node* NewNode;
	int Position;
	std::string Path;
	while (!Exit)
	{
		char Option = Menu();
		switch (Option) 
		{
		case '1':
			if (List->Size)
			{
				List->PrintList();
			}
			else
			{
				std::cout << "No list to Display" << std::endl << std::endl;
			}
			break;
		case '2':
			if (List->Size > 1)
			{
				std::cout << "Sort By:" << std::endl;
				std::cout << "*1 Price" << std::endl;
				std::cout << "*2 Quantity" << std::endl;
				std::cout << "*3 Name" << std::endl;
				std::cout << "*4 Type" << std::endl;
				std::cout << "What will you choose?" << std::endl;
				std::cout << "Enter Num: ";
				std::cin >> Case;
				std::cout << "Ascending or Descending? (Enter 'A' or 'D') ";
				std::cin >> ReverseIn;
				if (ReverseIn == 'd' or ReverseIn == 'D')
				{
					Reverse = true;
				}
				else
				{
					Reverse = false;
				}
				PrepareForSorting(List, Case, Reverse);
				Sort(1, List->Size, List);
				List->PrintList();
			}
			else
			{
				std::cout << "No list to Sort" << std::endl << std::endl;
			}
			break;
		case '3':
			Counter = List->Size + 1;
			std::cout << "Please use '_' character instead of space" << std::endl;
			std::cout << "e.g: Gun_That_Shoots_Things" << std::endl;
			std::cout << "Name? ";
			std::cin >> Name;

			std::cout << "Type? ";
			std::cin >> Type;

			std::cout << "Price? ";
			std::cin >> Price;

			std::cout << "Quantity? ";
			std::cin >> Quantity;

			for (int i = 0; i < Name.size(); i++)
			{
				if (Name[i] == '_')
				{
					Name[i] = ' ';
				}
			}
			for (int i = 0; i < Type.size(); i++)
			{
				if (Type[i] == '_')
				{
					Type[i] = ' ';
				}
			}

			NewNode = new Node(Counter, Name, Type, Price, Quantity);
			if (List->Size > 0)
			{
				List->InsertTail(NewNode);
			}
			else
			{
				List->InsertHead(NewNode);
			}
			break;
		case '4':
			if (List->Size > 0)
			{
				std::cout << "Position to Delete: ";
				std::cin >> Position;
				List->DeleteBody(Position);
			}
			else
			{
				std::cout << "No list to Delete" << std::endl << std::endl;
			}
			break;
		case '5':
			if (List->Size > 0)
			{
				std::cout << "Position to Edit: ";
				std::cin >> Position;
				
				std::cout << "Please use '_' character instead of space" << std::endl;
				std::cout << "e.g: Gun_That_Shoots_Things" << std::endl;
				std::cout << "Name? ";
				std::cin >> Name;
				
				std::cout << "Type? ";
				std::cin >> Type;

				std::cout << "Price? ";
				std::cin >> Price;

				std::cout << "Quantity? ";
				std::cin >> Quantity;

				for (int i = 0; i < Name.size(); i++)
				{
					if (Name[i] == '_')
					{
						Name[i] = ' ';
					}
				}
				for (int i = 0; i < Type.size(); i++)
				{
					if (Type[i] == '_')
					{
						Type[i] = ' ';
					}
				}

				List->GetNode(Position)->Name = Name;
				List->GetNode(Position)->Type = Type;
				List->GetNode(Position)->Price = Price;
				List->GetNode(Position)->Quantity = Quantity;
			}
			else
			{
				std::cout << "No list to edit" << std::endl << std::endl;
			}
			break;
		case '6':
			std::cout << "File Path: ";
			std::cin >> Path;
			ReadFileAndAppendToList(Path, List);
			break;
		case '7':
			if (List->Size > 0)
			{
				std::cout << "File Path: ";
				std::cin >> Path;
				List->SaveToFile(Path);
			}
			else
			{
				std::cout << "No list to Save" << std::endl << std::endl;
			}
			break;
		case '8':
			Exit = true;
			break;
		default:
			std::cout << "Not a valid option" << std::endl << std::endl;
		}
		std::cin.clear();
	}

	return 0;
}