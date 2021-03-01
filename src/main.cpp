#include "Game.h"

#include <iostream>

int main()
{
	try
	{
		std::vector<unsigned int> layers{2, 5, 4, 1};
		NeuralNetwork nn(layers);
		
		std::vector<std::vector<float>> inputs{
			std::vector<float>{0.2, 0.4},
			std::vector<float>{0.1, 0.7},
			std::vector<float>{0.4, 0.1},
			std::vector<float>{0.9, 0.3},
			std::vector<float>{0.8, 0.6},
			std::vector<float>{1., 0.f},
			std::vector<float>{0.f, 1.f},
			std::vector<float>{0.6, 0.1},
			std::vector<float>{0.6, 0.2},
			std::vector<float>{0.2, 0.2},
			std::vector<float>{0.7, 0.5},
			std::vector<float>{0.3, 0.6},
			std::vector<float>{0.4, 0.4},
			std::vector<float>{0.5, 0.4},
			std::vector<float>{0.6, 0.9},
			std::vector<float>{0.5, 0.8},
			std::vector<float>{0.3, 0.9}
		};
		
		std::vector<std::vector<float>> outputs{
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f}
		};
		
// 		nn.train(inputs, outputs, 10000);
		
		std::vector<bool> labels;
		for(std::size_t i = 0; i < outputs.size(); ++i)
		{
			if(outputs[i][0] == 1.f)
				labels.push_back(true);
			else
				labels.push_back(false);
		}
		
		Features features(inputs, labels);
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
