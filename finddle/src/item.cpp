//
//  item.cpp
//  handShadow
//
//  Created by PengCheng on 7/25/13.
//
//

#include "item.h"

item::item(){
    
    raduis = 26;
}

void item::setup(float x, float y){

    org.x = x;
    org.y = y;
    myType = NONE;
    int angle = (int)ofRandom(359);
    pos.x = (org.x)+60*cos(angle);
    pos.y = (org.y)+60*sin(angle);
    bCovered = false;
    timer = 0;
    
    bTimeSlower   = false;
    bDotExtender  = false;
    bDotFreezer   = false;
    bCoin         = false;
    bFixed        = true;
    
    typeDefinder();
    
//    cout<<myType<<endl;
//    cout<<coinChance<<" "<<timeSlowerChance<<" "<<dotExtenderChance<<"  "<<dotFreezerChance<<endl;
}

//---------------------------------------------------
void item::typeDefinder(){
    
    int value = (int)ofRandom(90);
    
    
    
    if (value>=0 && value <10+coinChance) {
        
        myType = COIN_MAKER;
        
    }
    else if(value>=30 && value < 30+timeSlowerChance){
    
        myType = TIME_SLOWER;

    }
    else if(value>=50 && value < 50+dotExtenderChance){
    
        myType = DOT_EXTENDER;

    }
    else if(value>=70 && value < 70+dotFreezerChance){
    
        myType = DOT_FREEZER;
        
    }
    else{
        
        myType = NONE;
    }
    
    
}

//---------------------------------------------------
void item::update(){
        
            
    if (!bFixed) {
        switch (myType) {
            case NONE:break;
                
            case TIME_SLOWER:
            {
                if (bCovered) {
                    bTimeSlower = true;
                    bCovered = false;
                    myType = NONE;
                }
            }break;
                
            case DOT_FREEZER:
            {
                if (bCovered) {
                    bDotFreezer = true;
                    bCovered = false;
                    myType = NONE;
                }
                
            }break;
                
            case DOT_EXTENDER:
            {
                if (bCovered) {
                    bDotExtender = true;
                    bCovered = false;
                    myType = NONE;
                }
                
            }break;
                
            case COIN_MAKER:
            {
                if (bCovered){
                    bCoin = true;
                    bCovered = false;
                    myType = NONE;
                }
            }break;
                
        }

    }
    
    
    
}

//---------------------------------------------------
void item::draw(){

  if (!bFixed) {         
    
    
    switch (myType) {
        case NONE:break;  
        case COIN_MAKER:
        {
            ofPushMatrix();
            ofTranslate(pos.x,pos.y);
//            ofSetColor(255, 0, 0,100);
//            ofCircle(0, 0, raduis);
//            ofSetColor(30, 30, 30);
//            ofCircle(0,0, 3);
            ofSetColor(255);
            itemImages[0]->draw(-itemImages[0]->getWidth()/2, -itemImages[0]->getHeight()/2);
            ofPopMatrix();
//            ofCircle(org,3);
//            ofLine(pos, org);
//            ofSetColor(30);
//            ofDrawBitmapString("Coin", pos);

        }break;
            
        case TIME_SLOWER:
        {
            ofPushMatrix();
            ofTranslate(pos.x,pos.y);
//            ofSetColor(0, 0, 255,100);
//            ofCircle(0, 0, raduis);
//            ofSetColor(30, 30, 30);
//            ofCircle(0,0, 3);
            ofSetColor(255);
            itemImages[1]->draw(-itemImages[0]->getWidth()/2, -itemImages[0]->getHeight()/2);

            ofPopMatrix();
//            ofCircle(org,3);
//            ofLine(pos, org);
//            ofSetColor(30);
//            ofDrawBitmapString("Timer", pos);
        }break;
            
        case DOT_EXTENDER:
        {
            ofPushMatrix();
            ofTranslate(pos.x,pos.y);
//            ofSetColor(0, 255, 0,100);
//            ofCircle(0, 0, raduis);
//            ofSetColor(30, 30, 30);
//            ofCircle(0,0, 3);
            ofSetColor(255);
            itemImages[2]->draw(-itemImages[0]->getWidth()/2, -itemImages[0]->getHeight()/2);

            ofPopMatrix();
//            ofCircle(org,3);
//            ofLine(pos, org);
//            ofSetColor(30);
//            ofDrawBitmapString("Extender", pos);

        }break;
            
        case DOT_FREEZER:
        {
            ofPushMatrix();
            ofTranslate(pos.x,pos.y);
//            ofSetColor(255, 255, 0,100);
//            ofCircle(0, 0, raduis);
//            ofSetColor(30, 30, 30);
//            ofCircle(0,0, 3);
            ofSetColor(255);
            itemImages[3]->draw(-itemImages[0]->getWidth()/2, -itemImages[0]->getHeight()/2);

            ofPopMatrix();
//            ofCircle(org,3);
//            ofLine(pos, org);
//            ofSetColor(30);
//            ofDrawBitmapString("Freezer", pos);
        }break;
            
    }
  
    
  }

}

//---------------------------------------------------
void item::touchDown(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bFixed) {
        bCovered = true;
    }
    
}

//---------------------------------------------------
void item::touchMove(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bFixed) {
         bCovered = true;
    }
    
}







