//
//  menu.cpp
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#include "menu.h"

//-------------------------------------------------------
void menu::setup(){

    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 40);
    
    mainMenuBg.loadImage("assets/images/mainMenu/mainMenuBg.png");
    button[0].loadImage("assets/images/mainMenu/Tutorial.png");
    buttonOver[0].loadImage("assets/images/mainMenu/Tutorial_b.png");
    background[0].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[1].loadImage("assets/images/mainMenu/Play.png");
    buttonOver[1].loadImage("assets/images/mainMenu/Play_b.png");
    background[1].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[2].loadImage("assets/images/mainMenu/Levels.png");
    buttonOver[2].loadImage("assets/images/mainMenu/Levels_b.png");
    background[2].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[3].loadImage("assets/images/mainMenu/Store.png");
    buttonOver[3].loadImage("assets/images/mainMenu/Store_b.png");
    background[3].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[4].loadImage("assets/images/mainMenu/Setting.png");
    buttonOver[4].loadImage("assets/images/mainMenu/Setting_b.png");
    background[4].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    hidenLogo.loadImage("assets/images/mainMenu/hidenLogo.png");
    imgLockedLevel.loadImage("assets/images/mainMenu/lock.png");
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].button = &button[i];
        mainMenuRect[i].buttonTouchOver = &buttonOver[i];
        mainMenuRect[i].background = &background[i];
        
        mainMenuRect[i].rectW = button[i].getWidth();
        mainMenuRect[i].rectH = button[i].getHeight();

    }
    
    
    reset();
    bSave = false;
    levelReset();
    purchaseSetup();
    setSetup();

}

//-------------------------------------------------------
void menu::update(){
    
    if(bSnapIn){
        snapIn();
    }
    else if (bSubMenu) {
        subMenu(subMenuNum);
        levelUpdate();
        purchaseUpdate();
        
    }
    else{
        drag();
    }
 
}

//-------------------------------------------------------
void menu::hiden(){
    
    float catchUpSpeed = 0.08f;
    float catchX = 36;
    
    if (!bHidenLogo) {
         if(mParticle.pos.x < 36){
            mParticle.pos.x = 36;
        }
    }
    
    if(!bDrag && bHidenLogo){
        frc.x = 0;
        mParticle.pos.x = (1-catchUpSpeed)*mParticle.pos.x + catchUpSpeed * catchX;
        if (mParticle.pos.x >35) {
            bHidenLogo = false;
        }
        
    }

}

//-------------------------------------------------------
void menu::reset(){
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].posa.x = 1000+ 100*i;
        mainMenuRect[i].posa.y = 0;
        mainMenuRect[i].posb.x = 300*i;
        mainMenuRect[i].posb.y = 0;
        mainMenuRect[i].posc.x = 0;
        mainMenuRect[i].posc.y = 0;
        mainMenuRect[i].shaper = 1.5;
        mainMenuRect[i].interpolateByPct(0);
        mainMenuRect[i].pct = 0;
        mainMenuRect[i].pos =  mainMenuRect[i].posa;
        pct[i] = 0;
    }
    
    
    speed = 0.05f;
    counter = 1;
    bSnapIn = true;
    bHidenLogo = false;
    bShowHidenLogo = false;
    bDrag = false;
    bSubMenu = false;
    touch.set(0, 0);
    preTouch = touch;
    frc.set(0, 0);

    mParticle.setInitialCondition(512, 384, 0, 0);
    preParticlePos = mParticle.pos;
    
    subMenuNum = -1;
    subStep = 0;
    timer =0;
    
    mainMenuBgPos.set(0, 0);
}

//-------------------------------------------------------
void menu::draw(){
    
    
    if (!bSubMenu && bShowHidenLogo) {
        ofSetColor(255);
        hidenLogo.draw(ofGetWidth()-168,0);
    }
    
    ofSetColor(255);
    mainMenuBg.draw(mainMenuBgPos);
    
   
    //subMenu draw
    
    levelDraw();
    purchaseDraw();
    setDraw();
    
   
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        ofSetColor(255);
        mainMenuRect[i].draw();
    }

}

//********-----------------------------------------------
void menu::touchDown(int x, int y, int touchID){
    
    dragDown(x, y, touchID);
    levelDown(x, y, touchID);
    setTouchDown(x, y);
    purchaseTouchDown(x, y);
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        if (mainMenuRect[i].buttonRect.inside(x, y)) {
            mainMenuRect[i].bTouchOver = true;
        }
    }
    
    
    
}

//-------------------------------------------------------
void menu::touchMove(int x, int y, int touchID){
    
    dragMove(x, y, touchID);
    levelMove(x, y, touchID);
    setTouchMove(x, y);
    purchaseTouchMove(x, y);
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        if (mainMenuRect[i].buttonRect.inside(x, y)) {
            mainMenuRect[i].bTouchOver = true;
        }else{
            mainMenuRect[i].bTouchOver = false;
        }
    }
    
    
    
}

//-------------------------------------------------------
void menu::touchUp(int x, int y, int touchID){
    
    dragUp(x, y, touchID);
    subMenuUp(x,y,touchID);
    levelUp(x,y,touchID);
    setTouchUp(x, y);
    purchaseTouchUp(x, y);
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        if (mainMenuRect[i].buttonRect.inside(x, y)) {
            mainMenuRect[i].bTouchOver = false;
        }
    }
    
}

//********-----------------------------------------------
void menu::subMenu(int num){
    
    vector<float> postion;
    
    if (num == 0) {
        float temp;
        temp = 0;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        
    }
    else if (num == 2) {
        float temp;
        temp = -600;
        postion.push_back(temp);
        temp = -300;
        postion.push_back(temp);
        temp = 0;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        
    }
    else if (num == 3) {
        float temp;
        temp = -900;
        postion.push_back(temp);
        temp = -600;
        postion.push_back(temp);
        temp = -300;
        postion.push_back(temp);
        temp = 0;
        postion.push_back(temp);
        temp = ofGetWidth()+10;
        postion.push_back(temp);
        
    }else if (num == 4) {
        float temp;
        temp = -1200;
        postion.push_back(temp);
        temp = -900;
        postion.push_back(temp);
        temp = -600;
        postion.push_back(temp);
        temp = -300;
        postion.push_back(temp);
        temp = 0;
        postion.push_back(temp);
    }
    
    
    if (subStep == 0){
        for (int i=0; i<5; i++) pct[i] =0;
        for (int i=0; i<MAIN_MENU_BUTTON; i++)mainMenuRect[i].posc.x = postion[i];
        subStep = 1;
    }
    else if (subStep == 1) {
        for (int i=0; i<MAIN_MENU_BUTTON; i++) {
            pct[i] += speed;
            if (pct[i]>1) pct[i] = 1;
            mainMenuRect[i].interpolateByPct2(pct[i]);
        }
        
        if (pct[MAIN_MENU_BUTTON-1] == 1) subStep = 2;
        
    }
    else if(subStep == 4){
        for (int i=0; i<5; i++) pct[i] =0;
        for (int i=0; i<MAIN_MENU_BUTTON; i++)mainMenuRect[i].posc.x = tempRectPos[i];
        subStep = 5;
    }
    
    else if(subStep == 5){
        for (int i=0; i<MAIN_MENU_BUTTON; i++) {
            pct[i] += speed;
            if (pct[i]>1) pct[i] = 1;
            mainMenuRect[i].interpolateByPct2(pct[i]);
        }
        
        if (pct[MAIN_MENU_BUTTON-1] == 1 ) {
            bSubMenu = false;
            subStep = 0;
            
            if (subMenuNum == 2) {
                levelReset();
            }
            
            subMenuNum = -1;
            
        }
        
        
    }
    
    
}

//-------------------------------------------------------
void menu::subMenuUp(int x, int y, int touchID){

    if (subStep == 0 && !bSubMenu) {
        if (mainMenuRect[0].buttonRect.inside(x, y)) {
            bSubMenu = true;
            subMenuNum = 0;
            mainMenuRect[0].bTouchOver = false;
            tempRectPos.clear();
            for (int i=0; i<MAIN_MENU_BUTTON; i++){
                float temp = mainMenuRect[i].pos.x;
                tempRectPos.push_back(temp);
            }
        }
        
        if (mainMenuRect[1].buttonRect.inside(x, y)) {
            if (*firstPlay==0) {
                *scene = 1;
            }else if(*firstPlay == 1){
                *scene = 2;
            }
            mainMenuRect[1].bTouchOver = false;
            reset();
        }
        
        if (mainMenuRect[2].buttonRect.inside(x, y)) {
            bSubMenu = true;
            subMenuNum = 2;
            mainMenuRect[2].bTouchOver = false;
            tempRectPos.clear();
            for (int i=0; i<MAIN_MENU_BUTTON; i++){
                float temp = mainMenuRect[i].pos.x;
                tempRectPos.push_back(temp);
            }
        }
        
        if (mainMenuRect[3].buttonRect.inside(x, y)) {
            bSubMenu = true;
            subMenuNum = 3;
            mainMenuRect[3].bTouchOver = false;
            tempRectPos.clear();
            for (int i=0; i<MAIN_MENU_BUTTON; i++){
                float temp = mainMenuRect[i].pos.x;
                tempRectPos.push_back(temp);
            }
        }
        
        if (mainMenuRect[4].buttonRect.inside(x, y)) {
            bSubMenu = true;
            subMenuNum = 4;
            mainMenuRect[4].bTouchOver = false;
            tempRectPos.clear();
            for (int i=0; i<MAIN_MENU_BUTTON; i++){
                float temp = mainMenuRect[i].pos.x;
                tempRectPos.push_back(temp);
            }
        }
        
    }
    
    else if (subStep == 2 && bSubMenu) {
        if (mainMenuRect[0].buttonRect.inside(x, y)) {
            subStep = 4;
            mainMenuRect[0].bTouchOver = false;
        }
        
        if (mainMenuRect[1].buttonRect.inside(x, y)) {
            
            *scene = 1;
            mainMenuRect[1].bTouchOver = false;
            reset();
        }
        
        if (mainMenuRect[2].buttonRect.inside(x, y)) {
            subStep = 4;
            mainMenuRect[2].bTouchOver = false;
        }
        
        if (mainMenuRect[3].buttonRect.inside(x, y)) {
            subStep = 4;
            mainMenuRect[3].bTouchOver = false;
        }
        
        if (mainMenuRect[4].buttonRect.inside(x, y)) {
            subStep = 4;
            mainMenuRect[4].bTouchOver = false;
        }
    }

}

//********-----------------------------------------------
void menu::drag(){
    
    
    mParticle.resetForce();
    mParticle.addForce(frc.x, 0);
    mParticle.addDampingForce();
    mParticle.update();
    
    if (mParticle.pos.x>512) {
        mParticle.pos.x = 512;
        
    }
    else if(mParticle.pos.x < -132){
        
        mParticle.pos.x = -132;
    }
    

    hiden();
    
    float diff = mParticle.pos.x -preParticlePos.x;
    
    if (mParticle.pos.x < 36) {
        mainMenuBgPos.x +=diff;
    }else{
        mainMenuBgPos.x = 0;
    }
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].pos.x += diff;
    }
    
    preParticlePos.x = mParticle.pos.x;
    
}
//-------------------------------------------------------

void menu::dragDown(int x, int y, int touchID){
    if (!bSnapIn) {
        touch.set(x, y);
        preTouch = touch;
        frc.x = 0;
        mParticle.frc.set(0,0);
        mParticle.vel.set(0,0);
        
    }
}

//-------------------------------------------------------
void menu::dragMove(int x, int y, int touchID){
    if (!bSnapIn){
        bDrag = true;
        frc.x = 0;
        mParticle.frc.set(0,0);
        mParticle.vel.set(0,0);
        
        touch.set(x, y);
        int diff =  touch.x - preTouch.x;
        
        float speed = 13;
    
        
        if (diff >1 ) {
            speed = ofMap(diff, 5, 50, 8, 12,true);
            frc.x = speed;
        }
        else if (diff < -1){
            speed = ofMap(diff, -50, -5, -12, -8,true);
            frc.x = speed;
            if (mParticle.pos.x<=36) {
                bHidenLogo = true;
            }
        }else{
            mParticle.vel.set(0,0);
            frc.x = 0;
        }
        
        preTouch.x = touch.x;
    }

}

//-------------------------------------------------------
void menu::dragUp(int x, int y, int touchID){
    bDrag = false;
}

//********-----------------------------------------------
void menu::snapIn(){
    
    for (int i=0; i<counter; i++) {
        pct[i] += speed;
        if (pct[i]>1) pct[i] = 1;
        
        
        if (pct[i]>0.3) {
            if (i == counter-1 && counter< MAIN_MENU_BUTTON) {
                counter++;
            }
        }
        
        mainMenuRect[i].interpolateByPct(pct[i]);
    }
    
    
    if (pct[MAIN_MENU_BUTTON-1] == 1) {
        bShowHidenLogo = true;
        bSnapIn = false;
        for (int i=0; i<counter; i++) pct[i] =0;
        counter = 1;
    }
    
    
}

//********-----------------------------------------------
void menu::levelDraw(){
   
    if (subStep ==1 || subStep ==2) {
        if (subMenuNum == 2) {
            for (int i =0 ; i<levelRect.size(); i++) {
                levelRect[i].drawLevel();
            }
        }
    }

}

//-------------------------------------------------------
void menu::levelUpdate(){
    
    if (subStep ==1 || subStep ==2) {
        if (subMenuNum == 2) {
    
            //unlock
            for (int i =0 ; i<levelRect.size(); i++) {
                if (i<=*unLockedLevel) {
                    levelRect[i].bLocked = false;
                }
            }
            
            //scroll
            mParticle.resetForce();
            mParticle.addForce(0, frc.y);
            mParticle.addDampingForce();
            mParticle.update();
            
            if (mParticle.pos.y>384) {
                mParticle.pos.y = 384;
            }
            
            else if (mParticle.pos.y< -800) {
                mParticle.pos.y = -800;
            }
            
            float diff = mParticle.pos.y - preParticlePos.y;
            
            
            for (int i=0; i<levelRect.size(); i++) {
                levelRect[i].pos.y += diff;
            }
            
            preParticlePos.y = mParticle.pos.y;
            
        }
    }
}

//-------------------------------------------------------
void menu::levelReset(){
    
    mParticle.pos.y = 384;
    preParticlePos.y = 384;
    levelCounter = 0;
    levelTimer = 0;
    levelRect.clear();
    levelPct.clear();

    
    levelTouch.set(0, 0);
    levelPreTouch.set(0, 0);
    axisX = 5;
    axisY = 12;
    int counter = -1;
    int j = 0;
    
    //world 1
    
    for (int i = 0; i<axisX*axisY; i++) {
        
        if (counter==(axisX-1)) {
            counter = 0;
            j++;
        }else{
            counter++;
        }
        
        rectangle temp;
        temp.shaper = 1.5;
        temp.rectW = 100;
        temp.rectH = 100;
        temp.imgLockedLevel = &imgLockedLevel;
        temp.pos.set(372+120*counter, 140+120*j);
        levelRect.push_back(temp);
        
        float pct =0;
        levelPct.push_back(pct);
    }
    

    
}

//-------------------------------------------------------
void menu::levelDown(int x, int y, int touchID){

    if (subStep ==1 || subStep ==2) {
        if (subMenuNum == 2) {

            levelTouch.set(x, y);
            levelPreTouch.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            for (int i=0; i<levelRect.size(); i++) {
                if (levelRect[i].buttonRect.inside(x, y)) {
                    levelRect[i].bTouchOver = true;
                }
            }
            
        }
    }
  
    
}

//-------------------------------------------------------
void menu::levelMove(int x, int y, int touchID){

    if (subStep ==1 || subStep ==2) {
        
        if (subMenuNum == 2) {
            
            levelTouch.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            float diff = levelTouch.y - levelPreTouch.y;
            float speed = 5;
            
            
            if (diff >1 ) {
                speed = ofMap(diff, 5, 50, 8, 12,true);
                frc.y = speed;
            }
            else if (diff < -1){
                speed = ofMap(diff, -50, -5, -12, -8,true);
                frc.y = speed;
                if (mParticle.pos.x<=36) {
                    bHidenLogo = true;
                }
            }else{
                mParticle.vel.set(0,0);
                frc.y = 0;
            }
            
            
            levelPreTouch.y = levelTouch.y;
            
            for (int i=0; i<levelRect.size(); i++) {
                if (levelRect[i].buttonRect.inside(x, y)) {
                    levelRect[i].bTouchOver = true;
                }else{
                    levelRect[i].bTouchOver = false;
                }
            }
            
        }
    }
    
}

//-------------------------------------------------------
void menu::levelUp(int x, int y, int touchID){
    if (subStep ==1 || subStep == 2) {
        if (subMenuNum == 2) {

            for (int i=0; i<levelRect.size(); i++) {
                if (levelRect[i].buttonRect.inside(x, y)) {
                    levelRect[i].bTouchOver = false;
                    if (i<= *unLockedLevel) {
                        *level = i;
                        *scene = 2;
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------
void menu::purchaseSetup(){
    
    
    for (int i=0; i<10; i++) {
        int startX = 500;
        rectangle tempRect;
        tempRect.rectW = 27;
        tempRect.rectH = 48;
         //coin 
        tempRect.pos.set(startX+27*i+20*i, 200);
        coinRects.push_back(tempRect);
         //Time Slower
        tempRect.pos.set(startX+27*i+20*i, 200+100);
        timeSlowerRects.push_back(tempRect);
        //dot extender
        tempRect.pos.set(startX+27*i+20*i, 200+200);
        dotExtenderRects.push_back(tempRect);
        //dot freezer
        tempRect.pos.set(startX+27*i+20*i, 200+300);
        dotFreezerRects.push_back(tempRect);
    }
    
    for (int i=0; i<4; i++) {
        rectangle tempRect;
        tempRect.rectW = 48;
        tempRect.rectH = 48;
        tempRect.pos.set(400, 200+100 * i);
        purchaseButtons.push_back(tempRect);
    }
    
   
    //coin
    coinCounter = ofMap(*coinChance, 0, 20, 1, 10);

    for (int i=0; i<coinCounter; i++) {
        coinRects[i].bTouchOver = true;
    }
    
    //Time Slower
    timeSlowerCounter = ofMap(*timeSlowerChance,0,20,1,10);

    for (int i=0; i<timeSlowerCounter; i++) {
        timeSlowerRects[i].bTouchOver = true;
    }
   
    //dot extender
    dotExtenderCounter = ofMap(*dotExtenderChance,0,20,1,10);
    
    for (int i=0; i<dotExtenderCounter; i++) {
        dotExtenderRects[i].bTouchOver = true;
    }
    //dot freezer
    dotFreezerCounter = ofMap(*dotFreezerChance,0,20,1,10);
    
    for (int i=0; i<dotFreezerCounter; i++) {
        dotFreezerRects[i].bTouchOver = true;
    }
}

//-------------------------------------------------------
void menu::purchaseUpdate(){

    if (subStep ==1 || subStep ==2) {
        if (subMenuNum == 3) {
            for (int i=0; i<purchaseButtons.size(); i++) {
                if (*coin<500) {
                    purchaseButtons[i].bFixed = true;
                    purchaseButtons[i].bTouchOver = true;
                }
            }
        }
    }

}

//-------------------------------------------------------
void menu::purchaseDraw(){
    
    if (subStep ==1 || subStep ==2 ) {
        
        if (subMenuNum == 3) {
            
            for (int i=0; i<10; i++) {
                timeSlowerRects[i].drawPurchase();
                coinRects[i].drawPurchase();
                dotExtenderRects[i].drawPurchase();
                dotFreezerRects[i].drawPurchase();
            }
            
            for (int i=0; i<purchaseButtons.size(); i++) {
                purchaseButtons[i].drawPurchase();
            }
            
            //coin
            if (coinCounter==10) {
                purchaseButtons[0].bTouchOver = true;
            }
            
            //timer slower
            if (timeSlowerCounter==10) {
                purchaseButtons[1].bTouchOver = true;
            }
            
            //dot extender
            if (dotExtenderCounter==10) {
                purchaseButtons[2].bTouchOver = true;
            }
            
            //dot freezer
            if (dotFreezerCounter==10) {
                purchaseButtons[3].bTouchOver = true;
            }
            
            ofSetColor(255);
            font.drawString("Coin: "+ofToString(*coin), 400, 100);
            
            if (bNoCoin) {
                ofSetColor(255);
                ofRect(400, 200, 400, 300);
            }
        }
    }
}

//-------------------------------------------------------
void menu::purchaseTouchDown(int x, int y){
    //coin

    if (subStep ==1 || subStep ==2) {
        
        if ( subMenuNum == 3 && coinCounter<10) {
            if (purchaseButtons[0].buttonRect.inside(x, y)) {
                purchaseButtons[0].bTouchOver = true;
            }
        }
        //timer slower

         if (subMenuNum == 3 && timeSlowerCounter<10) {
            if (purchaseButtons[1].buttonRect.inside(x, y)) {
                purchaseButtons[1].bTouchOver = true;
            }
        }
        
        //dot extender
        
         if (subMenuNum == 3 && dotExtenderCounter<10) {
            if (purchaseButtons[2].buttonRect.inside(x, y)) {
                purchaseButtons[2].bTouchOver = true;
            }
        }
        
        //dot freezer
            
         if (subMenuNum == 3 && dotFreezerCounter<10) {
            if (purchaseButtons[3].buttonRect.inside(x, y)) {
                purchaseButtons[3].bTouchOver = true;
            }
        }
    }
    

}

//-------------------------------------------------------
void menu::purchaseTouchMove(int x, int y){
    //coin
    if (subStep ==1 || subStep ==2) {
        
        if (subMenuNum == 3 && coinCounter<10) {
            if (purchaseButtons[0].buttonRect.inside(x, y)) {
                purchaseButtons[0].bTouchOver = true;
            }else{
                purchaseButtons[0].bTouchOver = false;
            }
        }
        //timer slower

        if (subMenuNum == 3&& timeSlowerCounter<10) {
            if (purchaseButtons[1].buttonRect.inside(x, y)) {
                purchaseButtons[1].bTouchOver = true;
            }else{
                purchaseButtons[1].bTouchOver = false;
            }
        }
        
        //dot extender
        if (subMenuNum == 3&& dotExtenderCounter<10) {
           if (purchaseButtons[2].buttonRect.inside(x, y)) {
               purchaseButtons[2].bTouchOver = true;
           }else{
               purchaseButtons[2].bTouchOver = false;
           }
       }
        
        //dot freezer
        if (subMenuNum == 3&& dotFreezerCounter<10) {
           if (purchaseButtons[3].buttonRect.inside(x, y)) {
               purchaseButtons[3].bTouchOver = true;
           }else{
               purchaseButtons[3].bTouchOver = false;
           }
        }
    }
}

//-------------------------------------------------------
void menu::purchaseTouchUp(int x, int y){
   
    //coin
    if (subStep ==1 || subStep ==2){
        if ( subMenuNum == 3 && coinCounter<10 && !purchaseButtons[0].bFixed) {
            if (purchaseButtons[0].buttonRect.inside(x, y)) {
                purchaseButtons[0].bTouchOver = false;
                if (*coin>=500) {
                    *coin -=500;
                    coinCounter ++;
                    bSave = true;
                    coinRects[coinCounter-1].bTouchOver = true;
                    *coinChance = (int)ofMap(coinCounter, 1, 10, 0, 20);
                }else{
                    purchaseButtons[0].bFixed = true;
                    purchaseButtons[0].bTouchOver = true;
                }
            }
        }
        //time slower
         if (subMenuNum == 3 && timeSlowerCounter<10 && !purchaseButtons[1].bFixed) {
            if (purchaseButtons[1].buttonRect.inside(x, y)) {
                purchaseButtons[1].bTouchOver = false;
                
                if (*coin>=500) {
                     *coin -=500;
                    timeSlowerCounter ++;
                    timeSlowerRects[timeSlowerCounter-1].bTouchOver = true;
                    *timeSlowerChance = (int)ofMap(timeSlowerCounter, 1, 10, 0, 20);
                    bSave = true;
                }else{
                    purchaseButtons[1].bFixed = true;
                    purchaseButtons[1].bTouchOver = true;
                }
            }
        }
        
        //dot extender
        
         if (subMenuNum == 3 && dotExtenderCounter<10 && !purchaseButtons[2].bFixed) {
            if (purchaseButtons[2].buttonRect.inside(x, y)) {
                purchaseButtons[2].bTouchOver = false;
                
                if (*coin>=500) {
                    *coin -=500;
                    dotExtenderCounter ++;
                    dotExtenderRects[dotExtenderCounter-1].bTouchOver = true;
                    *dotExtenderChance = (int)ofMap(dotExtenderCounter, 1, 10, 0, 20);
                    bSave = true;
                }else{
                    purchaseButtons[2].bFixed = true;
                    purchaseButtons[2].bTouchOver = true;
                }
               
            }
        }
        
        //dot freezer
         if (subMenuNum == 3 && dotFreezerCounter<10 && !purchaseButtons[3].bFixed) {
            if (purchaseButtons[3].buttonRect.inside(x, y)) {
                purchaseButtons[3].bTouchOver = false;

                if (*coin>=500) {
                    *coin -=500;
                    dotFreezerCounter ++;
                    dotFreezerRects[dotFreezerCounter-1].bTouchOver = true;
                    *dotFreezerChance = (int)ofMap(dotFreezerCounter, 1, 10, 0, 20);
                    bSave = true;
                }else{
                    purchaseButtons[3].bFixed = true;
                    purchaseButtons[3].bTouchOver = true;
                }
                
            }
        }
    }
}

//-------------------------------------------------------
void menu::setSetup(){

    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.pos.set(400, 100+120*i);
        tempRect.rectW = 100;
        tempRect.rectH = 100;
        settingButton.push_back(tempRect);
    }
    
}

//-------------------------------------------------------
void menu::setUpdate(){
    
}

//-------------------------------------------------------
void menu::setDraw(){
    if (subStep ==1 || subStep ==2){
         if ( subMenuNum == 4) {
            for (int i=0; i<settingButton.size(); i++) {
               settingButton[i].drawSetting();
            }
         }
    }
}

//-------------------------------------------------------
void menu::setTouchDown(int x, int y){
    if (subStep ==1 || subStep ==2) {
        if ( subMenuNum == 4) {
            if (settingButton[0].buttonRect.inside(x,y)) {
                settingButton[0].bTouchOver = true;
            }
            
            if (settingButton[1].buttonRect.inside(x,y)) {
                settingButton[1].bTouchOver = true;
            }
            
            if (settingButton[2].buttonRect.inside(x,y)) {
                settingButton[2].bTouchOver = true;
            }

        }
    }
}

//-------------------------------------------------------
void menu::setTouchMove(int x, int y){
    if (subStep ==1 || subStep ==2) {
        
        if ( subMenuNum == 4) {
            if (settingButton[0].buttonRect.inside(x,y)) {
                settingButton[0].bTouchOver = true;
            }else{
                settingButton[0].bTouchOver = false;
            }
            
            if (settingButton[1].buttonRect.inside(x,y)) {
                settingButton[1].bTouchOver = true;
            }else{
                settingButton[1].bTouchOver = false;
            }
            
            if (settingButton[2].buttonRect.inside(x,y)) {
                settingButton[2].bTouchOver = true;
            }else{
                settingButton[2].bTouchOver = false;
            }
            
        }
    }
}

//-------------------------------------------------------
void menu::setTouchUp(int x, int y){
    if (subStep ==1 || subStep ==2) {
        
        if ( subMenuNum == 4) {
            if (settingButton[0].buttonRect.inside(x,y)) {
                settingButton[0].bTouchOver = false;
                *scene = 1;
                *firstPlay = 1;
            }
            
            if (settingButton[1].buttonRect.inside(x,y)) {
                settingButton[1].bTouchOver = false;
            }
            
            if (settingButton[2].buttonRect.inside(x,y)) {
                settingButton[2].bTouchOver = false;
            }
            
        }
    }
}





















