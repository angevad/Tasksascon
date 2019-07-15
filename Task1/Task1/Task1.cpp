// Task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "SortFile.h"

int _tmain(int argc, _TCHAR* argv[])
  {
  CSortFile SortFile("cache.txt");

  cout << "Generate the file size of (1024 * 1024 * 1024) variables" << endl;
  SortFile.Generate (1024*1024*1024);
  cout << "The file was created." << endl;
  cout << "sorting file..." << endl;
  SortFile.Sort ();
  if (SortFile.isSorted ())
    cout << "File was sorted";
  else
    cout << "File wasn't sorted";
  cin.get ();
  return 0;
  }

