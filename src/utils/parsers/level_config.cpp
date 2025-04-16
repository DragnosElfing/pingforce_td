#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

LevelConfigParser::LevelConfigParser(std::string const& sourceFile):
    Parser<>{sourceFile, "levelconfig"}
{

}

void LevelConfigParser::parse()
{
    if(!this->isLabelValid()) return;

    while(true) {
        this->_getAttribute();  
        if(sourceStream.fail() || sourceStream.eof() || sourceStream.bad()) {
            break;
        }
        
        if(m_lastAttribute == "nestPosition") {
            m_attribs[m_lastAttribute] = {{this->get<float>(), this->get<float>()}};
        } else if(m_lastAttribute == "followPath") {
            if(this->get<char>() != '[') break;
            m_attribs[m_lastAttribute] = {};
            while(!(this->peekAhead() == ']' || sourceStream.eof() || sourceStream.bad())) {
                m_attribs[m_lastAttribute].push_back({this->get<float>(), this->get<float>()});
            }

        }
    }
}

std::vector<std::pair<float, float>> LevelConfigParser::getAttribute(std::string name) const
{
    return m_attribs.at(name);
}

std::string LevelConfigParser::_getAttribute()
{
    auto attribName = this->get<std::string>();
    // Kettőspontot elhagyjuk
    attribName = attribName.substr(0, attribName.size() - 1);

    m_lastAttribute = attribName;
    return m_lastAttribute;
}