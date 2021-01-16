#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "core.h"

using Graph_lib::Point;
using Graph_lib::Address;

struct My_window : Simple_window
{
    My_window(Point xy, int w, int h, const std::string& title)
        : Simple_window{ xy, w, h, title }
        , quit_button{ Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit }
    {
        attach(quit_button);
    }


    Graph_lib::Button quit_button;

private:
    static void cb_quit(Address, Address addr)
    {
        Graph_lib::reference_to<My_window>(addr).quit();
    }
    void quit() { hide(); }
};


struct Checkerboard : My_window
{
    Checkerboard(Point xy);
    Cell& at(Point);
    void reFill();
    game_core gc;                            //класс для работы с ядром

    static constexpr int N = 8;              // board N by N
    static constexpr int N_max = 8;
    int useless = 64;                        //индекс пустой синей клетки
    int needx,needy;

    static_assert (N <= N_max,
        "do not allow board larger than N_max by N_max");


private:
    static constexpr int margin = 30;
    static constexpr int width = (N+5) * Cell::size + 2 * margin + 70;
    static constexpr int height = N * Cell::size + 2 * margin;
    Graph_lib::Marks x_labels;
    Graph_lib::Marks y_labels;
    Graph_lib::Vector_ref<Figure> checkers;

    Cell* selected{ nullptr };

    Graph_lib::Vector_ref<Cell> cells;

    static void cb_clicked(Address widget, Address win)
    {
        Graph_lib::reference_to<Checkerboard>(win).clicked(widget);
    }
    void clicked(Address widget);
};


#endif // #ifndef BOARD_H
