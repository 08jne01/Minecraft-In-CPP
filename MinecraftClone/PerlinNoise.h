#pragma once
#include <vector>
#include <random>
#define PI 3.14159

class PerlinNoise

{
public:

	PerlinNoise(int xSize, int ySize, int seed, int noise, double scale);
	double perlin(double x, double y, double period);
	double fractalNoise(double x, double y, int layers, double period);
	double random();

private:
	int xS, yS;
	double s;
	std::vector<std::vector<std::vector<double>>> grad;
	double lerp(double p1, double p2, float w);
	double dotGridGradient(int intX, int intY, double x, double y);
	double lerpCos(double d1, double d2, double w);
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
};