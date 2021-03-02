#include "Game.h"

#include <iostream>

int main()
{
	try
	{
		std::vector<unsigned int> layers{2, 8, 6, 1};
		NeuralNetwork nn(layers);
		
		Features features(30);
		
// 		nn.train(features.getInputs(), features.getOutputs(), 3000);
		
		Game game(features, nn);
		game.run();
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
	
    return 0;
}
