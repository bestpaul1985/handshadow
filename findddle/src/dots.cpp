


#include "dots.h"

//-------------------------------------------------------
void dots::setup(float x, float y,ofImage *A, ofImage *B, ofImage *C, ofImage *D){
    
    
    ofPoint tempPos;
    
    bSondPlay=false;

    if (x<512 && y<384) {
        //top Left
        tempPos.set(0, 0);
        
    }else if(x>512 && y<384){
        //top right
        tempPos.set(1024, 0);

    }else if(x<512 && y>384){
        //bot Left
        tempPos.set(0, 768);

    }else if(x>512 && y>384){
        //bot right
        tempPos.set(1024, 768);

    }else{
        
        tempPos.set(512,768);
    }
    
    posA.set(tempPos);
    posB.set(x,y);
    radius = 83;
    goalRaduis = 83;

    frezzerRadiusX = (int)187/2;
    frezzerRadiusY = (int)196/2;
    frezzerGoalRadiusX = (int)187/2;
    frezzerGoalRadiusY = (int)196/2;
    dot_normal = A;
    dot_pressed = B;
    dot_freezed = C;
    fingle = D;
    
    bRadiusExtend = false;
    bFreezed = false;
    radiusPct = 0;
    radiusPctOrg = 0;
    fingerSpeed = 0.05f;
    speed = 0.05f;
    
    pct = 0;
    fingerPct = 0;
    
    notMyId.clear();
    myId.clear();
    bCovered = false;
    bFixed = true;
    
    float dx;
    float dy;
    dx = posA.x - posB.x;
    dy = posA.y - posB.y;
    
    if (posB.x<512 && posB.y<384) {
        //top Left
        angle = atan2(dy, dx)*RAD_TO_DEG -90;
    }else if(posB.x>512 && posB.y<384){
        //top right
        angle = atan2(dy, dx)*RAD_TO_DEG -90;
        
    }else if(posB.x<512 && posB.y>384){
        
        //bot Left
        angle = atan2(dy, dx)*RAD_TO_DEG -90;
        
    }else if(posB.x>512 && posB.y>384){
        //bot right
        angle = atan2(dy, dx)*RAD_TO_DEG -90;
    }else{
        
        angle = 0;
    }

    extenderSpeed = 0.1f;
    effextStep = 0;
}

//-------------------------------------------------------
void dots::update(){
   

    radiusExtend();

    if (!bFixed) {
        
        pct+=speed;
        if (pct>1) {
            pct = 1;
        }else if(pct<0){
            pct = 0;
        }

        fingerPct+=fingerSpeed;
        if (fingerPct>1) {
            fingerSpeed = 0.03;
            fingerSpeed*=-1;
        }else if(fingerPct<0){
            fingerPct=0;
        }
    }
    
    float myPct = powf(pct, 0.6);
    pos.x = (1-myPct)*posA.x + myPct*posB.x;
    pos.y = (1-myPct)*posA.y + myPct*posB.y;
    
    float myFingerPct = powf(fingerPct, 0.6);
    fingerPos.x = (1-myFingerPct)*posA.x + myFingerPct*posB.x;
    fingerPos.y = (1-myFingerPct)*posA.y + myFingerPct*posB.y;

}

//-------------------------------------------------------
void dots::radiusExtendReset(){
    
    radiusPct = 0;
    radiusPctOrg = 0;
    bRadiusExtend = false;
}
//-------------------------------------------------------

void dots::radiusExtend(){
    
    if (bRadiusExtend) {
        
            if (effextStep == 0) {
    
            radiusPctOrg += extenderSpeed;
            radiusPct = powf(radiusPctOrg, 0.6);
            radius = (1-radiusPct)*radius + radiusPct*(goalRaduis*1.3);
        
        
            frezzerRadiusX = (1-radiusPct)*frezzerRadiusX + radiusPct*frezzerGoalRadiusX;
            frezzerRadiusY = (1-radiusPct)*frezzerRadiusY + radiusPct*frezzerGoalRadiusY;
            
            if (radiusPctOrg >=1) {
                radiusPctOrg = 0;
                effextStep = 1;
            }
                
            }else if (effextStep == 1){
            
                radiusPctOrg += extenderSpeed/2;
                radiusPct = powf(radiusPctOrg, 1.5);
               
                if (radiusPctOrg >=1) {
                    radiusPctOrg = 1;
                    bRadiusExtend = false;
                    effextStep = 0;
                }

                radius = (1-radiusPct)*radius + radiusPct*goalRaduis;
                frezzerRadiusX = (1-radiusPct)*frezzerRadiusX + radiusPct*frezzerGoalRadiusX;
                frezzerRadiusY = (1-radiusPct)*frezzerRadiusY + radiusPct*frezzerGoalRadiusY;

                
                
            }

    }
    
}



//-------------------------------------------------------
void dots::draw(){
    
    if (!bFixed) {
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        if (bRadiusExtend){
            ofSetColor(247, 90, 146, 50);
            float tempRadius = radius+1;
            ofCircle(0, 0, tempRadius);
        }
    
        ofSetColor(color);
        if (bCovered) dot_pressed->draw(-radius, -radius,radius*2,radius*2);
        else dot_normal->draw(-radius, -radius,radius*2,radius*2);
        if (bFreezed) {
            dot_freezed->draw(-frezzerRadiusX, -frezzerRadiusY,frezzerRadiusX*2,frezzerRadiusY*2);
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(fingerPos);
        ofRotateZ(angle);
        fingle->draw(-fingle->getWidth()/2, 0);
        ofPopMatrix();
        
    }
}

//-------------------------------------------------------
void dots::touchDown(int x, int y, int touchID){
    
    if (!bFixed&& !bFreezed) {
        ofPoint touchPos(x,y);
        if (pos.distance(touchPos) < radius) {
            myId.push_back(touchID);
            bSondPlay = true;
        }
        
        if (myId.size()>0) {
            bCovered = true;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
    
    
}

//-------------------------------------------------------
void dots::touchMove(int x, int y, int touchID){
    
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) > radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        if (myId.size()==0) {
            bCovered = false;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
}

//-------------------------------------------------------
void dots::touchUp(int x, int y, int touchID){
    
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) < radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        if (myId.size()==0) {
            bCovered = false;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
}





