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
            level[1][j].top = false;
            level[n-2][j].bottom = false;
            level[i][1].left = false;
            level[i][n-2].right = false;
        }
    }
}

void showMaze(Cell level[n][n])
{
    system("CLS");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << " " << level[i][j].character;
        }
        cout << endl;
    }
}

vector<int> checkNeighbours(Cell level[n][n], stack<pair<int, int>> &backtrackStack)
{
    vector<int> neighbours;
    if((backtrackStack.top().second > 1) && 
        (level[(backtrackStack.top().second - 2)][(backtrackStack.top().first)].visited == false &&     //If target cell is not visited
        (level[(backtrackStack.top().second)][(backtrackStack.top().first)].top == true &&              //Doble check:
         level[(backtrackStack.top().second - 2)][(backtrackStack.top().first)].bottom == true)))       //If next cell is not blocked
    {
        neighbours.push_back(0);
    }

    if((backtrackStack.top().first < n - 2) && 
        (level[(backtrackStack.top().second)][(backtrackStack.top().first + 2)].visited == false &&
        (level[(backtrackStack.top().second)][(backtrackStack.top().first)].right == true && 
         level[(backtrackStack.top().second)][(backtrackStack.top().first + 2)].left == true)))
    {
        neighbours.push_back(1);
    }

    if((backtrackStack.top().second < n - 2) && 
        (level[(backtrackStack.top().second + 2)][(backtrackStack.top().first)].visited == false &&
        (level[(backtrackStack.top().second)][(backtrackStack.top().first)].bottom == true && 
         level[(backtrackStack.top().second + 2)][(backtrackStack.top().first)].top == true)))
    {
        neighbours.push_back(2);
    }

    if((backtrackStack.top().first > 1) && 
        (level[(backtrackStack.top().second)][(backtrackStack.top().first - 2)].visited == false &&
        (level[(backtrackStack.top().second)][(backtrackStack.top().first)].left == true && 
         level[(backtrackStack.top().second)][(backtrackStack.top().first + 2)].right == true)))
    {
        neighbours.push_back(3);
    }
    
    return neighbours;
}

void moveCell(Cell level[n][n], stack<pair<int, int>> &backtrackStack, int x, int y, int direction)
{
    //Add offsets using X and Y
    level[(backtrackStack.top().second + x)][(backtrackStack.top().first + y)].character = ' ';
    level[(backtrackStack.top().second + x)][(backtrackStack.top().first + y)].visited = true;

    //Move 2 cells
    level[(backtrackStack.top().second + (x*2))][(backtrackStack.top().first + (y*2))].visited = true;
    level[(backtrackStack.top().second + (x*2))][(backtrackStack.top().first + (y*2))].character = ' ';

    //Mark cells so I cant walk in there again
    switch (direction)
    {
        case 0: //North
            level[(backtrackStack.top().second)][(backtrackStack.top().first)].top = false;
            level[(backtrackStack.top().second + (x*2))][(backtrackStack.top().first)].bottom = false;
            break;
        case 1: //East
            level[(backtrackStack.top().second)][(backtrackStack.top().first)].right = false;
            level[(backtrackStack.top().second)][(backtrackStack.top().first + (y*2))].left = false;
            break;
        case 2: //South
            level[(backtrackStack.top().second)][(backtrackStack.top().first)].bottom = false;
            level[(backtrackStack.top().second + (x*2))][(backtrackStack.top().first)].top = false;
            break;
        case 3: //West
            level[(backtrackStack.top().second)][(backtrackStack.top().first)].left = false;
            level[(backtrackStack.top().second)][(backtrackStack.top().first + (y*2))].right = false;
            break;
    }

    backtrackStack.push(make_pair((backtrackStack.top().first + (y*2)), (backtrackStack.top().second + (x*2))));
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
                    moveCell(level, backtrackStack, -1, 0, nextDir);
                    break;
                case 1: //East
                    moveCell(level, backtrackStack, 0, 1, nextDir);
                    break;
                case 2: //South
                    moveCell(level, backtrackStack, 1, 0, nextDir);
                    break;
                case 3: //West
                    moveCell(level, backtrackStack, 0, -1, nextDir);
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
        //showMaze(level);
    }        
    //Exit point (A)
    level[(maxLengthStack.top().second)][(maxLengthStack.top().first)].character = 'B';
            
    //Show result
    showMaze(level);
}