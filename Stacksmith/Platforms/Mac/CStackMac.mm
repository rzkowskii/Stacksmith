//
//  CStackMac.mm
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-01-06.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#include "CStackMac.h"
#import <AppKit/AppKit.h>
#include "CButtonPart.h"
#include "CFieldPart.h"
#include "CMoviePlayerPart.h"
#include "CWebBrowserPart.h"
#include "CTimerPart.h"
#include "CRectanglePart.h"
#include "CPicturePart.h"


using namespace Carlson;


@interface WILDFlippedContentView : NSView

@end

@implementation WILDFlippedContentView

-(BOOL)	isFlipped { return YES; };

@end



class CMacPartBase
{
public:
	virtual void	CreateViewIn( NSView* inSuperView ) = 0;
	virtual void	DestroyView() = 0;

	virtual ~CMacPartBase() {};
};

template<class T>
class CMacPart : public CMacPartBase
{
public:
	CMacPart( T* inThis ) { mPart = inThis; };
	
	virtual void	CreateViewIn( NSView* inSuperView )	{ if( mView ) [mView release]; mView = [[NSBox alloc] initWithFrame: NSMakeRect(mPart->mLeft, mPart->mTop, mPart->mRight -mPart->mLeft, mPart->mBottom -mPart->mTop)]; [(NSBox*)mView setBoxType: NSBoxCustom]; [(NSBox*)mView setTitlePosition: NSNoTitle]; [inSuperView addSubview: mView]; };
	virtual void	DestroyView()						{ [mView removeFromSuperview]; [mView release]; mView = nil; };

protected:
	virtual ~CMacPart() {};
	
	NSView*		mView;
	T*			mPart;
};


class CButtonPartMac : public CButtonPart, public CMacPart<CButtonPartMac>
{
public:
	CButtonPartMac( CLayer *inOwner ) : CButtonPart( inOwner ), CMacPart(this) {};
	
	friend class CMacPart<CButtonPartMac>;
};


class CFieldPartMac : public CFieldPart, public CMacPart<CFieldPartMac>
{
public:
	CFieldPartMac( CLayer *inOwner ) : CFieldPart( inOwner ), CMacPart(this) {};
	
	friend class CMacPart<CFieldPartMac>;
};

class CMoviePlayerPartMac : public CMoviePlayerPart, public CMacPart<CMoviePlayerPartMac>
{
public:
	CMoviePlayerPartMac( CLayer *inOwner ) : CMoviePlayerPart( inOwner ), CMacPart(this) {};
		
	friend class CMacPart<CMoviePlayerPartMac>;
};

class CWebBrowserPartMac : public CWebBrowserPart, public CMacPart<CWebBrowserPartMac>
{
public:
	CWebBrowserPartMac( CLayer *inOwner ) : CWebBrowserPart( inOwner ), CMacPart(this) {};
		
	friend class CMacPart<CWebBrowserPartMac>;
};



@interface WILDStackWindowController : NSWindowController <NSWindowDelegate>
{
	CStackMac	*	mStack;
}

-(id)	initWithCppStack: (CStackMac*)inStack;

-(void)	removeAllViews;
-(void)	createAllViews;

@end

@implementation WILDStackWindowController

-(id)	initWithCppStack: (CStackMac*)inStack
{
	NSRect			wdBox = NSMakeRect(0,0,inStack->GetCardWidth(),inStack->GetCardHeight());
	NSWindow	*	theWindow = [[[NSWindow alloc] initWithContentRect: wdBox styleMask: NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask backing: NSBackingStoreBuffered defer: NO] autorelease];
	NSView*	cv = [[[WILDFlippedContentView alloc] initWithFrame: wdBox] autorelease];
	theWindow.contentView = cv;
	[theWindow setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];
	[theWindow setTitle: [NSString stringWithUTF8String: inStack->GetName().c_str()]];
	[theWindow setRepresentedURL: [NSURL URLWithString: [NSString stringWithUTF8String: inStack->GetURL().c_str()]]];
	[theWindow center];
	[theWindow setDelegate: self];

	self = [super initWithWindow: theWindow];
	if( self )
	{
		mStack = inStack;
	}
	
	return self;
}

-(void)	removeAllViews
{
	CCard	*	theCard = mStack->GetCurrentCard();
	if( !theCard )
		return;
	
	size_t	numParts = theCard->GetNumParts();
	for( size_t x = 0; x < numParts; x++ )
	{
		CMacPartBase*	currPart = dynamic_cast<CMacPartBase*>(theCard->GetPart(x));
		if( !currPart )
			continue;
		currPart->DestroyView();
	}
}

-(void)	createAllViews
{
	CCard	*	theCard = mStack->GetCurrentCard();
	if( !theCard )
		return;
	
	size_t	numParts = theCard->GetNumParts();
	for( size_t x = 0; x < numParts; x++ )
	{
		CMacPartBase*	currPart = dynamic_cast<CMacPartBase*>(theCard->GetPart(x));
		if( !currPart )
			continue;
		currPart->CreateViewIn( self.window.contentView );
	}
}

@end


CStackMac::CStackMac( const std::string& inURL, WILDObjectID inID, const std::string& inName, CDocument * inDocument )
	: CStack( inURL, inID, inName, inDocument )
{
	mMacWindowController = nil;
}


bool	CStackMac::GoThereInNewWindow( bool inNewWindow )
{
	if( !mMacWindowController )
		mMacWindowController = [[WILDStackWindowController alloc] initWithCppStack: this];
	[mMacWindowController showWindow: nil];
	
	return true;
}


void	CStackMac::SetCurrentCard( CCard* inCard )
{
	if( !mMacWindowController )
		mMacWindowController = [[WILDStackWindowController alloc] initWithCppStack: this];

	[mMacWindowController removeAllViews];
	
	CStack::SetCurrentCard(inCard);
	
	[mMacWindowController createAllViews];
}


void	CStackMac::RegisterPartCreators()
{
	static bool	sAlreadyDidThis = false;
	if( !sAlreadyDidThis )
	{
		CPart::RegisterPartCreator( new CPartCreator<CButtonPartMac>( "button" ) );
		CPart::RegisterPartCreator( new CPartCreator<CFieldPartMac>( "field" ) );
		CPart::RegisterPartCreator( new CPartCreator<CWebBrowserPartMac>( "browser" ) );
		CPart::RegisterPartCreator( new CPartCreator<CMoviePlayerPartMac>( "moviePlayer" ) );
		CPart::RegisterPartCreator( new CPartCreator<CTimerPart>( "timer" ) );
		CPart::RegisterPartCreator( new CPartCreator<CRectanglePart>( "rectangle" ) );
		CPart::RegisterPartCreator( new CPartCreator<CPicturePart>( "picture" ) );
		
		sAlreadyDidThis = true;
	}
}
