#include "NFA.cpp"

int main(int argc, char const *argv[])
{
	NFA nfa1(argv[1]);
	nfa1.printNFA();
	//nfa1.generateDFA();
	return 0;
}