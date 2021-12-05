#include "header.h"

int processLeave() {
  int ret;
  if (rooms[player.location]->numLeaveSteps > 0) {
    ret = performAction(rooms[player.location]->leaveSteps,
                  rooms[player.location]->numLeaveSteps);
    return ret;
    }
  return ACTION_FALSE;
  }

