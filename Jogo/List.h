#pragma once

#include <iostream>

/*
Classe Lista que já foi implementada durante as aulas no Sistema Acadêmico
*/

template <class TL> class List
{
private:

	template <class TE> class Element
	{
	private:

		Element<TE>* pNext;
		TE* pInfo;

	public:

		Element() {
			pNext = nullptr;
			pInfo = nullptr;
		}

		~Element() {
			pNext = nullptr;
			pInfo = nullptr;
		}

		void setNext(Element<TE>* pN) { this->pNext = pN; }
		Element<TE>* getNext() { return this->pNext; }

		void setInfo(TE* pI) { this->pInfo = pI; }
		TE* getInfo() { return this->pInfo; }

	};

	Element<TL>* pFirst;
	Element<TL>* pLast;

	int size;

public:

	List();
	~List();

	void clear();

	void push(TL* pI);
	TL* pop(TL* pI);

	int getSize() { return this->size; }

	TL* operator[](int index);

	Element<TL>* getFirst() { return this->pFirst; }
	Element<TL>* getLast() { return this->pLast; }

};

template<class TL>
List<TL>::List() {
	this->size = 0;
	this->pFirst = nullptr;
	this->pLast = nullptr;
}

template<class TL>
List<TL>::~List() {
	this->clear();
}

template<class TL>
void List<TL>::clear() {

	if (this->pFirst == nullptr) {
		std::cout << "List is already empty!" << std::endl;
	}

	else {
		Element<TL>* pTmp1 = nullptr;
		Element<TL>* pTmp2 = nullptr;

		pTmp1 = this->pFirst;
		pTmp2 = pTmp1;

		int i = 0;

		while (i < this->size && pTmp1 != nullptr) {
			pTmp2 = pTmp1->getNext();
			delete (pTmp1);
			(this->size)--;
			pTmp1 = pTmp2;
			i++;
		}

		this->pFirst = nullptr;
		this->pLast = nullptr;
	}
}

template<class TL>
void List<TL>::push(TL* pI) {

	if (pI == nullptr) {
		std::cout << "ERROR: pI is nullptr! Element not inserted on the list." << std::endl;
	}

	else {
		Element<TL>* pTmp = nullptr;
		pTmp = new Element<TL>();
		pTmp->setInfo(pI);

		if (this->pFirst == nullptr) {
			this->pFirst = pTmp;
			this->pLast = pTmp;
		}

		else {
			this->pLast->setNext(pTmp);
			this->pLast = this->pLast->getNext();
		}

		(this->size)++;
	}
}

template<class TL>
TL* List<TL>::pop(TL* pI) {

	if (pI == nullptr) {
		std::cout << "ERROR: pI is nullptr! Element couldn't be removed from the list." << std::endl;
		return nullptr;
	}

	else {
		Element<TL>* pTmp = nullptr;
		Element<TL>* pPrevTmp = nullptr;

		pTmp = this->pFirst;
		pPrevTmp = nullptr;

		while (pTmp->getInfo() != pI && pTmp != nullptr) {
			pPrevTmp = pTmp;
			pTmp = pTmp->getNext();
		}

		if (pTmp == nullptr) {
			std::cout << "ERROR: pI doesn't exist on the list! Element coudn't be removed from the list." << std::endl;
			return nullptr;
		}

		else {

			if (pTmp == this->pFirst) {
				this->pFirst = this->pFirst->getNext();
			}

			else if (pTmp == this->pLast) {
				this->pLast = pPrevTmp;
				this->pLast->setNext(nullptr);
			}

			else {
				pPrevTmp->setNext(pTmp->getNext());
			}

			delete (pTmp);
			(this->size)--;
			return pI;
		}
	}
}

template<class TL>
TL* List<TL>::operator[](int index) {

	if (index < 0 || index >= this->size) {
		std::cout << "ERROR: index exceed the boundaries of the list." << std::endl;
		exit(1);
	}

	Element<TL>* pTmp = nullptr;
	pTmp = this->pFirst;

	for (int i = 0; i < index; i++) {
		pTmp = pTmp->getNext();
	}

	if (pTmp == nullptr) {
		std::cout << "ERROR: pTmp is nullptr" << std::endl;
		exit(1);
	}

	return pTmp->getInfo();
}
