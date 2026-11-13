// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include <random>
#include <sstream>
#include <iomanip>

class FPWHexCodeGenerator
{
public:
	FPWHexCodeGenerator()
		: counter(0)
	{
		std::random_device rd;
		rng = std::mt19937(rd());
		dist = std::uniform_int_distribution<>(0, 255);
	}

	std::string Generate()
	{
		std::stringstream ss;
		ss << std::hex << std::setw(2) << std::setfill('0') << counter;
		ss << std::hex << std::setw(2) << std::setfill('0') << dist(rng);
		counter = (counter + 1) % 0x1000;
		return ss.str();
	}

private:
	unsigned int counter;
	std::mt19937 rng;
	std::uniform_int_distribution<> dist;
};