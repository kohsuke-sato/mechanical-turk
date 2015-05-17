// mechanicalTurk.c
// Created by Albert Smith and Kohsuke Sato
// A file submission to "Mechanical Turk"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

action decideAction (Game g) {
    action nextAction;
    action testAction;
    
    // Mr Pass
    testAction.actionCode = START_SPINOFF;
    if (isLegalAction(g, testAction)) {
        nextAction.actionCode = START_SPINOFF;
    } else {
        nextAction.actionCode = PASS;
    }
    
    // Mr Campus
    testAction.actionCode = BUILD_CAMPUS;
    if (isLegalAction(g, testAction)) {
        nextAction.actionCode = BUILD_CAMPUS;
    }
    
    return nextAction;
}
