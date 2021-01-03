#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

//global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions();
char askNoYes(string question);
int askNumber(string question, int h, int l = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char>& board, char computer);
void annouceWinner(char winner, char computer, char human);

int main()
{
    int move;
    const int NUM_SQUARE = 9;
    vector<char> board(NUM_SQUARE, EMPTY);

    instructions();

    char human = humanPiece();
    char computer = opponent(human);

    char turn = X;

    displayBoard(board);

    while(winner(board) == NO_ONE) {

        if(turn == human) {
            move = humanMove(board, human);
            board[move] = human;
        }else {
            move = computerMove(board, computer);
            board[move] = computer;
        }

        displayBoard(board);
        turn = opponent(turn);
    }

    annouceWinner(winner(board), computer, human);

    return 0;
}


void instructions() {
    cout << "Welcome to ultimate man-machine: Tic-Tac-Toe" << endl;
    cout << "-where human brain is pit against silicon processor\n" << endl;

    cout << "Make your move by entering a number 0-8. the number" << endl;
    cout << "Corresponds to the desired board position, as illustrated: " << endl << endl;

    cout << "\t 0 | 1 | 2" << endl;
    cout << "\t -- --- --" << endl;
    cout << "\t 3 | 4 | 5" << endl;
    cout << "\t -- --- --" << endl;
    cout << "\t 6 | 7 | 8" << endl;

    cout << endl;

    cout << "Prepare Yourself human, the battle is about to begin" << endl << endl;
}

char askNoYes(string question) {
    char response;

    do {
        cout << question << " (y/n): ";
        cin >> response;
    }while((response != 'y') && (response != 'n'));

    return response;
}

int askNumber(string question, int h, int l) {
    int number;

    do{
        cout << question << " (" << l << " - " << h << "):";
        cin >> number;
    }while(number > h || number < l);

    return number;
}

char humanPiece() {
    char go_first = askNoYes("Do you require first move? ");

    if(go_first == 'y') {
        cout << "\nthen take the first move. you will need it." << endl;
        return X;
    }else {
        cout << "your bravery will be your undoing... I will go first." << endl;
        return O;
    }
}

char opponent(char piece) {

    if(piece == X) {
        return O;
    }else {
        return X;
    }
}

void displayBoard(const vector<char>& board) {

    cout << endl;

    cout << "\t " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "\t -- --- --" << endl;

    cout << "\t " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "\t -- --- --" << endl;

    cout << "\t " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << "\t -- --- --" << endl;

    cout << endl << endl;
}

char winner(const vector<char>& board) {
    const int WINNING_ROWS[8][3] =
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; row++) {
        if(board[WINNING_ROWS[row][0]] != EMPTY
           && board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]
           && board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) {
            return board[WINNING_ROWS[row][0]];
        }
    }

    if(count(board.begin(), board.end(), EMPTY) == 0) {
        return TIE;
    }

    return NO_ONE;
}

inline bool isLegal(const vector<char>& board, int move) {
    return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human) {
    int move = askNumber("where will you move? ", board.size() - 1);

    while(!isLegal(board, move)) {
        cout << "\nthat square is already occupied, foolish human." << endl;
        move = askNumber("where will you move? ", board.size() - 1);
    }

    cout << "fine" << endl;

    return move;
}

int computerMove(vector<char>& board, char computer) {
    cout << "I shall take square number ";

    //check if you going to win and play there
    for(int move = 0; move < board.size(); move++) {
        if(isLegal(board, move)) {
            board[move] = computer;
            if(winner(board) == computer) {
                cout << move << endl;
                return move;
            }
            board[move] = EMPTY;
        }
    }

    //check if the human is going to win and block
    char human = opponent(computer);

    for(int move = 0; move < board.size(); move++) {
        if(isLegal(board, move)) {

            board[move] = human;
            if(winner(board) == human) {
                cout << move << endl;
                return move;
            }

            board[move] = EMPTY;
        }
    }

    const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

    srand(time(0));

    for(int i = 0; i < board.size(); i++){
        int move = BEST_MOVES[rand() % board.size()];
        if(isLegal(board, move)) {
            cout << move << endl;
            return move;
        }
    }
}

void annouceWinner(char winner, char computer, char human) {
    if(winner == computer) {
        cout << winner << "'s won" << endl;
        cout << "As I predicted, human, I am triumphant once more proof" << endl;
        cout << "that computers are superior to humans in all regards" << endl;
    }else if(winner == human) {
        cout << winner << "'s won" << endl;
        cout << "No, no! It cannot be! Somehow you tricked me, human." << endl;
        cout << "But never again! I, the computer, so swear it!" << endl;
    }else {
        cout << "It's a tie!" << endl;
        cout << "You were most lucky, human, and somehow managed to tie me." << endl;
        cout << "Celebrate... for this is the best you will ever achieve." << endl;
    }
}
