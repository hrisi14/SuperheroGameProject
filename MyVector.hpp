#pragma once
#include <iostream>
// parts of the implementation have been taken by github/Plamena-Ilieva/ OOP-Tasks-2022/Kindle/ Vector.hpp

template <typename T>
class Vector
{
    T* data;
    size_t size;
    size_t capacity;

    void free();
    void copyFrom(const Vector<T>&);


public:
    Vector();
    Vector(const Vector<T>&);
    Vector<T>& operator=(const Vector<T>&);
    ~Vector();

    size_t getSize() const;
    size_t getCapacity() const;
    void setCapacity(size_t);
    void pushBack(const T&);
    void resize(unsigned int newCapacity);
    void insert(const T&, size_t);

    T& operator[](size_t);
    const T& operator[](size_t) const;
    void popAt(size_t);
    void popBack();

    void clear();
    bool empty() const;   
    
    void incrementSize();
    void decrementSize();
};

template <typename T>
void Vector<T>::free() {
    delete[] data;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
    size = other.size;
    capacity = other.capacity;

    data = new T[capacity];

    for (size_t i = 0; i < size; i++)
        data[i] = other.data[i];
}

template <typename T>
void Vector<T>::resize(unsigned int newCapacity) {
    capacity = 2 * capacity;

    T* newMemory = new T[capacity];

    for (size_t i = 0; i < size; i++)
        newMemory[i] = std::move(data[i]);

    delete[] data;
    data = newMemory;
}

template <typename T>
Vector<T>::Vector() {
    size = 0;
    capacity = 8;
    data = new T[capacity];
}

template <typename T>
void Vector<T>::setCapacity(size_t newCapacity) {
    size = 0;
    delete[] data;
    capacity = newCapacity;
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
    copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector<T>() {
    free();
}

template <typename T>
size_t Vector<T>::getSize() const {
    return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void Vector<T>::pushBack(const T& element)
{
    if (size == capacity)
    {
        resize(capacity*2);
    }
    size++;
    data[size - 1] = element;
}

template <typename T>
void Vector<T>::insert(const T& element, size_t index) {
    if (size == capacity)
        resize();
    ++size;
    for (int i = size - 1; i > index; ++i) {
        data[i] = std::move(data[i - 1]);
    }

    data[index] = element;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size)
        throw std::out_of_range("Out of range!");
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Out of range!");

    return data[index];
}

template <typename T>
void Vector<T>::popAt(size_t index) {
    if (index >= size)
        throw std::out_of_range("out of range");

    for (size_t i = index; i < size - 1; ++i)
        data[i] = std::move(data[i + 1]);

    --size;
}

template <typename T>
void Vector<T>::popBack() {
    --size;
}

template <typename T>
void Vector<T>::clear() {
    free();
    size = 0;
    capacity = 8;
    data = new T[capacity];
}

template <typename T>
bool Vector<T>::empty() const
{
    return size == 0;
}

template <typename T>
void Vector<T>::incrementSize() 
{
    size++;
}

template <typename T>
void Vector<T>::decrementSize() 
{
    size--;
}



