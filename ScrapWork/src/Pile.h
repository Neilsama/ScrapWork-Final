#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poImage.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class Pile;
typedef std::shared_ptr<Pile> PileRef;

class Pile
:public po::scene::NodeContainer
{
public:
    static PileRef  create();
    void update();
    
private:
    Pile();
    void setup();
    void mousedown( po::scene::MouseEvent &event );
    void pileAnimation();
    
    
    
    gl::TextureRef          pileWaitTexture;
    gl::TextureRef          pileActive1Texture;
    gl::TextureRef          pileActive2Texture;
    gl::TextureRef          pileActive3Texture;
    gl::TextureRef          introTexture;
    
    po::scene::ImageRef     pileWaitImage;
    po::scene::ImageRef     pileActive1Image;
    po::scene::ImageRef     pileActive2Image;
    po::scene::ImageRef     pileActive3Image;
    po::scene::ImageRef     introImage;
    
    
};
