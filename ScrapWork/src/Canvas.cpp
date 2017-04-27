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
}

Canvas::Canvas()
:mPosition(ci::vec2(426.f, 295.f))
{}
