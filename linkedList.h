#ifndef linkedList_H
#define linkedList_H

template<typename T>
struct node {
	T data;
	node* link;
};

template<typename T>
class linkedList {
private:
	node<T>* first;
	node<T>* last;
	node<T>* current;
	int currentPosition;
public:
	int size;

	linkedList() {
		first = NULL;
		last = NULL;
		current = NULL;
		currentPosition = 0;
		size = 0;
	}

	linkedList(const linkedList& otherList) {
		size = otherList.size;
		currentPosition = otherList.currentPosition;
		if (otherList.size == 0) {
			first = NULL;
			last = NULL;
			current = NULL;
		}
		else
		{
			node<T>* temp = otherList.first;
			first = new node<T>;
			first->data = temp->data;
			first->link = NULL;
			last = first;
			current = first;
			temp = temp->link;
			int i = 0;
			while (temp->link != NULL)
			{
				node<T>* newnode = new node<T>;
				newnode->data = temp->data;
				newnode->link = temp->link;
				if (i == otherList.currentPosition) {
					current = newnode;
				}
				last->link = newnode;
				last = newnode;
				temp = temp->link;
			}
		}
	}


	~linkedList() {
		node<T>* temp;
		while (first != NULL)
		{
			temp = first;
			first = first->link;
			delete temp;
		}
	}

	void insert(T newData) {
		node<T>* newNode = new node<T>;
		newNode->data = newData;
		newNode->link = NULL;
		if (last != NULL) {
			last->link = newNode;
			last = newNode;
		}
		else {
			first = newNode;
			last = newNode;
			current = newNode;
			newNode->link = NULL;
		}
		size++;
	}

	void removeAtPosition(int position) {
		node<T>* prev;
		node<T>* temp;
		temp = first;
		prev = first;
		for (int i = 0; i < position; i++) {
			prev = temp;
			temp = temp->link;
		}
		prev->link = temp->link;
		delete temp;
		size--;
	}

	void remove(T deleteData) {
		node<T>* prev;
		node<T>* temp;
		temp = first;
		prev = first;
		for (int i = 0; i < size - 1; i++) {
			prev = temp;
			temp = temp->link;
			if (temp->data == deleteData) {
				prev->link = temp->link;
				delete temp;
				size--;
				return;
			}
		}
	}

	T at(int position) {
		node<T>* temp = first;
		for (int i = 0; i < position; i++) {
			temp = temp->link;
		}
		return temp->data;
	}

	T getCurrentAndMove() {
		T data = current->data;
		if (current->link != NULL) {
			current = current->link;
		}
		return data;
	}
	T getCurrent() {
		return current->data;
	}
	void resetCurrent() {
		current = first;
	}

};

#endif