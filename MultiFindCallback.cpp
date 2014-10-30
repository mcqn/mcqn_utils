// (c) Copyright 2014 MCQN Ltd

#include "MultiFindCallback.h"

FindItemCallback::FindItemCallback(const char* aFindString, CallbackFn aCallback, void* aUserData)
  : FindItem(aFindString), iCallback(aCallback), iUserData(aUserData)
{
}

void FindItemCallback::makeCallback()
{
  iCallback(iFindString, iUserData);
}


MultiFindCallback::MultiFindCallback(FindItemCallback* aItemsToFind, int aCount)
  : iItems(aItemsToFind), iCount(aCount)
{
}

void MultiFindCallback::reset()
{
  // Start from scratch
  for (int i =0; i < iCount; i++)
  {
    iItems[i].reset();
  }
}

bool MultiFindCallback::find(Stream& aStream)
{
  // Now go looking
  int c;
  do
  {
    c = aStream.read();
    if (c >= 0)
    {
Serial.print((char)c);
      for (int i =0; i < iCount; i++)
      {
        if (iItems[i].checkChar(c))
        {
          // We've found a string!
          iItems[i].makeCallback();
          return true;
        }
      }
    }
  } while (c != -1);

  // If we get here, we haven't found it
  return false;
}

