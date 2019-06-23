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

#ifndef FUNCTIONWRAPPER_HPP
#define FUNCTIONWRAPPER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that can store a function and execute it on
/// another thread
///
////////////////////////////////////////////////////////////
class FunctionWrapper
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                FunctionWrapper();

    ////////////////////////////////////////////////////////////
    /// \brief Constructor that connects a function by default
    ///
    ////////////////////////////////////////////////////////////
                FunctionWrapper(const std::function<void(void)>& function);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor that calls terminate
    ///
    ////////////////////////////////////////////////////////////
    virtual     ~FunctionWrapper();

    ////////////////////////////////////////////////////////////
    /// \brief Connect a function
    ///
    /// \param function Function to connect
    ///
    ////////////////////////////////////////////////////////////
    void        connect(const std::function<void(void)>& function);

    ////////////////////////////////////////////////////////////
    /// \brief Get connected
    ///
    /// \return True if a function is connected
    ///
    ////////////////////////////////////////////////////////////
    bool        connected();

    ////////////////////////////////////////////////////////////
    /// \brief Execute the connected function
    ///
    /// \return False if no function is connected or a function
    /// is already running
    ///
    ////////////////////////////////////////////////////////////
    bool        execute();

    ////////////////////////////////////////////////////////////
    /// \brief Connect and execute a function
    ///
    /// \return False if a function is already running
    ///
    ////////////////////////////////////////////////////////////
    bool        execute(const std::function<void(void)>& function);

    ////////////////////////////////////////////////////////////
    /// \brief Terminate the thread by force
    ///
    ////////////////////////////////////////////////////////////
    void        terminate();

    ////////////////////////////////////////////////////////////
    /// \brief Get function running event
    ///
    /// \return True if function running
    ///
    ////////////////////////////////////////////////////////////
    bool        isRunning();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Thread function
    ///
    ////////////////////////////////////////////////////////////
    void        handle();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::function<void(void)>   mFunction;  ///< Connected function
    std::thread                 mHandle;    ///< Thread to execute the connected function on
    std::mutex                  mMutex;     ///< Thread mutex
    std::condition_variable     mCondition; ///< Condition variable
    std::atomic_bool            mTerminate; ///< Terminate function
    std::atomic_bool            mRunning;   ///< Function is running
};

} // namespace CNGui

#endif // FUNCTIONWRAPPER_HPP
