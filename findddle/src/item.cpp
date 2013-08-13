//
//  item.cpp
//  handShadow
//
//  Created by PengCheng on 7/25/13.
//
//

#include "item.h"


void item::setup(ofPoint *Org){
    
    raduis = 26;
    org = Org;
    myType = NONE;
   
    bCovered = false;
    timer = 0;
    
    bTimeSlower   = false;
    bDotExtender  = false;
    bDotFreezer   = false;
    bCoin         = false;
    bFixed        = true;
    
    typeDefinder();
    angle = (int)ofRandom(359);
    
    
//    cout<<coinChance<<" "<<timeSlowerChance<<" "<<dotExtenderChance<<"  "<<dotFreezerChance<<endl;
    
    
}

//---------------------------------------------------
void item::typeDefinder(){
    
    int value = (int)ofRandom(90);
        
    if (value>=0 && value <10+coinChance) {
        
        myType = COIN_MAKER;
        
    }
    else if(value>30 && value < 30+timeSlowerChance){
    
        myType = TIME_SLOWER;

    }
    else if(value>50 && value < 50+dotExtenderChance){
    
        myType = DOT_EXTENDER;

    }
    else if(value>70 && value < 70+dotFreezerChance){
    
        myType = DOT_FREEZER;
        
    }
    else{
        
        myType = NONE;
    }
    
//    cout<<myType<<endl;
   
}

//---------------------------------------------------
void item::touchDown(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bFixed && !bCovered) {
        bCovered = true;
        
        if (myType == COIN_MAKER) {
            bCoin = true;
        }else if (myType == DOT_FREEZER){
            bDotFreezer = true;
        }else if (myType == DOT_EXTENDER){
            bDotExtender = true;
        }else if (myType == TIME_SLOWER){
            bTimeSlower = true;
        }
    }
    
}

//---------------------------------------------------
void item::touchMove(int x, int y, int touchId){
    ofPoint touch(x,y);
    if (touch.distance(pos)<raduis && !bFixed && !bCovered) {
        bCovered = true;
        if (myType == COIN_MAKER) {
            bCoin = true;
        }else if (myType == DOT_FREEZER){
            bDotFreezer = true;
        }else if (myType == DOT_EXTENDER){
            bDotExtender = true;
        }else if (myType == TIME_SLOWER){
            bTimeSlower = true;
        }
    }
}

//---------------------------------------------------
void item::update(){

    pos.x = (org->x)+60*cos(angle);
    pos.y = (org->y)+60*sin(angle);
    
}





