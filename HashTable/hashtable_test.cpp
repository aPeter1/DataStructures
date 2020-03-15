#include<iostream>
#include "hashtable.h"

int main(int argc, char** argv) {
	HashTable<int, int> table;
	
	const HashTable<int, int>::Entry entry1 (5, 3);
	table.insert(entry1);
	const HashTable<int, int>::Entry entry2 (1, 43);
	table.insert(entry2);
	const HashTable<int, int>::Entry entry3 (543, 2);
	table.insert(entry3);
	const HashTable<int, int>::Entry entry4 (13, 332);
	table.insert(entry4);
	
	table.printTable();
	std::cout << std::endl;
	
	HashTable<int, int>::iterator hashBegin = table.begin();
	std::cout << (*hashBegin).first << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << (*hashBegin).second << std::endl;
	hashBegin++;
	
	if(hashBegin == table.end()) {
		std::cout << "Begin iterated to before end == end" << std::endl;
	}
	
	std::cout << (*hashBegin).first << (*hashBegin).second << std::endl;
	hashBegin++;
	
	if(hashBegin == table.end()) {
		std::cout << "Begin iterated to end == end" << std::endl;
	}
	
	//HashTable<int, int>::iterator hashEnd = table.end();
	//std::cout << (*hashEnd).first << std::endl;
	
	std::cout << "All good." << std::endl;
	return 0;
}