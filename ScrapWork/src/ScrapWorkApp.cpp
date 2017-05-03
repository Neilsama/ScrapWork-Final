//Rosa was here


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

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrapWorkApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
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
    
    
    std::vector<int>           patchesQueue; //all id of patches that already add in canvas
    PatchRef                        newPatch; // when click on patch in grid, will generate a new patch
    int                             mCounter ;
    buttonMenuRef                   mButtonMenu ;
    po::scene::ImageRef             mClearButton ;
    
    
    Patch_ParticlesRef              mPatches ;
    float LIFE_SPAN = 500000 ;
    const float RANDOM_FORCE_RANGE = 0.005f ;
    
    std::vector<glm::vec2>          randomForces ;
};

void ScrapWorkApp::setup()
{
    ci::app::setWindowSize(1280.f, 800.f);
    //ci::app::setFullScreen();
    
    mCounter = 0 ;
    mainContainer = po::scene::NodeContainer::create();
    mScence = po::scene::Scene::create(mainContainer);
    bgPImg = po::scene::Image::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg.png"))));//  create background shape and load background image

    mainContainer->addChild(bgPImg);
    
    activeContainer = po::scene::NodeContainer::create();//  create boss container
    waitContainer = po::scene::NodeContainer::create();

    mainContainer->addChild(activeContainer);
    mainContainer->addChild(waitContainer);
    
    activeContainer->setVisible(false);
    
    
    // set up wait container
    
    mPatches = Patch_Particles::create(glm::vec2(0), glm::vec2(0)) ;
    waitContainer->addChild(mPatches) ;
    
    mPile = Pile::create();
    waitContainer->addChild(mPile);
    
    for(int i = 0 ; i < 24 ; i++) {
        randomForces.push_back(glm::vec2(0, ci::randFloat(1,2))) ;
    }
    
    
    // set up active container
    mSelectPatchPanel = SelectPatchPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_selectGrid.png"))));//  create select patch panel
    
    mPreviewPanel = PreviewPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_preview.png")))); //  create preview panel
    mCanvas = Canvas::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_canvas.png")))); //  create canvas
    
    activeContainer->addChild(mSelectPatchPanel);
    activeContainer->addChild(mPreviewPanel);
    activeContainer->addChild(mCanvas);

    // connect signal;
    for (int i = 0; i<mSelectPatchPanel->getPatchNum(); i++) {
        mSelectPatchPanel->getPatch(i)->getNewPatchSignal().connect(std::bind(&ScrapWorkApp::generateNewPatch,this, std::placeholders::_1));
    }
    
    mButtonMenu = buttonMenu::create() ;
    activeContainer->addChild(mButtonMenu) ;
    
    mPile->getChangeStatusSigal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this,std::placeholders::_1));
    
    mPreviewPanel->getButton()->getbuttonClickedSignal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this, std::placeholders::_1));
}

void ScrapWorkApp::generateNewPatch(int number)
{
    cout<<"generate a new patch"<<endl;
    newPatch = Patch::create(mSelectPatchPanel->getPatch(number)->getTexture());
    ci::app::timeline().apply(&newPatch->getPositionAnim(), mSelectPatchPanel->getPatch(number)->getPosition(), mSelectPatchPanel->getPatch(number)->getPosition()-ci::vec2(-10), 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getAlphaAnim(), 0.f, 1.f, 0.2f, EaseInAtan());
    ci::app::timeline().apply(&newPatch->getScaleAnim(), ci::vec2(0.f), ci::vec2(2.f), 0.2f, EaseInAtan());
    
    newPatch->setAsNew(true);
    newPatch->setID(mSelectPatchPanel->getPatchNum()+patchesQueue.size()+1);
    activeContainer->addChild(newPatch);
    
    newPatch->getIsInCavasSignal().connect(std::bind(&ScrapWorkApp::showOnCanvas, this,std::placeholders::_1));
}

void ScrapWorkApp::showOnCanvas(bool state)
{
    if (state) {
        if(newPatch->getIsNew()){
            patchesQueue.push_back(newPatch->getID());
            activeContainer->removeChild(newPatch);
            mCanvas->addChild(newPatch);
            cout<<"add a new patch:"<<newPatch->getID()<<endl;
            cout<<" now the size of patch queue is: "<<patchesQueue.size()<<endl;
            // newPatch
            for(int i = 0 ; i < 5 ; i++) {
                for(int j = 0 ; j < 4 ; j++) {
                    if(getMousePos().x >= (428+100*i) && getMousePos().x <= (528+100*i)
                       && getMousePos().y >= (297+100*j) && getMousePos().y <= (397+100*j)) {
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

void ScrapWorkApp::ChangeStatus(bool state)
{
    cout<<"activeContainer is visible? "<<activeContainer->isVisible()<<endl;
    cout<<"waitContainer is visible? "<<waitContainer->isVisible()<<endl;
    if (state) {
        if (waitContainer->isVisible()) {
            waitContainer->setVisible(false);
            mSelectPatchPanel->reset();
            mCanvas->reset();
            mPreviewPanel->reset();
            mPreviewPanel->getButton()->getbuttonClickedSignal().connect(std::bind(&ScrapWorkApp::ChangeStatus, this, std::placeholders::_1));
            activeContainer->setVisible(true);
            cout<<"already set active container true"<<endl;
        }
        else 
        {
            cout<<"here"<<endl;
            activeContainer->setVisible(false);
            
            mPile->reset();
            mPatches->reset();
            waitContainer->setVisible(true);
        }
    }
    else
        mPatches->swirl();
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
