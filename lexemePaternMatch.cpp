#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include"input_buffer.h"
#include"keywords_enum.h"
using namespace std;
int main(){
     
    //identifer analysis
    initialization_input_buffer();
    char readchar;
	int identifier_max_length = 31;  // identifier maximum length that is allowed is 31 byte
	char identifier[identifier_max_length]; // declaration of an identider array
    while(!bufferReadAll){  // if buffer file is not ended 
	    readchar =getChar_buffer();// read a single character and store in a varaible char
	 	 //-------------------checking for identifiers
	   if(isalpha(readchar)){
	   	  int i=0; 
	   	  int count_cummas =0;
	   	  //([a-zA-z][0-9])* // Identifier identification 
	   	  // ([A-z-A-z][0-9])*((([A-z-A-z][0-9])*,([A-z-A-z][0-9])*,) // function defination
	 	 	while((isalpha(readchar)|| isdigit(readchar)) || readchar =='_'){
	 	 	   if(i<identifier_max_length){
	 	 	   	   identifier[i++]=readchar;  
			    }/*
			    //([arg1]*,[arg2]*) functions identification
			    if(readchar=='('){
			    	//functions starts
			    	//readchar = getChar_buffer();
			    		if(readchar==','){
				          count_cummmas++; 
					//one argument is read 
				}
				
				}*/
			
				
				readchar =getChar_buffer(); // to read one character ahead    
			} 
		//--------------------- some keyword analaysis----------
		 //if identifier matches with keyword print it is keyword  
			if (strcmp(identifier,"else")==0) lexeme_is_matched_patern(30);
			else if (strcmp(identifier,"if")==0) lexeme_is_matched_patern(29);
			else if (strcmp(identifier,"int")==0) lexeme_is_matched_patern(41);
			else if (strcmp(identifier,"for")==0) lexeme_is_matched_patern(32);
			else if (strcmp(identifier,"switch")==0)lexeme_is_matched_patern(35);
			else if (strcmp(identifier,"return")==0)lexeme_is_matched_patern(45);
			else if (strcmp(identifier,"while")==0) lexeme_is_matched_patern(33);
			else lexeme_is_matched_patern(1); // identifier =1	
		}
		
       //----------------------checking Logical and Assignment operators
    	switch(readchar){
    	    case '<':
            	readchar =getChar_buffer(); // read next char
    	      	   if(readchar=='='){
    	      		 	lexeme_is_matched_patern(7);
    	      		 	break;
				    }
					  else{
					  	lexeme_is_matched_patern(6);
					  	break;
					}
					
		   case '>':
    	    	readchar =getChar_buffer();
			       if(readchar=='='){
			    	 	lexeme_is_matched_patern(8);
			    	 	break;
					}
					 else{
					  	lexeme_is_matched_patern(9);
					  	break;
				   }
				
			case '!':
				readchar =getChar_buffer();
					if(readchar=='='){
					    lexeme_is_matched_patern(12);
						break;
					}
					else{
					  	lexeme_is_matched_patern(11);
					  	break;
					}
				
			case '=':
				readchar =getChar_buffer();
					if(readchar=='='){
						lexeme_is_matched_patern(10);
						break;
					}
					else{
					  	lexeme_is_matched_patern(13);
					  	break;
					  	
					}
			case '&':
			    readchar =getChar_buffer();
					if(readchar=='&'){
						lexeme_is_matched_patern(60);
						break;
					}
					else{
					  	lexeme_is_matched_patern(21);
					  	break;
					  	
					}
			case '|':
			   readchar =getChar_buffer();
					if(readchar=='|'){
						lexeme_is_matched_patern(61);
						break;
					}
					else{
					  	lexeme_is_matched_patern(26);
					  	break;
					  	
					}
			case '*':
			    readchar =getChar_buffer();
					if(readchar=='='){
						lexeme_is_matched_patern(17);
						break;
					}
					else if(readchar=='/'){
						lexeme_is_matched_patern(69);
						break;
					}
					else{
					    lexeme_is_matched_patern(24);
					    break;
					  	
				   }
			case '/':
			    readchar =getChar_buffer();
					if(readchar=='='){
						lexeme_is_matched_patern(16);
						break;
					}
					//------comment lexemes
					else if(readchar=='*'){
						lexeme_is_matched_patern(68);
						break;
					}
					else{
					  	lexeme_is_matched_patern(23);
					  	break;
					  	
					}
			case '-':
	     	   readchar =getChar_buffer();
	     		   if(!isdigit(readchar)){  // if we do not get a digit after - sign
	     		       if(readchar=='='){
	     		    	 lexeme_is_matched_patern(15);
						}
						else{
						 	lexeme_is_matched_patern(22);
						}
	     		    	break;
					}			
			case '+':
				readchar =getChar_buffer();
	     		   if(!isdigit(readchar)){  // if we do not get a digit after - sign
	     		       if(readchar=='='){
	     		    	  lexeme_is_matched_patern(14);
						}
						else{
						 	lexeme_is_matched_patern(21);
						}
						
	     		    	break;
					}
			case '(':
				readchar =getChar_buffer();
				lexeme_is_matched_patern(62);
				
				break;
			case ')':
				
				readchar =getChar_buffer();
				lexeme_is_matched_patern(63);
				break;
			case '{':
				readchar =getChar_buffer();
				lexeme_is_matched_patern(66);
				break;
			case '}':
				readchar =getChar_buffer();
				lexeme_is_matched_patern(67);
				break;
			case '[':
				readchar =getChar_buffer();
				lexeme_is_matched_patern(64);
				break;
			case ']':
				readchar =getChar_buffer();
				lexeme_is_matched_patern(65);
		
			default:
				  break;			
		}
		//whitespaces
		switch(readchar){
			//[space][space]*
			case ' ':
				
				readchar = getChar_buffer();
				int i=0;
				while(reachar ==' '){
					white_spaces_length[i] = readchar;
					i++;
					readchar = getChar_buffer();
				}
				if(i==0){
					lexeme_is_matched_ptern(1);
				}
				else{
					lexeme_is_matched_patern(66); //multiple white spaces
				}
			//[\t\n][\t \n]* 
			case '\':
				readchar = getChar_buffer();
					int j=0;
				if(readchar == 't' || readchar=='n'){
					j=1;
					readchar = getChar_buffer();
					//[\t]*  reading multiple while tabe spaces
					bool flag = true;
					while(flag){
						switch(readchar){
							case '\':
							 	readchar = getChar_buffer;
								if(readchar =='t' || readchar=='n'){
									readchar = getChar_buffer;
								}
								break;
							default :
								flag = false;
								break;
					   }
					   j++;
					}
				}
				if(j==0){
					lexeme_is_matched_ptern(1);
				}
				else{
					lexeme_is_matched_patern(66); //multiple white spaces
				}			
		}
	    // -------------------NUmbers identification
	    
	    //[0-9]+([.[0-9]+])?(E[+-][0-9]+)?)                          // ? means a+|E 
	    if(isdigit(readchar)  && (int(readchar)>=0 ||int(readchar)<=9)){
	    	
	    	 // first digit part
			//[0-9]    
			readchar =getChar_buffer(); //first digit is read
	    	string number_stored;     // suppose number is 2 it is stored as 20
	    	number_stored +=readchar; //cancatenation ,adding new char into a string
	    	
	    	 // (optional fraction part)(optional Exponenetional part)
	    	//([.[0-9]+]?)(E[+-]?[0-9]+)?
	    	readchar =getChar_buffer(); 
			switch(readchar){
				case '.':
					// ([.[0-9][0-9]*])?    optional fractional part of number
					readchar =getChar_buffer(); 
					//[0-9]
					if(isdigit(readchar)){
						number_stored = readchar;
					}
					else{
						// after . dot [0-9] should be there once ,error
					}
					readchar =getChar_buffer(); 
			    break;
				case 'E':
					//(E[+-]?[0-9][0-9]*)?  optional Exponentioal  part of number
					number_stored = readchar; //stored the . dot in string number
					readchar =getChar_buffer(); //read the number from buffer
					//[+-]?	
				    if(readchar =='-' || readchar=='+'){
					   number_stored = readchar; //store the number
					}
					//[0-9]
					else if(isdigit(readchar)){
						number_stored = readchar; //store the number
					}
					else{
						//error as no [0-9] after read E 
						
					}
				
					readchar =getChar_buffer(); //file.get(readchar);
				break;	
			}
			// [0-9]*			
					
	    	while(isdigit(readchar)){
	    	/*	double num;
	    		stringstream convertor;
	    		 //converting string into double
	    		convertor<<number_stored;  //string
	    		convertor>>num;        //int 
				//converting number in result string   
	    		convertor<<10*num+int(readchar); // result 
	    		convertor>>number_stored;  //changed into string
	    	*/	
	    	    number_stored +=readchar;
				readchar =getChar_buffer(); //read the number from buffer			
		   }
		}
    }
	cout<<"input is done";	
}

