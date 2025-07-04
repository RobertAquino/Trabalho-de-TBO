#pragma once

#include "HashMap.hpp"
#include <vector>

template <typename K>
class HashSet
{
private:
    HashMap<K, bool> hashMap;

public:
    HashSet() {}

    HashSet(const HashSet<K> &other)
        : hashMap(other.hashMap)
    {
    }

    HashSet<K> &operator=(const HashSet<K> &other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->hashMap = other.hashMap;
        return *this;
    }

    void put(const K &key)
    {
        hashMap.put(key, true);
    }

    void remove(const K &key)
    {
        hashMap.remove(key);
    }

    bool contains(const K &key) const
    {
        return hashMap.containsKey(key);
    }

    int getSize() const
    {
        return hashMap.getSize();
    }

    std::vector<K> getAll() const
    {
        std::vector<K> keys;
        for (int i = 0; i < hashMap.getCapacity(); ++i)
        {
            std::vector<K> itens = hashMap.getKeysAtIndex(i);
            for (const auto &item : itens)
            {
                keys.push_back(item);
            }
        }
        return keys;
    }

    void print() const
    {
        for (int i = 0; i < hashMap.getCapacity(); ++i)
        {
            std::vector<K> itens = hashMap.getKeysAtIndex(i);
            for (const auto &item : itens)
            {
                std::cout << item << " ";
            }
        }
    }
};
