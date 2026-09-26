#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enRockPaperScissor
{
    Rock = 1,
    Paper = 2,
    Scissor = 3
};

enum enRoundResult
{
    PlayerWin = 1,
    ComputerWin = 2,
    Draw = 3
};

short HowManyRound()
{
    short Round;
    do
    {
        cout << "How Many Rounds 1 to 10 ?" << endl;
        cin >> Round;
    } while (Round < 1 || Round > 10);
    return Round;
}

int RandomNumber(int From, int To)
{
    int random = rand() % (To - From + 1) + From;
    return random;
}

void PrintRoundResult(int Round, string ComputerChoice, string PlayerChoice, string Winner)
{
    cout << "______________________Round[" << Round << "]______________________\n";
    cout << "Player Choice: " << PlayerChoice << endl;
    cout << "ComputerChoice: " << ComputerChoice << endl;
    cout << "Round Winner: " << "[" << Winner << "]" << endl;
    cout << "____________________________________________\n";
}

string ChoiceName(enRockPaperScissor Choice)
{
    switch (Choice)
    {
    case enRockPaperScissor::Rock:
        return "Rock";
    case enRockPaperScissor::Paper:
        return "Paper";
    case enRockPaperScissor::Scissor:
        return "Scissor";
    default:
        return "";
    }
}

enRockPaperScissor ComputerChoice()
{
    return enRockPaperScissor(RandomNumber(1, 3));
}

enRockPaperScissor PlayerChoice()
{
    int Choice;
    cout << "your Choice: [1]:Rock, [2]Paper, [3]Scissor?";
    cin >> Choice;
    return enRockPaperScissor(Choice);
}

enRoundResult RoundResult(enRockPaperScissor ComputerChoice, enRockPaperScissor PlayerChoice)
{
    if (ComputerChoice == enRockPaperScissor::Paper && PlayerChoice == enRockPaperScissor::Paper)
        return enRoundResult::Draw;
    else if (ComputerChoice == enRockPaperScissor::Paper && PlayerChoice == enRockPaperScissor::Rock)
        return enRoundResult::ComputerWin;
    else if (ComputerChoice == enRockPaperScissor::Paper && PlayerChoice == enRockPaperScissor::Scissor)
        return enRoundResult::PlayerWin;
    else if (ComputerChoice == enRockPaperScissor::Rock && PlayerChoice == enRockPaperScissor::Rock)
        return enRoundResult::Draw;
    else if (ComputerChoice == enRockPaperScissor::Rock && PlayerChoice == enRockPaperScissor::Paper)
        return enRoundResult::PlayerWin;
    else if (ComputerChoice == enRockPaperScissor::Rock && PlayerChoice == enRockPaperScissor::Scissor)
        return enRoundResult::ComputerWin;
    else if (ComputerChoice == enRockPaperScissor::Scissor && PlayerChoice == enRockPaperScissor::Scissor)
        return enRoundResult::Draw;
    else if (ComputerChoice == enRockPaperScissor::Scissor && PlayerChoice == enRockPaperScissor::Paper)
        return enRoundResult::ComputerWin;
    else if (ComputerChoice == enRockPaperScissor::Scissor && PlayerChoice == enRockPaperScissor::Rock)
        return enRoundResult::PlayerWin;
    return enRoundResult::ComputerWin;
}

void StartRound(int Round, int &PlayerWonTimes, int &ComputerWonTimes, int &DrawTimes,
                 enRockPaperScissor UserChoice, enRockPaperScissor CompChoice)
{
    PlayerWonTimes = 0;
    ComputerWonTimes = 0;
    DrawTimes = 0;
    for (int i = 1; i <= Round; i++)
    {
        cout << "Round[" << i << "] begins :\n";
        UserChoice = PlayerChoice();
        CompChoice = ComputerChoice();
        if (RoundResult(CompChoice, UserChoice) == PlayerWin)
        {
            PrintRoundResult(i, ChoiceName(CompChoice), ChoiceName(UserChoice), "Player");
            PlayerWonTimes++;
        }
        else if (RoundResult(CompChoice, UserChoice) == ComputerWin)
        {
            PrintRoundResult(i, ChoiceName(CompChoice), ChoiceName(UserChoice), "Computer");
            ComputerWonTimes++;
        }
        else
        {
            PrintRoundResult(i, ChoiceName(CompChoice), ChoiceName(UserChoice), "No Winner");
            DrawTimes++;
        }
    }
}

string FinalWinner(int PlayerWonTimes, int ComputerWonTimes)
{
    if (PlayerWonTimes > ComputerWonTimes)
        return "Player";
    else if (PlayerWonTimes < ComputerWonTimes)
        return "Computer";
    else
        return "No Winner";
}

void PrintFinalResult(int Round, int DrawTimes, int PlayerWonTimes, int ComputerWonTimes)
{
    cout << "    ___________________________________________\n";
    cout << "       +++ G a m e  O v e r +++\n";
    cout << "    ___________________________________________\n";
    cout << "    __________________ [Game Results] _________\n";
    cout << "    Game Rounds          : " << Round << endl;
    cout << "    Player Won Times     : " << PlayerWonTimes << endl;
    cout << "    Computer Won Times   : " << ComputerWonTimes << endl;
    cout << "    Draw Times           : " << DrawTimes << endl;
    cout << "    Final Winner         : " << FinalWinner(PlayerWonTimes, ComputerWonTimes) << endl;
    cout << "    ___________________________________________\n\n";
    cout << "Do you want to play again?  Y/N?" << endl;
}

void ResetGame()
{
    cout << "\033[2J\033[H";
}

void PlayGame()
{
    int PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
    enRockPaperScissor UserChoice;
    enRockPaperScissor CompChoice;
    char PlayAgain;
    do
    {
        ResetGame();
        int Round = HowManyRound();
        StartRound(Round, PlayerWonTimes, ComputerWonTimes, DrawTimes, UserChoice, CompChoice);
        PrintFinalResult(Round, DrawTimes, PlayerWonTimes, ComputerWonTimes);
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    PlayGame();

    return 0;
}