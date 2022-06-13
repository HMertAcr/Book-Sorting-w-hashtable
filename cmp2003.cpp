#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Hashtable.h"
#include "linkedList.h"

//size_t findwordENDSearcher(std::string text, size_t prev) {<
//	prev = text.find("\":", prev + 1);
//	while (!(text[prev + 2] <= '9' && text[prev + 2] >= '0')) {
//		prev = text.find("\":", prev + 1);
//	}
//
//	int digit = 1;
//	while (text[prev + 2 + digit] <= '9' && text[prev + 2 + digit] >= '0') {
//		digit++;
//	}
//	if ((prev + 2 + digit) < text.length()) {
//		if (text[prev + 2 + digit] != ',' && text[prev + 3 + digit] != '\"') {
//			findwordENDSearcher(text, prev);
//		}
//	}
//	return prev;
//}

//this doesnt get used because its slower

int main() {

	clock_t begin = clock();

	hashtable mainStorage(190000);
	
	linkedList<std::string> textDivided;

	size_t wordSTARTSearcher;
	size_t wordENDSearcher;
	size_t deletionPoint;

	int itteration;
	int newDigit;
	int oldDigit;
	int NewCount;
	int wordCleanerFront;
	int wordCleanerBack;

	std::string NewWord;
	std::string newLine;
	std::string text;

	std::ifstream publicationsDataSetFile("PublicationsDataSet.txt");

	while (std::getline(publicationsDataSetFile, newLine)) {

		deletionPoint = newLine.find("\"unigramCount\":");
		newLine = newLine.substr((deletionPoint + 16), newLine.length() - (deletionPoint + 18));
		textDivided.insert(newLine);

	}

	for (int i = 0; i < textDivided.size; i++) {

		wordSTARTSearcher = 0;
		wordENDSearcher = 0;
		itteration = 0;
		newDigit = 0;
		text = textDivided.getCurrentAndMove();

		while (wordENDSearcher + 8 < text.length()) {

			wordSTARTSearcher = wordENDSearcher;
			wordENDSearcher = text.find("\":", wordENDSearcher + 1);
			//wordENDSearcher = findwordENDSearcher(text, wordENDSearcher);

			while (!(text[wordENDSearcher + 2] <= '9' && text[wordENDSearcher + 2] >= '0')) {
				wordENDSearcher = text.find("\":", wordENDSearcher + 1);
			}

			oldDigit = newDigit;
			newDigit = 1;
			while (text[wordENDSearcher + 2 + newDigit] <= '9' && text[wordENDSearcher + 2 + newDigit] >= '0') {
				newDigit++;
			}
			if ((wordENDSearcher + 2 + newDigit) < text.length()) {
				if (text[wordENDSearcher + 2 + newDigit] != ',' && text[wordENDSearcher + 3 + newDigit] != '\"') {
					wordENDSearcher = text.find("\":", wordENDSearcher + 1);
					while (!(text[wordENDSearcher + 2] <= '9' && text[wordENDSearcher + 2] >= '0')) {
						wordENDSearcher = text.find("\":", wordENDSearcher + 1);
					}
				}
			}

			NewCount = 0;
			newDigit = 0;
			while (text[wordENDSearcher + 2 + newDigit] <= '9' && text[wordENDSearcher + 2 + newDigit] >= '0') {
				NewCount = NewCount * 10;
				NewCount += text[wordENDSearcher + 2 + newDigit] - '0';
				newDigit++;
			}

			if (itteration == 0) {
				NewWord = text.substr(wordSTARTSearcher + 1, wordENDSearcher - (wordSTARTSearcher + 1));
			}
			else {
				NewWord = text.substr(wordSTARTSearcher + 4 + oldDigit, wordENDSearcher - (wordSTARTSearcher + 4 + oldDigit));
			}

			wordCleanerFront = 0;

			while (!((NewWord[wordCleanerFront] >= 'a' && NewWord[wordCleanerFront] <= 'z') || (NewWord[wordCleanerFront] >= 'A' && NewWord[wordCleanerFront] <= 'Z') || (NewWord[wordCleanerFront] >= '0' && NewWord[wordCleanerFront] <= '9'))) {
				wordCleanerFront++;
				if (wordCleanerFront + 1 > NewWord.length()) {
					break;
				}
			}
			if (wordCleanerFront + 1 < NewWord.length()) {
				wordCleanerBack = 0;
				while (!((NewWord[NewWord.length() - (wordCleanerBack + 1)] >= 'a' && NewWord[NewWord.length() - (wordCleanerBack + 1)] <= 'z') || (NewWord[NewWord.length() - (wordCleanerBack + 1)] >= 'A' && NewWord[NewWord.length() - (wordCleanerBack + 1)] <= 'Z') || (NewWord[NewWord.length() - (wordCleanerBack + 1)] >= '0' && NewWord[NewWord.length() - (wordCleanerBack + 1)] <= '9'))) {
					wordCleanerBack++;
				}

				NewWord = NewWord.substr(wordCleanerFront, NewWord.length() - (wordCleanerFront + wordCleanerBack));

				if (shouldAddWord(NewWord)) {
					mainStorage.insert(NewWord, NewCount);
				}

			}

			itteration++;
		}
	}

	std::ifstream stopWordsFile("stopwords.txt");

	while (!stopWordsFile.eof()) {

		stopWordsFile >> newLine;
		mainStorage.remove(newLine);

	}

	wordCount* top10 = new wordCount[10];
	top10 = mainStorage.fastertop10();

	for (int i = 0; i < 10; i++) {
		std::cout << top10[i].count << " " << top10[i].word << std::endl;
	}

	clock_t end = clock();
	std::cout << "Total Elapsed Time: " << (end - begin) << " milliseconds" << std::endl;

}
