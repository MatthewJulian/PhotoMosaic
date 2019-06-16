#ifndef TILE_HPP
#define TILE_HPP

#include <filesystem>
#include <SFML/Graphics/Image.hpp>
#include "Utility.hpp"


class Tile {
public:
	Tile(std::experimental::filesystem::path path, unsigned int maxCount);
	unsigned int getCount() const;
	unsigned int getMaxCount() const;
	void incCount();
	sf::Color getColorWhite() const;
	sf::Color getColorBlack() const;
	const sf::Image& getImageBlack() const;
	const sf::Image& getImageWhite() const;
	std::string getPathString() const;
	bool getIsBestMatchBlack() const;
	void setIsBestMatchBlack(bool isBlack);

private:
	std::experimental::filesystem::path mPath;
	sf::Image mImage;
	sf::Image mImageBlack;
	sf::Image mImageWhite;
	unsigned int mUsedCount;
	unsigned int mMaxCount;
	sf::Color mColorWhite;
	sf::Color mColorBlack;
	bool mIsBestMatchBlack;
};

#endif