#ifndef MAPGENERATION_H_INCLUDED
#define MAPGENERATION_H_INCLUDED

#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include <limits>

void generateObstacles(int mapRows, int mapColumns, int obstaclesNumber, std::vector<std::pair<int,int>>& obstaclesCoord);
void generateMap(std::vector<std::vector<int>>& randomMap, int mapRows, int mapColumns, std::vector<std::pair<int,int>>& obstaclesCoord);
void printMap(int mapRows, int mapColumns, std::vector<std::vector<int>>& randomMap);
void clearMap(std::vector<std::vector<int>>& randomMap, std::vector<std::pair<int,int>>& obstaclesCoord);
void createRectangle(uint startX, uint startY, int width, int length, std::vector<std::vector<int>>& mapVector);

#endif // MAPGENERATION_H_INCLUDED
