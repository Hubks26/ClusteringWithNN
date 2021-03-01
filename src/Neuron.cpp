#include "Neuron.h"

Neuron::Neuron(float value, float biais)
: m_value(value)
, m_biais(biais)
{
}

float Neuron::getValue() const
{
	return(m_value);
}

float Neuron::getBiais() const
{
	return(m_biais);
}

void Neuron::setValue(float value)
{
	m_value = value;
}

void Neuron::setBiais(float biais)
{
	m_biais = biais;
}
