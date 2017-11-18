#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CP.h"

struct CP* newCP(char* course, char* preReq){
  struct CP *cp = malloc(sizeof(struct CP));
  cp->course = (char*)malloc(sizeof(char) * (6));
  cp->preReq = (char*)malloc(sizeof(char) * (3));
  strcpy(cp->course, course);
  strcpy(cp->preReq, preReq);
  cp->next = NULL;
  return cp;
}

struct CP** createTable() {
  struct CP** cpTab = malloc(1009*sizeof(struct CP));
  return cpTab;
}

int getCPKey(struct CP* cp) {
  int key = 0;
	int l = strlen(cp->course);
	for(int i=0; i < l; i++) {
		key += cp->course[i];
	}
	l = strlen(cp->preReq);
	for(int i = 0; i < l; i++) {
		key += cp->preReq[i];
	}
	key *= 997;
    return key%1009;
}

void insertTuple(struct CP** cpTable, char* course, char* preReq) {
  struct CP* cpTemp = newCP(course, preReq);
  int key = getCPKey(cpTemp);
  if (cpTable[key] == NULL) {
    cpTable[key] = cpTemp;
  } else {
    while(cpTable[key]->next != NULL){
      if (strcmp(cpTable[key]->course, course) == 0 && strcmp(cpTable[key]->preReq, preReq) == 0) {
        break;
      }
      cpTable[key] = cpTable[key]->next;
    }
    if (strcmp(cpTable[key]->course, course) != 0 || strcmp(cpTable[key]->preReq, preReq) != 0) {
      cpTable[key]->next = cpTemp;
    }
  }
}

void printTable(struct CP** cpTable) {
  for (int i = 0; i < 1009; i++) {
    if (cpTable[i] != NULL) {
      if (strcmp(cpTable[i]->course, "") != 0) {
        printf("Course: %s. PreReq: %s. Key %d\n", cpTable[i]->course, cpTable[i]->preReq, getCPKey(cpTable[i]));
      }
      while(cpTable[i]->next != NULL){
        if (strcmp(cpTable[i]->course, "") == 0) {
          cpTable[i] = cpTable[i]->next;
        } else {
          cpTable[i] = cpTable[i]->next;
          printf("Course: %s. PreReq: %s. Key %d\n", cpTable[i]->course, cpTable[i]->preReq, getCPKey(cpTable[i]));
        }
        if (cpTable[i]->next == NULL) {
          break;
        }
      }
    }
  }
}




int main(int argc, char* argv[]) {
  /*
  struct CP* cpTemp = newCP("coolg", "hehex");
  printf("%d", getCPKey(cpTemp));
  */
  struct CP** cpTable = createTable();
  insertTuple(cpTable, "CS101", "CS100");
  insertTuple(cpTable, "EE200", "EE005");
  insertTuple(cpTable, "EE200", "CS100");
  insertTuple(cpTable, "CS120", "CS101");
  insertTuple(cpTable, "CS121", "CS120");
  insertTuple(cpTable, "CS205", "CS101");
  insertTuple(cpTable, "CS206", "CS121");
  insertTuple(cpTable, "CS206", "CS205");
  insertTuple(cpTable, "CS120", "CS101");
  printTable(cpTable);
}
