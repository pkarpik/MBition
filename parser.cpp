//
// Created by PK on 23.03.2022.
//
#include "parser.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <filesystem>

using namespace std;

Parser::Parser() {

    // get current file path
    filePath = std::filesystem::current_path();

    auto it = filePath.find_last_of( '/' );

    if ( it != string::npos )
    {
        filePath.erase( it + 1 );
    }


    // environment set up
    pythonPacks();

}

void Parser::loadCityDict( string file ){

    ifstream dictFile( file );

    if ( dictFile.is_open() )
    {
        string tmp;

        int i = 0;

        while( !dictFile.eof() )
        {

            dictFile >> tmp;

            cityDict[tmp] = i;

            i++;

        }

        dictFile.close();
    }

    else {

        cout << "Unable to open file\n";

        throw -1;

    }

}

void Parser::normalizeText( string & str ){

    transform( str.begin(), str.end(), str.begin(),
               []( char ch ){ return tolower( ch ); } );

    removeSpaces( str );

}

void Parser::removeSpaces( string& str )
{
    int n = str.size();

    int i = 0, j = -1;

    bool spaceFound = false;

    while( ++j < n && str[j] == ' ' );

    while ( j < n )
    {

        if ( str[j] != ' ' )
        {

            if( ( str[j] == '.' || str[j] == ',' || str[j] == '?' )
                && i - 1 >= 0 &&
                str[i - 1] == ' ' )
                    str[i - 1] = str[j++];

            else    str[i++] = str[j++];

            spaceFound = false;
        }

        else if( str[j++] == ' ' )
        {

            if ( !spaceFound )
            {
                str[i++] = ' ';

                spaceFound = true;
            }
        }
    }

    if ( i <= 1)    str.erase( str.begin() + i, str.end() );

    else{

        if( str[i-1] != ' ' ) str.erase( str.begin() + i, str.end() );

        else str.erase( str.begin() + i - 1, str.end() );

    }

}

int Parser::isCity( string str ){

    string toErase = ",.?!";

    for( auto ch : toErase ) {

        str.erase(
                remove(str.begin(), str.end(), ch ),
                str.end()
        );

    }

    stringstream sbuf;

    sbuf << str;

    string word;

    while( sbuf >> word ){

        if( cityDict.find(word) != cityDict.end() ) return cityDict[word];

    }

    return -1;

}

string Parser::parseInquiry( string inq ){

    normalizeText( inq );

    auto response = gpt3Response( inq );

    if( response.size() == 0 ) throw -1;

    if( response.find( "Weather" ) != string::npos ) {

        // int code is used for future application
        // - to search for a city somewhere in database
        // in current version there is no need for it,
        // but it may be used as application extends
        auto code = isCity(inq);
        if ( code != -1 ) response += " City";

    }

    return response;

}

void Parser::pythonPacks(){

    // set virtual environment for python
    string setVirtEnv = "python3 -m venv " + filePath + "venv";

    system( setVirtEnv.c_str() );

    // get openai
    string getOpenAI = filePath + "venv/bin/pip install openai";
    system( getOpenAI.c_str() );

}

string Parser::gpt3Response( const string& inq ){

    // run script
    string cmd = filePath + "venv/bin/python " + filePath + "gtp3.py ";
    cmd += "'" + inq + "'";

    system( cmd.c_str() );

    ifstream responseFile( "GPT3Response.txt" );

    string response;

    if ( responseFile.is_open() )
    {

        getline( responseFile, response);

        responseFile.close();
    }

    else {

        cout << "Unable to open response file\n";

        throw -1;

    }

    return response;

}