#pragma once

#include "poNodeContainer.h"
#include "Buttons.h"
#include "popBox.h"

class buttonMenu;
typedef std::shared_ptr<buttonMenu> buttonMenuRef;

class buttonMenu
:public po::scene::NodeContainer
{
public:
    static buttonMenuRef create();
    
    void setup();
    void updateMenuState(int number);
    void updatePopBoxState(int number);
    void mouseDown(po::scene::MouseEvent &event);
    
    bool boxIsActive;
    
    
private:
    ButtonsRef btn1;
    ButtonsRef btn2;
    ButtonsRef btn3;
    ButtonsRef btn4;
    
    gl::TextureRef btn1Texture;
    gl::TextureRef btn2Texture;
    gl::TextureRef btn3Texture;
    gl::TextureRef btn4Texture;
    
    gl::TextureRef btn1ActiveTexture;
    gl::TextureRef btn2ActiveTexture;
    gl::TextureRef btn3ActiveTexture;
    gl::TextureRef btn4ActiveTexture;
    
    popBoxRef popBox1;
    popBoxRef popBox2;
    popBoxRef popBox3;
    popBoxRef popBox4;
    
    gl::TextureRef popBox1Texture;
    gl::TextureRef popBox2Texture;
    gl::TextureRef popBox3Texture;
    gl::TextureRef popBox4Texture;
    
    po::scene::ImageRef closeIcon;
    gl::TextureRef closeIconTexture;
    
    
    
};
