#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

#include "header/data-loader.h"
#include "header/util.h"
#include "header/NeuralNetwork.h"

int main(){
	clock_t START_TIMER = clock();

	std::vector< std::vector<double> > train_data  = load_dat_file("data/train_data.dat");
	std::vector< std::vector<double> > train_label = load_dat_file("data/train_labels.dat");

	assert(train_data.size() == train_label.size());

	int N_samples = train_data.size();

	int N_in = train_data[0].size();
	int N_hid = N_in;
	int N_out = train_label[0].size();

	std::cout << "Training on " << N_samples << " Samples." << std::endl;

	Network model(N_in, N_hid, N_out);

	int N_epochs = 30;
	double threshold = 1E-4;
	
	std::vector<double> inputValues;
	std::vector<double> targetValues;
	std::vector<double> resultValues;
	std::vector<double> error;
	std::vector<double> error_avg_epoch;

	// TRAINING
	for(int epoch=0; epoch<N_epochs; epoch++){
		for(int i=0; i<N_samples; i++){
	        inputValues.clear();
	        targetValues.clear();
	        resultValues.clear();
	        error.clear();

			// Loading the sample into the container that is then passed to the network-methods
			for(int n=0; n< train_data[0].size(); n++)  inputValues.push_back( train_data[i][n]);
			for(int m=0; m<train_label[0].size(); m++) targetValues.push_back(train_label[i][m]);

	        std::cout << std::endl;
	        std::cout << "Epoch " << epoch+1 << "/" << N_epochs << ", Step " << i+1 << "/" << N_samples << ":" << std::endl;

			showVector("   Inputs:", inputValues);
			model.feedForward(inputValues);

	        model.getResults(resultValues);
	        showVector("  Outputs:", resultValues);

	        showVector("  Targets:", targetValues);

	        model.backPropagation(targetValues);

			std::cout << "  Net recent average error: " << model.getRecentAverageError() << std::endl;

	        error.push_back(model.getRecentAverageError());
		}		
        if (model.getRecentAverageError() < threshold){
        	std::cout << std::endl;
        	std::cout << "Recent Average Error beneath threshold (" << threshold << ").\n";
        	std::cout << "Training ended.\n";
        	break;
        }
		error_avg_epoch.push_back(average(error));
	}

  	std::ofstream file("error.txt");

 	file << "#n" << "		" << "error" << std::endl;
  	for(int i = 0; i < error_avg_epoch.size(); i++){
  		file << i+1 << "	" << error_avg_epoch[i] << std::endl;
  	}

	// TESTING
	std::vector< std::vector<double> > test_data  = load_dat_file("data/test_data.dat");
	std::vector< std::vector<double> > test_label = load_dat_file("data/test_labels.dat");
	assert(test_data.size() == test_label.size());

	int N_test_samples = test_data.size();

	std::vector<double> difference;

	for(int i=0; i<N_test_samples; i++){
        inputValues.clear();
        targetValues.clear();
        resultValues.clear();

		// Loading the sample into the container that is then passed to the network-methods
		for(int n=0; n< test_data[0].size(); n++)  inputValues.push_back( test_data[i][n]);
		for(int m=0; m<test_label[0].size(); m++) targetValues.push_back(test_label[i][m]);

		model.feedForward(inputValues);
        model.getResults(resultValues);
		difference.push_back(sqrt(pow(resultValues[0] - targetValues[0],2)));
	}		

	double avg_difference = average(difference);
	
	std::cout << std::endl;
	std::cout << "Testing:" << std::endl;
	std::cout << "Average RMS on test set: " << round(avg_difference, 4) << std::endl;

	std::cout << std::endl;
	std::cout << "FINISHED!";
	double time = (clock() - START_TIMER) / (double)CLOCKS_PER_SEC;
	if(time > 60) std::cout << " (Runtime: " << round(time/60) << " min)" << std::endl;
	else if(time < 1) std::cout << " (Runtime: " << round(time*1000) << " ms)" << std::endl;
	else std::cout << " (Runtime: " << round(time) << " s)" << std::endl;

	return 0;
}








