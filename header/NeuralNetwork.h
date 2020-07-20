/*
	To make the code more readable, most of the functions are actually defined further down, outside of the class declaration
*/

/******************************************/
/************** CLASS_NEURON **************/
class Neuron{
public:
	Neuron(int numOutputs, int myIndex); 	// Neuron needs to know ho many ouputs it has!
	void setOutputVal(double val){outputVal = val;}
	double getOutputVal(void) const {return outputVal;}
	void feedForward(const std::vector<Neuron> &prevLayer);

	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const std::vector<Neuron> &outputLayer);
	void updateInputWeight(std::vector<Neuron> &prevLayer);
	static double eta;	// [0,...,1]

private:
	static double alpha; // [0,....]
	static double activationFunction(double x);
	static double activationFunctionDerivative(double x);
	double outputVal; 
	std::vector<double> outputWeights;
	std::vector<double> deltaOutputWeights;	
	int m_myIndex;
	double gradient;
};

/******************************************/
/************** CLASS_NET *****************/
class Network{
public:
	Network(const int N_in, const int N_hid, const int N_out);
	void feedForward(const std::vector<double> &inputValues);
	void backPropagation(const std::vector<double> &targetValues);
	void getResults(std::vector<double> &resultValues) const ;	// Just reads the outputVals of the output Layer and puts them into a container after emptying it
																// ResultValues is modified here
	double getRecentAverageError(void) const { return recentAverageError;}
	double getRecentError(void) const { return error;}
private:
	std::vector<Neuron> inputLayer; 	// Access elements: inputLayer[neuronNum]	
	std::vector<Neuron> hiddenLayer;
	std::vector<Neuron> outputLayer;
	double error;
    double recentAverageError;
    static double recentAverageSmoothingFactor;
};



/*
	Definitions of the declared functions
*/

double Neuron::eta   = 0.08;
double Neuron::alpha = 0.1;	

Neuron::Neuron(int numOutputs, int myIndex){
	for(int c=0; c<numOutputs; c++){			// All connections
		outputWeights.push_back(drand48());		// Gives Neuron outputweights between 0 and 1
		deltaOutputWeights.push_back(0);		// Some initialization
	}
	m_myIndex = myIndex;
}

void Neuron::feedForward(const std::vector<Neuron> &prevLayer){
	double sum = 0.0;
	// Sum the previous layers outputs (which are now inputs for this layer) 
	// including the bias neuron

	for(int n=0; n<prevLayer.size(); n++){			// All neurons including bias 
		sum += prevLayer[n].outputVal * prevLayer[n].outputWeights[m_myIndex];
		// Alternatively reach outputVal through its public API:
		// sum += prevLayer[n].getOutputVal()*.....;
		// m_myIndex is the neurons own index
	}
	outputVal = Neuron::activationFunction(sum);
	// Neuron:: because it's a static member function
}

double Neuron::activationFunction(double x){
	return tanh(x);
	// return 1/(1+exp(-x)); // Sigmoid
	// ReLU
	// if(x < 0) return 0;
	// // if(x < 0) return 0.1;
	// else return x;
}

double Neuron::activationFunctionDerivative(double x){
	return 1-pow(tanh(x),2);	// precise 
	// return exp(-x)*pow(1+exp(-x),-2);	// sigmoid 
	// ReLU
	// if(x < 0) return 0;
	// else return 1;
}

void Neuron::calcOutputGradients(double targetVal){
	double delta = targetVal - outputVal;
	gradient = delta * Neuron::activationFunctionDerivative(outputVal);
}

void Neuron::calcHiddenGradients(const std::vector<Neuron> &outputLayer){
	// Here we do not compare to a target value
	// but to the sum of the derivatives of the weights of the next (output) layer
	double sum = 0.0;
	for(int n=0; n<outputLayer.size() - 1; n++){	// All neurons except bias
		sum += outputWeights[n] * outputLayer[n].gradient;
	}
	gradient = sum * Neuron::activationFunctionDerivative(outputVal);;
}

void Neuron::updateInputWeight(std::vector<Neuron> &prevLayer){
/*
	Seg fault came from the fact that I didn't initialize the deltaOutputweight;
	Now that is taken care of in the Neuron constructor
*/
	for(int n=0; n<prevLayer.size(); n++){		// All neurons including bias 
		
		Neuron &neuron = prevLayer[n];	
		// that's a handle for the other neuron that feeds into the neuron whose inputValues we update when calling the function

		double oldDeltaWeight = neuron.deltaOutputWeights[m_myIndex];
		
		double newDeltaWeight = eta * neuron.getOutputVal() * gradient
				// Momentum
				+ alpha * oldDeltaWeight;
		neuron.deltaOutputWeights[m_myIndex] = newDeltaWeight;
		neuron.outputWeights[m_myIndex] += newDeltaWeight;
	}
}


Network::Network(const int N_in, const int N_hid, const int N_out){
	// Create input layer:
	for(int neuronNum = 0; neuronNum<=N_in; neuronNum++){	// <= because we create a bias
		// Create a new neuron
		inputLayer.push_back(Neuron(N_hid, neuronNum));
		// Neuron gets passed its own Index number
		// std::cout << "Created a neuron\n";
	} 
	// Sets bias neuron (the last one created to zero)
	// nothing in the program changes the bias later on
	inputLayer.back().setOutputVal(1.0);
	// std::cout << std::endl;

	// Create hidden layer:
	for(int neuronNum = 0; neuronNum<=N_hid; neuronNum++){
		// Create a new neuron
		hiddenLayer.push_back(Neuron(N_out, neuronNum));	
		// std::cout << "Created a neuron\n";
	}
	hiddenLayer.back().setOutputVal(1.0); 
	// std::cout << std::endl;

	// Create output layer:
	for(int neuronNum = 0; neuronNum<=N_out; neuronNum++){
		// Create a new neuron
		outputLayer.push_back(Neuron(0, neuronNum));	// output neurons don't have outputs themselves
		// std::cout << "Created a neuron\n";
	} 
	outputLayer.back().setOutputVal(1.0);
	std::cout << std::endl;
	std::cout << "Created a perceptron with:\n" 
			  << std::setw(5
			  	) << N_in  << "  Input neurons\n" 
			  << std::setw(5
			  	) << N_out << "  Output neurons\n" 
			  << std::setw(5
			  	) << N_hid << "  Hidden neurons\n";
	std::cout << std::endl;
}

void Network::feedForward(const std::vector<double> &inputValues){
	// safety first ("-1" accounts for our extra bias neuron)
	assert(inputValues.size() == inputLayer.size() - 1);
	// latch inputValues into the input neurons
	for(int i=0; i< inputValues.size(); i++){	// all input 
		// inputLayer[i].outputVal = ... 
		// not possible because we are in class net and not class Neuron
		// Hence:
		inputLayer[i].setOutputVal(inputValues[i]);
	}
	
	// forward propagate into hidden layer:
	for(int n=0; n<hiddenLayer.size() - 1; n++){	// all neurons -1 bias
		hiddenLayer[n].feedForward(inputLayer);
		// Here feedForward is member of Neuron, this is responsible for the math part
	}
	// forward propagate into output layer:
	for(int n=0; n<outputLayer.size() - 1; n++){	// all neurons -1 bias
		outputLayer[n].feedForward(hiddenLayer);
	}
}

double Network::recentAverageSmoothingFactor = 50.0; // Number of training samples to average over

void Network::backPropagation(const std::vector<double> &targetValues){
	// Calculate Error function (here: RMS)
	// Err = \sum_{i=1}^N (target_i-output_i)^2
	error = 0.0;
	for(int n=0; n<outputLayer.size() - 1; n++){	// all output neurons excluding bias
		double delta = targetValues[n] - outputLayer[n].getOutputVal();
		// Here we do need to use the API because class Net soes not know class Neurons private members
		error += delta*delta;
	}
	// recent average measurement: RAE_(n+1) = (RAE_n*smoothing + error)/(smoothing + 1)
    recentAverageError = (recentAverageError * recentAverageSmoothingFactor + error) / (recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradient
	for(int n=0; n<outputLayer.size() - 1; n++){	// All neurons except bias
		outputLayer[n].calcOutputGradients(targetValues[n]);
	}
	// Calculate output hidden gradient
	for(int n=0; n<hiddenLayer.size() - 1; n++){	// All neurons except bias
		hiddenLayer[n].calcHiddenGradients(outputLayer);
	}
	// Update connection weights for output layer
	for(int n=0; n<outputLayer.size() - 1; n++){	// All neurons except bias
		outputLayer[n].updateInputWeight(hiddenLayer);
	}
	// Update connection weights for hidden layer
	for(int n=0; n<hiddenLayer.size() - 1; n++){	// All neurons except bias
		hiddenLayer[n].updateInputWeight(inputLayer);
	}
}

void Network::getResults(std::vector<double> &resultValues) const{
	resultValues.clear();
	for(int n=0; n<outputLayer.size() - 1; n++){	// All neurons in outputlayer
		resultValues.push_back(outputLayer[n].getOutputVal());
	}
}



