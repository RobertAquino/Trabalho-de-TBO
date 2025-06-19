#pragma once

#include "HashMap.hpp"

template <typename K>
class HashSet
{
private:
    HashMap<K, bool> hashMap;

public:
    HashSet() {}

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
};