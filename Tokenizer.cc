#include "Tokenizer.h"
//Constructs Tokenizer object.
Tokenizer::Tokenizer(string code){
	this->code = code;
	int N = numberOfTokens();
	tokens = new string[N];
}

/*****************TOKENIZER*****************/

//Tokenizes the string and return the pointer of the first index of tokens array.
string* Tokenizer::tokenize(){
	stringstream st(code);
	int i = 0;
	while(st >> tokens[i]){
		i++;
	}
	return tokens;
}

//Calculates the number of tokens in the string to declare range of tokens array.
int Tokenizer::numberOfTokens(){
	stringstream stream(code);
	return distance(istream_iterator<string>(stream), istream_iterator<string>());
}
