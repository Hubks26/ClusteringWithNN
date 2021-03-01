#include "Layer.h"

Layer::Layer(std::size_t size)
: m_size(size)
, m_neurons(m_size, Neuron(0.f, 0.f))
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<float> distN_R(0.f, 1.f);
	float biais_value;
	
	for(std::size_t i = 0; i < m_size; ++i)
	{
		biais_value = distN_R(generator);
		m_neurons[i].setBiais(biais_value);
	}
}

std::size_t Layer::size() const
{
	return(m_size);
}

Matrix Layer::getBiaisMatrix() const
{
	Matrix res(m_size, 1);
	
	for(std::size_t i = 0; i < m_size; ++i)
	{
		res.setCoeff(i, 0, m_neurons[i].getBiais());
	}
	
	return(res);
}

Matrix Layer::getValueMatrix() const
{
	Matrix res(m_size, 1);
	
	for(std::size_t i = 0; i < m_size; ++i)
	{
		res.setCoeff(i, 0, m_neurons[i].getValue());
	}
	
	return(res);
}

void Layer::operator-=(const Matrix& B)
{
	for(std::size_t i = 0; i < B.row(); ++i)
	{
		m_neurons[i].setBiais(m_neurons[i].getBiais() - B.getCoeff(i, 0));
	}
}

void Layer::setNeuronValue(std::size_t i, float value)
{
	m_neurons[i].setValue(value);
}

void Layer::setNeuronBiais(std::size_t i, float biais)
{
	m_neurons[i].setBiais(biais);
}
