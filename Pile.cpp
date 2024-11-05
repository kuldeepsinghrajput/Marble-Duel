 

#include<stdio.h>
#include <cstdlib> 
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace::std;
void printFrame(const std::string& text, char horizontal = '~', char vertical = '|', char corner = '+') {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int textLength = text.length();
    int padding = (columns - textLength - 2) / 2;  // 2 for the vertical bars
    int verticalPadding = (rows - 3) / 2; // 3 for the top, bottom and text lines
    std::cout << std::string(columns, horizontal) << std::endl;
    std::cout << vertical << std::string(padding, ' ') << text << std::string(padding, ' ') << vertical << std::endl;
    std::cout << std::string(columns, horizontal) << std::endl;
}
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
void printCentered(const std::string& text) {
    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text ;
}
void moveToPosition(int x, int y) { COORD coord; coord.X = x; coord.Y = y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); }
void clearLine(int line) {
    moveToPosition(0, line);
    std::cout << std::string(getConsoleWidth(), ' '); // Clear the line 
    moveToPosition(0, line); // Move back to the beginning of the line 
}
COORD getCurrentCursorPosition() { CONSOLE_SCREEN_BUFFER_INFO csbi; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); return csbi.dwCursorPosition; }
void printCentered(const std::string& text, COORD coord) {
    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - text.length()) / 2;
    clearLine(coord.Y);
    std::cout << std::string(padding, ' ') << text;
}
int main() {  
	int turn, marbles,draw;
    COORD marbleLeft, turnsTo, drawAmount, errorMark,maxLine;

	srand(time(0));
    marbles = (rand() % 499) + 2;
    std::ostringstream oss;
    turn =   rand() % 2;
    
    
    {
        printFrame("Marble Duel");
        cout << endl << endl << endl;
        oss << "Wallah!! there are " << marbles << " marbles in the pile...";
        printCentered(oss.str());
        cout << "\n\n";
        oss.str(""); // Clear the content 
        oss.clear(); // Clear any error flags
        oss << "It's " << (turn % 2 ? "computer" : "player") << " who won the TOSS!!";

        printCentered(oss.str());

        cout << "\n\n";

        printCentered("(Press any key to play..)");
        _getch();
    }
    
    {
        system("cls");
        printFrame("Marble Duel");
        cout << "\n\n";
        oss.str("");
        oss.clear();
        oss << marbles << " Marbles left";
        marbleLeft = getCurrentCursorPosition();
        printCentered(oss.str(), marbleLeft);
        cout << "\n\n\n\n";

        oss.str("");
        oss.clear();

        turnsTo = getCurrentCursorPosition();
        oss << ((turn % 2 ? "Computer" : "Player")) << " Turn!!";
        printCentered(oss.str(), turnsTo);

        cout << "\n\n\n";
        maxLine = getCurrentCursorPosition();
        oss.str("");
        oss.clear();
        oss << "Enter your drawing amount?(Max:" << marbles / 2 << ")";
        printCentered(oss.str() );
        cout << "\n";
        drawAmount = getCurrentCursorPosition();
        printCentered("", drawAmount);

        cout << "\n\n\n";
        errorMark = getCurrentCursorPosition();

    }
    while (marbles > 1)
    {
        oss.str("");
        oss.clear();
        oss << marbles << " Marbles left";
        printCentered(oss.str(), marbleLeft);
        oss.str("");
        oss.clear();
        oss << ((turn % 2 ? "Computer" : "Player")) << " Turn!!";
        printCentered(oss.str(), turnsTo);
        oss.str("");
        oss.clear();
        oss << "Enter your drawing amount?(Max:" << marbles / 2 << ")";
        printCentered(oss.str(), maxLine);

        printCentered(" ", drawAmount);
        if (turn) 
        {
            draw = 256;
            while (marbles < draw)draw >>= 1;
            draw = marbles - draw + 1;
            if (draw > (marbles >> 1))draw = (rand() % (marbles >> 1) + 1);
            cout<<draw ;
            oss.str("");
            oss.clear();
            oss << "Computer has drwan "<<draw<<" Marbles..(Press any key to continue)";
            printCentered( oss.str(), errorMark);
            _getch();
            oss.str("");
            oss.clear();
            oss << "Enter your drawing amount?(Max:" << marbles / 2 << ")";
            printCentered(oss.str(),maxLine);
            printCentered(" ", errorMark);


      }
        else
        {
            cin >> draw;

            while ((marbles / 2) < draw)
            {
                printCentered("You have drawn more than half...Please try again..(Press any key to continue)", errorMark);
                _getch();
                printCentered("", errorMark);
                printCentered("", drawAmount);
                cin >> draw;

            }
        }
        marbles -= draw;
        turn ^= 1;
    }

    system("cls");
    printFrame("Marble Duel");
    cout << "\n\n\n";


    oss.str("");
    oss.clear();
    oss << ((turn % 2 ? "Hurray...You WON.." : "Oops!!! You Loose.."));
    printCentered(oss.str());
   
    _getch();
	return 0;
}
 