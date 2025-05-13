#include "utils/parsers.hpp"
#include "utils/substitute_types.hpp"

using namespace pftd::utils::parser;

LevelConfigParser::LevelConfigParser(std::string const& sourceFile):
    Parser{sourceFile, "levelconfig"}
{

}

void LevelConfigParser::parse()
{
    if(!this->isLabelValid()) {
        throw ParseError{"Helytelen 'label'!"};
    }

    while(!sourceStream.eof()) {
        // Beolvassuk a következő attribútumot.
        auto lastAttrib = this->_getAttribute();

        // Fészek infót kaptunk.
        if(lastAttrib == "nestPosition") {
            m_attribs[lastAttrib] = {this->get<utils::Vec2f>()};

        // Követési útvonal infót kaptunk.
        } else if(lastAttrib == "followPath") {
            // Hiba: nem array.
            if(this->get<char>() != '[') {
                throw ParseError{"Hiba beolvasás közben: a `followPath` attribútum 'array' típusú értéket vár el!"};
            }

            // Beolvassuk amíg vagy nem érünk el egy zárójelet, vagy fájlvége, vagy ill-formed.
            m_attribs[lastAttrib] = {};
            do {
                m_attribs[lastAttrib].push_back(this->get<utils::Vec2f>());
            } while(this->peekAhead() != ']');
            // Magát a zárójelet is beolvassuk.
            this->get<char>();

        }

        // Hátha már a fájl végén vagyunk. Ekkor már a ciklusnak vége lesz.
        this->peekAhead();
    }
}

std::vector<pftd::utils::Vec2f> LevelConfigParser::getAttribute(std::string name) const
{
    // Nem nézünk hibát, elég, amit az STL internally dob.
    return m_attribs.at(name);
}

std::string LevelConfigParser::_getAttribute()
{
    // Attribútum név (+ kettőspont a végén).
    auto attribName = this->get<std::string>();
    if(sourceStream.fail() || sourceStream.bad()) {
        throw ParseError{"Hiba beolvasás közben!"};
    }

    if (attribName.empty() || attribName.back() != ':') {
        print(attribName);
        throw ParseError{"Nem sikerült beolvasni az attribútum nevét! Lehet a kettőspont lemaradt?"};
    }

    // Kettőspontot elhagyjuk.
    attribName.pop_back();

    return attribName;
}
