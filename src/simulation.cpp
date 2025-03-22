#include "simulation.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <optional>
#include <random>
#include <sstream>

// Simulation Class Constant Definitions
const char* Simulation::GENERATION_MSG  = "Generation ";

// Constructor
Simulation::Simulation(SimConfig& sc) : 
        m_window_width(sc.window_width), 
        m_window_height(sc.window_height),
       // m_grid_width(sc.grid_width),
       // m_grid_height(sc.grid_height),
        m_cell_size(sc.cell_size),
        m_game(sc.grid_rows, sc.grid_cols)
{
    std::cerr << __func__ << " constructor executing\n";
    init(sc);
}

// Destructor
Simulation::~Simulation()
{
    std::cerr << "bye bye from ~Simulation()\n";
}


void Simulation::init(SimConfig& sc)
{
    std::cerr << "File:: " << __FILE__ << ", func: " << __func__ << " executing\n";

    m_window.create(sf::VideoMode({m_window_width, m_window_height}), "Game of Life Simulation"); 
    
    if(!m_font.openFromFile("resources/arial.ttf"))
    {
        std::cerr << "[FATAL] " << __func__ << ", failed to open font file arial.ttf\n";
        exit(EXIT_FAILURE);
    }

    m_window.setFramerateLimit(sc.framerate);

    // TODO: pass intialization pattern to function (add to config)
    // for now, we test with random initialization
    std::vector<Cell> aliveLocations;
    initPattern(aliveLocations, sc.pid);
    m_game.initializeGrid(aliveLocations);

    #if 0
    if(!ImGui::SFML::Init(m_window)){
        std::cerr << "[FATAL] ImGui::SFML::Init() failure\n";
        exit(EXIT_FAILURE);
    }
    #endif 
}

void Simulation::initPattern(std::vector<Cell>& cells, Pattern::PatternId pid, int numInstances)
{
    
    switch(pid)
    {
        case Pattern::BLOCK:
        case Pattern::BEEHIVE:
        case Pattern::LOAF:
        case Pattern::BOAT:
        case Pattern::TUB:
        case Pattern::BLINKER:
        case Pattern::TOAD:
        case Pattern::BEACON:
        {
            int rowInstances = numInstances;
            int colInstances = numInstances;
            int patternRows = Pattern::patterns[pid].rows;
            int patternCols = Pattern::patterns[pid].cols;

            int gridRows = m_game.rows();
            int gridCols = m_game.cols();

            std::cerr << "pattern: " << Pattern::patternNames[pid] << "\n";
            std::cerr << "patternRows: " << patternRows << ", patternCols: " << patternCols << "\n";
            std::cerr << "grid rows:   " << gridRows << ", grid cols: " << gridCols << "\n";

            while(rowInstances > (gridRows/patternRows)){
                --rowInstances;
            }

            while(colInstances > gridCols/patternCols)
            {
                --colInstances;
            }

            std::cerr << "numInstances: " << numInstances << ", rowInstances: " << rowInstances 
                << ", colInstances: " << colInstances << "\n";
            
            
            int rowOffset = (gridRows - (rowInstances * patternRows)) / rowInstances;
            int colOffset = (gridCols - (colInstances * patternCols)) / colInstances;

            std::cerr << "rowOffset: " << rowOffset << ", colOffset: " << colOffset << "\n";
            
            #if 1
            for(int i = 0; i < colInstances; i++){
                // iterate through the pattern
                for(int pr = 0; pr < Pattern::patterns[pid].rows; pr++){
                    for(int pc = 0; pc < Pattern::patterns[pid].cols; pc++){
                        int r = i * pr + rowOffset;
                        int c = i * pc + colOffset;
                        //std::cerr << "i: " << i << ", r: " << r << ", c: " << c << "\n";
                        Cell cell = {.state = Pattern::patterns[pid].data[pr][pc],
                        .row = r, .col = c};
                        cells.push_back(cell);
                    }
                }
            }
            #endif
        }
        break;
        case Pattern::RANDOM:
            initRandom(cells, GameLife::DEAD, GameLife::ALIVE);
        break;
    }
}



void Simulation::initRandom(std::vector<Cell>& cells, int min, int max)
{
    // seed random number generator
    // make it static to ensure it is only seeded once
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    for(int r = 0; r < m_game.rows(); r++){
        for(int c = 0; c < m_game.cols(); c++){
            int random_num = distrib(gen);
            if(random_num == GameLife::ALIVE){
                Cell cell{.state = GameLife::ALIVE, .row = r, .col = c};
                cells.push_back(cell);
            }
        }
    }
}


void Simulation::run(void)
{
    sf::Color Light_Gray {211,211,211};
    sf::Clock clock; 

    sf::Text text(m_font);
   

    text.setCharacterSize(24);      // in pixels 
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    unsigned int genCount = 1;

    while(m_window.isOpen()){
        while(const std::optional event = m_window.pollEvent()){
            
            //ImGui::SFML::ProcessEvent(m_window, *event);

            if(event->is<sf::Event::Closed>()){
                m_window.close();
            }
        }

        #if 0
        ImGui::SFML::Update(m_window, clock.restart());

        ImGui::SetNextWindowPos(ImVec2(m_window_width - 200, 200));
        ImGui::Begin("Button Example");
        if(ImGui::Button("Pause"))
        {
            std::cerr << "Button clicked\n";
        }
        ImGui::End();
        #endif 

        m_game.nextGeneration();

        m_window.clear(Light_Gray);

        std::stringstream ss;
        ss << GENERATION_MSG << genCount << '\n';
        ++genCount;
        text.setString(ss.str());
        text.setPosition(sf::Vector2f{m_window.getSize().x - text.getGlobalBounds().size.x - 10, 
            text.getGlobalBounds().size.y + 10});
        m_window.draw(text);

        // draw everything here
       m_game.draw(m_window, m_cell_size, 2.0f);

        m_game.draw_grid_lines(m_window, m_cell_size, 2.0f);

        //ImGui::SFML::Render(m_window);
        m_window.display();
    }

   // ImGui::SFML::Shutdown();
}