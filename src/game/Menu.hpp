#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Menu
{
public:
  enum class Option
  {
    PLAY_SOLO,
    PLAY_VS_AI,
    PLAY_ONLINE,
    NONE
  };

  Menu(unsigned int width, unsigned int height);
  void draw(sf::RenderWindow &window);
  void handleInput(const sf::Event &event);
  Option getSelectedOption() const;

private:
  sf::Font font;
  std::vector<sf::Text> options;
  int selectedIndex;
  Option selectedOption;
};

#endif // MENU_HPP
