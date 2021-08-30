#pragma once
#include <cassert>

template <class T> class DynamicArray {

	private:

		T* container;
		int length;//используемая память
		int reserved;//выделенная память

    public:

		DynamicArray(int newReserved) {//считаем, что каждый элемент добавляется в конец, иначе поле length в общем-то теряет смысл и реализация значительно усложняется
			assert(newReserved > 0);
            container = new T[newReserved];
            length = 0;
            reserved = newReserved;
		}

		DynamicArray(T* items, int count_) {
			container = new T[count_];
			length = count_;
			reserved = count_;
			for (int j = 0; j < count_; j++) {
				container[j] = items[j];
			}
		}

		/*DynamicArray(const DynamicArray<T>& arr) {
			container = new T[arr.reserved];
			length = arr.length;
			reserved = arr.reserved;
			for (int j = 0; j < arr.length; j++) {
				container[j] = (arr.container)[j];
			}
		}*/

		DynamicArray(DynamicArray<T>* arr) {
			container = new T[arr->reserved];
			length = arr->length;
			reserved = arr->reserved;
			for (int j = 0; j < arr->length; j++) {
				container[j] = (arr->container)[j];
			}
		}

		T Get(int index) const{
		    assert(index < length || !index);//length
		    assert(index >= 0);
            return container[index];
		}

		int GetSize() const{
			return length;
		}

		int GetReserved() const{
		    return reserved;
		}

		void Set(int index, T value) {
		    assert(index < reserved);
		    assert(index >= 0);
            container[index] = value;
		}

		void Resize(int newReserved) {
		    assert(newReserved > 0);
            T* temp = new T[newReserved];
            int end_ = (newReserved >= reserved) ? length : newReserved;
            for (int j = 0; j < end_; j++) {
                temp[j] = container[j];
            }
            delete[] container;
            container = temp;
            length = end_;
            reserved = newReserved;
		}

		void Relen(int newLength){
		    assert(newLength > 0);
		    length = newLength;
		}
};


