//
//  AlertViewDelegate.m
//  emptyExample
//
//  Created by lukasz karluk on 22/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AlertViewDelegate.h"
#import "testApp.h"

@implementation AlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{

    if(buttonIndex == 0){
        
        cout<<"0"<<endl;

    } else if(buttonIndex == 1){
       
        cout<<"1"<<endl;
  
    } else {
        cout<<"2"<<endl;
    }
    
}

@end
