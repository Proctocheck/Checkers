#ifndef CORE_H
#define CORE_H

#include <iostream>

using namespace std;

/*class game_core
{
private:
    int max_checkers = 12;

    int mustgo[12][2] = { NULL }, recomgo[12][2] = { NULL };   //МАССИВЫ, ДЛЯ ХРАНЕНИЯ КООРДИНАТ НЕОБХОДИМЫХ ШАШЕК(те, которыми можно просто походить либо которыми нужно бить)
    int countrecom = -1, countmust = -1;
    int count; //кол-во съеденых шашек
public:
    enum cell_type
    {
        white = 1, black, empty
    };
    static constexpr int N = 8;
    static constexpr int max_cell = 8;

    cell_type field[8][8] =
    {
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,

        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,black,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,black,empty,empty,empty,

        empty,empty,empty,white,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
    };

    int step = white;                              //содержит данные кто ходит в настоящий момент. ОЧЕНЬ НЕОБХОДИМАЯ ПЕРЕМЕННАЯ
    int startx = -1, starty = -1;


    bool end_game_or_continue();                         //вызывается в конце каждого хода, дабы проверитб кто выиграл и в функции input для проверки шашочки
    bool check_selected_cell(int x, int y);            //проверяем, правильные ли мы ввели координаты
    bool is_black()
    {
        return step == white ? false : true;
    }
    void change_color()
    {
        step == white ? black : white;
    }

    void show();
    bool move(int x, int y);                            //просто получаем на вход координаты и ходим, если удачно походили, то меняем step и изменяем поле)
    void king(int x, int y);

    //bool do_continue_fight(int x, int y);   //смотрим, можем ли мы продолжить бить шашки или нам пора угомониться.
                                            //если мы пользуемся графикой, то мы вызываем эту функцию после любого move и ...
    //bool continue_fight(int x, int y, int a, int b);

};
*/
class game_core
{
private:
    int max_checkers = 12;

    int mustgo[12][2] = { NULL }, recomgo[12][2] = { NULL };   //�������, ��� �������� ��������� ����������� �����(��, �������� ����� ������ �������� ���� �������� ����� ����)
    int countrecom = -1, countmust = -1;


public:
    enum cell_type
    {
        empty=0, white, black
    };
    static constexpr int N = 8;
    static constexpr int max_cell = 8;

    cell_type field[8][8] =
    {
//        empty,black,empty,black,empty,black,empty,black,
//        black,empty,black,empty,black,empty,black,empty,
//        empty,black,empty,black,empty,black,empty,black,
//        empty,empty,empty,empty,empty,empty,empty,empty,
//        empty,empty,empty,empty,empty,empty,empty,empty,
//        white,empty,white,empty,white,empty,white,empty,
//        empty,white,empty,white,empty,white,empty,white,
//        white,empty,white,empty,white,empty,white,empty,
        empty,empty,empty,black,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,black,empty,empty,empty,empty,empty,empty,
        white,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
    };
    int step = white;                              //�������� ������ ��� ����� � ��������� ������. ����� ����������� ����������
    int startx = -1, starty = -1;


    bool end_game_or_continue();                         //���������� � ����� ������� ����, ���� ��������� ��� ������� � � ������� input ��� �������� �������
    bool get_coordinates(int x, int y);            //���������, ���������� �� �� ����� ����������
    void show();
    bool is_black()
    {
        return step == white ? false : true;
    }
    void change_color()
    {
        step == white ? black : white;
    }

    bool move(int x, int y);                            //������ �������� �� ���� ���������� � �����, ���� ������ ��������, �� ������ step � �������� ����)

    //bool do_continue_fight(int x, int y);   //�������, ����� �� �� ���������� ���� ����� ��� ��� ���� �����������.
                                            //���� �� ���������� ��������, �� �� �������� ��� ������� ����� ������ move � ...
    //bool continue_fight(int x, int y, int a, int b);

};

#endif // CORE_H
