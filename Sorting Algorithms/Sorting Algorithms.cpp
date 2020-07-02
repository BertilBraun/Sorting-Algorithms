#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Algorithms.h"
#include "Sorter.h"

// For the Future: https://en.wikipedia.org/wiki/Sorting_algorithm#Comparison_sorts

template<typename T>
static void Run() {
	T solver;
	Sorter sorter(solver);
	if (sorter.Construct(w, h, 1, 1))
		sorter.Start();

	std::cout << "Sort took: " << sorter.solver->swaps << " swaps" << std::endl;
}

int main()
{
	while (true) {

		std::cout << "Please enter the type of Solver you want to use:" << std::endl;
		std::cout << "1: Insertion Sort" << std::endl;
		std::cout << "2: Heap Sort" << std::endl;
		std::cout << "3: Bubble Sort" << std::endl;
		std::cout << "4: Merge Sort" << std::endl;
		std::cout << "q: Quit" << std::endl;
		std::cout << "input> ";

		switch (std::cin.get()) {
		case '1': Run<InsertionSort>(); break;
		case '2': Run<HeapSort>(); break;
		case '3': Run<BubbleSort>(); break;
		case '4': Run<MergeSort>(); break;
		case 'q': return 0;
		default: std::cout << "Input not recognised, try again" << std::endl; break;
		}	
		std::cout << "\n\n";
		std::cin.get();
	}
	return 0;
}