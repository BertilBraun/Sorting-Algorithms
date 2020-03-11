#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <array>

// For the Future: https://en.wikipedia.org/wiki/Sorting_algorithm#Comparison_sorts

static const size_t dataSize = 50;
static const size_t scale = 1;
static const size_t pixelScale = 10;
static const size_t swapDelay = 10;

static void Delay(size_t delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

class Data : public std::array<float, dataSize>
{
public:
	Data(olc::PixelGameEngine* pge) : pge(pge) {
		for (int i = 0; i < size(); i++)
			(*this)[i] = (float)(i + 1) / (float)size();
	}

	void Shuffle() {
		for (int i = 0; i < size() * 2; i++)
			_Swap(rand() % size(), rand() % size(), 2);
	}

	void Swap(int from, int to) {
		_Swap(from, to, swapDelay);
		Display();
	}

	bool Complete() {
		for (int i = 1; i < size(); i++)
			if ((*this)[i] < (*this)[i - 1])
				return false;
		return true;
	}

private:
	void _Swap(int from, int to, int ms) {
		float temp = (*this)[from];
		(*this)[from] = (*this)[to];
		(*this)[to] = temp;
		Delay(ms);
	}

	void Display() {
		pge->Clear(olc::BLACK);

		for (int i = 0; i < size(); i++) {

			int w = (float)pge->ScreenWidth() / (float)size();
			int h = (*this)[i] * pge->ScreenHeight();
			int x = ((float)i / (float)size()) * pge->ScreenWidth();
			int y = pge->ScreenHeight() - h;

			pge->FillRect(x, y, w, h, olc::WHITE);
		}

		pge->Flush();
	}

	olc::PixelGameEngine* pge;
};

class Solver {
public:
	virtual void Solve(Data& data) = 0;
};

class InsertionSolver : public Solver {
public:

	virtual void Solve(Data& data) override
	{
		int i = 1;

		while (i < data.size()) {

			int j = i;

			while (j > 0 && data[j - 1] > data[j]) {
				data.Swap(j, j - 1);
				j--;
			}

			i++;
		}
	}
};

class HeapSolver : public Solver {
public:

	virtual void Solve(Data& data) override
	{
		heapifyDown(data);

		int end = data.size() - 1;

		while (end > 0) {
			data.Swap(end, 0);
			end--;
			siftDown(data, 0, end);
		}
	}

	int iParent(int i) { return floor((i - 1) / 2); }
	int	iLeftChild(int i) { return 2 * i + 1; }
	int	iRightChild(int i) { return 2 * i + 2; }

	void heapifyDown(Data& data) {
		for (int start = iParent(data.size() - 1); start >= 0; start--)
			siftDown(data, start, data.size() - 1);
	}

	void siftDown(Data& data, int start, int end) {
		int root = start;

		while (iLeftChild(root) <= end) {
			int child = iLeftChild(root);
			int swap = root;

			if (data[swap] < data[child])
				swap = child;
			if (child + 1 <= end && data[swap] < data[child + 1])
				swap = child + 1;
			if (swap == root)
				return;
			
			data.Swap(root, swap);
			root = swap;
		}
	}
	void heapifyUp(Data& data) {
		for (int end = 1; end < data.size(); end++)
			siftUp(data, 0, end);
	}

	void siftUp(Data& data, int start, int end) {
		int child = end;

		while (child > start) {
			int parent = iParent(child);
			if (data[parent] < data[child]) {
				data.Swap(parent, child);
				child = parent;
			}
			else
				return;
		}
	}
};

class SortingAlgorithms : public olc::PixelGameEngine
{
public:
	SortingAlgorithms() : data(this)
	{
		sAppName = "Sorting Algorithms";
	}

public:
	bool OnUserCreate() override
	{
		//solver = new InsertionSolver();
		solver = new HeapSolver();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		data.Shuffle();

		Delay(1000);

		solver->Solve(data);

		if (!data.Complete())
			std::cout << "Error on solve occured" << std::endl;

		Delay(2000);

		return true;
	}

	Solver* solver;
	Data data;
};


int main()
{
	SortingAlgorithms demo;
	if (demo.Construct(dataSize * scale, dataSize * scale, pixelScale, pixelScale))
		demo.Start();

	return 0;
}