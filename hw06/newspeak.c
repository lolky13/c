#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */
size_t m, flag;
/*inspired by courses examples*/
void append(char **tmp1, int *resL, int *resM, const char *appendStr, int appendLen){
  if(*resL + appendLen >= *resM){
    *resM = *resL + appendLen + 5;
    *tmp1 = (char *)realloc(*tmp1, *resM);
  }
  memcpy(*tmp1 + *resL, appendStr, appendLen);
  *resL += appendLen;
}
/*void append1(char **tmp1, int resL, int resM, const char *appendStr, int appendLen){
  if(resL + appendLen >= resM){
    resM = resL + appendLen + 5;
    *tmp1 = (char *)realloc(*tmp1, resM);
  }
  memcpy(*tmp1 + resL, appendStr, appendLen);
  resL += appendLen;
}*/

/*inspired by courses examples*/
char * strReplace ( char * text, const char * replace, const char * with){
  char *res = NULL, *occ;
  int resLen = 0, resMax = 0;
  int replaceLen = strlen(replace), withLen = strlen(with);
  if ( ! replaceLen ) 
    return NULL;
  /*if ( (m-replaceLen) > (strlen(text)+1) ){
    return text;
  }*/
  occ = strstr ( &text[m], replace );
  if (occ == &text[m]){
    append( &res, &resLen, &resMax, text, occ - text);
    append( &res, &resLen, &resMax, with, withLen );
    text = occ + replaceLen;
    m += withLen-1;
    flag = 0;
  }
  else{
    flag = 1;
    return text;
  }
  append(&res, &resLen, &resMax, text, strlen(text) + 1);
  return res;
}

char * newSpeak ( const char * text, const char * (*replace)[2] ){
  char *res=NULL, *tmp;
  int i=0, j=0;
  while (replace[j][0] != NULL){
    int k=j+1;
    size_t jLen=strlen(replace[j][0]);
    while (replace[k][0] != NULL){
      if (jLen < strlen(replace[k][0])){
          if ((strstr ( replace[k][0], replace[j][0])) == replace[k][0])
            return NULL;
      }
      else {
        if ((strstr ( replace[j][0], replace[k][0])) == replace[j][0])
          return NULL;
      }
      k++;
    }
    j++;
  }
  res = (char*)realloc(res, sizeof(*res) * ((strlen(text)) + 1));
  //append1( &res, 0, 0, text, strlen(text));
  //(res, text, strlen(text)+1);
  strcpy(res, text);
  m=0, flag=0;
  while (m <= strlen(res)){
    if (replace[i][0] == NULL){
      i = 0;
      if (flag == 1)
        m++;
    }
    tmp = strReplace(res, replace[i][0], replace[i][1]);
    if (flag == 0){
      size_t size = strlen(tmp);
      //append1( &res, 0, 0, tmp, size);
      res = (char*)realloc(res, sizeof(*res) * (size)+5);
      //memcpy(res, tmp, size+1);
      strcpy (res, tmp);
      free (tmp);
    }
    else {
      res = tmp;
    }
    i++;

  }
  //printf("%s\n", res);
  return res;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };

  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };

  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */