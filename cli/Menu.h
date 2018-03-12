#pragma once
#include <string>

using namespace std;

namespace cli
{
    /**
     * \brief Prints the menu and returns the user selection.
     */
    class Menu
    {
    public:
        static string select();
    };
}