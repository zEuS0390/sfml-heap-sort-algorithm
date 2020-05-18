#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.h"

window::window (unsigned int x, unsigned int y)
:   isRunning(true),
    renderWin(sf::VideoMode(x, y), "Heap Sort Algorithm Visualization"),
    spritesObj(&renderWin) {
    init();
}

void window::init (void) {
    loop();
    return;
}

void window::events (void) {
    sf::Event event;
    while (renderWin.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            isRunning = false;
            renderWin.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            spritesObj.events(&event);
        }
    }
    return;
}

void window::updates (void) {
    spritesObj.updates();
    return;
}

void window::renders (void) {
    renderWin.clear();
    spritesObj.renders();
    renderWin.display();
    return;
}

void window::loop (void) {
    while (isRunning) {
        events();
        updates();
        renders();
    }
    return;
}
