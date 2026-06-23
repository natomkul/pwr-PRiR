#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#define nodes_size 48

struct Node
{
 public:
    int id;
    int X, Y;
};

class Data
{
 private:
    std::vector<std::shared_ptr<Node>> nodes;

    int min_x = 0;
    int min_y = 0;

    int max_x = 0;
    int max_y = 0;
 
 public:
    Data(const char* file);
    void printData();

    int get_minX();
    int get_maxX();

    int get_minY();
    int get_maxY();

    std::vector<std::shared_ptr<Node>> get_nodes();
};
