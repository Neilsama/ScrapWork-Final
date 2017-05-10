//
//  scrapWorkController.cpp
//  ScrapWork
//
//  Created by Neil on 5/5/17.
//
//

#include "scrapWorkController.hpp"

scrapWorkControllerRef  scrapWorkController::create()
{
    scrapWorkControllerRef ref = std::shared_ptr<scrapWorkController>(new scrapWorkController);
    ref->setup();
    return ref;
}

scrapWorkController::scrapWorkController()
{}

void scrapWorkController::setup()
{  
    mCounter = 0 ;
    mainContainer = po::scene::NodeContainer::create();
    mScence = po::scene::Scene::create(mainContainer);
    
    bgPImg = po::scene::Image::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg.jpg"))));//  create background shape and load background image
    
    mainContainer->addChild(bgPImg);
    
//    activeContainer = po::scene::NodeContainer::create();//  create boss container
//    activeContainer->setAlpha(0.f);
    
    
    waitContainer = po::scene::NodeContainer::create();
    
    mainContainer->addChild(activeContainer);
    mainContainer->addChild(waitContainer);
    
    
    
    // set up wait container
    
    mPatches = Patch_Particles::create(glm::vec2(0), glm::vec2(0)) ;
    waitContainer->addChild(mPatches) ;
    
    mPile = Pile::create();
    waitContainer->addChild(mPile);
    
}


//  when clicked the patch, it will generate a new patch
void scrapWorkController::generateNewPatch(int number)
{
    
    newPatch = Patch::create(mSelectPatchPanel->getPatch(number)->getTexture());
    ci::app::timeline().apply(&newPatch->getPositionAnim(), mSelectPatchPanel->getPatch(number)->getPosition(), mSelectPatchPanel->getPatch(number)->getPosition()-ci::vec2(-10), 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getAlphaAnim(), 0.f, 1.f, 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getScaleAnim(), ci::vec2(0.f), ci::vec2(2.f), 0.2f, EaseInAtan());
    
    newPatch->setAsNew(true);
    newPatch->setID(mSelectPatchPanel->getPatchNum()+patchesQueue.size()+1);
    activeContainer->addChild(newPatch);
    
    newPatch->getIsInCavasSignal().connect(std::bind(&scrapWorkController::showOnCanvas, this,std::placeholders::_1));
    
}

//  the function that show all the patches on the canvas. The patch will
//  stick to invisible grid automatically.
//  every
void scrapWorkController::showOnCanvas(bool state)
{
    if (state) {
        if(newPatch->getIsNew()){
            patchesQueue.push_back(newPatch->getID());
            activeContainer->removeChild(newPatch);
            mCanvas->addChild(newPatch);
            
            // newPatch
//            for(int i = 0 ; i < 5 ; i++) {
//                for(int j = 0 ; j < 4 ; j++) {
//                    if(getMousePos().x >= (428+100*i) && getMousePos().x <= (528+100*i)
//                       && getMousePos().y >= (337+100*j) && getMousePos().y <= (437+100*j)) {
//                        mCanvas->setTexture(newPatch->getTexture(), mCounter) ;
//                        mPreviewPanel->getPatches(newPatch->getTexture(), mCounter) ;
//                        mCanvas->removeChild(newPatch) ;
//                    }
//                    mCounter++ ;
//                    if(i == 4 && j == 3) {
//                        mCounter = 0 ;
//                    }
//                }
//            }
        }
    }else{
        if(newPatch->getIsNew())
            activeContainer->removeChild(newPatch);
        else
            mCanvas->removeChild(newPatch);
    }
    
}


//  change application's status of waiting status and active status
//  connected to the signal of tow button triggers, one is save button signal "buttonClickedSignal" to change to
//  waiting page another one is pile introframe to change to active page
void scrapWorkController::ChangeStatus(bool state)
{
    
    if (state) {
        if (waitContainer->getAlpha() == 1.f) {
            
            waitContainer->setAlpha(0.f);
            waitContainer->removeAllChildren();
            
            mSelectPatchPanel->removeAllChildren();
            mSelectPatchPanel->reset();
            mSelectPatchPanel->setPosition(ci::vec2(0.f, -200.f));
            
            mCanvas->removeAllChildren();
            mCanvas->reset();
            mCanvas->setPosition(ci::vec2(0.f, 1124.f));
            
            mPreviewPanel->removeAllChildren();
            mPreviewPanel->reset();
            mPreviewPanel->setPosition(ci::vec2(-320.f, 0.f));
            
            mPreviewPanel->getButton()->getbuttonClickedSignal().connect(std::bind(&scrapWorkController::ChangeStatus, this, std::placeholders::_1));
            
            mButtonMenu->setPosition(ci::vec2(1480.f, 0.f));
            
            activeContainer->setAlpha(1.f);
            
            ci::app::timeline().apply(&mSelectPatchPanel->getPositionAnim(), mSelectPatchPanel->getPosition(), ci::vec2(0.f, 20.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mPreviewPanel->getPositionAnim(), mPreviewPanel->getPosition(), ci::vec2(0.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mCanvas->getPositionAnim(), mCanvas->getPosition(), ci::vec2(0.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mButtonMenu->getPositionAnim(), mButtonMenu->getPosition(), ci::vec2(0),1.f, EaseInOutBack());
            
        }
        else
        {
            
            writeImage(getDocumentsDirectory()/fs::path("ScrapWorkApp_screenShot.png"), copyWindowSurface(cinder::Area (glm::vec2(58.f, 340.f), glm::vec2(354.f, 669.f)))) ;
            waitContainer->setAlpha(1.f);
            
            activeContainer->setAlpha(0.f);
            activeContainer->removeAllChildren();
            
            mPile->removeAllChildren();
            mPile->reset();
            
            mPatches->removeAllChildren();
            mPatches->reset();
            ci::app::timeline().apply(&waitContainer->getAlphaAnim(), 0.f, 1.f,0.5f, EaseInAtan());
        }
    }
    else {
        mPatches->swirl();
    }
}


void scrapWorkController::update()
{
    mScence->update();
    mPatches->update() ;
    mPatches->addForce() ;
}

void scrapWorkController::draw()
{
    mScence->draw();
}







