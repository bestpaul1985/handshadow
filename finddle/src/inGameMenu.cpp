//
//  inGameMenu.cpp
//  handShadow
//
//  Created by PengCheng on 7/23/13.
//
//

#include "inGameMenu.h"

void inGameMenu::setup(int *Coin , int *Level , float &GameTimer, int &FingerSize, float &BGScale,  ofPoint *AccFrc){
    
    coin = Coin;
    level = Level;
    gameTimer = &GameTimer;
    fingerSize = &FingerSize;
    bgScale = &BGScale;
    accFrc = AccFrc;
    
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 46);
    fontBig.loadFont("assets/fonts/Comfortaa_Regular.ttf", 50);
    
    
    bgImg.loadImage("assets/images/inGameMenu/bg.png");
    clockOutLine.loadImage("assets/images/inGameMenu/outline.png");
    
    LDBackgroudImg[0].loadImage("assets/images/inGameMenu/bg_success.png");
    LDBackgroudImg[1].loadImage("assets/images/inGameMenu/bg_unsuccess.png");

    coinBag.loadImage("assets/images/inGameMenu/coin_bag.png");
    coinImg.loadImage("assets/images/inGameMenu/single_coin.png");
    
    for (int i=0; i<6; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/"+ofToString(i)+".png");
        fingerImg.push_back(temp);
    }
    for (int i=0; i<8; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/Dot"+ofToString(i)+"_Small.png");
        iconImg.push_back(temp);
    }
    
    bgRect.set(0, 0, bgImg.getWidth(),bgImg.getHeight());
    for (int i=0; i<3; i++) {
        ofRectangle temp;
        temp.set(140+220*i, 500, 40, 30);
        buttons.push_back(temp);
        
        ofColor tempColor;
        tempColor.set(200);
        buttonColor.push_back(tempColor);
    }
    
    for (int i=0; i<4; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/321_"+ofToString(i)+".png");
        readyImg.push_back(temp);
    }
    
    homeImgA.loadImage("assets/images/inGameMenu/menu.png");
    homeImgB.loadImage("assets/images/inGameMenu/menu_b.png");
    resumeImgA.loadImage("assets/images/inGameMenu/resume.png");
    resumeImgB.loadImage("assets/images/inGameMenu/resume_b.png");
    
    homeRect.button = &homeImgA;
    homeRect.buttonTouchOver= &homeImgB;
    resumeRect.button = &resumeImgA;
    resumeRect.buttonTouchOver = &resumeImgB;
    
    reset();
        
};

//-----------------------------------------------------------------------
void inGameMenu::update(){
    
    
    angle = (int)ofMap((60-*gameTimer), 0, 60, 0, 360);
    
    if (angle-preAngle == 1) {
        
        lineColor[angle].set(255,30);
    }
    
    for (int i=(angle+1); i<360; i++) {
        if (bTimeSlower) {
            lineColor[i].set(153,201,235);
        }else{
            lineColor[i].set(30);
        }
    }
    
    
    preAngle = angle;
    
    if (!bPauseL && !bPauseR) {
        if (accFrc->y > 0.5){
            bPauseL = true;
        }else if(accFrc->y<-0.5){
            bPauseR = true;
        }
    }
    

    
}

//-----------------------------------------------------------------------
void inGameMenu::starter(){

    if (!bGameStart) {
        
        gameStartAlpha += gameStartSpeed;
        
        if (gameStartAlpha>255&& gameStartCounter < 3) {
            gameStartAlpha = 255;
            
            gameStartOffset.y-=1;
            if (gameStartOffset.y > 2) {
                gameStartOffset.y = 2;
            }
            
            gameStartTimer ++;
            
        }
        
        if (gameStartTimer > 15 && gameStartCounter < 3) {
            gameStartSpeed *= -1;
            gameStartTimer = 0;
        }
        
        if(gameStartAlpha<0 && gameStartCounter < 3){
            gameStartAlpha = 0;
            gameStartSpeed *= -1;
            gameStartCounter++;
            gameStartOffset.y = 0;
        }
        
        if (gameStartCounter == 3) {
            gameStartPct +=0.2f;
            gameStartScale = (1-gameStartPct)*0.6+gameStartPct;
            if (gameStartPct > 1) {
                gameStartPct = 1;
                gameStartTimer ++;
            }
            
            if (gameStartTimer>15) {
                bGameStart = true;
            }
        }
        
       
        if (gameStartCounter==readyImg.size()) {
            gameStartCounter = readyImg.size()-1;
        }
       
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2+gameStartOffset.y);
        ofSetColor(255,gameStartAlpha);
        readyImg[gameStartCounter].draw(-readyImg[gameStartCounter].getWidth()/2*gameStartScale,
                                        -readyImg[gameStartCounter].getHeight()/2*gameStartScale,
                                        readyImg[gameStartCounter].getWidth()*gameStartScale,
                                        readyImg[gameStartCounter].getHeight()*gameStartScale);
                                        
        ofPopMatrix();
    }
    
    
}

//-----------------------------------------------------------------------
void inGameMenu::reset(){

    LDType = BG_FADE;

    bLevelDone = false;
    bNextLevel = false;
    bTryAgin   = false;
    bHome      = false;
    bLevelFail = false;
    bTimeSlower = false;
    angle      = 0;
    preAngle   = 0;
    
    linePos.clear();
    lineColor.clear();
    
    for (int i=0; i<360; i++) {
        ofPoint temp;
        temp.x = 20*cos(i*DEG_TO_RAD - PI/2);
        temp.y = 20*sin(i*DEG_TO_RAD - PI/2);
        linePos.push_back(temp);
        
        ofColor color(30);
        lineColor.push_back(color);
    }
    //game starter
    bGameStart = false;
    gameStartCounter = 0;
    gameStartAlpha = 0;
    gameStartSpeed = 90;
    gameStartOffset.set(0, 0);
    gameStartPct = 0;
    gameStartScale = 1;
    gameStartTimer = 0;
    //level done
    *bgScale = 1;
    LDVelocity.set(0, 0);
    LDGravity = 10;
    LDFriction = -0.75;
    LDRadius = 332;
    LDPos.set(ofGetWidth()/2, -LDRadius);
    LDAlpha = 0;
    
    //score
    preCoin = *coin;
    score = 0;
    timer = 0;
    
    //pause
    bPauseL = false;
    bPauseR = false;
    
    pausePct = 0;
    homeRect.shaper = 0.6;
    resumeRect.shaper = 0.6;
    homeRect.pos.set(-1000, ofGetHeight()/2);
    resumeRect.pos.set(-1000, ofGetHeight()/2);
    
    //small icon
    for (int i=0; i<8; i++) {
        bSmallIconCovered[i] = false;
    }
}

//-----------------------------------------------------------------------
void inGameMenu::draw(){
    
    if (!bPauseL && !bPauseR) {
        starter();
    }
    
    if (LDType == BG_FADE) {
        
        ofSetColor(255,255);
        bgImg.draw(bgRect);
        
        ofSetColor(255);
        fingerImg[*live].draw(166,-5,fingerImg[*live].getWidth()/4*3,fingerImg[*live].getHeight()/4*3);
        
        ofSetColor(30);
        font.drawString(ofToString(*level), 930, 45);
        
        ofPushMatrix();
        ofTranslate(56, 27);
        for (int i=0; i<linePos.size(); i++) {
            ofSetColor(lineColor[i]);
            ofLine(0, 0, linePos[i].x, linePos[i].y);
        }
        ofPopMatrix();
        ofSetColor(255);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        clockOutLine.draw(56, 27);
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        
        for (int i=0; i<8; i++) {
           
            if (bSmallIconCovered[i]) {
                ofSetColor(100);
            }else{
                ofSetColor(255);
            }
            
            if (i<*fingerSize) {
                iconImg[i].draw(345+50*i,10);
            }else{
                iconImg[7].draw(345+50*i,10);
            }
        }
    }
   
    if (!bPauseL && !bPauseR) {
        levelDoneDraw();
    }
    
    pause();

 
}

//-----------------------------------------------------------------------
void inGameMenu::touchDown(int x, int y){

    if (bPauseL || bPauseR) {
    
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = true;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = true;
        }
        
    }
    

}

//-----------------------------------------------------------------------
void inGameMenu::touchMove(int x, int y){

    if (bPauseL || bPauseR) {
        
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = true;
        }else{
            resumeRect.bTouchOver = false;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = true;
        }else{
            homeRect.bTouchOver = false;
        }
        
    }

}

//-----------------------------------------------------------------------
void inGameMenu::touchUp(int x, int y){
    
    if (bPauseL || bPauseR) {
        
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = false;
            bPauseL = false;
            bPauseR = false;
            pausePct = 0;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = false;
            bPauseL = false;
            bPauseR = false;
            pausePct = 0;
            bHome = true;
        }
        
    }

}

//-----------------------------------------------------------------------
void inGameMenu::levelDoneDraw(){
   
    if (bLevelDone || bLevelFail) {
        
        ofPoint coinPos(-coinImg.getWidth()-fontBig.stringWidth(ofToString(score))/2-20,-45);
        ofPoint coinBagPos(-coinBag.getWidth()-fontBig.stringWidth(ofToString(*coin))/2-10, 45);
        
        ofPoint scorePos(0,-10);
        ofPoint totalPos(0,110);
        
        switch (LDType) {
                
            case BG_FADE:{
                
                if (*bgScale>0.98) {
                    *bgScale-=0.001f;
                    LDAlpha += 10;
                }else{
                    LDType = ICON_SHOW;
                }
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
            }break;
            case ICON_SHOW:{
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                LDVelocity.y += LDGravity;
                LDPos +=LDVelocity;
               
                if (LDPos.y > ofGetHeight()/2) {
                    LDPos.y = ofGetHeight()/2;
                    LDVelocity*=LDFriction;
                }
                
                
                if (LDVelocity.y < 0 && LDVelocity.y > -5 && score>0) {
                    timer++;
                    if (timer>15) {
                        timer = 15;
                        score-=5;
                        preCoin+=5;
                    }
                }
                
                if (score<=0) {
                    score = 0;
                    preCoin = *coin;
                    timer++;
                }
                
                if (bLevelDone) {
                    if (timer>45) {
                        LDType = ICON_FADE;
                        LDVelocity.y = -70;
                    }
                }
                else if (bLevelFail) {
                    if (timer>100) {
                        LDType = ICON_FADE;
                        LDVelocity.y = -70;
                    }
                }
                
                
                ofSetColor(255);
                ofPushMatrix();
                ofTranslate(LDPos);
                ofSetRectMode(OF_RECTMODE_CENTER);
                if (bLevelDone) {
                    LDBackgroudImg[0].draw(0,0);
                }else{
                    LDBackgroudImg[1].draw(0,0);
                }
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(30);
                fontBig.drawString(ofToString(score), scorePos.x-fontBig.stringWidth(ofToString(score))/2, scorePos.y-fontBig.stringHeight(ofToString(score))/2);
                font.drawString(ofToString(preCoin), totalPos.x-font.stringWidth(ofToString(preCoin))/2, totalPos.y-font.stringHeight(ofToString(preCoin))/2);

                for (int i=0; i<5; i++) {
                    ofSetColor(255);
                    int offset;
                    (i%2)==0?  offset = -5: offset = 5;
                    coinImg.draw( coinPos.x+offset, coinPos.y-12*i);
                }
                ofSetColor(255);
//                coinBag.draw(coinBagPos);
                ofPopMatrix();
            
                
            }break;
            case ICON_FADE:{
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                LDVelocity.y += LDGravity;
                LDPos +=LDVelocity;
                
                ofSetColor(255);
                ofPushMatrix();
                ofTranslate(LDPos);
                ofSetRectMode(OF_RECTMODE_CENTER);
                if (bLevelDone) {
                    LDBackgroudImg[0].draw(0,0);
                }else{
                    LDBackgroudImg[1].draw(0,0);
                }                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(30);
                fontBig.drawString(ofToString(score), scorePos.x-fontBig.stringWidth(ofToString(score))/2,scorePos.y -fontBig.stringHeight(ofToString(score))/2);
                font.drawString(ofToString(preCoin), totalPos.x-font.stringWidth(ofToString(preCoin))/2, totalPos.y -font.stringHeight(ofToString(preCoin))/2);
                for (int i=0; i<5; i++) {
                    ofSetColor(255);
                    int offset;
                    (i%2)==0?  offset = -5: offset = 5;
                    coinImg.draw( coinPos.x, coinPos.y-12*i);
                }
                ofSetColor(255);
//                coinBag.draw(coinBagPos);
                ofPopMatrix();
                
                
                if (LDPos.y > ofGetHeight()+LDRadius) {
                    LDType = BG_BACK;
                }
                
            }break;
            case BG_BACK:{
                
                if (*bgScale< 1) {
                    *bgScale+=0.001f;
                    LDAlpha -= 10;
                }else{
                    if (bLevelDone) {
                        bNextLevel = true;
                    }else if(bLevelFail){
                        bTryAgin = true;
                    }
                }
              

                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
            }break;
                
          
        }
    }
}

//-----------------------------------------------------------------------
void inGameMenu::scoreUpdate(){

    int fingerRate;
    
    if (*fingerSize ==5) {
        fingerRate = 20;
    }else if(*fingerSize ==6){
        fingerRate = 40;
    }else if(*fingerSize ==7){
        fingerRate = 100;
    }else if(*fingerSize ==8){
        fingerRate = 200;
    }
    
    score = fingerRate*(*fingerSize) + (*coin - preCoin) + (int)((*gameTimer));
    
    if (bLevelFail) {
        score = 0;
    }
    
    *coin +=score;
}

//-----------------------------------------------------------------------
void inGameMenu::pause(){
    
    
    if (bPauseL || bPauseR) {
        float speed = 0.1f;
       
        ofSetColor(255, 200);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        if (bPauseL) {
            resumeRect.posa.set(-resumeRect.button->getWidth(), ofGetHeight()/2);
            homeRect.posa.set(-homeRect.button->getWidth(), ofGetHeight()/2);

        }
        else if (bPauseR) {
            resumeRect.posa.set(ofGetWidth()+resumeRect.button->getWidth(), ofGetHeight()/2);
            homeRect.posa.set(ofGetWidth()+homeRect.button->getWidth(), ofGetHeight()/2);
        }
        
        homeRect.posb.set(ofGetWidth()/2+200, ofGetHeight()/2);
        resumeRect.posb.set(ofGetWidth()/2-150, ofGetHeight()/2);

        pausePct+=speed;
        if (pausePct>1) {
            pausePct = 1;
        }
        
        homeRect.interpolateByPct(pausePct);
        resumeRect.interpolateByPct(pausePct);
        
        ofSetColor(255);
        resumeRect.drawPause();
        homeRect.drawPause();
    }
    
    
//    cout<<accFrc->y<<" "<<bPauseL<<" "<<bPauseR<<" "<<pausePct<<" "<<homeRect.pos<<" "<<resumeRect.pos<<endl;


}
