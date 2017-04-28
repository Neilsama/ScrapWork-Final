#include "buttonMenu.h"

using namespace po::scene;

buttonMenuRef buttonMenu::create()
{
    buttonMenuRef ref(new buttonMenu());
    ref->setup();
    return ref;
}

void buttonMenu::setup(){
    
    //btn setup
    
    btn1Texture = gl::Texture::create(loadImage(loadAsset("btn_FastFasion.png")));
    btn2Texture = gl::Texture::create(loadImage(loadAsset("btn_Biotextile.png")));
    btn3Texture = gl::Texture::create(loadImage(loadAsset("btn_Textile.png")));
    btn4Texture = gl::Texture::create(loadImage(loadAsset("btn_Dye.png")));
    
    btn1ActiveTexture = gl::Texture::create(loadImage(loadAsset("btn_FastFasion_active.png")));
    btn2ActiveTexture = gl::Texture::create(loadImage(loadAsset("btn_Biotextile_active.png")));
    btn3ActiveTexture = gl::Texture::create(loadImage(loadAsset("btn_Textile_active.png")));
    btn4ActiveTexture = gl::Texture::create(loadImage(loadAsset("btn_Dye_active.png")));

    btn1 = Buttons::create(btn1Texture, btn1ActiveTexture);
    btn1->setPosition(ci::vec2 (1046.f, 290.f));
    btn1->setID(1);
    addChild(btn1);
    
    
    btn2 = Buttons::create(btn2Texture, btn2ActiveTexture);
    btn2->setPosition(ci::vec2 (1046.f, 290 + 78.f));
    btn2->setID(2);
    addChild(btn2);
    
    
    btn3 = Buttons::create(btn3Texture, btn3ActiveTexture);
    btn3->setPosition(ci::vec2 (1046.f, 290 + (78 * 2)));
    btn3->setID(3);
    addChild(btn3);
    
    
    btn4 = Buttons::create(btn4Texture, btn4ActiveTexture);
    btn4->setPosition(ci::vec2 (1046.f, 290 + (78 * 3)));
    btn4->setID(4);
    addChild(btn4);
   
    
    btn1->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updateMenuState, this, std::placeholders::_1));
    btn2->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updateMenuState, this, std::placeholders::_1));
    btn3->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updateMenuState, this, std::placeholders::_1));
    btn4->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updateMenuState, this, std::placeholders::_1));

    //popBox setup
    
    popBox1Texture = gl::Texture::create(loadImage(loadAsset("FastFashion_popbox.png")));
    popBox2Texture = gl::Texture::create(loadImage(loadAsset("Biotextile_popbox.png")));
    popBox3Texture = gl::Texture::create(loadImage(loadAsset("Textile_popbox.png")));
    popBox4Texture = gl::Texture::create(loadImage(loadAsset("Dye_popbox.png")));
    
    popBox1 = popBox::create(popBox1Texture);
    popBox2 = popBox::create(popBox2Texture);
    popBox3 = popBox::create(popBox3Texture);
    popBox4 = popBox::create(popBox4Texture);
    addChild(popBox1);
    addChild(popBox2);
    addChild(popBox3);
    addChild(popBox4);


}

void buttonMenu::updateMenuState(int number)
{
    switch (number) {
        case 1:
            cout<<"recieved signal 1"<<endl;
            popBox1->setAlpha(1.f);
            popBox2->setAlpha(0.f);
            popBox3->setAlpha(0.f);
            popBox4->setAlpha(0.f);
            btn2->setToNormal();
            btn3->setToNormal();
            btn4->setToNormal();
           
            break;

        case 2:
            cout<<"recieved signal 2"<<endl;
            popBox2->setAlpha(1.f);
            popBox1->setAlpha(0.f);
            popBox3->setAlpha(0.f);
            popBox4->setAlpha(0.f);
            btn1->setToNormal();
            btn3->setToNormal();
            btn4->setToNormal();
            break;
        case 3:
            cout<<"recieved signal 3"<<endl;
            popBox3->setAlpha(1.f);
            popBox1->setAlpha(0.f);
            popBox2->setAlpha(0.f);
            popBox4->setAlpha(0.f);
            btn1->setToNormal();
            btn2->setToNormal();
            btn4->setToNormal();
            break;
        case 4:
            cout<<"recieved signal 4"<<endl;
            popBox4->setAlpha(1.f);
            popBox1->setAlpha(0.f);
            popBox2->setAlpha(0.f);
            popBox3->setAlpha(0.f);
            btn1->setToNormal();
            btn2->setToNormal();
            btn3->setToNormal();
            break;

        default:
            break;
    }
}














