#include "simulation.hpp"

#include <optional>
#include <sstream>


Simulation::Simulation(SimConfig sc) : 
        m_window_width(sc.window_width), 
        m_window_height(sc.window_height),
        m_cell_size(sc.cell_size),
        m_game(sc.grid_rows, sc.grid_cols)
{
    std::cerr << __func__ << " constructor executing\n";
    init(sc.framerate);
}

void Simulation::init(int framerate)
{
    std::cerr << __func__ << " initialization executing\n";

    m_window.create(sf::VideoMode({m_window_width, m_window_height}), "Game of Life Simulation"); 
    
    if(!m_font.openFromFile("resources/arial.ttf"))
    {
        std::cerr << "[FATAL] " << __func__ << ", failed to open font file arial.ttf\n";
        exit(EXIT_FAILURE);
    }

    m_window.setFramerateLimit(framerate);

    // TODO: pass intialization pattern to function (add to config)
    // for now, we test with random initialization
    m_game.initRandom();
}

Simulation::~Simulation()
{
    std::cerr << "bye bye from ~Simulation()\n";
}


void Simulation::run(void)
{
    sf::Text text(m_font);
    const char* genMsg = "Generation ";

    text.setCharacterSize(24);      // in pixels 
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    unsigned int genCount = 1;

    while(m_window.isOpen()){
        while(const std::optional event = m_window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                m_window.close();
            }
        }

        m_window.clear(sf::Color::Black);
        m_game.nextGeneration();

        std::stringstream ss;
        ss << genMsg << genCount << '\n';
        ++genCount;
        text.setString(ss.str());
        text.setPosition(sf::Vector2f{m_window.getSize().x - text.getGlobalBounds().size.x - 10, 
            text.getGlobalBounds().size.y + 10});
        m_window.draw(text);

        // draw everything here
        m_game.draw(m_window, m_cell_size, 2.0f);
        m_window.display();
    }
}