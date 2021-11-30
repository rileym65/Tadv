#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

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

typedef struct {
  int*  phraseTokens;
  int   numPhraseTokens;
  int*  actionTokens;
  int   numActionTokens;
  } ACTION;

typedef struct _item_struct {
  char*   name;
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
  int     wearable;
  int     beingworn;
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
  } PLAYER;

typedef unsigned char byte;

typedef struct {
  byte s[256];
  byte k[256];
  int  i;
  int  j;
  } RC4_DATA;

LINK ACTION** turnActions;
LINK int     numTurnActions;
LINK ACTION** actions;
LINK int      numActions;
LINK ITEM** items;
LINK int    numItems; 
LINK ROOM** rooms;
LINK int   numRooms;
LINK MESSAGE** messages;
LINK int    numMessages;
LINK DOOR** doors;
LINK int    numDoors;
LINK PLAYER player;
LINK char** vocab;
LINK int    numVocab;
LINK int    tokens[256];
LINK int    numTokens;
LINK char   flags[1024];
LINK char** flagNames;
LINK int    numFlagNames;
LINK char   gameFlag;
LINK char** varNames;
LINK int    numVarNames;
LINK int*   vars;
LINK char   lastDir;
LINK int    debug;
LINK char** equates;
LINK int*   eqValues;
LINK int    numEquates;
LINK int*   startSteps;
LINK int    numStartSteps;
LINK char   encrypted;
LINK RC4_DATA key;
LINK ACTION** functions;
LINK int      numFunctions;
LINK int doStack[100];
LINK int dsp;
LINK int stack[100];
LINK int sp;


extern int   numberForItem(ITEM* item);
extern char* fileRead(char* buffer,FILE* file);
extern int   rcs_random(int size);
extern void  rcs_randomize();
extern char* trim(char* buffer);
extern char* nextWord(char* buffer);
extern int   tokenize(char* buffer);
extern int   tokenizeAdd(char* buffer);
extern int   getToken(char* buffer);
extern char* upper(char* buffer);
extern void  printToken(int token);

extern int  performAction(int* actions,int count);
extern int  checkRoomActions();
extern int  checkActions();
extern int  checkObjects();
extern int  getItem(int itemNum);
extern int  dropItem(int itemNum);

extern void init();
extern void reset();
extern int  readFile(char* filename);
extern int  getItemNumber(char* wrd);
extern void addWord(char* wrd);
extern int  load(char* filename);
extern void save();

extern RC4_DATA rc4_init(byte* key,int keylen);
extern void     rc4(byte* buffer,int len,RC4_DATA* key);
extern void encrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key);
extern void decrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key);

