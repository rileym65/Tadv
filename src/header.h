#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_TRUE             101
#define ACTION_FALSE            100

#define CMD_CARRYING            30000
#define CMD_IN_ROOM             30001
#define CMD_NOT_IN_ROOM         30002
#define CMD_FLAG_SET            30003
#define CMD_SET_FLAG            30004
#define CMD_RESET_FLAG          30005
#define CMD_OBJECT_IN_ROOM      30006
#define CMD_OBJECT_NOT_IN_ROOM  30007
#define CMD_SAY                 30008
#define CMD_TRUE                30009
#define CMD_FALSE              30010
#define CMD_ELSE               30011
#define CMD_PLACE_OBJECT       30012
#define CMD_TAKE_OBJECT        30013
#define CMD_DROP_OBJECT        30014
#define CMD_FLAG_RESET         30015
#define CMD_NOT_CARRYING       30016
#define CMD_ADD_SCORE          30017
#define CMD_SUB_SCORE          30018
#define CMD_TELEPORT           30019
#define CMD_DIE                30020
#define CMD_WIN                30021
#define CMD_LOSE               30022
#define CMD_IF                 30023
#define CMD_ADD                30024
#define CMD_SUB                30025
#define CMD_MUL                30026
#define CMD_DIV                30027
#define CMD_DUP                30028
#define CMD_DROP               30029
#define CMD_SWAP               30030
#define CMD_SET                30031
#define CMD_GET                30032
#define CMD_EQ                 30033
#define CMD_NE                 30034
#define CMD_GT                 30035
#define CMD_LT                 30036
#define CMD_GE                 30037
#define CMD_LE                 30038
#define CMD_RANDOM             30039
#define CMD_DOT                30040
#define CMD_CR                 30041
#define CMD_NSAY               30042
#define CMD_ENTERED            30043
#define CMD_GOING_EAST         30044
#define CMD_GOING_WEST         30045
#define CMD_GOING_NORTH        30046
#define CMD_GOING_SOUTH        30047
#define CMD_GOING_UP           30048
#define CMD_GOING_DOWN         30049
#define CMD_CURRENT_ROOM       30050
#define CMD_REMOVE_ITEM        30051
#define CMD_THEN               30052
#define CMD_OVER               30053
#define CMD_ROT                30054
#define CMD_MROT               30055
#define CMD_AND                30056
#define CMD_OR                 30057
#define CMD_XOR                30058
#define CMD_PICK               30059
#define CMD_DO                 30060
#define CMD_I                  30061
#define CMD_LOOP               30062
#define CMD_ROOM_DESC          30063
#define CMD_SPACES             30064
#define CMD_LOCATION           30065
#define CMD_EXTRACT            30066
#define CMD_SCORE              30067
#define CMD_WEIGHT             30068
#define CMD_GET_EAST           30069
#define CMD_GET_WEST           30070
#define CMD_GET_NORTH          30071
#define CMD_GET_SOUTH          30072
#define CMD_GET_UP             30073
#define CMD_GET_DOWN           30074
#define CMD_EMIT               30075
#define CMD_NOT                30076
#define CMD_MORE               30077
#define CMD_LIGHT              30078
#define CMD_HAS_LIGHT          30079
#define CMD_ERROR              30080
#define CMD_OPEN               30081
#define CMD_CLOSE              30082
#define CMD_OPENED             30083
#define CMD_LOCK               30084
#define CMD_UNLOCK             30085
#define CMD_UNLOCKED           30086
#define CMD_TURNCOUNT          30087
#define CMD_EXAMINEITEM        30088
#define CMD_OPEN_DOOR          30089
#define CMD_CLOSE_DOOR         30090
#define CMD_LOCK_DOOR          30091
#define CMD_UNLOCK_DOOR        30092
#define CMD_DOOR_CLOSED        30093
#define CMD_DOOR_LOCKED        30094
#define CMD_INV_COUNT          30095
#define CMD_MOD                30096
#define CMD_INVITEM            30097
#define CMD_DESC_ITEM          30098
#define CMD_SPACE              30099
#define CMD_WEARABLE           30100
#define CMD_WEARING            30101
#define CMD_WHILE              30102
#define CMD_REPEAT             30103
#define CMD_COUNT              30104
#define CMD_CLEAR              30105
#define CMD_BEGIN              30106
#define CMD_UNTIL              30107
#define CMD_NDOT               30108
#define CMD_STACK              30109
#define CMD_ABS                30110
#define CMD_SGN                30111
#define CMD_INC                30112
#define CMD_DEC                30113
#define CMD_AUG                30114
#define CMD_DIM                30115
#define CMD_CHS                30116
#define CMD_MAX                30117
#define CMD_MIN                30118
#define CMD_NMAX               30119
#define CMD_NMIN               30120
#define CMD_NDROP              30121
#define CMD_SUM                30122
#define CMD_DROPUNTIL          30123
#define CMD_DUP2               30124
#define CMD_SWAP2              30125
#define CMD_QMARK              30126
#define CMD_ITEMCOUNT          30127
#define CMD_L_AND              30128
#define CMD_L_OR               30129
#define CMD_L_XOR              30130
#define CMD_L_NOT              30131
#define CMD_S_DOT              30132
#define CMD_S_QMARK            30133
#define CMD_S_LEN              30134
#define CMD_S_LEFT             30135
#define CMD_S_COPY             30136
#define CMD_S_PLUS             30137
#define CMD_S_RIGHT            30138
#define CMD_S_AT               30139
#define CMD_S_SET              30140
#define CMD_S_EQ               30141
#define CMD_S_NE               30142
#define CMD_S_GT               30143
#define CMD_S_LT               30144
#define CMD_S_GE               30145
#define CMD_S_LE               30146
#define CMD_S_CLEAR            30147
#define CMD_S_TRIM             30148
#define CMD_S_LC               30149
#define CMD_S_UC               30150
#define CMD_S_VAL              30151
#define CMD_S_STR              30152
#define CMD_BLESS              30153
#define CMD_CURSE              30154
#define CMD_CURSED             30155
#define CMD_ISCONTAINER        30156
#define CMD_CONTENTS           30157
#define CMD_PUT_INTO           30158
#define CMD_TAKE_FROM          30159
#define CMD_CONTAINS           30160
#define CMD_HEALTH             30161
#define CMD_HEALTH_PLUS        30162
#define CMD_HEALTH_MINUS       30163
#define CMD_HEALTH_EQ          30164
#define CMD_LINK_NORTH         30165
#define CMD_LINK_SOUTH         30166
#define CMD_LINK_EAST          30167
#define CMD_LINK_WEST          30168
#define CMD_LINK_NE            30169
#define CMD_LINK_NW            30170
#define CMD_LINK_SE            30171
#define CMD_LINK_SW            30172
#define CMD_LINK_UP            30173
#define CMD_LINK_DOWN          30174
#define CMD_AT_EQ              30175
#define CMD_AT_PLUSPLUS        30176
#define CMD_AT_MINUSMINUS      30177
#define CMD_AT_PLUS_EQ         30178
#define CMD_AT_MINUS_EQ        30179
#define CMD_AT_DOT             30180
#define CMD_LT_LT              30181
#define CMD_GT_GT              30182
#define CMD_TRON               30183
#define CMD_TROFF              30184
#define CMD_DUPQ               30185
#define CMD_NIP                30186
#define CMD_TUCK               30187
#define CMD_INVENTORY          30188
#define CMD_QT                 30189

#define V_LOOK                     0
#define V_NORTH                    1
#define V_N                        2
#define V_SOUTH                    3
#define V_S                        4
#define V_EAST                     5
#define V_E                        6
#define V_WEST                     7
#define V_W                        8
#define V_GO                       9
#define V_UP                      10
#define V_DOWN                    11
#define V_INVENT                  12
#define V_SCORE                   13
#define V_SAVE                    14
#define V_DIAGNOSE                15
#define V_QUIT                    16
#define V_GET                     17
#define V_TAKE                    18
#define V_PUT                     19
#define V_DROP                    20
#define V_ALL                     21
#define V_VOCAB                   22
#define V_EXAMINE                 23
#define V_LOAD                    24
#define V_NE                      25
#define V_NW                      26
#define V_SE                      27
#define V_SW                      28
#define V_WEIGHT                  29
#define V_OPEN                    30
#define V_CLOSE                   31
#define V_LOCK                    32
#define V_UNLOCK                  33
#define V_DOOR                    34
#define V_WITH                    35
#define V_EXITS                   36
#define V_WEAR                    37
#define V_REMOVE                  38
#define V_INTO                    39
#define V_IN                      40
#define V_FROM                    41
#define V_WEARING                 42

typedef struct {
  int*  phraseTokens;
  int   numPhraseTokens;
  int*  actionTokens;
  int   numActionTokens;
  } ACTION;

typedef struct _item_struct {
  int     number;
  char*   name;
  char*   identifier;
  char*   description;
  char*   examine;
  int     weight;
  int     location;
  int     score;
  ACTION** actions;
  int     numActions;
  int*    examSteps;
  int     numExamSteps;
  int*    descSteps;
  int     numDescSteps;
  int*    carryingSteps;
  int     numCarryingSteps;
  int*    turnSteps;
  int     numTurnSteps;
  int*    acquiredSteps;
  int     numAcquiredSteps;
  int*    lostSteps;
  int     numLostSteps;
  int*    wornSteps;
  int     numWornSteps;
  int*    wearingSteps;
  int     numWearingSteps;
  int*    removedSteps;
  int     numRemovedSteps;
  int     wearable;
  int     beingworn;
  int     startingItem;
  int     cursed;
  int     container;
  int     maxContents;
  int     contents[256];
  int     numContents;
  } ITEM;

typedef struct {
  char* name;
  char* shortDesc;
  char** description;
  int    numDesc;
  int   north[2];
  int   south[2];
  int   east[2];
  int   west[2];
  int   up[2];
  int   down[2];
  int   ne[2];
  int   nw[2];
  int   se[2];
  int   sw[2];
  int   visited;
  char  needLight;
  ITEM** items;
  int    numItems;
  int*   enterSteps;
  int    numEnterSteps;
  int*   leaveSteps;
  int    numLeaveSteps;
  ACTION** actions;
  int     numActions;
  int*    occupiedSteps;
  int     numOccupiedSteps;
  int*    turnSteps;
  int     numTurnSteps;
  int     numDescSteps;
  int*    descSteps;
  } ROOM;

typedef struct {
  char* name;
  int   opened;
  int   unlocked;
  int   lockable;
  int   key;
  char* description;
  int*  descSteps;
  int   numDescSteps;
  int*  onOpenSteps;
  int   numOnOpenSteps;
  int*  onCloseSteps;
  int   numOnCloseSteps;
  int*  onLockSteps;
  int   numOnLockSteps;
  int*  onUnlockSteps;
  int   numOnUnlockSteps;
  } DOOR;

typedef struct {
  char** message;
  int    numLines;
  } MESSAGE;

typedef struct {
  ITEM** items;
  int    numItems;
  int    location;
  int    lastLocation;
  int    score;
  int    light;
  long   turnCount;
  int    health;
  int    maxWeight;
  int    maxItems;
  } PLAYER;

typedef unsigned char byte;

typedef struct {
  byte s[256];
  byte k[256];
  int  i;
  int  j;
  } RC4_DATA;

LINK ACTION**  actions;
LINK int       debug;
LINK DOOR**    doors;
LINK int       doStack[1024];
LINK int       dsp;
LINK char      encrypted;
LINK char**    equates;
LINK int*      eqValues;
LINK char      flags[1024];
LINK char**    flagNames;
LINK ACTION**  functions;
LINK char      gameFlag;
LINK ITEM**    items;
LINK RC4_DATA  key;
LINK char      lastDir;
LINK MESSAGE** messages;
LINK int       numActions;
LINK int       numDoors;
LINK int       numEquates;
LINK int       numFlagNames;
LINK int       numFunctions;
LINK int       numItems; 
LINK int       numMessages;
LINK int       numRooms;
LINK int       numStartSteps;
LINK int       numSVars;
LINK int       numTokens;
LINK int       numTurnActions;
LINK int       numVarNames;
LINK int       numVocab;
LINK PLAYER    player;
LINK ROOM**    rooms;
LINK int       sp;
LINK int       stack[1024];
LINK char      startingRoom[1024];
LINK int*      startSteps;
LINK char**    sVarNames;
LINK char**    sVarValues;
LINK int       tokens[256];
LINK int       tracing;
LINK int       tron;
LINK ACTION**  turnActions;
LINK char**    varNames;
LINK int*      vars;
LINK char**    vocab;

extern int      actionBlock(int* actions,int count);
extern void     addEquate(char* name, int value);
extern void     addFlag(char* pBuffer);
extern void     addWord(char* wrd);
extern int      carrying(int item);
extern int      checkActions();
extern int      checkObjects();
extern int      checkRoomActions();
extern int      containerScore(int container);
extern int      containerWeight(int container);
extern void     decrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key);
extern int      doorsInRoom(int room,int* door);
extern int      dropItem(int itemNum);
extern void     encodeFile(char* fname);
extern void     encrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key);
extern void     extract(int item);
extern char*    fileRead(char* buffer,FILE* file);
extern int      getCode(char* wrd);
extern int      getItem(int itemNum);
extern int      getItemNumber(char* wrd);
extern int      getRoomNumber(char* wrd);
extern int      getToken(char* buffer);
extern int      getValue(char* wrd);
extern void     init();
extern int      load(char* filename);
extern void     mainLoop();
extern char*    nextWord(char* buffer);
extern int      numberForItem(ITEM* item);
extern int      performAction(int* actions,int count);
extern int      pop();
extern int      prePass(char* filename);
extern void     printToken(int token);
extern int      processLeave();
extern void     push(int n);
extern int      putIntoContainer(int container, int item);
extern int      putIntoInventory(int item);
extern void     putIntoRoom(int room, int item);
extern int      rcs_random(int size);
extern void     rcs_randomize();
extern void     read_dest(char* buffer,int* link);
extern void     readAction(FILE* inFile,char* buffer);
extern int*     readActionSteps(FILE* inFile,int* count, char* pBuf);
extern void     readAdventure(FILE* inFile);
extern void     readDoor(FILE* inFile,char* buf);
extern int      readFile(char* filename);
extern void     readFunction(FILE* inFile,char* buffer);
extern void     readItem(FILE* inFile,char* buf);
extern void     readMessage(FILE* inFile,char* buf);
extern void     readRoom(FILE* inFile,char* buf);
extern int      removeItem(int itemNum,int roomNumber);
extern void     reset();
extern void     rc4(byte* buffer,int len,RC4_DATA* key);
extern RC4_DATA rc4_init(byte* key,int keylen);
extern void     save();
extern int      score();
extern int      takeFromContainer(int container, int item);
extern int      takeFromInventory(int item);
extern int      takeFromRoom(int room, int item);
extern int      tokenize(char* buffer);
extern int      tokenizeAdd(char* buffer);
extern char*    trim(char* buffer);
extern char*    upper(char* buffer);
extern int      weight();

