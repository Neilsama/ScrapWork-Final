#pragma once

#include "poNodeContainer.h"
#include "poImage.h"
#include "Buttons.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class popBox;
typedef  std::shared_ptr<popBox> popBoxRef;



class popBox
:public po::scene::NodeContainer
{
public:
    
    static popBoxRef  create(gl::TextureRef popBoxImg);
    
    void setup(gl::TextureRef popBox);
    void setToNormal();
    
private:
    
    po::scene::ImageRef mPopBox;
    gl::TextureRef mPopBoxTexture;
    
    
};
