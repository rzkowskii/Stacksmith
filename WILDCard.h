//
//  WILDCard.h
//  Propaganda
//
//  Created by Uli Kusterer on 28.02.10.
//  Copyright 2010 The Void Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "WILDBackground.h"
#import "WILDSearchContext.h"


@interface WILDCard : WILDBackground <WILDSearchable>
{
	WILDBackground	*	mOwner;
}

-(id)						initWithXMLDocument: (NSXMLElement*)elem forStack: (WILDStack*)theStack;

-(NSInteger)				backgroundID;	// ID of *owning* background.
-(WILDBackground*)			owningBackground;
-(void)						setOwningBackground: (WILDBackground*)theBg;

-(NSInteger)				cardID;			// ID of this card block.

-(NSInteger)				cardNumber;

@end