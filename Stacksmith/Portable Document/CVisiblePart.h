//
//  CVisiblePart.h
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-01-02.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

/*
	Base class for all parts that are real visible objects on screen,
	as opposed to e.g. timers, which are only visible during editing.
	Provides default code for reading/writing a few more properties
	shared by all these "visible" objects.
*/

#ifndef __Stacksmith__CVisiblePart__
#define __Stacksmith__CVisiblePart__

#include "CPart.h"


namespace Calhoun {

enum EPartTextAlign
{
	CPartTextAlignDefault = 0,	// "natural" text alignment. Whatever the user expects from the OS.
	CPartTextAlignLeft,
	CPartTextAlignCenter,
	CPartTextAlignRight,
	CPartTextAlignJustified
};
typedef unsigned	CPartTextAlign;


enum EPartTextStyle
{
	CPartTextStylePlain		= 0,
	CPartTextStyleBold		= (1 << 0),
	CPartTextStyleItalic	= (1 << 1),
	CPartTextStyleUnderline	= (1 << 2),
	CPartTextStyleOutline	= (1 << 3),
	CPartTextStyleShadow	= (1 << 4),
	CPartTextStyleCondensed	= (1 << 5),
	CPartTextStyleExtended	= (1 << 6)
};
typedef unsigned	CPartTextStyle;


class CVisiblePart : public CPart
{
public:
	CVisiblePart( CLayer * inOwner ) : CPart(inOwner) {};

protected:
	virtual void			LoadPropertiesFromElement( tinyxml2::XMLElement * inElement );
	
	virtual void			DumpProperties( size_t inIndent );

protected:
	bool			mVisible;
	bool			mEnabled;
	int				mFillColorRed;
	int				mFillColorGreen;
	int				mFillColorBlue;
	int				mFillColorAlpha;
	int				mLineColorRed;
	int				mLineColorGreen;
	int				mLineColorBlue;
	int				mLineColorAlpha;
	int				mShadowColorRed;
	int				mShadowColorGreen;
	int				mShadowColorBlue;
	int				mShadowColorAlpha;
	double			mShadowOffsetWidth;
	double			mShadowOffsetHeight;
	double			mShadowBlurRadius;
	int				mLineWidth;
	int				mBevelWidth;
	int				mBevelAngle;
};

}

#endif /* defined(__Stacksmith__CVisiblePart__) */
