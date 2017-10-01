// including
#include <ReadPGM.h>
#include <iostream>
#include <fstream>

// using
using namespace std;
using std::cout;
using std::cerr;
using std::ifstream;

int main(int argc, char* argv[])
{
	// check number of args
	if (argc != 2){
		cerr << "ERROR: Not enough arguments" << endl;
		return -1;
	}

	// check file opening  
	ifstream istr(argv[1]);
	if (istr.fail()){
		cerr << "ERROR: File could not be opened." << endl;
		return -1;
	}

	// send file to ReadPGM
	ReadPGM read;
	int test = read.readFile(argv[1]);

	// check for error
	if(test < 0){
		return -1;
	}

	return 0;

}
