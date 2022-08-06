#ifndef DE99A324_78F6_4041_9C09_5DB4135F2509
#define DE99A324_78F6_4041_9C09_5DB4135F2509
#include <fstream>
#include <string>
using namespace std;
/**
 * @brief Text, Uli, Oli, Hr, Title, Img, ImgBracket, Hyper
 *
 */
enum Type {
    Text,   // start with
    Uli,    // start with
    Oli,    // start with
    Hr,     // start with
    Title,  // start with
    Img,
    ImgBracket,
    Hyper
};
/**
 * @brief judge string s[startFrom]~s[s.len] start from what
 *
 * @param s the string
 * @param startFrom index that start judging from
 * @return Type
 */
Type startWith(string& s, int startFrom);
/**
 * @brief Get the Url
 *
 * @param s the string
 * @param startFrom index that start judging from
 * @return string
 */
string getUrl(string& s, int startFrom);
/**
 * @brief Get the Alt
 *
 * @param s the string
 * @param startFrom index that start from judging from
 * @return string
 */
string getAlt(string& s, int startFrom);
/**
 * @brief find the position of c in s starting from startFrom
 *
 * @param s the string
 * @param startFrom index that from which starts judging
 * @param c
 * @param exclude if there's any char in between c and start, return -1
 * @return int -1 if failed, otherwise the index
 */
int findChar(string& s, int startFrom, char c, string exclude);
/**
 * @brief judge whether s consists of only space and \n
 *
 * @param s
 * @return true
 * @return false
 */
bool isEmpty(string& s);
int findDigit(string& s, int startFrom);
#endif /* DE99A324_78F6_4041_9C09_5DB4135F2509 */
