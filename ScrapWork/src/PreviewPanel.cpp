//
//  PreviewPanel.cpp
//  ScrapWork
//
//  Created by Neil on 4/21/17.
//
//

#include "PreviewPanel.hpp"
#include "poShape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PreviewPanelRef PreviewPanel::create(ci::gl::TextureRef frameTexture)
{
    PreviewPanelRef ref = std::shared_ptr<PreviewPanel>(new PreviewPanel);
    ref->setup(frameTexture);
    return ref;
}

PreviewPanel::PreviewPanel(){}

void PreviewPanel::setup(ci::gl::TextureRef frameTexture)
{
    // load preview panel frame picture
    mFrameTexture = frameTexture;
    mPFrameImg = po::scene::Image::create(frameTexture);
    mPFrameImg->setPosition(ci::vec2(0, 180));
    
    //  add bag outline
    mRect = po::scene::Shape::createRect(220, 176);
    mRect->setStrokeEnabled(true);
    mRect->setStrokeColor(ci::Color::hex(0xfefefe));
    mRect->setPosition(ci::vec2(97, 434));
    
    btnSave = button::create(ci::gl::Texture::create(loadImage(loadAsset("btn_save.png"))),ci::gl::Texture::create(loadImage(loadAsset("btn_save_active.png"))));
    btnSave->setPosition(ci::vec2(54,650));
    
    
    addChild(mPFrameImg);
    addChild(mRect);
    addChild(btnSave);
}
