#include <iostream>

using namespace std;

int main()
{
    int posibilities = 10;
    for (int i = 0; i < posibilities; ++i)
    {
        int c = i;
        for(int j = 0; j < 9; ++j)
        {
            cout << (c%3) << " ";
            c /= 3;
        }
        cout << endl;
    }
    

    cin.get();
    return 0;
}