#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRange
{
  public:
    // constructor
    CRange(const long long & low, const long long & hig){
        if (low > hig)
            throw logic_error("Error: Lo > Hi."); // idk how to use this
        else {
            lo = low;
            hi = hig;
        }
    }
    // operator <
    bool operator < (const CRange & r)const{
      if (r.lo == LLONG_MIN)
        return false;
      return this->hi < (r.lo - 1); // hi in list is less than lo-1 in searched range
    }
    // operator +
    vector<CRange> operator + (const CRange & r)const{
      vector<CRange> m_Res;

      if (r.lo <= this->lo ){ 
        if (r.hi <= this->hi){      
          if (this->lo != LLONG_MIN && r.hi < (this->lo -1)){
            m_Res.push_back(r);
            m_Res.push_back(*this);
          }
          else
            m_Res.push_back(CRange(r.lo, this->hi));
        }
        else
          m_Res.push_back(r);
      }
      else{
        if (this->hi == LLONG_MAX)
          m_Res.push_back(*this);
        else if (r.lo > (this->hi + 1)){
          m_Res.push_back(*this);
          m_Res.push_back(r);
        }
        else{
          if (r.hi <= this->hi)
            m_Res.push_back(*this);
          else
            m_Res.push_back(CRange(this->lo,r.hi));
        }
      }
      return m_Res;
    }

    friend vector<CRange> operator + (const vector<CRange> & list, const CRange & range) {

      vector<CRange> m_Res = list;
      auto found = lower_bound(m_Res.begin(), m_Res.end(), range, []( const CRange & l, const CRange & r ) { return  l < r; });
      if (found == m_Res.end()){  // end of list, lo in new range is bigger than last hi 
        m_Res.insert(found, range);
        return m_Res;
      }
      if (range.lo >= found->lo){
        if (found->hi == LLONG_MAX || (found->hi + 1) >= range.lo){
          vector<CRange> m_Tmp = (*found) + range;
          (*found) = m_Tmp[0];
        }
        else
          found = m_Res.insert(found,range);
      }
      else
        found = m_Res.insert(found,range);

      auto foundNext = found + 1;
      if (found == m_Res.end() || foundNext == m_Res.end())             // end of list
        return m_Res;
      while (found->hi >= (foundNext->lo - 1)){ // while new hi is equal or greater than next lo-1
        vector<CRange> m_Tmp = (*found) + (*foundNext);
        (*found) = m_Tmp[0];
        foundNext =  m_Res.erase(foundNext);               // erase the old range
        if (foundNext == m_Res.end())           // end of list, return
          return m_Res;
      }
      return m_Res;
    }
    // operator -
    vector<CRange> operator - (const CRange & r)const{
      vector<CRange> m_Res;
      if ( r.hi < this->lo)         // range is lower
        m_Res.push_back(*this);
      else if (r.lo <= this->lo ){    
        if (r.hi < this->hi)        // range between range hi and this hi  
          m_Res.push_back(CRange(r.hi + 1, this->hi));
      }
      else{
        if (r. lo > this->hi)       // range is higher
          m_Res.push_back(*this);
        else {                      // range between this lo and range lo
          m_Res.push_back(CRange(this->lo, r.lo - 1));
          if (r.hi < this->hi)      // range between range hi and this hi
            m_Res.push_back(CRange(r.hi + 1, this->hi));
        }
      }
      return m_Res;
    }

    friend vector<CRange> operator - (const vector<CRange> & list, const CRange & range) {

      vector<CRange> m_Res = list;
      auto found = lower_bound(m_Res.begin(), m_Res.end(), range, []( const CRange & l, const CRange & r ) { return  l < r; });
      if (found == m_Res.end()){  // end of list
        return m_Res;
      }
      vector<CRange> m_Tmp = (*found) - range;
      if (m_Tmp.size() == 0)  // deleted whole range
        found = m_Res.erase(found);
      else{
        (*found) = m_Tmp[0];    // deleted range from side 
        if (m_Tmp.size() == 2){  // deleted range from in between
          m_Res.insert(++found, m_Tmp[1]);
          return m_Res;
        }
        found++;
      }

      if (found == m_Res.end()) // end of list
        return m_Res;
      while (range.hi >= (found->lo)){                  // while new hi is equal or greater than next lo-1
        m_Tmp = (*found) - range;
        if (m_Tmp.size() == 0){                             // erase the old range
          found = m_Res.erase(found);
          if (found == m_Res.end())                     // end of list, return
            return m_Res;
        }
        else{
          (*found) = m_Tmp[0];            // deleted range from side
          found++;
        }
        if (found == m_Res.end())         // end of list, return
          return m_Res;
      }
      return m_Res;
    }

    //operator !=
    bool operator != (const CRange & r)const{
      return (this->lo != r.lo || this->hi != r.hi);
    }

    // range members
    long long lo, hi;
};
class CRangeList
{
  public:
    // constructor
    CRangeList() {}
    CRangeList(const CRangeList & l) { m_List = l.m_List; }

    // includes long long / range
    bool includes(const int value) const {
		  return includes(CRange(value, value));
	  }
	  bool includes(const long long & r) const {
		  return includes(CRange(r, r));
	  }
    bool includes(const CRange & r) const {
		  auto found = lower_bound(m_List.begin(), m_List.end(), r, []( const CRange & l, const CRange & r ) { return  l < r; });
		  if (found == m_List.end())
        return false;
		  return (r.lo >= found->lo && r.hi <= found->hi);
	  }

    // = range / range list
    CRangeList & operator = (const CRange & range){
      m_List.clear();
      m_List.push_back(range);
      return *this;
    }
    CRangeList & operator = (const CRangeList & list){
      m_List = list.m_List;
      return *this;
    }
    CRangeList & operator = (const vector<CRange> & vect){
      m_List = vect;
      return *this;
    }
    // += range / range list
    CRangeList & operator += (const CRange & range){
      this->m_List = this->m_List + range;
      return *this;
    }
    CRangeList & operator += (const CRangeList & list){
      for (size_t i = 0; i < list.m_List.size(); i++)
        *this += list.m_List[i];
      return *this;
    }
    CRangeList & operator += (const vector<CRange> & vect){
      for (auto & r : vect)
        *this += r;
      return *this;
    }
    // -= range / range list
    CRangeList & operator -= (const CRange & range){
      this->m_List = this->m_List - range;
      return *this;
    }
    CRangeList & operator -= (const CRangeList & list){
      *this -= list.m_List;
      return *this;
    }
    CRangeList & operator -= (const vector<CRange> & vect){
      for (auto & r : vect)
        *this -= r;
      return *this;
    }

    // operator ==
    bool operator == (const CRangeList & l)const{
      if (l.m_List.size() != m_List.size())
        return false;
      for (size_t i = 0; i < m_List.size(); i++){
        if (l.m_List[i] != m_List[i])
          return false;
      }
      return true;
    }
    // operator !=
    bool operator != (const CRangeList & l)const{
      return !(*this == l);
    }

    // operator <<
    friend ostream & operator << (ostream & out, const CRangeList & l) {
      out << "{";
      bool colon = false;
      for (auto o : l.m_List){
        if (colon)
          out << ",";
        colon = true;
        if (o.lo != o.hi)
          out << "<" << o.lo << ".." << o.hi << ">";
        else
          out << o.lo;
      }
      out << "}";
      return out;
    }

    // list
    vector<CRange> m_List;
};

#ifndef __PROGTEST__
string toString ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
  CRangeList a, b;
  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 50 );
  assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
  a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
  assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
  a += CRange ( 106, 119 ) + CRange ( 152, 158 );
  assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
  a += CRange ( -3, 170 );
  a += CRange ( -30, 1000 );
  assert ( toString ( a ) == "{<-30..1000>}" );
  b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
  a += b;
  assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( -400, -400 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  try
  {
    a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
    assert ( "Exception not thrown" == nullptr );
  }
  catch ( const std::logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == nullptr );
  }
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  b = a;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 15, 15 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
  assert ( !( a == b ) );
  assert ( a != b );
  assert ( b . includes ( 15 ) );
  assert ( b . includes ( 2900 ) );
  assert ( b . includes ( CRange ( 15, 15 ) ) );
  assert ( b . includes ( CRange ( -350, -350 ) ) );
  assert ( b . includes ( CRange ( 100, 200 ) ) );
  assert ( !b . includes ( CRange ( 800, 900 ) ) );
  assert ( !b . includes ( CRange ( -1000, -450 ) ) );
  assert ( !b . includes ( CRange ( 0, 500 ) ) );
  a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
  assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );

#ifdef EXTENDED_SYNTAX
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
