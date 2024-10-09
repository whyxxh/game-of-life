#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 100
#define HEIGHT 100
#define DEAD_CELL '.'
#define ALIVE_CELL '#'

int aliveCountGlobal = 0;

typedef enum
{
  DEAD,
  ALIVE,
} State;

typedef struct
{
  State state;
} Cell;

Cell grid[HEIGHT][WIDTH] = {0};

void initGrid()
{
  
  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < WIDTH; j++)
    {
      float randNumber = (double)rand() / (double)RAND_MAX;
      if (randNumber < 0.5)
      {
        grid[i][j].state = DEAD;
      }
      else if (randNumber >=0.5)
      {
        grid[i][j].state = ALIVE;
        aliveCountGlobal++;
      }
    }
  }
}

void printGrid()
{
  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < WIDTH; j++)
    {
      if (grid[i][j].state == ALIVE)
      {
        printf(" %c", ALIVE_CELL);
      }
      else
      {
        printf(" %c", DEAD_CELL);
      }
    }
    printf("\n");
  }
}

int countLiveNeighbors(int x, int y)
{
  int liveCount = 0;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if (i == 0 && j == 0)
        continue;
      int newX = x + i;
      int newY = y + j;
      if (newX >= 0 && newX < HEIGHT && newY >= 0 && newY < WIDTH)
      {
        if (grid[newX][newY].state == ALIVE)
        {
          liveCount++;
        }
      }
    }
  }
  return liveCount;
}

void updateGrid()
{
  Cell newGrid[HEIGHT][WIDTH] = {0};
  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < HEIGHT; j++)
    {
      int liveNeighbors = countLiveNeighbors(i, j);
      if (grid[i][j].state == ALIVE)
      {
        if (liveNeighbors < 2 || liveNeighbors > 3)
        {
          newGrid[i][j].state = DEAD;
          aliveCountGlobal -= 1;
        }
        else
        {
          newGrid[i][j].state = ALIVE;
        }
      }
      else
      {
        if (liveNeighbors == 3)
        {
          newGrid[i][j].state = ALIVE;
          aliveCountGlobal += 1;
        }
        else
        {
          newGrid[i][j].state = DEAD;
        }
      }
    }
  }
  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < WIDTH; j++)
    {
      grid[i][j] = newGrid[i][j];
    }
  }
}

int main()
{
  srand(time(NULL));
  initGrid();
  while (aliveCountGlobal != 0)
  {
    usleep(0.1 * 1000000);
    system("clear");
    updateGrid();
    printGrid();
  }
  return 0;
}
