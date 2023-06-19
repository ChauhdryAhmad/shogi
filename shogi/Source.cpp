#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

#define cap 50

enum Color
{
	white,black
};

struct pos
{
	int ri, ci;
};

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void Init(char**& B, int& dim, string Pname[2], int& turn, string f)
{
    ifstream rdr(f);
    rdr >> dim;
    B = new char* [dim];
    for (int i = 0; i < dim; i++)
    {
        B[i] = new char[dim];
        for (int j = 0; j < dim; j++) 
        {
            rdr >> B[i][j];
        }
    }
    for (int i = 0; i < 2; i++)
    {
        cout << "\nEnter Player " << i + 1 << " name : ";
        cin >> Pname[i];
    }
    turn = white;
}

void drawPawn(int r, int c, char type, char sym)
{
    if (type == 'p')
        SetClr(2);
    if (type == 'P')
        SetClr(6);
    if (type == 't')
        SetClr(4);
    if (type == 'T')
        SetClr(0);
    for (int rad = 0; rad < 3; rad++)
    {
        for (int theta = 0; theta < 360; theta++)
        {
            float radian = theta * (3.14 / 180);
            int x = rad * cos(radian) + (r*8)+4;
            int y = rad * sin(radian) + (c*8)+4;
            gotoRowCol(x, y);
            cout << sym;
        }
    }
}

void drawBishop(int r, int c, char type, char sym)
{
    if (type == 'b')
        SetClr(2);
    if (type == 'B')
        SetClr(6);
    if (type == 'a')
        SetClr(4);
    if (type == 'A')
        SetClr(0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3 + i; j++)
        {
            gotoRowCol(r*8+1+j, c * 8 + 2 + i);
            cout << sym;
        }
    }
    
}

void drawRook(int r, int c, char type, char sym)
{
    if (type == 'r')
        SetClr(2);
    if (type == 'R')
        SetClr(6);
    if (type == 'd')
        SetClr(4);
    if (type == 'D')
        SetClr(0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoRowCol(r * 8 + 3 + i, c * 8 + 2 + j);
            cout << sym;
        }
    }
    for (int i = 1; i < 5; i += 3)
    {
        gotoRowCol(r * 8 + 2, c * 8 + 1 + i);
        cout << sym;
    }
   
}

void drawLance(int r, int c, char type, char sym)
{
    if (type == 'l')
        SetClr(2);
    if (type == 'L')
        SetClr(6);
    if (type == 'x')
        SetClr(4);
    if (type == 'X')
        SetClr(0);
    gotoRowCol(r * 8 + 2, c * 8 + 4);
    cout << sym;
    for (int i = 0; i < 3; i++)
    {
        gotoRowCol(r * 8 + 3, c * 8 + 3 + i);
        cout << sym;
    }
    for (int i = 0; i < 5; i++)
    {
        gotoRowCol(r * 8 + 4, c * 8 + 2 + i);
        cout << sym;
    }
    for (int i = 0; i < 2; i++)
    {
        gotoRowCol(r * 8 + 5 + i, c * 8 + 4);
        cout << sym;
    }
}

void drawKnight(int r, int c, char type, char sym)
{
    if (type == 'h')
        SetClr(2);
    if (type == 'H')
        SetClr(6);
    if (type == 'y')
        SetClr(4);
    if (type == 'Y')
        SetClr(0);
    gotoRowCol(r * 8 + 2, c * 8 + 4);
    cout << sym;
    for (int i = 0; i < 3; i += 1)
    {
        gotoRowCol(r * 8 + 3, c * 8 + 3 + i);
        cout << sym;
    }
    for (int i = 0; i < 5; i += 1)
    {
        gotoRowCol(r * 8 + 4, c * 8 + 2 + i);
        cout << sym;
    }
    for (int i = 0; i < 3; i += 1)
    {
        gotoRowCol(r * 8 + 5, c * 8 + 3 + i);
        cout << sym;
    }
    gotoRowCol(r * 8 + 6, c * 8 + 4);
    cout << sym;
}

void drawSilver(int r, int c, char type, char sym)
{
    if (type == 's')
        SetClr(2);
    if (type == 'S')
        SetClr(6);
    if (type == 'z')
        SetClr(4);
    if (type == 'Z')
        SetClr(0);
    for (int i = 0; i < 5; i++)
    {
        gotoRowCol(r * 8 + 3, c * 8 + 2 + i);
        cout << sym;
    }
    for (int i = 0; i < 6; i++)
    {
        gotoRowCol(r * 8 + 2+i, c * 8 + 4);
        cout << sym;
    }
}

void drawGold(int r, int c, char type, char sym)
{
    if (type == 'g')
        SetClr(2);
    if (type == 'G')
        SetClr(6);
    for (int i = 0; i < 5; i++)
    {
        gotoRowCol(r * 8 + 3, c * 8 + 2 + i);
        cout << sym;
    }
    for (int i = 0; i < 7; i++)
    {
        gotoRowCol(r * 8 + 5, c * 8 + 1+ i);
        cout << sym;
    }
    for (int i = 0; i < 6; i++)
    {
        gotoRowCol(r * 8 + 2 + i, c * 8 + 4);
        cout << sym;
    }
}

void drawKing(int r, int c, char type, char sym)
{
    if (type == 'g')
        SetClr(2);
    if (type == 'G')
        SetClr(6);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoRowCol(r * 8 + 2 + i, c * 8 + 2 + j);
            cout << sym;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        gotoRowCol(r * 8 + 6, c * 8 + 1 + i);
        cout << sym;
    }
 

}

void duplicateBoard(char** B, char**& b, int dim)
{
    b = new char* [dim];
    for (int i = 0; i < dim; i++)
    {
        b[i] = new char[dim];
        for (int j = 0; j < dim; j++)
        {
            b[i][j] = B[i][j];
        }
    }
}

void drawPeice(char** B, int dim, char sym)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            switch (B[r][c])
            {
            case'p':
            case'P':
            case't':
            case'T':
                drawPawn(r, c, B[r][c], sym);
                break;
            case'b':
            case'B':
            case'a':
            case'A':
                drawBishop(r, c, B[r][c], sym);
                break;
            case'r':
            case'R':
            case'd':
            case'D':
                drawRook(r, c, B[r][c], sym);
                break;
            case'l':
            case'L':
            case'x':
            case'X':
                drawLance(r, c, B[r][c], sym);
                break;
            case'h':
            case'H':
            case'y':
            case'Y':
                drawKnight(r, c, B[r][c], sym);
                break;
            case's':
            case'S':
            case'z':
            case'Z':
                drawSilver(r, c, B[r][c], sym);
                break;
            case'g':
            case'G':
                drawGold(r, c, B[r][c], sym);
                break;
            case'k':
            case'K':
                drawKing(r, c, B[r][c], sym);
                break;
            default:
                break;
            }
        }
    }
}

void drawBox(int sr, int sc, int brow, int bcol, int clr, int pClr, char sym, char peice)
{
    for (int ri = 0; ri < brow; ri++)
    {
        for (int ci = 0; ci < bcol; ci++)
        {
            if (peice == ' ' && (ri == 0 || ri == brow - 1) && (ci == 0 || ci == bcol - 1))
            {
                SetClr(2);
                gotoRowCol(sr + ri, sc + ci);
                cout << sym;
            }
            else if (ri == brow / 2 && ci == bcol / 2 && peice != '-')
            {
                SetClr(pClr);
                gotoRowCol(sr + ri, sc + ci);
                cout << peice;
            }
            else
            {
                SetClr(clr);
                gotoRowCol(sr + ri, sc + ci);
                cout << sym;
            }
        }
    }
}

void drawBoard(char** B, int dim, int brow, int bcol, char sym)
{
 
    int clr = 7, CLR = 9, pClr = 0, bclr = 0;
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {

            if ((ri + ci) % 2 == 0)
            {
                if (B[ri][ci] >= 'a' || B[ri][ci] <= 'z')
                {
                    pClr = 4;
                }
                if (B[ri][ci] >= 'A' || B[ri][ci] <= 'Z')
                {
                    pClr = 6;
                }
                drawBox(ri * brow, ci * bcol, brow, bcol, clr, pClr, sym, B[ri][ci]);
            }
            else
            {
                if (B[ri][ci] >= 'a' || B[ri][ci] <= 'z')
                {
                    pClr = 4;
                }
                if (B[ri][ci] >= 'A' || B[ri][ci] <= 'Z')
                {
                    pClr = 6;
                }
                drawBox(ri * brow, ci * bcol, brow, bcol, CLR, pClr, sym, B[ri][ci]);
            }
        }
    }
    drawPeice(B, dim, sym);
}

void turnMsg(string name)
{
    gotoRowCol(30, 120);
    cout << "                                 ";
    gotoRowCol(30, 120);
    cout << name << " turn";
}

void selectSc(pos& Sc)
{
    getRowColbyLeftClick(Sc.ri, Sc.ci);
    Sc.ri = Sc.ri / 8;
    Sc.ci = Sc.ci / 8;
    gotoRowCol(35, 120);
    cout << "                                       ";
    gotoRowCol(35, 120);
    cout << "( " << Sc.ri << " , " << Sc.ci << " )";
}

void selectDes(pos& Des)
{
    getRowColbyLeftClick(Des.ri, Des.ci);
    Des.ri = Des.ri / 8;
    Des.ci = Des.ci / 8;
    gotoRowCol(37, 120);
    cout << "                                      ";
    gotoRowCol(37, 120);
    cout << "( " << Des.ri << " , " << Des.ci << " )";
}

bool isMyPeice(char** B, pos P, int turn)
{
    if (turn == white)
    {
        if (B[P.ri][P.ci] >= 'a' && B[P.ri][P.ci] <= 'z')
            return true;
    }
    else
    {
        if (B[P.ri][P.ci] >= 'A' && B[P.ri][P.ci] <= 'Z')
            return true;
    }
    return false;
}

bool isValidSc(char** B, int dim, pos Sc, int turn)
{
    if (Sc.ri < 0 || Sc.ci < 0 || Sc.ri >= dim || Sc.ci >= dim)
    {
        return false;
    }
    if (!isMyPeice(B, Sc, turn))
    {
        return false;
    }
    return true;
}

bool isValidDes(char** B, int dim, pos Des, int turn)
{
    if (Des.ri < 0 || Des.ci < 0 || Des.ri >= dim || Des.ci >= dim)
    {
        return false;
    }
    if (B[Des.ri][Des.ci] == '-')
        return true;
    else if (isMyPeice(B, Des, turn))
    {
        return false;
    }
    return true;
}

void updateBoard(char** B, pos Sc, pos Des,char a[],char c[],int &sizea,int &sizec)
{
    if (B[Des.ri][Des.ci] >= 'a' && B[Des.ri][Des.ci] <= 'z')
    {
        sizea++;
        a[sizea - 1] = B[Des.ri][Des.ci];
    }
    if (B[Des.ri][Des.ci] >= 'A' && B[Des.ri][Des.ci] <= 'Z')
    {
        sizec++;
        c[sizea - 1] = B[Des.ri][Des.ci];
    }
    B[Des.ri][Des.ci] = B[Sc.ri][Sc.ci];
    B[Sc.ri][Sc.ci] = '-';
}

void duplicateUpdateBoard(char** b, pos Sc, pos Des)
{
    b[Des.ri][Des.ci] = b[Sc.ri][Sc.ci];
    b[Sc.ri][Sc.ci] = '-';
}

void turnChange(int& turn)
{
    turn = (turn + 1) % 2;
}

bool isElligibleForPromotion(char** B, pos Sc, pos Des, int turn)
{
    if (B[Des.ri][Des.ci] == 'k' || B[Des.ri][Des.ci] == 'K' || B[Des.ri][Des.ci] == 'g' || B[Des.ri][Des.ci] == 'G' || B[Des.ri][Des.ci] == 't' || B[Des.ri][Des.ci] == 'T' || B[Des.ri][Des.ci] == 'a' || B[Des.ri][Des.ci] == 'A' || B[Des.ri][Des.ci] == 'x' || B[Des.ri][Des.ci] == 'X' || B[Des.ri][Des.ci] == 'y' || B[Des.ri][Des.ci] == 'Y' || B[Des.ri][Des.ci] == 'z' || B[Des.ri][Des.ci] == 'Z' || B[Des.ri][Des.ci] == 'd' || B[Des.ri][Des.ci] == 'D')
        return false;
    if (turn == white && Des.ri <= 2)
        return true;
    if (turn == black && Des.ri >= 6)
        return true;
    return false;
}

bool promotionForPandL(char** B, pos Sc, pos Des, int turn)
{
    if (Des.ri == 0 && (B[Des.ri][Des.ci] == 'p' || B[Des.ri][Des.ci] == 'l') && turn == white)
           return true;
    if (Des.ri == 8 && (B[Des.ri][Des.ci] == 'p' || B[Des.ri][Des.ci] == 'l') && turn == black)
           return true;
    return false;
}

void isPromoted(char** B, pos Sc, pos Des, int turn)
{
    switch (B[Des.ri][Des.ci])
    {
    case'p':
        B[Des.ri][Des.ci] = 't';
        break;
    case'P':
        B[Des.ri][Des.ci] = 'T';
        break;
    case'b':
        B[Des.ri][Des.ci] = 'a';
        break;
    case'B':
        B[Des.ri][Des.ci] = 'A';
        break;
    case'r':
        B[Des.ri][Des.ci] = 'd';
        break;
    case'R':
        B[Des.ri][Des.ci] = 'D';
        break;
    case'l':
        B[Des.ri][Des.ci] = 'x';
        break;
    case'L':
        B[Des.ri][Des.ci] = 'X';
        break;
    case'h':
        B[Des.ri][Des.ci] = 'y';
        break;
    case'H':
        B[Des.ri][Des.ci] = 'Y';
        break;
    case's':
        B[Des.ri][Des.ci] = 'z';
        break;
    case'S':
        B[Des.ri][Des.ci] = 'Z';
        break;
    }
}

bool isHorizontalMove(pos Sc, pos Des)
{
    if (Sc.ri == Des.ri)
        return true;
    return false;
}

bool isVerticalMove(pos Sc, pos Des)
{
    if (Sc.ci == Des.ci)
        return true;
    return false;
}

bool isDiagnolMove(pos Sc, pos Des)
{
    if (abs(Sc.ri - Des.ri) == abs(Sc.ci - Des.ci))
        return true;
    return false;
}

bool isHorizontalPathClear(char** B, pos Sc, pos Des, int turn)
{
    if (Sc.ci < Des.ci)
    {
        for (int i = Sc.ci + 1; i <= Des.ci; i++)
        {
            if (B[Sc.ri][i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    else
    {
        for (int i = Des.ci + 1; i < Sc.ci; i++)
        {
            if (B[Sc.ri][i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    return true;
}

bool isVerticalPathClear(char** B, pos Sc, pos Des, int turn)
{
    if (Sc.ri < Des.ri)
    {
        for (int i = Sc.ri + 1; i < Des.ri; i++)
        {
            if (B[i][Sc.ci] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    else
    {
        for (int i = Des.ri + 1; i < Sc.ri; i++)
        {
            if (B[i][Sc.ci] != '-')
                return false;
        }
    }
    return true;
}

bool isDiagnolL2RPathClear(char** B, pos Sc, pos Des, int turn)
{
    int r = abs(Sc.ri - Des.ri);
    if (Sc.ri < Des.ri)
    {
        for (int i = 1; i < r; i++)
        {
            if (B[Sc.ri + i][Sc.ci + i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    else
    {
        for (int i = 1; i < r; i++)
        {
            if (B[Sc.ri - i][Sc.ci - i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    return true;
}

bool isDiagnolR2LPathClear(char** B, pos Sc, pos Des, int turn)
{
    int r = abs(Sc.ri - Des.ri);
    if (Sc.ri < Des.ri)
    {
        for (int i = 1; i < r; i++)
        {
            if (B[Sc.ri + i][Sc.ci - i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    else
    {
        for (int i = 1; i < r; i++)
        {
            if (B[Sc.ri - i][Sc.ci + i] != '-' || isMyPeice(B, Des, turn))
                return false;
        }
    }
    return true;
}

bool kingLegality(char** B, pos Sc, pos Des,int turn)
{
    int r = abs(Sc.ri - Des.ri);
    int c = abs(Sc.ci - Des.ci);
    if (r == 1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des))
        return true;
    else if (r == 0 && c == 1 && isHorizontalPathClear(B, Sc, Des, turn) && isHorizontalMove(Sc, Des))
        return true;
    else if (r == 1 && c == 1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
        return true;
    else if (r == 1 && c == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
        return true;
    return false;
}

bool GoldGeneralLegality(char** B, pos Sc, pos Des, int turn)
{


    if ((isHorizontalPathClear(B, Sc, Des, turn) && isHorizontalMove(Sc, Des)) || (isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des)) || (isDiagnolMove(Sc, Des) && isDiagnolL2RPathClear(B, Sc, Des, turn)) || (isDiagnolMove(Sc, Des) && isDiagnolR2LPathClear(B, Sc, Des, turn)))
        return true;
    return false;
















    /*
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (abs(r)==1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des))
        return true;
    else if (abs(c)==1 && r == 0 && isHorizontalPathClear(B, Sc, Des, turn) && isHorizontalMove(Sc, Des))
        return true;
    if (turn == white)
    {
        if (r == -1 && c == -1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
        else if (r == -1 && c == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
    }
    if (turn == black)
    {
        if (r == 1 && c == -1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
        else if (r == 1 && c == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
    }
    return false;*/
}

bool SilverGeneralLegality(char** B, pos Sc, pos Des, int turn)
{
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (r == 1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == black)
        return true;
    else if (r == -1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == white)
        return true;
    else if (abs(r) == 1 && abs(c) == 1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
        return true;
    else if (abs(r) == 1 && abs(c) == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
        return true;
    return false;
}

bool knightLegality(char** B, pos Sc, pos Des, int turn)
{
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (r == -2 && abs(c) == 1 && turn == white)
        return true;
    else if (r == 2 && abs(c) == 1 && turn == black)
        return true;
    return false;
}

bool lanceLegality(char** B, pos Sc, pos Des, int turn)
{
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (r < 0 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == white)
        return true;
    else if (r > 0 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == black)
        return true;
    return false;
}

bool rookLegality(char** B, pos Sc, pos Des, int turn)
{
    if ((isHorizontalPathClear(B, Sc, Des, turn) && isHorizontalMove(Sc, Des)) || (isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des)))
        return true;
    return false;
}

bool bishopLegality(char** B, pos Sc, pos Des, int turn)
{
    if (isDiagnolMove(Sc, Des) && (isDiagnolL2RPathClear(B, Sc, Des, turn) || isDiagnolR2LPathClear(B, Sc, Des, turn)))
        return true;
    return false;
}

bool pawnLeaglity(char** B, pos Sc, pos Des, int turn)
{
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (r == -1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == white)
        return true;
    if (r == 1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des) && turn == black)
        return true;
    return false;
}

bool dragonKingLegality(char** B, pos Sc, pos Des,int turn)
{
    if (rookLegality(B, Sc, Des, turn) || kingLegality(B, Sc, Des, turn))
        return true;
    return false;
}

bool horseKingLegality(char** B, pos Sc, pos Des, int turn)
{
    if (bishopLegality(B, Sc, Des, turn) || kingLegality(B, Sc, Des, turn))
        return true;
    return false;
}

bool promotedPeices(char** B, pos Sc, pos Des, int turn)
{
    int r = Des.ri - Sc.ri;
    int c = Des.ci - Sc.ci;
    if (abs(r) == 1 && c == 0 && isVerticalPathClear(B, Sc, Des, turn) && isVerticalMove(Sc, Des))
        return true;
    else if (abs(c) == 1 && r == 0 && isHorizontalPathClear(B, Sc, Des, turn) && isHorizontalMove(Sc, Des))
        return true;
    if (turn == white)
    {
        if (r == -1 && c == -1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
        else if (r == -1 && c == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
    }
    if (turn == black)
    {
        if (r == 1 && c == -1 && isDiagnolL2RPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
        else if (r == 1 && c == 1 && isDiagnolR2LPathClear(B, Sc, Des, turn) && isDiagnolMove(Sc, Des))
            return true;
    }
    return false;
}

bool isLegality(char** B, pos Sc, pos Des, int turn)
{
    switch (B[Sc.ri][Sc.ci])
    {
    case'k':
    case'K':
        return kingLegality(B, Sc, Des, turn);
    case'g':
    case'G':
        return GoldGeneralLegality(B, Sc, Des, turn);
    case's':
    case'S':
        return SilverGeneralLegality(B, Sc, Des, turn);
    case'h':
    case'H':
        return knightLegality(B, Sc, Des, turn);
    case'l':
    case'L':
        return lanceLegality(B, Sc, Des, turn);
    case'r':
    case'R':
        return rookLegality(B, Sc, Des, turn);
    case'b':
    case'B':
        return bishopLegality(B, Sc, Des, turn);
    case'p':
    case'P':
        return pawnLeaglity(B, Sc, Des, turn);
    case'd':
    case'D':
        return dragonKingLegality(B, Sc, Des, turn);
    case'a':
    case'A':
        return horseKingLegality(B, Sc, Des, turn);
    case't':
    case'T':
    case'x':
    case'X':
    case'y':
    case'Y':
    case'z':
    case'Z':
        return promotedPeices(B, Sc, Des, turn);
    }
    return false;
}

void findKing(char** B, int dim, pos& P, int turn)
{
    if (turn == white)
    {
        for (int r = 0; r < dim; r++)
        {
            for (int c = 0; c < dim; c++)
            {
                if (B[r][c] == 'k')
                {
                    P.ri = r;
                    P.ci = c;
                }
            }
        }
    }
    else if (turn == black)
    {
        for (int r = 0; r < dim; r++)
        {
            for (int c = 0; c < dim; c++)
            {
                if (B[r][c] == 'K')
                {
                    P.ri = r;
                    P.ci = c;
                }
            }
        }
    }
}

bool check(char** B, int dim, int turn)
{
    pos P,S;
    turnChange(turn);
    findKing(B, dim, P, turn);
    turnChange(turn);
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            S.ri = r;
            S.ci = c;
            if (isValidSc(B, dim, S, turn) && isLegality(B, S, P, turn))
                return true;
        }
    }
    return false;
}

bool selfCheck(char** b, int dim, pos Sc, pos Des, int turn)
{
    char temp = b[Des.ri][Des.ci];
    b[Des.ri][Des.ci] = b[Sc.ri][Sc.ci];
    b[Sc.ri][Sc.ci] = '-';
    turnChange(turn);
    if (check(b, dim, turn))
    {
        b[Sc.ri][Sc.ci] = b[Des.ri][Des.ci];
        b[Des.ri][Des.ci] = temp;
        return true;
    }
    b[Sc.ri][Sc.ci] = b[Des.ri][Des.ci];
    b[Des.ri][Des.ci] = temp;
    return false;
}

bool kingCheck(char** B, int dim, int turn, pos D)
{
    pos S;
    turnChange(turn);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            S.ri = i;
            S.ci = j;
            if (isValidSc(B, dim, S, turn) && isLegality(B, S, D, turn))
                return true;
        }
    }
    return false;
}

bool checkmate(char** B, int dim, int turn)
{
    int lcount = 0, ccount = 0;
    pos P,D;
    findKing(B, dim, P, turn);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            D.ri = i, D.ci = j;
            if (isLegality(B, P, D, turn) && isValidDes(B, dim, D, turn))
            {
                lcount++;
                if (kingCheck(B, dim, turn, D))
                    ccount++;
            }
        }
    }
    turnChange(turn);

    if (lcount == ccount)
        return true;
    return false;
}

void drawGrid(int sr, int sc, int brow, int bcol, int clr, char sym)
{
    for (int i = 0; i < brow; i++)
    {
        for (int j = 0; j < bcol; j++)
        {
            if (i == 0 || i == brow - 1 || j == 0 || j == bcol - 1)
            {
                SetClr(clr);
                gotoRowCol(sr + i, sc + j);
                cout << sym;
            }
        }
    }
}

void highlight(int dim, char** b, bool** bmap)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (bmap[i][j] == true)
                drawGrid(i * 8, j * 8, 8, 8, 13, -37);
        }
    }
}

void unHighlight(char** b, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (b[i][j] == ',')
                b[i][j] = '-';
        }
    }
}

void computeHighlightPositions(char** B, int dim, pos Sc, char** b,int turn)
{
    bool** bmap;
    pos D;
    bmap = new bool* [dim];
    for (int i = 0; i < dim; i++)
    {
        bmap[i] = new bool[dim];
        for (int j = 0; j < dim; j++)
        {
            bmap[i][j] = false;
            D.ri = i;
            D.ci = j;
            if (isValidDes(B, dim, D, turn) && isLegality(B, Sc, D, turn) && !selfCheck(b, dim, Sc, D, turn))
            {
                bmap[i][j] = true;
            }
        }
    }
    highlight(dim, b, bmap);
}

void Save(char** B, int Dim, int Turn)
{
    ofstream writer("Savetxt.txt");
    writer << Dim << endl;
    for (int i = 0; i < Dim; i++)
    {
        for (int j = 0; j < Dim; j++)
        {
            writer << B[i][j];
        }
        writer << endl;
    }
    writer << endl << Turn;
}

void PrintPieces(char a[], int sizea, char c[], int sizec, string PNames[])
{
    gotoRowCol(2, 80);
    cout << PNames[0] << "'s captured pieces: ";
    for (int i = 0; i < sizea; i++)
    {
        gotoRowCol(4, 82 + i);

        cout << a[i];
    }
    /*  DrawCaptured(a, sizea, 16/8, 80/8);*/
    gotoRowCol(10, 80);
    cout << PNames[1] << "'s captured pieces: ";
    for (int i = 0; i < sizec; i++)
    {
        gotoRowCol(12, 82 + i);

        cout << c[i];

    }
    /* DrawCaptured(c, sizeb, 32/8, 80/8);*/
}













int main()
{
    char** B, sym = -37, ** b;
    char a[50] = {};char c[50] = {};
    int dim, turn, ch, fs, sizea = 0, sizec = 0;
    string Pname[2],f;
    pos Sc, Des;
    cout << "What do you want :\n1-New Game\n2-Load Game\n";
    cin >> fs;
    if (fs == 1)
        f = "board.txt";
    if (fs == 2)
        f = "Savetxt.txt";
    Init(B, dim, Pname, turn,f);
    duplicateBoard(B, b, dim);
    system("cls");
    drawBoard(B, dim, 8, 8, sym);
    while (true)
    {
        do
        {
            do
            {
                turnMsg(Pname[turn]);
                do
                {
                    selectSc(Sc);
                    if (!isValidSc(B, dim, Sc, turn))
                    {
                        gotoRowCol(35, 120);
                        cout << "                   ";
                        gotoRowCol(35, 120);
                        cout << "Invalid Source";
                    }
                } while (!isValidSc(B, dim, Sc, turn));
                computeHighlightPositions(B, dim, Sc, b, turn);
                do
                {
                    selectDes(Des);
                    if (!isValidDes(B, dim, Des, turn))
                    {
                        gotoRowCol(37, 120);
                        cout << "                   ";
                        gotoRowCol(37, 120);
                        cout << "Invalid Destination";
                    }
                } while (!isValidDes(B, dim, Des, turn));
            } while (!isLegality(B, Sc, Des, turn));
        } while (selfCheck(B, dim, Sc, Des, turn));
       // unHighlight(b, dim);
       // drawBoard(b, dim, 8, 8, sym);
        Save(B, dim, turn);
        updateBoard(B, Sc, Des, a, c, sizea, sizec);
        duplicateUpdateBoard(b, Sc, Des);
        PrintPieces(a, sizea, c, sizec, Pname);
        drawBoard(B, dim, 8, 8, sym);
        if (promotionForPandL(B, Sc, Des, turn))
        {
            isPromoted(B, Sc, Des, turn);
        }
        if (isElligibleForPromotion(B, Sc, Des, turn))
        {
            gotoRowCol(44, 120);
            cout << "                                 ";
            gotoRowCol(46, 120);
            cout << "                              ";
            gotoRowCol(48, 120);
            cout << "                            ";
            gotoRowCol(50, 120);
            cout << "                             ";
            gotoRowCol(44, 120);
            cout << "Do you want to Promote";
            gotoRowCol(46, 120);
            cout << "1-Yes";
            gotoRowCol(48, 120);
            cout << "2-No";
            gotoRowCol(49, 120);
            SetClr(15);
            cin >> ch;
            gotoRowCol(52, 120);
            cout << "                                         ";
            if (ch == 1)
            {
                gotoRowCol(52, 120);
                cout << "Peice is Promoted";

                isPromoted(B, Sc, Des, turn);
                drawBoard(B, dim, 8, 8, sym);
            }
            gotoRowCol(44, 120);
            cout << "                                 ";
            gotoRowCol(46, 120);
            cout << "                              ";
            gotoRowCol(48, 120);
            cout << "                            ";
            gotoRowCol(50, 120);
            cout << "                             ";
            gotoRowCol(52, 120);
            cout << "                                         ";
        }

        if (check(B, dim, turn))
        {
            turnChange(turn);
            if (checkmate(B, dim, turn))
            {
                gotoRowCol(55, 120);
                cout << Pname[turn] << " won by checkmate";
            }
            else 
            {
                gotoRowCol(55, 120);
                cout << Pname[turn] << " is in check";
                turnChange(turn);
            }
        }
        turnChange(turn);
        Save(B, dim, turn);

        
    }

    return _getch();
}
