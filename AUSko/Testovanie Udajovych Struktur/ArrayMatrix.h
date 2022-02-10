#pragma once
#include "ArrayList.h"
#include "Matrix.h"
#include <crtdbg.h>

using namespace std;

/// <summary>Trieda Matica tvorena polom poli</summary>
/// <typeparam name = "T"> Typ ukladanych dat  < / typepram>
template<typename T>
struct ArrayMatrix : public Matrix<T> {
	/// <summary>Pocet riadkov</summary>
	int rows_;
	/// <summary>Pocet stlpcov</summary>
	int columns_;
	/// <summary>Pole poli</summary>
	ArrayList<ArrayList<T>*>* array_;
	/// <summary> Konstruktor Matice </summary>
	/// <param name = "column"> pocet stlpcov</param>
	/// <param name = "rows"> pocet riadkov</param>
	ArrayMatrix(const int row, const int column);

	/// <summary> Destruktor Matice </summary>
	~ArrayMatrix();
	
	/// <summary>Nastavnie prvku na pozcii</summary>
	/// <param name = "column">Stlpec prvku</param>
	/// <param name = "row">Riadok prvku</param>
	/// <param name = "data">Data na nastavenie</param>
	void set(const int row, int column, const T& data);
	
	/// <summary>Ziskanie prvku na pozcii</summary>
	/// <param name = "column">Stlpec prvku</param>
	/// <param name = "row">Riadok prvku</param>
	/// <returns> Prvok na pozicii </returns>
	T& get(const int row, const  int column);
	
	/// <summary>Vrati pocet stlpcov</summary>
	/// <returns> Pocet stlpcov </returns>
	int getColumns();
	
	/// <summary> Vrati pocet riadkov</summary>
	/// <returns> PocetRiadkov </returns>
	int getRows();
};

template<typename T>
ArrayMatrix<T>::ArrayMatrix(int row, int column) :
	rows_(row),
	columns_(column) {
		this->array_ = new ArrayList<ArrayList<T>*>(this->rows_);
		for (int i = 0; i < this->rows_; i++) {
			this->array_->add(new ArrayList<T>(this->columns_));
		}
}

template<typename T>
ArrayMatrix<T>::~ArrayMatrix() {
	for (int i = 0; i < this->array_->size_; i++) {
		delete this->array_->get(i);
	}
	delete this->array_;
}

template<typename T>
void ArrayMatrix<T>::set(int row, int column, const T& data) {
	ArrayList<T>* ar = this->array_->get(row);
	ar->set(column, data);
}

template<typename T>
T& ArrayMatrix<T>::get(int row, int column) {
	ArrayList<T>* ar = this->array_->get(row);
	return ar->get(column);
}

template<typename T>
int ArrayMatrix<T>::getColumns() {
	return columns_;
}

template<typename T>
int ArrayMatrix<T>::getRows() {
	return rows_;
}