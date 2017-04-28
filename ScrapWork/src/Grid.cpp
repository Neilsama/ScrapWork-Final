//
//  Grid.cpp
//  Grid
//
//  Created by Aaron Lee on 4/21/17.
//
//

#include "Grid.h"

GridRef Grid::create()
{
    GridRef ref = std::shared_ptr<Grid> (new Grid()) ;
    ref->setup() ;
    return ref ;
}

Grid::Grid()
{
    //    this->setup() ;
}

void Grid::setup()
{
    readyToDraw = false ;
    gridSize = 3.f ;
    
    mPosition = glm::vec2(ci::app::getWindowCenter()) ;
    
    
    mGrid = po::scene::Shape::createRect(500.f, 400.f) ;
    mGrid->setPosition(glm::vec2(425.f, 295.f)) ;
    mGrid->setFillColor(ci::Color::white()) ;
    mGrid->setStrokeEnabled(true) ;
    mGrid->setStrokeColor(0, 0, 255.f) ;
    std::cout << mGrid->getStrokeColor() << std::endl ;
    //    mGrid->setStrokeColor(ci::Color (0,0,1.f)) ;
    //    mGrid->setDrawBounds(true) ;
    addChild(mGrid) ;
    mGridBox = po::scene::Shape::createRect(gridSize*100.f, gridSize) ;
    
    mClearButton = po::scene::Shape::createRoundedRect(100, 70, 10.f) ;
    addChild(mClearButton) ;
    mClearButton->setFillColor(ci::Color::gray(0.5f)) ;
    mClearButton->setPosition(glm::vec2(425.f, 195.f)) ;
    
    mDrawingButton = po::scene::Shape::createRoundedRect(100, 70, 10.f) ;
    addChild(mDrawingButton) ;
    mDrawingButton->setFillColor(ci::Color (0,.50,.70)) ;
    mDrawingButton->setPosition(glm::vec2(550.f, 195.f)) ;
    
    
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Grid::onMouseEvent, this, std::placeholders::_1)) ;
    getSignal(po::scene::MouseEvent::DRAG_INSIDE).connect(std::bind(&Grid::onMouseEvent, this, std::placeholders::_1)) ;
    
}

void Grid::update()
{
    for(int i = 0 ; i < mDrawing.size() ; i++) {
        addChild(mDrawing[i]) ;
    }
}


void Grid::drawOnGrid()
{
    
}


void Grid::clear()
{
    for(int i = mDrawing.size()-1 ; i > -1 ; i--) {
        removeChild(mDrawing[i]) ;
        mDrawing.pop_back() ;
        std::cout << mDrawing.size() << std::endl ;
    }
    
}

void Grid::onMouseEvent(po::scene::MouseEvent &event)
{
    switch(event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            if(event.getWindowPos().x >= mGrid->getPosition().x &&
               event.getWindowPos().x <= mGrid->getPosition().x+500.f &&
               event.getWindowPos().y >= mGrid->getPosition().y &&
               event.getWindowPos().y <= mGrid->getPosition().y+400.f) {
                std::cout << "its in the grid!" << std::endl ;
            }
            if(event.getWindowPos().x >= mClearButton->getPosition().x &&
               event.getWindowPos().x <= mClearButton->getPosition().x + 100.f &&
               event.getWindowPos().y >= mClearButton->getPosition().y &&
               event.getWindowPos().y <= mClearButton->getPosition().y + 70.f) {
                std::cout << "hit the clear button" << std::endl ;
                clear() ;
            }
            if(event.getWindowPos().x >= mDrawingButton->getPosition().x &&
               event.getWindowPos().x <= mDrawingButton->getPosition().x + 100.f &&
               event.getWindowPos().y >= mDrawingButton->getPosition().y &&
               event.getWindowPos().y <= mDrawingButton->getPosition().y + 70.f) {
                readyToDraw = !readyToDraw ;
                if(readyToDraw == true) {
                    mDrawingButton->setFillColor(ci::Color (1.0,0,0)) ;
                } else {
                    mDrawingButton->setFillColor(ci::Color(0,0.5,.70)) ;
                }
                
            }
            
            break ;
        case po::scene::MouseEvent::DRAG_INSIDE:
            if(readyToDraw == true) {
                if(event.getWindowPos().x >= mGrid->getPosition().x &&
                   event.getWindowPos().x <= mGrid->getPosition().x+500.f &&
                   event.getWindowPos().y >= mGrid->getPosition().y &&
                   event.getWindowPos().y <= mGrid->getPosition().y+400.f) {
                    mCircles = po::scene::Shape::createCircle(10.f) ;
                    mCircles->setPosition(glm::vec2(event.getWindowPos())) ;
                    mCircles->setFillColor(ci::Color::black()) ;
                    mCircles->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
                    mDrawing.push_back(mCircles) ;
                }
            }
            
        default:
            break ;
    }
}
