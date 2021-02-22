#include <iostream>
#include <map>
#include <set>

using namespace std;

// Comparison function for sorting the set by increasing order of its pair's
// second value. If second value are equal, order by the pair's first value
struct comp
{
    template<typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second)
            return l.second > r.second;
 
        return l.first > r.first;
    }
};

void decryptMessage(string message, string freqLang);
map<char, size_t> CompareAndCount(string msgBackup);
set<pair<char, size_t>, comp> SortMap(map<char, size_t> map);
string Replace(string message, set<pair<char, size_t>, comp> set, string freqLang);

int main()
{
    string message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
    string freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";

    decryptMessage(message, freqLang);

    return 0;
}

void decryptMessage(string message, string freqLang)
{
    string msg;
    map<char, size_t> map;
    set<pair<char, size_t>, comp> set;

    map = CompareAndCount(message);
    set = SortMap(map);
    msg = Replace(message, set, freqLang);

    cout << msg;
}

map<char, size_t> CompareAndCount(string msgBackup)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    map<char, size_t> _map;

    // First made a list of alphabet characters to count and initialize in 0.
    for (auto ch : alphabet)
        _map[ch] = 0;

    // Then count ONLY the inserted characters.
    for (auto ch : msgBackup) 
    {
        auto it = _map.find(tolower(ch));
        if (it != _map.end())
            ++it->second;
    }

    // Print the letter and his frecuency.
    /*for (auto pair : _map)
        if (pair.second > 0)
            cout << '\'' << pair.first << "\'\t" << pair.second << endl;*/

    return _map;
}

set<pair<char, size_t>, comp> SortMap(map<char, size_t> map)
{
    // Sort the vector
    // create an empty vector of pairs
    set<pair<char, size_t>, comp>set(map.begin(), map.end());
 
    // Print the vector in order
    /*for (auto const &pair: set) 
    {
       cout << '{' << pair.first << "," << pair.second << '}' << '\n';
    }*/

    return set;
}

string Replace(string message, set<pair<char, size_t>, comp> set, string freqLang)
{
    string msgBackup = message;

    //Replace letters
    int msgIndex = 0;
    int replaceIndex = 0;
    for (auto const &pair: set) 
    {
        for (auto ch : msgBackup) 
        {
            if(ch == pair.first)
            {
                message[msgIndex] = tolower(freqLang[replaceIndex]);
            }
            if(ch == toupper(pair.first))
            {
                message[msgIndex] = freqLang[replaceIndex];
            }
            msgIndex++;
        }
        msgIndex = 0;
        replaceIndex++;
    }

    return message;
}