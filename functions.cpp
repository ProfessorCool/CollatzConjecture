#include "functions.hpp"

long long int collatz(const long long int& input) //The input function F(X)
{
	if (input < 1)
		throw std::invalid_argument("Must be positive integer");
	if (input % 2 == 1)
		return 3 * input + 1;
	else
		return input / 2;
}
long long int collatz(const long long int& input, int& numberOfDivisions, int& numberOfMultiplications) //The input function F(X)
{
	if (input < 1)
		throw std::invalid_argument("Must be positive integer");
	if (input % 2 == 1)
	{
		++numberOfMultiplications;
		return 3 * input + 1;
	}
	else
	{
		++numberOfDivisions;
		return input / 2;
	}
}
int collatzToDepth(const int& counter, const int& startVal) //Outputs the value after counter iterations
{
	if (counter < 1)
		throw std::invalid_argument("Can't be less than one");
	int val = startVal;
	for (int i = 0; i != counter; ++i)
	{
		val = collatz(val);
	}
	return val;
}
int collatzToDepth(const int& counter, const int& startVal, int& numberOfDivisions, int& numberOfMultiplications) //Outputs the value after counter iterations
{
	if (counter < 1)
		throw std::invalid_argument("Can't be less than one");
	int val = startVal;
	for (int i = 0; i != counter; ++i)
	{
		val = collatz(val, numberOfDivisions, numberOfMultiplications);
	}
	return val;
}
void func1ToDepthPrintIncr(const int& counter, const int& startVal) //Similar to func1ToDepth, but prints every value iterated through
{
	if (counter < 1)
		throw std::invalid_argument("Can't be less than one");
	int val = startVal;
	for (int i = 0; i != counter; ++i)
	{
		std::cout << i + 1;
		if (i + 1 < 10)
			std::cout << "  | ";
		else
			std::cout << " | ";
		std::cout << "F(" << val << ") = ";
		val = collatz(val);
		std::cout << val << "\n";
	}
}
std::vector<int> functionOfVector(const std::vector<int>& inputVector, long long int(*function)(const long long int& input))
{
	std::vector<int> temp = {};
	for (auto i = inputVector.begin(); i != inputVector.end(); ++i)
	{
		temp.push_back(collatz(*i));
	}
	return temp;
}
std::vector<int> functionOfVector(const std::vector<int>& inputVector, int& numberOfDivisions, int& numberOfMultiplications, long long int(*function)(const long long int& input))
{
	std::vector<int> temp = {};
	for (auto i = inputVector.begin(); i != inputVector.end(); ++i)
	{
		temp.push_back(collatz(*i, numberOfDivisions, numberOfMultiplications));
	}
	return temp;
}
std::array<std::vector<int>, 2> sortCollatzVector(const std::vector<int>& inputVector)
{
	if (inputVector.size() % 2 != 0)
		throw std::invalid_argument("Must be even number of elements in vector");
	std::vector<int> temp = {};
	std::vector<int> temp2 = {};
	for (int i = 0; i != inputVector.size(); ++i)
	{
		if (i % 2 == 0)
			temp.push_back(inputVector[i]);
		else
			temp2.push_back(inputVector[i]);
	}
	/*std::vector<int> temp3 = {};
	temp3.reserve(temp.size() + temp2.size());
	temp3.insert(temp3.end(), temp.begin(), temp.end());
	temp3.insert(temp3.end(), temp2.begin(), temp2.end());
	*/
	return std::array<std::vector<int>, 2>({ { { { temp } },{ { temp2 } } } });
}
int findCommonDifference(const std::vector<int>& inputVector)
{
	std::vector<int> temp;
	for (int i = 1; i != inputVector.size(); ++i)
		temp.push_back(inputVector[i] - inputVector[i - 1]);
	if (std::adjacent_find(temp.begin(), temp.end(), std::not_equal_to<>()) != temp.end())
		throw std::runtime_error("all values not equal");
	else
		return temp[0];
}
inline std::string linearEquationOfVectorString(const std::vector<int>& inputVector)
{
	return std::string(std::to_string(findCommonDifference(inputVector)) + "n+" + std::to_string(inputVector[0]));
}
inline std::array<int, 2> linearEquationOfVector(const std::vector<int>& inputVector)	// arr[0] is coefficient, arr[1] is y intercept
{
	//{ { { { findCommonDifference(inputVector) } },{ { inputVector[0] } } } };
	std::array<int, 2> output;
	output[0] = findCommonDifference(inputVector);
	output[1] = inputVector[0];
	return output;
}
inline std::string printLinearEquation(const std::array<int, 2>& input)
{
	return std::string(std::to_string(input[0]) + "n+" + std::to_string(input[1]));
}
std::vector<int> expandEquationToLength(std::array<int, 2> linearEquation, int lengthOfVector)
{
	std::vector<int> temp;
	for (int i = 0; i != lengthOfVector; ++i)
	{
		temp.push_back(linearEquation[0] * i + linearEquation[1]);
	}
	return temp;
}
std::vector<std::pair<std::array<int, 2>, double>>::iterator equationProbPairVectorIteratorOfInput(std::vector<std::pair<std::array<int, 2>, double>>& inputVector, const std::pair<std::array<int, 2>, double>& target)
{
	for (auto iOfPairs = inputVector.begin(); iOfPairs != inputVector.end(); ++iOfPairs)
	{
		if (std::get<0>(*iOfPairs) == std::get<0>(target))
			return iOfPairs;
	}
	return inputVector.end();
}
std::vector<std::pair<std::array<int, 2>, double>> linearDecompositionOfCollatz(std::vector<int> distribution, int depth, int& numberOfDivisions, int& numberOfMultiplications, double totalProbability)	//Returns a vector (all possibilities) of pairs of linear equations (an+b) and their probability of occuring; and number of divisions and multiplications is returned via reference
{
	//I'm going to finish this function out of a sense of spite
	//THE numberOfMultiplications and numberOfDivisions SHOULD BE INPUT AS 0
	//for (int i = 0; i != lengthOfVectorsUsed; ++i)
	//	distribution.push_back(i);
	const int sizeOfVector = distribution.size();

	distribution = functionOfVector(distribution, numberOfDivisions, numberOfMultiplications);	//Runs the collatz function on the distribution

	std::array<std::vector<int>, 2> sortedDistributions = sortCollatzVector(distribution);
	//Sorts the distribution into 2 vectors

	//std::vector<std::array<int, 2>> linearEquations = {linearEquationOfVector(sortedDistributions[0]), linearEquationOfVector(sortedDistributions[1])};
	//Above seems unnecessary



	if (depth != 0)
	{
		std::vector<int> distributionSorted1 = expandEquationToLength(linearEquationOfVector(sortedDistributions[0]), sizeOfVector);
		std::vector<int> distributionSorted2 = expandEquationToLength(linearEquationOfVector(sortedDistributions[1]), sizeOfVector);
		//The linear equations are turned into 2 vectors to be passed into the recursive function

		std::vector<std::pair<std::array<int, 2>, double>> returnOfRecursion1 = linearDecompositionOfCollatz(distributionSorted1, depth - 1, numberOfDivisions, numberOfMultiplications, totalProbability / 2);
		std::vector<std::pair<std::array<int, 2>, double>> returnOfRecursion2 = linearDecompositionOfCollatz(distributionSorted2, depth - 1, numberOfDivisions, numberOfMultiplications, totalProbability / 2);

		std::vector<std::pair<std::array<int, 2>, double>> equationProbPairVector;
		for (const auto& vec1 : returnOfRecursion1)
		{
			if (equationProbPairVectorIteratorOfInput(equationProbPairVector, vec1) != equationProbPairVector.end())
			{
				auto iteratorPos = equationProbPairVectorIteratorOfInput(equationProbPairVector, vec1);
				std::get<1>(*iteratorPos) += std::get<1>(vec1);
			}
			else
				equationProbPairVector.push_back(vec1);
		}
		for (const auto& vec2 : returnOfRecursion2)
		{
			if (equationProbPairVectorIteratorOfInput(equationProbPairVector, vec2) != equationProbPairVector.end())
			{
				auto iteratorPos = equationProbPairVectorIteratorOfInput(equationProbPairVector, vec2);
				std::get<1>(*iteratorPos) += std::get<1>(vec2);
			}
			else
				equationProbPairVector.push_back(vec2);
		}
		return equationProbPairVector;
	}
	else
	{
		std::pair<std::array<int, 2>, double> equationProbPair1 = std::make_pair(linearEquationOfVector(sortedDistributions[0]), totalProbability / 2);
		std::pair<std::array<int, 2>, double> equationProbPair2 = std::make_pair(linearEquationOfVector(sortedDistributions[1]), totalProbability / 2);
		//Above generates a pair of linear equation formulas and their probability of occuring
		std::vector<std::pair<std::array<int, 2>, double>> equationProbPairVector = { equationProbPair1, equationProbPair2 };
		//Above puts these into a vector, for further assimilation up the line
		return equationProbPairVector;
	}
}
void readLinearDecompositionOfCollatzOutput(const std::vector<std::pair<std::array<int, 2>, double>>& input)
{
	for (const auto& pairs : input)
	{
		std::cout << printLinearEquation(std::get<0>(pairs)) << " has probability " << std::to_string(std::get<1>(pairs)) << "\n";
	}
}
void runLinearDecompositionOfCollatz(int depth, int distributionLength)
{
	std::vector<int> distribution = {};
	for (int i = 0; i != distributionLength; ++i)
		distribution.push_back(i + 1);
	int numberOfDivisions = 0;
	int numberOfMultiplications = 0;
	readLinearDecompositionOfCollatzOutput(linearDecompositionOfCollatz(distribution, depth, numberOfDivisions, numberOfMultiplications));
	double probabilityOfDivision = static_cast<double>(numberOfDivisions) / (static_cast<double>(numberOfDivisions) + static_cast<double>(numberOfMultiplications));
	std::cout << "There were " << numberOfDivisions << " divisions and " << numberOfMultiplications << " multiplications.\nThe probability of division was " << probabilityOfDivision << "\n";
	double ratio = static_cast<double>(numberOfMultiplications) / static_cast<double>(numberOfDivisions);
	constexpr double lim = 0.63092975357;
	if (ratio < lim)
		std::cout << "The condition was satisfied, with a difference of: " << lim - ratio << "\n";
	else
		std::cout << "The condition was not satisfied, with a difference of: " << ratio - lim << "\n";
}
void mainLoop()
{
	std::cout << "Enter a number to perform a linear decomposition of the collatz function to that depth.\nWARNING!ENTERING NUMBERS ABOVE 10 WILL TAKE A SIGNIFICANT AMOUNT OF TIME!\nGarbage inputs may yield unexpected results.\nType \"exit\" without quotes to exit.\n";
	std::string input;
	while (std::cin >> input)
	{
		if (input.compare(std::string("exit")) == 0)
			break;
		else
			runLinearDecompositionOfCollatz(std::stoi(input));
	}
}