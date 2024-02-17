#include <fileManip.hpp>
// returns number of chars in a file
int fileLength(ifstream& infile)
{
    infile.seekg(0, infile.end);
    int length = infile.tellg();
    infile.seekg(0, infile.beg);

    return length;
}
// returns a string containing the whole file
char* getFileContents(string filename)
{
    ifstream infile;
    infile.exceptions( ifstream::badbit | ifstream::eofbit );

    try
    {
        infile.open(filename, ifstream::in);
        infile.clear();
    
        if (infile.is_open())
        {
            int length = fileLength(infile);
            char * buffer = new char[length];

            infile.read(buffer, length);
            infile.close();

            return buffer;
        }
    }
    catch (ifstream::failure e)
    {
        cout << "Error opening stream for reading" << endl;
        cerr << "Error: " << e.what() << endl;
        exit(-1);
    }
}

// returns number of lines in file
int numberOfLines(char * fileContents)
{
    stringstream instring(fileContents);
    string token;
    int length = 0;
    
    while(getline(instring, token, '\n'))
        length++;

    return length;
}

// splits file into array of string entries
void splitFileContents(string * arr, char * fileContents)
{
    stringstream instring(fileContents);
    string token;
    int length = numberOfLines(fileContents);
    int counter = 0;
    
    while(getline(instring, token, '\n'))
    {
        arr[counter] = token;
        counter++;
    }

    delete[] fileContents;
}
