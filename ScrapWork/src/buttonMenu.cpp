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
    btn1->setPosition(ci::vec2 (1046.f, 330.f));
    btn1->setID(1);
    addChild(btn1);
    
    
    btn2 = Buttons::create(btn2Texture, btn2ActiveTexture);
    btn2->setPosition(ci::vec2 (1046.f, 330 + 78.f));
    btn2->setID(2);
    addChild(btn2);
    
    
    btn3 = Buttons::create(btn3Texture, btn3ActiveTexture);
    btn3->setPosition(ci::vec2 (1046.f, 330 + (78 * 2)));
    btn3->setID(3);
    addChild(btn3);
    
    
    btn4 = Buttons::create(btn4Texture, btn4ActiveTexture);
    btn4->setPosition(ci::vec2 (1046.f, 330 + (78 * 3)));
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
    
    popBox1->setAlpha(0.f);
    popBox2->setAlpha(0.f);
    popBox3->setAlpha(0.f);
    popBox4->setAlpha(0.f);
    
    
    btn1->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updatePopBoxState, this, std::placeholders::_1));
    btn2->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updatePopBoxState, this, std::placeholders::_1));
    btn3->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updatePopBoxState, this, std::placeholders::_1));
    btn4->getbtnChangeStateSignal().connect(std::bind(&buttonMenu::updatePopBoxState, this, std::placeholders::_1));
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&buttonMenu::mouseDown, this, std::placeholders::_1)) ;
    
    closeIconTexture = gl::Texture::create(loadImage(loadAsset("close.png")));
    closeIcon = po::scene::Image::create(closeIconTexture);
    closeIcon ->setPosition(ci::vec2 (950.f, 200.f));
    closeIcon->setDrawBounds(false);
    closeIcon->setAlpha(0.f);
//    addChild(closeIcon);
    
}

void buttonMenu::updateMenuState(int number)
{
    switch (number) {
        case 1:
            cout<<"recieved signal 1"<<endl;
            btn2->setToNormal();
            btn3->setToNormal();
            btn4->setToNormal();
            
            break;
            
        case 2:
            cout<<"recieved signal 2"<<endl;
            btn1->setToNormal();
            btn3->setToNormal();
            btn4->setToNormal();
            break;
        case 3:
            cout<<"recieved signal 3"<<endl;
            btn1->setToNormal();
            btn2->setToNormal();
            btn4->setToNormal();
            break;
        case 4:
            cout<<"recieved signal 4"<<endl;
            btn1->setToNormal();
            btn2->setToNormal();
            btn3->setToNormal();
            break;
            
        default:
            break;
    }
}


void buttonMenu::updatePopBoxState(int number){
    switch (number) {
        case 1:
            cout<<"recieved popbox signal 1"<<endl;
            boxIsActive = true;
            if (boxIsActive){
                cout<<"box1 active"<<endl;
                closeIcon->setAlpha(1.f);
                cout << closeIcon->getPosition().x << endl ;
                addChild(popBox1) ;
                addChild(popBox2) ;
                addChild(popBox3) ;
                addChild(popBox4) ;
                addChild(closeIcon);
                popBox1->setAlpha(1.f) ;
                popBox2->setAlpha(0.f);
                popBox3->setAlpha(0.f);
                popBox4->setAlpha(0.f);
            }
            else{
                cout<<"box1 inactive"<<endl;
                popBox1->setAlpha(0.f);
            }
            break;
            
            
        case 2:
            cout<<"recieved popbox signal 2"<<endl;
            boxIsActive = true;;
            if (boxIsActive){
                cout<<"box2 active"<<endl;
                closeIcon->setAlpha(1.f);
                addChild(popBox1) ;
                addChild(popBox2) ;
                addChild(popBox3) ;
                addChild(popBox4) ;
                addChild(closeIcon);
                popBox2->setAlpha(1.f);
                popBox1->setAlpha(0.f);
                popBox3->setAlpha(0.f);
                popBox4->setAlpha(0.f);
            }
            else{
                cout<<"box2 inactive"<<endl;
                popBox2->setAlpha(0.f);
            }
            break;
            
        case 3:
            cout<<"recieved popbox signal 3"<<endl;
            boxIsActive = true;
            if (boxIsActive){
                cout<<"box3 active"<<endl;
                addChild(popBox1) ;
                addChild(popBox2) ;
                addChild(popBox3) ;
                addChild(popBox4) ;
                addChild(closeIcon);
                closeIcon->setAlpha(1.f);
                popBox3->setAlpha(1.f);
                popBox1->setAlpha(0.f);
                popBox2->setAlpha(0.f);
                popBox4->setAlpha(0.f);
            }
            else{
                cout<<"box3 inactive"<<endl;
                popBox3->setAlpha(0.f);
            }
            break;
            
        case 4:
            cout<<"recieved popbox signal 4"<<endl;
            boxIsActive = true;
            if (boxIsActive){
                cout<<"box4 active"<<endl;
                closeIcon->setAlpha(1.f);
                addChild(popBox1) ;
                addChild(popBox2) ;
                addChild(popBox3) ;
                addChild(popBox4) ;
                addChild(closeIcon);
                popBox4->setAlpha(1.f);
                popBox2->setAlpha(0.f);
                popBox3->setAlpha(0.f);
                popBox1->setAlpha(0.f);
            }
            else{
                cout<<"box1 active"<<endl;
                popBox4->setAlpha(0.f);
            }
            break;
            
        default:
            break;
    }
    
}

void buttonMenu::mouseDown( po::scene::MouseEvent &event ) {
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            
            if (boxIsActive == true){
                if (event.getWindowPos().x >= 950.f && event.getWindowPos().x <= 950.f+18 && event.getWindowPos().y >= 200.f  && event.getWindowPos().y <= 200.f + 18){
                    cout<<"box is closed"<<endl;
                    btn1->setToNormal();
                    btn2->setToNormal();
                    btn3->setToNormal();
                    btn4->setToNormal();
                    closeIcon->setAlpha(0.f);
                    removeChild(popBox1) ;
                    removeChild(popBox2) ;
                    removeChild(popBox3) ;
                    removeChild(popBox4) ;
                    removeChild(closeIcon) ;
                    
                }
            }
        default:
            break;
    }
}
