#ifndef Hashtable_H
#define Hashtable_H

struct wordCount {
	std::string word;
	int count;
	wordCount() {
		word = "";
		count = -1;
	}
};

bool shouldAddWord(std::string word) {

	bool addword = true;
	int quotationmarkCount = 0;

	size_t wordlength = word.length();

	if (((word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z')) && ((word[wordlength - 1] >= 'a' && word[wordlength - 1] <= 'z') || (word[wordlength - 1] >= 'A' && word[wordlength - 1] <= 'Z'))) {
		for (int i = 1; i < wordlength - 2; i++) {
			if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '\'')) {
				addword = false;
				break;
			}
			if (word[i] == '\'') {
				quotationmarkCount++;
				if (quotationmarkCount > 1) {
					addword = false;
					break;
				}
			}
		}
	}
	else {
		addword = false;
	}

	return addword;

}

class hashtable {
public:
	wordCount* table;
	int length;
	int size;

public:

	hashtable(int size) {
		this->size = size;
		length = 0;
		table = new wordCount[size];
	}

	~hashtable() {
		delete[] table;
	}

	void insert(std::string Word, int Count) {

		if (float(length+1) / float(size) > 0.9) {
			rehash();
		}

		int hashIndex = 0;
		int probingItteration = 0;
		for (unsigned int i = 0; i < Word.length(); i++) {
			if (Word[i] >= 'A' && Word[i] <= 'Z') {
				Word[i] = Word[i] + (32);
			}
		}

		for (unsigned int i = 0; i < Word.length(); i++) {
			hashIndex += (i+3) * Word[i] * Word[i];
		}

		while (probingItteration < size) {

			if (table[(hashIndex + (probingItteration * probingItteration)) % size].word == Word) {
				table[(hashIndex + (probingItteration * probingItteration)) % size].count += Count;
				return;
			}
			else {
				if (table[(hashIndex + (probingItteration * probingItteration)) % size].count == -1) {
					table[(hashIndex + (probingItteration * probingItteration)) % size].word = Word;
					table[(hashIndex + (probingItteration * probingItteration)) % size].count = Count;

					length++;
					return;
				}
				else {
					probingItteration++;
				}
			}
		}

	}

	void rehash() {

		hashtable newtable(size * 2);

		for (int i = 0; i < size; i++) {
			if (table[i].count != -1) {
				newtable.insert(table[i].word, table[i].count);
			}
		}

		table = new wordCount[size*2];
		for (int i = 0; i < size * 2; i++) {
			table[i].count = newtable.table[i].count;
			table[i].word = newtable.table[i].word;
		}
		size = size * 2;
	}

	void remove(std::string deleteWord) {
		for (int i = 0; i < size; i++) {
			if (table[i].word == deleteWord) {
				table[i].word = "";
				table[i].count = -1;
				return;
			}
		}
	}

	wordCount* top10() {

		wordCount* sortedList = new wordCount[10];
		wordCount* tempList = new wordCount[size];

		for (int i = 0; i < size; i++) {
			tempList[i].count = table[i].count;
			tempList[i].word = table[i].word;
		}

		int max = 0;
		int maxPosition;

		for (int i = 0; i < 10; i++) {
			sortedList[i].count = -1;
			sortedList[i].word = "";
		}
		for (int i = 0; i < 10; i++) {
			max = 0;
			maxPosition = 0;
			for (int j = 0; j < size; j++) {
				if (tempList[j].count > max) {
					max = tempList[j].count;
					maxPosition = j;
				}
			}
			sortedList[i] = tempList[maxPosition];
			tempList[maxPosition].count = -1;
			tempList[maxPosition].word = "";
		}
		return sortedList;
	}

	wordCount* fastertop10() {

		wordCount* sortedList = new wordCount[10];

		int max = 0;
		int maxPosition;

		for (int i = 0; i < 10; i++) {
			max = 0;
			maxPosition = 0;
			for (int j = 0; j < size; j++) {
				if (table[j].count > max) {
					max = table[j].count;
					maxPosition = j;
				}
			}
			sortedList[i] = table[maxPosition];
			table[maxPosition].count = -1;
			table[maxPosition].word = "";
		}
		return sortedList;
	}

};

#endif