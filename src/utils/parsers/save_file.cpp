#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

SaveFileParser::SaveFileParser(std::string const& sourceFile):
    Parser<>{sourceFile, "pingforce"}
{

}

void SaveFileParser::parse()
{
    if(!this->isLabelValid()) return;

    m_readStats.score = this->get<unsigned int>();
    m_readStats.wealth = this->get<unsigned int>();
    m_readStats.hp = this->get<unsigned int>();

    while(true) {
        break;
    }
}