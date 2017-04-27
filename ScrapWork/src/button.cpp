//
//  button.cpp
//  ScrapWork
//
//  Created by Neil on 4/21/17.
//
//

#include "button.hpp"
#include "PreviewPanel.hpp"
#include "poShape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

buttonRef button::create(ci::gl::TextureRef buttonNormalTexture, ci::gl::TextureRef buttonActiveTexture)
{
    buttonRef ref = std::shared_ptr<button>(new button);
    ref->setup(buttonNormalTexture, buttonActiveTexture);
    return ref;
}

button::button(){}


void button::setup(ci::gl::TextureRef buttonNormalTexture, ci::gl::TextureRef buttonActiveTexture)
{
    // load preview panel frame picture
    mButtonNormalTexture = buttonNormalTexture;
    mButtonActiveTexture = buttonActiveTexture;
    mPButtonNormalImg = po::scene::Image::create(buttonNormalTexture);
    mPButtonActiveImg = po::scene::Image::create(mButtonActiveTexture);
    mPButtonActiveImg->setAlpha(0);
    
    isActive = false;
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&button::onMouseEvent, this, std::placeholders::_1));
    
    addChild(mPButtonNormalImg);
    addChild(mPButtonActiveImg);
}

void button::onMouseEvent(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
        {
            isActive = !isActive;
            if (isActive) {
                setActiveState();
            }else
                setNormalState();
        }
            
            break;
    
        default:
            break;
    }
}

void button::setActiveState()
{
    ci::app::timeline().apply(&mPButtonNormalImg->getAlphaAnim(),1.f,0.f,0.1);
    ci::app::timeline().apply(&mPButtonActiveImg->getAlphaAnim(),0.f,1.f,0.1);
}

void button::setNormalState()
{
    ci::app::timeline().apply(&mPButtonNormalImg->getAlphaAnim(),0.f,1.f,0.1);
    ci::app::timeline().apply(&mPButtonActiveImg->getAlphaAnim(),1.f,0.f,0.1);

}

