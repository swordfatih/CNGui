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

#include <CNGui/Tools/Scissors.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
Scissors::Scissors(sf::FloatRect area)
{
    //Start
    mBusy = glIsEnabled(GL_SCISSOR_TEST);

    //Save and modify
    if(mBusy)
    {
        int existing_scissors[4];
        glGetIntegerv(GL_SCISSOR_BOX, existing_scissors);

        mAreaExisting = {existing_scissors[0], existing_scissors[1], existing_scissors[2], existing_scissors[3]};

        area.intersects(mAreaExisting, area);
    }

    //Clip
    glEnable(GL_SCISSOR_TEST);
    glScissor(area.left, area.top, area.width, area.height);

    mAreaClip = area;
}

////////////////////////////////////////////////////////////
Scissors::~Scissors()
{
    glScissor(mAreaExisting.left, mAreaExisting.top, mAreaExisting.width, mAreaExisting.height);

    if(!mBusy)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

////////////////////////////////////////////////////////////
sf::FloatRect Scissors::area()
{
    return mAreaClip;
}

} // namespace CNGui
