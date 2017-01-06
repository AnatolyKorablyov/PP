#pragma once
#include <random>
#include <sstream>

float RandomRangeFloat(float a, float b) 
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(b));
	return dist(gen);

	//float random = ((float)std::rand()) / (float)RAND_MAX;
	//std::cout << "rand " << random * 1000 / 1000 << " x " << dist(gen) * 1000 / 1000 << std::endl;
	
	//float diff = b - a;
	//float r = random * diff;
	//return a + r;
}

template <typename T>
std::string NumberToString(T number)
{
	std::ostringstream os;
	os << number;
	return os.str();

}