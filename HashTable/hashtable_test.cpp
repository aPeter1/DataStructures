#include<iostream>
#include "hashtable.h"

int main(int argc, char** argv) {
	HashTable<int, int> table;
	
	std::cout << std::endl << "Test 0" << std::endl;
	HashTable<int, int>::iterator hashBegin0 = table.begin();
	
	if(hashBegin0 == table.end()) {
		std::cout << "Begin == end when empty" << std::endl;
	}
	
	std::cout << std::endl << "Test 1" << std::endl;
	const HashTable<int, int>::Entry entry1 (5, 3);
	table.insert(entry1);
	const HashTable<int, int>::Entry entry2 (1, 43);
	table.insert(entry2);
	const HashTable<int, int>::Entry entry3 (543, 2);
	table.insert(entry3);
	const HashTable<int, int>::Entry entry4 (13, 332);
	table.insert(entry4);
	const HashTable<int, int>::Entry entry5 (101, 142);
	table.insert(entry5);
	const HashTable<int, int>::Entry entry6 (201, 144);
	table.insert(entry6);
	const HashTable<int, int>::Entry entry7 (301, 1442);
	table.insert(entry7);
	
	table.printTable();
	
	HashTable<int, int>::iterator hashBegin = table.begin();
	
	if(hashBegin == table.end()) {
		std::cout << "Begin == end" << std::endl;
	}
	
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	
	if(hashBegin == table.end()) {
		std::cout << "Begin iterated to before end == end" << std::endl;
	}
	
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	std::cout << (*hashBegin).first << " " << (*hashBegin).second << std::endl;
	hashBegin++;
	
	if(hashBegin == table.end()) {
		std::cout << "Begin iterated to end == end" << std::endl;
	}
	
	std::cout << std::endl << "Test 2" << std::endl;
	HashTable<int, int>::iterator newHashBegin = table.begin();
	while(newHashBegin != table.end()) {
		std::cout << (*newHashBegin).first << " " << (*newHashBegin).second << std::endl;
		newHashBegin++;
	}
	
	std::cout << std::endl << "Test 3" << std::endl;
	const HashTable<int, int>::Entry entry8 (301, 1442);
	table.insert(entry8);
	HashTable<int, int>::iterator newHashBegin2 = table.begin();
	while(newHashBegin2 != table.end()) {
		std::cout << (*newHashBegin2).first << " " << (*newHashBegin2).second << std::endl;
		newHashBegin2++;
	}
	table.printTable();
	
	std::cout << std::endl << "All good :)" << std::endl;
	return 0;
}