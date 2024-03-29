#pragma once
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

class Layer {
private:
	int layerSize;

public:
	MatrixXd layerMat, layerBiases, layerWeights;
	MatrixXd deltaLayer, deltaBiases, deltaWeights, layerMatNoSigmoid;

public:
	Layer(int layerSize, int previousLayerSize);

	void calculateLayer(Layer* previousLayer);

	inline int getLayerSize() { return layerSize; }
};

class NeuralNetwork {
public:
	std::vector<Layer*> layers;

public:
	NeuralNetwork(int hiddenLayers, int inputLayerSize, int hiddenLayerSize, int outputLayerSize);
	~NeuralNetwork();

	void setInputLayer(char* image, int imageSize);
	void propogateForward();

	void propogateBackwards(int answer);
	void calculateDeltaWeights(int layerIndex);
	void calculateDeltaLayer(int layerIndex, int answer);
	void calculateDeltaBiases(int layerIndex);

	void updateLayers(int batchSize, double stepSize);
	double calculateCost(int answer);
	bool isCorrect(int answer);
	int getAnswer();

	void writeWeightsAndBiasesToFile(std::string filename);
	void loadWeightsAndBiasesFromFile(std::string filepath);

	inline Layer* getInputLayer() { return layers[0]; }
	inline Layer* getOutputLayer() { return layers[layers.size() - 1]; }
};