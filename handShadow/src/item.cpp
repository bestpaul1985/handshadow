//
//  item.cpp
//  handShadow
//
//  Created by PengCheng on 7/25/13.
//
//

#include "item.h"

item::item(){
    
    timeSlowerChance = 5;
    dotExtenderChance =5;
    dotFreezerChance =5;
    coinChance =10;
    raduis = 30;
}

void item::setup(ofPoint Pos){

    pos.x = Pos.x+(ofRandom(10, 50))*cos(ofRandom(360));
    pos.y = Pos.y+(ofRandom(10, 50))*sin(ofRandom(360));
    bCovered = false;
    timer = 0;
    
    bTimeSlowerChance   = false;
    bDotExtenderChance  = false;
    bDotFreezerChance   = false;
    bCoinChance         = false;
    bFixed              = true;
    
    typeDefinder();
    
}

//---------------------------------------------------
void item::typeDefinder(){
    
    int value = (int)ofRandom(79);
    
    if (value>=0 && value <coinChance) {
        
        myType = COIN_MAKER;
        
    }else if(value>=20 && value < 20+dotExtenderChance){
    
        myType = DOT_EXTENDER;

    }else if(value>=40 && value < 40+dotFreezerChance){
    
        myType = DOT_FREEZER;

    }else if(value>=60 && value < 60+timeSlowerChance){
    
        myType = TIME_SLOWER;
        
    }else{
        
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
                if (bCovered){
                    
                    timer++;
                    
                    if (timer<50) {
                        
                        bTimeSlowerChance = true;
                    }else{
                        
                        bTimeSlowerChance = false;
                    }
                }
                
            }break;
            
            case DOT_FREEZER:
            {
                if (bCovered){
                    timer++;
                    if (timer<50) {
                        
                        bDotFreezerChance = true;
                    }else{
                        
                        bDotFreezerChance = false;
                    }
                
                }
                
            }break;
                
            case DOT_EXTENDER:
            {
                if (bCovered){
                    timer++;
                    if (timer<50) {
                        
                        bDotExtenderChance = true;
                    }else{
                        
                        bDotExtenderChance = false;
                    }
                    
                }
            }break;
                
            case COIN_MAKER:
            {
                if (bCovered){
                    bCoinChance = true;
                    myType = NONE;
                }
            }break;
                
        }
    }
    
}

//---------------------------------------------------
void item::draw(){

    if (!bFixed && !bCovered && myType != NONE) {
            
            ofPushMatrix();
            ofTranslate(pos);
            ofSetColor(200, 30, 200);
            ofCircle(0, 0, 20);
            ofPopMatrix();
    }
    
}

//---------------------------------------------------
void item::touchDown(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bCovered&&!bFixed) {
        bCovered = true;
    }
    
}

//---------------------------------------------------
void item::touchMove(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bCovered &&!bFixed) {
         bCovered = true;
    }
    
}







