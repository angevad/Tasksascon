// Task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "FileList.h"
#include <iostream>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
  {
  char buf[255];
  vector<CString> *pResult;
  CString sAppPath = *argv;
  CString sWorkDir;
  int n = sAppPath.ReverseFind ('\\');

  sWorkDir.GetBufferSetLength (n + 1);
  sAppPath.CopyChars (sWorkDir.GetBuffer (), sAppPath, n + 1);

  wcout << "Find result:" << endl;
  CFileList FileList (&sWorkDir);
  if (FileList.Parser (argc, argv))
    FileList.Scan (FileList.GetDirPath (), &FileList.GetMask ());

  pResult = &FileList.GetFoundResult ();
  for (vector<CString>::iterator iter = pResult->begin (); iter != pResult->end (); iter++)
    {
    CharToOem (iter->GetString (), buf);
    wcout << buf << endl;
    }

  cout<< endl << "Press any key";
  cin.get ();
	return 0;
  }

