#ifndef CELL_H
#define CELL_H

#include "../Graph_lib/Simple_window.h"


//checkersEn ch;

using Graph_lib::Point;

struct Figure;

struct Cell : Graph_lib::Button
{
    void attach_figure(Figure& check);
    Figure& detach_figure();

    bool has_figure() const
    {
        return fig != nullptr;
    }
    const Figure& figure() const
    {
        return *fig;
    }


    enum Type { black, white,neutral };

    Cell(Point xy, Graph_lib::Callback cb, Type t);

    void attach(Graph_lib::Window& win) override;

    bool is_black() const
    {
        return type == black;
    }
    bool is_neutral() const
    {
        return type == neutral;
    }

    Point center() const
    {
        return Point{ loc.x + width / 2,
                      loc.y + height / 2 };
    }

    void activate()
    {
        if (pw) pw->color(FL_SELECTION_COLOR);
    }   //graph_lib:button --> grapf_lib : digit(а он содержит указатель типа FL_Wigit* pw) и в selec...color находится цвет который необходимо установить

    void deactivate()
    {
        reset_color();
    }

    static constexpr int size = 50;

private:
    Type type;

    void reset_color();

    Figure* fig{ nullptr };

};

struct Figure
{
    virtual bool is_black() const = 0;

    virtual void attach(const Cell& c) = 0;

    void detach() { cell = nullptr; }

    bool is_attached() const
    {
        return cell != nullptr;
    };    //нужен для сохранения данных о клетке, есть ли в ней фигура и т.д.

protected:
    const Cell* cell{ nullptr };
};

struct Checker:Figure, Graph_lib::Circle
{
    Checker(Graph_lib::Window& win);

    void attach(const Cell& c) override;
    void draw_lines() const override;
private:
    static constexpr int r = 0.4 * Cell::size;
    static constexpr double half = 0.5;
};

struct WhiteChecker : Checker
{
    WhiteChecker(Graph_lib::Window& win);
    bool is_black() const override
    {
        return false;
    }
};

struct BlackChecker : Checker
{
    BlackChecker(Graph_lib::Window& win);
    bool is_black() const override
    {
        return true;
    }
};
#endif // CELL_H
