//
//  Patch.cpp
//  ScrapWork
//
//  Created by Neil on 4/21/17.
//
//

#include "Patch.h"
using namespace ci;
using namespace ci::app;
using namespace std;

PatchRef Patch::create(ci::gl::TextureRef patchTexture)
{
    PatchRef ref = std::shared_ptr<Patch>(new Patch);
    ref->setup(patchTexture);
    return ref;
}

Patch::Patch()
:mScale(ci::vec2(0.5))
,isNew(false)
{}

void Patch::setup(ci::gl::TextureRef patchTexture)
{
    mPatchexture = patchTexture;
    mPPatchImg = po::scene::Image::create(mPatchexture);
    mPPatchImg->setScale(normalScale);
    
    addChild(mPPatchImg);
    
    //connect signal
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Patch::onMouseEvent, this, std::placeholders::_1));
    getSignal(po::scene::MouseEvent::UP_INSIDE).connect(std::bind(&Patch::onMouseEvent, this, std::placeholders::_1));
    getSignal(po::scene::MouseEvent::DRAG_INSIDE).connect(std::bind(&Patch::onMouseEvent, this, std::placeholders::_1));

}


void Patch::onMouseEvent(po::scene::MouseEvent &event)
{
    ci::vec2    mousePos = event.getWindowPos();
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
        {
            // check mouse is in grid
            if (mousePos.y <= 180)
            {
                mNewPatchSignal.emit(mID);
                //cout<<"patch in grid"<<endl;
                
            }else if (mousePos.x >= 426 && mousePos.x <= 930 && mousePos.y >= 295 && mousePos.y <= 696)
            {
                isNew = false;
                //cout<<"patch in canvas"<<endl;
            }
            
            break;
        }
            
        case po::scene::MouseEvent::UP_INSIDE:
        {
            if (mousePos.x >= 426 && mousePos.x <= 930 && mousePos.y >= 295 && mousePos.y <= 696)
            {
                mIsInCanvasSignal.emit(true);
                //cout<<"released in canvas"<<endl;
            }
            else{
                mIsInCanvasSignal.emit(false);
                //cout<<"released out of canvas"<<endl;
            }
            break;
        
        }
            
        case po::scene::MouseEvent::DRAG_INSIDE:
        {
            mPPatchImg->setPosition(event.getLocalPos() - ci::vec2(25));
            break;
        }
                
            default:
                break;
        }

    
}










