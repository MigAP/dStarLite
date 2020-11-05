#include "mapGeneration.h"

void generateObstacles(int mapRows, int mapColumns, int obstaclesNumber, std::vector<std::pair<int,int>>& obstaclesCoord){

	std::pair<int, int> firstObstacle {rand() % mapRows ,rand() % mapColumns }; // generate first random Obstacle coord

	obstaclesCoord.push_back(firstObstacle);

	std::pair<int,int> obstacle;

	for(int i = 1; i<obstaclesNumber; i++){
		obstacle  = {rand() % mapRows ,rand() % mapColumns }; // generate random Obstacle coord

		while(std::find(obstaclesCoord.begin(), obstaclesCoord.end(), obstacle) != obstaclesCoord.end() ){ // make sure the obstacles are in diferent positions
			obstacle  = {rand() % mapRows ,rand() % mapColumns }; // generate random Obstacle coord
		}

		obstaclesCoord.push_back(obstacle);
	}
}

void generateMap(std::vector<std::vector<int>>& randomMap, int mapRows, int mapColumns, std::vector<std::pair<int,int>>& obstaclesCoord) {

	randomMap.resize(mapRows);

	for(int i =0; i<mapColumns; i++){
		randomMap[i].resize(mapColumns);
	}

	int x,y;

	for(int i = 0; i<obstaclesCoord.size(); i++){
		x = obstaclesCoord[i].first;
		y = obstaclesCoord[i].second;

		randomMap[x][y] = 1;
	}
}

void printMap(int mapRows, int mapColumns, std::vector<std::vector<int>>& randomMap) {

	std::cout << "PRINTING RANDOM MAP" << std::endl;
	for(int i = 0; i< mapRows; i++){

		for (int j= 0; j<mapColumns; j++){
			std::cout << randomMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void clearMap(std::vector<std::vector<int>>& randomMap, std::vector<std::pair<int,int>>& obstaclesCoord){

    for(int i = 0 ; i< randomMap.size(); i++){

        for(int j = 0; j< randomMap[0].size(); j++){
            randomMap[i][j] = 0;
        }
    }
    obstaclesCoord.clear();
}

/*
Creates an obstacle rectangle at (startX, startY)
*/
void createRectangle(uint startX, uint startY, int width, int length, std::vector<std::vector<int>>& mapVector){

	if( ( (startX + width) >  mapVector.size()  ) || ( (startY + length)  > mapVector[0].size() ) )
	{
		std::cerr << "Rectangle creation fail : Too big of rectangle :( " << std::endl;
		std::cerr << "X : " << startX << " Y " << startY << " W " << width << " L " << length << std::endl;
		return;
	}

	for(int i = 0; i<width; i++)
	{
		for(int j = 0; j<length; j++)
		{
			mapVector[startX +i][startY+j] = 1;
		}
	}
}
