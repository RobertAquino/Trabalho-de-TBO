#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class ArrayList
{
private:
    T *data;
    int capacity;
    int size;

public:
    ArrayList(int initialCapacity = 8);
    ~ArrayList();

    void add(const T &value);

    void removeAll(const T &value);

    void removeAt(int index);

    T &operator[](int index);

    int getSize() const;

    void print() const;

    void resize(int newCapacity);
};

template <typename T>
ArrayList<T>::ArrayList(int initialCapacity) : capacity(initialCapacity), size(0)
{
    data = new T[capacity];
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] data;
}

template <typename T>
T &ArrayList<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    return data[index];
}

template <typename T>
void ArrayList<T>::add(const T &value)
{
    if (size >= capacity)
    {
        resize(capacity * 2);
    }
    data[size++] = value;
}

template <typename T>
void ArrayList<T>::removeAll(const T &value)
{

    for (int i = 0; i < size; i++)

        if (data[i] == value)
        {
            removeAt(i);
        }
}

template <typename T>
void ArrayList<T>::removeAt(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    for (int i = index + 1; i < size; ++i)
    {
        data[i - 1] = data[i];
    }

    size--;
}

template <typename T>
int ArrayList<T>::getSize() const
{
    return size;
}

template <typename T>
void ArrayList<T>::resize(int newCapacity)
{
    if (newCapacity < size)
    {
        throw std::invalid_argument("Error: new capacity can't be smaller than current size.");
    }

    T *newData = new T[newCapacity];
    for (int i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void ArrayList<T>::print() const
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << "\n";
}
