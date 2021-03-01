#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"

class NeuralNetwork
{
public :
	
	NeuralNetwork(std::vector<unsigned int>);
	
	Matrix feedForward(const Matrix&) const;
	float backPropagation(const Matrix&);
	
	void train(const std::vector<std::vector<float>>&, const std::vector<std::vector<float>>&, unsigned int n);
	float predict(float x, float y) const;
	
private :
	
	std::vector<Layer*> m_layers;
	std::vector<Matrix*> m_weights;
};

#endif // NEURALNETWORK_H
