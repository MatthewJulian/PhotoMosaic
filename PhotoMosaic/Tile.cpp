#include <SFML/Graphics.hpp>
#include "Tile.hpp"

using namespace std;
namespace filesystem = std::experimental::filesystem;

Tile::Tile(filesystem::path path, unsigned int maxCount) : mPath(path), mUsedCount(0), mMaxCount(maxCount), mIsBestMatchBlack(true) {
	mImage.loadFromFile(mPath.string());

	mImageBlack.create(mImage.getSize().x, mImage.getSize().y, sf::Color::Black);
	mImageBlack.copy(mImage, 0, 0, sf::IntRect(0, 0, 0, 0), true);

	mImageWhite.create(mImage.getSize().x, mImage.getSize().y, sf::Color::Black);
	mImageWhite.copy(mImage, 0, 0, sf::IntRect(0, 0, 0, 0), true);

	mColorBlack = averageColor(mImageBlack);
	mColorWhite = averageColor(mImageWhite);
}

unsigned int Tile::getCount() const {
	return mUsedCount;
}

unsigned int Tile::getMaxCount() const {
	return mMaxCount;
}

void Tile::incCount() {
	++mUsedCount;
}

sf::Color Tile::getColorWhite() const {
	return mColorWhite;
}

sf::Color Tile::getColorBlack() const {
	return mColorBlack;
}

const sf::Image& Tile::getImageBlack() const {
	return mImageBlack;
}

const sf::Image& Tile::getImageWhite() const {
	return mImageWhite;
}

std::string Tile::getPathString() const {
	return mPath.string();
}

bool Tile::getIsBestMatchBlack() const {
	return mIsBestMatchBlack;
}

void Tile::setIsBestMatchBlack(bool isBlack) {
	mIsBestMatchBlack = isBlack;
}