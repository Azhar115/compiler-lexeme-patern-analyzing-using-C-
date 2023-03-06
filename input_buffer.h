#include<iostream>
#include<fstream>
#include<string>
#define Max_buffer_size 4096  // macrose for input buffer max size
using namespace std;
//------------------global variables--------
char _1stBuffer[Max_buffer_size];
ifstream input; //reading input object
ofstream output; //writing in outputfile
bool readAllFlage = false;//to cheack that the file is read all
bool bufferReadAll=false;
string inputFileName ;  //path of input file
string outputFileName ;  //path of outputFIle
int start_lexeme_ptr =-1;   //start of the lexeme pointer
int forward_lexeme_ptr =-1;  //forwrad lexeme recognition pointer
	
//------------functions---------
void initialization_input_buffer(); //initialize input buffer at start
char getChar_buffer(); //return char at forward_ptr index
bool is_buffer_readAll(int buffer_current_index); // to cheack if buffer stored data is read all
bool is_inputFile_readAll(char valueAtCurrent_cursorInfile,int current_index);  //  to cheak all data is read from input file
void lexeme_is_matched_patern(int Token_symabal); //

//---------------test --------ok
/*  
	 puting values at the start of program in input buffer for compilation
*/
void initialization_input_buffer(){
   	
   	 // creating the file to write the output of the current file
   	output.open( "outputFile.txt",ios::out);
   	if(output){
   		
	   }
	else{
		output.close();
	}
	//default values to show that the buffer is empity  /0=end or empity of buffer
	_1stBuffer[0] ='/'; 
	_1stBuffer[1]='0';	
	
  //filling input buffer to 2048 bytes as program analyzing starts
	input.open( "input.txt",ios::in );   // taking input from user entered file	

	char readchar;
	int i=0;
    while(!readAllFlage && i<(Max_buffer_size/2-1)){
    	input.get(readchar);
	    if(is_inputFile_readAll(readchar,i)){
	      /*   -----test---ok
			int j= i++;
	    	cout<<_1stBuffer[j]<<","<<_1stBuffer[i];
	     */
	     	break;
		}
    	_1stBuffer[i] = readchar;
    	//cout<<_1stBuffer[i]; --test ---ok
    	i++;
	}
}


//---------------------test---ok
/*To cheak that the file is read all there is no input to read as it ends with /0 */
bool is_inputFile_readAll(char valueAtCurrent_cursorInfile,int current_index){
	char readchar = valueAtCurrent_cursorInfile;
	if(readchar=='/'){
	    input.get(readchar);
	    if(readchar=='0'){
	        readAllFlage=true;
	        _1stBuffer[current_index] ='/';
	        current_index++;
	        _1stBuffer[current_index] ='0'; //stored in last of the buffer to show end of file
	        input.close();
			return true;	 
		}
	}
	return false;//not read all		 
}
// ---------test ----ok
/* cheak if the current buffer ends with /0 means read all or the file has an error to be resolved*/
bool is_buffer_readAll(int buffer_current_index){
	switch(_1stBuffer[buffer_current_index]){
		case '/':
	    	// cout<<_1stBuffer[buffer_current_index]<<"cc";
		    buffer_current_index++;
		    if(_1stBuffer[buffer_current_index]=='0'){
		   //  cout<<_1stBuffer[buffer_current_index]<<"cc";
		   		bufferReadAll =true;
		    	return true; break;}
			else {
				  //  cout<<_1stBuffer[buffer_current_index]<<"cc2";
				  return false; break;
		    }
		default :{
			//cout<<_1stBuffer[buffer_current_index]<<"cc3  ";
			return false;
			break;
		}   
	}
}
/*
bool is_outputFile_writeFull(){
	if(output.fail()){
		output.exceptions();
		output.close();
		return true;
	}
	else if(output.eof()){
		output.exceptions();
		output.close();
		return true;
	}
	else{
		
		return false;
	}
}*/
/*
  * getchar_buffer() function returns character from index of iput buffer where forward_lexeme_ptr is pointing
  * if half of input buffer is read then the second half from 2048 to 4096 is filled with input characters and then forward_lexeme is return from that
  * if second half lexeme is full [2048 to 4096] then first half of input buffer is fulled if till lexe start ptr not came on index
  
*/ 
//--------test----ok
char getChar_buffer(){
     // ---test ---ok
	if(forward_lexeme_ptr==(Max_buffer_size/2-1)){
		char readchar;
		int i=Max_buffer_size/2;
		//filling buffer array [2048 to 4095 byte] if input taking index does not reach start lexeme ptr
    	while((!readAllFlage  && i<Max_buffer_size) && ((i!=start_lexeme_ptr))){  
    		input.get(readchar);
    		if(is_inputFile_readAll(readchar,i)){
	     		break;
			}
    		_1stBuffer[i] = readchar;
    		i = (i+1)%Max_buffer_size; //circular queue type
		}
	}
	 //----------test --ok
	else if(forward_lexeme_ptr==(Max_buffer_size-1)){
		char readchar;
		int i=0;
		//filling input buffer array [0 to 2047 bytes] if input taking index does not reach start lexeme ptr
    	while((!readAllFlage  && (i<Max_buffer_size/2-1)) && (i!=start_lexeme_ptr)){
    	    input.get(readchar);
    		if(is_inputFile_readAll(readchar,i)){
	     	    break;
			}
			_1stBuffer[i] = readchar;
    		i = (i+1)%(Max_buffer_size/2-1);
		}	
	}
	 //---------test  --ok
	// returnig char and movinf forward_lexeme buffer one index ahead till it does not matches with a patern
	if(start_lexeme_ptr==-1 && forward_lexeme_ptr ==-1){
		
		start_lexeme_ptr=0;
		forward_lexeme_ptr=0;
		if(!is_buffer_readAll(0))
		  return _1stBuffer[forward_lexeme_ptr];
	}
	//----test------ok
	else if(forward_lexeme_ptr+1!=start_lexeme_ptr){
		int temp_ptr = forward_lexeme_ptr;
		forward_lexeme_ptr++;
		if(!is_buffer_readAll(temp_ptr)){
		  return _1stBuffer[temp_ptr]; 
		}  
	}
	
}
 //---------------test----ok
void lexeme_is_matched_patern(int Token_symbal){
		
	bool flag =true;
	int i=start_lexeme_ptr;
	// stroring lexeme in output file that is matched with a patern
			output<<"<"<<Token_symbal<<",";  
		while( i<forward_lexeme_ptr){
			if(is_buffer_readAll(i)){
				flag =false;
				break;
			}
			cout<<_1stBuffer[i];	
			output<<_1stBuffer[i];  //optional token value
			i++;
		}
		if(flag){
			output<<">";
			cout<<"first_token is read"<<endl;
			start_lexeme_ptr = forward_lexeme_ptr; //lexeme checking is jumped to new stream in buffer
			cout<<start_lexeme_ptr<<","<<forward_lexeme_ptr<<endl;
	    }
    
    

}
/*
 // -----------test passed----ok
int main(){
	initialization_input_buffer(); //ok
   for(int i=0;i<9;i++){
   	  
   	getChar_buffer();
   	
   }
   lexeme_is_matched_patern(1);
   
   for(int i=0;i<9;i++){
   	  getChar_buffer();
   }
   lexeme_is_matched_patern(2);
   for(int i=0;i<9;i++){
   	  getChar_buffer();
   }
    lexeme_is_matched_patern(3);
    for(int i=0;i<9;i++){
   	  getChar_buffer();
   }  
   lexeme_is_matched_patern(4);
   for(int i=0;i<6;i++){
   	  getChar_buffer();
   }  
     
   lexeme_is_matched_patern(6);
}
*/
