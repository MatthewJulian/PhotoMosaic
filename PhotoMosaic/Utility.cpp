#include <iostream>

#include <vector>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Utility.hpp"

using namespace std;

sf::Color averageColor(const sf::Image& img) {
	const sf::Vector2u VSIZE = img.getSize();
	const unsigned int SIZE = VSIZE.x * VSIZE.y;
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;

	for (unsigned int y = 0; y < VSIZE.y; ++y) {
		for (unsigned int x = 0; x < VSIZE.x; ++x) {
			sf::Color color = img.getPixel(x, y);
			red += color.r;
			green += color.g;
			blue += color.b;
		}
	}

	red /= SIZE;
	green /= SIZE;
	blue /= SIZE;

	return sf::Color(red, green, blue, 255);
}

int colorDistance(const sf::Color& c1, const sf::Color& c2) {
	int red = c2.r - c1.r;
	int green = c2.g - c1.g;
	int blue = c2.b - c1.b;

	return static_cast<int>(sqrt((red * red) + (green * green) + (blue * blue)));
}

string centerText(const string& text) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	const int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	const int diff = columns - text.length();
	const int padLeft = diff / 2;
	const int padRight = diff - padLeft;
	return string(padLeft, ' ') + text + std::string(padRight, ' ');
}
