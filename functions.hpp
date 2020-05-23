#ifndef FUNCTIONS_H
#include <vector>
#include <stdexcept>
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <string>
#include <cstdlib>

long long int collatz(const long long int& input);
long long int collatz(const long long int& input, int& numberOfDivisions, int& numberOfMultiplications);
int collatzToDepth(const int& counter, const int& startVal);
int collatzToDepth(const int& counter, const int& startVal, int& numberOfDivisions, int& numberOfMultiplications);
void func1ToDepthPrintIncr(const int& counter, const int& startVal);
std::vector<int> functionOfVector(const std::vector<int>& inputVector, long long int(*function)(const long long int& input) = &collatz);
std::vector<int> functionOfVector(const std::vector<int>& inputVector, int& numberOfDivisions, int& numberOfMultiplications, long long int(*function)(const long long int& input) = &collatz);
std::array<std::vector<int>, 2> sortCollatzVector(const std::vector<int>& inputVector);
int findCommonDifference(const std::vector<int>& inputVector);
inline std::string linearEquationOfVectorString(const std::vector<int>& inputVector);
inline std::array<int, 2> linearEquationOfVector(const std::vector<int>& inputVector);
inline std::string printLinearEquation(const std::array<int, 2>& input);
std::vector<int> expandEquationToLength(std::array<int, 2> linearEquation, int lengthOfVector);
std::vector<std::pair<std::array<int, 2>, double>>::iterator equationProbPairVectorIteratorOfInput(std::vector<std::pair<std::array<int, 2>, double>>& inputVector, const std::pair<std::array<int, 2>, double>& target);
std::vector<std::pair<std::array<int, 2>, double>> linearDecompositionOfCollatz(std::vector<int> distribution, int depth, int& numberOfDivisions, int& numberOfMultiplications, double totalProbability = 1);
void readLinearDecompositionOfCollatzOutput(const std::vector<std::pair<std::array<int, 2>, double>>& input);
void runLinearDecompositionOfCollatz(int depth, int distributionLength = 16);
void mainLoop();

#endif // !FUNCTIONS_H

