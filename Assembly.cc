#include "Assembly.h"
//Constructs Assembly object.
Assembly::Assembly(){
	write = "";
	is_printed = 0;
	is_read = 0;
}

//Returns the Assembly code.
string Assembly::getCode(){
	return write;
}

/********************CODE GENERATING*********************/

//Starts to write the code with segment opening "code segment".
void Assembly::begin(){
	write.append("code segment\n");
}

//Ends to write the code with segment closeing "code ends".
//Also, adds read or print functions to the Assembly code if used.
void Assembly::end(){
	write.append("   int 20h\n");
		if(is_read)
			call_myread();
		if(is_printed)
			call_myprint();
		add_variables();
	write.append("code ends");
}

void Assembly::push_add_var(string var){
	variables.insert("v"+var);
	write.append("   push offset v"+var+"\n");
}

void Assembly::push_num(string num){
	write.append("   push "+num+"\n");
}

void Assembly::push_val_var(string var){
	variables.insert("v"+var);
	write.append("   push v"+var+" w\n");
}

void Assembly::mul(){
	write.append("   pop cx\n"
				 "   pop ax\n"
				 "   mul cx\n"
				 "   push ax\n");
}

void Assembly::div(){
	write.append("   mov dx,0\n"
				 "   pop cx\n"
				 "   pop ax\n"
				 "   div cx\n"
				 "   push ax\n");
}

void Assembly::add(){
	write.append("   pop cx\n"
				 "   pop ax\n"
				 "   add ax,cx\n"
				 "   push ax\n");
}

void Assembly::sub(){
	write.append("   pop cx\n"
				 "   pop ax\n"
				 "   sub ax,cx\n"
				 "   push ax\n");
}

void Assembly::mod(){
	write.append("   mov dx,0\n"
				 "   pop cx\n"
				 "   pop ax\n"
				 "   div cx\n"
				 "   push dx\n");
}

void Assembly::assign(){
	write.append("   pop ax\n"
				 "   pop bx\n"
				 "   mov [bx],ax\n");
}

void Assembly::print(){
	is_printed = 1;
	write.append("   pop ax\n"
				 "   call myprint\n");
}

void Assembly::call_myprint(){
	write.append("myprint:\n"
				 	 "   mov    si,10d\n"
					 "   xor    dx,dx\n"
					 "   push   0Ah\n"
					 "   mov    cx,1d\n"
					 "nonzero:\n"
					 "   div    si\n"
					 "   add    dx,48d\n"
					 "   push   dx\n"
					 "   inc    cx\n"
					 "   xor    dx,dx\n"
					 "   cmp    ax,0h\n"
					 "   jne    nonzero\n"
					 "writeloop:\n"
					 "   pop    dx\n"
					 "   mov    ah,02h\n"
					 "   int    21h\n"
					 "   dec    cx\n"
					 "   jnz    writeloop\n"
					 "   ret\n");
}

void Assembly::read(string id){
	variables.insert("v"+id);
	is_read = 1;
	write.append("call myread\n"
				 "   mov v"+id+",cx\n");
}

void Assembly::call_myread(){
	write.append("myread:\n"
				 "   mov cx,0\n"
				 "morechar:\n"
				 "   mov ah,01h\n"
				 "   int 21h\n"
				 "   mov dx,0\n"
				 "   mov dl,al\n"
				 "   mov ax,cx\n"
				 "   cmp dl,0d\n"
				 "   je myret\n"
				 "   sub dx,48d\n"
				 "   mov bp,dx\n"
				 "   mov ax,cx\n"
				 "   mov cx,10d\n"
				 "   mul cx\n"
				 "   add ax,bp\n"
				 "   mov cx,ax\n"
				 "   jmp morechar\n"
				 "myret:\n"
				 "   ret\n");
}

void Assembly::add_variables(){
	 for(set<string>::iterator it=variables.begin(); it!=variables.end(); ++it){
		write.append(*it+"      dw ?\n");
	 }
}

void Assembly::ifFirst(int i){
	ss<<i;
	write.append("   pop ax\n"
				 "   if z jmp label"+ss.str()+"\n");
	ss.str(string());
}

void Assembly::ifSecond(int i){
	ss<<i;
	write.append("label"+ss.str()+":\n");
	ss.str(string());
}

void Assembly::whileFirst(int i){
	ss<<i;
	write.append("label"+ss.str()+":\n");
	ss.str(string());
}

void Assembly::whileSecond(int i){
	ss<<i;
	write.append("   pop ax\n"
				 "   cmp ax,0\n"
				 "   if z jmp label"+ss.str()+"\n");
	ss.str(string());
}

void Assembly::whileThird(int i){
	ss<<(i);
	write.append("   jmp label"+ss.str()+"\n");
	ss.str(string());
	ss<<(i+1);
	write.append("label"+ss.str()+":\n");
	ss.str(string());
}
