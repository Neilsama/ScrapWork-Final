//
//  scrapWorkController.hpp
//  ScrapWork
//
//  Created by Neil on 5/5/17.
//
//

#ifndef scrapWorkController_hpp
#define scrapWorkController_hpp

#include <stdio.h>
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

class scrapWorkController;
typedef std::shared_ptr<scrapWorkController> scrapWorkControllerRef;

class scrapWorkController {

public:
    static scrapWorkControllerRef  create();
    void    setup();
    void    update();
    void    draw();
 
private:
    scrapWorkController();
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
    po::scene::ShapeRef             mBlack ;
    
    
    std::vector<int>                patchesQueue; //all id of patches that already add in canvas
    PatchRef                        newPatch; // when click on patch in grid, will generate a new patch
    int                             mCounter ;
    buttonMenuRef                   mButtonMenu ;
    po::scene::ImageRef             mClearButton ;
    
    int                             statusCounter = 0 ;
    
    Patch_ParticlesRef              mPatches ;
    float LIFE_SPAN = 500000 ;
    const float RANDOM_FORCE_RANGE = 0.005f ;
    
    std::vector<glm::vec2>          randomForces ;

};

#endif /* scrapWorkController_hpp */
