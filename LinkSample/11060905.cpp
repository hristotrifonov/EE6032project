// LinkSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>	// needed by CHILKAT e.g. for SystemTime

// added for CHILKAT
#include "..\include\ckimap.h" 
//#include "..\include\tchar.h"
//
// need this for various things
extern "C" {
#include "../include/allC.h"
#include "../include/allUnicodeC.h"
}
#include "../include/allUnicode.h"

// for the AES Encryption & Hashing
#include "../include/CkCrypt2.h"

// for RSA
#include "../include/CkRsa.h"

// get strings, because the const char* causes problems....
#include <iostream>
#include <string>
using namespace std;

// RSA example function. You may need to alter this to allow parameter passing etc..
void RSA_ex(void);

//Function to pause your program - for debugging purposes. Could also use this command [ system("pause"); ]
void key_press(void);

// This function is just to see if your files compile and link ok........its not needed for the project in EE6032/ED5012
void DoNothing(void);

void DoNothing(void)
{
	CkImap imap;
	imap.UnlockComponent("T12302015IMAPMAILQ_gdXOQ92bIRDN");
	imap.Connect("imap.gmail.com");

	CkFtp2W ftp2W;

	bool success = ftp2W.UnlockComponent(L"T12302015FTP_yJTfpTRHIR5l");

    HCkSFtpW c_sftp = CkSFtpW_Create();
    int isuccess = CkSFtpW_UnlockComponent(c_sftp,L"T12302015FTP_yJTfpTRHIR5l");
    CkSFtpW_Dispose(c_sftp);

    HCkImap c_imap = CkImap_Create();
    isuccess = CkImap_UnlockComponent(c_imap,"T12302015IMAPMAILQ_gdXOQ92bIRDN");
    CkImap_Dispose(c_imap);
}

void key_press(void)
{
	cout << "\nPress Any Key to Continue!\n\n";
	do {} while(!getchar());
}

void RSA_ex(void)
{
    CkRsa rsa;

    bool success;
    success = rsa.UnlockComponent("T12302015RSA_nn56BzHGIRMg");
    if (success != true) {
        printf("RSA component unlock failed\n");
        return;
    }

    //  This example also generates the public and private
    //  keys to be used in the RSA encryption.
    //  Normally, you would generate a key pair once,
    //  and distribute the public key to your partner.
    //  Anything encrypted with the public key can be
    //  decrypted with the private key.  The reverse is
    //  also true: anything encrypted using the private
    //  key can be decrypted using the public key.

    //  Generate a 1024-bit key.  Chilkat RSA supports
    //  key sizes ranging from 512 bits to 4096 bits.
    success = rsa.GenerateKey(1024);  //cut out the code and only use it wheen key generation is needed
    if (success != true) {
        printf("%s\n",rsa.lastErrorText());
        return;
    }

    //  Keys are exported in XML format:
    const char * publicKey;
    publicKey = rsa.exportPublicKey();
    const char * privateKey;
    privateKey = rsa.exportPrivateKey();

    const char * plainText;
    plainText = "Encrypting and decrypting should be easy!";

    //  Start with a new RSA object to demonstrate that all we
    //  need are the keys previously exported:
    CkRsa rsaEncryptor;

    //  Encrypted output is always binary.  In this case, we want
    //  to encode the encrypted bytes in a printable string.
    //  Our choices are "hex", "base64", "url", "quoted-printable".
    rsaEncryptor.put_EncodingMode("hex");

    //  We'll encrypt with the public key and decrypt with the private
    //  key.  It's also possible to do the reverse.
    rsaEncryptor.ImportPublicKey(publicKey);

    bool usePrivateKey;
    usePrivateKey = false;
    const char * encryptedStr;
    encryptedStr = rsaEncryptor.encryptStringENC(plainText,usePrivateKey);
    printf("%s\n",encryptedStr);

    //  Now decrypt:
    CkRsa rsaDecryptor;

    rsaDecryptor.put_EncodingMode("hex");
    rsaDecryptor.ImportPrivateKey(privateKey);

    usePrivateKey = true;
    const char * decryptedStr;
    decryptedStr = rsaDecryptor.decryptStringENC(encryptedStr,usePrivateKey);

    printf("%s\n",decryptedStr);
}


int _tmain(int argc, _TCHAR* argv[])
{
	DoNothing();
	RSA_ex();
	
	key_press();
	return 0;
}

