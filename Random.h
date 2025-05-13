//
// Created by Cally on 4/2/2021.
//

#ifndef PROJECT_3_RANDOM_H
#define PROJECT_3_RANDOM_H

#include <random>
using namespace std;

class Random {

    static mt19937 random;

public:

    static int Int(int min, int max);
    static float Float(float min, float max);
};


#endif //PROJECT_3_RANDOM_H
