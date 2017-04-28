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
    
    for(int i = 0 ; i < 5 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            mPrevPatch.push_back(po::scene::Shape::createRect(44.f,44.f)) ;
            mPrevPatch[mCounter]->setPosition(97+44*i, 434+44*j) ;
            //            mPrevPatch[mCounter]->setDrawBounds(true) ;
            mPrevPatch[mCounter]->setAlpha(0.f) ;
            addChild(mPrevPatch[mCounter]) ;
            mCounter++ ;
            if(i == 4 && j == 3) {
                mCounter = 0 ;
            }
        }
    }
}

void PreviewPanel::getPatches(ci::gl::TextureRef mTex, int getCounter)
{
    //    for(int i = 0 ; i < 5 ; i++) {
    //        for(int j = 0 ; j < 4 ; j++) {
    mPrevPatch[getCounter]->setTexture(mTex, po::scene::TextureFit::Type::EXACT) ;
    mPrevPatch[getCounter]->setAlpha(1.0) ;
    //            mCounter++ ;
    //            if(i == 4 && j == 3) {
    //                mCounter = 0 ;
    //            }
    //        }
    //    }
}

