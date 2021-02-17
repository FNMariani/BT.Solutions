#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void loadTextures(map<std::string, sf::Texture> &_textures);
void drawChessBoard(string initPosition, sf::RenderWindow &_window, map<std::string, sf::Texture> &_textures);

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess");

    string initPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    //string initPosition = "4p3";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        map<std::string, sf::Texture> textures;
        vector<sf::Sprite> sprites;

        loadTextures(textures);

        window.clear();

        drawChessBoard(initPosition, window, textures);

        window.display();
    }

    return 0;
}

void loadTextures(map<std::string, sf::Texture> &_textures)
{
    sf::Texture tex;

    //Black Textures
    tex.loadFromFile("Assets/Sprites/bBishop.png");
    _textures["bBishop"] = tex;

    tex.loadFromFile("Assets/Sprites/bKing.png");
    _textures["bKing"] = tex;

    tex.loadFromFile("Assets/Sprites/bKnight.png");
    _textures["bKnight"] = tex;

    tex.loadFromFile("Assets/Sprites/bPawn.png");
    _textures["bPawn"] = tex;

    tex.loadFromFile("Assets/Sprites/bQueen.png");
    _textures["bQueen"] = tex;

    tex.loadFromFile("Assets/Sprites/bRook.png");
    _textures["bRook"] = tex;

    //White Textures
    tex.loadFromFile("Assets/Sprites/wBishop.png");
    _textures["wBishop"] = tex;

    tex.loadFromFile("Assets/Sprites/wKing.png");
    _textures["wKing"] = tex;

    tex.loadFromFile("Assets/Sprites/wKnight.png");
    _textures["wKnight"] = tex;

    tex.loadFromFile("Assets/Sprites/wPawn.png");
    _textures["wPawn"] = tex;

    tex.loadFromFile("Assets/Sprites/wQueen.png");
    _textures["wQueen"] = tex;

    tex.loadFromFile("Assets/Sprites/wRook.png");
    _textures["wRook"] = tex;
}

void drawChessBoard(string initPosition, sf::RenderWindow& _window, map<std::string, sf::Texture> &_textures)
{
    // Draw background
    sf::Texture backgroundLightTexture;
    backgroundLightTexture.loadFromFile("Assets/Sprites/square_brown_light.png");

    sf::Texture backgroundDarkTexture;
    backgroundDarkTexture.loadFromFile("Assets/Sprites/square_brown_dark.png");

    sf::Sprite backgroundSprites[8][8];
    float xPos = 80.f;
    float yPos = 80.f;

    for (unsigned int i = 0; i < 8; ++i)
    {
        for (unsigned int j = 0; j < 8; ++j)
        {
            // If both are even or if both are odd 
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
            {
                backgroundSprites[i][j].setTexture(backgroundLightTexture);
            }
            else
            {
                backgroundSprites[i][j].setTexture(backgroundDarkTexture);
            }

            backgroundSprites[i][j].setPosition(sf::Vector2f(xPos * j, yPos * i));
        }
    }


    sf::Sprite pieces[8][8];
    int xIndex = 0;
    int yIndex = 0;

    for (unsigned int i = 0; i < initPosition.length(); i++)
    {
        if (isalpha(initPosition[i]))
        {
            if (isupper(initPosition[i]))
            {
                // White pieces
                if (initPosition[i] == 'P')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wPawn"));
                }
                if (initPosition[i] == 'R')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wRook"));
                }
                if (initPosition[i] == 'B')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wBishop"));
                }
                if (initPosition[i] == 'N')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wKnight"));
                }
                if (initPosition[i] == 'Q')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wQueen"));
                }
                if (initPosition[i] == 'K')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("wKing"));
                }
            }
            else
            {
                // Black pieces
                if (initPosition[i] == 'p')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bPawn"));
                }

                if (initPosition[i] == 'r')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bRook"));
                }

                if (initPosition[i] == 'b')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bBishop"));
                }

                if (initPosition[i] == 'n')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bKnight"));
                }

                if (initPosition[i] == 'q')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bQueen"));
                }

                if (initPosition[i] == 'k')
                {
                    pieces[xIndex][yIndex].setTexture(_textures.at("bKing"));
                }
            }

            pieces[xIndex][yIndex].setPosition(sf::Vector2f(xPos * xIndex, yPos * yIndex));
            pieces[xIndex][yIndex].move(10.f, 10.f);
        }

        //Numbers
        if (isdigit(initPosition[i]))
        {
            // Convert to int and
            // -1 to compensate with index of array
            xIndex += (int)(initPosition[i] - '0') - 1;
        }

        xIndex++;

        if (initPosition[i] == '/')
        {
            yIndex++;
            xIndex = 0;
        }
    }

    for (unsigned int i = 0; i < 8; ++i)
    {
        for (unsigned int j = 0; j < 8; ++j)
        {
            _window.draw(backgroundSprites[i][j]);
        }
    }

    for (unsigned int i = 0; i < 8; ++i)
    {
        for (unsigned int j = 0; j < 8; ++j)
        {
            _window.draw(pieces[i][j]);
        }
    }
}