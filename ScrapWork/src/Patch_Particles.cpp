//
//  Patch_Particles.cpp
//  Patch_Particles
//
//  Created by Aaron Lee on 4/19/17.
//
//

#include "Patch_Particles.h"

Patch_ParticlesRef Patch_Particles::create(glm::vec2 position, glm::vec2 acceleration)
{
    Patch_ParticlesRef ref = std::shared_ptr<Patch_Particles> (new Patch_Particles()) ;
    ref->setup(position, acceleration) ;
    return ref ;
}

Patch_Particles::Patch_Particles()
:mFriction(0.98f)
, mVel(glm::vec2(0))
, mAcc(glm::vec2(0))
{
    
}

void Patch_Particles::setup(glm::vec2 position, glm::vec2 acceleration) {
    
    mPos = position ;
    mAcc = acceleration ;
    mVel += mAcc;
    notSwirling = true ;
    
    for (int i = 0; i < 24; i++) {
        
        try {
            
            // load pathes image into vector
            ci::gl::TextureRef  texture = ci::gl::Texture::create(loadImage(loadAsset(std::to_string(i)+".jpg")));
            mPatchesTexture.push_back(texture);
            
        } catch (exception& e) {
            cout<<e.what()<<endl;
        }
        
    }
    
    for (int i = 0; i < 24; i++) {
        
        WaitPatchRef ref = WaitPatch::create(mPatchesTexture[i]);
        
        ref->setScale(0.5);//origin is 100px, change to 50px
        
        mPatches.push_back(ref);
        
        //add Random position for patch
        mPos = glm::vec2(ci::randFloat(ci::app::getWindowCenter().x + 200, ci::app::getWindowCenter().x - 200), -100) ;
        mPositions.push_back(mPos) ;
        mRandForces.push_back(glm::vec2(0, ci::randFloat(0.01,0.1))) ;
        mPatches[i]->setPosition(mPos) ;
        //        mPatches[i]->setDrawBounds(true) ;
        mPatches[i]->setAlignment(po::scene::Alignment::TOP_CENTER) ;
        
        
        addChild(mPatches[i]);
    }
    
    displayPatch = po::scene::Image::create(mPatchesTexture[0]);
    addChild(displayPatch);
    displayPatch->setScale(2.0) ;
    displayPatch->setPosition(glm::vec2(ci::app::getWindowCenter().x - 350 , ci::app::getWindowCenter().y)) ;
    //    displayPatch->setDrawBounds(true) ;
    displayPatch->setAlpha(0) ;
    displayPatch->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    
    displayText = po::scene::Shape::createRoundedRect(200.f, 100.f, 10.f) ;
    addChild(displayText) ;
    displayText->setAlpha(0) ;
    displayText->setFillColor(ci::Color::gray(0.5)) ;
    displayText->setAlignment(po::scene::Alignment::CENTER_LEFT) ;
    displayText->setPosition(glm::vec2(ci::app::getWindowCenter().x-250, ci::app::getWindowCenter().y)) ;
    
    closeText = po::scene::Shape::createRoundedRect(20.f, 20.f, 10.f) ;
    addChild(closeText) ;
    closeText->setAlpha(0) ;
    closeText->setFillColor(ci::Color::white()) ;
    closeText->setAlignment(po::scene::Alignment::CENTER_LEFT) ;
    closeText->setPosition(glm::vec2(ci::app::getWindowCenter().x-75, ci::app::getWindowCenter().y-35)) ;
    
    swirlingButtonEx = po::scene::Shape::createRect(100.f,100.f) ;
    addChild(swirlingButtonEx) ;
    swirlingButtonEx->setFillColor(ci::Color (1.f,0,0)) ;
    swirlingButtonEx->setAlignment(po::scene::Alignment::TOP_CENTER) ;
    swirlingButtonEx->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y+300)) ;
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Patch_Particles::onMouseEvent, this, std::placeholders::_1)) ;
    
    
}


void Patch_Particles::update()
{
    if(notSwirling == true) {
        for(int i = 0 ; i < 24 ; i++) {
            mVel *= mFriction ;
            mPositions[i] += mVel ;
            mPatches[i]->setPosition(mPositions[i]) ;
            if(mPatches[i]->getPosition().y > 1000) {
                mPositions[i] = glm::vec2(ci::randFloat(ci::app::getWindowCenter().x + 200, ci::app::getWindowCenter().x - 200), -100) ;
                mPatches[i]->setPosition(mPositions[i]) ;
            }
        }
    }
    else {
        if(doOnce == true) {
            for(int i = 0 ; i < 24 ; i++) {
                mPatches[i]->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y+300)) ;
                mVel = glm::vec2(0) ;
                mRandForces[i] = glm::vec2(0) ;
                //                std::cout << "THIS IS RUNNING" << std::endl ;
            }
            doOnce = false ;
        }
        float basicA = getElapsedFrames()*0.01f;
        for(int i = 0 ; i < 24 ; i++) {
            float angle = basicA + i * 2 ;
            float x = cos(angle)*350 + ci::app::getWindowCenter().x;
            std::cout<< x << std::endl ;
            float y = sin(angle)*350 + ci::app::getWindowCenter().y;
            //            gl::pushModelMatrix() ;
            //            gl::translate(ci::app::getWindowCenter()) ;
            mPatches[i]->setPosition(glm::vec2(x,y)) ;
            //            gl::popModelMatrix() ;
        }
    }
    
}


void Patch_Particles::addForce()
{
    for(int i = 0 ; i < 24 ; i++) {
        mVel += mRandForces[i] ;
    }
    
}

void Patch_Particles::onMouseEvent(po::scene::MouseEvent &event)
{
    switch(event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            //            mIsActivated = !mIsActivated ;
            
            for(int i = 0 ; i < 24 ; i++) {
                if(event.getWindowPos().x >= mPatches[i]->getPosition().x-50 && event.getWindowPos().x <= mPatches[i]->getPosition().x+50 && event.getWindowPos().y >= mPatches[i]->getPosition().y && event.getWindowPos().y <= mPatches[i]->getPosition().y+100) {
                    //                    std::cout << "I hit a patch!" << std::endl ;
                    displayPatch->setTexture(mPatchesTexture[i]) ;
                    ci::app::timeline().apply(&displayPatch->getAlphaAnim(), 1.f, 2.f, ci::EaseOutExpo()) ;
                    ci::app::timeline().apply(&displayText->getAlphaAnim(), 1.f, 2.f, ci::EaseOutExpo()) ;
                    ci::app::timeline().apply(&closeText->getAlphaAnim(), 1.f, 2.f, ci::EaseOutExpo()) ;
                }
            }
            if(event.getWindowPos().x >= closeText->getPosition().x && event.getWindowPos().x <= closeText->getPosition().x + 20.f && event.getWindowPos().y >= closeText->getPosition().y-10.f && getWindowPos().y <= closeText->getPosition().y+10.f) {
                //                std::cout << "Hit the close button!" << std::endl ;
                ci::app::timeline().apply(&displayPatch->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
                ci::app::timeline().apply(&displayText->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
                ci::app::timeline().apply(&closeText->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
            }
            if(event.getWindowPos().x >= swirlingButtonEx->getPosition().x-50 && event.getWindowPos().x <= swirlingButtonEx->getPosition().x+50 && event.getWindowPos().y >= swirlingButtonEx->getPosition().y && event.getWindowPos().y <= swirlingButtonEx->getPosition().y+100) {
                std::cout << "Time to SWIRL!" << std::endl ;
                //                for(int i = 0 ; i < 24 ; i++) {
                ////                    ci::app::timeline().apply(&mPatches[i]->getPositionAnim(), glm::vec2(ci::app::getWindowCenter(), 2.f)) ;
                ////                    ci::app::timeline().apply(&mPatches[i]->getPositionAnim(), 1.f, 2.f, ci::EaseOutExpo()) ;
                //                }
                swirl() ;
                ci::app::timeline().apply(&displayPatch->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
                ci::app::timeline().apply(&displayText->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
                ci::app::timeline().apply(&closeText->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
                ci::app::timeline().apply(&swirlingButtonEx->getAlphaAnim(), 0.f, 2.f, ci::EaseOutExpo()) ;
            }
            break ;
        default:
            break ;
    }
}

void Patch_Particles::swirl()
{
    notSwirling = false ;
    doOnce = true ;
}


