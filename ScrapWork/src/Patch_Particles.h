//
//  Patch_Particles.hpp
//  Patch_Particles
//
//  Created by Aaron Lee on 4/19/17.
//
//


#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poImage.h"
#include "WaitPatch.h"
#include "cinder/Rand.h"

class Patch_Particles ;
typedef std::shared_ptr<Patch_Particles> Patch_ParticlesRef ;

class Patch_Particles : public po::scene::NodeContainer {
public:
    static Patch_ParticlesRef create(glm::vec2 position, glm::vec2 acceleration) ;
    Patch_Particles() ;
    void update() ;
    void addForce() ;
    glm::vec2 getPos() {return mPos ;}
    void swirl() ;
    
    
private:
    void setup(glm::vec2 position, glm::vec2 acceleration) ;
    
    void onMouseEvent(po::scene::MouseEvent &event) ;
    
    glm::vec2           mPos ;
    float               mFriction ;
    glm::vec2           mVel ;
    glm::vec2           mAcc ;
    bool                mIsActivated ;
    bool                notSwirling ;
    bool                doOnce ;
    
    float               mSwirl ;
    
    
    std::vector<glm::vec2>  mPositions ;
    std::vector<WaitPatchRef>   mPatches ;
    po::scene::ImageRef     displayPatch ;
    po::scene::ShapeRef     displayText ;
    po::scene::ShapeRef     closeText ;
    po::scene::ShapeRef     swirlingButtonEx ;
    
    std::vector<ci::gl::TextureRef>     mPatchesTexture;
    std::vector<glm::vec2>              mRandForces ;
    std::vector<ci::gl::TextureRef>     mText ;
    gl::TextureRef                      closeIconTexture;
    gl::TextureRef                      woolText ;
    gl::TextureRef                      denimText ;
    gl::TextureRef                      silkText ;
    gl::TextureRef                      linenText ;
};
