#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include<iostream>
#include<vector>
#include<list>


// Credit to "Objects, Abstraction, Data Structures and Design using C++" for providing the skeleton of this class.
template<typename KeyType, typename ValueType>
class HashTable
{
	public:
		typedef std::pair<const KeyType, ValueType> Entry;
		
		class iterator {
			public:
				iterator(const typename HashTable<KeyType, ValueType>::iterator& other):
					parent(other.parent), index(other.index), end(false) {}
					
				Entry& operator*() {
					return *position; 
				}
				Entry& operator->() { 
					Entry* e;
					if (end) {
						return nullptr;
					}
					return e->position; 
				}
				iterator& operator++() { 
					increment(1); 
					return *this; 
				}
				iterator& operator++(int move) { 
					increment(move+1); 
					return *this; 
				}
				bool operator==(const iterator& other) const{
					return position == other.position;
				}
				bool operator!=(const iterator& other) const {
					return !(position == other.position);
				}
				
				friend class HashTable;
				
			private:
				HashTable<KeyType, ValueType>* parent;
				typename std::list<Entry>::iterator position;
				size_t index;
				bool end;
								
				iterator(HashTable<KeyType, ValueType>* parent, size_t& index, const typename std::list<Entry>::iterator& position):
					parent(parent), index(index), position(position), end(false){}
					
				iterator():
					index(-1), end(true) {}
				
				void increment(int move) {
					int moved = 0;
					while(moved < move) {
						position++;
						if(position == parent->table[index].end()) {
							advance();
						}
						moved++;
					}
				}
				
				void advance() {
					if(index >= parent->table.size()) {
						return;
					}
					
					index++;
					while(parent->table[index].empty()) index++;
					
					position = parent->table[index].begin();
				}
		};
		
		class const_iterator : private iterator {
			public:
				const_iterator(const typename HashTable<KeyType, ValueType>::iterator& other):
						parent(other.parent), index(other.index), end(false) {}
				
				const Entry& operator*() {
					return *position; 
				}
				
				const Entry& operator->() {
					Entry* e;
					if (end) {
						return nullptr;
					}
					return e->position; 
				}
			
			private:
				HashTable<KeyType, ValueType>* parent;
				typename std::list<Entry>::iterator position;
				size_t index;
				bool end;
		};
					
		HashTable():
			hashFunction(std::hash<KeyType>()), entries(0),
			table(INITIAL_CAPACITY), LOAD_THRESHOLD(3.0){}
			
		iterator begin() {
			typename std::vector<std::list<Entry>>::iterator bucket = table.begin();
			size_t index = 0;
						
			while((*bucket).begin() == (*bucket).end() && bucket != table.end()) index++, bucket++;
			
			if(bucket == table.end()) {
				return this->end();
			}
			return iterator(this, index, bucket->begin());
		}
		
		iterator end() {		
			return iterator();
		}
		
		const_iterator begin() const {
			iterator nonConst = begin();
			return const_iterator(nonConst);
		}
		
		const_iterator end() const {
			return const_iterator();
		}
		
		/**
			@param entry is a reference to an entry object which contains the key-value pair for the table.
			@returns bool true if item was inserted, false if it was already in the table.
		*/
		std::pair<iterator, bool> insert(const Entry& entry) {
			double loadFactor = double(entries) / table.size();
			if(loadFactor > LOAD_THRESHOLD) {
				rehash();
			}
			
			// Find the position i the table.
			size_t index = hashFunction(entry.first) % table.size();
				
			// Search for the key.
			typename std::list<Entry>::iterator position = table[index].begin();
			while(position != table[index].end() && position->first != entry.first) ++position;
			
			if(position == table[index].end()) { // Not in table.
				table[index].push_back(Entry(entry));
				entries++;
				return std::make_pair(iterator(this, index, --(table[index].end())), true);
			} else { // In table.
				return std::make_pair(iterator(this, index, position), false);
			}
		}
		
		void erase(const KeyType& key);
		
		iterator find(const KeyType& key);
		
		ValueType& operator[](const KeyType& key);	
		
		void printTable() {
			// THIS BELOW IS EXACTLY WHAT AN ITERATOR FOR THE TABLE SHOULD DO!!! Just a side note.
			std::cout << "HashTable {" << std::endl;
			
			typename std::vector<std::list<Entry>>::iterator vectorIterator = table.begin();
			while(vectorIterator != table.end()) {
				typename std::list<Entry>::iterator listIterator = (*vectorIterator).begin();
				
				while(listIterator != (*vectorIterator).end()) {
					Entry tableEntry = *listIterator;
					
					std::cout << "[Key:" << tableEntry.first << ", Value:" << tableEntry.second << "]" << std::endl;
					
					listIterator++;
				}
			
				vectorIterator++;
			}
			
			std::cout << "}" << std::endl;
		}
		
		virtual ~HashTable() {}

	private:
		std::hash<KeyType> hashFunction;
		size_t entries;
		std::vector<std::list<Entry>> table;
		
		static const size_t INITIAL_CAPACITY = 100;
		const double LOAD_THRESHOLD;
		
		void rehash();
	
};
	
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
	
}
	
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::erase(const KeyType& key) {
	
}
	
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::iterator HashTable<KeyType, ValueType>::find(const KeyType& key) {
	
}
	
#endif