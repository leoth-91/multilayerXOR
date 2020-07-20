
std::vector< std::vector<double> > load_dat_file(std::string path){
	std::vector< std::vector<double> > data;

	std::ifstream file(path);
	std::string line;

	while(std::getline(file, line)){
		std::vector<double> lineData;

		std::stringstream lineStream(line);
		double value;
		
		while(lineStream >> value){				// Read an integer at a time from the line
			lineData.push_back(value);			// Add the integers from a line to a 1D array (vector)
		}
		data.push_back(lineData);			// When all the integers have been read, the 1D array is added to the 2d array
	}
	return data;
}


