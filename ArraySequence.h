#pragma once
#include "Sequence.h"

template <class T> class ArraySequence : public Sequence<T> {

	private:

		DynamicArray<T>* arr;

	public:

		ArraySequence(T* items, int count_){
		    arr = new DynamicArray<T>(items, count_);
		}

		ArraySequence(const ArraySequence<T>& cpy){
            arr = new DynamicArray<T>(cpy.arr);
		}

		ArraySequence(int size_){
		    arr = new DynamicArray<T>(size_);
		}

		ArraySequence(const LinkedList<T>& lst){//
            arr = new DynamicArray<T>(lst.GetLength());
            for(int i = 0; i < lst.GetLength(); i++){
                arr->Set(lst.Get(i), i);
            }
		}

		int GetLength() const{
		    return arr->GetSize();
		}

		int GetReserved() const{
		    return arr->GetReserved();
		}

		T GetLast() const{
		    if(!GetLength()){
                return GetFirst();
		    }
		    return arr->Get(GetLength() - 1);
		}

		T GetFirst() const{
		    return arr->Get(0);
		}

		T Get(int index) const{
		    return arr->Get(index);
		}

		void Set(int index, T item){
		    arr->Set(index, item);
		}

		void Append(T item){
		    if(arr->GetSize() == arr->GetReserved()){
                arr->Resize(arr->GetReserved() + 1);
		    }
		    arr->Set(GetLength(), item);
		    arr->Relen(arr->GetSize() + 1);
		}

		void Prepend(T item){
		    if(arr->GetSize() == arr->GetReserved()){
                arr->Resize(arr->GetReserved() + 1);
		    }
            for(int i = GetLength() - 1; i >= 0; i--){
                arr->Set(i + 1, Get(i));
            }
            arr->Set(0, item);
            arr->Relen(arr->GetSize() + 1);

		}

        ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const{
            assert(startIndex >= 0 && startIndex < GetLength());
		    assert(endIndex >= 0 && endIndex < GetLength());
		    //assert(startIndex <= endIndex);
            ArraySequence<T>* subarr = new ArraySequence<T>(endIndex - startIndex + 1);
            for (int i = startIndex; i <= endIndex; i++) {
                subarr->Set(i, Get(i));
            }
            return subarr;
        }

		ArraySequence<T>* Concat(Sequence<T>* lst){
            ArraySequence<T>* res = new ArraySequence<T>(arr->GetReserved() + lst->GetReserved());//
            for (int i = 0; i < GetLength(); i++) {
                res->Append(Get(i));
            }
            for (int i = 0; i < lst->GetLength(); i++) {
                res->Append(lst->Get(i));
            }
            return res;
		}

		void InsertAt(T item, int index){
		    if(arr->GetSize() == arr->GetReserved()){
                arr->Resize(arr->GetReserved() + 1);
		    }
		    for(int i = index + 1; i < GetLength(); i++){
                arr->Set(i + 1, Get(i));
            }
            arr->Set(index + 1, item);
            arr->Relen(arr->GetSize() + 1);
		}
};
