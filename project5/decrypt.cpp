#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>

bool cribMatch(const char encrypted[], const char crib[], char cipher[]);
bool decrypt(const char ciphertext[], const char crib[]);
void printDecrypted(const char encrypted[], const char cipher[]);
bool testDecrypt(const char ciphertext[], const char crib[],
                 const char decrypted[], bool expected);

int main() {

  char cipher[27];

  const char spec_encrypted[] =
      "Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\nUdbyjo iqcju cg wybgj "
      "cg jds esjqiqo zqy\nXbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\nZU 31 "
      "cu zdqrrsgecge!";
  const char spec_decrypted[] =
      "LEwTo ANx MmeSo ENTER TdE vANf vo TdE vAzf xbbR.\nSdbRTo iAITS IN wRbNT "
      "IN TdE eETAiAo zAR\nxbN'T LET TdE TELLER TRIn TdE SILENT ALARM.\nzS 31 "
      "IS zdALLENeINe!";
  const char spec_crib0[] = "silent alarm";
  assert(testDecrypt(spec_encrypted, spec_crib0, spec_decrypted,
                     true)); // given by spec

  const char frog_encrypted[] =
      "A frog is any member of a diverse and largely carnivorous group of "
      "short-bodied,\ntailless amphibians composing the order Anura (literally "
      "without tail in Ancient\nGreek). The oldest fossil 'proto-frog' "
      "appeared in the early Triassic\nof Madagascar, but molecular clock "
      "dating suggests their origins\nmay extend further back to the Permian, "
      "265 million years ago.";
  const char frog_decypted[] =
      "a FrOg IS any mEmbEr OF a DIvErSE anD LargELy carnIvOrOuS grOup OF "
      "ShOrT-bODIED,\nTaILLESS amphIbIanS cOmpOSIng ThE OrDEr anura (LITEraLLy "
      "wIThOuT TaIL In ancIEnT\ngrEEk). ThE OLDEST FOSSIL 'prOTO-FrOg' "
      "appEarED In ThE EarLy TrIaSSIc\nOF maDagaScar, buT mOLEcuLar cLOck "
      "DaTIng SuggESTS ThEIr OrIgInS\nmay ExTEnD FurThEr back TO ThE pErmIan, "
      "265 mILLIOn yEarS agO.";
  const char frog_crib0[] = "oldest fossil";    // exact match of crib
  const char frog_crib1[] = "  oldest  fossil"; // extra spaces in crib
  const char frog_crib2[] =
      "    OLdEst    foSSil    "; // leading and trailing spaces in crib,
                                  // capitalized letters
  const char frog_crib3[] =
      "1oLDeSt9===0'fOssIl;"; // random characters scattered throughout crib,
                              // capitalized letters
  const char frog_cipher0[] =
      "   def  i  l  o   st      "; // the expected cipher
  assert(cribMatch(frog_crib0, frog_crib0, cipher) &&
         !strcmp(cipher, frog_cipher0)); // cribMatch should match itself
  assert(cribMatch(frog_crib0, frog_crib1, cipher) &&
         !strcmp(cipher, frog_cipher0)); // cribMatch should handle extra spaces
  assert(
      cribMatch(frog_crib0, frog_crib2, cipher) &&
      !strcmp(cipher, frog_cipher0)); // cribMatch should handle capitalizations
  assert(cribMatch(frog_crib2, frog_crib3, cipher) &&
         !strcmp(cipher, frog_cipher0)); // cribMatch should handle random
                                         // character and capitalizations
  assert(cribMatch(frog_crib3, frog_crib0, cipher) &&
         !strcmp(cipher,
                 frog_cipher0)); // cribMatch should handle random characters
  assert(testDecrypt(frog_encrypted, frog_crib0, frog_decypted,
                     true)); // decrypt should handle exact match
  assert(testDecrypt(frog_encrypted, frog_crib1, frog_decypted,
                     true)); // decrypt should handle extra spaces
  assert(testDecrypt(
      frog_encrypted, frog_crib2, frog_decypted,
      true)); // decrypt should handle extra spaces and uppercase letters
  assert(testDecrypt(frog_encrypted, frog_crib3, frog_decypted,
                     true)); // decrypt should handle multiple extra characters

  const char faq_encrypted[] = "abcd efg hijk ilm nppq rst dccb cba uwwx wyz";
  const char faq_decrypted[] = "abcd efg hijk ilm nppq rst dccb cba GOOD ONE";
  const char faq_crib0[] = "good one";
  assert(testDecrypt(faq_encrypted, faq_crib0, faq_decrypted,
                     true)); // ensure reverse cipher functions correctly

  const char email_encrypted[] =
      "If your correctness score is 60 or below, it may not be because of a "
      "lack\nignore repeated admonitions in the spec and in class to avoid "
      "specific\nfoolish mistakes, yet you made them anyway.  Whatever your "
      "field of study\nis, you should work to fix whatever coused you to do "
      "this.";
  const char email_decrypted0[] =
      "Af your correctQess score As 60 or below, At mBy Qot be becBuse of B "
      "lBck\nAgQore repeBteI BImoQAtAoQs AQ the spec BQI AQ clBss to BvoAI "
      "specAfAc\nfoolAsh mAstBkes, yet you mBIe them BQywBy.  whBtever your "
      "fAelI of stuIy\nAs, you shoulI work to fAx whBtever couseI you to Io "
      "thAs.";
  const char email_decrypted1[] =
      "if your correctness score is 60 or below, it mWy not be becWuse of W "
      "lWck\nignore repeWted Wdmonitions in the spec Wnd in clWss to Wvoid "
      "specific\nfoolish mistWkes, yet you mWde them WnywWy.  whWtever your "
      "field of study\nis, you should work to fix whWtever coused you to do "
      "this.";
  const char email_decrypted2[] = "";
  const char email_decrypted3[] =
      "IF YOUR CORRECTNESS SCORE IS 60 OR BELOW, IT MAY NOT BE BECAUSE OF A "
      "LACK\nIgNORE REpEATEd AdMONITIONS IN ThE SpEC ANd IN CLASS TO AvOId "
      "SpECIFIC\nFOOLISh MISTAKES, YET YOU MAdE ThEM ANYWAY.  WhATEvER YOUR "
      "FIELd OF STUdY\nIS, YOU ShOULd WORK TO FIx WhATEvER COUSEd YOU TO dO "
      "ThIS.";
  const char email_crib0a[] = "@bqi aq , 25, 72";
  const char email_crib1a[] = "w";
  const char email_crib1b[] = " w ";
  const char email_crib2a[] = "";
  const char email_crib2b[] = " 89012./'` ";
  const char email_crib2c[] = "aa";
  const char email_crib3a[] = "If your correctness score is 60 or below, it "
                              "may not be because of a lack";

  assert(testDecrypt(email_encrypted, email_crib0a, email_decrypted0,
                     true)); // random crib just to ensure email string works
  assert(testDecrypt(email_encrypted, email_crib1a, email_decrypted1,
                     true)); // single character crib
  assert(
      testDecrypt(email_encrypted, email_crib1b, email_decrypted1,
                  true)); // single character crib with leading/trailing spaces
  assert(testDecrypt(email_encrypted, email_crib2a, email_decrypted2,
                     false)); // empty crib returns false
  assert(testDecrypt(email_encrypted, email_crib2b, email_decrypted2,
                     false)); // crib with all non letters returns false
  assert(testDecrypt(email_encrypted, email_crib2c, email_decrypted2,
                     false)); // crib with no match returns false
  assert(testDecrypt(email_encrypted, email_crib3a, email_decrypted3,
                     true)); // very long crib (exact match) is valid

  const char too_long_encrypted[] = "abcdef zxy\ncs31 phys1ah\n\nucla\n";
  const char too_long_decrypted0[] = "";
  const char too_long_crib0a[] = "zxywvu bca yq";
  const char too_long_crib0b[] =
      "The Industrial Revolution and its consequences have been a disaster for "
      "the human race.";
  assert(testDecrypt(too_long_encrypted, too_long_crib0a, too_long_decrypted0,
                     false)); // crib can't match across lines
  assert(testDecrypt(too_long_encrypted, too_long_crib0b, too_long_decrypted0,
                     false)); // crib can't match if over 90 characters
  return 0;
}

// check if an encrypted message matches the reptetion scheme of a crib
bool cribMatch(const char encrypted[], const char crib[], char *cipher) {
  int ei = 0;
  int ci = 0;
  // initialize cipher and reverse cipher to strings of 26 spaces
  char reverse_cipher[27];
  memset(cipher, ' ', 26);
  memset(reverse_cipher, ' ', 26);
  cipher[26] = '\0';
  reverse_cipher[26] = '\0';
  while (encrypted[ei] != '\0' && crib[ci] != '\0') {
    // ignore all non-letters in the encrypted message and the crib
    if (!isalpha(encrypted[ei])) {
      ei++;
      continue;
    }
    if (!isalpha(crib[ci])) {
      ci++;
      continue;
    }
    // both characters are letters
    if (isalpha(encrypted[ei]) && isalpha(crib[ci])) {
      // get the index corresponding to the given letter (a:0, b:2 ... z:25)
      int cipher_key = tolower(encrypted[ei]) - 'a';
      int reverse_cipher_key = tolower(crib[ci]) - 'a';
      // if the cipher has already stored the current encrypted letter (the
      // value at the key index is not a space) and if the value at the key
      // index is not the correctly mapped letter (also check the reverse of
      // this) then the cipher doesnt match the reptition scheme and return
      // false
      if ((cipher[cipher_key] != ' ' &&
           cipher[cipher_key] != tolower(crib[ci])) ||
          (reverse_cipher[reverse_cipher_key] != ' ' &&

           reverse_cipher[reverse_cipher_key] != tolower(encrypted[ei]))) {
        cipher[0] = '\0';
        return false;
      } else {
        // map the the encrypted message character to its decrypted crib
        // character
        cipher[cipher_key] = tolower(crib[ci]);
        // map the the decrypted crab character to its encrypted message
        // character
        reverse_cipher[reverse_cipher_key] = tolower(encrypted[ei]);
      }
    }
    ei++;
    ci++;
  }
  return true;
}

bool decrypt(const char ciphertext[], const char crib[]) {
  char cipher[27];
  int words[90];
  int word_count = 0;
  int word_length = 0;
  int cur_word = 0;
  int crib_start = 0;

  // loop over crib
  for (int i = 0; crib[i] != '\0'; i++) {
    // if not at a letter, then the current word length must be 0
    if (!isalpha(crib[i])) {
      word_length = 0;
      continue;
    }
    // if at a letter
    if (isalpha(crib[i])) {
      // increase word length by 1
      word_length++;
      // if the next character is not a letter, we are at the end of the word
      if (!isalpha(crib[i + 1])) {
        // add the word length to the array
        words[word_count] = word_length;
        // incease word count by 1
        word_count++;
      }
    }
  }
  if (word_count == 0) {
    return false;
  }
  words[word_count] = -1;
  word_length = 0;
  // loop over cipher text
  for (int i = 0; ciphertext[i] != '\0'; i++) {
    // if current character is not a letter
    if (!isalpha(ciphertext[i])) {
      // if havent found any words yet, the matched crib might start at the
      // current index so set crib_start to the current index
      if (cur_word == 0) {
        crib_start = i;
      }
      // havent encountered any letters yet so the word length must be 0
      word_length = 0;
      continue;
    }
    // if the current character ia a letter
    if (isalpha(ciphertext[i])) {
      word_length++;
      // if the next character is not a letter
      if (!isalpha(ciphertext[i + 1])) {
        // if the current word is the wrong length or we encounter a line break
        // before the final word the current string must not be a crib
        if (words[cur_word] != word_length ||
            (ciphertext[i + 1] == '\n' && cur_word + 1 != word_count)) {
          cur_word = 0;
        } else {

          // otherwise the current word is valid in the crib
          cur_word++;
        }

        // if all words have been found
        if (cur_word == word_count) {
          // check if it actually is a crib using cribMatch
          if (cribMatch(&ciphertext[crib_start], crib, cipher)) {
            // print and return true if crib is found
            printDecrypted(ciphertext, cipher);
            return true;
          }
        }
      }
    }
  }
  // no crib found, return false
  return false;
}

// decrypt a message using cipher and print it out
void printDecrypted(const char encrypted[], const char cipher[]) {
  for (int i = 0; encrypted[i] != '\0'; i++) {
    // decrypt the current character using cipher
    char decrypted;
    if (isalpha(encrypted[i])) {
      decrypted = cipher[tolower(encrypted[i]) - 'a'];
    } else {
      decrypted = ' ';
    }
    // check if the decryption exists in the cipher
    // if so, print the decrypted character in uppercase
    // else, print the original character in lowercase
    if (isalpha(encrypted[i]) && decrypted != ' ') {
      std::cout << (char)toupper(decrypted);
    } else {
      std::cout << (char)tolower(encrypted[i]);
    }
  }
}

// code for testDecrypt borrowed from
// https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
bool testDecrypt(const char ciphertext[], const char crib[],
                 const char decypted[], bool expected) {
  bool success = false;
  std::ostringstream oss;
  // temporarily stores original streambuf of cout
  std::streambuf *tmp_cout_streambuf = std::cout.rdbuf();
  // redirects cout to stringstream we can read from
  std::cout.rdbuf(oss.rdbuf());

  // runs decrypt (everything printed here is captured in oss)
  success = decrypt(ciphertext, crib);

  // replaces original streambuf of cout
  std::cout.rdbuf(tmp_cout_streambuf);

  // ensures the text printed by output is equal to the decrypted string
  // parameter
  return oss && (oss.str() == decypted) && (success == expected);
}
