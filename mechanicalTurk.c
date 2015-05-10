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
    
    if ((g->playerArray[getWhoseTurn(g) - 1].students[STUDENT_MJ] > 1) &&
        (g->playerArray[getWhoseTurn(g) - 1].students[STUDENT_MTV] > 1) &&
        (g->playerArray[getWhoseTurn(g) - 1].students[STUDENT_MMONEY] > 1)) {
        nextAction.actionCode = START_SPINOFF;
    } else {
        nextAction.actionCode = PASS;
    }
    
    return nextAction;
}
