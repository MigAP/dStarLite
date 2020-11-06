#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include <limits>
#include "mapGeneration.h"
#include "dStarLite.h"
#include <chrono>

std::vector<std::vector<int>> randomMap; // Randomly generated map
std::vector<std::pair<int,int>> obstaclesCoord; // Obstacles Coordinates

int mapRows, mapColumns, obstaclesNumber;
int km {0};

Node startNode = {infinity,infinity,0,std::pair<int,int>(25,49)};
Node goalNode = {infinity,0,0,std::pair<int,int>(25,0), false};
//
//Node startNode = {infinity,infinity,0,std::pair<int,int>(0,0)};
//Node goalNode = {infinity,0,0,std::pair<int,int>(4,4), false};

priorityList uList; // priority List
priorityList2 uList2; // priority List
mappedNodes knownNodes; // node the robot can see

int main()
{

  std::cout << (std::numeric_limits<int>::max() > infinity ) << std::endl;
  std::cout << "Infinity " << infinity << std::endl;

  std::cout << "Enter the number of rows" << std::endl;
  std::cin >> mapRows;
  std::cout << "Enter the number of columns" << std::endl;
  std::cin >> mapColumns;
  std::cout << "Enter the number of Obstacles" << std::endl;
  std::cin >> obstaclesNumber;

  // MAP GENERATION
  generateObstacles(mapRows, mapColumns, obstaclesNumber, obstaclesCoord); // Generate the Coord of the diferent obstacles
  generateMap(randomMap, mapRows, mapColumns,obstaclesCoord);  // Generates random map with its obstacles
  createRectangle(0,0,5,50, randomMap); // creates a 400x2000 obstacle rectangle  at (1600,0)
  createRectangle(45,0,5,50, randomMap); // creates a 400x2000 obstacle rectangle  at (1600,0)
  randomMap[startNode.coord.first][startNode.coord.second] = 0;
  randomMap[goalNode.coord.first][goalNode.coord.second] = 0;
  printMap(mapRows, mapColumns, randomMap);

  //DStarLite first run
  Node lastNode = startNode;
  initialize(randomMap, knownNodes, uList, startNode, goalNode, uList2);
  goalNode = knownNodes.at(goalNode.coord);

  std::cout << "Start computing" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  computeShortestPath(uList, knownNodes, startNode.coord, goalNode, uList2);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "End computing" << std::endl;
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  startNode = knownNodes.at(startNode.coord); // we update the start node
  goalNode = knownNodes.at(goalNode.coord);
  char command;

  while(startNode.coord != goalNode.coord){

    if(startNode.costG == infinity){
      std::cerr << "NOT KNOWN PATH" << std::endl;
      break;
    }

    startNode = bestNode(startNode, knownNodes, goalNode); // we "move" the robot
    findPath(randomMap,knownNodes,startNode,goalNode); // we see the best path

    //Position printing
    //        int tmpo = randomMap[startNode.coord.first][startNode.coord.second];
    //        randomMap[startNode.coord.first][startNode.coord.second] = 3;
    //        printMap(mapRows, mapColumns, randomMap);
    //        randomMap[startNode.coord.first][startNode.coord.second] = tmpo;

    std::cout << "Enter c to continue or m to modify the map" << std::endl;
    std::cin >> command;
    switch(command){

    case 'c':
      break;
    case 'm':
      // Map random modification
      clearMap(randomMap, obstaclesCoord);
      generateObstacles(mapRows, mapColumns, obstaclesNumber, obstaclesCoord); // Generate the Coord of the diferent obstacles
      generateMap(randomMap, mapRows, mapColumns,obstaclesCoord);  // Generates random map with its obstacles
      randomMap[startNode.coord.first][startNode.coord.second] = 0;
      randomMap[goalNode.coord.first][goalNode.coord.second] = 0;

      //Print new map
      std::cout << std::endl<< "----NEW MAP-----" << std::endl;
      printMap(mapRows, mapColumns, randomMap);

      km = km + distance2(lastNode, startNode);
      lastNode = startNode;
      updateMap(knownNodes, randomMap, uList, startNode.coord, goalNode, uList2); // we update all the changed nodes

      //printNodesAndKeys(knownNodes);
      std::cout << "Start computing" << std::endl;
      start = std::chrono::high_resolution_clock::now();
      computeShortestPath(uList, knownNodes, startNode.coord, goalNode, uList2);
      stop = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      std::cout << "End computing" << std::endl;
      std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
      //printNodesAndKeys(knownNodes);
      startNode = knownNodes.at(startNode.coord); // we update the start node
      goalNode = knownNodes.at(goalNode.coord);
      break;

    case 'd':

      createRectangle(15,15,25,25, randomMap);
      std::cout << std::endl<< "----NEW MAP-----infinity" << std::endl;
      printMap(mapRows, mapColumns, randomMap);

      lastNode = startNode;
      km = km + distance2(lastNode, startNode);
      lastNode = startNode;
      updateMap(knownNodes, randomMap, uList, startNode.coord, goalNode, uList2); // we update all the changed nodes

      //fastInitialize(knownNodes, uList,startNode,goalNode);
      //updateMap(knownNodes, randomMap, uList, startNode.coord, goalNode); // we update all the changed nodes

      std::cout << "Start computing" << std::endl;
      start = std::chrono::high_resolution_clock::now();
      computeShortestPath(uList, knownNodes, startNode.coord, goalNode, uList2);
      stop = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      std::cout << "End computing" << std::endl;
      std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

      startNode = knownNodes.at(startNode.coord); // we update the start node
      //printNodesAndKeys(knownNodes);
      break;
    }

  }

  //Print the path
  //findPath(randomMap,knownNodes,startNode,goalNode);
  //printMap(mapRows, mapColumns, randomMap);
  return 0;
}

