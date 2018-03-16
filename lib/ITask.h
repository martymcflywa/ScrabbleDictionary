#pragma once
#include <list>
#include <memory>
#include <string>
#include "TaskType.h"
#include "Word.h"

namespace lib
{
    class ITask
    {
    public:
        virtual ~ITask() = default;
        virtual void handleTasks(std::shared_ptr<Word> wordObj) = 0;
        virtual std::list<std::shared_ptr<Word>> getTaskResult(TaskType taskType) = 0;
        virtual std::list<std::shared_ptr<Word>> getTaskResult(TaskType taskType, const std::string& word) = 0;
    };
}
