#pragma once

#include <SFML/Graphics.hpp>
#include "anealling.h"

void wind(double temp, const char* fname, const char* ss)
{
    Data* proc = new Data(fname);

    Anealling* prob = new Anealling(proc->get_nodes(), temp);
    auto dlh = prob->try_new();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Nodes");

    auto minX = proc->get_minX() - 100;
    auto maxX = proc->get_maxX() + 100;
    auto minY = proc->get_minY() - 100;
    auto maxY = proc->get_maxY() + 100;

    sf::View view(
        sf::FloatRect(
            minX,
            minY,
            maxX - minX,
            maxY - minY
        )
    );

    window.setView(view);

    auto nodes = proc->get_nodes();

    int x = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {    
                sf::Texture texture;
    
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
    
                sf::Image image = texture.copyToImage();
                image.saveToFile(ss);

                window.close();
            
            }
        }

        window.clear();

        for (int i = 0; i < nodes_size; i++)
        {
            sf::CircleShape dot(4.f);
            dot.setPosition(nodes[i]->X, nodes[i]->Y);
            dot.setFillColor(sf::Color::Yellow);

            if ( i == (nodes_size - 1))
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(nodes[0]->X, nodes[0]->Y), sf::Color::Yellow),
                    sf::Vertex(sf::Vector2f(nodes[nodes_size - 1]->X, nodes[nodes_size - 1]->Y), sf::Color::Yellow)
                };
                
                window.draw(line, 2, sf::Lines);
                window.draw(dot);
            
            } else {

                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(nodes[i]->X, nodes[i]->Y), sf::Color::Yellow),
                    sf::Vertex(sf::Vector2f(nodes[i + 1]->X, nodes[i + 1]->Y), sf::Color::Yellow)
                };
                
                window.draw(line, 2, sf::Lines);
                window.draw(dot);
            }
        }

        if (prob->get_ended())
        {
            sf::Texture texture;
            
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);
    
            sf::Image image = texture.copyToImage();
            image.saveToFile(ss);
            
            window.close();
            
        }

        window.display();

        x++;

        nodes = prob->try_new();
    }
    

    delete proc;
    delete prob;
    return;
}
