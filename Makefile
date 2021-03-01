CC = g++
EXEC = NeuralNetwork
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/main.o: $(O)/Game.o
	$(CC) $(S)/main.cpp -c -o $(O)/main.o $(STD) $(FLAGS)

$(O)/Game.o: $(O)/Features.o $(O)/Field.o 
	$(CC) $(S)/Game.cpp -c -o $(O)/Game.o $(STD) $(FLAGS)

$(O)/Field.o: $(O)/NeuralNetwork.o 
	$(CC) $(S)/Field.cpp -c -o $(O)/Field.o $(STD) $(FLAGS)

$(O)/NeuralNetwork.o: $(O)/Layer.o
	$(CC) $(S)/NeuralNetwork.cpp -c -o $(O)/NeuralNetwork.o $(STD) $(FLAGS)

$(O)/Layer.o: $(O)/Neuron.o $(O)/Matrix.o
	$(CC) $(S)/Layer.cpp -c -o $(O)/Layer.o $(STD) $(FLAGS)

$(O)/Neuron.o:
	$(CC) $(S)/Neuron.cpp -c -o $(O)/Neuron.o $(STD) $(FLAGS)

$(O)/Matrix.o:
	$(CC) $(S)/Matrix.cpp -c -o $(O)/Matrix.o $(STD) $(FLAGS)

$(O)/Features.o:
	$(CC) $(S)/Features.cpp -c -o $(O)/Features.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
