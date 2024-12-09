#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <map>
#include <fstream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
using namespace std;

template <typename T>
class wordTTT_Board : public Board<T> {
    map<string, string> words;
    fstream file;
public:
    wordTTT_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class wordTTT_Player : public Player<T> {
public:
    wordTTT_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class wordTTT_Random_Player : public RandomPlayer<T> {
public:
    wordTTT_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//----------Implementation-------------

template <typename T>
wordTTT_Board<T>::wordTTT_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    file.open("dic.txt", ios::in);
    string value;
    while (file >> value) {
        words[value] = value;
    }
}

template <typename T>
bool wordTTT_Board<T>::update_board(int x, int y, T Letter) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || Letter == 0)) {
        if (Letter == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(Letter);
        }
        return true;
    }
    return false;
}

template <typename T>
void wordTTT_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool wordTTT_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((words.find(string(1, this->board[i][0]) + this->board[i][1] + this->board[i][2]) != words.end() && this->board[i][0] != 0) ||
            (words.find(string(1, this->board[0][i]) + this->board[1][i] + this->board[2][i]) != words.end() && this->board[0][i] != 0)) {
            return true;
            }
    }

    // Check diagonals
    if ((words.find(string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2]) != words.end() && this->board[0][0] != 0) ||
        (words.find(string(1, this->board[0][2]) + this->board[1][1] + this->board[2][0]) != words.end() && this->board[0][2] != 0)) {
        return true;
        }

    return false;
}

template <typename T>
bool wordTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool wordTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
wordTTT_Player<T>::wordTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void wordTTT_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "Please enter the letter: ";
    T letter;
    cin >> letter;
    this->symbol=letter;
}

template <typename T>
wordTTT_Random_Player<T>::wordTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void wordTTT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol = 'A' + (rand() % 26);  // Random letter between 'A' and 'Z'
}
// Pyramic tic tac toe
template <typename T>
class pyramicTTT_board:public Board<T> {
    vector<vector<char>> board;

public:
    pyramicTTT_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class pyramicTTT_player:public Player<T> {
public:
    pyramicTTT_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class pyramicTTT_randomplayer:public RandomPlayer<T> {
public:
    pyramicTTT_randomplayer (T symbol);
    void getmove(int &x, int &y) ;
};

//-----------implementation----------
template<typename T>
pyramicTTT_board<T>::pyramicTTT_board() {
    this->rows=3;
    this->columns=5;
    this->n_moves=0;
    this->board={{' '},{' ',' ',' '},{' ',' ',' ',' ',' '}};
}
template <typename T>
bool pyramicTTT_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] ==' '|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] =' ';
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void pyramicTTT_board<T>::display_board() {
    cout<<setw(16)<<"("<<0<<","<<0<<") ";
    cout<<this->board[0][0];
    cout << endl;
    for(int i=0;i<3;i++) {
        cout<<setw(6)<<"("<<1<<","<<i<<") ";
        cout<<this->board[1][i];
    }
    cout<<endl;
    for(int i=0;i<5;i++) {
        cout<<setw(3)<<"("<<2<<","<<i<<")";
        cout<<this->board[2][i];
    }
    cout<<endl;

}

template <typename T>
bool pyramicTTT_board<T>::is_win() {  //will be implemented--------------------------------------------
    // Check column
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && this->board[0][0] != ' ') {
        return true;
    }
    //check second level
    for(int i=0;i<3;i++) {
        if(board[1][0]==board[1][1] && board[1][1]==board[1][2]&& this->board[1][i] != ' ') {
            return true;
        }
    }

    //check third level
    for(int i=0;i<5;i++) {

        if(board[2][i]==board[2][i+1] && board[2][i+1]==board[2][i+2] && this->board[2][i] != ' ') {
            return true;
        }
    }
    //check diagonal
    if(board[0][0]==board[1][2] && board[1][2]==board[2][4] && this->board[0][0] != ' ' || board[0][0]==board[1][0] && board[1][0]==board[2][0] && this->board[0][0] != ' ') {
        return true;
    }
    return false;
}
template <typename T>
bool pyramicTTT_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool pyramicTTT_board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
pyramicTTT_player<T>::pyramicTTT_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void pyramicTTT_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
pyramicTTT_randomplayer<T>::pyramicTTT_randomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void pyramicTTT_randomplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


template <typename T>
class ultimateTTT_board:public Board<T> {

    int miniB;
protected:
    vector<Board<T>*> miniBoards;
public:
    ultimateTTT_board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    vector<Board<T>*>& getMiniBoards(); // Getter method
    T getCell(int row, int col) const;
};

template <typename T>
class ultimateTTT_player:public Player<T> {
    Board<T>* originalBoard; //points to the original board
    Board<T>* miniBoard; //points to the mini board we are currently using
    ultimateTTT_board<T>* tempBoard; //points to a tempBoard
public:
    ultimateTTT_player (string name, T symbol);
    void getmove(int& x, int& y) ;
    void set_miniB(int newMiniB); // Setter method to change miniB
    void display_mini_board(int miniB);
    void resetptr();
};

template <typename T>
class ultimateTTT_randomplayer:public RandomPlayer<T> {
public:
    ultimateTTT_randomplayer (T symbol);
    void getmove(int &x, int &y) ;
};

//---------------implementation------------------
template<typename T>
ultimateTTT_board<T>::ultimateTTT_board() {
    this->miniB = 0;                  // Initialize miniB
    this->n_moves = 0;               // Initialize number of moves
    this->rows = this->columns = 3;  // Set dimensions of the ultimate board
    for (int i = 0; i < 9; ++i) {
        miniBoards.push_back(new ultimateTTT_board<T>());
    }
}

template <typename T>
vector<Board<T>*>& ultimateTTT_board<T>::getMiniBoards() {
    return miniBoards;
}

template <typename T>
T ultimateTTT_board<T>::getCell(int row, int col) const {
    return this->board[row][col];
}
template <typename T>
void ultimateTTT_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template<typename T>
void ultimateTTT_player<T>::set_miniB(int newMiniB) {
    if (newMiniB >= 0 && newMiniB < 9) {
        this->miniB = newMiniB;
    } else {
        cout <<"Invalid mini board index. Please choose a value between 0 and 8"<<endl;
    }
}
// template <typename T>
// void ultimateTTT_player<T>::display_mini_board(int miniB) {
//     Board<T>* miniBoard = this->tempBoard->getMiniBoards()[miniB];
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             cout << miniBoard->board[i][j] << " ";
//         }
//         cout << endl;
//     }
// }
template <typename T>
ultimateTTT_player<T>::ultimateTTT_player(string name, T symbol) : Player<T>(name, symbol) {
    this->originalBoard=this->boardPtr; //the original board pointer
}

template <typename T>
void ultimateTTT_player<T>::resetptr() {
    this->boardPtr=this->originalBoard; // Reset the board pointer to the original board
}

template <typename T>
void ultimateTTT_player<T>::getmove(int& x, int& y) {
    int newboard;
    cout<<"Please choose which mini board (0,8): ";
    cin>>newboard;
    this->setBoard(this->tempBoard->getMiniBoards()[newboard]);
    this->tempBoard->display_board();
    // miniBoard=&(this->originalBoard->miniBoards[newboard]); //pointer to the new mini board
    // this->setBoard(miniBoard);
    //
    // // this->set_miniB(newboard);
    // this->display_mini_board(newboard); //to display the mini board for the user

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    this->resetptr(); //reset pointer to points on the original board
}

// Constructor for X_O_Random_Player
template <typename T>
ultimateTTT_randomplayer<T>::ultimateTTT_randomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ultimateTTT_randomplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template <typename T>
bool ultimateTTT_board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
            }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
        }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool ultimateTTT_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool ultimateTTT_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
bool ultimateTTT_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}
#endif // WORD_TIC_TAC_TOE_H