#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

// sprite class
class sprite {
    public:
        int                     posX;
        int                     index;
        int                     value;
        int                     width;
    public:
        sprite                  (int, int, int);
    public:
        void init               (void);
        void changeValue        (int);
        void update             (void);
    public:
        sf::Vector2f            shapeSize;
        sf::Vector2f            currPos;
        sf::RectangleShape      shape;
};

// sprites class
class sprites {
    public:
        int                     times;
        int                     width;
        bool                    isSorted;
        std::vector<int>        vecArray;
        std::vector<sprite>     spritesVec;
    public:
        sprites                 (sf::RenderWindow*);
        ~sprites                (void);
        void init               (void);
        int randomNumber        (int, int);
        void createSprite       (int, int);
        void maxHeap            (int,
                                 int);
        void heapSort           (int);
        void changeValues       (void);
        void events             (sf::Event*);
        void updates            (void);
        void renders            (void);
    private:
        std::mt19937            eng;
        sf::Clock               clock;
        sf::RenderWindow*       renderWin;
};

#endif
