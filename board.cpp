#include <iostream>

#include "board.h"
#include "core.h"
using namespace std;

using namespace Graph_lib;

std::string letters()     //������� ��� ����������� ������ �� ��������� (�������)
{
    std::string s( Checkerboard::N_max, '\0' );
    for (int i = 0; i < Checkerboard::N_max; ++i)
        s[i] = 'a' + i;
    return s;
}

std::string digits()      //������� ��� ����������� ������ �� ����������� (�������)
{
    std::string s( Checkerboard::N_max, '\0' );
    for (int i = 0; i < Checkerboard::N_max; ++i)
        s[i] = '1' + i;
    return s;
}

Cell::Type type_of_cell(int i, int j)
{
    if (i % 2 == 0)
        return (j % 2 == 0) ? Cell::black : Cell::white;
    else
        return (j % 2 == 0) ? Cell::white : Cell::black;
}

Checkerboard::Checkerboard(Point xy): My_window{ xy, width, height,"Checkerboard" } , x_labels{ letters() }, y_labels{ digits() }
{
    size_range(width, height, width, height);  // fixed window size

    for (int i = 0; i < N; ++i)
    {
        const Point lu{ margin + Cell::size / 2, margin + N * Cell::size + 10};//����� ������ �������� ����
        const Point rb{ margin - 10, margin + N * Cell::size - Cell::size / 2};
        x_labels.add(Point{ lu.x + i * Cell::size, lu.y });
        y_labels.add(Point{ rb.x, rb.y - i * Cell::size });
    }

    attach(x_labels);
    attach(y_labels);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            cells.push_back(new Cell{ Point{margin + j * Cell::size,
                                            margin + (N - 1 - i) * Cell::size},
                                      cb_clicked, type_of_cell(i,j) });
            attach(cells[cells.size() - 1]);
        }
    //ячейки для побитых шашек
    for (int i = N; i < N+3; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cells.push_back(new Cell{ Point{margin + i * Cell::size, margin + (N - 1 - j) * Cell::size}, cb_clicked, Cell::neutral });
            attach(cells[cells.size() - 1]);
        }
    }

    int count = 8;
    //расстановка шашечек
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
        {
            if (!cells[count*(N-i-1)+j].has_figure() && gc.field[i][j] != gc.empty)
                if (gc.field[i][j] == gc.white)
                {
                    checkers.push_back(new WhiteChecker{ *this });
                    cells[count*(N-i-1)+j].attach_figure(checkers[checkers.size() - 1]);
                }
                else
                {
                    checkers.push_back(new BlackChecker{ *this });
                    cells[count*(N-i-1)+j].attach_figure(checkers[checkers.size() - 1]);
                }
        }

    reFill();
}


/*void Checkerboard::clicked(Address widget)
{
    Fl_Widget& w = reference_to<Fl_Widget>(widget);
    Cell& c = at (Point{ w.x(), w.y() });
    if (!selected)
    {
        selected = &c;
        c.activate();
    }
    else
    {
        if (&c == selected)
        {
            selected -> deactivate();
            selected = nullptr;
        }
        else
        {
            selected->deactivate();
            selected = &c;
            c.activate();
        }
    }
    Fl::redraw();
}
*/
Cell& Checkerboard::at(Point p)
{
    int i = N - 1 - (p.y - margin) / Cell::size;
    int j = (p.x - margin) / Cell::size;
    return cells[i * N + j];
}
void Checkerboard::clicked(Address widget)
{
    Fl_Widget&w = reference_to<Fl_Widget>(widget);
    Cell& c = at(Point{ w.x(),w.y() });
    if (!c.is_black() || c.is_neutral())return;
    int x = (w.x() - margin) / Cell::size, y = N - 1 - (w.y() - margin) / Cell::size;
    y = N - y -1;

    if(!selected)
    {
        if (c.has_figure()
                && gc.get_coordinates(x,y)
                && ((!gc.is_black() && !c.figure().is_black()) || (gc.is_black() && c.figure().is_black())) )
            //if (gc.check_selected_cell((w.x()-30)/50,(w.y()-30)/50) == true)
        {
            gc.startx = (w.x()-30)/50;
            gc.starty = (w.y()-30)/50;
            selected = &c;
            c.activate();
        }
    }
    else
    {
        if (selected->is_neutral())
            return;
        selected->deactivate();
        if (selected == &c)//выбираем ту же клетку
        {
            selected = nullptr;
        }
        else  if (c.has_figure() && ((!gc.is_black() && !c.figure().is_black()) || (gc.is_black() && c.figure().is_black())))
            //выбираем клетку с фиурой нужного цвета
        {
            selected = &c;
            c.activate();
            gc.change_color();
        }
        else if (!c.has_figure() && gc.move(x,y))//пустая клетка
        {
            c.attach_figure(selected->detach_figure());
            selected = nullptr;
        }
    }
    //gc.show();
    reFill();

    if (!gc.end_game_or_continue())//чекаем конец игры
        hide();
    Fl::redraw();
}

void Checkerboard::reFill()
{
    int count = 8;//счётчик по вектору cells
    //вывод в консоль
    for (int i = 0; i < 8; i++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout << i + 1 << " | " << gc.field[i][0] << " | " << gc.field[i][1] << " | " << gc.field[i][2] << " | " << gc.field[i][3] << " | " << gc.field[i][4] << " | " << gc.field[i][5] << " | " << gc.field[i][6] << " | " << gc.field[i][7] << " |" << endl;

    }
    //уборка побитых шашек
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            if (cells[count*(N-i-1)+j].has_figure() && gc.field[i][j] == gc.empty)
            {
                cells[useless].attach_figure(cells[count*(N-i-1)+j].detach_figure());
                useless++;
            }
    //доставка недостающих(нахуя, сам не знаю)
}
