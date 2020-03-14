#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include<iostream>
#include<vector>

template<typename KeyType, typename ValueType>
	class HashTable
	{
		public:
			typedef std::pair<const KeyType, ValueType> Entry;
			typedef std::tuple<Entry*, struct Link*, struct Link*> Link;
			class iterator;
			class const_iterator;
						
			HashTable():
				hashFunction(std::hash<KeyType>()), length(0),
				table(INITIAL_CAPACITY, NULL),
				LOAD_THRESHOLD(0.75) {}
				
			iterator begin();
			
			iterator end();
			
			const_iterator begin() const;
			
			const_iterator end() const;
			
			bool insert(const Entry& entry);
			
			void erase(const KeyType& key);
			
			iterator find(const KeyType& key);
			
			ValueType& operator[](const KeyType& key);	
			
			virtual ~HashTable() {}

		private:
			std::hash<KeyType> hashFunction;
			size_t length;
			std::vector<Link*> table;
			
			static const size_t INITIAL_CAPACITY = 100;
			const double LOAD_THRESHOLD;
			const int LINK_ENTRY = 0;
			const int LINK_NEXT = 1;
			const int LINK_PREV = 2;
			const int ENTRY_KEY = 0;
			const int ENTRY_VALUE = 1;
			
			Link* locate(const KeyType& key);
		
	};

template<typename KeyType, typename ValueType>
	typename HashTable<KeyType, ValueType>::Link* HashTable<KeyType, ValueType>::locate(const KeyType& key) {
		size_t index = hashFunction(*key) % table.size();
		
		Link* link = table.get(index);
		
		if(link == NULL) {
			Link* link = new Link();
		}
		
		while(link != NULL) {
			if(link->get(LINK_ENTRY)->get(ENTRY_KEY) == *key){
				return link;
			}
			link = link->get(LINK_NEXT);
		}
		
		return link;
	}

template<typename KeyType, typename ValueType>
	bool HashTable<KeyType, ValueType>::insert(const Entry& entry) {
		Link* link = locate(&entry->get(ENTRY_KEY));
		
		
		
		return true;
	}
	
template<typename KeyType, typename ValueType>
	void HashTable<KeyType, ValueType>::erase(const KeyType& key) {
		
	}
	
template<typename KeyType, typename ValueType>
	typename HashTable<KeyType, ValueType>::iterator HashTable<KeyType, ValueType>::find(const KeyType& key) {
		
	}
	
#endif