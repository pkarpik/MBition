//
// Created by PK on 24.03.2022.
//

#include "gtest/gtest.h"
#include "../parser.h"
#include <filesystem>
#include <vector>

using namespace std;

Parser par;

TEST( ParserTest, LoadDictFile ) {

    string filePath = std::filesystem::current_path();

    auto it = filePath.find_last_of( '/' );

    if ( it != string::npos )
    {
        filePath.erase( it + 1 );
    }

    filePath += "citydict.txt";

    EXPECT_NO_THROW( par.loadCityDict( filePath ) );

}

TEST( ParserTest, LoadDictFileExcept ) {

    string filePath = "random-path-that-barely-exists";

    EXPECT_ANY_THROW( par.loadCityDict( filePath ) );

}

TEST( ParserTest, TestInputVariations ) {

    vector<string> req = {

            "What is the weather like today?",
            "WhAt is THE wEather like todAy?",
            "  What     is  the weather   like  today ?",
            "  WhAt    is  THE wEather   like todAy?",

    };

    for( auto inquiry : req ) {

        auto response = par.parseInquiry(inquiry);

        EXPECT_EQ( response, "Get Weather" );

    }

}

TEST( ParserTest, TestCases ) {
    
    vector<string> req = {

            "What is the weather like today?",
            "What is the weather like in Paris today?",
            "Tell me an interesting fact.",
            "Want to listen to a story.",
            "I would like to know this information.",
            "Tell me about the weather.",
            "The weather is bad.",
            "I heard a story."

    };

    vector<string> resp = {

            "Get Weather",
            "Get Weather City",
            "Get Fact",
            "Get Story",
            "Get Information",
            "Get Weather",
            "-",
            "-"

    };

    for( int k = 0; k < req.size(); k++ ) {

        auto response = par.parseInquiry( req[k] );

        EXPECT_EQ( response, resp[k] );

    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}