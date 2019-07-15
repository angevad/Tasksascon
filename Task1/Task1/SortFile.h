#include <vector>
#include <algorithm>

using namespace std;

class CSortFile
  {
  public:
    CSortFile (char *psFileName);
    ~CSortFile ();
    void       Generate (int nSizeOf);
    void       Sort ();
    const bool isSorted () {return m_bSorted;};
  protected:
    bool       FileOpen (char *psFileName);
    bool       AddToCache ();
    void       LoadFromCache (int nSize, int nSeek);
    bool       SaveFile (int nSeek);
  protected:
    vector<double> m_dVal;
    vector<double> m_dValCache;
    vector<int>    m_nParts;
    bool           m_bSorted;
    FILE           *m_pfile;
    errno_t        m_err_File; 
    char           m_sFileName[30];
  };