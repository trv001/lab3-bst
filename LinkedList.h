#pragma once
#include <cassert>

template <class T> class LinkedListNode {

	public:

		LinkedListNode<T>* next;
		LinkedListNode<T>* prev;
		T value;

		LinkedListNode(T val) {
			next = NULL;
			value = val;
		}

};

template <class T> class LinkedList {

	private:

		LinkedListNode<T>* head;
		LinkedListNode<T>* tail;
		int length;

		LinkedListNode<T>* GetPtr(int index) const{
			assert(index >= 0 && index < length);
			LinkedListNode<T>* ptr = head;
			for (int i = 0; i < index; i++) {
				ptr = ptr->next;
			}
			return ptr;
		}

    public:

		LinkedList(const LinkedList<T>& lst) {
			LinkedListNode<T>* ptr = head;
			LinkedListNode<T>* ptr_prev = head;
			LinkedListNode<T>* lst_ptr = lst.head;
			ptr = new LinkedListNode<T>(lst_ptr->value);
			for (int i = 1; i < lst.length; i++) {
				ptr = ptr->next;
				lst_ptr = lst_ptr->next;
				ptr = new LinkedListNode<T>(lst_ptr->value);
				ptr->prev = ptr_prev;
				ptr->prev = ptr_prev->next;
			}
			tail = ptr;
			length = lst.length;
		}

		LinkedList(T* items, int count_) {
			LinkedListNode<T>* ptr = head;
			LinkedListNode<T>* ptr_prev = head;
			ptr = new LinkedListNode<T>(items[0]);
			for (int i = 1; i < count_; i++) {
				ptr = ptr->next;
				ptr = new LinkedListNode<T>(items[i]);
				ptr->prev = ptr_prev;
				ptr_prev = ptr_prev->next;
			}
			tail = ptr;
			length = count_;
		}

		LinkedList() {
			head = NULL;
			tail = NULL;
			length = 0;
		}

		T GetFirst() const{
		    assert(head != NULL);
			return head->value;
		}

		T GetLast() const{
		    assert(tail != NULL);
			return tail->value;
		}

		T Get(int index) const{
		    assert(index < length);
		    assert(index >= 0);
			return GetPtr(index)->value;
		}

		int GetLength() const{
			return length;
		}

		void Append(T item) {
			if (head != NULL) {
				tail->next = new LinkedListNode<T>(item);
				(tail->next)->prev = tail;
				tail = tail->next;
			}
			else {
				head = new LinkedListNode<T>(item);
				tail = head;
				head->next = tail;
				tail->prev = head;
			}
			length++;
		}

		void Prepend(T item) {
			if (head != NULL) {
				head->prev = new LinkedListNode<T>(item);
				(head->prev)->next = head;
				head = head->prev;
			}
			else {
				head = new LinkedListNode<T>(item);
				tail = head;
				head->next = tail;
				tail->prev = head;
			}
			length++;
		}

		T Pop(){
		    T item = tail->value;
		    tail = tail->prev;
		    delete tail->next;
		    tail->next = NULL;
		    return item;
		}

		void Set(int index, T item) {
            assert(index < length);
            assert(index >= 0);
			GetPtr(index)->value = item;
		}

		void InsertAt(T item, int index) {
            assert(index < length - 1);
            assert(index >= 0);
			LinkedListNode<T>* new_node = new LinkedListNode<T>(item);
			LinkedListNode<T>* p1 = GetPtr(index);
			LinkedListNode<T>* p2 = GetPtr(index + 1);
			p1->next = new_node;
			new_node->prev = p1;
			new_node->next = p2;
			p2->prev = new_node;
			length++;
		}

		LinkedList<T>* GetSubList(int startIndex, int endIndex) const{
		    assert(startIndex >= 0 && startIndex < length);
		    assert(endIndex >= 0 && endIndex < length);
		    //assert(startIndex <= endIndex);
			LinkedList<T>* sublist = new LinkedList<T>;
			for (int i = startIndex; i <= endIndex; i++) {
				sublist->Append(this->Get(i));
			}
			return sublist;
		}

		LinkedList<T>* Concat(LinkedList<T>* lst) {
			LinkedList<T>* res = new LinkedList<T>;
			for (int i = 0; i < GetLength(); i++) {
				res->Append(Get(i));
			}
			for (int i = 0; i < lst->GetLength(); i++) {
				res->Append(lst->Get(i));
			}
			return res;
		}
};
