// mechanicalTurk.c
// Created by Albert Smith and Kohsuke Sato
// A file submission to "Mechanical Turk"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    action nextAction;
    action testAction;
    
    char chosen = FALSE;
    
    // Mr Pass - commented out for now
    /*
    testAction.actionCode = START_SPINOFF;
    if (isLegalAction(g, testAction)) {
        nextAction.actionCode = START_SPINOFF;
    } else {
        nextAction.actionCode = PASS;
    }
    */

    // Mr Campus
    if (!chosen) {
        path paths[] = ALL_PATHS;
        int i = 0;
        while ((i < sizeof(paths) / sizeof(paths[0])) && !chosen)
        {
            testAction.actionCode = BUILD_CAMPUS;
            testAction.destination = arcs[i];
            if (isLegalAction(g, testAction)) {
                nextAction.actionCode = BUILD_CAMPUS;
                nextAction.destination = arcs[i];
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
            testAction.actionCode = BUILD_ARC;
            testAction.destination = paths[i];
            if (isLegalAction(g, testAction)) {
                nextAction.actionCode = BUILD_ARC;
                nextAction.destination = paths[i];
                chosen = TRUE;
            }
            i++;
        }
    }
    
    // Mr GO8
    if (!chosen) {
        path paths[] = ALL_PATHS;
        int i = 0;
        while ((i < sizeof(paths) / sizeof(paths[0])) & !chosen) {
            testAction.actionCode = BUILD_GO8;
            testAction.destination = paths[i];
            if (isLegalAction(g, testAction)) {
                nextAction.actionCode = BUILD_GO8;
                nextAction.destination = paths[i];
                chosen = TRUE;
            }
            i++;
        }
    }
    
    return nextAction;
}
