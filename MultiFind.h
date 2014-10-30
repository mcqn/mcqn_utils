//  
// (c) Copyright 2014 MCQN Ltd

#ifndef MULTIFIND_H
#define MULTIFIND_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class FindItem
{
public:
  FindItem(const char* aFindString =NULL);
  void reset();
  // FIXME Current algorithm doesn't cope with repeated strings
  // FIXME i.e. I think it wouldn't find "frefred" in "frefrefred"
  bool checkChar(char aChar);
protected:
  const char* iFindString;
  int iCurrentPos;
  int iLength;
};

class MultiFind
{
public:
  MultiFind(FindItem* aItemsToFind, int aCount);
  // Find one of the given items
  // @param aStream - stream to search
  // @return -1 if it failed to find any of them
  //         otherwise the index of the found item
  int find(Stream& aStream);
protected:
  // Because the version in Stream is protected and so inaccessible to us
  int timedRead(Stream& aStream);

  FindItem* iItems;
  int iCount;
};

class MultiFindNonBlocking
{
public:
  MultiFindNonBlocking(FindItem* aItemsToFind, int aCount);
  void reset();
  // Find one of the given items
  // @param aStream - stream to search
  // @return -1 if it failed to find any of them
  //         otherwise the index of the found item
  int find(Stream& aStream);
protected:
  FindItem* iItems;
  int iCount;
};


#endif
