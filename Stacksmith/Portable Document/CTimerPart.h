//
//  CTimerPart.h
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-01-02.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#ifndef __Stacksmith__CTimerPart__
#define __Stacksmith__CTimerPart__

#include "CPart.h"
#include <string>
#include "CTimer.h"


namespace Carlson {

class CTimerPart : public CPart
{
public:
	explicit CTimerPart( CLayer *inOwner );
	
	virtual void			SetStarted( bool inStarted )	{ mStarted = inStarted; if( inStarted ) mActualTimer.Start(); else mActualTimer.Stop(); IncrementChangeCount(); };
	virtual bool			GetStarted()					{ return mStarted; };
	
	virtual void			SetInterval( long long inInterval )	{ mInterval = inInterval; mActualTimer.SetInterval( inInterval ); IncrementChangeCount(); };
	virtual long long		GetInterval()						{ return mInterval; };

	virtual std::string		GetMessage()						{ return mMessage; };
	virtual void			SetMessage( const std::string& inMessage )	{ mMessage = inMessage; IncrementChangeCount(); };

	virtual void			SetRepeat( bool n )					{ mRepeat = n; IncrementChangeCount(); };
	bool					GetRepeat()							{ return mRepeat; };

	virtual bool			GetPropertyNamed( const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd, LEOContext* inContext, LEOValuePtr outValue );
	virtual bool			SetValueForPropertyNamed( LEOValuePtr inValue, LEOContext* inContext, const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd );
	
	virtual std::vector<CAddHandlerListEntry>	GetAddHandlerList();

	virtual void			WakeUp();
	virtual void			GoToSleep();
	
protected:
	virtual void			LoadPropertiesFromElement( tinyxml2::XMLElement * inElement );
	virtual void			SavePropertiesToElement( tinyxml2::XMLElement * inElement );
	
	virtual const char*		GetIdentityForDump()	{ return "Timer"; };
	virtual void			DumpProperties( size_t inIndent );
	
	virtual void			Trigger();
	
protected:
	std::string		mMessage;
	long long		mInterval;
	bool			mStarted;
	bool			mRepeat;
	CTimer			mActualTimer;
};

}

#endif /* defined(__Stacksmith__CTimerPart__) */
