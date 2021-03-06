//
//  CGraphicPart.h
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-01-02.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#ifndef __Stacksmith__CGraphicPart__
#define __Stacksmith__CGraphicPart__

#include "CVisiblePart.h"
#include <set>

namespace Carlson {
	
	struct CPathSegment
	{
		LEONumber		x;
		LEONumber		y;
		LEONumber		lineWidth;
	};
	
	typedef enum
	{
		EGraphicStyleOval,
		EGraphicStyleRectangle,
		EGraphicStyleRoundrect,
		EGraphicStyleLine,
		EGraphicStyleBezierPath,
		EGraphicStyle_Last
	} TGraphicStyle;

	class CGraphicPart : public CVisiblePart
	{
	public:
		explicit CGraphicPart( CLayer *inOwner ) : CVisiblePart( inOwner ), mStyle(EGraphicStyleRectangle)	 {};
		
		void					SetStyle( TGraphicStyle inStyle )	{ mStyle = inStyle; };
		
		virtual bool			CanBeEditedWithTool( TTool inTool );
		virtual LEOInteger		GetNumCustomHandlesForTool( TTool inTool );	// -1 means no custom handles, use the standard 8.
		virtual void			SetPositionOfCustomHandleAtIndex( LEOInteger idx, LEONumber x, LEONumber y );
		virtual void			GetPositionOfCustomHandleAtIndex( LEOInteger idx, LEONumber *outX, LEONumber *outY );
		
		virtual bool			GetPropertyNamed( const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd, LEOContext* inContext, LEOValuePtr outValue );
		virtual bool			SetValueForPropertyNamed( LEOValuePtr inValue, LEOContext* inContext, const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd );
		
		virtual void			AddPoint( LEONumber x, LEONumber y, LEONumber lineWidth );
		virtual void			UpdateLastPoint( LEONumber x, LEONumber y, LEONumber lineWidth );
		
		virtual void			SizeToFit();
		
		virtual void			SetSelected( bool inSelected, LEOInteger inHandleIndex = EAllHandlesSelected );
		static void				ConvertPointsToStepSize( const std::vector<LEONumber>& inCoordinates, LEONumber stepSize, std::vector<LEONumber>& outCoordinates );
		
	protected:
		~CGraphicPart()	{};
		
		virtual void			LoadPropertiesFromElement( tinyxml2::XMLElement * inElement );
		virtual void			SavePropertiesToElement( tinyxml2::XMLElement * inElement );
		
		virtual const char*		GetIdentityForDump()	{ return "Graphic"; };
		virtual void			DumpProperties( size_t inIndent );

		static TGraphicStyle	GetGraphicStyleFromString( const char* inStr );
	
	protected:
		std::vector<CPathSegment>	mPoints;
		TGraphicStyle				mStyle;
	};
	
}

#endif /* defined(__Stacksmith__CGraphicPart__) */
