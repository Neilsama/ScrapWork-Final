//
//  PreviewPanel.hpp
//  ScrapWork
//
//  Created by Neil on 4/21/17.
//
//

#ifndef PreviewPanel_hpp
#define PreviewPanel_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"
#include "button.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class PreviewPanel;
typedef std::shared_ptr<PreviewPanel> PreviewPanelRef;

class PreviewPanel
:public po::scene::NodeContainer
{
    
public:
    static PreviewPanelRef  create(ci::gl::TextureRef   frameTexture);
    //void update();
    
private:
    PreviewPanel();
    void  setup(ci::gl::TextureRef   frameTexture);
    ci::gl::TextureRef      mFrameTexture;
    po::scene::ImageRef     mPFrameImg;
    po::scene::ShapeRef     mRect;
    
    buttonRef               btnSave;
};


#endif /* PreviewPanel_hpp */
