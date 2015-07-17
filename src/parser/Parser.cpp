/**
 * Parsing is done top-down, according to regex grammar:
 *
 * <regex>  ::= <term> '|' <regex>
 *           |  <term>
 *
 * <term>   ::= <factor> <term>
 *           |  <factor>
 *
 * <factor> ::= <atom> <multi>
 *           |  <atom>
 *
 * <atom>   ::= char
 *           |  '(' <regex> ')'
 * 
 * <multi>  ::= '*'
 *           |  '+'
 *           |  '?'
 *           |  '{' uint '}'
 *           |  '{' uint ',' uint '}'
 *           |  '{' uint ',' 'INF' '}'
 */

#include <vector>

#include "../common.h"
#include "Parser.h"
#include "ast/Multi.h"
#include "ast/RegexChar.h"
#include "ast/RegexChoice.h"
#include "ast/RegexSequence.h"
#include "../throwable/error/NotImplementedError.h"
#include "../throwable/runtime/IllegalArgumentException.h"

using namespace std;
using namespace regexsf;

Parser::Parser() {
}

Parser::~Parser() {
}

pair<unsigned int, unsigned int> Parser::parseUInt(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseUInt: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    unsigned int z = 0;
    unsigned int k = 0;

    // TODO what if not ASCII
    for (k = pos; ((k < s.length()) && ('0' <= s[k]) && (s[k] <= '9')); ++k) {
        z = 10*z + (s[k] - '0');
    }

    if (k == pos) {
        RX_THROW_STREAM(IllegalArgumentException, "Expected 0-9 at position: " << pos << " but got: " << s[pos]);
    }

    RX_DEBUG("parseUInt: " << z);
    return pair<unsigned int, unsigned int>(z, k);
}

pair<Multi*, unsigned int> Parser::parseMulti(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseMulti: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    pair<Multi*, unsigned int> m(nullptr, 1+pos);

    if ('*' == s[pos]) {
        RX_NEW_ARGS(m.first, Multi, MultiType::ZeroOrMore);
    } else if ('+' == s[pos]) {
        RX_NEW_ARGS(m.first, Multi, MultiType::OneOrMore);
    } else if ('?' == s[pos]) {
        RX_NEW_ARGS(m.first, Multi, MultiType::ZeroOrOne);
    } else if ('{' == s[pos]) {
        pair<unsigned int, unsigned int> u = parseUInt(s, 1+pos);

        if (u.second < s.length()) {
            if (',' == s[u.second]) {
                RX_DEBUG("compare przecinek");
                if (0 == s.compare(u.second, 5, ",INF}")) {
                    m.second = 5 + u.second;
                    RX_NEW_ARGS(m.first, Multi, MultiType::AtLeast, u.first);
                } else {
                    pair<unsigned int, unsigned int> u2 = parseUInt(s, 1 + u.second);

                    if (u2.second < s.length()) {
                        if ('}' != s[u2.second])
                            RX_THROW_STREAM(IllegalArgumentException, "Expected } at position: " << (u2.second) << " but got: " << s[u2.second]);
                        m.second = 1 + u2.second;
                        RX_NEW_ARGS(m.first, Multi, MultiType::Range, u.first, u2.first);
                    } else {
                        RX_THROW_STREAM(IllegalArgumentException, "Unexpected end of input regex string!");
                    }
                }
            } else if ('}' == s[u.second]) {
                m.second = 1+u.second;
                RX_NEW_ARGS(m.first, Multi, MultiType::Exact, u.first);
            } else {
                RX_THROW_STREAM(IllegalArgumentException, "Expected }, at position: " << (u.second) << " but got: " << s[u.second]);
            }
        } else {
            RX_THROW_STREAM(IllegalArgumentException, "Unexpected end of input regex string!");
        }
    } else {
        RX_THROW_STREAM(IllegalArgumentException, "Expected *+?{ at position: " << pos << " but got: " << s[pos]);
    }

    RX_DEBUG("parseMulti: " << (m.first) << " " << (*m.first));
    return m;
}

pair<AbstractRegex*, unsigned int> Parser::parseAtom(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseAtom: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    pair<AbstractRegex*, unsigned int> m;

    // TODO what if not ASCII
    if ((('a' <= s[pos]) && (s[pos] <= 'z')) || (('A' <= s[pos]) && (s[pos] <= 'Z'))) {
        RX_NEW_ARGS(m.first, RegexChar, s[pos]);
        m.second = 1+pos;
    } else if ('(' == s[pos]) {
        m = parseRegex(s, 1+pos);

        if ((m.second < s.length()) && (')' == s[m.second])) {
            m.second++;
        } else {
            RX_THROW_STREAM(IllegalArgumentException, "Expected ')' at position: " << pos << " but got: " << s[pos]);
        }
    } else {
        RX_THROW_STREAM(IllegalArgumentException, "Expected '(', ')', 'a'-'z' or 'A'-'Z' at position: " << pos << " but got: " << s[pos]);
    }

    RX_DEBUG("parseAtom: " << (*m.first));
    return m;
}

pair<AbstractRegex*, unsigned int> Parser::parseFactor(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseFactor: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    pair<AbstractRegex*, unsigned int> a = parseAtom(s, pos);

    if ((a.second < s.length()) &&
            (('*' == s[a.second]) ||
             ('+' == s[a.second]) ||
             ('?' == s[a.second]) ||
             ('{' == s[a.second]))) {
        pair<Multi*, unsigned int> m = parseMulti(s, a.second);
        // RX_DEBUG("pushMulti (1): " << a.first << " " << m.first << " " << m.second);
        a.first->pushMulti(m.first);
        // RX_DEBUG("pushMulti (2): " << a.first << " " << m.first << " " << m.second);
        a.second = m.second;
    }

    // RX_DEBUG("parseFactor: " << a.first);
    RX_DEBUG("parseFactor: " << (*a.first));
    return a;
}

pair<AbstractRegex*, unsigned int> Parser::parseTerm(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseTerm: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    vector<AbstractRegex*> sr;
    pair<AbstractRegex*, unsigned int> m;
    m.second = pos;

    do {
        m = parseFactor(s, m.second);
        sr.push_back(m.first);
    } while ((m.second < s.length()) && 
                ( ('(' == s[m.second]) || 
                 (('a' <= s[m.second]) && (s[m.second] <= 'z')) ||
                 (('A' <= s[m.second]) && (s[m.second] <= 'Z'))));

    if (1 == sr.size()) {
        m.first = sr.at(0);
    } else {
        RX_NEW_ARGS(m.first, RegexSequence, sr);
    }

    RX_DEBUG("parseTerm: " << (*m.first));
    return m;
}

pair<AbstractRegex*, unsigned int> Parser::parseRegex(const TString& s, const unsigned int pos) const {
    RX_DEBUG("parseRegex: pos=" << pos);

    if (s.length() <= pos)
        RX_THROW_STREAM(IllegalArgumentException, "pos=" << pos << " but s.length()=" << s.length());

    vector<AbstractRegex*> sr;
    pair<AbstractRegex*, unsigned int> m;
    m.second = pos - 1;

    do {
        m = parseTerm(s, 1 + m.second);
        sr.push_back(m.first);
    } while ((m.second < s.length()) && ('|' == s[m.second]));

    if (1 == sr.size()) {
        m.first = sr.at(0);
    } else {
        RX_NEW_ARGS(m.first, RegexChoice, sr);
    }

    RX_DEBUG("parseRegex: " << (*m.first));
    return m;
}

AbstractRegex* Parser::parse(const TString& s) const {
    if (s.empty())
        RX_THROW_ARGS(IllegalArgumentException, "Input regex string is empty!");

    // check for allowed characters
    for (unsigned int i=0; i < s.length(); ++i) {
        if (! ((('0' <= s[i]) && (s[i] <= '9')) ||
               (('a' <= s[i]) && (s[i] <= 'z')) ||
               (('A' <= s[i]) && (s[i] <= 'Z')) ||
                ('(' == s[i]) ||
                (')' == s[i]) ||
                ('{' == s[i]) ||
                ('}' == s[i]) ||
                ('|' == s[i]) ||
                ('*' == s[i]) ||
                ('+' == s[i]) ||
                ('?' == s[i]) ||
                (',' == s[i])))
        RX_THROW_ARGS(IllegalArgumentException, RX_STRING("Illegal character at position " << i << ": " << s[i]));
    }

    std::pair<AbstractRegex *, unsigned int> m = parseRegex(s, 0);
    if (m.second < s.length()) {
        RX_THROW_ARGS(IllegalArgumentException, RX_STRING("Unexpected characters at the end of input regex string, starting at position " << m.second << ": " << s[m.second]));
    } else if (s.length() < m.second) {
        // we should not be here: something went wrong!
        RX_THROW_ARGS(NotImplementedError, RX_STRING("s.len()=" << s.length() << " < m.second=" << m.second));
    }

    RX_INFO("parse: " << (*m.first));
    return m.first;
}

