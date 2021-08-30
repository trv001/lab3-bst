#pragma once
#include "Sequence.h"

template <class T> class ListSequence : public Sequence<T>{

	private:

  		LinkedList<T>* lst;

	public:

        ListSequence() {
            lst = new LinkedList<T>;
        }

        ListSequence(T* items, int count_) {
            lst = new LinkedList<T>(*items, count_);
        }

        ListSequence(const LinkedList<T>& cpy) {
            lst = new LinkedList<T>(cpy);
        }

        T GetFirst() const{
            return lst->GetFirst();
        }

        T GetLast() const{
            return lst->GetLast();
        }

        T Get(int index) const{
            return lst->Get(index);
        }

        int GetLength() const{
            return lst->GetLength();
        }

        int GetReserved() const{
            return lst->GetLength();
        }

        void Set(int index, T item) {
            lst->Set(index, item);
        }

        T Pop(){
            return lst->Pop();
        }

        void Append(T item) {
            lst->Append(item);
        }

        void Prepend(T item) {
            lst->Prepend(item);
        }

        void InsertAt(T item, int index) {
            lst->InsertAt(item, index);
        }

        ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const{
            assert(startIndex >= 0 && startIndex < GetLength());
		    assert(endIndex >= 0 && endIndex < GetLength());
		    //assert(startIndex <= endIndex);
            ListSequence<T>* sublist = new ListSequence<T>;
            for (int i = startIndex; i <= endIndex; i++) {
                sublist->Append(Get(i));
            }
            return sublist;
        }

        ListSequence<T>* Concat(Sequence<T>* lst) {
            ListSequence<T>* res = new ListSequence<T>;
            for (int i = 0; i < GetLength(); i++) {
                res->Append(Get(i));
            }
            for (int i = 0; i < lst->GetLength(); i++) {
                res->Append(lst->Get(i));
            }
            return res;
        }
};
