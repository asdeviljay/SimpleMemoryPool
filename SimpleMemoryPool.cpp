// SimpleMemoryPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "MyMemoryPool.hpp"
#include <iostream>

#define _CRTDBG_MAP_ALLOC  

struct Item {
	unsigned int item_id;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MyMemoryPool p;
	p.init(sizeof(struct Item), 4);

	struct Item* item1 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	item1->item_id = 105;
	std::cout << "Item1 : " << item1->item_id << std::endl;
	struct Item* item2 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	item2->item_id = 210;
	std::cout << "Item2 : " << item2->item_id << std::endl;
	struct Item* item3 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	item3->item_id = 515;
	std::cout << "Item3 : " << item3->item_id << std::endl;
	struct Item* item4 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	item4->item_id = 10125;
	std::cout << "Item4 : " << item4->item_id << std::endl;
	p.release(item1, sizeof(struct Item));
	p.release(item2, sizeof(struct Item));
	p.release(item3, sizeof(struct Item));
	p.release(item4, sizeof(struct Item));
	struct Item* item5 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	std::cout << "Item5 : " << item5->item_id << std::endl;
	item1 = reinterpret_cast<struct Item*>(p.alloc(sizeof(struct Item)));
	std::cout << "Item1 : " << item1->item_id << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
