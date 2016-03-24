#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "ticcutils/StringOps.h"

using namespace std;

int main(){
  set<string> auc_words;
  map<string,string> frog_words;

  ifstream auc( "auco.txt" );
  string line;
  while ( getline( auc, line ) ){
    string word = TiCC::trim( line );
    auc_words.insert( word );
  }
  cout << "read " << auc_words.size() << " known compounds " << endl;
  ifstream frog( "comp.tsv" );
  while ( getline( frog, line ) ){
    vector<string> words;
    int num = TiCC::split( line, words );
    if ( num != 2 ){
      cerr << "problem with line: " << line << endl;
    }
    else {
      frog_words.insert( make_pair( words[0], words[1] ) );
    }
  }
  cerr << "read " << frog_words.size() << " assumed frog compounds " << endl;
  ofstream valid( "found_compounds" );
  ofstream invalid( "not_found_compounds" );
  for ( auto const& w : frog_words ){
    if ( auc_words.find( w.first ) != auc_words.end() ){
      valid << w.first << endl;
    }
    else {
      invalid << w.first << "\t" << w.second << endl;
    }
  }
  ofstream notyet( "not_yet_found_compounds" );
  for ( auto const& w : auc_words ){
    if ( frog_words.find( w ) == frog_words.end() ){
      notyet << w << endl;
    }
  }
}
