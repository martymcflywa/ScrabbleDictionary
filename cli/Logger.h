#pragma once
#include <chrono>

namespace cli
{
    /*
     * \brief What type of message this is.
     */
    enum Prefix
    {
        Error,
        Info,
        Input,
        Menu,
        Output,
        Task
    };

    /**
     * \brief Prints stuff to console.
     */
    class Logger
    {
    public:
        /**
         * \brief Need this overload so we can handle exception messages from .what()
         * \param response The message response type.
         * \param message The message to print.
         */
        static void log(Prefix response, char const* message);
        /**
        * \brief Overload to print message with operation duration.
        * \param response The message response type.
        * \param message The message to print.
        * \param duration How long the operation took.
        */
        static void log(Prefix response, const std::string& message, const std::chrono::duration<double>& duration);
        /**
         * \brief Overload to print messages passed in as std::string.
         * \param response The message response type.
         * \param message The message to print.
         */
        static void log(Prefix response, const std::string& message);
        /**
         * \brief Overload for messages without prefix.
         * \param message The message to print.
         */
        static void log(const std::string& message);
        /**
        * \brief Print '>' cli prompt when user input required.
        */
        static void printPrompt();
    private:
        /**
         * \brief Resolves prefix to string which is prepended to the message.
         * \param response The message response type.
         * \return The formatted prefix.
         */
        static std::string resolvePrefix(Prefix response);
    };
}
