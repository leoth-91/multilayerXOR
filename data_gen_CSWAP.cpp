#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <ctime>
#include <cassert>
#include <iomanip>

int main(){
	std::string train_data   = "data/train_data.dat";
	std::string train_labels = "data/train_labels.dat";
	std::string test_data    = "data/test_data.dat";
	std::string test_labels  = "data/test_labels.dat";	

	int N_train = 250;
	int N_test = 100;

	srand(time(NULL));

	int spaces = 3;
	std::ofstream file_train_dat(train_data);
	std::ofstream file_train_lab(train_labels);

	for(int i=0; i<N_train; i++){
		int c = rand()%2;
		int x = rand()%2;
		int y = rand()%2;
		if (c == 0){
			file_train_dat << std::setw(spaces) << std::left << c 
					       << std::setw(spaces) << std::left << x
						   << std::setw(spaces) << std::left << y
						   << std::endl;
			file_train_lab << std::setw(spaces) << std::left << c
					       << std::setw(spaces) << std::left << x
						   << std::setw(spaces) << std::left << y
						   << std::endl;
		}else if (c == 1){
			file_train_dat << std::setw(spaces) << std::left << c 
					       << std::setw(spaces) << std::left << x
						   << std::setw(spaces) << std::left << y
						   << std::endl;
			file_train_lab << std::setw(spaces) << std::left << c
					       << std::setw(spaces) << std::left << y
						   << std::setw(spaces) << std::left << x
						   << std::endl;		
		}
	}

	std::ofstream file_test_dat(test_data);
	std::ofstream file_test_lab(test_labels);

	for(int i=0; i<N_test; i++){
		int c = rand()%2;
		int x = rand()%2;
		int y = rand()%2;
		if (c == 0){
			file_test_dat << std::setw(spaces) << std::left << c 
						  << std::setw(spaces) << std::left << x
						  << std::setw(spaces) << std::left << y
						  << std::endl;
			file_test_lab << std::setw(spaces) << std::left << c
						  << std::setw(spaces) << std::left << x
						  << std::setw(spaces) << std::left << y
						  << std::endl;
		}else if (c == 1){
			file_test_dat << std::setw(spaces) << std::left << c 
						  << std::setw(spaces) << std::left << x
						  << std::setw(spaces) << std::left << y
						  << std::endl;
			file_test_lab << std::setw(spaces) << std::left << c
						  << std::setw(spaces) << std::left << y
						  << std::setw(spaces) << std::left << x
						  << std::endl;		
		}
	}
	std::cout << "FINISHED!";
	std::cout << std::endl;

	return 0;
}







