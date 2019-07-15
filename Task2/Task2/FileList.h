#include <windows.h>
#include "atlstr.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class CFileList
  {
  public:
    CFileList (CString *pWorkDir);
    void Scan (CString sPath, vector<CString> *pvsMask, int nIndMask = 0);
    bool Parser (int nArgc, _TCHAR *sPath[]);
    CString& GetDirPath ();
    vector<CString>& GetMask ();
    vector<CString>& GetFoundResult ();
  protected:
    bool m_b_F_Set;
    bool m_b_R_Set;

    CString m_sDirPath;
    CString m_sAppPath;
    CString m_sWorkDir;
    CString m_sFMask;
    CString m_sFExt;
    vector<int> m_vnMask;
    vector<CString> m_vsFMask;
    vector<CString> m_vsFoundResult;
  };