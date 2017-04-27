//
//  WaitPatch.cpp
//  Patch_Particles
//
//  Created by Aaron Lee on 4/21/17.
//
//

#include "WaitPatch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

WaitPatchRef WaitPatch::create(ci::gl::TextureRef patchTexture)
{
    WaitPatchRef ref = std::shared_ptr<WaitPatch>(new WaitPatch);
    ref->setup(patchTexture);
    return ref;
}

WaitPatch::WaitPatch()
{

}

void WaitPatch::setup(ci::gl::TextureRef patchTexture)
{
    mPatchexture = patchTexture;
    mPPatchImg = po::scene::Image::create(mPatchexture);
    addChild(mPPatchImg);
}
