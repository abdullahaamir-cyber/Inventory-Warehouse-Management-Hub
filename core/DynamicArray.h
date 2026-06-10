#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

template <typename T>
class DynamicArray 
{
private:
    T* arr;
    int arraySize;
    int arrayCapacity;

    void resize(int newCapacity) {
        T* temp = new T[newCapacity];
        for (int i = 0; i < arraySize; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        arrayCapacity = newCapacity;
    }

public:
    DynamicArray() : arr(nullptr), arraySize(0), arrayCapacity(0) {}

    DynamicArray(int initialSize) : arraySize(initialSize), arrayCapacity(initialSize) {
        arr = new T[arrayCapacity];
    }

    // Rule of Three: Copy Constructor
    DynamicArray(const DynamicArray& other) : arraySize(other.arraySize), arrayCapacity(other.arrayCapacity) {
        if (arrayCapacity > 0) {
            arr = new T[arrayCapacity];
            for (int i = 0; i < arraySize; i++) {
                arr[i] = other.arr[i];
            }
        } else {
            arr = nullptr;
        }
    }

    // Rule of Three: Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] arr;
            arraySize = other.arraySize;
            arrayCapacity = other.arrayCapacity;
            if (arrayCapacity > 0) {
                arr = new T[arrayCapacity];
                for (int i = 0; i < arraySize; i++) {
                    arr[i] = other.arr[i];
                }
            } else {
                arr = nullptr;
            }
        }
        return *this;
    }

    // Rule of Three: Destructor
    ~DynamicArray() {
        delete[] arr;
    }

    void push_back(const T& val) {
        if (arrayCapacity == 0) {
            resize(1);
        } else if (arraySize == arrayCapacity) {
            resize(arrayCapacity * 2);
        }
        arr[arraySize++] = val;
    }

    void pop_back() {
        if (arraySize > 0) {
            arraySize--;
        }
    }

    void erase(int index) {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < arraySize - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arraySize--;
    }

    void clear() {
        delete[] arr;
        arr = nullptr;
        arraySize = 0;
        arrayCapacity = 0;
    }

    int size() const { return arraySize; }
    int capacity() const { return arrayCapacity; }
    bool empty() const { return arraySize == 0; }

    T& operator[](int index) {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    // Iterators for range-based for loops
    T* begin() { return arr; }
    T* end() { return arr + arraySize; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + arraySize; }
};

#endif
