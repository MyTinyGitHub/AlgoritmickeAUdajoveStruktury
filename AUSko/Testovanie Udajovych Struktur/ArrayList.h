#pragma once
#include "List.h"
#include <crtdbg.h>

/// <summary> Datova Struktura ArrayList </summary>
/// <typeparam name = "T"> Typ ukladanych dat  < / typepram>
template <typename T>
struct ArrayList : public List<T> {
	/// <summary> Urcuje aktualnu velkost pola</summary>
	size_t size_;
	/// <summary> Urcuje kapacitu pola </summary>
	size_t capacity_;
	/// <summary> Vektor s datami </summary>
	T* array_;
	/// <summary> Bezparametricky konstruktor. </summary>
	ArrayList();
	/// <summary>Konstruktor. </summary>
	/// <param name = "capacity"> urcuje prvotnu kapacitu. </param>
	ArrayList(const size_t capacity);
	/// <summary> Destruktor. </summary>
	~ArrayList();
	/// <summary> Funkcia vlozenia. </summary>
	/// <param name = "data"> Data na vlozenie. </param>
	void add(const T& data);
	/// <summary> Funkcia vlozenia na prvy index. </summary>
	/// <param name = "data"> Data na vlozenie. </param>
	void addFirst(const T& data);
	/// <summary> Funkcia vlozenia na index. </summary>
	/// <param name = "data"> data na vlozenie </param>
	void addOnIndex(const T& data, int index);
	/// <summary> Funkcia na zmazanie prveho prvku. </summary>
	/// <returns> Kopiu zmazaneho prvok. </returns>
	T& removeFirst();
	/// <summary> Funkcia na zmazanie posledneho prvku. </summary>
	/// <returns> Kopiu zmazaneho prvku. </returns>
	T& removeLast();
	/// <summary> Zmaze prvok na indexe. </summary>
	/// <param name = "index"> Index na vlozenie. </param>
	/// <returns> Kopiu zmazaneho prvku. </returns>
	T& removeAt(int index);
	/// <summary> Funkcia na zmazanie prvku na indexe. </summary>
	/// <param name = "index"> Index na zmazanie. </param>
	/// <returns> Kopiu zmazaneho prvku. </returns>
	T& get(int index);
	/// <summary> Nahradi prvok na indexe. </summary>
	/// <param name = "index"> Index na nastavenie. </param>
	/// <param name = "data"> Data na nastavenie. </param>
	void set(int index, const T& data);
	/// <summary> Najde prvok s rovnakymi datami. </summary>
	/// <param name = "data"> Data na najdenie. </param>
	/// <returns> Index prvku </returns>
	int index(const T data);
	/// <summary> Funkcia na zvacsenie pola. </summary>
	void enlarge();
	/// <summary> Funkcia na skopirovanie pola. </summary>
	/// <param name = "src"> Zdroj z ktoreho budeme kopirtovat. </param>
	/// <param name = "srcIndex"> Index od ktoreho sa bude kopirovat. </param>
	/// <param name = "dest"> Kam sa bude kopirovat. </param>
	/// <param name = "destIndex"> Index na ktorom sa zacne kopirovanie. </param>
	void copy(T* src, int srcIndex, T* dest, int destIndex);
	/// <summary> Vrati velkost pola. </summary>
	/// <returns> Velkost pola. </returns>
	int size();
};

template <typename T>
ArrayList<T>::ArrayList() :ArrayList(4) {

}

template <typename T>
ArrayList<T>::ArrayList(const size_t capacity) :
	size_(0),
	capacity_(capacity) {
	this->array_ = reinterpret_cast<T*>(calloc(capacity_, sizeof(T)));
}


template <typename T>
ArrayList<T>::~ArrayList() {
	free(this->array_);
	this->size_ = 0;
	this->capacity_ = 0;
}

template <typename T>
inline void ArrayList<T>::add(const T& data) {
	this->array_[this->size_] = data;
	this->size_++;
	if (this->size_ >= this->capacity_) this->enlarge();
}


template <typename T>
inline void ArrayList<T>::addFirst(const T& data) {
	this->copy(this->array_, 0, this->array_, 1);
	this->array_[0] = data;
	this->size_++;
	if (this->size_ >= this->capacity_)	this->enlarge();
}


template <typename T>
inline void ArrayList<T>::addOnIndex(const T& data, int index) {
	if (this->size_ + 1 >= this->capacity_)	this->enlarge();
	this->copy(this->array_, index, this->array_, index + 1);
	this->array_[index] = data;
	this->size_++;

}

template <typename T>
inline T& ArrayList<T>::removeFirst() {
	return this->removeAt(0);
}

template <typename T>
inline T& ArrayList<T>::removeLast() {
	return removeAt(this->size_ - 1);
}

template <typename T>
inline T& ArrayList<T>::removeAt(int index) {
	if (this->size_ == 0) {
	}
	else {
		T temp = this->array_[index];
		this->copy(this->array_, index + 1, this->array_, index);
		this->size_--;
		return temp;
	}
}

template <typename T>
inline T& ArrayList<T>::get(int index) {
	return this->array_[index];
}

template <typename T>
inline void ArrayList<T>::set(int index, const T& data) {
	this->array_[index] = data;
}

template <typename T>
inline int ArrayList<T>::index(const T data) {
	for (int i = 0; i < this->size_; i++) {
		if (this->array_[i] == data) {
			return i;
		}
	}
	return -1;
}

template <typename T>
inline void ArrayList<T>::enlarge() {
	this->capacity_ = this->capacity_ * 2;
	T* temp = reinterpret_cast<T*>(calloc(this->capacity_, sizeof(T)));
	copy(this->array_, 0, temp, 0);
	free(this->array_);
	this->array_ = temp;
}


template <typename T>
inline void ArrayList<T>::copy(T* src, int srcIndex, T* dest, int destIndex) {
	int length = (this->size_ - srcIndex) * sizeof(T);
	if (&src[srcIndex] <= &dest[destIndex] && &dest[destIndex] <= &src[srcIndex + length] ||
		&dest[destIndex] <= &src[srcIndex] && &src[srcIndex] <= &dest[destIndex + length]) {
		memmove(&dest[destIndex], &src[srcIndex], length);
	
	}
	else {
		memcpy(&dest[destIndex], &src[srcIndex], length);
	}

}

template<typename T>
inline int ArrayList<T>::size() {
	return this->size_;
}