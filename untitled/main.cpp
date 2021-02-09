#include <iostream>
#include <fstream> // fstream header file for ifstream, ofstream,fstream classes
#include <vector>
#include <cstring>

using namespace std;

/**
 * This function text converts into sentences by delimiter and stores the sentences in a vector
 * @param str The Input Text from the file
 * @param delimiter " . "
 * @param out Vector of string
 */
void tokenize(string const &str, const char* delimiter,vector<string> &out);

/**
 * This function replace the desired substring from sentence
 * @param sentence
 * @param toSearch
 * @param replaceSubstring
 */
void Replace(string & sentence,const string& toSearch,const string& replaceSubstring);

/**
 * This functions converts the string to UPPERCASE
 * @param oString
 * @return oString
 */
string stringToUpper(string oString);

/**
 * This function iterates over the elements(sentences) of vector out. finds the word and replace it.
 * and Stores the sentences to the vector search
 * @param sentences vector<out>
 * @param word
 * @return vector found
 */
vector<string> search(vector<string> &sentences, const string& word);

int main()
{
    // Creation of ifstream class object to read the file
    ifstream fin;
    fin.open("in.txt");// by default open mode = ios::in mode
    // Creation of ofstream class object
	ofstream fileout;
    /**  by default ios::out mode, automatically deletes
    the content of file. To append the content, open in ios:app
    fileout.open("out.txt", ios::app) */
	fileout.open("out.txt");
	if(fin.fail()){
    cerr << "Input file opening failed.\n";
    exit(1);
  	}
    string temp;
    temp = "";
	getline(fin,temp); // Read a Line from standard input
	vector<string> out;
	tokenize(temp, ".", out);
	int n;
	fin>>n;  // input no of words from file
	for(int i=0 ; i<n ; i++){
    string word;
    fin>>word; // input word from the file
    vector<string> result = search(out , word); //
    fileout<<result.size()<<endl;
    	for(const auto& found : result){
    	  fileout<<found<<endl; // print output to the file
    	}
  	}
    // Close the file
	fileout.close();
	fin.close();
	return 0;
}

void tokenize(string const &str, const char* delimiter,vector<string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delimiter);
    int i=1;
    while (token != nullptr)
    {
        out.emplace_back(token);
        token = strtok(nullptr, delimiter);
        i++;
    }
}

void Replace(string & sentence,const string& toSearch,const string& replaceSubstring)
{
    // Get the first occurrence
    size_t pos = sentence.find(toSearch);
    // Repeat till end is reached
    while( pos != string::npos)
    {
        // Replace this occurrence of Sub String
        sentence.replace(pos, toSearch.size(), replaceSubstring);
        // Get the next occurrence from the current position
        pos =sentence.find(toSearch, pos + replaceSubstring.size());
    }
}

string stringToUpper(string oString)
{
	for(auto & i : oString){
       i = toupper(i);
    }
    return oString;
}

vector<string> search(vector<string> &sentences, const string& word)
{
	vector<string> found; // Assign vector
	for(string sentence : sentences)
	{
    size_t pos = sentence.find(word);    // Get the first occurrence
    	if(pos != string::npos)
		{
    	Replace(sentence , word , stringToUpper(word)); // word get replaced
      	found.push_back(sentence + ".");
    	}
  	}
  	return found;
}