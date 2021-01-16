/*#include "core.h"

void game_core::show()
{
    system("cls");
    for (int i = 0; i < 8; i++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout << i + 1 << " | " << field[i][0] << " | " << field[i][1] << " | " << field[i][2] << " | " << field[i][3] << " | " << field[i][4] << " | " << field[i][5] << " | " << field[i][6] << " | " << field[i][7] << " |" << endl;

    }
}

bool game_core::end_game_or_continue()
{
    //recomgo = NULL; mustgo = NULL;  //ОБНУЛЕНИЕ ДАННЫХ О КООРДИНАТ ШАШЕК

    int no_block = 0, enemy = 0;                          //
    countmust = -1; countrecom = -1;                      //необходимы счётчик для записывания кол-ва шашек для recomgo и mustgo

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (field[i][j] == white && i == 0) field[i][j] = empty; else if (field[i][j] == black && i == 7) field[i][j] = empty;

            if (field[i][j] != step && field[i][j] != empty) enemy++;
            if (enemy > max_checkers || no_block > max_checkers) { cout << "TOO MANY CHECKERS"; return false; }

            if (field[i][j] == step)
            {
                if (field[i - 1][j - 1] != step && field[i - 1][j - 1] != empty && field[i - 2][j - 2] == empty && i - 2 > 0 && j - 2 > 0)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i - 1][j + 1] != step && field[i - 1][j + 1] != empty && field[i - 2][j + 2] == empty && i - 2 > 0 && j + 2 < 8)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i + 1][j - 1] != step && field[i + 1][j - 1] != empty && field[i + 2][j - 2] == empty && i + 2 < 8 && j - 2 > 0)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i + 1][j + 1] != step && field[i + 1][j + 1] != empty && field[i + 2][j + 2] == empty && i + 2 < 8 && j + 2 < 8)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (step == white)
                {
                    if ((field[i - 1][j - 1] == empty && j != 0 && i != 0) || (field[i - 1][j + 1] == empty && j != 7 && i != 0))
                    {
                        no_block++;
                        countrecom++;
                        recomgo[countrecom][0] = i; recomgo[countrecom][1] = j;
                    }
                }
                else if (step == black)
                {
                    if ((field[i + 1][j - 1] == empty && j != 0 && i != 7) || (field[i - 1][j + 1] == empty && j != 7 && i != 7))
                    {
                        no_block++;
                        countrecom++;
                        recomgo[countrecom][0] = i; recomgo[countrecom][1] = j;
                    }
                }
            }
        }

    if (enemy == 0)
    {
        if (step == white)
            cout << "\n\n\t\t\t\tWIN__________WHITE"; else cout << "\n\n\t\t\t\tWIN__________BLACK";
        return false;
    }
    if (no_block == 0)
    {
        if (step == white)
            cout << "\n\n\t\t\t\tWIN__________BLACK"; else cout << "\n\n\t\t\t\tWIN__________WHITE";
        return false;
    }
    return true;
}
//СЛУЖИТ ДЛЯ ПРОВЕРКИ ИГРАБЕЛЬНЫХ ШАШЕК. ЕСЛИ ТАКИХ НЕТУ, ТО ЗАВЕРШАЕМ ИГРУ, ИНАЧЕ ПРОДОЛЖАЕМ

bool game_core::check_selected_cell(int x, int y)
{
    if (field[y][x] != step)
        return false;

    for (int i = 0; i < 12; i++)
    {
        if (countmust == -1)
        {
            if (recomgo[i][1] == x && recomgo[i][0] == y
                && countrecom != 0 && i <= countrecom)  //(i <= countrecom - 1) необходимо для того, чтобы мы смотрели только координаты, кол-во которых <countrecom-1

                return true;
        }
        else if (mustgo[i][1] == x && mustgo[i][0] == y
            && i <= countmust)                   //(i <= countmust- 1) необходимо для того, чтобы мы смотрели только координаты, кол-во которых <countmust-1
            return true;
    }

    return false;
}

bool game_core::move(int x, int y)
{
    int b = x, a = y;
    x = startx; y = starty;

    if (step == white)
    {
        if (countmust == -1)
        {
            if (field[y - 1][x - 1] == empty && a + 1 == y && b + 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            if (field[y - 1][x + 1] == empty && a + 1 == y && b - 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
        }
        else
        {
            if (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty && field[y - 2][x - 2] == empty && a + 2 == y && b + 2 == x)
            {
                field[y - 1][x - 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty && field[y - 2][x + 2] == empty && a + 2 == y && b - 2 == x)
            {
                field[y - 1][x + 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty && field[y + 2][x - 2] == empty && a - 2 == y && b + 2 == x)
            {
                field[y + 1][x - 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty && field[y + 2][x + 2] == empty && a - 2 == y && b - 2 == x)
            {
                field[y + 1][x + 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            return false;
        }
    }
    if (step == black)
    {
        if (countmust == -1)
        {
            if (field[y + 1][x - 1] == empty && a - 1 == y && b + 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            if (field[y + 1][x + 1] == empty && a - 1 == y && b - 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
        }
        else
        {
            if (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty && field[y - 2][x - 2] == empty && a + 2 == y && b + 2 == x)
            {
                field[y - 1][x - 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty && field[y - 2][x + 2] == empty && a + 2 == y && b - 2 == x)
            {
                field[y - 1][x + 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty && field[y + 2][x - 2] == empty && a - 2 == y && b + 2 == x)
            {
                field[y + 1][x - 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty && field[y + 2][x + 2] == empty && a - 2 == y && b - 2 == x)
            {
                field[y + 1][x + 1] = empty;
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            } return false;
        }
    }
}

void game_core::king(int x, int y)
{

}
*/
#include "core.h"
void game_core::show()
{
    game_core gc;
    //system("cls");
    cout << "\n\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout << i + 1 << " | " << gc.field[i][0] << " | " << gc.field[i][1] << " | " << gc.field[i][2] << " | " << gc.field[i][3] << " | " << gc.field[i][4] << " | " << gc.field[i][5] << " | " << gc.field[i][6] << " | " << gc.field[i][7] << " |" << endl;

    }
    cout << "\n\n\n";
}

bool game_core::end_game_or_continue()
{


    int no_block = 0, enemy = 0;
    countmust = -1; countrecom = -1;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (field[i][j] == white && i == 0) field[i][j] = empty; else if (field[i][j] == black && i == 7) field[i][j] = empty;

            if (field[i][j] != step && field[i][j] != empty) enemy++;
            if (enemy > max_checkers || no_block > max_checkers) { cout << "TOO MANY CHECKERS"; return false; }

            if (field[i][j] == step)
            {
                if (field[i - 1][j - 1] != step && field[i - 1][j - 1] != empty && field[i - 2][j - 2] == empty && i - 2 > 0 && j - 2 > 0)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i - 1][j + 1] != step && field[i - 1][j + 1] != empty && field[i - 2][j + 2] == empty && i - 2 > 0 && j + 2 < 8)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i + 1][j - 1] != step && field[i + 1][j - 1] != empty && field[i + 2][j - 2] == empty && i + 2 < 8 && j - 2 > 0)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (field[i + 1][j + 1] != step && field[i + 1][j + 1] != empty && field[i + 2][j + 2] == empty && i + 2 < 8 && j + 2 < 8)
                {
                    no_block++;
                    countmust++;
                    mustgo[countmust][0] = i; mustgo[countmust][1] = j;
                }
                else if (step == white)
                {
                    if ((field[i - 1][j - 1] == empty && j != 0 && i != 0) || (field[i - 1][j + 1] == empty && j != 7 && i != 0))
                    {
                        no_block++;
                        countrecom++;
                        recomgo[countrecom][0] = i; recomgo[countrecom][1] = j;
                    }
                }
                else if (step == black)
                {
                    if ((field[i + 1][j - 1] == empty && j != 0 && i != 7) || (field[i - 1][j + 1] == empty && j != 7 && i != 7))
                    {
                        no_block++;
                        countrecom++;
                        recomgo[countrecom][0] = i; recomgo[countrecom][1] = j;
                    }
                }
            }
        }

    if (enemy == 0)
    {
        if (step == white)
            cout << "\n\n\t\t\t\tWIN__________WHITE"; else cout << "\n\n\t\t\t\tWIN__________BLACK";
        return false;
    }
    if (no_block == 0)
    {
        if (step == white)
            cout << "\n\n\t\t\t\tWIN__________BLACK"; else cout << "\n\n\t\t\t\tWIN__________WHITE";
        return false;
    }
    return true;
}
//� Ў� ›� Ј� –� � ў � ”� ›� Ї � џ�  � ћ� ’� •�  � љ�  � � “�  � ђ� ‘� •� ›� ¬� ќ� «� Ґ � Ё� ђ� Ё� •� љ. � •� Ў� ›�  � ў� ђ� љ� � Ґ � ќ� •� ў� Ј, � ў� ћ � —� ђ� ’� •�  � Ё� ђ� •� њ � � “�  � Ј, � � ќ� ђ� §� • � џ�  � ћ� ”� ћ� ›� –� ђ� •� њ

bool game_core::get_coordinates(int x, int y)
{
    if (field[y][x] != step)
        return false;

    for (int i = 0; i < 12; i++)
    {
        if (countmust == -1)
        {
            if (recomgo[i][1] == x && recomgo[i][0] == y
                && countrecom != 0 && i <= countrecom)  //(i <= countrecom - 1) � Ѕ� µ� ѕ� ±С…� ѕ� ґ� ё� ј� ѕ � ґ� »СЏ С‚� ѕ� і� ѕ, С‡С‚� ѕ� ±С‹ � јС‹ СЃ� ј� ѕС‚СЂ� µ� »� ё С‚� ѕ� »СЊ� є� ѕ � є� ѕ� ѕСЂ� ґ� ё� Ѕ� °С‚С‹, � є� ѕ� »-� І� ѕ � є� ѕС‚� ѕСЂС‹С… <countrecom-1

                return true;
        }
        else if (mustgo[i][1] == x && mustgo[i][0] == y
            && i <= countmust)                   //(i <= countmust- 1) � Ѕ� µ� ѕ� ±С…� ѕ� ґ� ё� ј� ѕ � ґ� »СЏ С‚� ѕ� і� ѕ, С‡С‚� ѕ� ±С‹ � јС‹ СЃ� ј� ѕС‚СЂ� µ� »� ё С‚� ѕ� »СЊ� є� ѕ � є� ѕ� ѕСЂ� ґ� ё� Ѕ� °С‚С‹, � є� ѕ� »-� І� ѕ � є� ѕС‚� ѕСЂС‹С… <countmust-1
            return true;
    }

    return false;
}

bool game_core::move(int x, int y)
{
    int b = x, a = y;
    x = startx; y = starty;
    int q{ 0 };
    if (step == white)
    {
        if (countmust == -1)
        {
            if (field[y - 1][x - 1] == empty && a + 1 == y && b + 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            if (field[y - 1][x + 1] == empty && a + 1 == y && b - 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
        }
        else
        {
        fightw:
            if (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty && field[y - 2][x - 2] == empty && a + 2 + q * 2 == y && b + 2 + q * 2 == x)
            {
                field[y - 1][x - 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a + q * 2][b + q * 2] = white; else field[a + q * 2][b + q * 2] = black;
                if ((field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty))

                {
                    x = b + q * 2;
                    y = a + q * 2;
                    ++q;
                    goto fightw;
                }

                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty && field[y - 2][x + 2] == empty && a + 2 + q * 2 == y && b - 2 - q * 2 == x)
            {
                field[y - 1][x + 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a + q * 2][b - q * 2] = white; else field[a + q * 2][b - q * 2] = black;
                if ((field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty))

                {
                    x = b - q * 2;
                    y = a + q * 2;
                    ++q;
                    goto fightw;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty && field[y + 2][x - 2] == empty && a - 2 - q * 2 == y && b + 2 + q * 2 == x)
            {
                field[y + 1][x - 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a - q * 2][b + q * 2] = white; else field[a - q * 2][b + q * 2] = black;
                if ((field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty))

                {
                    x = b + q * 2;
                    y = a - q * 2;
                    ++q;

                    goto fightw;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty && field[y + 2][x + 2] == empty && a - 2 - q * 2 == y && b - 2 - q * 2 == x)
            {
                field[y + 1][x + 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a - q * 2][b - q * 2] = white; else field[a - q * 2][b - q * 2] = black;
                if ((field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty))
                {
                    x = b - q * 2;
                    y = a - q * 2;
                    ++q;
                    goto fightw;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
        }
        cout << "Pizda\n";
        return false;
    }
    if (step == black)
    {
        if (countmust == -1)
        {
            if (field[y + 1][x - 1] == empty && a - 1 == y && b + 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
            if (field[y + 1][x + 1] == empty && a - 1 == y && b - 1 == x)
            {
                field[y][x] = empty;
                if (step == white)
                    field[a][b] = white; else field[a][b] = black;
                if (step == white) step = black; else step = white;
                return true;
            }
        }
        else
        {
        fightb:
            if (field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty && field[y - 2][x - 2] == empty && a + 2 + q * 2 == y && b + 2 + q * 2 == x)
            {
                field[y - 1][x - 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a + q * 2][b + q * 2] = white; else field[a + q * 2][b + q * 2] = black;
                if ((field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty))
                {
                    x = b + q * 2;
                    y = a + q * 2;
                    ++q;
                    goto fightb;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty && field[y - 2][x + 2] == empty && a + 2 + q * 2 == y && b - 2 - q * 2 == x)
            {
                field[y - 1][x + 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a + q * 2][b - q * 2] = white; else field[a + q * 2][b - q * 2] = black;
                if ((field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty))
                {
                    x = b - q * 2;
                    y = a + q * 2;
                    ++q;
                    goto fightb;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty && field[y + 2][x - 2] == empty && a - 2 - q * 2 == y && b + 2 + q * 2 == x)
            {
                field[y + 1][x - 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a - q * 2][b + q * 2] = white; else field[a - q * 2][b + q * 2] = black;
                if ((field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty))
                {
                    x = b + q * 2;
                    y = a - q * 2;
                    ++q;
                    goto fightb;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            else if (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty && field[y + 2][x + 2] == empty && a - 2 - q * 2 == y && b - 2 - q * 2 == x)
            {
                field[y + 1][x + 1] = empty;
                field[y][x] = empty;

                if (step == white)
                    field[a - q * 2][b - q * 2] = white; else field[a - q * 2][b - q * 2] = black;

                if ((field[y - 1][x - 1] != step && field[y - 1][x - 1] != empty) || (field[y - 1][x + 1] != step && field[y - 1][x + 1] != empty) || (field[y + 1][x - 1] != step && field[y + 1][x - 1] != empty) || (field[y + 1][x + 1] != step && field[y + 1][x + 1] != empty))
                {
                    x = b - q * 2;
                    y = a - q * 2;
                    ++q;
                    goto fightb;
                }
                if (step == white) step = black; else step = white;
                return true;
            }
            return false;
        }
    }

    return false;
}
