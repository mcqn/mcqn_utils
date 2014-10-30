// (c) Copyright 2014 MCQN Ltd

#include "MultiFind.h"

FindItem::FindItem(const char* aFindString)
  : iFindString(aFindString)
{
  iLength = strlen(iFindString);
  reset();
}

void FindItem::reset()
{
  iCurrentPos = 0;
}

bool FindItem::checkChar(char aChar)
{
  if (iFindString[iCurrentPos] == aChar)
  {
    iCurrentPos++;
    if (iCurrentPos == iLength)
    {
      // We've found it!
      iCurrentPos = 0;
      return true;
    }
    else
    {
      // Getting closer, but not successfully
      return false;
    }
  }
  else
  {
    iCurrentPos = 0;
    return false;
  }
}

MultiFind::MultiFind(FindItem* aItemsToFind, int aCount)
  : iItems(aItemsToFind), iCount(aCount)
{
}

int MultiFind::timedRead(Stream& aStream)
{
  int c;
  unsigned long _startMillis = millis();
  unsigned long _timeout = 20*1000UL;
  do {
    c = aStream.read();
    if (c >= 0) return c;
  } while(millis() - _startMillis < _timeout);
  return -1;     // -1 indicates timeout
}

int MultiFind::find(Stream& aStream)
{
  // Start from scratch
  for (int i =0; i < iCount; i++)
  {
    iItems[i].reset();
  }

  // Now go looking
  int c;
  do
  {
    c = timedRead(aStream);
    if (c >= 0)
    {
      for (int i =0; i < iCount; i++)
      {
        if (iItems[i].checkChar(c))
        {
          // We've found a string!
          return i;
        }
      }
    }
  } while (c != -1);

  // If we get here, we haven't found it
  return -1;
}

MultiFindNonBlocking::MultiFindNonBlocking(FindItem* aItemsToFind, int aCount)
  : iItems(aItemsToFind), iCount(aCount)
{
}

void MultiFindNonBlocking::reset()
{
  // Start from scratch
  for (int i =0; i < iCount; i++)
  {
    iItems[i].reset();
  }
}

int MultiFindNonBlocking::find(Stream& aStream)
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
          return i;
        }
      }
    }
  } while (c != -1);

  // If we get here, we haven't found it
  return -1;
}

