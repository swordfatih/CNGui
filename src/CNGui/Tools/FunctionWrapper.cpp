/////////////////////////////////////////////////////////////////////////////////
//
// CNGui 1.1 - Chats Noirs Graphical User Interface
// Copyright (c) 2019 Fatih (accfldekur@gmail.com)
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <CNGui/Tools/FunctionWrapper.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
FunctionWrapper::FunctionWrapper() : mHandle(&FunctionWrapper::handle, this), mTerminate(false), mRunning(false)
{
    //ctor
}

////////////////////////////////////////////////////////////
FunctionWrapper::FunctionWrapper(const std::function<void(void)>& function) : FunctionWrapper()
{
    connect(function);
}

////////////////////////////////////////////////////////////
FunctionWrapper::~FunctionWrapper()
{
    terminate();
}

////////////////////////////////////////////////////////////
void FunctionWrapper::connect(const std::function<void(void)>& function)
{
    mFunction = function;
}

////////////////////////////////////////////////////////////
bool FunctionWrapper::connected()
{
    if(mFunction)
    {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////
bool FunctionWrapper::execute()
{
    if(mFunction && !mRunning)
    {
        mCondition.notify_one();
        mRunning = true;
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////
bool FunctionWrapper::execute(const std::function<void(void)>& function)
{
    if(!mRunning)
    {
        connect(function);

        if(mFunction)
        {
            mRunning = true;
            mCondition.notify_one();
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////
void FunctionWrapper::terminate()
{
    mTerminate = true;
    mRunning = true;
    mCondition.notify_one();
    if(mHandle.joinable())
    {
        mHandle.join();
    }
}

////////////////////////////////////////////////////////////
bool FunctionWrapper::isRunning()
{
    return mRunning;
}

////////////////////////////////////////////////////////////
void FunctionWrapper::handle()
{
    while(!mTerminate)
    {
        std::unique_lock<std::mutex> lock(mMutex);

        mCondition.wait(lock, [this](){return mRunning.load();});

        if(!mTerminate)
        {
            mFunction();
            mRunning = false;
        }
    }
}

} // namespace CNGui
