#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem * m_Next;
  char * m_Name;
  char m_Secret[24];
} TITEM;
#endif /* __PROGTEST__ */

TITEM* newItem(const char* name,TITEM* next){
  TITEM* tmp = (TITEM*)malloc(sizeof(TITEM));
  char* n=NULL;
  strcpy(n,name);
  tmp->m_Name = n;
  memset(tmp->m_Secret, '\0', (sizeof(tmp->m_Secret)));
  tmp->m_Next = next;
  return tmp;
}

void frontBackSplit(TITEM* src, TITEM* front, TITEM* back){
    if (src == NULL || src->m_Next == NULL){
        front = src;
        back = NULL;
        return;
    }
    TITEM* slow = src;
    TITEM* fast = src->m_Next;
    while (fast != NULL){
        fast = fast->m_Next;
        if (fast != NULL){
            slow = slow->m_Next;
            fast = fast->m_Next;
        }
    }
    front = src;
    back = slow->m_Next;
    slow->m_Next = NULL;
}

TITEM* sortedMerge(TITEM* a, TITEM* b, int ascending){
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    TITEM* result = NULL;
    if (ascending){
      if (a->m_Name <= b->m_Name){
          result = a;
          result->m_Next = sortedMerge(a->m_Next, b, ascending);
      }
      else {
          result = b;
          result->m_Next = sortedMerge(a, b->m_Next, ascending);
      }
    }
    else{
      if (a->m_Name >= b->m_Name){
          result = a;
          result->m_Next = sortedMerge(a->m_Next, b, ascending);
      }
      else {
          result = b;
          result->m_Next = sortedMerge(a, b->m_Next, ascending);
      }
    }
    return result;
}

TITEM* sortList(TITEM* l,int ascending){
    if (l == NULL || l->m_Next == NULL)
        return l;
    TITEM* a=NULL;
    TITEM* b=NULL;
    frontBackSplit(l, a, b);
    sortList(a, ascending);
    sortList(b, ascending);
    return sortedMerge(a, b, ascending);
}


void freeList(TITEM* src){
  TITEM  * tmp;
  while ( src->m_Name ){
    tmp = src->m_Next;
    free (src->m_Name);
    //free (src->m_Secret);
    src->m_Next = tmp;
  }
  src -> m_Next  = NULL;
  free ( src );
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TITEM * l;
  char tmp[50];

  assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
  l = NULL;
  l = newItem ( "PA1", l );
  l = newItem ( "PA2", l );
  l = newItem ( "UOS", l );
  l = newItem ( "LIN", l );
  l = newItem ( "AG1", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 1 );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = newItem ( "programming and algorithmic I", l );
  l = newItem ( "AAG", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  l = NULL;
  strncpy ( tmp, "PA1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "PA2", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "UOS", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "LIN", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 1 );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  strncpy ( tmp, "programming and algorithmic I", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AAG", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */