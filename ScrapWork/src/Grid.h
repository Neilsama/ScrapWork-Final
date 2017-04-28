//
//  Grid.hpp
//  Grid
//
//  Created by Aaron Lee on 4/21/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"

class Grid ;
typedef std::shared_ptr<Grid> GridRef ;

class Grid : public po::scene::NodeContainer {
public:
    static GridRef create() ;
    Grid() ;
    void clear() ;
    
    void drawOnGrid() ;
    void setup() ;
    void update() ;
    
    
    
    
private:
    int gridSize ;
    int min ;
    int max ;
    void onMouseEvent(po::scene::MouseEvent &event) ;
    //    bool readyToPopTheDrawing ;
    bool readyToDraw ;
    
    po::scene::ShapeRef     mGrid ;
    po::scene::ShapeRef     mGridBox ;
    po::scene::ShapeRef     mClearButton ;
    po::scene::ShapeRef     mDrawingButton ;
    po::scene::ShapeRef     mClearAll ;
    
    po::scene::ShapeRef              mCircles ;
    std::vector<po::scene::ShapeRef> mDrawing ;
    
    glm::vec2               mPosition ;
};
