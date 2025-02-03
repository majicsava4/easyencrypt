#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cryptopp/aes.h>
#include <string>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <algorithm>
#include <cryptopp/osrng.h>



static void printUsage(const char* easyencrypt) {
    std::cout << "Usage: " << easyencrypt << " <encrypt|decrypt> <inputfile> <key>\n";
    std::cout << "  <encrypt|decrypt> : Specify whether to encrypt or decrypt the file\n";
    std::cout << "  <inputfile>       : The file to be encrypted/decrypted\n";
    std::cout << "  <key>             : A 16-byte key for AES-128 encryption\n";
    std::cout << "Example:\n";
    std::cout << "  " << easyencrypt << " encrypt myfile.txt 0123456789abcdef\n";
}




static bool strEqual(const char *s1, const char *s2){

  if(strlen(s1) != strlen(s2)){
    return false;
  }
  int len = strlen(s1);
  for(int i = 0; i < len; i++){
    if(s1[i] != s2[i]){
      return false;
    }
  }
  return true;
}


static void checkError(int argc, char *argv[]){
  if(argc != 4){
    std::cerr << "Usage: " << argv[0] << " <encrypt/decrypt> <inputfile> <key>\n";
    exit(1);
  }
  else if(!strEqual(argv[1], (char*)"encrypt") && !strEqual(argv[1], (char*)"decrypt")){
    std::cerr << "First argument can only be encrypt or decrypt\n";
    exit(1);
  }else if(strlen(argv[3]) != 16){
    std::cerr << "Key must be 16 bytes.\n";
    exit(1);
  }
  
}


static std::string AESEncrypt(const std::string &fileContent, const std::string &keyString){

    std::string encryptedString;
    
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);

    std::memcpy(key, keyString.data(), std::min(keyString.size(), key.size()));

    //Generating random IV
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());
        
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    encryption.SetKeyWithIV(key, key.size(), iv, iv.size());
    

    CryptoPP::StringSource ss(fileContent, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(encryptedString)));


    //Prepending the IV to the encyptedString
    std::string ivStr(reinterpret_cast<const char*>(&iv[0]), iv.size());
    
    return ivStr + encryptedString;
}


static std::string AESDecrypt(const std::string &fileContent, const std::string &keyString){

  //Ensuring the file content is long enough to contain the IV
  if(fileContent.size() < CryptoPP::AES::BLOCKSIZE){
    std::cerr << "Too short, missing IV\n";
    exit(1);
  }

  //Extracting the IV from the beginning
  CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
  std::memcpy(iv, fileContent.data(), CryptoPP::AES::BLOCKSIZE);

  std::string actualText = fileContent.substr(CryptoPP::AES::BLOCKSIZE);

  std::string decryptedString;
  CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
  std::memcpy(key, keyString.data(), std::min(keyString.size(), key.size()));

  CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
  decryption.SetKeyWithIV(key, key.size(), iv, iv.size());

  CryptoPP::StringSource ss(actualText, true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(decryptedString)));

  
  return decryptedString;
}


int main(int argc, char *argv[]){


  if(argc >= 2 && (strEqual(argv[1], "-h") || (strEqual(argv[1], "--help")))){

    printUsage(argv[0]);
    return 0;
    
  }
  
  checkError(argc, argv);
  
  std::string mode = argv[1];
  std::string inputFileName = argv[2];
  std::string keyString = argv[3]; //minimum 16 bytes for AES-128

   
  std::ifstream inFile(inputFileName, std::ios::binary);
  if(!inFile){
    std::cerr << "Error: Unable to open file: " << inputFileName << "\n";
    exit(1);
  }
  
  std::string fileContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
  inFile.close();
  
    
  if(strEqual(mode.c_str(), (char*)"encrypt")){
      std::string encrypted = AESEncrypt(fileContent, keyString);
      std::ofstream outFile("encrypted.bin", std::ios::binary);

      if(!outFile){
        std::cerr << "Error: Unable to create an output file.\n";
        exit(1);
      }
      
      outFile.write(encrypted.data(), encrypted.size());
      outFile.close();

      std::cout << "Encrypted data has been written into encrypted.bin, don't forget your key!\n";
  }


  if(strEqual(mode.c_str(), (char*)"decrypt")){
      std::string decrypted = AESDecrypt(fileContent, keyString);
      std::ofstream outFile("decrypted.txt");
      if(!outFile){
        std::cerr << "Error: Unable to create an output file.\n";
        exit(1);
      }

      outFile.write(decrypted.c_str(), decrypted.size());
      outFile.close();

      std::cout << "Decrypted text has been written to decrypted.txt\n";
  }

  return 0;
}
