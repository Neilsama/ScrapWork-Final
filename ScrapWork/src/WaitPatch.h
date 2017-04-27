//
//  WaitPatch.hpp
//  Patch_Particles
//
//  Created by Aaron Lee on 4/21/17.
//
//

#pragma once
#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class WaitPatch;
typedef std::shared_ptr<WaitPatch> WaitPatchRef;

class WaitPatch
:public po::scene::NodeContainer
{
    
public:
    static WaitPatchRef create(ci::gl::TextureRef   patchTexture);
    
private:
    WaitPatch();
    void  setup(ci::gl::TextureRef   patchTexture);
    
    ci::gl::TextureRef      mPatchexture;
    po::scene::ImageRef     mPPatchImg;
    
};
