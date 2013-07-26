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

    button[0].loadImage("assets/images/mainMenu/Tutorial.png");
    buttonOver[0].loadImage("assets/images/mainMenu/Tutorial_b.png");
    background[0].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[1].loadImage("assets/images/mainMenu/Play.png");
    buttonOver[1].loadImage("assets/images/mainMenu/Play_b.png");
    background[1].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[2].loadImage("assets/images/mainMenu/Levels.png");
    buttonOver[2].loadImage("assets/images/mainMenu/Levels_b.png");
    background[2].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[3].loadImage("assets/images/mainMenu/Theme.png");
    buttonOver[3].loadImage("assets/images/mainMenu/Theme_b.png");
    background[3].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    button[4].loadImage("assets/images/mainMenu/Credit.png");
    buttonOver[4].loadImage("assets/images/mainMenu/Credit_b.png");
    background[4].loadImage("assets/images/mainMenu/mainMenuBg.png");
    
    hidenLogo.loadImage("assets/images/mainMenu/hidenLogo.png");
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].button = &button[i];
        mainMenuRect[i].buttonTouchOver = &buttonOver[i];
        mainMenuRect[i].background = &background[i];
        
        mainMenuRect[i].rectW = button[i].getWidth();
        mainMenuRect[i].rectH = button[i].getHeight();

    }
    
    
    reset();
    
    levelReset();
 }

//-------------------------------------------------------
void menu::update(){
    
    if(bSnapIn){
        snapIn();
    }
    else if (bSubMenu) {
        subMenu(subMenuNum);
        levelUpdate();
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
}

//-------------------------------------------------------
void menu::draw(){
    
    if (bShowHidenLogo) {
        ofBackground(0);
    }else{
        ofBackground(255);
    }
    
  
    if (subMenuNum == 2) {
        levelDraw();
    }
    
    
    if (!bSubMenu && bShowHidenLogo) {
        ofSetColor(255);
        hidenLogo.draw(ofGetWidth()-168,0);
    }
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        ofSetColor(255);
        mainMenuRect[i].draw();
    }

}

//********-----------------------------------------------
void menu::touchDown(int x, int y, int touchID){
    
    dragDown(x, y, touchID);
    levelDown(x, y, touchID);
    
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
            *currentScene = 1;
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
            *currentScene = 1;
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
        if (diff>1&&diff<20) {
                mParticle.pos.x+=speed;
            
        }
        else if (diff<-1&&diff>-20) {
                mParticle.pos.x-=speed;
                if (mParticle.pos.x<36) {
                    bHidenLogo = true;
                }
        }
        
        
        speed = 3;
        if (diff >20) {
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            frc.x = speed;
        }
        else if (diff < -20){
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            frc.x = -speed;
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
    
    for (int i =0 ; i<levelRect2.size(); i++) {
        levelRect1[i].drawLevel();
        levelRect2[i].drawLevel();
    }
    
}

//-------------------------------------------------------
void menu::levelUpdate(){
    
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
    
    
    for (int i=0; i<levelRect1.size(); i++) {
        levelRect1[i].pos.y += diff;
    }
    
    for (int i=0; i<levelRect2.size(); i++) {
        levelRect2[i].pos.y += diff;
    }
    
    preParticlePos.y = mParticle.pos.y;
    
    cout<<diff<<endl;
}

//-------------------------------------------------------
void menu::levelReset(){
    
    mParticle.pos.y = 384;
    preParticlePos.y = 384;
    levelCounter = 0;
    levelTimer = 0;
    levelRect1.clear();
    levelPct1.clear();
    
    levelRect2.clear();
    levelPct2.clear();
    
    levelTouch.set(0, 0);
    levelPreTouch.set(0, 0);
    axisX = 5;
    axisY = 4;
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
        temp.bTouchOver = false;
        temp.pos.set(372+50+120*counter, 140+120*j);
        levelRect1.push_back(temp);
        
        float pct =0;
        levelPct1.push_back(pct);
    }
    
    //world2
    int u = 0;
    for (int i = 0; i<axisX*axisY; i++) {
        
        if (counter==(axisX-1)) {
            counter = 0;
            u++;
        }else{
            counter++;
        }
        
        rectangle temp;
        temp.shaper = 1.5;
        temp.rectW = 100;
        temp.rectH = 100;
        temp.bTouchOver = false;
        temp.pos.set(372+50+120*counter, 650-100+120*u);
        levelRect2.push_back(temp);
        
        float pct =0;
        levelPct2.push_back(pct);
        
    }
    
}

//-------------------------------------------------------
void menu::levelDown(int x, int y, int touchID){

    if (subStep ==2) {
        levelTouch.set(x, y);
        levelPreTouch.set(x, y);
        frc.y = 0;
        mParticle.frc.set(0,0);
        mParticle.vel.set(0,0);
        
        for (int i=0; i<levelRect1.size(); i++) {
            if (levelRect1[i].buttonRect.inside(x, y)) {
                levelRect1[i].bTouchOver = true;
            }
        }
        
        for (int i=0; i<levelRect2.size(); i++) {
            if (levelRect2[i].buttonRect.inside(x, y)) {
                levelRect2[i].bTouchOver = true;
            }
        }

    }
  
    
}

//-------------------------------------------------------
void menu::levelMove(int x, int y, int touchID){

    if (subStep ==2) {
        levelTouch.set(x, y);
        frc.y = 0;
        mParticle.frc.set(0,0);
        mParticle.vel.set(0,0);
        
        float diff = levelTouch.y - levelPreTouch.y;
        float speed = 10;
        
        if (diff>1&&diff<10) {
            
            mParticle.pos.y+=speed;
        }
        else if (diff<-1&&diff>-10) {
            
            mParticle.pos.y-=speed;

        }
        
        speed = 2;
        if (diff >10) {
            frc.y = speed;
        }
        else if (diff < -10){
            frc.y = -speed;
        }
        
        
        levelPreTouch.y = levelTouch.y;
        
        for (int i=0; i<levelRect1.size(); i++) {
            if (levelRect1[i].buttonRect.inside(x, y)) {
                levelRect1[i].bTouchOver = true;
            }else{
                levelRect1[i].bTouchOver = false;
            }
        }
        
        for (int i=0; i<levelRect2.size(); i++) {
            if (levelRect2[i].buttonRect.inside(x, y)) {
                levelRect2[i].bTouchOver = true;
            }else{
                levelRect2[i].bTouchOver = false;
            }
        }
        
    }
    
}

//-------------------------------------------------------
void menu::levelUp(int x, int y, int touchID){
    if (subStep == 2) {
        for (int i=0; i<levelRect1.size(); i++) {
            if (levelRect1[i].buttonRect.inside(x, y)) {
                levelRect1[i].bTouchOver = false;
            }
        }
        
        for (int i=0; i<levelRect2.size(); i++) {
            if (levelRect2[i].buttonRect.inside(x, y)) {
                levelRect2[i].bTouchOver = false;
            }
        }
    }
}














