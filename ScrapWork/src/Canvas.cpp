//
//  Canvas.cpp
//  ScrapWork
//
//  Created by Neil on 4/24/17.
//
//

#include "Canvas.hpp"
using namespace ci;
using namespace ci::app;
using namespace std;

CanvasRef Canvas::create(ci::gl::TextureRef  canvasTexture)
{
    CanvasRef ref = std::shared_ptr<Canvas>(new Canvas);
    ref->setup(canvasTexture);
    return ref;
}

void Canvas::reset()
{
    setup(mCanvasTexture);
}

void Canvas::setup(ci::gl::TextureRef   canvasTexture)
{
    mCanvasTexture = canvasTexture;
    mPCanvasImg = po::scene::Image::create(mCanvasTexture);
    mPCanvasImg->setPosition(mPosition);
    addChild(mPCanvasImg);
    
    
    for(int i = 0 ; i < 5 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            mPatches.push_back(po::scene::Shape::createRect(100.f,100.f)) ;
            mPatches[mCounter]->setPosition(428+100*i, 297+100*j) ;
            mPatches[mCounter]->setAlpha(0.f) ;
            addChild(mPatches[mCounter]) ;
            mCounter++ ;
            if(i == 4 && j == 3) {
                mCounter = 0 ;
            }
        }
    }
}

void Canvas::setTexture(ci::gl::TextureRef mTex, int getCounter)
{
    mPatches[getCounter]->setTexture(mTex) ;
    mPatches[getCounter]->setAlpha(1.f) ;
}
Canvas::Canvas()
:mPosition(ci::vec2(426.f, 295.f))
{}
