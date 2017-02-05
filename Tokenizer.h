#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <sstream>
#include <iterator>
using namespace std;
//Tokenizer class deals with tokenizing the string.
//Tokenizes the string and put them in an array.
//There should be at least one blank space between tokens.
class Tokenizer{
	private:
		string code;
		string* tokens;
	public:
		Tokenizer(string code);
		string* tokenize();
		int numberOfTokens();
};
#endif /* TOKENIZER_H */
