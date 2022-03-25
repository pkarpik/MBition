//
// Created by PK on 23.03.2022.
//

#include <unordered_map>
#include <string>

#ifndef MBITION_PARSER_H
#define MBITION_PARSER_H

class Parser{
private:
    std::unordered_map<std::string, int> cityDict;
    std::string filePath;

    Parser( Parser&& ) = delete;
    Parser( Parser& ) = delete;

    void normalizeText( std::string& );
    void removeSpaces( std::string& );
    std::string gpt3Response( const std::string& );
    int isCity( std::string );
    void pythonPacks();
public:
    Parser& operator=( Parser&& ) = delete;
    Parser& operator=( Parser& ) = delete;
    Parser();
    ~Parser() = default;

    void loadCityDict( std::string );
    std::string parseInquiry( std::string );

};

#endif //MBITION_PARSER_H
