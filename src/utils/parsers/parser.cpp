#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

Parser::Parser(std::string const& sourceFile, std::string label):
    sourceStream{std::ifstream{sourceFile}},
    validLabel{label}
{
    if(sourceStream.fail()) {
        throw ParseError{"Nem lehetett megnyitni a fájlt: " + sourceFile};
    }
}

Parser::~Parser()
{
    if(sourceStream.is_open()) {
        sourceStream.close();
    }
}

void Parser::reset()
{
    sourceStream.clear();
    sourceStream.seekg(0);
}

void Parser::skip(size_t howMany, char until)
{
    sourceStream.ignore(howMany, until);
}

void Parser::skip(char while_)
{
    while(sourceStream.peek() == while_) {
        sourceStream.ignore(1, while_);
    }
}


void Parser::_skipLine()
{
    this->skip(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Parser::_skipWhitespace()
{
    while(sourceStream.peek() == '\n' || sourceStream.peek() == ' ' || sourceStream.peek() == '\t') {
        sourceStream.ignore(1);
    }
}

bool Parser::isLabelValid(bool skip)
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

char Parser::peekAhead()
{
    // Minden fölös karaktert skippelünk addig.
    this->_skipWhitespace();
    while(sourceStream.peek() == commentDenoter) {
        this->_skipLine();
        this->_skipWhitespace();
    }

    return sourceStream.peek();
}
