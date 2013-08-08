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
    fontLevel.loadFont("assets/fonts/Comfortaa_Regular.ttf", 30);

    for (int i=0; i<5; i++) {
        fingerTop[i].loadImage("assets/images/mainMenu/f"+ofToString(i+1)+".png");
        fingerBot[i].loadImage("assets/images/mainMenu/f"+ofToString(i+6)+".png");
    }
    
    mainMenuBg.loadImage("assets/images/mainMenu/mainMenuBg.png");
//    buttonBackground.loadImage("assets/images/mainMenu/bg_for_level.png");
    
    button[0].loadImage("assets/images/mainMenu/Tutorial.png");
    buttonOver[0].loadImage("assets/images/mainMenu/Tutorial_b.png");
    
    
    button[1].loadImage("assets/images/mainMenu/Play.png");
    buttonOver[1].loadImage("assets/images/mainMenu/Play_b.png");
    
    button[2].loadImage("assets/images/mainMenu/Levels.png");
    buttonOver[2].loadImage("assets/images/mainMenu/Levels_b.png");
    
    button[3].loadImage("assets/images/mainMenu/Store.png");
    buttonOver[3].loadImage("assets/images/mainMenu/Store_b.png");
    
    button[4].loadImage("assets/images/mainMenu/Setting.png");
    buttonOver[4].loadImage("assets/images/mainMenu/Setting_b.png");
    
    hidenLogo.loadImage("assets/images/mainMenu/hidenLogo.png");
    imgLockedLevel.loadImage("assets/images/mainMenu/level_locked.png");
    imgUnlockedLevel.loadImage("assets/images/mainMenu/level_normal.png");
    
    reset();
    bSave = false;
    bSound = true;
    bLevelChosen = false;
    levelReset();
    purchaseSetup();
    setSetup();
    tutorialSetup();
    
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
        tutorialUpdate();
        setUpdate();
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
        mainMenuRect[i].button = &button[i];
        mainMenuRect[i].buttonTouchOver = &buttonOver[i];
//        mainMenuRect[i].background = &buttonBackground;
        mainMenuRect[i].fingerImg[0]= &fingerTop[i];
        mainMenuRect[i].fingerImg[1]= &fingerBot[i];
        mainMenuRect[i].rectW = button[i].getWidth();
        mainMenuRect[i].rectH = button[i].getHeight();
        mainMenuRect[i].shadowWidth = 0;

    }
    
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
    
    if (!bSubMenu) {
        ofSetColor(76,74,72);
    }else{
        ofSetColor(0);
    }
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
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
    tutorialDraw();

   
    
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
    tutorialTouchDown(x, y);
    
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
    tutorialTouchMove(x,y);
    
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
        
        mainMenuRect[num].shadowWidth = ofMap(mainMenuRect[num].pos.x,1024, 150, 0, 724,true);

        if (pct[MAIN_MENU_BUTTON-1] == 1) {
            subStep = 2;
        }
        
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

        mainMenuRect[num].shadowWidth = ofMap(mainMenuRect[num].pos.x,150, mainMenuRect[num].posc.x, 724, 0,true);

        if (pct[MAIN_MENU_BUTTON-1] == 1 ) {
            bSubMenu = false;
            subStep = 0;
            
            if (subMenuNum == 2) {
                levelReset();
            }else if(subMenuNum == 0){
                tutorialReset();

            }else if(subMenuNum == 3){
                purchaseReset();
            
            }else if(subMenuNum == 4){
                setReset();
                
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
   
    if (subStep ==2) {
        if (subMenuNum == 2) {
            for (int i =0 ; i<levelRect.size(); i++) {
                levelRect[i].drawLevel();
            }
        }
    }

}

//-------------------------------------------------------
void menu::levelUpdate(){
    
    if (subStep ==2) {
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
            
            if (mParticle.pos.y>410) {
                mParticle.pos.y = 410;
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
    
    mParticle.pos.y = 410;
    preParticlePos.y = 410;
    levelCounter = 0;
    levelTimer = 0;
    levelRect.clear();
    levelPct.clear();

    
    levelTouch.set(0, 0);
    levelPreTouch.set(0, 0);
    axisX = 5;
    axisY = 16;
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
        temp.imgUnlockedLevel = &imgUnlockedLevel;
        temp.pos.set(420+120*counter, 70+120*j);
        temp.font = &fontLevel;
        temp.message = ofToString(i+1);
        levelRect.push_back(temp);
        
        float pct =0;
        levelPct.push_back(pct);
    }
    
}

//-------------------------------------------------------
void menu::levelDown(int x, int y, int touchID){

    if (subStep ==2) {
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

    if (subStep ==2) {
        
        if (subMenuNum == 2) {
            
            levelTouch.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            float diff = levelTouch.y - levelPreTouch.y;
            float speed;
            
            if (diff >1 ) {
                speed = ofMap(diff, 1, 50, 5, 6,true);
                frc.y = speed;
            }
            else if (diff < -1){
                speed = ofMap(diff, -1, -50, -5, -6,true);
                frc.y = speed;
                
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
    if (subStep == 2) {
        if (subMenuNum == 2) {
            for (int i=0; i<levelRect.size(); i++) {
                if (levelRect[i].buttonRect.inside(x, y)) {
                    levelRect[i].bTouchOver = false;
                    if (i<= *unLockedLevel) {
                        *level = i;
                        levelReset();
                        reset();
                        bLevelChosen = true;
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------
void menu::purchaseSetup(){
    
    coinOffset.set(0, 0);
    float offSetX = 340;
    //info bar
    infoRect.set(offSetX, 0, 632, 100);
    infoBarImg.loadImage("assets/images/mainMenu/purchaseBanner.png");
    
    purchaseline[0].set(offSetX, 127, 608, 30);
    purChaseImglines[0].loadImage("assets/images/mainMenu/purchaseline00.png");
    //purchase buttons
    
    for (int i=0; i<3; i++) {
        ofImage temImg;
        temImg.loadImage("assets/images/mainMenu/purchaseCion0"+ofToString(i)+".png");
        purChaseImgCoins.push_back(temImg);
        
        temImg.loadImage("assets/images/mainMenu/purchaseLive0"+ofToString(i)+".png");
        purChaseImglives.push_back(temImg);
    }
    
    for (int i=0; i<4; i++) {
        ofImage temImg;
        temImg.loadImage("assets/images/mainMenu/purchaseItem0"+ofToString(i)+".png");
        purChaseImgItems.push_back(temImg);
    }
    
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i, 170);
        tempRect.purchaseImg = &purChaseImgCoins[i];
        coinButtons.push_back(tempRect);
    }
    
    for (int i=0; i<3; i++) {
        prices01[i].set(offSetX + 24 + 226*i, 353, 122, 27);
    }
    
    purchaseline[1].set(offSetX, 411, 608, 30);
    purChaseImglines[1].loadImage("assets/images/mainMenu/purchaseline01.png");
    //live buttons
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i,  468);
        tempRect.purchaseImg = &purChaseImglives[i];
        liveButtons.push_back(tempRect);
    }
    
    
    for (int i=0; i<3; i++) {
        prices02[i].set(offSetX + 24 + 226*i, 648, 122, 27);
    }
    
    purchaseline[2].set(offSetX, 686, 608, 30);
    purChaseImglines[2].loadImage("assets/images/mainMenu/purchaseline02.png");
    
    //item buttons
  
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i,  744);
        
       
        tempRect.purchaseImg = &purChaseImgItems[i];
        itemButtons.push_back(tempRect);
    }
    
    for (int i=0; i<3; i++) {
        prices03[i].set(offSetX + 24 + 226*i, 926, 122, 27);
    }
    
   
    
    for (int i=0; i<1; i++) {
        rectangle tempRect;
        tempRect.rectW = 176;
        tempRect.rectH = 176;
        tempRect.pos.set(offSetX + 220*i, 974);
        
        tempRect.purchaseImg = &purChaseImgItems[i+3];
        itemButtons.push_back(tempRect);
    }
    
    prices03[3].set(offSetX + 24, 1155, 122, 27);
    
    
}

//-------------------------------------------------------
void menu::purchaseReset(){
    
    mParticle.pos.y = 410;
    preParticlePos.y = 410;
    
    coinButtons.clear();
    liveButtons.clear();
    itemButtons.clear();
    
    float offSetX = 340;
    //info bar
    infoRect.set(offSetX, 0, 632, 100);
    purchaseline[0].set(offSetX, 127, 608, 30);
    
    //purchase buttons
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i, 170);
        tempRect.purchaseImg = &purChaseImgCoins[i];
        coinButtons.push_back(tempRect);
    }
    
    for (int i=0; i<3; i++) {
        prices01[i].set(offSetX + 24 + 226*i, 353, 122, 27);
    }
    
    purchaseline[1].set(offSetX, 411, 608, 30);
    
    //live buttons
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i,  468);
        tempRect.purchaseImg = &purChaseImglives[i];
        liveButtons.push_back(tempRect);
    }
    
    
    for (int i=0; i<3; i++) {
        prices02[i].set(offSetX + 24 + 226*i, 648, 122, 27);
    }
    
    purchaseline[2].set(offSetX, 686, 608, 30);
    
    
    //item buttons
    
    for (int i=0; i<3; i++) {
        rectangle tempRect;
        tempRect.rectW = 175;
        tempRect.rectH = 175;
        tempRect.pos.set(offSetX + 228*i,  744);
        tempRect.purchaseImg = &purChaseImgItems[i];
        tempRect.purchaseImg = &purChaseImgItems[i];
        itemButtons.push_back(tempRect);
    }
    
    for (int i=0; i<3; i++) {
        prices03[i].set(offSetX + 24 + 226*i, 926, 122, 27);
    }
    
    
    
    for (int i=0; i<1; i++) {
        rectangle tempRect;
        tempRect.rectW = 176;
        tempRect.rectH = 176;
        tempRect.pos.set(offSetX + 220*i, 974);
        tempRect.purchaseImg = &purChaseImgItems[i+3];
        itemButtons.push_back(tempRect);
    }
    
    prices03[3].set(offSetX + 24, 1155, 122, 27);
    
    
}

//-------------------------------------------------------
void menu::purchaseUpdate(){

    if (subStep ==2) {
        if (subMenuNum == 3) {
            
            mParticle.resetForce();
            mParticle.addForce(0, frc.y);
            mParticle.addDampingForce();
            mParticle.update();
            
            if (mParticle.pos.y>410) {
                mParticle.pos.y = 410;
            }
            
            else if (mParticle.pos.y< -100) {
                mParticle.pos.y = -100;
            }
            
            float diff = mParticle.pos.y - preParticlePos.y;
            
            infoRect.position.y +=diff;
            
            for (int i=0; i<coinButtons.size(); i++) {
                coinButtons[i].pos.y +=diff;
            }
            
            for (int i=0; i<liveButtons.size(); i++) {
                liveButtons[i].pos.y +=diff;
            }
            
            for (int i=0; i<itemButtons.size(); i++) {
                itemButtons[i].pos.y +=diff;
            }
            
            
            for (int i=0; i<3; i++) {
                purchaseline[i].position.y+=diff;
            }
            
            
            for (int i=0; i< 3; i++) {
                prices01[i].position.y +=diff;
            }
            
            for (int i=0; i< 3; i++) {
                prices02[i].position.y +=diff;
            }
            
            
            for (int i=0; i< 4; i++) {
                prices03[i].position.y +=diff;
            }
            
            coinOffset.y+=diff;
            
            preParticlePos.y = mParticle.pos.y;
            
        }
    }

}

//-------------------------------------------------------
void menu::purchaseDraw(){
    
    if (subStep ==2 ) {
        if (subMenuNum == 3) {
            
            ofSetColor(255);
            infoBarImg.draw(infoRect.position);
            
            for (int i=0; i<coinButtons.size(); i++) {
                coinButtons[i].drawPurchase();
            }
            
            for (int i=0; i<liveButtons.size(); i++) {
                liveButtons[i].drawPurchase();
            }
            
            for (int i=0; i<itemButtons.size(); i++) {
                itemButtons[i].drawPurchase();
            }
            
            for (int i=0; i<3; i++) {
                ofSetColor(255);
                purChaseImglines[i].draw(purchaseline[i].position);
            }
            
            ofSetColor(38, 52, 40);
            font.drawString(ofToString(*coin), 670, 50+font.stringHeight(ofToString(*coin))/2+coinOffset.y);
            
//            for (int i=0; i< 3; i++) {
//                ofSetColor(155);
//                ofRect(prices01[i]);
//            }
//            
//            for (int i=0; i< 3; i++) {
//                ofSetColor(155);
//                ofRect(prices02[i]);
//            }
//            
//            
//            for (int i=0; i< 4; i++) {
//                ofSetColor(155);
//                ofRect(prices03[i]);
//            }
        }
    }
}

//-------------------------------------------------------
void menu::purchaseTouchDown(int x, int y){
    //coin

    if (subStep ==2) {
        if (subMenuNum == 3) {
            
            purchasePos.set(x, y);
            purchasePrePos.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            for (int i=0; i<coinButtons.size(); i++) {
                if (coinButtons[i].buttonRect.inside(x, y)) {
                    coinButtons[i].bTouchOver = true;
                }
            }
            
            for (int i=0; i<liveButtons.size(); i++) {
                if (liveButtons[i].buttonRect.inside(x, y)) {
                    liveButtons[i].bTouchOver = true;
                }
            }
            
            for (int i=0; i<itemButtons.size(); i++) {
                if (itemButtons[i].buttonRect.inside(x, y)) {
                    itemButtons[i].bTouchOver = true;
                }
            }
            
        }
    }    

}

//-------------------------------------------------------
void menu::purchaseTouchMove(int x, int y){
    
    if (subStep ==2) {
        if (subMenuNum == 3) {
            
            purchasePos.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            float diff = purchasePos.y - purchasePrePos.y;
            float speed;
            
            if (diff >1 ) {
                speed = ofMap(diff, 1, 50, 5, 6,true);
                frc.y = speed;
            }
            else if (diff < -1){
                speed = ofMap(diff, -1, -50, -5, -6,true);
                frc.y = speed;
                
            }else{
                mParticle.vel.set(0,0);
                frc.y = 0;
            }
            
            purchasePrePos.y = purchasePos.y;
            
            for (int i=0; i<coinButtons.size(); i++) {
                if (coinButtons[i].buttonRect.inside(x, y)) {
                    coinButtons[i].bTouchOver = true;
                }else{
                    coinButtons[i].bTouchOver = false;
                }
            }
            
            for (int i=0; i<liveButtons.size(); i++) {
                if (liveButtons[i].buttonRect.inside(x, y)) {
                    liveButtons[i].bTouchOver = true;
                }else{
                    liveButtons[i].bTouchOver = false;
                }
            }
            
            for (int i=0; i<itemButtons.size(); i++) {
                if (itemButtons[i].buttonRect.inside(x, y)) {
                    itemButtons[i].bTouchOver = true;
                }else{
                    itemButtons[i].bTouchOver = false;
                }
            }
            
        }
    }
}

//-------------------------------------------------------
void menu::purchaseTouchUp(int x, int y){
   
    
    if (subStep ==2) {
        if (subMenuNum == 3) {
            
            
            for (int i=0; i<coinButtons.size(); i++) {
                if (coinButtons[i].buttonRect.inside(x, y)) {
                    coinButtons[i].bTouchOver = false;
                }
            }
            
            for (int i=0; i<liveButtons.size(); i++) {
                if (liveButtons[i].buttonRect.inside(x, y)) {
                    liveButtons[i].bTouchOver = false;
                }
            }
            
            for (int i=0; i<itemButtons.size(); i++) {
                if (itemButtons[i].buttonRect.inside(x, y)) {
                    itemButtons[i].bTouchOver = false;
                }
            }
            
        }
    }
    
}

//-------------------------------------------------------
void menu::setSetup(){

    for (int i=0; i<3; i++) {
        ofImage temp;
        temp.loadImage("assets/images/setting/setting0"+ofToString(i)+".png");
        setImgs.push_back(temp);
    }
    
    for (int i=0; i<2; i++) {
        rectangle tempRect;
        tempRect.pos.set(430 + 220*i, 120);
        tempRect.rectW = 200;
        tempRect.rectH = 200;
        tempRect.setImg = &setImgs[i];
        settingButton.push_back(tempRect);
    }
    
}

//-------------------------------------------------------
void menu::setReset(){
    mParticle.pos.y = 410;
    preParticlePos.y = 410;
    coinOffset.set(0, 0);
    settingButton.clear();
    for (int i=0; i<2; i++) {
        rectangle tempRect;
        tempRect.pos.set(430 + 220*i, 120);
        tempRect.rectW = 200;
        tempRect.rectH = 200;
        tempRect.setImg = &setImgs[i];
        settingButton.push_back(tempRect);
    }
    
}

//-------------------------------------------------------
void menu::setUpdate(){
    if (subStep==1 ||subStep ==2){
        if (bSound) {
            settingButton[1].setImg = &setImgs[1];
        }else{
            settingButton[1].setImg = &setImgs[2];
        }
    }
    
}

//-------------------------------------------------------
void menu::setDraw(){
    
    if (subStep ==2){
         if ( subMenuNum == 4) {
            for (int i=0; i<settingButton.size(); i++) {
               settingButton[i].drawSetting();
            }
         }
    }
}

//-------------------------------------------------------
void menu::setTouchDown(int x, int y){
    if (subStep ==2) {
        if ( subMenuNum == 4) {
            if (settingButton[0].buttonRect.inside(x,y)) {
                settingButton[0].bTouchOver = true;
            }
            
            if (settingButton[1].buttonRect.inside(x,y)) {
                settingButton[1].bTouchOver = true;
            }

        }
    }
}

//-------------------------------------------------------
void menu::setTouchMove(int x, int y){
    if (subStep ==2) {
        
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
                bSound = !bSound;
            }
            
        }
    }
}

//-------------------------------------------------------
void menu::tutorialSetup(){

    for (int i=0; i<3; i++) {
        ofImage temp;
        temp.loadImage("assets/images/tutorial/tutorial0"+ofToString(i)+".png");
        tutorialImg.push_back(temp);
        
        ofPoint pos;
        pos.set(312, 13+540*i);
        tutorialPos.push_back(pos);
    }
        
}

//-------------------------------------------------------
void menu::tutorialUpdate(){
    if (subStep ==2) {
        if (subMenuNum == 0) {
            //scroll
            mParticle.resetForce();
            mParticle.addForce(0, frc.y);
            mParticle.addDampingForce();
            mParticle.update();
            
            if (mParticle.pos.y>410) {
                mParticle.pos.y = 410;
            }
            
            else if (mParticle.pos.y< -480) {
                mParticle.pos.y = -480;
            }
            
            float diff = mParticle.pos.y - preParticlePos.y;
            
            for (int i=0; i<tutorialPos.size(); i++) {
                tutorialPos[i].y += diff;
            }
            
            preParticlePos.y = mParticle.pos.y;
           
        }
    }
}

//-------------------------------------------------------
void menu::tutorialDraw(){
    if (subStep ==2) {
        if (subMenuNum == 0) {
            for (int i=0; i<tutorialPos.size(); i++) {
                ofSetColor(255);
                tutorialImg[i].draw(tutorialPos[i]);
            }
        }
    }
}

//-------------------------------------------------------
void menu::tutorialTouchDown(int x, int y){
    if (subStep ==2) {
        if (subMenuNum == 0) {
            
            tutorialTouch.set(x, y);
            tutorialPreTouch.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
        }
    }
}

//-------------------------------------------------------
void menu::tutorialTouchMove(int x, int y){
    if (subStep ==2) {
        
        if (subMenuNum == 0) {
            
            tutorialTouch.set(x, y);
            frc.y = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            float diff = tutorialTouch.y - tutorialPreTouch.y;
            float speed;
            
            if (diff >1 ) {
                speed = ofMap(diff, 1, 50, 5, 6,true);
                frc.y = speed;
            }
            else if (diff < -1){
                speed = ofMap(diff, -1, -50, -5, -6,true);
                frc.y = speed;
             
            }else{
                mParticle.vel.set(0,0);
                frc.y = 0;
            }
            
            
            tutorialPreTouch.y = tutorialTouch.y;
            
        }
    }

}

//-------------------------------------------------------
void menu::tutorialReset(){
    
    mParticle.pos.y = 410;
    preParticlePos.y = 410;
    tutorialPos.clear();
    
    for (int i=0; i<3; i++) {
        ofPoint pos;
        pos.set(312, 13+540*i);
        tutorialPos.push_back(pos);
    }
}


















