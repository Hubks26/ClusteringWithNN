#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> L)
{
	
	// ARCHITECHTURE DU RESEAU
	
	std::vector<Layer*> layers;
	
	for(std::size_t i = 0; i < L.size(); ++i)
	{
		layers.push_back(new Layer(L[i]));
	}
	
	m_layers = layers;
	
	// ATTRIBUTION ALEATOIRE DES POIDS
	
	std::vector<Matrix*> weights;
	
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<float> distN_R(0.f, 1.f);
	float weight_value;
	
	for(std::size_t k = 0; k < m_layers.size()-1; ++k)
	{
		Matrix* mat = new Matrix(m_layers[k+1]->size(), m_layers[k]->size());
		
		for(std::size_t i = 0; i < mat->row(); ++i)
		{
			for(std::size_t j = 0; j < mat->col(); ++j)
			{
				weight_value = distN_R(generator);
				mat->setCoeff(i, j, weight_value);
			}
		}
		
		weights.push_back(mat);
	}
	
	m_weights = weights;
	
	//########################  ---> à déplacer dans .train()
	
// 	Matrix input(1,1);
// 	Matrix output(1,1);
// 	
// 	for(int i = 0; i < 10000; ++i)
// 	{
// 		float cost = 0.f;
// 		
// 		input.setCoeff(0, 0, 0.f);
// 		output.setCoeff(0, 0, 0.9);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		input.setCoeff(0, 0, 0.2);
// 		output.setCoeff(0, 0, 0.1);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		input.setCoeff(0, 0, 0.4);
// 		output.setCoeff(0, 0, 0.9);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		input.setCoeff(0, 0, 0.6);
// 		output.setCoeff(0, 0, 0.1);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		input.setCoeff(0, 0, 0.8);
// 		output.setCoeff(0, 0, 0.9);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		input.setCoeff(0, 0, 1.f);
// 		output.setCoeff(0, 0, 0.1);
// 		
// 		feedForward(input);
// 		cost += backPropagation(output);
// 		
// 		std::cout << "COST = " << cost/6.f << std::endl;
// 	}
}

Matrix NeuralNetwork::feedForward(const Matrix& input) const
{
	std::size_t n1 = m_layers[0]->size();
	
	if (input.row() != n1 || input.col() != 1)
		throw std::runtime_error ("NeuralNetwork::feedForward - wrong dimensions for the input");
	
	for(std::size_t i = 0; i < n1; ++i)
	{
		m_layers[0]->setNeuronValue(i, input.getCoeff(i, 0));
	}
	
	Matrix output = (*m_weights[0])*(input) + m_layers[1]->getBiaisMatrix(); // Le premier layer correspond 
																			 //à l'input et n'a donc pas de biais
	output.applySigmo();
	
	for(std::size_t i = 0; i < m_layers[1]->size(); ++i)
	{
		m_layers[1]->setNeuronValue(i, output.getCoeff(i, 0));
	}
	
	for(std::size_t i = 1; i < m_weights.size(); ++i)
	{
		output = (*m_weights[i])*output + m_layers[i+1]->getBiaisMatrix();
		output.applySigmo();
		
		for(std::size_t j = 0; j < m_layers[i+1]->size(); ++j)
		{
			m_layers[i+1]->setNeuronValue(j, output.getCoeff(j, 0));
		}
	}
	
	return(output);
}

float NeuralNetwork::backPropagation(const Matrix& outputExpected)
{	
	std::size_t size_layers = m_layers.size();
	std::size_t size_weights = m_weights.size();
	
	std::size_t size_output = m_layers[size_layers - 1]->size();
	
	if (size_output != outputExpected.row() || outputExpected.col() != 1)
		throw std::runtime_error ("NeuralNetwork::backPropagation - wrong dimensions");
	
	// Calcul des DW, DB et DA
	//Initialisation : 
	
// 	std::vector<Matrix*> DB_vect;
// 	std::vector<Matrix*> DW_vect;
	
	Matrix z = (*m_weights[size_weights - 1])*m_layers[size_layers - 2]->getValueMatrix() + m_layers[size_layers - 1]->getBiaisMatrix();
	z.applySigmoPrime();
	z.constMult(2.f);
	Matrix Z = z.diag();
	Matrix output = m_layers[size_layers - 1]->getValueMatrix();
	Matrix Y = outputExpected;
	Y.constMult(-1.f);
	Matrix DB = Z * (output + Y);
	
	Matrix A = m_layers[size_layers - 2]->getValueMatrix();
	Matrix DW = DB * A.transposee();
	
	Matrix DA = (*m_weights[size_weights - 1]).transposee() * DB;
	
	std::vector<Matrix*> DB_vect(1, new Matrix(DB));
	std::vector<Matrix*> DW_vect(1, new Matrix(DW));
	for (std::size_t i = 2; i < size_weights; ++i)
	{
		z = (*m_weights[size_weights-i])*m_layers[size_layers-i-1]->getValueMatrix()+m_layers[size_layers-i]->getBiaisMatrix();
		z.applySigmoPrime();
		Z = z.diag();
		DB = Z * DA;
		
		A = m_layers[size_layers - i - 1]->getValueMatrix();
		DW = DB * A.transposee();
		
		DA = (*m_weights[size_weights - i]).transposee() * DB;
		
		DB_vect.push_back(new Matrix(DB));
		DW_vect.push_back(new Matrix(DW));
	}
	
	z = (*m_weights[0])*m_layers[0]->getValueMatrix()+m_layers[1]->getBiaisMatrix();
	z.applySigmoPrime();
	Z = z.diag();
	DB = Z * DA;

	A = m_layers[0]->getValueMatrix();
	DW = DB * A.transposee();
	
	DB_vect.push_back(new Matrix(DB));
	DW_vect.push_back(new Matrix(DW));
	
	for (std::size_t i = 0; i < size_weights; ++i)
	{
		(*m_layers[i+1]) -= (*DB_vect[size_weights-i-1]);
		(*m_weights[i]) -= (*DW_vect[size_weights-i-1]);
	}
	
	float cost = 0.f;
	
	for(std::size_t i = 0; i < output.row(); ++i)
	{
		cost += (output.getCoeff(i, 0) - outputExpected.getCoeff(i, 0)) * (output.getCoeff(i, 0) - outputExpected.getCoeff(i, 0));
	}
	
	return(cost);
}

void NeuralNetwork::train(const std::vector<std::vector<float>>& inputs, const std::vector<std::vector<float>>& outputs, unsigned int n)
{
	std::size_t size = inputs.size();
	Matrix input(0,0);
	Matrix output(0,0);
	float cost;
	
	for(std::size_t k = 0; k < n; ++k)
	{
		cost = 0.f;
		for(std::size_t i = 0; i < size; ++i)
		{
			input = Matrix(inputs[i], false);
			output = Matrix(outputs[i], false);
			
			feedForward(input);
			cost += backPropagation(output);
		}
		std::cout << "COST = " << cost/size << std::endl;
	}
}

float NeuralNetwork::predict(float x, float y) const
{
	float value = feedForward(Matrix(std::vector<float>{x, y}, false)).getCoeff(0,0);
	return(value);
}
