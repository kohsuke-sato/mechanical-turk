// mechanicalTurk.c
// Created by Albert Smith and Kohsuke Sato
// A file submission to "Mechanical Turk"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define ALL_PATHS {"RRLR", "RRLRL", "RRLRLL", "RRLRLLR", "RRLRLLRL",\
"RRLRLLRLR", "RRLRLLRLRL", "RR", "RRL", "RRLL", "RRLLR", "RRLLRL", \
"RRLLRLR", "RRLLRLRL", "RRLLRLRLR", "RRLLRLRLRL", "", "R", "RL", "RLR",\
"RLRL", "RLRLR", "RLRLRL", "RLRLRLR", "RLRLRLRL", "RLRLRLRLR", \
"RLRLRLRLRL", "L", "LR", "LRR", "LRRL", "LRRLR", "LRRLRL", "LRRLRLR", \
"LRRLRLRL", "LRRLRLRLR", "LRRLRLRLRL", "LRRLRLRLRLR", "LRL", "LRLR", \
"LRLRR", "LRLRRL", "LRLRRLR", "LRLRRLRL","LRLRRLRLR", "LRLRRLRLRL", \
"LRLRRLRLRLR", "LRLRL", "LRLRLR", "LRLRLRR","LRLRLRRL", "LRLRLRRLR", \
"LRLRLRRLRL", "LRLRLRRLRLR"}

action decideAction (Game g) {
    action testAction;
    action nextAction;
    
    char chosen = FALSE;

    // Try to change disciplines
    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BQN;
        testAction.disciplineTo = STUDENT_MJ;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MJ) < STUDENT_BQN * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BPS;
        testAction.disciplineTo = STUDENT_MJ;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MJ) < STUDENT_BPS * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BQN;
        testAction.disciplineTo = STUDENT_MTV;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MTV) < STUDENT_BQN * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BPS;
        testAction.disciplineTo = STUDENT_MTV;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MTV) < STUDENT_BPS * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BQN;
        testAction.disciplineTo = STUDENT_MMONEY;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) < STUDENT_BQN * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    if (!chosen) {
        testAction.actionCode = RETRAIN_STUDENTS;
        testAction.disciplineFrom = STUDENT_BPS;
        testAction.disciplineTo = STUDENT_MMONEY;
        if (isLegalAction(g, testAction) && getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) < STUDENT_BPS * 2) {
            nextAction = testAction;
            chosen = TRUE;
        }
    }

    // Mr GO8
    if (!chosen) {
        path paths[] = ALL_PATHS;
        int i = 0;
        while ((i < sizeof(paths) / sizeof(paths[0])) & !chosen) {
            testAction.actionCode = BUILD_GO8;
            memcpy(testAction.destination, paths[i],
                   sizeof(paths[i]));
            if (isLegalAction(g, testAction)) {
                nextAction = testAction;
                chosen = TRUE;
            }
            i++;
        }
    }

    // Mr Campus
    if (!chosen) {
        path paths[] = ALL_PATHS;
        int i = 0;
        while ((i < sizeof(paths) / sizeof(paths[0])) && !chosen)
        {
            testAction.actionCode = BUILD_CAMPUS;
            memcpy(testAction.destination, paths[i],
                   sizeof(paths[i]));
            if (isLegalAction(g, testAction)) {
                nextAction = testAction;
                chosen = TRUE;
            }
            i++;
        }
    }
    
    // The roots of Mr ARC - very buggy at the moment
    if (!chosen) {
        path arcs[] = ALL_PATHS;
        int i = 0;
        while ((i < sizeof(arcs) / sizeof(arcs[0])) && !chosen)
        {
            testAction.actionCode = OBTAIN_ARC;
            memcpy(testAction.destination, arcs[i],
                   sizeof(arcs[i]));
            if (isLegalAction(g, testAction)) {
                nextAction = testAction;
                chosen = TRUE;
            }
            i++;
        }
    }

    // Mr Pass

    if (!chosen) {
        testAction.actionCode = START_SPINOFF;
        if (isLegalAction(g, testAction)) {
            nextAction = testAction;
            chosen = TRUE;
        } 
    }

    if (!chosen) {
        nextAction.actionCode = PASS;
    }
     
    return nextAction;
}
