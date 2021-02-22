#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//Struct used for comparison (numbers order by reference)
struct {
    bool operator()(char a, char b) const { 
        string numbers = {"23456789TJQKA"};
        int found = numbers.find(a);
        return numbers.find(a) < numbers.find(b); }
} comparator;

class Hand 
{ 
public: 
    string hand; 
    string handSorted;
    string handClass;
    int handForce = 0;
    string cardsInGame;
    string cardsOutGame;
    string higherCardInGame = "";
    string higherCardOutGame = "";

    void Initialize(string hnd)
    {
        hand = hnd;

        //Sort hand
        handSorted = {hnd[0], hnd[3], hnd[6], hnd[9], hnd[12]};
        sort(handSorted.begin(), handSorted.end(), comparator);

        //Check class
        handClass = checkHand();

        //Check force
        handForce = getIndex();

        //Check cards out game
        checkOutGame();

        //Higher card out game
        higherCardOutGame = cardsOutGame.back();
    }

    int getIndex()
    {
        vector<string> hands = {"HIGH CARD", "ONE PAIR", "TWO PAIRS", "THREE OF A KIND", "STRAIGHT", "FLUSH", "FULL HOUSE", "FOUR OF A KIND", "STRAIGHT FLUSH", "ROYAL FLUSH"};

        auto it = find(hands.begin(), hands.end(), handClass);

        if (it != hands.end()) 
        {
            int index = it - hands.begin();
            return index;
        }
        else 
        {
            return -1;
        }
    }

    bool checkFlush()
    {
        //If all had same type
        int n = count(hand.begin(), hand.end(), hand[1]);
        if(n == 5) 
        {
            cardsInGame = handSorted;
            higherCardInGame = cardsInGame.back();
            return true;
        }

        return false;
    }

    bool checkStraight()
    {
        string numbers = {"23456789TJQKA"};
        //If is substring
        size_t found = numbers.find(handSorted);
        if (found != string::npos)
        {
            cardsInGame = handSorted;
            higherCardInGame = cardsInGame.back();
            return true;
        }

        return false;
    }

    string checkHand()
    {
        bool hasFlush = false;
        bool hasStraight = false;

        hasFlush = checkFlush();
        hasStraight = checkStraight();


        if(hasStraight && hasFlush)
        {
            if(handSorted == "TJQKA") return "ROYAL FLUSH";
            else return "STRAIGHT FLUSH";
        }
        else if(hasFlush) return "FLUSH";
        else if(hasStraight) return "STRAIGHT";


        int sameNumber = 0;
        sameNumber = checkSameNumber();

        if(sameNumber == 5) return "FULL HOUSE";
        if(sameNumber == 4) return "FOUR OF A KIND";
        if(sameNumber == 3) return "THREE OF A KIND";
        if(sameNumber == 2) return "TWO PAIRS";
        if(sameNumber == 1) return "ONE PAIR";

        return "HIGH CARD";
    }

    int checkSameNumber()
    {
        bool hasPair = false;
        bool hasThree = false;

        int opt = 0;
        char cardInPair = 'a';
        
        for (int i = 0; i < handSorted.length(); i++)
        {
            int quantity = count(handSorted.begin(), handSorted.end(), handSorted[i]);

            if(quantity == 2 && opt != 2) 
            {
                opt = 1;
                cardsInGame += handSorted[i];

                if(higherCardInGame == "")
                    higherCardInGame = cardsInGame.back();

                if(cardInPair != handSorted[i] && hasPair)
                {
                    opt = 2;
                    cardsInGame += handSorted[i];
                    higherCardInGame = cardsInGame.back();
                }

                cardInPair = handSorted[i];
                hasPair = true;
            }
            
            if(quantity == 3) 
            {
                hasThree = true;
                opt = 3;
                cardsInGame += handSorted[i];
                higherCardInGame = handSorted[i];
            }
            
            if(quantity == 4) 
            {
                opt = 4;
                cardsInGame += handSorted[i];
                higherCardInGame = handSorted[i];
            }
        }    

        if(hasPair && hasThree)
        {
            opt = 5;
        }

        return opt;
    }

    void checkOutGame()
    {
        for (int i = 0; i < handSorted.length(); i++)
        {
            if(!(cardsInGame.find(handSorted[i]) != string::npos))
            {
                cardsOutGame += handSorted[i];
            }
        }
    }

    void showAll()
    {
        showHand();
        showHandClass();
        showForce();
        showCardsInGame();
        showHigherInGame();
        showCardsOutGame();
        showHigherOutGame();
    }
  
    void showHand() 
    { 
       cout << "Hand is: " << hand << endl; 
    } 

    void showHandClass() 
    { 
       cout << "HandClass is: " << handClass << endl; 
    } 

    void showForce() 
    { 
       cout << "Force is: " << handForce << endl; 
    } 

    void showCardsInGame() 
    { 
       cout << "cardsInGame is: " << cardsInGame << endl; 
    } 

    void showHigherInGame() 
    { 
       cout << "higherCardInGame is: " << higherCardInGame << endl; 
    } 

    void showCardsOutGame() 
    { 
       cout << "cardsOutGame is: " << cardsOutGame << endl; 
    } 

    void showHigherOutGame() 
    { 
       cout << "higherCardOutGame is: " << higherCardOutGame << endl; 
    } 
};  

int checkWinner(Hand pj1Hand, Hand pj2Hand);
int checkHigherCard(Hand pj1Hand, Hand pj2Hand);

int main()
{
    ifstream file("Poker.txt");
    string input; 

    int pj1WinCount = 0;
    int pj2WinCount = 0;

    while (getline(file, input))
    {
        string pj1Cards = input.substr (0, 14);
        string pj2Cards = input.substr (15, 28);

        Hand pj1Hand;
        pj1Hand.Initialize(pj1Cards);
        //pj1Hand.showAll();

        Hand pj2Hand;
        pj2Hand.Initialize(pj2Cards);
        //pj2Hand.showAll();

        int winner = 0;
        winner = checkWinner(pj1Hand, pj2Hand);

        if(winner == 1)
        {
            pj1WinCount++;
        }
        else if(winner == 2)
        {
            pj2WinCount++;
        }
    }

    cout << "pj1WinCount: " << pj1WinCount << endl;
    cout << "pj2WinCount: " << pj2WinCount << endl;

    return 0;
}

int checkWinner(Hand pj1Hand, Hand pj2Hand)
{
    int winner = 0;

    if(pj1Hand.handForce > pj2Hand.handForce)
    {
        winner = 1;
    }
    else if(pj1Hand.handForce < pj2Hand.handForce)
    {
        winner = 2;
    }
    else //Draw
    {
        winner = checkHigherCard(pj1Hand, pj2Hand);
    }

    return winner;
}

int checkHigherCard(Hand pj1Hand, Hand pj2Hand)
{
    string numbers = {"23456789TJQKA"};

    //Weight is based in position in numbers reference
    auto pj1WeightCard = numbers.find(pj1Hand.higherCardInGame);
    auto pj2WeightCard = numbers.find(pj2Hand.higherCardInGame);

    if(pj1WeightCard > pj2WeightCard)
    {
        return 1;
    }
    else if(pj1WeightCard < pj2WeightCard)
    {
        return 2;
    }
    else
    {
        for (int i = pj1Hand.handSorted.length(); i > 0; i--)
        {
            auto pj1WeightCard = numbers.find(pj1Hand.handSorted[i]);
            auto pj2WeightCard = numbers.find(pj2Hand.handSorted[i]);

            if(pj1WeightCard > pj2WeightCard)
            {
                return 1;
            }
            else if (pj1WeightCard < pj2WeightCard)
            {
                return 2;
            }
        }
    }

    return 0;
}