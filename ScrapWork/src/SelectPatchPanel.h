//
//  SelectPatchPanel.hpp
//  ScrapWork
//
//  Created by Neil on 4/20/17.
//
//

#ifndef SelectPatchPanel_h
#define SelectPatchPanel_h

#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"
#include "Patch.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class SelectPatchPanel;
typedef std::shared_ptr<SelectPatchPanel> SelectPatchPanelRef;

class SelectPatchPanel
:public po::scene::NodeContainer
{
    
public:
    static  SelectPatchPanelRef create(ci::gl::TextureRef   textureRef);
    PatchRef getPatch(int index){return mPatches[index];}
    int     getPatchNum(){return patchNum;}
    
private:
    SelectPatchPanel();
    void setup(ci::gl::TextureRef   textureRef);
    
    ci::gl::TextureRef      mGridTexture;
    po::scene::ImageRef     mPGridImg;
    
    int                     patchNum;
    std::vector<PatchRef>   mPatches;
    std::vector<ci::gl::TextureRef>     mPatchesTexture;

    
    
};

#endif /* SelectPatchPanel_h */

