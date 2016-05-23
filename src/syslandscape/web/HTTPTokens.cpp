#include "HTTPTokens.h"

namespace syslandscape {
namespace web {

HTTPTokens::HTTPTokens()
{
  setupStateList();
}

HTTPTokens::State HTTPTokens::getState(int c)
{
  return getInstance()._stateList[c];
}
  
bool HTTPTokens::isLegal(int c)
{
  return State::LEGAL == getState(c);
}

bool HTTPTokens::isDigit(int c)
{
  return isLegal(c) && (c >= 0x30 && c<= 0x39);
}

void HTTPTokens::setupStateList()
{
    _stateList.fill(State::ILLEGAL);
    for (int i = 0x2A; i < 0x5B; i++) _stateList[i] = State::LEGAL;
    for (int i = 0x5D; i < 0x7E; i++) _stateList[i] = State::LEGAL;
    for (int i = 0x80; i < 0xFF; i++) _stateList[i] = State::LEGAL;
    
    _stateList[LF] = State::LF;
    _stateList[CR] = State::CR;
    _stateList[TAB] = State::LEGAL;
    _stateList[SPACE] = State::LEGAL;
    _stateList['!'] = State::LEGAL;
    _stateList['#'] = State::LEGAL;
    _stateList['$'] = State::LEGAL;
    _stateList['%'] = State::LEGAL;
    _stateList['&'] = State::LEGAL;
    _stateList['\''] = State::LEGAL;
    _stateList['*'] = State::LEGAL;
    _stateList['+'] = State::LEGAL;
    _stateList['-'] = State::LEGAL;
    _stateList['.'] = State::LEGAL;
    _stateList['^'] = State::LEGAL;
    _stateList['_'] = State::LEGAL;
    _stateList['`'] = State::LEGAL;
    _stateList['|'] = State::LEGAL;
    _stateList['~'] = State::LEGAL;
    _stateList['"'] = State::LEGAL;
    _stateList['\\'] = State::LEGAL;
    _stateList['('] = State::LEGAL;
    _stateList[')'] = State::LEGAL;
}

} /* namespace web */
} /* namespace syslandscape */
