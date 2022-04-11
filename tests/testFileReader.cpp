//todo
#include "../FileReader.h"
#include "../cs225/catch/catch.hpp"


TEST_CASE("Read Users Simple", "[weight=1]") {
    std::string file_path = "data/testConstructor/";
    FileReader reader = FileReader(file_path);

    set<string> users = reader.getUserListFromSubRedditFile("one");
    set<string> expected = {"a", "b"};
    REQUIRE(users == expected);
}


TEST_CASE("Read Subreddits Simple", "[weight=1]") {
    std::string file_path = "data/testConstructor/";
    FileReader reader = FileReader(file_path);

    set<string> subs = reader.getSubRedditListFromUserFile("a");
    set<string> expected = {"one", "two", "three", "four"};
    REQUIRE(subs == expected);
}




