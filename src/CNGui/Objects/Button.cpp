#include "CNGui/Objects/Button.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
bool Button::onClick()
{
    return mClicked;
}

////////////////////////////////////////////////////////////
bool Button::onHover()
{
    return mHover;
}

////////////////////////////////////////////////////////////
void Button::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        mShape.setType(mStyle.shape);
        mShape.setSize(mSize);
        mShape.setFillColor(mStyle.fillcolor);
        if(mStyle.outline)
        {
            mShape.setOutlineColor(mStyle.outlinecolor);
            mShape.setOutlineThickness(mStyle.outlinethickness);
        }
        mLabel.setFont(mStyle.font);
        mLabel.setFillColor(mStyle.labelcolor);
        mLabel.setCharacterSize(mStyle.charactersize);
        mLabel.setString(mName);
        while(mLabel.getGlobalBounds().width > mShape.getGlobalBounds().width || mLabel.getGlobalBounds().height > mShape.getGlobalBounds().height)
            mLabel.setCharacterSize(mLabel.getCharacterSize() - 1);
        mLabel.setPosition(mShape.getGlobalBounds().width / 2 - mLabel.getGlobalBounds().width / 1.95, mShape.getGlobalBounds().height / 2 - mLabel.getGlobalBounds().height);
        mUpdate = false;
    }

    //If the mouse hovers the button
    if(sf::FloatRect(getPosition().x, getPosition().y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height).contains(mMouse))
    {
        mHover = true;

        //If the mouse click on the boutton we throw an event by a bool
        if(mHandleEvent.isActive(sf::Event::MouseButtonPressed))
        {
            if(mHandleEvent[sf::Event::MouseButtonPressed].mouseButton.button == sf::Mouse::Left)
                mClicked = true;
        }
        else
            mClicked = false;

        //If mouse pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.clickedcolor);
            mLabel.setFillColor(mStyle.labelclickedcolor);
            mShape.setOutlineColor(mStyle.outlineclickedcolor);
            mReturn = true;
        }
        //If mouse only hovers
        else
        {
            if(!mStyle.selectable)
            {
                mShape.setFillColor(mStyle.hovercolor);
                mLabel.setFillColor(mStyle.labelhovercolor);
                mShape.setOutlineColor(mStyle.outlinehovercolor);
                mReturn = false;
            }
            else if(!mReturn)
            {
                mShape.setFillColor(mStyle.hovercolor);
                mLabel.setFillColor(mStyle.labelhovercolor);
                mShape.setOutlineColor(mStyle.outlinehovercolor);
            }
        }
    }
    //If mouse doesn't hover the button
    else
    {
        mHover = false;

        //If mouse isn't selected
        if(!mReturn)
        {
            mShape.setFillColor(mStyle.fillcolor);
            mLabel.setFillColor(mStyle.labelcolor);
            mShape.setOutlineColor(mStyle.outlinecolor);
        }
        //If button is selected and mouse left is clicked
        else if(mHandleEvent.isActive(sf::Event::MouseButtonPressed) && mHandleEvent[sf::Event::MouseButtonPressed].mouseButton.button == sf::Mouse::Left)
        {
            mShape.setFillColor(mStyle.fillcolor);
            mLabel.setFillColor(mStyle.labelcolor);
            mShape.setOutlineColor(mStyle.outlinecolor);
            mReturn = false;
        }
    }
}

////////////////////////////////////////////////////////////
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mShape, states);
    target.draw(mLabel, states);
}

} // namespace CNGui
