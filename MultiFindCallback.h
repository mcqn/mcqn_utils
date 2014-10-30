// Non-blocking version of MultiFind which calls a callback
// function when it finds a match
//
// (c) Copyright 2014 MCQN Ltd

#ifndef MULTIFINDCALLBACK_H
#define MULTIFINDCALLBACK_H

#include "MultiFind.h"

typedef void (*CallbackFn)(const char* aMatchString, void* aUserData);

class FindItemCallback : public FindItem
{
public:
  FindItemCallback(const char* aFindString =NULL, CallbackFn aCallback =NULL, void* aUserData =NULL);
  void makeCallback();
protected:
  CallbackFn iCallback;
  void* iUserData;
};

class MultiFindCallback
{
public:
  MultiFindCallback(FindItemCallback* aItemsToFind, int aCount);
  void reset();
  // Find one of the given items and if so, call its callback
  // @param aStream - stream to search
  // @return true if it found an item (and called the callback)
  //         otherwise it didn't find an item
  bool find(Stream& aStream);
protected:
  FindItemCallback* iItems;
  int iCount;
};


#endif

