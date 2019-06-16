#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

sf::Color averageColor(const sf::Image& img);

int colorDistance(const sf::Color& c1, const sf::Color& c2);

std::string centerText(const std::string& text);

#endif