#include <iostream>
#include <stdlib.h>
#include <random>
#include <vector>
#include <ctime>
#include "sprite.h"

sprite::sprite (int index, int value, int width)
:   posX(0),
    index(index),
    value(value),
    width(width) {
    init();
}

void sprite::init (void) {
    shapeSize = sf::Vector2f(width, value*2);
    shape.setSize(shapeSize);
    for (int i = 0; i < index; i++) {
        posX += width;
    }
    currPos = sf::Vector2f(posX, 480-shapeSize.y);
    shape.setPosition(currPos);
    if (index%2) {
        shape.setFillColor(sf::Color::Yellow);
    } else {
        shape.setFillColor(sf::Color(255, 150, 0));
    }
    return;
}

void sprite::changeValue (int value) {
    shapeSize.y = value*2;
    currPos.y = 480-shapeSize.y;
    return;
}

void sprite::update (void) {
    shape.setSize(shapeSize);
    shape.setPosition(currPos);
    return;
}

sprites::sprites (sf::RenderWindow* renderWin)
:   times(0),
    width(20),
    isSorted(false),
    eng(time(NULL)),
    renderWin(renderWin) {
    init();
}

sprites::~sprites (void) {
    spritesVec.clear();
}

void sprites::init (void) {
    // Random numbers
//    int arr[] = {100, 10, 50, 122, 180, 20, 70, 48, 200, 210, 150, 121, 119, 159};
    int arr[640/width];
    for (int i = 0; i < 32; i++) {
        arr[i] = randomNumber(10, 220);
    }
    std::cout << std::endl << "Random numbers (Unsorted Array)" << std::endl << std::endl;
    for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        std::cout << arr[i];
        if (i < sizeof(arr)/sizeof(arr[0])-1) {
            std::cout << ", ";
        }
        vecArray.push_back(arr[i]);
        createSprite(i, arr[i]);
    }
    std::cout << std::endl << std::endl;
    return;
}

int sprites::randomNumber (int MIN, int MAX) {
    std::uniform_int_distribution<int> distr(MIN, MAX);
    return distr(eng);
}

void sprites::createSprite (int index, int value) {
    spritesVec.push_back(sprite(index, value, width));
    return;
}

void sprites::maxHeap (int length, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < length && vecArray[left] > vecArray[largest]) {
        largest = left;
    }
    if (right < length && vecArray[right] > vecArray[largest]) {
        largest = right;
    }
    if (largest != index) {
        std::cout << "Comparison " << times << ": ";
        for (int i = 0; i < length; i++) {
            std::cout << vecArray.at(i);
            if (i < length - 1 )
                std::cout << ", ";
        }
        std::cout << std::endl;
        std::swap(vecArray[index], vecArray[largest]);
        times++;
        maxHeap(length, largest);
    }
    return;
}

void sprites::heapSort (int length) {
    std::cout << "Building Max Heap" << std::endl << std::endl;
    for (int i = length / 2 - 1; i >= 0; i--) {
        maxHeap(length, i);
    }
    std::cout << std::endl << "Heap Sort" << std::endl << std::endl;
    for (int i = length - 1; i > 0; i--) {
        std::swap(vecArray[0], vecArray[i]);
        maxHeap(i, 0);
    }
    std::cout << std::endl << "Sorted Array (Ascending Order)" << std::endl << std::endl;
    for (int i = 0; i < length; i++) {
        std::cout << vecArray.at(i);
        if (i < length-1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    return;
}

void sprites::changeValues (void) {
    for (unsigned int i = 0; i < spritesVec.size(); i++) {
        spritesVec.at(i).changeValue(vecArray.at(i));
    }
    return;
}

void sprites::events (sf::Event* event) {
    if (event->key.code == sf::Keyboard::Enter) {
        if (!isSorted) {
            isSorted = true;
            heapSort(vecArray.size());
            changeValues();
        }
    } else if (event->key.code == sf::Keyboard::R) {
        if (isSorted) {
            times = 0;
            system("cls");
            isSorted = false;
            int arr[640/width];
            for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
                arr[i] = randomNumber(10, 225);
            }
            std::cout << std::endl << "Random numbers (Unsorted Array)" << std::endl << std::endl;
            vecArray.clear();
            for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
                std::cout << arr[i];
                if (i < sizeof(arr)/sizeof(arr[0])-1) {
                    std::cout << ", ";
                }
                vecArray.push_back(arr[i]);
            }
            std::cout << std::endl << std::endl;
            changeValues();
        }
    }
    return;
}

void sprites::updates (void) {
    for (unsigned int i = 0; i < spritesVec.size(); i++) {
        spritesVec.at(i).update();
    }
    return;
}

void sprites::renders (void) {
    for (unsigned int i = 0; i < spritesVec.size(); i++) {
        renderWin->draw(spritesVec.at(i).shape);
    }
    return;
}
