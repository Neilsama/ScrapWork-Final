#include "Pile.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PileRef Pile::create(){
    PileRef ref = std::shared_ptr<Pile>(new Pile);
    ref->setup();
    return ref;
}

Pile::Pile(){}

void Pile::setup(){
    
    //pile img
    pileWaitTexture = gl::Texture::create(loadImage(loadAsset("wait_pile.png")));
    pileActive1Texture = gl::Texture::create(loadImage(loadAsset("active_pile_1.png")));
    pileActive2Texture = gl::Texture::create(loadImage(loadAsset("active_pile_2.png")));
    pileActive3Texture = gl::Texture::create(loadImage(loadAsset("active_pile_3.png")));
    introTexture = gl::Texture::create(loadImage(loadAsset("wait_introFrame.png")));
    
    pileWaitImage = po::scene::Image::create(pileWaitTexture);
    pileActive1Image = po::scene::Image::create(pileActive1Texture);
    pileActive2Image = po::scene::Image::create(pileActive2Texture);
    pileActive3Image = po::scene::Image::create(pileActive3Texture);
    introImage = po::scene::Image::create(introTexture);

    
    pileWaitImage->setAlignment(po::scene::Alignment::BOTTOM_CENTER);
    pileWaitImage->setPosition(ci::vec2(getWindowWidth()/2, getWindowHeight()));
   
    
    pileActive1Image->setAlignment(po::scene::Alignment::BOTTOM_CENTER);
    pileActive1Image->setPosition(ci::vec2(getWindowWidth()/2, getWindowHeight()));
   
    
    pileActive2Image->setAlignment(po::scene::Alignment::BOTTOM_CENTER);
    pileActive2Image->setPosition(ci::vec2(getWindowWidth()/2, getWindowHeight()));
    
    
    pileActive3Image->setAlignment(po::scene::Alignment::BOTTOM_CENTER);
    pileActive3Image->setPosition(ci::vec2(getWindowWidth()/2, getWindowHeight()));
    
    
    introImage->setAlpha(0.f);
    introImage->setAlignment(po::scene::Alignment::BOTTOM_CENTER);
    introImage->setPosition(ci::vec2(getWindowWidth()/2, getWindowHeight()));
    
    addChild(introImage);
    addChild(pileWaitImage);
    addChild(pileActive3Image);
    addChild(pileActive2Image);
    addChild(pileActive1Image);
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Pile::mousedown, this, std::placeholders::_1));
}

void Pile::update(){
    ci::app::timeline().appendTo(&pileActive3Image->getPositionAnim(), pileActive3Image->getPosition()+ vec2(1.f,0), 0.1f, ci::EaseInExpo());
    ci::app::timeline().appendTo(&pileActive3Image->getPositionAnim(), pileActive3Image->getPosition()- vec2(1.f,0), 0.1f, ci::EaseInExpo());
}

void Pile::mousedown( po::scene::MouseEvent &event ) {
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
       
            if (event.getWindowPos().x >= pileWaitImage->getPosition().x-450 && event.getWindowPos().x <= pileWaitImage->getPosition().x+450 && event.getWindowPos().y >= pileWaitImage->getPosition().y-464 && event.getWindowPos().y <= pileWaitImage->getPosition().y){
                pileAnimation();
                
            }else{
            }
            break;
       default:
            break;
    }
}


void Pile::pileAnimation(){
    
    ci::app::timeline().apply(&introImage->getAlphaAnim(), 1.f, 1.f, ci::EaseInCubic()) ;
    ci::vec2 moveEndPos = ci::vec2(640.f, 685.f);
    ci::app::timeline().apply(&introImage->getPositionAnim(), moveEndPos, 1.f, ci::EaseOutExpo());
    
    ci::app::timeline().apply(&pileWaitImage->getAlphaAnim(), 0.f, 0.5f, ci::EaseOutExpo()) ;
    ci::app::timeline().apply(&pileActive1Image->getAlphaAnim(), 0.f, 1.f, ci::EaseOutExpo()) ;
    ci::app::timeline().apply(&pileActive2Image->getAlphaAnim(), 0.f, 1.5f, ci::EaseOutExpo()) ;
    
    
}
