#pragma once

#include "poNodeContainer.h"
#include "poImage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Buttons;
typedef  std::shared_ptr<Buttons> ButtonsRef;
typedef  ci::signals::Signal<void(int number)> btnChangeState;

class Buttons
:public po::scene::NodeContainer
{
public:
    
    static ButtonsRef  create(gl::TextureRef btnImg, gl::TextureRef btnActiveImg);
    btnChangeState& getbtnChangeStateSignal(){return btnStateChangeSignal;}
    
    void setup(gl::TextureRef btnImg, gl::TextureRef btnActiveImg);
    void mousedown(po::scene::MouseEvent &event);
    void setToNormal();
    void setID(int number){mID = number;}
    btnChangeState btnStateChangeSignal;
    bool btnIsActivated;
    
    
private:
    
    po::scene::ImageRef mButton;
    po::scene::ImageRef mButtonActive;
    
    gl::TextureRef mButtonTexture;
    gl::TextureRef mButtonActiveTexture;
    
    int             mID;
};

