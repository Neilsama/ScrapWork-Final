//
//  Canvas.hpp
//  ScrapWork
//
//  Created by Neil on 4/24/17.
//
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"
#include "cinder/Signals.h"
#include "Patch.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class Canvas;
typedef std::shared_ptr<Canvas> CanvasRef;

class Canvas
:public po::scene::NodeContainer
{
    
public:
    static CanvasRef   create(ci::gl::TextureRef   canvasTexture);
    
private:
    Canvas();
    void setup(ci::gl::TextureRef   canvasTexture);
    
    ci::gl::TextureRef      mCanvasTexture;
    po::scene::ImageRef     mPCanvasImg;
    ci::vec2                mPosition;
    
    
};


#endif /* Canvas_hpp */
