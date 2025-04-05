#pragma once

#include "utils/logger.hpp"
#include <istream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace pftd 
{
namespace utils 
{
namespace parser 
{

template<typename StreamType = std::ifstream>
class Parser
{
public:
    Parser(StreamType const& sourceStream, std::string label = "");
    Parser(std::string const& sourceFile, std::string label = "");
    virtual ~Parser();

    void reset();
    bool isLabelValid(bool skip = true);
    void skip(size_t howMany, char until = '\n');
    void skip(char while_);
    template<typename T> T get()
    {
        this->_skipWhitespace();
        while(sourceStream.peek() == commentDenoter) {
            this->_skipLine();
            this->_skipWhitespace();
        }

        T got;
        sourceStream >> got;
        return got;
    }
    char peekAhead();
    virtual void parse() = 0;

protected:
    StreamType sourceStream;
    std::string validLabel;
    char commentDenoter = '#';

    //virtual bool validate() const = 0;

private:
    void _skipLine();
    void _skipWhitespace();

};

class LevelConfigParser final : public Parser<>
{
public:
    LevelConfigParser(std::string const& sourceFile);
    ~LevelConfigParser() = default;

    void parse() override;
    std::vector<std::pair<float, float>> getAttribute(std::string name) const;

private:
    std::string m_lastAttribute;
    std::unordered_map<std::string, std::vector<std::pair<float, float>>> m_attribs;

    std::string _getAttribute();

};

class SaveFileParser final : public Parser<>
{
public:
    SaveFileParser(std::string const& sourceFile);
    ~SaveFileParser() = default;

    void parse() override;

};

}
}
}