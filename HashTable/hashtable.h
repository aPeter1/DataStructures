#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include<iostream>
#include<vector>

template<typename KeyType, typename ValueType>
	class HashTable
	{
		
		public:
			typedef std::pair<const KeyType, ValueType> Entry;
			typedef std::tuple<Entry*, Entry*, Entry*> Link;
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
			
			size_t locate(const KeyType& key);
		
	};

template<typename KeyType, typename ValueType>
	size_t HashTable<KeyType, ValueType>::locate(const KeyType& entry) {
		size_t index = hashFunction(entry->get(0)) % table.size();
		return true;
	}




#endif