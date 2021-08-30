#pragma once
#include "DynamicArray.h"
#include "LinkedList.h"

template <class T> class Sequence {

    public:

        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual int GetLength() const = 0;
        virtual int GetReserved() const = 0;
        virtual void Append(T item) = 0;
        virtual void Prepend(T item) = 0;
        virtual void InsertAt(T item, int index) = 0;
        virtual void Set(int index, T value) = 0;
        virtual Sequence<T>* Concat(Sequence<T>* lst) = 0;
        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
};
