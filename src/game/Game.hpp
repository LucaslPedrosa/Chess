#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../core/Board.hpp"
#include "Menu.hpp"
#include "GameState.hpp"

class Game {
public:
    Game();
    void run();

private:
    void loadAssets();
    void processEvents(const sf::Event &event);
    void render();

    const unsigned int chessBoard_size = 800;
    const int tileSize = 100;

    sf::RenderWindow window;
    GameState state = GameState::MENU;
    Menu menu {chessBoard_size, chessBoard_size}; 

    Board board;
    sf::Texture boardTexture;
    std::unique_ptr<sf::Sprite> boardSprite;
    std::optional<int> selectedSquare;

    std::unordered_map<Board::Piece, sf::Texture> pieceTextures;
    std::unordered_map<Board::Piece, sf::Sprite> pieceSprites;
};

#endif // GAME_HPP
