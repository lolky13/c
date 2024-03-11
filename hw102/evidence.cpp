#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CEmployee;

class CEmail{
  public:
    CEmail(string email, CEmployee *person = nullptr): email(email), person(person){}
    bool operator < (const CEmail& e)const{ //< operator definition for comparing emails
        return this->email < e.email;
    }
    bool emailIsInList(const CEmail& e)const{ // check whether the email is already in db
      return (this->email == e.email);
    }
    CEmployee *dName(){
      return this->person;
    }
    string email;
    CEmployee *person;
};

class CEmployee { //class definition for vector structure
  public:
    CEmployee(const string name, const string surname, unsigned int salary,  CEmail *pEmail = nullptr): name(name), surname(surname), salary(salary), pEmail(pEmail){}
    bool operator < (const CEmployee& e)const{ //< operator definition for comparing employees by names
      if ( this->surname == e.surname ) 
        return this->name < e.name;
      return this->surname < e.surname;
    }
    bool nameIsInList(const CEmployee& e)const{ // check whether the person is already in db
      return (this->name == e.name && this->surname == e.surname);
    }
    unsigned int getSalary()const{ // get persons salary
      return this->salary;
    }
    CEmail *dEmail(){
      return this->pEmail;
    }
  //private: // persons data
    string name, surname;
    unsigned int salary;
    CEmail *pEmail;
};



class CPersonalAgenda
{
  public:
                  CPersonalAgenda  ( void ){}
                  ~CPersonalAgenda ( void ){
                    for (auto &n : m_list)
                      delete n;
                    for (auto &e : m_listByEmail)
                      delete e;
                  }
    // function to add new person into db
    bool          add              ( const string & name,const string & surname,const string & email,unsigned int salary){
      CEmployee *newEmployee = new CEmployee(name, surname, salary);
      CEmail *newEmail = new CEmail(email);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
      // check whether the new email or name is present, if yes returns false
      if ( (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)) || (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail))){
        delete newEmail;
        delete newEmployee;
        return false;
      }
      // inserts email alphabetically
      
      m_listByEmail.insert( foundByEmail, newEmail);
      // inserts person alphabetically
      m_list.insert( foundByName, newEmployee );
      newEmail->person = newEmployee;
      newEmployee->pEmail = newEmail;
      return true;
    }
    bool          del              ( const string & name, const string & surname ){ // delete person by name
      if (m_list.empty())
        return false;
      CEmployee *newEmployee = new CEmployee(name, surname, 100);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){ // deletes person, if it's present
        auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), (*foundByName)->dEmail(), []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
        delete *foundByEmail;
        delete *foundByName;
        m_listByEmail.erase(foundByEmail);
        m_list.erase(foundByName);
        
        delete newEmployee; 
        return true;
      }
      //return false, if it's not present
      delete newEmployee;
      return false;
    }
    bool          del              ( const string & email ){ // delete person by email
      if (m_list.empty())
        return false;
      CEmail *newEmail = new CEmail(email);
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
      if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail)){ // deletes person, if it's present
          auto foundByName = lower_bound(m_list.begin(), m_list.end(), (*foundByEmail)->dName(), []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
          delete *foundByEmail;
          delete *foundByName;
          m_listByEmail.erase(foundByEmail);
          m_list.erase(foundByName);
          
          delete newEmail;
          return true;
		  }
      //return false, if it's not present
      delete newEmail;
      return false;
    }
    bool          changeName       ( const string & email, const string & newName, const string & newSurname ){ // changes persons name
      if (m_list.empty())
        return false;
      CEmail *newEmail = new CEmail(email);
      CEmployee *newEmployee = new CEmployee(newName, newSurname, 100);
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
			  if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail)){ // if the email is present
          auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return *l < *r; });
          if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){ // returns false, if the new name is present
            delete newEmail;
            delete newEmployee;
            return false;
          }
          foundByName = lower_bound(m_list.begin(), m_list.end(), (*foundByEmail)->dName(), []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
          (newEmployee)->salary = (*foundByName)->salary;
          delete *foundByEmail;
          delete *foundByName;
          m_listByEmail.erase(foundByEmail);
          m_list.erase(foundByName); // deletes the old entry
          
          foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
          foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
          // inserts email alphabetically
          
          m_listByEmail.insert( foundByEmail, newEmail);
          // inserts person alphabetically
          m_list.insert( foundByName, newEmployee );
          newEmail->person = newEmployee;
          newEmployee->pEmail = newEmail;
                  
          //delete newEmail;
          //delete newEmployee;
          //add(newName, newSurname, email, salary); // add new person
          
          return true;
        }
      delete newEmail;
      delete newEmployee;
      return false;
    }
    bool          changeEmail      ( const string & name, const string & surname, const string & newEmail ){ // changes persons email
      if (m_list.empty())
        return false;
      CEmployee *newEmployee = new CEmployee(name, surname, 100);
      CEmail *neEmail = new CEmail(newEmail);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){
        auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), neEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
        if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*neEmail)){
          delete neEmail;
          delete newEmployee;
          return false;
        }
        auto tmp = (*foundByName)->dEmail();
        auto foundByEmailOld = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), tmp, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
        delete *foundByEmailOld;
        m_listByEmail.erase(foundByEmailOld); // deletes the old entry
        
        m_listByEmail.insert( foundByEmail, neEmail); // inserts email alphabetically
        neEmail->person = *foundByName;
        delete newEmployee;
        return true;
      }
      delete newEmployee;
      delete neEmail;
      return false;
    }
    bool          setSalary        ( const string & name, const string & surname, unsigned int   salary ){ // changes persons salary by name
      if (m_list.empty())
        return false;
      CEmployee *newEmployee = new CEmployee(name, surname, salary);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){ // if person is present
        (*foundByName)->salary = salary;
        delete newEmployee;
        return true;
      }
      delete newEmployee;
      return false;
    }
    bool          setSalary        ( const string & email, unsigned int   salary ){ // changes persons salary by email
      if (m_listByEmail.empty())
        return false;
      CEmail *newEmail = new CEmail(email);
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
      if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail)){
        (*foundByEmail)->person->salary = salary;
        delete newEmail;
        return true;
      }
      delete newEmail;
      return false;
    }
    unsigned int  getSalary        ( const string & name, const string & surname ) const{ // gets persons salary by name
      if (m_list.empty())
        return 0;
      CEmployee *newEmployee = new CEmployee(name, surname, 100);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){ // person is present
        delete newEmployee;
        return (*foundByName)->salary;
      }
      delete newEmployee;
      return 0;
    }
    unsigned int  getSalary        ( const string & email ) const{ // gets persons salary by email
      if (m_listByEmail.empty())
        return 0;
      CEmail *newEmail = new CEmail(email);
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
      if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail)){
        delete newEmail;
        return ((*foundByEmail)->person->salary);
      }
      delete newEmail;
      return 0;
    }
    bool          getRank          ( const string & name, const string & surname, int & rankMin, int & rankMax ) const{ // gets persons salary position by name
      if (m_list.empty())
        return false;
      CEmployee *newEmployee = new CEmployee(name, surname, 100);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if (foundByName == m_list.end()){ // person is not present
        delete newEmployee;
        return false;
      }
      if (!(*foundByName)->nameIsInList(*newEmployee)){
        delete newEmployee;
        return false;
      }
      unsigned int employeeRate = (*foundByName)->salary;
      unsigned int less = 0, same = 0;
      for ( size_t i = 0; i < m_list.size ( ); ++ i ) {
			  unsigned int tmp = m_list [ i ]->salary;
        if (tmp<employeeRate)
          less++;
        else if (tmp == employeeRate)
          same++;
      }
      rankMin = less;
      rankMax = less + same -1;
      delete newEmployee;
      return true;;
    }

    bool          getRank          ( const string & email, int    & rankMin, int    & rankMax ) const{ // gets persons salary position by name
      if (m_list.empty())
        return false;
      CEmail *newEmail = new CEmail(email);
      auto foundByEmail = lower_bound(m_listByEmail.begin(), m_listByEmail.end(), newEmail, []( const CEmail *l, const CEmail *r ) { return  *l < *r; });
      if (foundByEmail != m_listByEmail.end() && (*foundByEmail)->emailIsInList(*newEmail)){
        unsigned int employeeRate = (*foundByEmail)->person->getSalary();
          unsigned int less = 0, same = 0;
          for ( size_t j = 0; j < m_list.size ( ); ++ j ) {
            unsigned int tmp = m_list [ j ]->getSalary();
            if (tmp < employeeRate)
              less++;
            else if (tmp == employeeRate)
              same++;
          }
          rankMin = less;
          rankMax = less + same -1;
          delete newEmail;
          return true;
      }
      delete newEmail;
      return false;
    }

    bool getFirst( string & outName, string & outSurname ) const{ // gets first person present
      if (m_list.empty())
        return false;
      outName = m_list[0]->name;
      outSurname = m_list[0]->surname;
      return true;
    }
    bool getNext( const string & name, const string & surname, string & outName, string & outSurname ) const{ // gets next person 
      if (m_list.empty())
        return false;
      CEmployee *newEmployee = new CEmployee(name, surname, 100);
      auto foundByName = lower_bound(m_list.begin(), m_list.end(), newEmployee, []( const CEmployee *l, const CEmployee *r ) { return  *l < *r; });
      if ((foundByName == (m_list.end() - 1) ) || (foundByName == m_list.end())){ // end of db
        delete newEmployee;
        return false;
      }
      if (foundByName != m_list.end() && (*foundByName)->nameIsInList(*newEmployee)){ // person is present
        outName = (*(foundByName + 1))->name;
        outSurname = (*(foundByName + 1))->surname;
        delete newEmployee;
        return true;
      }
      delete newEmployee;
      return false;
    }
  private:
    // todo
    vector<CEmployee *>  m_list;
    vector<CEmail *> m_listByEmail;
};


#ifndef __PROGTEST__
int main ( void )
{
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert ( b1 . add ( "John", "Smith", "john", 30000 ) );
  assert ( b1 . add ( "John", "Miller", "johnm", 35000 ) );
  assert ( b1 . add ( "Peter", "Smith", "peter", 23000 ) );
  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( b1 . getNext ( "John", "Smith", outName, outSurname )
           && outName == "Peter"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "Peter", "Smith", outName, outSurname ) );
  assert ( b1 . setSalary ( "john", 32000 ) );
  assert ( b1 . getSalary ( "john" ) ==  32000 );
  // cout << b1 . getSalary ( "John", "Smith" ) << endl;
  assert ( b1 . getSalary ( "John", "Smith" ) ==  32000 );
  assert ( b1 . getRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . getRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getRank ( "johnm", lo, hi )
           && lo == 2
           && hi == 2 );
  assert ( b1 . setSalary ( "John", "Smith", 35000 ) );
  assert ( b1 . getSalary ( "John", "Smith" ) ==  35000 );
  assert ( b1 . getSalary ( "john" ) ==  35000 );
  assert ( b1 . getRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . getRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getRank ( "johnm", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . changeName ( "peter", "James", "Bond" ) );
  assert ( b1 . getSalary ( "peter" ) ==  23000 );
            //cout << b1 . getSalary ( "James", "Bond" ) << endl;
  assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . getSalary ( "Peter", "Smith" ) ==  0 );
  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "James"
           && outSurname == "Bond" );
  assert ( b1 . getNext ( "James", "Bond", outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . changeEmail ( "James", "Bond", "james" ) );
  assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . getSalary ( "james" ) ==  23000 );
  assert ( b1 . getSalary ( "peter" ) ==  0 );
  assert ( b1 . del ( "james" ) );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 0
           && hi == 1 );
  assert ( b1 . del ( "John", "Miller" ) );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . del ( "john" ) );
  assert ( ! b1 . getFirst ( outName, outSurname ) );
  assert ( b1 . add ( "John", "Smith", "john", 31000 ) );
  assert ( b1 . add ( "john", "Smith", "joHn", 31000 ) );
  assert ( b1 . add ( "John", "smith", "jOhn", 31000 ) );

  CPersonalAgenda b2;
  assert ( ! b2 . getFirst ( outName, outSurname ) );
  assert ( b2 . add ( "James", "Bond", "james", 70000 ) );
  assert ( b2 . add ( "James", "Smith", "james2", 30000 ) );
  assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( ! b2 . add ( "James", "Bond", "james3", 60000 ) );
  assert ( ! b2 . add ( "Peter", "Bond", "peter", 50000 ) );
  assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . setSalary ( "Joe", "Black", 90000 ) );
  assert ( ! b2 . setSalary ( "joe", 90000 ) );
  assert ( b2 . getSalary ( "Joe", "Black" ) ==  0 );
  assert ( b2 . getSalary ( "joe" ) ==  0 );
  assert ( ! b2 . getRank ( "Joe", "Black", lo, hi ) );
  assert ( ! b2 . getRank ( "joe", lo, hi ) );
  assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . del ( "Joe", "Black" ) );
  assert ( ! b2 . del ( "joe" ) );
  assert ( ! b2 . changeName ( "james2", "James", "Bond" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "james" ) );
  assert ( ! b2 . changeName ( "peter", "Peter", "Smith" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter" ) );
  assert ( b2 . del ( "Peter", "Smith" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter2" ) );
  assert ( ! b2 . setSalary ( "Peter", "Smith", 35000 ) );
  assert ( b2 . getSalary ( "Peter", "Smith" ) ==  0 );
  assert ( ! b2 . getRank ( "Peter", "Smith", lo, hi ) );
  assert ( ! b2 . changeName ( "peter", "Peter", "Falcon" ) );
  assert ( ! b2 . setSalary ( "peter", 37000 ) );
  assert ( b2 . getSalary ( "peter" ) ==  0 );
  assert ( ! b2 . getRank ( "peter", lo, hi ) );
  assert ( ! b2 . del ( "Peter", "Smith" ) );
  assert ( ! b2 . del ( "peter" ) );
  assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( b2 . getSalary ( "peter" ) ==  40000 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
