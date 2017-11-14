#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSG.h"

struct CSG* newCSG(char* course, int studentID, char* grade){
  struct CSG *csg = malloc(sizeof(struct CSG));
  csg->course = (char*)malloc(sizeof(char) * (6));
  csg->grade = (char*)malloc(sizeof(char) * (3));
  strcpy(csg->course, course);
  strcpy(csg->grade, grade);
  csg->studentID = studentID;
  csg->next = NULL;
  return csg;
}

struct CSG** createTable() {
  struct CSG** csgTab = malloc(1009*sizeof(struct CSG));
  return csgTab;
}

int getHashKey(struct CSG* csg) {
  return csg->studentID % 1009;
}

void insertTuple(struct CSG** csgTable, char* course, int studentID, char* grade) {
  struct CSG* csgTemp = newCSG(course, studentID, grade);
  int key = getHashKey(csgTemp);
  if(csgTable[key] == NULL){
    csgTable[key] = csgTemp;
    //printf("hello");
  } else{
    while(csgTable[key]->next != NULL){
      csgTable[key] = csgTable[key]->next;
    }
    csgTable[key]->next = csgTemp;
  }
  //csgTable[key] = csgTemp;
}

void deleteTuple(struct CSG** csgTable, char* course, int studentID, char* grade) {
  struct CSG* csgTemp = newCSG(course, studentID, grade);
  struct CSG* csgFiller = newCSG("", 0, "");
  char string[50];
  sprintf(string, "%d", studentID);
  char* idString = string;
  //all three defined
  if (strcmp(course, "*") != 0 && strcmp(idString, "*") != 0 && strcmp(grade, "*") != 0) {
    //printf("Gets here");
    int key = getHashKey(csgTemp);
    if (strcmp(csgTable[key]->course, course) == 0 && strcmp(csgTable[key]->grade, grade) == 0 && csgTable[key]->studentID == studentID) {
      //printf("Reaches Here");
      csgTable[key] = csgFiller;
    }
    while(csgTable[key]->next != NULL) {
      if (strcmp(csgTable[key]->course, course) == 0 && strcmp(csgTable[key]->grade, grade) == 0 && csgTable[key]->studentID == studentID) {
        //printf("Reaches Here");
        csgTable[key] = csgFiller;
        break;
      } else {
        //printf("Reaches Here");
        csgTable[key] = csgTable[key]->next;
      }
    }
  }
  //only studentID defined
  else if (strcmp(course, "*") == 0 && strcmp(grade, "*") == 0) {
    int key = getHashKey(csgTemp);
    while(csgTable[key]->next != NULL) {
      if (csgTable[key]->studentID == studentID) {
        //printf("Reaches Here");
        csgTable[key] = csgFiller;
      } else {
        //printf("Reaches Here");
        csgTable[key] = csgTable[key]->next;
      }
    }
    if (csgTable[key]->studentID == studentID) {
      //printf("Reaches Here");
      csgTable[key] = csgFiller;
    }
  }

  //studentID and grade defined
  else if (strcmp(course, "*") == 0) {
    int key = getHashKey(csgTemp);
    while(csgTable[key]->next != NULL) {
      if (csgTable[key]->studentID == studentID && strcmp(csgTable[key]->grade, grade) == 0){
        //csgTable[key] = csgFiller;
        printf("gets here");
        csgTable[key] = csgTable[key]->next;
      } else {
        csgTable[key] = csgTable[key]->next;
      }
    }
  }
}


void printTable(struct CSG** csgTable) {
  for (int i = 0; i < 1009; i++) {
    if (csgTable[i] != NULL) {
      if (strcmp(csgTable[i]->course, "") != 0) {
        printf("Course: %s. Student ID: %d. Grade: %s. Key %d\n", csgTable[i]->course, csgTable[i]->studentID, csgTable[i]->grade, getHashKey(csgTable[i]));
      }
      while(csgTable[i]->next != NULL){
        if (strcmp(csgTable[i]->course, "") == 0) {
          csgTable[i] = csgTable[i]->next;
        } else {
          csgTable[i] = csgTable[i]->next;
          printf("Course: %s. Student ID: %d. Grade: %s, Key: %d\n", csgTable[i]->course, csgTable[i]->studentID, csgTable[i]->grade, getHashKey(csgTable[i]));
        }

        if (csgTable[i]->next == NULL) {
          break;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  struct CSG** csgTable = createTable();
  //insertTuple(csgTable, "", 0, "");
  insertTuple(csgTable, "CSC101", 12345, "A");
  insertTuple(csgTable, "CSC101", 67890, "B");
  insertTuple(csgTable, "EE200", 12345, "C");
  insertTuple(csgTable, "EE200", 49192, "D");
  insertTuple(csgTable, "PH100", 81824, "C-");
  insertTuple(csgTable, "EN150", 20310, "D+");
  insertTuple(csgTable, "EE200", 22222, "B+");
  insertTuple(csgTable, "CSC101", 33333, "A-");
  insertTuple(csgTable, "PH100", 67890, "C+");
  insertTuple(csgTable, "CSC101", 67890, "C+");
  deleteTuple(csgTable, "EN150", 20310, "D+");
  deleteTuple(csgTable, "*", 12345, "*");
  deleteTuple(csgTable, "*", 67890, "C+");
  printTable(csgTable);
}
