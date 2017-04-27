//
//  button.hpp
//  ScrapWork
//
//  Created by Neil on 4/21/17.
//
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class button;
typedef std::shared_ptr<button> buttonRef;
//typedef ci::signals::Signal<void(bool state)> buttonClickedSignal;

class button
:public po::scene::NodeContainer
{
    
public:
    static buttonRef  create(ci::gl::TextureRef buttonNormalTexture, ci::gl::TextureRef buttonActiveTexture);
    //buttonClickedSignal& getbuttonClickedSignal(){return mButtonSignal;}
    void onMouseEvent(po::scene::MouseEvent &event);
    void reset();
    
private:
    button();
    void  setup(ci::gl::TextureRef buttonNormalTexture, ci::gl::TextureRef buttonActiveTexture);
    ci::gl::TextureRef      mButtonNormalTexture;
    ci::gl::TextureRef      mButtonActiveTexture;
    po::scene::ImageRef     mPButtonNormalImg;
    po::scene::ImageRef     mPButtonActiveImg;
    
    
    //buttonClickedSignal     mButtonSignal;
    bool                    isActive;

    
    void setActiveState();
    void setNormalState();
};

#endif /* button_hpp */
