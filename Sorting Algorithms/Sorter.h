#pragma once

#include "olcPixelGameEngine.h"

class Solver;

class Sorter : public olc::PixelGameEngine {
public:
	Solver* solver;

	Sorter(Solver& _solver) : solver(&_solver) {
		sAppName = solver->title;
		solver->pge = this;
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		solver->Shuffle();

		continueToDisplay();

		solver->Delay(1000);

		solver->Solve();

		if (!solver->Complete())
			std::cout << "Error on solve occured" << std::endl;

		continueToDisplay();

		return false;
	}

	void continueToDisplay() {
		for (int i = 0; i < 10; i++) {
			solver->Display();
			solver->Delay(swapDelay);
		}
	}
};