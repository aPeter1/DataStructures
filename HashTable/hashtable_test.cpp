#include<iostream>
#include "hashtable.h"

int main(int argc, char** argv) {
	HashTable<int, int> table;
	const int KEY = 4;
	int value = 5;
	const HashTable<int, int>::Entry entry (KEY, value);
	table.insert(entry);
	std::cout << "We have a table!" << std::endl;
	return 0;
}