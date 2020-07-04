#pragma once
#include "olcPixelGameEngine.h"
#include "Config.h"

#include <array>

class Data {
public:
	int accesses = 0;

	int size() {
		return data.size();
	}

	float& operator[](int i) {
		accesses++;
		return data[i];
	}

	float& get(int i) {
		return data[i];
	}
	float& getCol(int i) {
		return color[i];
	}

	std::array<float, collums> data;
	std::array<float, collums> color;
};

class Solver {
public:
	const char* title;
	int swaps = 0;

	Solver(const char* _title) : title(_title)
	{
		for (int i = 0; i < size(); i++)
			data.get(i) = (float)(i + 1) / (float)size();
	}

	virtual void Solve() = 0;

	void Shuffle() {

		for (int i = 0; i < size() * 1.5; i++)
			Swap(rand() % size(), rand() % size(), shuffleDelay);
	}

	void Swap(int from, int to, int ms = swapDelay) {
		if (ms == swapDelay) {
			std::swap(data[from], data[to]);
			swaps++;
		}
		else
			std::swap(data.get(from), data.get(to));
		data.getCol(to) = 0;
		Display();
		Delay(ms);
	}

	void Set(int to, float d) {
		data[to] = d;
		swaps++;
		data.getCol(to) = 0;
		Display();
		Delay(swapDelay);
	}

	bool Complete() {
		for (int i = 1; i < size(); i++) {
			data.getCol(i) = 0;
			Display();
			if (data.get(i) < data.get(i - 1))
				return false;
		}
		return true;
	}

	void Display() {
		pge->Clear(olc::BLACK);

		for (int i = 0; i < size(); i++) {

			int w = std::round((float)pge->ScreenWidth() / (float)size());
			int h = std::round(data.get(i) * (pge->ScreenHeight() - 30));
			int x = std::round(((float)i / (float)size()) * (float)pge->ScreenWidth());
			int y = pge->ScreenHeight() - h;

			pge->FillRect(x, y, w, h, olc::Pixel(255, data.getCol(i) * 255, data.getCol(i) * 255));
			data.getCol(i) += 0.1;
			if (data.getCol(i) > 1)
				data.getCol(i) = 1;
		}

		pge->DrawString(5, 5, title, olc::WHITE, 2);
		pge->DrawString(300, 5, "Swaps: " + std::to_string(swaps), olc::WHITE, 2);
		pge->DrawString(500, 5, "Accesses: " + std::to_string(data.accesses), olc::WHITE, 2);
		pge->Flush();
	}

	int size() {
		return data.size();
	}

	void Delay(size_t delay) {
		std::this_thread::sleep_for(std::chrono::microseconds(delay));
	}

	olc::PixelGameEngine* pge;
	Data data;
};