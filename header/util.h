
void showVector(std::string label, std::vector<double> &vector){
	std::cout << label << " ";
	for (int i = 0; i < vector.size(); i++){
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

void printArray(std::vector< std::vector<double> > array){
	for(int i=0; i<array.size(); i++){
		for(int j=0; j<array[0].size(); j++){
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}	
}

double average(std::vector<double> vector){
	double avg = 0.0;
	for(int i=0; i<vector.size(); i++){
		avg += vector[i]/vector.size();
	}
	return avg;
}


double round(double var, int num){
	int number = pow(10,num);
	return (double)((int)(var * number + .5))/number;
}