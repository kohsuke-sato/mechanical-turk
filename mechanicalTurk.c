// mechanicalTurk.c
// Created by Albert Smith and Kohsuke Sato
// A file submission to "Mechanical Turk"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

/*#define ALL_PATHS {"RRLR", "RRLRL", "RRLRLL", "RRLRLLR", "RRLRLLRL",\
"RRLRLLRLR", "RRLRLLRLRL", "RR", "RRL", "RRLL", "RRLLR", "RRLLRL", \
"RRLLRLR", "RRLLRLRL", "RRLLRLRLR", "RRLLRLRLRL", "", "R", "RL", "RLR",\
"RLRL", "RLRLR", "RLRLRL", "RLRLRLR", "RLRLRLRL", "RLRLRLRLR", \
"RLRLRLRLRL", "L", "LR", "LRR", "LRRL", "LRRLR", "LRRLRL", "LRRLRLR", \
"LRRLRLRL", "LRRLRLRLR", "LRRLRLRLRL", "LRRLRLRLRLR", "LRL", "LRLR", \
"LRLRR", "LRLRRL", "LRLRRLR", "LRLRRLRL","LRLRRLRLR", "LRLRRLRLRL", \
"LRLRRLRLRLR", "LRLRL", "LRLRLR", "LRLRLRR","LRLRLRRL", "LRLRLRRLR", \
"LRLRLRRLRL", "LRLRLRRLRLR"}*/

#define ALL_PATHS {"RL", "RLR", "RLL", "RLRL", "RLRR", "RLLR",\
 "RLRRL", "RLRLR", "RLRLL", "RLLRL", "RLRRLL", "RLRLRL",\
 "RLRLLR", "RLLRLR", "RLLRLRR", "RLRLRLL", "RLRLRLR", "RLRRLLR",\
 "RLLRLRRL", "RLRLRLLR", "RLRLRLRL", "RLRLRLRR","RLRLRLLRR", "RLLRLRRLR",\
 "", "R", "L", "RR", "LR", "RRL",\
 "LRL", "RRLR", "LRLR", "LRLRL", "RRLRL", "LRLRLR",\
 "RRLRLL", "LRLRLRR", "RRLRLLR", "LRLRLRR", "RRLRLLRL", "LRLRLRRL",\
 "RRLRLLRLR", "LRLRLRRLR", "LRLRLRRLRR", "RRLRLLRLRL", "LRLRRLRLRL", "RRLLRLRLR",\
 "LRLRRLRLRLR", "RRLLRLRLRL", "LRRLRLRLRL", "RLRLRLRLR", "RLRLRLRLRL", "LRRLRLRLRLR"}
 #define NUM_PATHS 54

action decideAction (Game g) {
    action testAction;
    action nextAction;
    
    char chosen = FALSE;
    int mostStudents;
    int leastStudents;

    // Mr retrain
    if (!chosen) {
        mostStudents = STUDENT_BPS;
        leastStudents = STUDENT_BPS;
        int i = STUDENT_BPS;
        while (i <= STUDENT_MMONEY) {
            if (getStudents(g, getWhoseTurn(g), i) < getStudents(g, getWhoseTurn(g), leastStudents)) {
                leastStudents = i;
            }
            if (getStudents(g, getWhoseTurn(g), i) > getStudents(g, getWhoseTurn(g), mostStudents)) {
                mostStudents = i;
            }
            i++;
        }
        
        if (getStudents(g, getWhoseTurn(g), STUDENT_BQN) == 0) {
            leastStudents = STUDENT_BQN;
        } else if (getStudents(g, getWhoseTurn(g), STUDENT_BPS) == 0) {
            leastStudents = STUDENT_BPS;
        }
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = mostStudents;
        testAction.disciplineTo = leastStudents;
        if ((getStudents(g, getWhoseTurn(g), mostStudents) > 3) && isLegalAction(g, testAction)) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    // Mr Campus
    if (!chosen) {
        path paths[] = ALL_PATHS;
        int i = 0;
        while ((i < NUM_PATHS) && !chosen) {
            testAction.actionCode = BUILD_CAMPUS;
            memcpy(testAction.destination, paths[i], sizeof(paths[i]));
            if (isLegalAction(g, testAction)) {
                nextAction = testAction;
                chosen = TRUE;
            }
            i++;
        }
    }

    // Mr ARC
    if (!chosen) {
        path arcs[] = ALL_PATHS;
        int i = 0;
        while ((i < NUM_PATHS) && !chosen) {
            testAction.actionCode = OBTAIN_ARC;
            memcpy(testAction.destination, arcs[i], sizeof(arcs[i]));
            if (isLegalAction(g, testAction)) {
                nextAction = testAction;
                chosen = TRUE;
            }
            i++;
        }
    }

    // Mr GO8
    if (!chosen) {
        if (getCampuses(g, getWhoseTurn(g)) > 0) {
            path paths[] = ALL_PATHS;
            int i = 0;
            while ((i < NUM_PATHS) & !chosen) {
                testAction.actionCode = BUILD_GO8;
                memcpy(testAction.destination, paths[i], sizeof(paths[i]));
                if (isLegalAction(g, testAction)) {
                    nextAction = testAction;
                    chosen = TRUE;
                }
                i++;
            }
        }
    }

    // Mr Spinoff
    if (!chosen) {
        testAction.actionCode = START_SPINOFF;
        if (isLegalAction(g, testAction)) {
            nextAction = testAction;
            chosen = TRUE;
        } 
    }

    // Mr Pass
    if (!chosen) {
        nextAction.actionCode = PASS;
    }
     
    return nextAction;
}
