#pragma once
#include <string>

using namespace std;

namespace cli
{
    /*
     * \brief What type of message this is.
     */
    enum Prefix
    {
        Input,
        Output,
        Info,
        Error
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
         * \brief Overload to print messages passed in as std::string.
         * \param response The message response type.
         * \param message The message to print.
         */
        static void log(Prefix response, string& message);
    private:
        /**
         * \brief Resolves prefix to string which is prepended to the message.
         * \param response The message response type.
         * \return The formatted prefix.
         */
        static string resolvePrefix(Prefix response);
    };
}