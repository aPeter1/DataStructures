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
					parent(other.parent), index(other.index) {}
					
				iterator(HashTable<KeyType, ValueType>* parent, size_t& index, const typename std::list<Entry>::iterator& position):
					parent(parent), index(index), position(position){}
				
				Entry& operator*() { return *position; }
				Entry& operator->() { Entry* e; return e->position; }
				iterator& operator++() {
					if(position == parent->table[index].end()) {
						position = 
					}
				}
				iterator& operator++(int);
				
				bool operator==(const iterator& other) const;
				
			private:
				HashTable<KeyType, ValueType>* parent;
				typename std::list<Entry>::iterator position;
				size_t index;
				
				iterator(const HashTable<KeyType, ValueType>* parent, size_t index);
				void advance();
		};
		
		
		class const_iterator;
					
		HashTable():
			hashFunction(std::hash<KeyType>()), entries(0),
			table(INITIAL_CAPACITY), LOAD_THRESHOLD(3.0){}
			
		iterator begin();
		
		iterator end();
		
		const_iterator begin() const;
		
		const_iterator end() const;
		
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