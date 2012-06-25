// 
// File:   AES.h
// $Id: AES.h 9 2010-08-19 17:42:20Z df2417 $
//
//

#ifndef AES_H
#define	AES_H

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>

using namespace std;

class AES {
public:
    AES();
    AES(const AES& orig);
    virtual ~AES();
    string& encrypt(string& s);
    string& decrypt(string& s);
private:
    
};

#endif	/* AES_H */

