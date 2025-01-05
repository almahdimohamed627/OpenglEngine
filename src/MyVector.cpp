#include "MyVector.h"

MyVector::MyVector() : vector() {}

MyVector::~MyVector() {
    for (size_t i = 0; i < vector.size(); i++)
    {
        delete vector[i];
    }
    
}

// Overload the [] operator to find an Entity* by ID
Entity *MyVector::operator[](int index)
{
    for (Entity *entity : vector)
    {
        if (entity->getId() == index)
        {
            return entity;
        }
    }
    return vector.back(); // Return nullptr if no matching Entity* is found
}

// Overload assignment operator
MyVector &MyVector::operator=(const MyVector &other)
{
    if (this != &other)
    {
        vector = other.vector;
    }
    return *this;
}

// Overload equality operators
bool MyVector::operator==(const MyVector &other) const
{
    return vector == other.vector;
}

bool MyVector::operator!=(const MyVector &other) const
{
    return vector != other.vector;
}

// Overload addition operator to push back an Entity*
void MyVector::operator+=(Entity *entity)
{
    vector.push_back(entity);
}

// Overload subtraction operator to pop elements
void MyVector::operator-=(int count)
{
    for (int i = 0; i < count && !vector.empty(); ++i)
    {
        vector.pop_back();
    }
}

// Size of the vector
size_t MyVector::size() const
{
    return vector.size();
}

// Check if the vector is empty
bool MyVector::empty() const
{
    return vector.empty();
}

// Clear all entities
void MyVector::clear()
{
    vector.clear();
}

// Iterator support for range-based for loops
std::vector<Entity *>::iterator MyVector::begin()
{
    return vector.begin();
}

std::vector<Entity *>::iterator MyVector::end()
{
    return vector.end();
}

std::vector<Entity *>::const_iterator MyVector::begin() const
{
    return vector.begin();
}

std::vector<Entity *>::const_iterator MyVector::end() const
{
    return vector.end();
}

// Override .back() method
Entity *MyVector::back() const
{
    if (!vector.empty())
    {
        return vector.back();
    }
    return nullptr; // Return nullptr if the vector is empty
}

// Override .erase() method (single position)
void MyVector::erase(std::vector<Entity *>::iterator position)
{
    if (position >= vector.begin() && position < vector.end())
    {
        vector.erase(position);
    }
}

void MyVector::erase(int index)
{
    for (auto i = vector.begin(); i < vector.end(); i++) 
    {
        if ((*i)->getId() == index)
        {
            vector.erase(i);
        }
    }
    
}

// Override .erase() method (range of positions)
void MyVector::erase(std::vector<Entity *>::iterator first, std::vector<Entity *>::iterator last)
{
    if (first >= vector.begin() && last <= vector.end() && first <= last)
    {
        vector.erase(first, last);
    }
}

int MyVector::next(int index)
{

    for (size_t i = 0; i < vector.size(); ++i)
    {
        if (vector[i]->getId() == index)
        {
            // Return the ID of the next entity, wrapping to the beginning if at the end
            return vector[(i + 1) % vector.size()]->getId();
        }
    }
    return vector[0]->getId();
}

int MyVector::prev(int index)
{

    for (size_t i = 0; i < vector.size(); ++i)
    {
        if (vector[i]->getId() == index)
        {
            // Return the ID of the previous entity, wrapping to the end if at the beginning
            return vector[(i + vector.size() - 1) % vector.size()]->getId();
        }
    }
    return vector[vector.size() - 1]->getId();
}