#include <cstring>
#include <fstream>
#include <iostream>
#include <cryptopp/aes.h>
#include <string>



static bool strEqual(const char *s1,const char *s2){

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


static void checkErorr(int argc, char *argv[]){
  if(argc != 5){
    std::cerr << "Usage: " << argv[0] << " <encrypt/decrypt> <inputfile> <destination file> <key>\n";
  }
  else if(!strEqual(argv[1], (char*)"encrypt") && !strEqual(argv[1], (char*)"decrypt")){
    std::cerr << "First argument can only be encrypt or decrypt\n";
  }else if(strlen(argv[1]) != 16){
    std::cerr << "Key must be minimum 16 bytes.\n";
  }
  
}


static std::string AESEncrypt(const std::string fileContent, const std::string keyString){

    std::string encryptedString;
    std::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {};

    std::memcpy(key, keyString.data(), keyString.size());

    std::byte iv[CryptoPP::AES::BLOCKSIZE] = {};
    std::memset(iv, 0, CryptoPP::AES::BLOCKSIZE);
    
    CBC_MODE
    
    
    return encryptedString;
}

int main(int argc, char *argv[]){

  checkErorr(argc, argv);
  
  std::string mode = argv[1];
  std::string inputFileName = argv[2];
  std::string outputFileName = argv[3];
  std::string keyString = argv[4]; //minimum 16 bytes for AES-128

   
  std::ifstream inFile(inputFileName);
  if(!inFile){
    std::cerr << "Error: Unable to open file: " << inputFileName << "\n";
  }
  
  std::string fileContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

  


  return 0;
}
