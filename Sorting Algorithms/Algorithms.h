#pragma once
#include "Solver.h"

class InsertionSort : public Solver
{
public:
	InsertionSort() : Solver("Insertion Sort")
	{ }

	virtual void Solve() override {
		int i = 1;

		while (i < size()) {

			int j = i;

			while (j > 0 && data[j - 1] > data[j]) {
				Swap(j, j - 1);
				j--;
			}

			i++;
		}
	}
};

class HeapSort : public Solver
{
public:
	HeapSort() : Solver("Heap Sort")
	{ }

	virtual void Solve() override
	{
		heapifyDown();

		int end = size() - 1;

		while (end > 0) {
			Swap(end, 0);
			end--;
			siftDown(0, end);
		}
	}

	int iParent(int i) { return floor((i - 1) / 2); }
	int	iLeftChild(int i) { return 2 * i + 1; }
	int	iRightChild(int i) { return 2 * i + 2; }

	void heapifyDown() {
		for (int start = iParent(size() - 1); start >= 0; start--)
			siftDown(start, size() - 1);
	}

	void siftDown(int start, int end) {
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

			Swap(root, swap);
			root = swap;
		}
	}
	void heapifyUp() {
		for (int end = 1; end < size(); end++)
			siftUp(0, end);
	}

	void siftUp(int start, int end) {
		int child = end;

		while (child > start) {
			int parent = iParent(child);
			if (data[parent] < data[child]) {
				Swap(parent, child);
				child = parent;
			}
			else
				return;
		}
	}
};

class BubbleSort : public Solver
{
public:
	BubbleSort() : Solver("Bubble Sort")
	{ }

	virtual void Solve() override {

		for (int i = 0; i < size() - 1; i++)
			for (int j = 0; j < size() - i - 1; j++)
				if (data[j] > data[j + 1])
					Swap(j, j + 1);
	}
};

class MergeSort : public Solver
{
public:
	MergeSort() : Solver("Merge Sort")
	{ }

	virtual void Solve() override {

		mergeSort(0, size() - 1);
	}

	void merge(int l, int m, int r)
	{
		int n1 = m - l + 1;
		int n2 = r - m;
		
		float* L = new float[n1];
		float* R = new float[n2];

		memcpy(L, data.data.data() + l, (n1) * sizeof(float));
		memcpy(R, data.data.data() + m + 1, (n2) * sizeof(float));

		int i = 0, j = 0;
		while (i < n1 && j < n2)
			if (L[i] <= R[j])
				Set(l++, L[i++]);
			else 
				Set(l++, R[j++]);

		while (i < n1)
			Set(l++, L[i++]);

		while (j < n2)
			Set(l++, R[j++]);

		delete[] L;
		delete[] R;
	}

	void mergeSort(int l, int r)
	{
		if (l < r) {
			int m = (l + r) / 2;

			mergeSort(l, m);
			mergeSort(m + 1, r);

			merge(l, m, r);
		}
	}
};
