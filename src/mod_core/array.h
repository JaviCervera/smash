#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include <stdlib.h>

#define CAPACITY_INC 128

template <typename T>
class Array {
public:
    Array(int initialCapacity = 0);
    Array(const Array<T>& other);
    ~Array() { delete [] buffer; }

    Array<T>& operator=(const Array<T>& other);
    T& operator[](unsigned int pos) { return buffer[pos]; }
    const T& operator[](unsigned int pos) const { return buffer[pos]; }

    int Size() const { return size; }
    void Add(const T& elem);
    void Set(int index, const T& elem) { buffer[index] = elem; }
    T& Last() { return buffer[size-1]; }
    const T& Last() const { return buffer[size-1]; }
    void RemoveLast() { RemoveAt(Size()-1); }
    void RemoveAt(int index);
    void Remove(const T& elem);
    void RemoveEach(const T& elem);
    void Clear();
private:
    T* buffer;
    int size;
    int capacity;
};

template <typename T>
Array<T>::Array(int initialCapacity) {
    if ( initialCapacity > 0  &&  initialCapacity < CAPACITY_INC )
        initialCapacity = CAPACITY_INC;
    buffer = new T[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

template <typename T>
Array<T>::Array(const Array<T>& other) {
    buffer = new T[other.capacity];
    for ( int i = 0; i < other.size; i++ )
        buffer[i] = other.buffer[i];
    size = other.size;
    capacity = other.capacity;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    delete [] buffer;
    buffer = new T[other.capacity];
    for ( int i = 0; i < other.size; i++ )
        buffer[i] = other.buffer[i];
    size = other.size;
    capacity = other.capacity;
    return *this;
}

template <typename T>
void Array<T>::Add(const T& elem) {
    if ( capacity == size ) {
        capacity += CAPACITY_INC;
        T* oldBuffer = buffer;
        buffer = new T[capacity];
        for ( int i = 0; i < size; i++ )
            buffer[i] = oldBuffer[i];
        delete [] oldBuffer;
    }
    buffer[size++] = elem;
}

template <typename T>
void Array<T>::RemoveAt(int index) {
    for ( int i = index+1; i < size; i++ ) {
        buffer[i-1] = buffer[i];
    }
    size--;
}

template <typename T>
void Array<T>::Remove(const T& elem) {
    for ( int i = 0; i < size; i++ ) {
        if ( buffer[i] == elem ) {
            RemoveAt(i);
            break;
        }
    }
}

template <typename T>
void Array<T>::RemoveEach(const T& elem) {
    int i = 0;
    while ( i < size ) {
        if ( buffer[i] == elem ) {
            RemoveAt(i);
        } else {
            i++;
        }
    }
}

template <typename T>
void Array<T>::Clear() {
    delete [] buffer;
    buffer = new T[CAPACITY_INC];
    size = 0;
    capacity = CAPACITY_INC;
}

#undef CAPACITY_INC

#endif // CORE_ARRAY_H
