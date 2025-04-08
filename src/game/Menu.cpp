#include <iostream> // Para log opcional
#include <SFML/Graphics.hpp>
#include "Menu.hpp"

Menu::Menu(unsigned int width, unsigned int height)
    : selectedIndex(0), selectedOption(Option::NONE)
{
    if (!font.openFromFile("assets/fonts/ArialMdm.ttf")) {
        std::cerr << "Erro ao carregar fonte: assets/fonts/arial.ttf\n";
    }

    const std::vector<std::string> labels = {
        "Jogar Sozinho",
        "Contra IA",
        "Jogar Online"
    };

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text(font);
        text.setString(labels[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(
            sf::Vector2f(width / 2.f - 100.f, height / 2.f + static_cast<float>(i * 60))
        );
        options.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for (const auto& text : options) {
        window.draw(text);
    }
}

void Menu::handleInput(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyPressed->scancode) {
        case sf::Keyboard::Scan::Up:
            if (selectedIndex > 0)
                selectedIndex--;
            break;

        case sf::Keyboard::Scan::Down:
            if (selectedIndex < static_cast<int>(options.size()) - 1)
                selectedIndex++;
            break;

        case sf::Keyboard::Scan::Enter:
            selectedOption = static_cast<Option>(selectedIndex);
            break;

        default:
            break;
        }

        // Atualiza as cores após qualquer mudança
        for (size_t i = 0; i < options.size(); ++i) {
            options[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        }
    }
}

Menu::Option Menu::getSelectedOption() const
{
    return selectedOption;
}
