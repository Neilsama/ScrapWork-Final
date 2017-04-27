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

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrapWorkApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event )  override;
	void update() override;
	void draw() override;
    
    void generateNewPatch(int number);
    void showOnCanvas(bool state);
    
    po::scene::SceneRef             mScence;
    po::scene::NodeContainerRef     activeContainer;
    
    po::scene::ShapeRef             bgShape; // background shape
    po::scene::ImageRef             bgPImg; // background image
    SelectPatchPanelRef             mSelectPatchPanel; //  select patch panel image
    PreviewPanelRef                 mPreviewPanel; //  preview panel
    CanvasRef                          mCanvas; // canvas image
    
    
    std::vector<int>           patchesQueue; //all patches already add in play panel
    PatchRef                        newPatch;
};

void ScrapWorkApp::setup()
{
    ci::app::setWindowSize(1280.f, 800.f);
    
    
    activeContainer = po::scene::NodeContainer::create();//  create boss container
    mScence = po::scene::Scene::create(activeContainer);
    
    
    bgPImg = po::scene::Image::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg.png"))));//  create background shape and load background image
    
    mSelectPatchPanel = SelectPatchPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_selectGrid.png"))));//  create select patch panel
    //mSelectPatchPanel->setInteractionEnabled(true);
    
    mPreviewPanel = PreviewPanel::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_preview.png")))); //  create preview panel
    mCanvas = Canvas::create(ci::gl::Texture::create(ci::loadImage(loadAsset("bg_canvas.png")))); //  create canvas
    
    activeContainer->addChild(bgPImg);
    activeContainer->addChild(mSelectPatchPanel);
    activeContainer->addChild(mPreviewPanel);
    activeContainer->addChild(mCanvas);
    
    // connect signal;
    for (int i = 0; i<mSelectPatchPanel->getPatchNum(); i++) {
        mSelectPatchPanel->getPatch(i)->getNewPatchSignal().connect(std::bind(&ScrapWorkApp::generateNewPatch,this, std::placeholders::_1));
    }
    
}

void ScrapWorkApp::generateNewPatch(int number)
{
    cout<<"generate a new patch"<<endl;
    newPatch = Patch::create(mSelectPatchPanel->getPatch(number)->getTexture());
    newPatch->setAlpha(0.f);
//    newPatch->setPosition(mSelectPatchPanel->getPatch(number)->getPosition()-ci::vec2(-10));
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
            //cout<<"showOnCanvas signal state : "<<state<<endl;
        }
        else
            cout<<"still the patch in canvas"<<endl;
    }else{
        //cout<<"out of canvas"<<endl;
        if(newPatch->getIsNew())
            activeContainer->removeChild(newPatch);
        else
            mCanvas->removeChild(newPatch);
        
        cout<<"removed child"<<endl;
    }
    
}

void ScrapWorkApp::mouseDown( MouseEvent event )
{
//
//    if (mSelectPatchPanel->isInteractionEnabled()) {
//        for (int i = 0 ; i < mSelectPatchPanel->getPatchNum() ; i++) {
//            if (event.getX() > mSelectPatchPanel->getPatch(i)->getPosition().x
//                && event.getX() < mSelectPatchPanel->getPatch(i)->getPosition().x + 50
//                && event.getY() > mSelectPatchPanel->getPatch(i)->getPosition().y
//                && event.getY() < mSelectPatchPanel->getPatch(i)->getPosition().y+50) {
//                
//                // if generate a new patch
//                mSelectPatchPanel->setInteractionEnabled(false);
//                newPatch = Patch::create(mSelectPatchPanel->getPatch(i)->getTexture());
//                newPatch->setPosition(mSelectPatchPanel->getPatch(i)->getPosition());
//            
//                ci::app::timeline().apply(&newPatch->getScaleAnim(), newPatch->getScale(), newPatch->getScale()+ci::vec2(0.1), 0.3,ci::EaseOutQuad());
//            
//                newPatch->setNewOne(true);
//            
//                activeContainer->addChild(newPatch);
//                
//                }
//            }
//    }
}


void ScrapWorkApp::mouseUp(MouseEvent event)
{
//    // only when hold a patch, select panel is interaction false
//    if (!mSelectPatchPanel->isInteractionEnabled()) {
//
//        // if in play area
//        if (event.getX() > 426 && event.getX() < 926 && event.getY() > 295 && event.getY() < 695)
//        {
//            // if the patch is a new one
//            if(newPatch->isNew())
//            {// if the patch is a new one and drag in the play area
//                patchesQueue.push_back(newPatch);
//                newPatch->setNewOne(false);
//                
//            }else
//                ;// if the patch is not a new one, just change position, here is update position in position vector
//            
//        }
//        
//        // if not in play area, just fade out and delete child
//        else
//        {
//            // if patch not in play area
//            ci::app::timeline().apply(&newPatch->getAlphaAnim(),1.f ,0.f ,0.2 ,ci::EaseInSine());
//        }
//        cout<<"patchesQueue size : "<<patchesQueue.size()<<endl;
//        mSelectPatchPanel->setInteractionEnabled(true);
//    }
//    // if not holding a patch
//    else;
    
}


void ScrapWorkApp::update()
{
    mScence->update();
}

void ScrapWorkApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScence->draw();

}

CINDER_APP( ScrapWorkApp, RendererGl )
