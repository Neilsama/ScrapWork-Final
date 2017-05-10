//Rosa was here
//1280 by 1024
//Presentation
//Concept
//Process
//Highlights
//Live Demo
//Playtest

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


#include "scrapWorkController.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrapWorkApp : public App {
    
public:
    void setup() override;
    void update() override;
    void draw() override ;

    scrapWorkControllerRef          mController;
    
};

void ScrapWorkApp::setup()
{
    mController = scrapWorkController::create();
}


//  when clicked the patch, it will generate a new patch

void ScrapWorkApp::update()
{
    mController->update();
}


void ScrapWorkApp::draw()
{
    gl::clear( Color( 1, 1, 1 ) );
    mController->draw();
}

CINDER_APP( ScrapWorkApp, RendererGl )
