#include <iostream>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

#define n 11

struct Cell
{
    bool visited = false;
    bool top = true;
    bool bottom = true;
    bool left = true;
    bool right = true;
    char character = '*';
};

bool checkN();
void showMaze(Cell *level);
void initialize(Cell *level);
vector<int> checkNeighbours(Cell *level, stack<pair<int, int>> &backtrackStack);
void moveCell(Cell *level, stack<pair<int, int>> &backtrackStack, int x, int y, int direction);
void createMaze2D();
 
int main() 
{
    if(!checkN())
    {
        cout << "Error: 'n' invalid!" << endl;
    }
    else
    {
        createMaze2D();
    }
    
    return 0;
}

bool checkN()
{
    return ((n % 2 != 0) && (n > 3));
}

void initialize(Cell level[n][n])
{
    //Block border cells
    for(int i=1; i<n-1; i++) 
    {
        for(int j=1; j<n-1; j++) {
            level[1][j].left = false;
            level[n-2][j].right = false;
            level[i][1].top = false;
            level[i][n-2].bottom = false;
        }
    }
}

void showMaze(Cell level[n][n])
{
    system("CLS");

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            cout << " " << level[x][y].character;
        }
        cout << endl;
    }
}

vector<int> checkNeighbours(Cell level[n][n], stack<pair<int, int>> &backtrackStack)
{
    vector<int> neighbours;

    int axisX = backtrackStack.top().first;
    int axisY = backtrackStack.top().second;

    //North
    if((axisY > 1) && 
        (level[axisX][(axisY - 2)].visited == false &&      //If target cell is not visited
        (level[axisX][axisY].top == true &&                 //Doble check:
         level[axisX][(axisY - 2)].bottom == true)))        //If next cell is not blocked
    {
        neighbours.push_back(0);
    }

    if((axisX < n - 2) && 
        (level[(axisX + 2)][axisY].visited == false &&
        (level[axisX][axisY].right == true && 
         level[(axisX + 2)][axisY].left == true)))
    {
        neighbours.push_back(1);
    }

    if((axisY < n - 2) && 
        (level[axisX][(axisY + 2)].visited == false &&
        (level[axisX][axisY].bottom == true && 
         level[axisX][(axisY + 2)].top == true)))
    {
        neighbours.push_back(2);
    }

    if((axisX > 1) && 
        (level[(axisX - 2)][axisY].visited == false &&
        (level[axisX][axisY].left == true && 
         level[(axisX - 2)][axisY].right == true)))
    {
        neighbours.push_back(3);
    }
    
    return neighbours;
}

void moveCell(Cell level[n][n], stack<pair<int, int>> &backtrackStack, int x, int y, int direction)
{
    int axisX = backtrackStack.top().first;
    int axisY = backtrackStack.top().second;

    //Add offsets using X and Y
    level[(axisX + x)][(axisY + y)].character = ' ';
    level[(axisX + x)][(axisY + y)].visited = true;

    //Move 2 cells
    level[(axisX + (x*2))][(axisY + (y*2))].visited = true;
    level[(axisX + (x*2))][(axisY + (y*2))].character = ' ';

    //Mark cells so I cant walk in there again
    switch (direction)
    {
        case 0: //North
            level[axisX][axisY].top = false;
            level[axisX][axisY + (y*2)].bottom = false;
            break;
        case 1: //East
            level[axisX][axisY].right = false;
            level[axisX + (x*2)][axisY].left = false;
            break;
        case 2: //South
            level[axisX][axisY].bottom = false;
            level[axisX][axisY + (y*2)].top = false;
            break;
        case 3: //West
            level[axisX][axisY].left = false;
            level[axisX + (x*2)][axisY].right = false;
            break;
    }
    backtrackStack.push(make_pair((axisX + (x*2)), (axisY + (y*2))));
}

void createMaze2D()
{
    srand(time(NULL));
    Cell level[n][n];
    int visitedCells = 0;

    stack<pair<int, int>> maxLengthStack;
    stack<pair<int, int>> backtrackStack;

    //Entry point (A)
    backtrackStack.push(make_pair(1,1));
    level[1][1].visited = true;
    level[1][1].character = 'A';
    visitedCells++;

    initialize(level);

    int totalCells = ((n-1)/2)*((n-1)/2);
    while(visitedCells < totalCells)
    {
        vector<int> neighbours;
        neighbours = checkNeighbours(level, backtrackStack);

        if(!neighbours.empty())
        {
            //Random pick neigbour
            int nextDir = neighbours[rand() % neighbours.size()];

            switch (nextDir)
            {
                case 0: //North
                    moveCell(level, backtrackStack, 0, -1, nextDir);
                    break;
                case 1: //East
                    moveCell(level, backtrackStack, 1, 0, nextDir);
                    break;
                case 2: //South
                    moveCell(level, backtrackStack, 0, 1, nextDir);
                    break;
                case 3: //West
                    moveCell(level, backtrackStack, -1, 0, nextDir);
                    break;
            }
            visitedCells++;
        }
        else
        {
            backtrackStack.pop();
        }

        //Backup longest path
        if(backtrackStack.size() > maxLengthStack.size())
        {
            maxLengthStack = backtrackStack;
        }

        //Show step by step
        showMaze(level);
    }        
    //Exit point (A)
    level[(maxLengthStack.top().first)][(maxLengthStack.top().second)].character = 'B';
            
    //Show result
    showMaze(level);
}