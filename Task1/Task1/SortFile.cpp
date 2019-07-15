#include "stdafx.h"

#include "SortFile.h"

CSortFile::CSortFile (char *psFileName)
  {
  errno_t err = strcpy_s (m_sFileName, psFileName);
  if (err == 0)
    FileOpen (psFileName);
  else
    FileOpen ("tmp_chach.bin");
  }

bool CSortFile::FileOpen (char *psFileName)
  {
  m_err_File = fopen_s (&m_pfile, psFileName, "wb+");
  if (m_err_File == 0)
    return true;
  else
    return false;
  }

CSortFile::~CSortFile ()
  {
  fclose (m_pfile);
  remove (m_sFileName);
  }

void CSortFile::Generate (int nSizeOf)
  {
  for (int n (0); n < nSizeOf; n++)
    {
    try
      {
      m_dVal.push_back ((rand() / (double)RAND_MAX) * 1000.0);
      }
    catch (...)
      {
      if (AddToCache ())
        {
        m_nParts.push_back (m_dVal.size ());
        m_dVal.clear ();
        }
      }
    }
  if (SaveFile (0))
    {
    m_nParts.push_back (m_dVal.size ());
    m_dVal.clear ();
    }
  m_bSorted = false;
  }

void CSortFile::Sort ()
  {
  int nSeek = 0;
  vector<int>::iterator iter;
  if (m_nParts.size ())
    {
    iter = m_nParts.begin ();
  do
    {
    LoadFromCache (iter[0], nSeek);
    sort (m_dVal.begin (), m_dVal.end ());
    SaveFile (nSeek);
    nSeek += iter[0];
    } while (++iter != m_nParts.end ());
  m_bSorted = true;
    }
  else
    m_bSorted = false;
  }

bool CSortFile::SaveFile (int nSeek)
  {
  if (m_err_File == 0)
    {
    fseek (m_pfile, nSeek, SEEK_SET);
    for (vector<double>::iterator iter = m_dVal.begin (); iter != m_dVal.end (); iter++)
      fwrite (&iter[0], sizeof (double), 1, m_pfile);
  
    m_dVal.clear ();
    fflush (m_pfile);

    return (true);
    }
  else
    return (false);
  }

bool CSortFile::AddToCache ()
  {
  if (m_err_File == 0)
    {
    int nSize = m_dVal.size ();
    if (nSize)
      {
      m_nParts.push_back (nSize);
      for (vector<double>::iterator iter = m_dVal.begin (); iter != m_dVal.end (); iter++)
        fwrite (&iter[0], sizeof (double), 1, m_pfile);
      fflush (m_pfile);
      return true;
      }
    }
  return false;
  }

void CSortFile::LoadFromCache (int nSize, int nSeek)
  {
  double dCache;
  m_dVal.clear ();

  nSeek = fseek (m_pfile, nSeek, SEEK_SET);
  for (int n (0); n < nSize; n++)
    {
    fread (&dCache, sizeof (double), 1, m_pfile);
    m_dVal.push_back (dCache);
    }
  }