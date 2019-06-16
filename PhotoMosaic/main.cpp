#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Tile.hpp"
#include "Utility.hpp"

namespace filesystem = std::experimental::filesystem;
using namespace std;


vector<unique_ptr<Tile>> getTiles(filesystem::path folder, unsigned int maxTileUse = 10);

void createMosiac(string newFilename, vector<unique_ptr<Tile>>& tiles, const sf::Image& sourceImage);

const sf::Image& getBestTileImage(const vector<unique_ptr<Tile>>& tiles, sf::Color pixelColor);


int main() {
	srand(time(nullptr));

	const string title = centerText("Welcome to PhotoMosiac!");
	cout << title << endl << endl;

	string tileFolder;
	string sourceImageFilename;
	string destImageFilename;
	string maxTileUse;
	cout << "Enter folder where tiles are: ";
	cin >> tileFolder;
	cout << "Enter source image file name: ";
	cin >> sourceImageFilename;
	cout << "Enter destination image file name: ";
	cin >> destImageFilename;
	cout << "Enter max number each tile can be used (default is 10): ";
	cin >> maxTileUse;

	cout << "Loading tiles..." << endl;
	filesystem::path tilePath(tileFolder);
	vector<unique_ptr<Tile>> tiles = getTiles(tilePath, stoi(maxTileUse));
	cout << "Loaded " << tiles.size() << " tiles." << endl;

	sf::Image sourceImage;
	sourceImage.loadFromFile(sourceImageFilename);
	cout << "Creating new image..." << endl;
	createMosiac(destImageFilename, tiles, sourceImage);
	cout << "Image created!" << endl;

	system("pause");

	return EXIT_SUCCESS;
}



vector<unique_ptr<Tile>> getTiles(filesystem::path folder, unsigned int maxTileUse /* = 10 */) {
	vector<unique_ptr<Tile>> tiles;
	for (const auto& entry : filesystem::directory_iterator(folder)) {
		tiles.push_back(make_unique<Tile>(entry.path(), maxTileUse));
	}

	return tiles;
}

void createMosiac(string newFilename, vector<unique_ptr<Tile>>& tiles, const sf::Image& sourceImage) {
	const unsigned int imageWidth = sourceImage.getSize().x;
	const unsigned int imageHeight = sourceImage.getSize().y;
	const unsigned int tileWidth = tiles[0]->getImageBlack().getSize().x;
	const unsigned int tileHeight = tiles[0]->getImageBlack().getSize().y;

	sf::Image mosiac;
	mosiac.create(imageWidth * tileWidth, imageHeight * tileHeight, sf::Color::Black);

	for (unsigned int y = 0; y < imageHeight; ++y) {
		for (unsigned int x = 0; x < imageWidth; ++x) {
			const sf::Color pixelColor = sourceImage.getPixel(x, y);

			// If the source pixel is transparent, skip it
			if (pixelColor.a == 0)
				continue;

			const sf::Image& bestMatch = getBestTileImage(tiles, pixelColor);

			mosiac.copy(bestMatch, x * tileWidth, y * tileHeight);
		}

		cout << "Copied " << y + 1 << '/' << imageHeight << " chunks..." << endl;
	}

	tiles.clear();
	cout << "Saving image to disk..." << endl;

	mosiac.saveToFile(newFilename);
}


const sf::Image& getBestTileImage(const vector<unique_ptr<Tile>>& tiles, sf::Color pixelColor) {
	// Depending on how many tiles you have, this will make it so there are less repeated tiles right next to eachother
	const unsigned int RAND_SIZE = 3;

	Tile* bestTiles[RAND_SIZE];

	for (unsigned int i = 0; i < RAND_SIZE; ++i) {
		bestTiles[i] = tiles[0].get();

		int distance = colorDistance(tiles[0]->getColorBlack(), pixelColor);

		for (const auto& tile : tiles) {
			if (tile->getCount() < tile->getMaxCount() && find(begin(bestTiles), end(bestTiles), tile.get()) == end(bestTiles)) {
				int tempDistBlack = colorDistance(tile->getColorBlack(), pixelColor);
				int tempDistWhite = colorDistance(tile->getColorWhite(), pixelColor);

				if (tempDistBlack < distance) {
					distance = tempDistBlack;
					tile->setIsBestMatchBlack(true);
					bestTiles[i] = tile.get();
				}
				if (tempDistWhite < distance) {
					distance = tempDistWhite;
					tile->setIsBestMatchBlack(false);
					bestTiles[i] = tile.get();
				}
			}
		}
	}


	Tile* bestTile = bestTiles[rand() % RAND_SIZE];
	bestTile->incCount();
	if (bestTile->getIsBestMatchBlack())
		return bestTile->getImageBlack();
	else
		return bestTile->getImageWhite();
}
