#pragma once
#include <iostream>
#include <crtdbg.h>

using namespace std;

class BitMap {
public:
	int min;
	int max;
	int size;
	int velkost;

	unsigned long long* x;
	BitMap(int min, int max);
	~BitMap();

	bool isBitSet(int bit);
	void setBit(int bit);
	void removeBit(int bit);
	bool jeRovna(BitMap* bitmap);
	bool jePodmnozina(BitMap* bitmap);
	BitMap* zjednotenie(BitMap* bitmap);
	BitMap* prienik(BitMap* bitmap);
	BitMap* rozdiel(BitMap* bitmap);
};


BitMap::~BitMap() {
	delete []x;
}


BitMap::BitMap(int min, int max) {
	this->min = min;
	this->max = max + 1;
	this->size = (this->max - this->min) / 64;
	this->size++;
	this->velkost = max - min;
	this->x = new unsigned long long[size];


	for (int i = 0; i < size; i++) {
		x[i] = 0;
	}
}

bool BitMap::isBitSet(int bit) {
	if (bit > max - min) {
		return false;
	}
	else {
		return 1 == ((x[bit / 64] >> bit % 64) & 1);
	}

}

void BitMap::setBit(int bit) {
	if (bit > max - min) {
		return;
	}
	else {
		x[bit / 64] |= 1ULL << bit % 64;
	}
}

void BitMap::removeBit(int bit) {
	if (bit > max - min) {
		return;
	}
	else {
		x[bit / 64] &= ~(1ULL << bit % 64);
	}
}

bool BitMap::jeRovna(BitMap* bitmap) {
	if (this->min != bitmap->min || this->max != bitmap->max) {
		return false;
	}
	else {
		for (int i = 0; i <= size; i++) {
			if (x[i] == bitmap->x[i]) {
			}
			else {
				return false;
			}
		}
		return true;
	}
}


bool BitMap::jePodmnozina(BitMap* bitmap) {
	if (jeRovna(bitmap)) {
		return true;
	}
	else {
		for (int i = min; i <= max; i++) {
			if (bitmap->isBitSet(i) && !isBitSet(i)) {
				return false;
			}
		}
	}
}


BitMap* BitMap::zjednotenie(BitMap* bitmap) {
	int min;
	int max;

	if (this->min < bitmap->min) {
		min = this->min;
	}
	else {
		min = bitmap->min;
	}

	if (this->max > bitmap->max) {
		max = this->max;
	}
	else {
		max = bitmap->max;
	}

	BitMap* new_bitmap = new BitMap(min, max);


	for (int i = min; i <= max; i++) {
		if (bitmap->isBitSet(i)) {
			new_bitmap->setBit(i);
		}
		else if (this->isBitSet(i)) {
			new_bitmap->setBit(i);
		}
	}
	return new_bitmap;
}


BitMap* BitMap::prienik(BitMap* bitmap) {
	int min;
	int max;

	if (this->min > bitmap->min) {
		min = this->min;
	}
	else {
		min = bitmap->min;
	}

	if (this->max < bitmap->max) {
		max = this->max;
	}
	else {
		max = bitmap->max;
	}

	BitMap* new_bitmap = new BitMap(min, max);

	for (int i = min; i <= max; i++) {
		if (bitmap->isBitSet(i) && isBitSet(i)) {
			new_bitmap->setBit(i);
		}
	}

	return new_bitmap;
}

BitMap* BitMap::rozdiel(BitMap* bitmap) {
	BitMap* new_bitmap = new BitMap(min, max);
	for (int i = min; i <= max; i++) {
		if (!bitmap->isBitSet(i) && isBitSet(i)) {
			new_bitmap->setBit(i);
		}
	}

	return new_bitmap;
}