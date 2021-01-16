#include <iostream>
//#include "graphics.h"
#include "board.h"
#include "core.h"
#include "windows.h"

using namespace std;

int main()
{
    game_core ch;

    /*checkers ch;
     *

    ch.step = ch.a;



    try
    {
        ch.game(ch, ch.step);
    }
    catch (const std::exception&)
    {

    }*/
    system("cls");

    Sleep(300);

    cout << "\n\n________________________Welcome to the club, buddy________________________\n\n" << endl;
    const char* Quote[4] = { "THE","GAME","STARTS","NOW !!!" };
    for (int i = 0; i < 4; i++)
    {
        cout << "\n\n" << "\t\t\t" << Quote[i] << "  ";
        //Sleep(1000);
    }
    cout << "\n";
    Sleep(300);

   // cout << ch.step << endl;

    Sleep(1000);

    //system("cls");
    if (ch.end_game_or_continue() == true)
    {
        Checkerboard board{ Point{100, 100} };
        return Graph_lib::gui_main();
    }
}
