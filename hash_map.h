#pragma once
#include "Linkedlist.h"
#include <mutex>
#include <atomic>

template <typename Key,typename Value>
class Hash_map 
{
private:

	Linked_list<Key,Value>* buckets[10000];
	std::atomic<bool> occupied[10000];
	std::mutex mutex_pool[10000];
	void checker(Key key);

public:
	Hash_map();
	~Hash_map();
	int Get_Hash(Key key);
	void insert(Key key, Value val);
	bool exists(Key key);
	Value& operator[] (Key key);
	void remove(Key key);
	std::atomic<int> elements =0;

};
   
template<typename Key, typename Value>
inline void Hash_map<Key, Value>::checker(Key key)
{
	if (occupied[Get_Hash(key)])
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		checker(key);
	}
}

template<typename Key, typename Value>
inline Hash_map<Key, Value>::Hash_map()
{
	for (size_t i = 0; i < 10000; i++)
	{
		buckets[i] = new Linked_list<Key, Value>;
		occupied[i] = false;
	}
}

template<typename Key, typename Value>
inline Hash_map<Key, Value>::~Hash_map()
{
	for (size_t i = 0; i < 10000; i++)
	{
		Linked_list<int, double>* a = new Linked_list<int, double>;
		a->~Linked_list();
		buckets[i] = a;
	}
}

template<typename Key, typename Value>
inline int Hash_map<Key, Value>::Get_Hash(Key key)
{
	return floor(((int)key) % 10000);
}

template<typename Key, typename Value>
inline void Hash_map<Key, Value>::insert(Key key, Value val)
{
	Linked_list<Key, Value> b = *buckets[Get_Hash(key)];
	b.insertNode(key, val);
	occupied[Get_Hash(key)] = true;
	mutex_pool[Get_Hash(key)].lock();	
	*buckets[Get_Hash(key)] = b;
	mutex_pool[Get_Hash(key)].unlock();
	occupied[Get_Hash(key)] = false;
	elements++;
}

template<typename Key, typename Value>
inline bool Hash_map<Key, Value>::exists(Key key)
{
	Linked_list<int, double> a = *buckets[Get_Hash(key)];
	return a.exists(key);
}

template<typename Key, typename Value>
inline Value& Hash_map<Key, Value>::operator[](Key key)
{
	Linked_list<int, double> a = *buckets[Get_Hash(key)];
	return a.find(key);
}

template<typename Key, typename Value>
inline void Hash_map<Key, Value>::remove(Key key)
{
	Linked_list<Key, Value> b = *buckets[Get_Hash(key)];
	b.deleteNode(key);
	checker(key);
	occupied[Get_Hash(key)] = false;
	mutex_pool[Get_Hash(key)].lock();
	*buckets[Get_Hash(key)] = b;
	mutex_pool[Get_Hash(key)].unlock();
	occupied[Get_Hash(key)] = true;
}

