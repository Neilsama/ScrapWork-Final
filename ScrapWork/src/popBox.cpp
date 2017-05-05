#include "popBox.h"

using namespace po::scene;

popBoxRef popBox::create(gl::TextureRef popBoxImg){
    popBoxRef ref = std::shared_ptr<popBox>(new popBox);
    ref -> setup(popBoxImg);
    return ref;
}

void popBox::setup(gl::TextureRef popBoxImg){
    
    mPopBoxTexture = popBoxImg;
    mPopBox = po::scene::Image::create(mPopBoxTexture);
    mPopBox->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mPopBox->setPosition(getWindowWidth()/2, getWindowHeight()/2 + 75.f);
    mPopBox->setDrawBounds(false) ;
    addChild(mPopBox);
    
    
}


void popBox::setToNormal()
{
    mPopBox->setAlpha(0.f);
}
