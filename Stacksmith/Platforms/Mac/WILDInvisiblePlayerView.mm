//
//  WILDInvisiblePlayerView.mm
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-03-02.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#import "WILDInvisiblePlayerView.h"
#include "CAlert.h"


using namespace Carlson;


@implementation WILDInvisiblePlayerView

@synthesize owningPart = owningPart;

-(void)	mouseDown: (NSEvent *)theEvent
{
	if( owningPart )
	{
		CAutoreleasePool		pool;
		owningPart->SendMessage( NULL, [](const char *errMsg, size_t inLineOffset, size_t inOffset, CScriptableObject* inErrObj){ CAlert::RunScriptErrorAlert( inErrObj, errMsg, inLineOffset, inOffset ); }, "mouseDown %ld", [theEvent buttonNumber] );
	}
}


-(void)	mouseDragged: (NSEvent *)theEvent
{
	if( owningPart )
	{
		CAutoreleasePool		pool;
		owningPart->SendMessage( NULL, [](const char *errMsg, size_t inLineOffset, size_t inOffset, CScriptableObject* inErrObj){ CAlert::RunScriptErrorAlert( inErrObj, errMsg, inLineOffset, inOffset ); }, "mouseDrag %ld", [theEvent buttonNumber] );
	}
}


-(void)	mouseUp: (NSEvent *)theEvent
{
	if( owningPart )
	{
		CAutoreleasePool		pool;
		owningPart->SendMessage( NULL, [](const char *errMsg, size_t inLineOffset, size_t inOffset, CScriptableObject* inErrObj){ CAlert::RunScriptErrorAlert( inErrObj, errMsg, inLineOffset, inOffset ); }, "mouseUp %ld", [theEvent buttonNumber] );
	}
}

@end
