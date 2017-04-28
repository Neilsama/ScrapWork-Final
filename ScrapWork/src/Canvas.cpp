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

void Canvas::setup(ci::gl::TextureRef   canvasTexture)
{
    mPCanvasImg = po::scene::Image::create(canvasTexture);
    mPCanvasImg->setPosition(mPosition);
    addChild(mPCanvasImg);
    
    for(int i = 0 ; i < 5 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            mPatches.push_back(po::scene::Shape::createRect(100.f,100.f)) ;
            mPatches[mCounter]->setPosition(428+100*i, 297+100*j) ;
            //            mPatches[mCounter]->setDrawBounds(true) ;
            mPatches[mCounter]->setAlpha(0.f) ;
            //        mPatches[i]->setFillColor(ci::gl::color(1.0,0,0)) ;
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
    //    for (int i = 0 ; i < 5 ; i++) {
    //        for(int j = 0 ; j < 4 ; j++) {
    //            if(i == hori && j == vert) {
    mPatches[getCounter]->setTexture(mTex) ;
    mPatches[getCounter]->setAlpha(1.f) ;
    //            }
    //            mCounter++ ;
    //        }
    //    }
    
    //    mCounter = 0 ;
}


Canvas::Canvas()
:mPosition(ci::vec2(426.f, 295.f))
{}
