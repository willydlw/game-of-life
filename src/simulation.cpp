#include "simulation.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

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
    std::cerr << "File:: " << __FILE__ << ", func: " << __func__ << " executing\n";

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

    if(!ImGui::SFML::Init(m_window)){
        std::cerr << "[FATAL] ImGui::SFML::Init() failure\n";
        exit(EXIT_FAILURE);
    }
}

Simulation::~Simulation()
{
    std::cerr << "bye bye from ~Simulation()\n";
}


void Simulation::loadPattern(std::string_view name)
{
    std::cerr << __func__ << ", string name: " << name << "\n";
}

#if 0
void Simulation::createPattern(PatternName patternName, int numInstances)
{
    std::vector<Cell> aliveList;

    int r = m_window_height / 2 - 1;
    int c = m_window_width / 2 - 1;

    for(int i = 0; i < 3; i++, r++){
        for(int j = 0; j < 3; j++, c++){
            if(R_PENTOMINO[i][j] == GameLife::ALIVE){
                Cell cell = {.state = GameLife::ALIVE, .row = r, .col = c};
                aliveList.push_back(cell);
            }
        }
    }

    m_game.initializeGrid(aliveList);
}

#endif

void Simulation::run(void)
{
    sf::Clock clock; 

    sf::Text text(m_font);
    const char* genMsg = "Generation ";

    text.setCharacterSize(24);      // in pixels 
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    unsigned int genCount = 1;

    while(m_window.isOpen()){
        while(const std::optional event = m_window.pollEvent()){
            
            ImGui::SFML::ProcessEvent(m_window, *event);

            if(event->is<sf::Event::Closed>()){
                m_window.close();
            }
        }

        ImGui::SFML::Update(m_window, clock.restart());

        ImGui::SetNextWindowPos(ImVec2(m_window_width - 200, 200));
        ImGui::Begin("Button Example");
        if(ImGui::Button("Pause"))
        {
            std::cerr << "Button clicked\n";
        }
        ImGui::End();

        m_game.nextGeneration();

        m_window.clear(sf::Color::Black);

        std::stringstream ss;
        ss << genMsg << genCount << '\n';
        ++genCount;
        text.setString(ss.str());
        text.setPosition(sf::Vector2f{m_window.getSize().x - text.getGlobalBounds().size.x - 10, 
            text.getGlobalBounds().size.y + 10});
        m_window.draw(text);

        // draw everything here
        m_game.draw(m_window, m_cell_size, 2.0f);

        ImGui::SFML::Render(m_window);
        m_window.display();
    }

    ImGui::SFML::Shutdown();
}