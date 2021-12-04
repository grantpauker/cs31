#include "grid.h"
#include <cassert>
#include <cctype>
#include <iostream>
#include <regex>
#include <string>

bool isCardinal(int dir);
bool isRowValid(int row);
bool isColValid(int col);
bool isValidPosition(int row, int col);
bool isWallOrBorder(int row, int col);
bool hasCorrectForm(std::string plan);
int travelSafeDistance(int &r, int &c, char dir, int maxSteps);
int determineSafeDistance(int r, int c, char dir, int maxSteps);
int obeyPlan(int sr, int sc, int er, int ec, char dir, std::string plan, int &nsteps);

// array of cardinal directions
const char CARDINALS[4] = {'n', 'e', 's', 'w'};

int main()
{
	int len;

	// hasCorrectForm tests
	assert(hasCorrectForm(""));				   // valid
	assert(hasCorrectForm("Rll04R00LrrL10l")); // valid
	assert(hasCorrectForm("R"));			   // valid
	assert(!hasCorrectForm("r5j5l"));		   // invalid
	assert(!hasCorrectForm("7"));			   // invalid
	assert(!hasCorrectForm("R1"));			   // invalid

	// grid 0 plans
	std::string plan0_grid0 =
		"RR2L2L2R5R6R1L2L3R1R";				  // succeeds with length of 24
	std::string plan1_grid0 = "RR3L4R5L5R1R"; // succeeds with length of 18
	std::string plan2_grid0 = "RR9L7L1R2R1R"; // succeeds with length of 20
	setWall(1,2);
	setWall(2,2);
	setWall(5,2);
	setWall(5,3);
	setWall(2,4);
	setWall(3,7);
	setWall(3,8);

	// grid 0 setup
	setSize(10, 10);
	setWall(1, 2);
	setWall(2, 2);
	setWall(5, 2);
	setWall(5, 3);
	setWall(2, 4);
	setWall(3, 4);
	setWall(5, 4);
	setWall(7, 4);
	setWall(8, 4);
	setWall(9, 4);
	setWall(3, 5);
	setWall(3, 6);
	setWall(3, 7);
	setWall(4, 7);
	setWall(5, 7);
	setWall(8, 8);
	setWall(8, 9);
	setWall(8, 10);
	setWall(10, 9);
	draw(1, 1, 10, 10);

	// determineSafeDistance tests
	assert(determineSafeDistance(7, 6, 'N', 10) == 3); // hits wall
	assert(determineSafeDistance(7, 6, 'N', 2) == 2);  // doesnt hit wall
	assert(determineSafeDistance(7, 6, 'W', 5) == 1);  // hits wall
	assert(determineSafeDistance(7, 6, 'E', 8) == 4);  // hits edge

	// obeyPlan invalid parameter tests
	assert(obeyPlan(1, 1, 1, 1, 'N', "J7", len) == 2); // invalid plan
	assert(obeyPlan(0, 1, 1, 1, 'N', "5R", len) == 2); // invalid start coord
	assert(obeyPlan(1, 1, 0, 1, 'N', "5R", len) == 2); // invalid end coord
	assert(obeyPlan(1, 1, 1, 1, 'j', "5R", len) == 2); // invalid direction

	// obeyPlan tests for grid0
	assert(obeyPlan(1, 1, 10, 10, 'N', plan0_grid0, len) == 0 && len == 24);
	assert(obeyPlan(1, 1, 10, 10, 'N', plan1_grid0, len) == 0 && len == 18);
	assert(obeyPlan(1, 1, 10, 10, 'N', plan2_grid0, len) == 0 && len == 20);

	// grid 1 plans
	std::string plan0_grid1 =
		"L1R2R4L3L5L3R1L4L4L3R4R2R1R";				 // succeeds with length of 37
	std::string plan1_grid1 = "LL3L4L2L";			 // succeeds with length of 9
	std::string plan2_grid1 = "L1R3R1R1L6L2L4R2L1L"; // crashes with length of 15
	std::string plan3_grid1 = "LL3R7L";				 // crashes with length of 6
	std::string plan4_grid1 = "R1L1R3L3L";			 // crashes with length of 7
	std::string plan5_grid1 = "L2L";				 // crashes with length of 1
	std::string plan6_grid1 =
		"R1L2L4L2L"; // stops before reaching end coords with length of 9
	std::string plan7_grid1 =
		"L1R3L1R2R3L"; // stops before reaching end coords with length of 10
	std::string plan8_grid1 =
		"RR3L4L1L"; // stops before reaching end coords with length of 8

	// grid 1 setup
	setSize(10, 10);
	setWall(1, 7);
	setWall(1, 8);
	setWall(1, 9);
	setWall(2, 3);
	setWall(2, 4);
	setWall(2, 5);
	setWall(3, 8);
	setWall(4, 5);
	setWall(4, 8);
	setWall(5, 7);
	setWall(6, 2);
	setWall(6, 3);
	setWall(6, 4);
	setWall(6, 7);
	setWall(7, 3);
	setWall(8, 4);
	setWall(8, 8);
	setWall(9, 2);
	setWall(10, 5);
	draw(4, 4, 8, 3);

	// obeyPlan tests for grid1
	assert(obeyPlan(4, 4, 8, 3, 'E', plan0_grid1, len) == 0 && len == 37);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan1_grid1, len) == 0 && len == 9);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan2_grid1, len) == 3 && len == 15);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan3_grid1, len) == 3 && len == 6);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan4_grid1, len) == 3 && len == 7);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan5_grid1, len) == 3 && len == 1);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan6_grid1, len) == 1 && len == 9);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan7_grid1, len) == 1 && len == 10);
	assert(obeyPlan(4, 4, 8, 3, 'E', plan8_grid1, len) == 1 && len == 8);

	return 0;
}

// macro for checking if character is cardinal direction (NESW)
bool isCardinal(int dir)
{
	return tolower(dir) == 'n' || tolower(dir) == 'e' || tolower(dir) == 's' || tolower(dir) == 'w';
}

// check if row/col are within bounds
bool isRowValid(int row)
{
	return 0 < row && row <= getRows();
}
bool isColValid(int col)
{
	return 0 < col && col <= getCols();
}

// check if row and col are within bounds and (row, col) is not a wall
bool isValidPosition(int row, int col)
{
	return isRowValid(row) && isColValid(col) && !isWall(row, col);
}

// checks if a given coordinate is either a wall or directly outside the
// boundaries of the grid
bool isWallOrBorder(int row, int col)
{
	return !isRowValid(row) || !isColValid(col) || isWall(row, col);
}

// check if a plan is in the correct form
bool hasCorrectForm(std::string plan)
{
	// defines a regular expression matching the group of 0-2 digits followed by
	// an l/r repeated any number of times
	std::regex valid_plan = std::regex("([0-9]{0,2}[lLrR])*");
	// checks if plan matches regex
	return std::regex_match(plan, valid_plan);
}

// implements determine safe distance as the spec specifies but passes r and c
// by reference for use in obeyPlan
int travelSafeDistance(int &r, int &c, char dir, int maxSteps)
{
	// ensures given parameters are valid
	if (!isValidPosition(r, c) || maxSteps < 0)
	{
		return -1;
	}
	int step_count = 0;
	int temp_r = r;
	int temp_c = c;
	// loop until we hit a wall or run outside bounds or reach the max number of
	// steps
	while (!isWallOrBorder(r, c) && step_count < maxSteps)
	{
		temp_r = r;
		temp_c = c;
		// increase row/col count based on direction
		if (tolower(dir) == 's')
		{
			r++;
		}
		else if (tolower(dir) == 'n')
		{
			r--;
		}
		else if (tolower(dir) == 'e')
		{
			c++;
		}
		else if (tolower(dir) == 'w')
		{
			c--;
		}
		step_count++;
	}
	// if we ran into a wall/outside bounds undo the last step by setting r and c
	// to what they were before and decreasing step count by 1
	if (isWallOrBorder(r, c))
	{
		r = temp_r;
		c = temp_c;
		step_count--;
	}

	return step_count;
}

// calls travel safe distance without changing r/c
int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	return travelSafeDistance(r, c, dir, maxSteps);
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, std::string plan,
			 int &nsteps)
{
	int row = sr;
	int col = sc;
	// check if supplied parameters are valid
	if (!isValidPosition(sr, sc) || !isValidPosition(er, ec) ||
		!isCardinal(dir) || !hasCorrectForm(plan))
	{
		return 2;
	}
	nsteps = 0;
	// finds in the index of the initial direction in the CARDINALS array. by
	// storing the direction this way, it makes the cyclic nature of turning much
	// easier to implement
	int cur_dir = 0;
	for (int i = 0; i < 4; i++)
	{
		if (tolower(dir) == CARDINALS[i])
		{
			cur_dir = i;
			break;
		}
	}
	int steps_portion = 0;
	// loop over a valid plan and increase row/col and nsteps while doing so
	for (int i = 0; i < plan.length(); i++)
	{
		if (tolower(plan[i]) == 'l')
		{
			// turn left by decreasing the direction index by 1. also does some fancy
			// modulo math to cycle it back to 3 if it goes below 0
			cur_dir--;
			cur_dir = (cur_dir % 4 + 4) % 4;
		}
		else if (tolower(plan[i]) == 'r')
		{
			// turn right by increasing the direction index by 1. also does some fancy
			// modulo math to cycle it back to 0 if it goes above 3
			cur_dir++;
			cur_dir %= 4;
		}
		else if (isdigit(plan[i]))
		{
			// get the current steps we want to travel
			steps_portion = plan[i] - '0';
			if (isdigit(plan[i + 1]))
			{
				// if the next character is a digit, compute the 2 digit number's value
				// and increase the index by 1
				steps_portion *= 10;
				steps_portion += plan[i + 1] - '0';
				i++;
			}
			// get the distance traveled
			int traveled =
				travelSafeDistance(row, col, CARDINALS[cur_dir], steps_portion);
			nsteps += traveled;
			// if traveled does not equal steps_portion, we either ran out of bounds
			// or hit a wall so return 3
			if (traveled != steps_portion)
			{
				return 3;
			}
		}
	}
	// if we are at the end coords, return 0, else 1
	return (row == er && col == ec) ? 0 : 1;
}
