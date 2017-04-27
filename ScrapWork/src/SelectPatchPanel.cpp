//
//  SelectPatchPanel.cpp
//  ScrapWork
//
//  Created by Neil on 4/20/17.
//
//

#include "SelectPatchPanel.h"
using namespace ci;
using namespace ci::app;
using namespace std;

SelectPatchPanelRef SelectPatchPanel::create(ci::gl::TextureRef textureRef)
{
    SelectPatchPanelRef ref = std::shared_ptr<SelectPatchPanel>(new SelectPatchPanel);
    ref->setup(textureRef);
    return ref;
}

SelectPatchPanel::SelectPatchPanel()
{}

void SelectPatchPanel::setup(ci::gl::TextureRef textureRef)
{
    mGridTexture = textureRef;
    mPGridImg = po::scene::Image::create(mGridTexture);
    addChild(mPGridImg);
    
    patchNum = 24;
    
    for (int i = 0; i < patchNum; i++) {
        string  filePath = "patches/" + to_string(i+1) + ".jpg";
        try {
            
            // load pathes image into vector
            ci::gl::TextureRef  texture = ci::gl::Texture::create(loadImage(loadAsset(filePath)));
            mPatchesTexture.push_back(texture);
            
        } catch (exception& e) {
            cout<<e.what()<<endl;
        }
        
    }
    // put patch texture into patch ref
    for (int i = 0; i < patchNum; i++) {
        
        PatchRef ref = Patch::create(mPatchesTexture[i]);
        mPatches.push_back(ref);
        mPatches[i]->setID(i);
        
        //append to select Panel
        if (i < 6)
            mPatches[i]->setPosition(ci::vec2(182 + 78*i, 40));
        else if (i >= 6 && i < 12)
            mPatches[i]->setPosition(ci::vec2(205 + 78*i, 40));
        else if (i >= 12 && i< 18)
            mPatches[i]->setPosition(ci::vec2(182 + 78*(i-12),113));
        else
            mPatches[i]->setPosition(ci::vec2(205 + 78*(i-12),113));
                
        addChild(mPatches[i]);
    }
   
}

