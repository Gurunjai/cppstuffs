#include<iostream>
#include<cassert>
#include<string>

using namespace std;

class Searcher {
public:
    Searcher(char const *pat)
    {
        set(pat);
    }

    ~Searcher()
    {
        set(NULL);
    }

    void Reset(char const *pat)
    {
        set(pat);
    }

    Searcher& operator=(char const *pat)
    {
        set(pat);
        return *this;
    }

    void Dump() 
    {
        cout << "Preprocessed Indexing:\n";

        cout << m_prevPosLen << endl;
        cout << m_searchPatLen << endl;
        for (int k = 0; k < m_searchPatLen; k++) {
            cout << m_searchPattern[k] << " ";
        }
        cout << endl;

        for (int k = 0; k < m_searchPatLen; k++) {
            cout << m_searchPatPos[k] << " ";
        }
        cout << "\n\n\n";
    }

    bool SearchStr(const char *txt) {
        int N = strlen(txt);
       
        // std::function<bool(char, char)> equality = 
        //     m_bCaseSensitive
        //     ? [](char a, char b) {return a == b;} 
        //     : [](char a, char b) {return std::tolower(a) == std::tolower(b);};

        int i = 0;
        int j = m_prevPosLen;
        while ( i < N ) {
            if ( m_searchPattern[j] == txt[i] ) {
                i++;
                j++;
            }

            if ( j == m_searchPatLen ) {
                cout << "Pattern \"" << m_searchPattern << "\" has been found in the string:\t \"" << txt << "\"\n\n";
                return true;
            }
            else if ( i < N && m_searchPattern[j] != txt[i] ) {
                if ( j != 0 ) {
                    j = m_searchPatPos[ j - 1 ];
                } else {
                    i = i + 1;
                }
            }
        }

        m_prevPosLen = j;
        
        return false;
    }

private:
    void set(char const *pat)
    {
        m_prevPosLen = 0;
        m_searchPatLen = 0;
        if ( m_searchPattern != NULL )
        {
            free (m_searchPattern);
            m_searchPattern = NULL;
        }

        if ( m_searchPatPos != NULL )
        {
            free (m_searchPatPos);
            m_searchPatPos = NULL;
        }
    
        if ( pat != NULL )
        {
            m_searchPatLen = strlen(pat);
            m_searchPattern = new char[m_searchPatLen + 1];
            strncpy(m_searchPattern, pat, m_searchPatLen);
            m_searchPattern[m_searchPatLen] = '\0';

            m_searchPatPos = new int[m_searchPatLen];
            memset(m_searchPatPos, 0, m_searchPatLen);

            computeStrPos();
        }
    }

    void computeStrPos()
    {
        int len = 0;

        m_searchPatPos[0] = 0;

        int i = 1;

        while (i < m_searchPatLen) {
            if ( m_searchPattern[i] == m_searchPattern[len] ) {
                len++;
                m_searchPatPos[i] = len;
                i++;
            } else {
                if ( len != 0 ) {
                    len = m_searchPatPos[len - 1];
                } else {
                    m_searchPatPos[i] = 0;
                    i++;
                }
            }
        }

        return;
    }

    
private:
    int     *m_searchPatPos = NULL;
    char    *m_searchPattern = NULL;
    size_t   m_searchPatLen = 0;
    size_t   m_prevPosLen = 0;
};

int main() {
    Searcher sObj("is This Valid?");
    // sObj.Dump();
    
    for (int i = 0; i < 1000; i++) {
        assert(sObj.SearchStr("this is") == false);
    }
    assert(sObj.SearchStr(" This Valid??"));

    sObj = "WHAT IF";
    // sObj.Reset("WHAT IF is");
    // sObj.Dump();
    assert(sObj.SearchStr("The house is on fire, WHAT IF someone is inside"));

    sObj.Reset("Don't try it out");
    // sObj.Dump();
    assert(sObj.SearchStr("You can't find the string here") == false);

 
    return 0;
}