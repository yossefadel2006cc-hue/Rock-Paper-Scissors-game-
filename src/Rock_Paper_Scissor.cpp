#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice {Rock = 1 , Paper = 2 , Scissors = 3};

enum enWinner {Player1 =1 , Computer = 2 , Draw =3};

struct stRoundInfo
{
   short RoundNumber = 0;
   enGameChoice Player1Choice;
   enGameChoice ComputerChoice;
   enWinner Winner;
   string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName ="";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice(){   
    return (enGameChoice)RandomNumber(1,3);
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do{
        cout<<"\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors?";
        cin>>Choice;

    }while(Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
        return enWinner::Draw;
    switch(RoundInfo.Player1Choice)
    {
        case enGameChoice::Rock:
            if(RoundInfo.ComputerChoice == enGameChoice::Paper)
            {
                return enWinner::Computer;
            }
            break;
        case enGameChoice::Paper:
            if(RoundInfo.ComputerChoice == enGameChoice::Scissors)
            {
                return enWinner::Computer;
            }
            break;
        case enGameChoice::Scissors:
            if(RoundInfo.ComputerChoice == enGameChoice::Rock)
            {
                return enWinner::Computer;
            }
            break;

    }
    return enWinner::Player1;
}

enWinner WhoWonTheGame(short Player1WinTimes , short ComputerWinTimes)
{
    if(Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes >Player1WinTimes)
        return enWinner::Computer;
    else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = {"Rock", "Paper", "Scissors" };
    return arrGameChoice[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = {"Player1", "Computer", "No Winner(Draw)" };
    return arrWinnerName[Winner - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch(Winner)
    {
        case enWinner::Player1:
            cout<<"\033[42m"; //Green Screen
            break;
        case enWinner::Computer:
            cout << "\033[41m"; //Red Screen
            cout<<"\a";
            break;
        default:
            cout<<"\033[43m"; //Yellow Screen

    }
}

void PrintRoundResults(stRoundInfo stRoundInfo)
{
    cout<<"\n____________Round ["<<stRoundInfo.RoundNumber<<"]____________\n\n";
    cout << "Player Choice: " <<ChoiceName(stRoundInfo.Player1Choice)<< endl;
    cout << "ComputerChoice: " << ChoiceName(stRoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: " << "[" << stRoundInfo.WinnerName << "]" << endl;
    cout << "_________________________________________\n"<<endl;
}

short HowManyRounds()
{
    short Rounds;
    do
    {
        cout << "How Many Rounds 1 to 10 ?" << endl;
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

stGameResults PlayGame(short NumberOfRounds)
{
    stRoundInfo RoundInfo ;
    short Player1WinTimes = 0 , ComputerWinTimes = 0 , DrawTimes = 0;
    for(short GameRound = 1 ; GameRound <= NumberOfRounds ; GameRound++)
    {
        cout<<"\nRound["<<GameRound<<"] begins :\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if(RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else if(RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else DrawTimes++;
        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(NumberOfRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for(int i =1 ; i <= NumberOfTabs ; i++)
         t+= "\t";

    return t;
}

void ShowGameOverScreen()
{
    cout<<Tabs(3)<<"____________________________________________________\n\n";
    cout<<Tabs(3)<<"                ++G A M E  O V E R++\n";
    cout<<Tabs(3)<<"____________________________________________________\n\n";
}

void ShowGameResults(stGameResults GameResults)
{
    cout<<Tabs(3)<<"__________________[ Game Results ]_____________________\n\n";
    cout<<Tabs(3)<<"Game Rounds      : " <<GameResults.GameRounds<<endl;
    cout<<Tabs(3)<<"PlayerWonTimes   : " <<GameResults.PlayerWinTimes<<endl;
    cout<<Tabs(3)<<"ComputerWonTimes : " <<GameResults.ComputerWinTimes<<endl;
    cout<<Tabs(3)<<"Draw Times       : " <<GameResults.DrawTimes<<endl;
    cout<<Tabs(3)<<"Final Winner     : " <<GameResults.WinnerName<<endl;
    cout<<Tabs(3)<<"________________________________________________________\n";
    
    SetWinnerScreenColor(GameResults.GameWinner);
}

// void ResetScreen()
// {
//     system("cls");
// }

void StartGame()
{
    char PlayAgain ='Y';
    do{
        // ResetScreen();
        stGameResults GameResults = PlayGame(HowManyRounds());
        ShowGameOverScreen();
        ShowGameResults(GameResults);
        cout<<endl<<Tabs(3)<<"Do you want to play again? Y/N?";
        cin>>PlayAgain;
    }while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}