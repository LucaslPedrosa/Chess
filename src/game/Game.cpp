#include <optional>
#include <iostream>

#include "Game.hpp"
#include "GameState.hpp"
#include "Menu.hpp"

Game::Game()
    : window(sf::VideoMode({chessBoard_size, chessBoard_size}), "Chess", sf::Style::Close | sf::Style::Titlebar)
{
    window.setFramerateLimit(60);
    board.initialize();
    loadAssets();
}

void Game::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (state == GameState::MENU)
            {
                menu.handleInput(*event);
                if (menu.getSelectedOption() != Menu::Option::NONE)
                {
                    state = GameState::PLAYING;
                }
            }
            else if (state == GameState::PLAYING)
            {
                processEvents(*event); // 👈 Agora com argumento
            }
        }

        render();
    }
}

void Game::loadAssets()
{

    if (!boardTexture.loadFromFile("assets/textures/boards/ChessBoard_brown.png"))
    {
        std::cerr << "Failed to load board texture" << std::endl;
        return;
    }
    boardTexture.setSmooth(true); // Enable smooth scaling for better quality
    if (!moveSelfSoundBuffer.loadFromFile("assets/audio/move-self.mp3"))
    {
        std::cerr << "Failed to load move sound" << std::endl;
        return;
    }
    else
    {
        moveSelfSound = std::make_unique<sf::Sound>(moveSelfSoundBuffer);
        moveSelfSound->setVolume(50.f);
    }

    boardSprite = std::make_unique<sf::Sprite>(boardTexture);
    boardSprite->setScale(sf::Vector2f(
        static_cast<float>(chessBoard_size) / boardTexture.getSize().x,
        static_cast<float>(chessBoard_size) / boardTexture.getSize().y));

    std::unordered_map<Board::Piece, std::string> pieceTextureFiles = {
        {Board::Piece::WHITE_PAWN, "wp.png"},
        {Board::Piece::BLACK_PAWN, "bp.png"},
        {Board::Piece::WHITE_KNIGHT, "wn.png"},
        {Board::Piece::BLACK_KNIGHT, "bn.png"},
        {Board::Piece::WHITE_BISHOP, "wb.png"},
        {Board::Piece::BLACK_BISHOP, "bb.png"},
        {Board::Piece::WHITE_ROOK, "wr.png"},
        {Board::Piece::BLACK_ROOK, "br.png"},
        {Board::Piece::WHITE_QUEEN, "wq.png"},
        {Board::Piece::BLACK_QUEEN, "bq.png"},
        {Board::Piece::WHITE_KING, "wk.png"},
        {Board::Piece::BLACK_KING, "bk.png"}};

    for (const auto &[piece, filename] : pieceTextureFiles)
    {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/textures/pieces/bases/" + filename))
        {
            std::cerr << "Failed to load piece texture: " << filename << std::endl;
            continue;
        }
        texture.setSmooth(true); // Enable smooth scaling for better quality
        pieceTextures[piece] = texture;

        sf::Sprite sprite(pieceTextures[piece]);
        sprite.setScale(sf::Vector2f(
            static_cast<float>(tileSize) / texture.getSize().x,
            static_cast<float>(tileSize) / texture.getSize().y));
        pieceSprites.emplace(piece, sprite);
    }
}
void Game::processEvents(const sf::Event &event)
{
    if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            int x = mousePressed->position.x;
            int y = mousePressed->position.y;

            int file = x / tileSize;
            int rank = 7 - (y / tileSize); // Lembrando que o tabuleiro foi invertido na hora de desenhar

            // ✅ Verificação de limites
            if (file < 0 || file >= 8 || rank < 0 || rank >= 8)
                return;

            int clickedSquare = rank * 8 + file;

            if (!selectedSquare.has_value())
            {
                if (board.getPieceAt(clickedSquare) != Board::Piece::EMPTY)
                {
                    selectedSquare = clickedSquare;
                }
            }
            else
            {
                Board::Piece movingPiece = board.getPieceAt(selectedSquare.value());
                board.setPieceAt(clickedSquare, movingPiece);
                board.setPieceAt(selectedSquare.value(), Board::Piece::EMPTY);
                selectedSquare.reset();
                // Play the sound when a piece is moved
                if (moveSelfSound)
                    moveSelfSound->play();
            }
        }
    }
}

void Game::render()
{
    window.clear();

    if (state == GameState::MENU)
    {
        menu.draw(window);
    }
    else if (state == GameState::PLAYING)
    {
        window.draw(*boardSprite);

        for (int square = 0; square < 64; ++square)
        {
            Board::Piece p = board.getPieceAt(square);
            if (p == Board::Piece::EMPTY)
                continue;

            int file = square % 8;
            int rank = 7 - square / 8;

            sf::Sprite &sprite = pieceSprites.at(p);
            sprite.setPosition(sf::Vector2f(file * tileSize, rank * tileSize));
            window.draw(sprite);
        }
    }

    window.display();
}