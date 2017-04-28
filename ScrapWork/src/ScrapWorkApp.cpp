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

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrapWorkApp : public App {
  public:
	void setup() override;
    void getPosInCanvas(int i, int j );
    void mouseUp(ci::app::MouseEvent event) override;
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
    CanvasRef                       mCanvas; // canvas image
    
    
    std::vector<int>           patchesQueue; //all id of patches that already add in canvas
    PatchRef                        newPatch; // when click on patch in grid, will generate a new patch
    int                             mCounter ;
    buttonMenuRef                   mButtonMenu ;
    po::scene::ImageRef             mClearButton ;
};

void ScrapWorkApp::setup()
{
    ci::app::setWindowSize(1280.f, 800.f);
    
    mCounter = 0 ;
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
    
    
    
    mButtonMenu = buttonMenu::create() ;
    activeContainer->addChild(mButtonMenu) ;
}

void ScrapWorkApp::generateNewPatch(int number)
{
    cout<<"generate a new patch"<<endl;
    newPatch = Patch::create(mSelectPatchPanel->getPatch(number)->getTexture());
    //    newPatch->setAlpha(0.f);
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
            //            newPatch
            for(int i = 0 ; i < 5 ; i++) {
                for(int j = 0 ; j < 4 ; j++) {
                    if(getMousePos().x >= (428+100*i) && getMousePos().x <= (528+100*i)
                       && getMousePos().y >= (297+100*j) && getMousePos().y <= (397+100*j)) {
                        mCanvas->setTexture(newPatch->getTexture(), mCounter) ;
                        //                        cout << "i is " << i << endl ;
                        //                        cout << "j is " << j << endl ;
                        //                        cout << "MouseX is " << getMousePos().x << endl ;
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

void ScrapWorkApp::mouseUp(ci::app::MouseEvent event)
{
//    ci::vec2 posInCanvas = ci::vec2(floor((event.getX() - 426.f)/100.f), floor((event.getY() - 259.f)/100.f));
//    cout <<"patch position is: ( "<<posInCanvas.x<<", "<<posInCanvas.y<<")"<<endl;
}

void ScrapWorkApp::getPosInCanvas(int i, int j )
{

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
