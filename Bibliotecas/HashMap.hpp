#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <stdexcept>
#include <functional> // For std::reference_wrapper
#include "Filme.hpp"

template <typename K, typename V>
struct HashNode
{
    K key;
    V value;
    HashNode *next;
    HashNode(const K &k, const V &v) : key(k), value(v), next(nullptr) {}
};

template <typename K>
struct HashFunc
{
    int operator()(const K &) const
    {
        static_assert(sizeof(K) == 0, "HashFunc não implementado para este tipo.");
        return 0;
    }
};

// HashFunc specializations (unchanged)
template <>
struct HashFunc<std::string>
{
    int operator()(const std::string &chave) const
    {
        unsigned int h = 0;
        for (char c : chave)
        {
            h = h * 31 + c;
        }
        return h;
    }
};

template <>
struct HashFunc<int>
{
    int operator()(const int &chave) const
    {
        return chave;
    }
};

template <>
struct HashFunc<long>
{
    int operator()(const long &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <>
struct HashFunc<double>
{
    int operator()(const double &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <>
struct HashFunc<char>
{
    int operator()(const char &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <>
struct HashFunc<Genres>
{
    int operator()(const Genres &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <>
struct HashFunc<TitleType>
{
    int operator()(const TitleType &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <>
struct HashFunc<bool>
{
    int operator()(const bool &chave) const
    {
        return static_cast<int>(chave);
    }
};

template <typename K, typename V>
class HashMap
{
private:
    HashNode<K, V> **table;
    int capacity;
    int size;

    const int primes[19] = {7, 23, 53, 73, 101, 211, 431, 863, 1741, 3469, 6949, 14033, 28813, 60493,
                            115249, 216091, 430467, 860933, 1721903};
    int primeIndex = 0;

    int hash(const K &key) const
    {
        HashFunc<K> hashFunc;
        return hashFunc(key) % capacity;
    }

public:
    HashMap(int initialCapacity = 101) : capacity(initialCapacity), size(0)
    {
        capacity = primes[primeIndex];
        while (capacity < initialCapacity && primeIndex < sizeof(primes) / sizeof(primes[0]) - 1)
        {
            primeIndex++;
            capacity = primes[primeIndex];
        }
        table = new HashNode<K, V> *[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            table[i] = nullptr;
        }
    }

    // Construtor de Copia
    HashMap(const HashMap<K, V> &other)
        : capacity(other.capacity), size(0), primeIndex(other.primeIndex)
    {
        table = new HashNode<K, V> *[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            table[i] = nullptr;
        }

        for (int i = 0; i < other.capacity; ++i)
        {
            HashNode<K, V> *node = other.table[i];
            while (node)
            {
                this->put(node->key, node->value);
                node = node->next;
            }
        }
    }

    HashMap<K, V> &operator=(const HashMap<K, V> &other)
    {
        if (this == &other)
        {
            return *this;
        }

        for (int i = 0; i < capacity; ++i)
        {
            HashNode<K, V> *node = table[i];
            while (node)
            {
                HashNode<K, V> *temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;

        capacity = other.capacity;
        size = 0;
        primeIndex = other.primeIndex;

        table = new HashNode<K, V> *[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            table[i] = nullptr;
        }
        for (int i = 0; i < other.capacity; ++i)
        {
            HashNode<K, V> *node = other.table[i];
            while (node)
            {
                this->put(node->key, node->value);
                node = node->next;
            }
        }

        return *this;
    }

    ~HashMap()
    {
        for (int i = 0; i < capacity; ++i)
        {
            HashNode<K, V> *node = table[i];
            while (node)
            {
                HashNode<K, V> *temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int getCapacity() const
    {
        return capacity;
    }

    void put(const K &key, const V &value)
    {
        int index = hash(key);
        HashNode<K, V> *node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->value = value;
                return;
            }
            node = node->next;
        }
        HashNode<K, V> *newNode = new HashNode<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
        if (size > capacity * 0.7)
        {
            resize();
        }
    }

    // Non-const get returns a reference to the value
    std::optional<std::reference_wrapper<V>> get(const K &key)
    {
        int index = hash(key);
        HashNode<K, V> *node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return std::optional<std::reference_wrapper<V>>(std::ref(node->value));
            }
            node = node->next;
        }
        return std::nullopt;
    }

    // Const get returns a copy of the value
    std::optional<V> get(const K &key) const
    {
        int index = hash(key);
        HashNode<K, V> *node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return node->value;
            }
            node = node->next;
        }
        return std::nullopt;
    }

    void remove(const K &key)
    {
        int index = hash(key);
        HashNode<K, V> *node = table[index];
        HashNode<K, V> *prev = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                if (prev == nullptr)
                {
                    table[index] = node->next;
                }
                else
                {
                    prev->next = node->next;
                }
                delete node;
                size--;
                return;
            }
            prev = node;
            node = node->next;
        }
        throw std::out_of_range("Key not found in HashMap.");
    }

    bool containsKey(const K &key) const
    {
        int index = hash(key);
        HashNode<K, V> *node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return true;
            }
            node = node->next;
        }
        return false;
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void resize()
    {
        int oldCapacity = capacity;

        if (primeIndex + 1 >= sizeof(primes) / sizeof(primes[0]))
        {
            throw std::runtime_error("HashMap maximum capacity reached - no more prime numbers for resizing.");
        }

        capacity = primes[++primeIndex];
        HashNode<K, V> **oldTable = table;
        table = new HashNode<K, V> *[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            table[i] = nullptr;
        }

        this->size = 0;

        for (int i = 0; i < oldCapacity; ++i)
        {
            HashNode<K, V> *node = oldTable[i];
            while (node != nullptr)
            {
                put(node->key, node->value);
                HashNode<K, V> *temp = node;
                node = node->next;
                delete temp;
            }
        }

        delete[] oldTable;
    }

    std::vector<K> getKeysAtIndex(int index) const
    {
        std::vector<K> keys;
        HashNode<K, V> *node = table[index];
        while (node != nullptr)
        {
            keys.push_back(node->key);
            node = node->next;
        }
        return keys;
    }
};