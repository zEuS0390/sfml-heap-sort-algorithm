#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "sprite.h"

// window class
class window {
    public:
        bool                isRunning;
    public:
        window              (unsigned int,
                             unsigned int);
    private:
        void init           (void);
        void events         (void);
        void updates        (void);
        void renders        (void);
        void loop           (void);
    private:
        sf::RenderWindow    renderWin;
        sprites             spritesObj;

};

#endif
