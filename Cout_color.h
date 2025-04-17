
/// ----------------------------------------
///  Cout colors
///  Coded by JP CHAMPEAUX
///  contact : JPC@irsamc.upse-tlse.fr
///  Free of use for Academic purpose only
///  (please, just mention author in your works if used or if your own code is inspired from it)
/// ----------------------------------------

#include <windows.h>
#include <math.h>
#include <time.h>

//#define UCHAR_MAX 256
using namespace std;

/// POUR FAIRE JOLI -----------------------------------
inline std::ostream& blue(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

// Couleur Jaune
inline std::ostream& yellow(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

// Couleur Cyan
inline std::ostream& cyan(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    return s;
}

// Couleur Magenta (violet)
inline std::ostream& magenta(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    return s;
}

// Couleur grise (low intensity)
inline std::ostream& grey(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

struct color {
    color(WORD attribute) : m_color(attribute) {};
    WORD m_color;
};
/// -----------------------------------------------------
