﻿#pragma once
#include <string>
#include "../lib/Dictionary.h"
#include "../lib/IUserInterface.h"

namespace cli
{
    /**
     * \brief Implementation of IUserInterface for command line console app.
     */
    class CliUserInterface : public lib::IUserInterface
    {
        lib::Dictionary& _dictionary;
        std::string _menu;

    public:
        /**
         * \brief Constructor for CliUserInterface. Dictionary used to retrieve
         * values to show the user.
         * \param dictionary The dictionary, once populated with Words.
         */
        explicit CliUserInterface(lib::Dictionary& dictionary);
        /**
        * \brief Show user main menu. Ask user to select item from menu,
        * then perform task. If input is invalid, retry until user picks corrrect option,
        * or rage quits with CTRL+C.
        * \return The selection made by the user.
        */
        void start() override;
    private:
        /**
        * \brief Ask user to enter a word to search the dictionary with.
        * If word is found, print the definition, else notify user word is not found.
        * Repeat until user chooses to go back to main menu.
        */
        void findDefinition();
        /**
        * \brief Show user the longest word/s in the dictionary.
        * Then go back to main menu.
        */
        void longestWords();
        /**
        * \brief Show user words that end in 'logy' that have a length of seven or less chars.
        * Then go back to main menu.
        */
        void wordsEndWithLogy();
        /**
         * \brief Shutdown console app gracefully.
         */
        void shutdown() const;
        /**
         * \brief Returns true if user selection at main menu matches any MenuItem.
         * \param selection The selection made by the user at main menu.
         * \returns true if input matches any MenuItem.
         */
        bool isValidMenuSelection(const std::string& selection) const;
    };
}