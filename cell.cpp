#include "cell.h"

using namespace Graph_lib;


Cell::Cell(Point xy, Callback cb, Type t)
    : Button{ xy, size, size, "", cb }
    , type{ t }  {}


void Cell::attach(Graph_lib::Window& win)
{
    Button::attach(win);
    reset_color();
}


void Cell::reset_color()
{
    if (!pw) error("Cell is not attached to a window");
    if(Cell::is_neutral())
        pw->color(Color::red);
    else if (is_black())
        pw->color(Color::black);
    else
        pw->color(Color::white);
}


Checker::Checker(Graph_lib::Window& win)
    : Circle{ Point{0,0}, r }
{
    set_style(Line_style{ Line_style::solid,2 });
    win.attach(*this);
}

void Checker::attach(const Cell& c)
{
    if (is_attached()) error("Already attached");
    cell = &c;
    move(c.center().x - center().x,
        c.center().y - center().y);
}
void Checker::draw_lines() const
{
    Circle::draw_lines();

    if (color().visibility())
    {
        int r = half * radius();
        fl_arc(center().x - r, center().y - r, r + r, r + r, 0, 360);
    }

}

const Color White{ 17 };
const Color Black{ 30 };

WhiteChecker::WhiteChecker(Graph_lib::Window& win) :Checker{ win }
{
    set_color(Black);
    set_fill_color(White);
}

BlackChecker::BlackChecker(Graph_lib::Window& win) :Checker{ win }
{
    set_color(White);
    set_fill_color(Black);
}

void Cell::attach_figure(Figure& ch)
{
    if (fig) error("Already hasa a  figure");
    fig = &ch;
    ch.attach(*this);
}
Figure& Cell::detach_figure()
{
    move(0, 0);
    if (fig)
    {
        Figure * o = fig;
        fig->detach();
        fig = nullptr;
        return *o;
    }

    throw std::runtime_error("error");
}
