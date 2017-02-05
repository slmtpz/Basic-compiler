#include <fstream>
#include "Parser.h"
#include "Tokenizer.h"

int main(int argc, char *argv[]){
	if(argc < 2){
		cout<<"Usage: ./a.out <input_name> <output_name>\n";
		return 0;
	}

	/******INPUT******/
	string inputFile = argv[1];
	string outputFile = argv[2];
    ifstream ifs(inputFile.c_str(), ios::in);
	if(!ifs.is_open()){
		cout<<"Input file fails to open.\n";
		return 0;
	}
	string str( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>() ) );
	ifs.close();

	/******PARSER OBJECT******/
	Parser pars(str);
	pars.run();
	pars.end();

	/******ASSEMBLY CODE******/
	string code = pars.getAssemblyCode();

	/******OUTPUT******/
    ofstream ofs(outputFile.c_str(), ios::out);
	ofs << code;
	ofs.close();
	return 0;
}
