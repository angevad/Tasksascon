#include "stdafx.h"
#include "FileList.h"

using namespace std;

CFileList::CFileList (CString *pWorkDir)
  {
  m_sWorkDir = *pWorkDir;
  m_b_F_Set = m_b_R_Set = false;
  }

bool CFileList::Parser (int nArgc, _TCHAR *sPath[])
  {
  bool bSuccess (false);

  int nFindSymbol (0);
  m_sAppPath = sPath[0];
  CString sTmp;
  
  if (nArgc > 1)
    {
    for (int n(1); n < nArgc; n++)
      {
      sTmp = sPath[n];
      sTmp.MakeUpper ();
      if (sTmp == "-F")
        m_b_F_Set = true;
      else if (m_b_F_Set)
        {
        m_sDirPath = sTmp;
        m_b_F_Set = false;
        }
      if (sTmp == "-R")
        m_b_R_Set = true;
      else if (m_b_R_Set)
        {
        m_sFMask = sTmp;
        CString sTmpMask (m_sFMask);

        do
          {
          nFindSymbol = sTmpMask.Find (_T("\\"));
          if (nFindSymbol != -1)
            {
            sTmp.GetBufferSetLength (nFindSymbol);
            if (nFindSymbol == 0)
              sTmpMask.Delete (0);
            else
              {
              sTmpMask.CopyChars (sTmp.GetBuffer (), sTmpMask, nFindSymbol);
              if ((sTmp.Find ('*') != -1) && (sTmp.GetLength () > 1))
                m_vsFMask.push_back ("");
              else
                m_vsFMask.push_back (sTmp);
              sTmpMask.Delete (0, nFindSymbol + 1);
              }
            }
          } 
        while (nFindSymbol != -1);
        
        m_vsFMask.push_back (sTmpMask);

        m_b_R_Set = false;
        bSuccess = true;
        }
      }
    if (m_sDirPath.IsEmpty ())
      {
      m_sDirPath = m_sWorkDir;
      }
    }
  return bSuccess;
  }

void CFileList::Scan (CString sPath, vector<CString> *pvsMask, int nIndMask /*= 0*/)
  {
  if (UINT (nIndMask) < m_vsFMask.size ())
    {
    HANDLE hFind;
    WIN32_FIND_DATA FindData;
    CString sFileName;
    CString sFullPath;

//// IT MAY IMPLEMENT AS NEW FUNCTION
    if (m_vsFMask.at (nIndMask).Find ('*') == -1)
      sFullPath = sPath + '*';
    else
      sFullPath = sPath + m_vsFMask.at (nIndMask);

    for (UINT n (nIndMask); n < m_vsFMask.size (); n++)
      {
      if (m_vsFMask.at (n).Find ('*') == -1)
        {
        nIndMask = n;
        break;
        }
      }
////////////////////

    hFind = FindFirstFile (sFullPath, &FindData);
    if (hFind == INVALID_HANDLE_VALUE)
      {
      GetLastError ();
      return;
      }
    else
      {
      do
        {
        sFileName = FindData.cFileName;
        sFileName.MakeUpper ();
        if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
          {
          if (sFileName == m_vsFMask.at (nIndMask))
            {
            m_vsFoundResult.push_back (sPath + FindData.cFileName);
            Scan (sPath + FindData.cFileName + "\\", &m_vsFMask, nIndMask + 1);
            }
          else if (UINT (nIndMask) < m_vsFMask.size () - 1)
            {
            if ((sFileName != CString (".")) && (sFileName != CString("..")))
              Scan (sPath + FindData.cFileName + "\\", &m_vsFMask, nIndMask);
            }
          }
        else
            {
            if (nIndMask == (m_vsFMask.size () - 1))
              m_vsFoundResult.push_back (sPath + FindData.cFileName);
            }
        }
        while (FindNextFile (hFind, &FindData));
      }
    }
  }

CString& CFileList::GetDirPath ()
  {
  return m_sDirPath;
  }

vector<CString>& CFileList::GetMask ()
  {
  return m_vsFMask;
  }

vector<CString>& CFileList::GetFoundResult ()
  {
  return m_vsFoundResult;
  }