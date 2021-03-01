#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include "Matrix.h"

#include <chrono>
#include <vector>
#include <random>

class Layer
{
public :
	
	Layer(std::size_t size);
	
	std::size_t size() const;
	
	Matrix getBiaisMatrix() const;
	Matrix getValueMatrix() const;
	
	void operator-=(const Matrix&);
	
	void setNeuronValue(std::size_t, float);
	void setNeuronBiais(std::size_t, float);
	
private :
	
	std::size_t m_size;
	std::vector<Neuron> m_neurons;
};

#endif // LAYER_H
