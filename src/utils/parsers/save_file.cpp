#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

SaveFileParser::SaveFileParser(std::string const& sourceFile):
    Parser{sourceFile, "pingforce"}
{

}

void SaveFileParser::parse()
{
    if(!this->isLabelValid()) return;

    while(true) {
        break;
    }
}