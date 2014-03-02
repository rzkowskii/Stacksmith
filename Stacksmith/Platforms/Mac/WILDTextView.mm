//
//  WILDTextView.m
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-03-02.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#import "WILDTextView.h"
#include "CAlert.h"

using namespace Carlson;


@implementation WILDTextView

@synthesize owningPart = owningPart;

-(void)	mouseDown: (NSEvent*)evt
{
	if( owningPart )
	{
		owningPart->SendMessage( NULL, [](const char *errMsg, size_t inLineOffset, size_t inOffset, CScriptableObject* inErrObj){ CAlert::RunScriptErrorAlert( inErrObj, errMsg, inLineOffset, inOffset ); }, "mouseDown %ld", [evt buttonNumber] );
	}
	[super mouseDown: evt];
	if( owningPart )
	{
		owningPart->SendMessage( NULL, [](const char *errMsg, size_t inLineOffset, size_t inOffset, CScriptableObject* inErrObj){ CAlert::RunScriptErrorAlert( inErrObj, errMsg, inLineOffset, inOffset ); }, "mouseUp %ld", [evt buttonNumber] );
	}
}


//-(void)	mouseUp: (NSEvent*)evt
//{
//	NSLog(@"mouseUp START");
//	[super mouseUp: evt];
//	NSLog(@"mouseUp END");
//}

@end
