#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>
#include "Assembly.h"
#include "Tokenizer.h"
using namespace std;
//Parser class deals with parsing.
//Tokenizing the initial string through Tokenizer class.
//While parsing, writes the assembly code through Assembly class.
class Parser {
	private:
		Assembly convert;
		Tokenizer* toker;
		string *current_token;
		int i;
		void match_token();
		void stm();
		void opt_stmts();
		void stmt_list();
		void expr();
		void moreterms();
		void term();
		void morefactors();
		void factor();
		bool is_number(const string& s);
		bool is_id(string str);
		stack<int> counter;
	public:
		Parser(string str);
		void run();
		void end();
		string getAssemblyCode();
};
