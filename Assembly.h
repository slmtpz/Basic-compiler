#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include <iostream>
#include <set>
#include <sstream>
using namespace std;
//Assembly class deals with converting instructions given by Parser to Assembly code.
class Assembly{
	private:
		stringstream ss;
		string write;
		int is_printed;
		int is_read;
		void call_myprint();
		void call_myread();
		void add_variables();
		set<string> variables;
	public:
		Assembly();
		void begin();
		void end();
		void push_add_var(string var);
		void push_num(string num);
		void push_val_var(string var);
		void mul();
		void div();
		void add();
		void sub();
		void mod();
		void assign();
		void print();
		void read(string id);
		void ifFirst(int i);
		void ifSecond(int i);
		void whileFirst(int i);
		void whileSecond(int i);
		void whileThird(int i);
		void whileFourth(int i);
		string getCode();
};
#endif /* ASSEMBLY_H */
