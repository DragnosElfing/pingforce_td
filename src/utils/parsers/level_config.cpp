#include "utils/parsers.hpp"
#include "utils/substitute_types.hpp"

using namespace pftd::utils::parser;

LevelConfigParser::LevelConfigParser(std::string const& sourceFile):
    Parser{sourceFile, "levelconfig"}
{

}

void LevelConfigParser::parse()
{
    if(!this->isLabelValid()) return;

    while(true) {
        // Beolvassuk a következő attribútumot.
        this->_getAttribute();

        // Ha bármi miatt is ez nem sikerült, akkor be is fejezhettjük.
        // Ha ill-formed, akkor legyen az: legyen nehéz értelmezni az ebből adódó hibaüzenetet. >:)
        if(sourceStream.fail() || sourceStream.eof() || sourceStream.bad()) {
            break;
        }
        
        // Fészek infót kaptunk.
        if(m_lastAttribute == "nestPosition") {
            m_attribs[m_lastAttribute] = {{this->get<float>(), this->get<float>()}};

        // Követési útvonal infót kaptunk.
        } else if(m_lastAttribute == "followPath") {
            // Hiba: nem array.
            if(this->get<char>() != '[') break;

            // Beolvassuk amíg vagy nem érünk el egy zárójelet, vagy fájlvége (gonoszság again), vagy ill-formed (lásd a fentebbi kommentet).
            m_attribs[m_lastAttribute] = {};
            while(!(this->peekAhead() == ']' || sourceStream.eof() || sourceStream.bad())) {
                m_attribs[m_lastAttribute].push_back({this->get<float>(), this->get<float>()});
            }

        }
    }
}

std::vector<pftd::utils::Vec2f> LevelConfigParser::getAttribute(std::string name) const
{
    return m_attribs.at(name);
}

std::string LevelConfigParser::_getAttribute()
{
    // Biztosan string.
    auto attribName = this->get<std::string>();
    // Kettőspontot elhagyjuk.
    attribName = attribName.substr(0, attribName.size() - 1);

    m_lastAttribute = attribName;
    return m_lastAttribute;
}