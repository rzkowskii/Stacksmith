//
//  CScriptableObjectValue.h
//  Stacksmith
//
//  Created by Uli Kusterer on 16.04.11.
//  Copyright 2011 Uli Kusterer. All rights reserved.
//

/*!
	@header CScriptableObjectValue
	This file contains everything that is needed to interface Stacksmith's
	CConcreteObject-based object hierarchy (buttons, fields, cards) with the
	Leonie bytecode interpreter. This allows performing common operations on
	them (like retrieve property values, change their value, call handlers
	in their scripts, add user properties etc.
	
	So that the Leonie bytecode interpreter can deal with objects of this type,
	it also defines kLeoValueTypeScriptableObject, which is like a native object,
	but guarantees that the object conforms to the CScriptableObject protocol.
	
	You can create such a value using the <tt>CInitScriptableObjectValue</tt> function,
	just like any other values.
*/

#ifndef __Stacksmith__CScriptableObjectValue__
#define __Stacksmith__CScriptableObjectValue__

#include "LEOValue.h"
#include "CRefCountedObject.h"
#include <string>
#include <functional>
#include "LEOScript.h"
#include "LEOInterpreter.h"



extern struct LEOValueType	kLeoValueTypeScriptableObject;


namespace Calhoun
{

class CStack;


class CScriptableObject : public CRefCountedObject
{
public:
	virtual ~CScriptableObject() {};
	
// The BOOL returns on these methods indicate whether the given object can do
//	what was asked (as in, ever). So if a property doesn't exist, they'd return
//	NO. If an object has no contents, the same.

	bool				GetTextContents( std::string& outString )		{ return false; };
	bool				SetTextContents( std::string inString)			{ return false; };

	bool				GoThereInNewWindow( bool inNewWindow )			{ return false; };

	bool				GetPropertyNamed( const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd, LEOValuePtr outValue )						{ return false; };
	bool				SetValueForPropertyNamed( LEOValuePtr inValue, const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd )	{ return false; };

	LEOScript*			GetScriptObject( std::function<void(const char*,size_t,size_t,CScriptableObject*)> errorHandler )								{ return NULL; };
	CScriptableObject*	GetParentObject()								{ return NULL; };

	CStack*				GetStack()			{ return NULL; };
	bool				DeleteObject()		{ return false; };

	void				OpenScriptEditorAndShowOffset( size_t byteOffset )	{};
	void				OpenScriptEditorAndShowLine( size_t lineIndex )		{};

	bool				AddUserPropertyNamed( const char* userPropName )	{ return false; };
	bool				DeleteUserPropertyNamed( const char* userPropName )	{ return false; };
	size_t				GetNumUserProperties()								{ return 0; };
	std::string			GetUserPropertyNameAtIndex( size_t inIndex )		{ return std::string(); };
	bool				SetUserPropertyNameAtIndex( const char* inNewName, size_t inIndex )	{ return false; };
	bool				GetUserPropertyValueForName( const char* inPropName, LEOValuePtr outValue )	{ return false; };
	bool				SetUserPropertyValueForName( LEOValuePtr inValue, const char* inPropName )	{ return false; };
	static void			InitScriptableObjectValue( LEOValueObject* inStorage, CScriptableObject* wildObject, LEOKeepReferencesFlag keepReferences, LEOContext* inContext );
	static LEOScript*	GetParentScript( LEOScript* inScript, LEOContext* inContext );

	static CScriptableObject*	GetOwnerScriptableObjectFromContext( LEOContext * inContext );
};



}

#endif /* defined(__Stacksmith__CScriptableObjectValue__) */
