#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "Entity.h"
#include <vector>
#include <iostream>

class MyVector {
protected:
    std::vector<Entity *> vector; // Underlying vector to store entities

public:
    MyVector();
    ~MyVector();
    // Overload the [] operator to find an Entity* by ID
    Entity* operator[](int index);

    // Overload assignment operator
    MyVector& operator=(const MyVector& other);

    // Overload equality operators
    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;

    // Overload addition operator to push back an Entity*
    void operator+=(Entity* entity);

    // Overload subtraction operator to pop elements
    void operator-=(int count);

    // Size of the vector
    size_t size() const;

    // Check if the vector is empty
    bool empty() const;

    // Clear all entities
    void clear();

    // Iterator support for range-based for loops
    std::vector<Entity*>::iterator begin();
    std::vector<Entity*>::iterator end();
    std::vector<Entity*>::const_iterator begin() const;
    std::vector<Entity*>::const_iterator end() const;

    // New overrides
    Entity* back() const; // Get the last element
    void erase(std::vector<Entity*>::iterator position); // Erase an element at the given position
    void erase(int index);
    void erase(std::vector<Entity*>::iterator first, std::vector<Entity*>::iterator last); // Erase a range of elements

    int next(int index);
    int prev(int index);

};

#endif
