//Rosa was here
//1280 by 1024
//Presentation
//Concept
//Process
//Highlights
//Live Demo
//Playtest

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene.h"
#include "poImage.h"
#include "poShape.h"
#include "poNodeContainer.h"

#include "SelectPatchPanel.h"
#include "Patch.h"
#include "PreviewPanel.hpp"
#include "Canvas.hpp"

#include "buttonMenu.h"
#include "Pile.h"
#include "Patch_Particles.h"

#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrapWorkApp : public App {
    
public:
    void setup() override;
    void update() override;
    void draw() override ;
    
    
    void generateNewPatch(int number);
    void showOnCanvas(bool state);
    void ChangeStatus(bool state);
    
    po::scene::SceneRef             mScence;
    
    po::scene::NodeContainerRef     mainContainer;
    
    po::scene::NodeContainerRef     activeContainer;
    po::scene::NodeContainerRef     waitContainer;
    
    PileRef                         mPile;
    
    po::scene::ShapeRef             bgShape; // background shape
    po::scene::ImageRef             bgPImg; // background image
    SelectPatchPanelRef             mSelectPatchPanel; //  select patch panel image
    PreviewPanelRef                 mPreviewPanel; //  preview panel
    CanvasRef                       mCanvas; // canvas image
    //po::scene::ShapeRef             mBlack ;
    
    
    std::vector<int>                patchesQueue; //all id of patches that already add in canvas
    PatchRef                        newPatch; // when click on patch in grid, will generate a new patch
    int                             mCounter ;
    buttonMenuRef                   mButtonMenu ;
    //po::scene::ImageRef             mClearButton ;
    bool                            firstTimeActive ;
    
    int                             statusCounter = 0 ;
    
    Patch_ParticlesRef              mPatches ;
    //float LIFE_SPAN = 500000 ;
    //const float RANDOM_FORCE_RANGE = 0.005f ;
    
    std::vector<glm::vec2>          randomForces ;
};

void ScrapWorkApp::setup()
{
    ci::app::setWindowSize(1280.f, 1024.f);
    
    firstTimeActive = true ;
    mCounter = 0 ;
    mainContainer = po::scene::NodeContainer::create();
    mScence = po::scene::Scene::create(mainContainer);
    
    bgPImg = po::scene::Image::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg.jpg"))));//  create background shape and load background image
    
    mainContainer->addChild(bgPImg);
    
    activeContainer = po::scene::NodeContainer::create();//  create boss container
    activeContainer->setAlpha(0.f);
    
    
    waitContainer = po::scene::NodeContainer::create();
    
    mainContainer->addChild(activeContainer);
    mainContainer->addChild(waitContainer);
    
    
    
    // set up wait container
    
    mPatches = Patch_Particles::create(glm::vec2(0), glm::vec2(0)) ;
    waitContainer->addChild(mPatches) ;
    
    mPile = Pile::create();
    waitContainer->addChild(mPile);
    
    
    // set up active container
    mSelectPatchPanel = SelectPatchPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_selectGrid.png"))));//  create select patch panel
    mSelectPatchPanel->setPosition(ci::vec2(0.f, -200.f));
    
    mPreviewPanel = PreviewPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_preview.png")))); //  create preview panel
    mPreviewPanel->setPosition(ci::vec2(-220.f, 220.f));
    
    
    mCanvas = Canvas::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_canvas.png")))); //  create canvas
    
    //    activeContainer->addChild(mSelectPatchPanel);
    //    activeContainer->addChild(mPreviewPanel);
    //    activeContainer->addChild(mCanvas);
    
    
    // connect signal;
    for (int i = 0; i<mSelectPatchPanel->getPatchNum(); i++) {
        mSelectPatchPanel->getPatch(i)->getNewPatchSignal().connect(std::bind(&ScrapWorkApp::generateNewPatch,this, std::placeholders::_1));
    }
    
    mButtonMenu = buttonMenu::create() ;
    mButtonMenu->setPosition(ci::vec2(1480.f, 0.f));
    //    activeContainer->addChild(mButtonMenu) ;
    
    mPile->getChangeStatusSigal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this,std::placeholders::_1));
    
    mPreviewPanel->getButton()->getbuttonClickedSignal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this, std::placeholders::_1));
}


//  when clicked the patch, it will generate a new patch
void ScrapWorkApp::generateNewPatch(int number)
{
    
    newPatch = Patch::create(mSelectPatchPanel->getPatch(number)->getTexture());
    ci::app::timeline().apply(&newPatch->getPositionAnim(), mSelectPatchPanel->getPatch(number)->getPosition(), mSelectPatchPanel->getPatch(number)->getPosition()-ci::vec2(-10), 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getAlphaAnim(), 0.f, 1.f, 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getScaleAnim(), ci::vec2(0.f), ci::vec2(2.f), 0.2f, EaseInAtan());
    
    newPatch->setAsNew(true);
    newPatch->setID(mSelectPatchPanel->getPatchNum()+patchesQueue.size()+1);
    activeContainer->addChild(newPatch);
    
    newPatch->getIsInCavasSignal().connect(std::bind(&ScrapWorkApp::showOnCanvas, this,std::placeholders::_1));
    
}

//  the function that show all the patches on the canvas. The patch will
//  stick to invisible grid automatically.
//  every
void ScrapWorkApp::showOnCanvas(bool state)
{
    if (state) {
        if(newPatch->getIsNew()){
            patchesQueue.push_back(newPatch->getID());
            activeContainer->removeChild(newPatch);
            mCanvas->addChild(newPatch);
            
            // newPatch
            for(int i = 0 ; i < 5 ; i++) {
                for(int j = 0 ; j < 4 ; j++) {
                    if(getMousePos().x >= (428+100*i) && getMousePos().x <= (528+100*i)
                       && getMousePos().y >= (337+100*j) && getMousePos().y <= (437+100*j)) {
                        mCanvas->setTexture(newPatch->getTexture(), mCounter) ;
                        mPreviewPanel->getPatches(newPatch->getTexture(), mCounter) ;
                        mCanvas->removeChild(newPatch) ;
                    }
                    mCounter++ ;
                    if(i == 4 && j == 3) {
                        mCounter = 0 ;
                    }
                }
            }
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
void ScrapWorkApp::ChangeStatus(bool state)
{
    
    
    if (state) {
        if (waitContainer->getAlpha() == 1.f) {
            
            waitContainer->setAlpha(0.f);
            waitContainer->removeAllChildren();
            
            activeContainer->setAlpha(1.f);
            
            mSelectPatchPanel->removeAllChildren();
            mSelectPatchPanel->reset();
            mSelectPatchPanel->setPosition(ci::vec2(0.f, -200.f));
            
            mCanvas->removeAllChildren();
            mCanvas->reset();
            mCanvas->setPosition(ci::vec2(0.f, 1124.f));
            
            mPreviewPanel->removeAllChildren();
            mPreviewPanel->reset();
            mPreviewPanel->setPosition(ci::vec2(-320.f, 0.f));
            
            mPreviewPanel->getButton()->getbuttonClickedSignal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this, std::placeholders::_1));
            
            mButtonMenu->setPosition(ci::vec2(1480.f, 0.f));
            
            
            
            activeContainer->addChild(mSelectPatchPanel);
            activeContainer->addChild(mCanvas);
            activeContainer->addChild(mPreviewPanel);
            activeContainer->addChild(mButtonMenu);
            
            
            
            ci::app::timeline().apply(&mSelectPatchPanel->getPositionAnim(), mSelectPatchPanel->getPosition(), ci::vec2(0.f, 20.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mPreviewPanel->getPositionAnim(), mPreviewPanel->getPosition(), ci::vec2(0.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mCanvas->getPositionAnim(), mCanvas->getPosition(), ci::vec2(0.f), 1.f, EaseInOutBack());
            ci::app::timeline().apply(&mButtonMenu->getPositionAnim(), mButtonMenu->getPosition(), ci::vec2(0),1.f, EaseInOutBack());
            cout<<"animation runed"<<activeContainer->isVisible()<< endl;
        }
        else
        {
            
            writeImage(getDocumentsDirectory()/fs::path("ScrapWorkApp_screenShot.png"), copyWindowSurface(cinder::Area (glm::vec2(58.f, 340.f), glm::vec2(354.f, 669.f)))) ;
            
            activeContainer->removeAllChildren();
            mButtonMenu->reset();
            activeContainer->setAlpha(0.f);
            
            
            waitContainer->addChild(mPatches);
            waitContainer->addChild(mPile);
            
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


void ScrapWorkApp::update()
{
    mScence->update();
    mPatches->update() ;
    mPatches->addForce() ;
}


void ScrapWorkApp::draw()
{
    gl::clear( Color( 1, 1, 1 ) );
    mScence->draw();
    
}

CINDER_APP( ScrapWorkApp, RendererGl )
