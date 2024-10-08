#ifndef ARRAY_H
#define ARRAY_H
// #define ARRAYSIZE 100

#include <iostream>
#include <cassert>

template <typename T>
class Array {

private:
	// static const int ARRAYSIZE;
	T *pArr_;
	// int size_;

protected:
	static const int ARRAYSIZE;
	
	int size_;

public:
	static int getArrayDefaultSize();				// array클래스와 관련된 전역함수(static)
	
	explicit Array(int size = ARRAYSIZE);			// int 타입 객체로 Array타입 객체로 묵시적으로 변환되는것을 막음(explicit 사용)
	Array(const T *pArr, int size);
	Array(const Array<T>& rhs);
	virtual ~Array();
	
	// Array<T> *operator & () { return this; }
	// const Array<T> *operator & () const { return this; }
	
	Array<T>& operator = (const Array<T>& rhs);
	
	bool operator == (const Array<T>& rhs) const;
	// bool operator != (const Array<T>& rhs) const;
	
	virtual T& operator [] (int index);				// virtual - 동적 바인딩을 위한 키워드(반드시 소멸자도 virtual 사용해야됨!)
	virtual const T& operator [] (int index) const;
	
	int size() const;
};

template <typename T>
const int Array<T>::ARRAYSIZE = 100;

template <typename T>
int Array<T>::getArrayDefaultSize() {
	return Array<T>::ARRAYSIZE;
}

template <typename T>
Array<T>::Array(int size) 
: pArr_(new T[size]), size_(size) {
	assert(pArr_);
}

template <typename T>
Array<T>::Array(const T *pArr, int size)
: pArr_(new T[size]), size_(size){
	assert(pArr_);
	for(int i = 0; i < size; ++i) {
		pArr_[i] = pArr[i];
	}
}

template <typename T>
Array<T>::Array(const Array<T>& rhs)
: pArr_(new T[rhs.size_]), size_(rhs.size_) {
	assert(pArr_);
	for(int i = 0; i < size_; ++i) {
		pArr_[i] = rhs.pArr_[i];
	}
}

template <typename T>
Array<T>::~Array() {
	delete [] pArr_;
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs) {
	if(this != &rhs) {
		delete [] pArr_;
		pArr_ = new T[rhs.size_];
		assert(pArr_);
		size_ = rhs.size_;
		
		for(int i = 0; i < size_; ++i) {
			pArr_[i] = rhs.pArr_[i];
		}
	}
	return *this;
}

template <typename T>	
bool Array<T>::operator == (const Array<T>& rhs) const {
	if(size_ != rhs.size_)
		return false;
	
	int i;
	for(i = 0; i < rhs.size_; ++i)
		if(pArr_[i] != rhs.pArr_[i])
			break;

	
	return (i == rhs.size_);
}

template <typename T>
T& Array<T>::operator [] (int index) {
	return pArr_[index];	
}

template <typename T>
const T& Array<T>::operator [] (int index) const {
	return pArr_[index];
}

template <typename T>
int Array<T>::size() const {
	return size_;
}

#endif
