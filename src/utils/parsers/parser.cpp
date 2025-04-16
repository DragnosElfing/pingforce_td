#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

template<typename ST>
Parser<ST>::Parser(ST const& sourceStream, std::string label):
    sourceStream{sourceStream},
    validLabel{label}
{

}

template<>
Parser<>::Parser(std::string const& sourceFile, std::string label):
    sourceStream{std::ifstream{sourceFile}},
    validLabel{label}
{

}

template<>
Parser<>::~Parser()
{
    if(sourceStream.is_open()) {
        sourceStream.close();
    }
}

template<>
void Parser<>::reset()
{
    sourceStream.clear();
    sourceStream.seekg(0);
}

template<>
void Parser<>::skip(size_t howMany, char until)
{
    sourceStream.ignore(howMany, until);
}

template<>
void Parser<>::skip(char while_)
{
    while(sourceStream.peek() == while_) {
        sourceStream.ignore(1, while_);
    }
}


template<>
void Parser<>::_skipLine()
{
    this->skip(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<>
void Parser<>::_skipWhitespace()
{
    while(sourceStream.peek() == '\n' || sourceStream.peek() == ' ' || sourceStream.peek() == '\t') {
        sourceStream.ignore(1);
    }
}

template<>
bool Parser<>::isLabelValid(bool skip)
{
    std::string gotLabel;
    sourceStream >> gotLabel;
    if(gotLabel == validLabel) {
        if(!skip) {
            this->reset();
        }
        return true;
    }

    return false;
}

template<>
char Parser<>::peekAhead()
{
    this->_skipWhitespace();
    while(sourceStream.peek() == commentDenoter) {
        this->_skipLine();
        this->_skipWhitespace();
    }

    return sourceStream.peek();
}