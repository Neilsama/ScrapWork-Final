#include "Buttons.h"

using namespace po::scene;

ButtonsRef Buttons::create(gl::TextureRef btnImg, gl::TextureRef btnActiveImg){
    ButtonsRef ref = std::shared_ptr<Buttons>(new Buttons);
    ref -> setup(btnImg, btnActiveImg);
    return ref;
}

void Buttons::setup(gl::TextureRef btnImg, gl::TextureRef btnActiveImg){
    
    mButtonTexture = btnImg;
    mButton = po::scene::Image::create(mButtonTexture);
    
    mButtonActiveTexture = btnActiveImg;
    mButtonActive = po::scene::Image::create(mButtonActiveTexture);
    
    mButton->setAlpha(1.f);
    mButtonActive->setAlpha(0.f);
    
    addChild(mButton);
    addChild(mButtonActive);


    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Buttons::mousedown, this, std::placeholders::_1));
}

void Buttons::mousedown(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            btnIsActivated = !btnIsActivated;
            if (btnIsActivated){
                ci::app::timeline().apply(&mButtonActive->getAlphaAnim(), 0.f, 1.f, 0.8f,EaseOutExpo());
                ci::app::timeline().apply(&mButton->getAlphaAnim(), 1.f, 0.f, 0.8f,EaseOutExpo());
                btnStateChangeSignal.emit(mID);
            }
            else{
                ci::app::timeline().apply(&mButtonActive->getAlphaAnim(), 1.f, 0.f, 0.8f,EaseOutExpo());
                ci::app::timeline().apply(&mButton->getAlphaAnim(), 0.f, 1.f, 0.8f,EaseOutExpo());
                btnStateChangeSignal.emit(mID);
            }
            break;
        default:
            break;
    }
}


void Buttons::setToNormal()
{
    mButtonActive->setAlpha(0.f);
    mButton->setAlpha(1.f);
    btnIsActivated = false;
}
