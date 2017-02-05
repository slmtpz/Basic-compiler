#include "Parser.h"

//Constructs the parser object.
Parser::Parser(string str){
	i = 1;
	toker = new Tokenizer(str);
	current_token = toker->tokenize();
}

//Starts parsing and writing the code.
void Parser::run(){
	convert.begin();
	stm();
}

//Ends parsing and writing the code.
void Parser::end(){
	convert.end();
}

//Gets the assembly code prepared in Assembly object
//and returns it.
string Parser::getAssemblyCode(){
	return convert.getCode();
}

//Whenever a token is matched, the function is called.
//Sets pointer on tokens array to next index.
void Parser::match_token(){
	current_token++;
}

//Checks if a string implies a number or not.
bool Parser::is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

//Checks if a string implies an id or not.
bool Parser::is_id(string str){
	return (!(str == "begin" || str == "end" || str == "(" || str == "print" ||
			str == ")" || str == "*" || str == "/" || str == "read" ||
			str == "%" || str == "+" || str == "-" || str == "do" ||
			str == ";" || str == "if" || str == "while" || str == "=" || is_number(str)));
}

/**********RECURSIVE PARSING***********/
//Parse the string in order for a specific mylang grammar.
//The comments indicates what the corresponding function can go to.
//Also, gives syntax error when expected.

// (expr) | id | num
void Parser::factor(){
	if(*current_token == "("){
		match_token();
		expr();
			if(*current_token == ")"){
				match_token();
			}
	} else if (is_number(*current_token)){
		convert.push_num(*current_token);
		match_token();
	} else if (is_id(*current_token)){
		convert.push_val_var(*current_token);
		match_token();
	} else {
		cout << "Syntax Error !";
		exit(0);
	}
}

// * factor morefactors | / factor morefactors | % factor morefactors | ε
void Parser::morefactors(){
	if(*current_token == "*"){
		match_token();
		factor();
		convert.mul();
		morefactors();
	} else if (*current_token == "/"){
		match_token();
		factor();
		convert.div();
		morefactors();
	} else if (*current_token == "%"){
		match_token();
		factor();
		convert.mod();
		morefactors();
	}
}

// factor morefactors
void Parser::term(){
	factor();
	morefactors();
}

// + term moreterms | - term moreterms | ε
void Parser::moreterms(){
	if(*current_token == "+"){
		match_token();
		term();
		convert.add();
		moreterms();
	} else if (*current_token == "-"){
		match_token();
		term();
		convert.sub();
		moreterms();
	}
}

// term moreterms
void Parser::expr(){
	term();
	moreterms();
}

// stm ; stmt_list | stm
void Parser::stmt_list(){
	stm();
	if(*current_token == ";"){
		match_token();
		stmt_list();
	}
}

// stmt_list | ε
void Parser::opt_stmts(){
	if(*current_token != "end")
		stmt_list();
}

// id = expr | print expr | read id | if expr then stm | while expr do stm | begin opt_stmts end
void Parser::stm(){

	if(is_id(*current_token)){
		convert.push_add_var(*current_token);
		match_token();
		if(*current_token == "="){
			match_token();
			expr();
			convert.assign();
		} else {
			cout << "Syntax Error !";
			exit(0);
		}

	} else if (*current_token == "print") {
		match_token();
		expr();
		convert.print();

	} else if (*current_token == "read") {
		match_token();
		if(is_id(*current_token)){
			convert.read(*current_token);
			match_token();
		} else {
			cout << "Syntax Error !";
			exit(0);
		}

	} else if (*current_token == "if") {
		match_token();
		expr();
		counter.push(i);
		convert.ifFirst(i++);
		if(*current_token == "then"){
			match_token();
			stm();
			int m = counter.top();
			counter.pop();
			convert.ifSecond(m);
		} else {
			cout << "Syntax Error !";
			exit(0);
		}

	} else if (*current_token == "while") {
		match_token();
		counter.push(i);
		convert.whileFirst(i++);
		expr();
		convert.whileSecond(i++);
		if(*current_token == "do"){
			match_token();
			stm();
			int m = counter.top();
			counter.pop();
			convert.whileThird(m);
		} else {
			cout << "Syntax Error !";
			exit(0);
		}

	} else if (*current_token == "begin") {
		match_token();
		opt_stmts();
		if(*current_token == "end"){
			match_token();
		} else {
			cout << "Syntax Error !";
			exit(0);
		}
	}
}
