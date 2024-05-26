#define mapWidth 6400
#define mapHeight 3328
#define MapMagnification 2

#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#include "screens.h"
#include "gameHUD.h"
#include "loadGame.h"

// Check is other key is pressed except the specified key
bool OtherMoveKeyNotDown(int key) {
    if ((key != KEY_D && IsKeyDown(KEY_D)) ||
        (key != KEY_A && IsKeyDown(KEY_A)) ||
        (key != KEY_W && IsKeyDown(KEY_W)) ||
        (key != KEY_S && IsKeyDown(KEY_S))) {
        return false;
    }
    else {
        return true;
    }
}

// Check is Ogre object is overlap with the obstacle in the map
bool OgreMapCollision (Ogre *ogre) {
    // Set the collision box of the ogre
    Rectangle ogreCollisionRect = {ogre->position.x + abs(ogre->ActiveFrameRect.width / 2) - 5,
                                   ogre->position.y + abs(ogre->ActiveFrameRect.height / 2) + 20,
                                   20, 20};

    // hard-coded boundary box
    Rectangle Collision [270] = {
            // boundary
            {-100, 0, 100, 1664}, // left bound
            {3200, 0, 100, 1664}, // right bound
            {0, -100, 3200, 100}, // top bound
            {0, 1664, 3200, 100}, // bottom bound

            // fences
            {411, 1420, 398, 19},
            {380, 1293, 30, 20},
            {409, 1294, 449, 18},
            {892, 1295, 173, 18},
            {1247, 1295, 415, 18},
            {956, 1422, 705, 19},
            // logged trees
            // big
            {2056, 28, 30, 20},
            {2671, 125, 30, 20},
            {2861, 30, 30, 20},
            {2831, 766, 30, 20},
            {2701, 926, 30, 20},
            {3151, 1533, 30, 20},
            {3151, 1565, 30, 20},
            {3087, 1595, 30, 20},
            {2895, 1597, 30, 20},
            {2894, 1534, 30, 20},
            {2766, 1501, 30, 20},
            {2733, 1629, 30, 20},
            {1294, 1533, 30, 20},
            {1071, 1597, 30, 20},
            {750, 1597, 30, 20},
            {622, 1469, 30, 20},
            {14, 1085, 30, 20},
            {1713, 732, 30, 20},
            {1740, 1021, 30, 20},
            {1548, 603, 30, 20},
            {1390, 542, 30, 20},
            {396, 1053, 30, 20},
            {396, 892, 30, 20},
            {300, 957, 30, 20},
            {235, 1117, 30, 20},
            {302, 701, 30, 20},
            {271, 763, 30, 20},
            {367, 763, 30, 20},
            {1635, 1481, 25, 20},
            {1571, 1482, 25, 20},
            {1603,1610, 25, 20},
            {1347,1449, 25, 20},
            {1123,1451, 25, 20},
            {515,1451, 25, 20},
            {451,1515, 25, 20},
            {387,1482, 25, 20},
            {54,1578, 25, 20},
            {290,1609, 25, 20},
            {163,1354, 25, 20},
            {68,1419, 25, 20},
            {99,1322, 25, 20},
            {2,1321, 25, 20},
            {355,1579, 25, 20},
            {70,960, 20, 30},
            {6,897, 20, 30},
            {1531,1023, 20, 30},
            {1379,832, 20, 30},
            {1316,1089, 20, 30},
            {803,1120, 20, 30},
            {645,769, 20, 30},
            {261,993, 20, 30},
            {580,1257, 20, 30},
            {546,1162, 20, 30},
            {386,1226, 20, 30},
            {354,1129, 20, 30},

            // small
            {2471,41,18,16},
            {2664,41,18,16},
            {2825,72,18,16},
            {3079,73,18,16},
            {2856,424,18,16},
            {2856,424,18,16},
            {2632,551,18,16},
            {3048,553,18,16},
            {2600,713,18,16},
            {2519,776,18,16},
            {2919,776,18,16},
            {2646,999,18,16},
            {2599,1639,18,16},
            {2377,1576,18,16},
            {2216,1544,18,16},
            {1253,934,18,16},
            {1160,646,18,16},
            {1128,551,18,16},
            {1031,744,18,16},
            {1060,870,18,16},
            {841,712,18,16},
            {810,872,18,16},
            {2857,1192,13,16},
            {2889,1127,13,16},
            {2505,1158,13,16},
            {553,678,13,16},
            {712,648,13,16},
            {422,646,13,16},
            {2500,1552,10,10},
            {2372,1650,10,10},
            {2180,1586,10,10},
            {2117,1650,10,10},
            {1987,1553,10,10},
            {840,932,10,20},
            {875,998,10,20},
            {617,934,10,20},
            {331,900,10,20},

            // lying trunks
            {512, 1536, 28, 27},
            {1601, 1536, 28, 27},
            {1663, 1630, 28, 27},
            {1663, 1503, 28, 27},
            {1600, 1439, 28, 27},
            {1631, 1633, 28, 27},
            {1631, 992, 28, 27},
            {1824, 799, 28, 27},
            {1696, 577, 28, 27},
            {1536, 737, 28, 27},
            {479, 1585, 46, 15},
            {447, 1652, 46, 15},
            {1823, 1084, 25, 14},
            {1823, 1084, 25, 14},
            {1698, 852, 25, 14},
            {1317, 756, 25, 14},
            {1220, 692, 25, 14},

            {64,376,60,20},
            {260,442,60,20},
            {773,378,60,20},
            {965,282,60,20},
            {964,218,60,20},
            {1059,155,60,20},
            {1234,280,24,11},
            {2900,1050,24,11},

            // small trees
            {1460,428,20,15},
            {1557,521,20,15},
            {1392,716,20,15},
            {1780,717,20,15},
            {213,1630,20,20},
            {280,1535,20,20},
            {439,1438,20,20},
            {2487,481,20,20},
            {2646,834,20,20},
            {2456,930,20,20},
            {2615,1155,20,20},
            {2358,1155,20,20},
            {2231,1155,20,20},
            {1336,449,20,20},
            {1303,386,20,20},
            {1269,417,20,20},
            {1269,479,20,20},
            {1140,97,20,20},
            {851,192,20,20},
            {787,99,20,20},
            {787,99,20,20},
            {850,187,20,20},
            {852,320,20,20},
            {372,64,20,20},
            {277,161,20,20},
            {182,347,20,20},
            {117,161,20,20},
            {83,100,20,20},
            {51,1035,25,20},
            {52,354,20,15},
            {117,606,20,15},
            {309,582,20,15},

            // medium trees
            {45,940,25,20},
            {302,843,25,20},
            {430,943,25,20},
            {462,1006,25,20},
            {560,845,25,20},
            {665,718,25,20},
            {720,751,25,20},
            {686,911,25,20},
            {846,635,25,20},
            {944,911,25,20},
            {1168,912,25,20},
            {1198,814,25,20},
            {1167,911,25,20},
            {1326,941,25,20},
            {3090,1165,30,20},
            {2992,1230,30,20},
            {2992,1038,30,20},
            {2080,1102,30,20},
            {2703,1229,30,20},
            {2513,1003,30,20},
            {2990,907,30,20},
            {2829,909,30,20},
            {2482,819,30,20},
            {2704,685,30,20},
            {2989,686,30,20},
            {2546,652,30,20},
            {2803,620,30,20},
            {3119,559,30,20},
            {3085,462,30,20},
            {2924,494,30,20},
            {2765,494,30,20},
            {2611,457,30,20},
            {2574,524,30,20},
            {45,1035,30,20},
            {13,844,30,20},
            {12,620,30,20},
            {46,460,30,20},
            {111,303,30,20},
            {298,524,30,20},
            {235,940,30,20},
            {270,1067,30,20},
            {365,846,30,20},
            {363,973,30,20},
            {459,751,30,20},
            {523,908,30,20},
            {524,1100,30,20},
            {723,1100,30,20},
            {723,1100,30,20},
            {174,109,30,20},
            {368,143,30,20},
            {303,267,30,20},
            {432,78,30,20},
            {461,363,30,20},
            {431,588,30,20},
            {497,557,30,20},
            {561,619,30,20},
            {590,460,30,20},
            {654,589,30,20},
            {655,45,30,20},
            {719,236,30,20},
            {784,552,30,20},
            {876,141,30,20},
            {906,397,30,20},
            {878,490,30,20},
            {943,557,30,20},
            {974,77,30,20},
            {1038,493,30,20},
            {1070,371,30,20},
            {1042,495,30,20},
            {1106,303,30,20},
            {1138,493,30,20},
            {1168,338,30,20},
            {1200,429,30,20},
            {1265,205,30,20},
            {1263,112,30,20},
            {2799,1100,30,20},
            {908,1171,35,15},
            {906,1266,35,15},
            {1134,1044,35,15},
            {1292,1238,35,15},
            {1387,1109,35,15},
            {692,1006,35,15},
            {786,1039,35,15},
            {691,1006,35,15},
            {755,1198,35,15},
            {978,1037,35,15},
            {1233,1039,35,15},
            {1171,1198,35,15},
            {1391,1196,35,15},

            // big trees
            {18,1481,30,25},
            {17,1165,30,25},
            {117,1419,30,25},
            {243,1614,30,25},
            {338,1514,30,25},
            {1045,1484,30,25},
            {1233,1486,30,25},
            {1491,1485,30,25},
            {1556,1551,30,25},
            {1426,1646,30,25},
            {308,1166,30,25},
            {470,1261,30,25},
            {1682,1166,30,25},
            {1841,1005,30,25},
            {1840,750,30,25},
            {1586,686,30,25},
            {1649,463,30,25},
            {1230,1174,40,25}
    };

    // Multiply the every value in the multidimensional array by the magnification of map
    for (int i = 0; i < 270; i++) {
        Collision[i].x *= MapMagnification;
        Collision[i].y *= MapMagnification;
        Collision[i].width *= MapMagnification;
        Collision[i].height *= MapMagnification;
    }

    for (int i = 0; i < 270; i++) {
        if (CheckCollisionRecs(ogreCollisionRect, Collision[i])) {
            return true;
        }
    }
    return false;
}

bool GhostMapCollision (Ghost *ghost) {
    // Set the collision box of the ghost
    Rectangle ghostCollisionRect = {ghost->position.x + abs(ghost->frameRect.width / 2) - 7,
                                    ghost->position.y + abs(ghost->frameRect.height / 2) + 20,
                                    20, 20};

    // hard-coded boundary box
    Rectangle Collision [270] = {
            // boundary
            {-100, 0, 100, 1664}, // left bound
            {3200, 0, 100, 1664}, // right bound
            {0, -100, 3200, 100}, // top bound
            {0, 1664, 3200, 100}, // bottom bound

            // fences
            {411, 1420, 398, 19},
            {380, 1293, 30, 20},
            {409, 1294, 449, 18},
            {892, 1295, 173, 18},
            {1247, 1295, 415, 18},
            {956, 1422, 705, 19},
            // logged trees
            // big
            {2056, 28, 30, 20},
            {2671, 125, 30, 20},
            {2861, 30, 30, 20},
            {2831, 766, 30, 20},
            {2701, 926, 30, 20},
            {3151, 1533, 30, 20},
            {3151, 1565, 30, 20},
            {3087, 1595, 30, 20},
            {2895, 1597, 30, 20},
            {2894, 1534, 30, 20},
            {2766, 1501, 30, 20},
            {2733, 1629, 30, 20},
            {1294, 1533, 30, 20},
            {1071, 1597, 30, 20},
            {750, 1597, 30, 20},
            {622, 1469, 30, 20},
            {14, 1085, 30, 20},
            {1713, 732, 30, 20},
            {1740, 1021, 30, 20},
            {1548, 603, 30, 20},
            {1390, 542, 30, 20},
            {396, 1053, 30, 20},
            {396, 892, 30, 20},
            {300, 957, 30, 20},
            {235, 1117, 30, 20},
            {302, 701, 30, 20},
            {271, 763, 30, 20},
            {367, 763, 30, 20},
            {1635, 1481, 25, 20},
            {1571, 1482, 25, 20},
            {1603,1610, 25, 20},
            {1347,1449, 25, 20},
            {1123,1451, 25, 20},
            {515,1451, 25, 20},
            {451,1515, 25, 20},
            {387,1482, 25, 20},
            {54,1578, 25, 20},
            {290,1609, 25, 20},
            {163,1354, 25, 20},
            {68,1419, 25, 20},
            {99,1322, 25, 20},
            {2,1321, 25, 20},
            {355,1579, 25, 20},
            {70,960, 20, 30},
            {6,897, 20, 30},
            {1531,1023, 20, 30},
            {1379,832, 20, 30},
            {1316,1089, 20, 30},
            {803,1120, 20, 30},
            {645,769, 20, 30},
            {261,993, 20, 30},
            {580,1257, 20, 30},
            {546,1162, 20, 30},
            {386,1226, 20, 30},
            {354,1129, 20, 30},

            // small
            {2471,41,18,16},
            {2664,41,18,16},
            {2825,72,18,16},
            {3079,73,18,16},
            {2856,424,18,16},
            {2856,424,18,16},
            {2632,551,18,16},
            {3048,553,18,16},
            {2600,713,18,16},
            {2519,776,18,16},
            {2919,776,18,16},
            {2646,999,18,16},
            {2599,1639,18,16},
            {2377,1576,18,16},
            {2216,1544,18,16},
            {1253,934,18,16},
            {1160,646,18,16},
            {1128,551,18,16},
            {1031,744,18,16},
            {1060,870,18,16},
            {841,712,18,16},
            {810,872,18,16},
            {2857,1192,13,16},
            {2889,1127,13,16},
            {2505,1158,13,16},
            {553,678,13,16},
            {712,648,13,16},
            {422,646,13,16},
            {2500,1552,10,10},
            {2372,1650,10,10},
            {2180,1586,10,10},
            {2117,1650,10,10},
            {1987,1553,10,10},
            {840,932,10,20},
            {875,998,10,20},
            {617,934,10,20},
            {331,900,10,20},

            // lying trunks
            {512, 1536, 28, 27},
            {1601, 1536, 28, 27},
            {1663, 1630, 28, 27},
            {1663, 1503, 28, 27},
            {1600, 1439, 28, 27},
            {1631, 1633, 28, 27},
            {1631, 992, 28, 27},
            {1824, 799, 28, 27},
            {1696, 577, 28, 27},
            {1536, 737, 28, 27},
            {479, 1585, 46, 15},
            {447, 1652, 46, 15},
            {1823, 1084, 25, 14},
            {1823, 1084, 25, 14},
            {1698, 852, 25, 14},
            {1317, 756, 25, 14},
            {1220, 692, 25, 14},

            {64,376,60,20},
            {260,442,60,20},
            {773,378,60,20},
            {965,282,60,20},
            {964,218,60,20},
            {1059,155,60,20},
            {1234,280,24,11},
            {2900,1050,24,11},

            // small trees
            {1460,428,20,15},
            {1557,521,20,15},
            {1392,716,20,15},
            {1780,717,20,15},
            {213,1630,20,20},
            {280,1535,20,20},
            {439,1438,20,20},
            {2487,481,20,20},
            {2646,834,20,20},
            {2456,930,20,20},
            {2615,1155,20,20},
            {2358,1155,20,20},
            {2231,1155,20,20},
            {1336,449,20,20},
            {1303,386,20,20},
            {1269,417,20,20},
            {1269,479,20,20},
            {1140,97,20,20},
            {851,192,20,20},
            {787,99,20,20},
            {787,99,20,20},
            {850,187,20,20},
            {852,320,20,20},
            {372,64,20,20},
            {277,161,20,20},
            {182,347,20,20},
            {117,161,20,20},
            {83,100,20,20},
            {51,1035,25,20},
            {52,354,20,15},
            {117,606,20,15},
            {309,582,20,15},

            // medium trees
            {45,940,25,20},
            {302,843,25,20},
            {430,943,25,20},
            {462,1006,25,20},
            {560,845,25,20},
            {665,718,25,20},
            {720,751,25,20},
            {686,911,25,20},
            {846,635,25,20},
            {944,911,25,20},
            {1168,912,25,20},
            {1198,814,25,20},
            {1167,911,25,20},
            {1326,941,25,20},
            {3090,1165,30,20},
            {2992,1230,30,20},
            {2992,1038,30,20},
            {2080,1102,30,20},
            {2703,1229,30,20},
            {2513,1003,30,20},
            {2990,907,30,20},
            {2829,909,30,20},
            {2482,819,30,20},
            {2704,685,30,20},
            {2989,686,30,20},
            {2546,652,30,20},
            {2803,620,30,20},
            {3119,559,30,20},
            {3085,462,30,20},
            {2924,494,30,20},
            {2765,494,30,20},
            {2611,457,30,20},
            {2574,524,30,20},
            {45,1035,30,20},
            {13,844,30,20},
            {12,620,30,20},
            {46,460,30,20},
            {111,303,30,20},
            {298,524,30,20},
            {235,940,30,20},
            {270,1067,30,20},
            {365,846,30,20},
            {363,973,30,20},
            {459,751,30,20},
            {523,908,30,20},
            {524,1100,30,20},
            {723,1100,30,20},
            {723,1100,30,20},
            {174,109,30,20},
            {368,143,30,20},
            {303,267,30,20},
            {432,78,30,20},
            {461,363,30,20},
            {431,588,30,20},
            {497,557,30,20},
            {561,619,30,20},
            {590,460,30,20},
            {654,589,30,20},
            {655,45,30,20},
            {719,236,30,20},
            {784,552,30,20},
            {876,141,30,20},
            {906,397,30,20},
            {878,490,30,20},
            {943,557,30,20},
            {974,77,30,20},
            {1038,493,30,20},
            {1070,371,30,20},
            {1042,495,30,20},
            {1106,303,30,20},
            {1138,493,30,20},
            {1168,338,30,20},
            {1200,429,30,20},
            {1265,205,30,20},
            {1263,112,30,20},
            {2799,1100,30,20},
            {908,1171,35,15},
            {906,1266,35,15},
            {1134,1044,35,15},
            {1292,1238,35,15},
            {1387,1109,35,15},
            {692,1006,35,15},
            {786,1039,35,15},
            {691,1006,35,15},
            {755,1198,35,15},
            {978,1037,35,15},
            {1233,1039,35,15},
            {1171,1198,35,15},
            {1391,1196,35,15},

            // big trees
            {18,1481,30,25},
            {17,1165,30,25},
            {117,1419,30,25},
            {243,1614,30,25},
            {338,1514,30,25},
            {1045,1484,30,25},
            {1233,1486,30,25},
            {1491,1485,30,25},
            {1556,1551,30,25},
            {1426,1646,30,25},
            {308,1166,30,25},
            {470,1261,30,25},
            {1682,1166,30,25},
            {1841,1005,30,25},
            {1840,750,30,25},
            {1586,686,30,25},
            {1649,463,30,25},
            {1230,1174,40,25}
    };

    // Multiply the every value in the multidimensional array by the magnification of map
    for (int i = 0; i < 270; i++) {
        Collision[i].x *= MapMagnification;
        Collision[i].y *= MapMagnification;
        Collision[i].width *= MapMagnification;
        Collision[i].height *= MapMagnification;
    }

    for (int i = 0; i < 270; i++) {
        if (CheckCollisionRecs(ghostCollisionRect, Collision[i])) {
            return true;
        }
    }

    return false;
}

// Initialize the state of the ogre
void InitOgreState (Ogre *ogre) {
    ogre->state->level = 1;
    ogre->state->maxExp = 1000 + 200 * ogre->state->level;
    ogre->state->currentExp = 0;
    ogre->state->armor = 10 + 0.2 * ogre->state->level;
    ogre->state->maxHealth = 700 + 60 * ogre->state->level;
    ogre->state->healthRegen = 10 + 4 * ogre->state->level;
    ogre->state->health = ogre->state->maxHealth;
    ogre->state->atk = 200 + 50 * ogre->state->level;
}

// Initialize the state of the ogre
void InitGhostState (Ghost *ghost) {
    ghost->state->level = 2;
    ghost->state->expDrop = 300 + 300 * ghost->state->level;
    ghost->state->maxHealth = 300 + 300 * ghost->state->level;
    ghost->state->health = ghost->state->maxHealth;
    ghost->state->healthRegen = 5 + 2 * ghost->state->level;
    ghost->state->armor = 10 + 0.5 * ghost->state->level;
    ghost->state->atk = 120 + 50 * ghost->state->level;
}

// Initialize the ogre object except its states
void InitOgre (Ogre *ogre) {

    Texture2D Texture_move = LoadTexture("resources/ogre_moving.png");
    Texture2D Texture_attack = LoadTexture("resources/ogre_attacking.png");

    Sound ogreHurt = LoadSound("resources/ogreHurt.mp3");
    Sound ogreDead = LoadSound("resources/ogreDead.mp3");
    Sound ogreAtk1 = LoadSound("resources/ogreAtk1.mp3");
    Sound ogreAtk2 = LoadSound("resources/ogreAtk2.mp3");

    SetSoundVolume(ogreHurt, .5f);
    SetSoundVolume(ogreDead, .9f);
    SetSoundVolume(ogreAtk1, .5f);
    SetSoundVolume(ogreAtk2, .5f);

    ogre->IsAlive = true;
    ogre->respawnCD = 360;
    ogre->respawnCounter = 360;
    ogre->numFrames_move = 18;
    ogre->numFrames_attack = 12;
    ogre->speed = 1.5f;

    ogre->ogreDead = ogreDead;
    ogre->ogreAtk1 = ogreAtk1;
    ogre->ogreAtk2 = ogreAtk2;

    ogre->Texture_move = Texture_move;
    ogre->Texture_attack = Texture_attack;
    ogre->ActiveTexture = Texture_move;
    ogre->frameWidth_move = ogre->Texture_move.width / ogre->numFrames_move;
    ogre->frameWidth_attack = ogre->Texture_attack.width / ogre->numFrames_attack;

    ogre->position = (Vector2) {100, mapHeight - 250}; // fixed new game spawn position

    ogre->velocity = (Vector2){0.0f, 0.0f};

    ogre->frameRect_move = (Rectangle){0.0f, 0.0f, (float) ogre->frameWidth_move, (float) ogre-> Texture_move.height};
    ogre->frameRect_attack = (Rectangle) {0.0f, 0.0f, (float) ogre->frameWidth_attack, (float) ogre-> Texture_attack.height};
    ogre->ActiveFrameRect = ogre->frameRect_move;
    ogre->playAttackAnimation = false;
    ogre->maxAttackCD = 60;
    ogre->attackCD = 0;

    ogre->state = (playerState *) malloc(sizeof(playerState));
    InitOgreState(ogre);
}

// Initialize the ghost object except its states
void InitGhost (Ghost *ghost) {
    Texture Texture_idle = LoadTexture("resources/ghost_idle.png");
    Texture Texture_move = LoadTexture("resources/ghost_moving.png");
    Texture Texture_attack = LoadTexture("resources/ghost_attacking.png");

    Sound ghostSound1 = LoadSound("resources/ghostSound1.mp3");
    Sound ghostSound2 = LoadSound("resources/ghostSound2.mp3");
    Sound ghostDying = LoadSound("resources/ghostDying.mp3");
    Sound ghostAtk1 = LoadSound("resources/ghostAtk1.mp3");
    Sound ghostAtk2 = LoadSound("resources/ghostAtk2.mp3");

    SetSoundVolume(ghostSound1, .5f);
    SetSoundVolume(ghostSound2, .5f);
    SetSoundVolume(ghostDying, .5f);
    SetSoundVolume(ghostAtk1, .5f);
    SetSoundVolume(ghostAtk2, .5f);

    ghost->ghostSound1 = ghostSound1;
    ghost->ghostSound2 = ghostSound2;
    ghost->ghostDying = ghostDying;
    ghost->ghostAtk1 = ghostAtk1;
    ghost->ghostAtk2 = ghostAtk2;

    ghost->IsAlive = true;
    ghost->respawnCD = 720;
    ghost->respawnCounter = 720;

    ghost->numFrames = 12;
    ghost->speed = 1.0f;
    ghost->Texture_idle = Texture_idle;
    ghost->Texture_move = Texture_move;
    ghost->Texture_attack = Texture_attack;
    ghost->ActiveTexture = Texture_idle;
    ghost->frameWidth = ghost->ActiveTexture.width / ghost->numFrames;
    ghost->position = (Vector2) {rand() % (mapWidth - 200) + 200, rand() % (mapHeight - 200) + 200};
    ghost->velocity = (Vector2) {0.0f, 0.0f};
    ghost->frameRect = (Rectangle) {0.0f, 0.0f, (float) ghost->frameWidth, (float) ghost->ActiveTexture.height};
    ghost->playAttackAnimation = false;
    ghost->maxAttackCD = 60;
    ghost->attackCD = 0;

    ghost->state = (enemyState *) malloc(sizeof(enemyState));
    InitGhostState(ghost);
}

// Handle the input of the ogre, and animation of ogre moving
void InputHandling_Move(Ogre *ogre) {
    static unsigned frameDelayCounter = 0;
    unsigned frameDelay = 5;

    // Store the initial position before each frame of moving
    float originalPositionX = ogre->position.x;
    float originalPositionY = ogre->position.y;

    if (IsKeyDown(KEY_D) && OtherMoveKeyNotDown(KEY_D)) {
        ogre->velocity.x = ogre->speed;
        // Turn face around to right
        if (ogre->frameRect_move.width < 0) {
            ogre->frameRect_move.width = -ogre->frameRect_move.width;
        }
    }
    else if (IsKeyDown(KEY_A) && OtherMoveKeyNotDown(KEY_A)) {
        ogre->velocity.x = -ogre->speed;
        // Turn face around to left
        if (ogre->frameRect_move.width > 0) {
            ogre->frameRect_move.width = -ogre->frameRect_move.width;
        }
    }
    else if (IsKeyDown(KEY_W) && OtherMoveKeyNotDown(KEY_W)) {
        ogre->velocity.y = -ogre->speed;
    }
    else if (IsKeyDown(KEY_S) && OtherMoveKeyNotDown(KEY_S)) {
        ogre->velocity.y = ogre->speed;
    }
    else {
        ogre->velocity.x = 0;
        ogre->velocity.y = 0;
    }

    bool IsOgreMoving = ogre->velocity.x != 0.0f || ogre->velocity.y != 0.0f;

    ogre->position = Vector2Add(ogre->position, ogre->velocity);

    // Stop and Limit the movement of ogre when it hit obstacle or world boundary
    if (OgreMapCollision(ogre)) {
        ogre->position.x = originalPositionX;
        ogre->position.y = originalPositionY;
        ogre->velocity.x = 0;
        ogre->velocity.y = 0;
    }

    if (IsOgreMoving) {
        ++frameDelayCounter;
        // Change the active Texture to Texture of moving
        ogre->ActiveTexture = ogre->Texture_move;
        ogre->ActiveFrameRect = ogre->frameRect_move;
        // Play moving animation
        if (frameDelayCounter > frameDelay) {
            frameDelayCounter = 0;
            ogre->frameRect_move.x += ogre->frameRect_move.width;
            if (ogre->frameRect_move.x >= ogre->Texture_move.width) {
                ogre->frameRect_move.x = 0;
            }
        }
    }
}

// Damage dealing logic of ogre attack
void OgreDealDamage (Ogre *ogre, Ghost *ghost, unsigned ghost_num) {
    const float attackRange = 120;
    for (int i = 0; i < ghost_num; i++) {
        if (Vector2Distance(ogre->position, ghost[i].position) <= attackRange) {
            if (ghost[i].IsAlive) {
                PlaySound(ogre->ogreAtk2);
                // Deal damage to the ghost within attack range
                float damageDealt = ogre->state->atk * (ghost[i].state->armor) / 70;
                ghost[i].state->health -= damageDealt;

                if (ghost[i].state->health <= 0) {
                    PlaySound(ghost->ghostDying);
                    // reset the health of ghost to 0, only matters when the health dropped below 0
                    ghost[i].state->health = 0;
                    ogre->state->currentExp += ghost[i].state->expDrop; // ogre gain Exp
                    ghost[i].IsAlive = false;
                }
            }
        }
        else {
            PlaySound(ogre->ogreAtk1);
        }
    }
}

// Handle the input of ogre attack and animation of ogre attacking
void InputHandling_Attack (Ogre *ogre, Ghost *ghost, unsigned ghost_num) {
    static unsigned frameIndex = 0;
    static unsigned frameDelayCounter = 0;
    unsigned frameDelay = 20;

    if(IsKeyPressed(KEY_J) && !ogre->playAttackAnimation && ogre->attackCD <= 0) {
        frameIndex = 0; // reset the animation
        ogre->playAttackAnimation = true;
    }

    if (ogre->playAttackAnimation) {
        frameDelayCounter ++; // wait for 20 frames
        if (frameDelayCounter >= frameDelay) {
            frameDelayCounter = 0;
            frameIndex++;
            ogre->ActiveTexture = ogre->Texture_attack;
            ogre->ActiveFrameRect = ogre->frameRect_attack;
            ogre->frameRect_attack.width = ogre->frameRect_move.width;
            ogre->attackCD = ogre->maxAttackCD;

            // After one complete animation played
            if (frameIndex >= ogre->numFrames_attack) {
                // Stop animation and compute the damage dealing logic
                ogre->playAttackAnimation = false;
                frameIndex = 0;
                OgreDealDamage(ogre, ghost, ghost_num);
            }

            // Play attack animation
            ogre->frameRect_attack.x = (float) ogre->frameWidth_attack * frameIndex;
        }
    }

    if (ogre->attackCD > 0) {
        ogre->ActiveTexture = ogre->Texture_attack;
        ogre->ActiveFrameRect = ogre->frameRect_attack;
        ogre->attackCD --;
    }
}

// Update the ogre state when leveling
void UpdateOgreState (Ogre *ogre) {
    ogre->state->maxExp = 1000 + 200 * ogre->state->level;
    ogre->state->armor = 10 + 0.2 * ogre->state->level;
    ogre->state->maxHealth = 700 + 60 * ogre->state->level;
    ogre->state->healthRegen = 10 + 4 * ogre->state->level;
    ogre->state->atk = 200 + 50 * ogre->state->level;
}

// Handler of ogre behavior in the game
void OgreBehavior (Ogre *ogre, Ghost *ghost, unsigned ghost_num) {
    // Leveling logic
    if (ogre->state->currentExp >= ogre->state->maxExp) {
        ogre->state->level ++;
        UpdateOgreState(ogre);

        if (ogre->state->currentExp > ogre->state->maxExp) {
            ogre->state->currentExp -= ogre->state->maxExp;
        }
    }

    // Check is ogre died
    if (ogre->state->health <= 0) {
        ogre->IsAlive = false;
    }

    // Input logic
    if (ogre->IsAlive) {
        InputHandling_Move(ogre);
        for (int i = 0; i < ghost_num; i++) {
            InputHandling_Attack(ogre, ghost, ghost_num);
        }
    }

    // Respawn Logic
    if (!ogre->IsAlive) {
        if (ogre->respawnCounter > 0) {
            ogre->respawnCounter--;
        }
        else {
            ogre->IsAlive = true;
            ogre->state->health = ogre->state->maxHealth;
            ogre->respawnCounter = ogre->respawnCD;
        }
    }
    else {
        // Ogre Health regen logic if not die
        static unsigned frameDelayCounter = 0;
        unsigned frameDelay = 60;
        if (frameDelayCounter >= frameDelay) {
            frameDelayCounter = 0;
            if (ogre->state->health < ogre->state->maxHealth) {
                ogre->state->health += ogre->state->healthRegen;
                if (ogre->state->health > ogre->state->maxHealth) {
                    ogre->state->health = ogre->state->maxHealth;
                }
            }
        } else {
            frameDelayCounter++;
        }
    }
}

// Set ghost to idle mode
void EnemyIdle(Ghost *ghost) {
    static unsigned frameDelayCounter = 0;
    unsigned frameDelay = 10;

    ++frameDelayCounter;
    ghost->ActiveTexture = ghost->Texture_idle;
    if (frameDelayCounter > frameDelay) {
        frameDelayCounter = 0;
        // Play idle animation
        ghost->frameRect.x += ghost->frameRect.width;
        if (ghost->frameRect.x >= ghost->ActiveTexture.width) {
            ghost->frameRect.x = 0;
        }
    }
}

// Set ghost to randomly patrolling
void EnemyPatrol(Ghost *ghost) {
    static unsigned frameDelayCounter = 0;
    unsigned frameDelay = 5;
    const int patrolCD = 360;
    int patrolDuration = 360;
    static int patrolCounter = 0;
    static int moveCounter = 0;
    static unsigned randMovement;

    patrolCounter++;

    if (patrolCounter >= patrolCD) {
        if (moveCounter < patrolDuration) {

            float originalPositionX = ghost->position.x;
            float originalPositionY = ghost->position.y;

            if (moveCounter == 0) {
                randMovement = GetRandomValue(0, 4);

                if (randMovement == 0) { // not move
                    ghost->velocity.x = 0;
                    ghost->velocity.y = 0;
                }
                else if (randMovement == 1 && ghost->position.x >= 0) { // left
                    ghost->velocity.x = -ghost->speed;
                    if (ghost->frameRect.width > 0) {
                        ghost->frameRect.width = -ghost->frameRect.width;
                    }
                }
                else if (randMovement == 2 && (ghost->position.x + ghost->frameRect.width) <= mapWidth) { // right
                    ghost->velocity.x = ghost->speed;
                    if (ghost->frameRect.width < 0) {
                        ghost->frameRect.width = -ghost->frameRect.width;
                    }
                }
                else if (randMovement == 3) { // top
                    ghost->velocity.y = -ghost->speed;
                }
                else if (randMovement == 4 && (ghost->position.y + ghost->frameRect.height) <= mapHeight) { // down
                    ghost->velocity.y = ghost->speed;
                }
            }
            moveCounter++;

            ghost->position = Vector2Add(ghost->position, ghost->velocity);

            if (GhostMapCollision(ghost)) {
                ghost->position.x = originalPositionX;
                ghost->position.y = originalPositionY;
                ghost->velocity.x = 0;
                ghost->velocity.y = 0;
            }
        }
        else {
            patrolCounter = 0;
            moveCounter = 0;
        }
    }

    bool IsGhostMoving = ghost->velocity.x != 0.0f || ghost->velocity.y != 0.0f;

    // Play moving animation when ghost is moving
    if (IsGhostMoving) {
        ++frameDelayCounter;
        ghost->ActiveTexture = ghost->Texture_move;
        if (frameDelayCounter > frameDelay) {
            frameDelayCounter = 0;
            ghost->frameRect.x += ghost->frameRect.width;
            if (ghost->frameRect.x >= ghost->Texture_move.width) {
                ghost->frameRect.x = 0;
            }
        }
    }
    else {
        ghost->ActiveTexture = ghost->Texture_idle;
    }
}

// Handle ghost damage dealing logic
void EnemyDealDamage (Ghost *ghost, Ogre *ogre) {
    const float attackRange = 100;

    if (Vector2Distance(ghost->position, ogre->position) <= attackRange) {
        if (ogre->IsAlive) {
            // Deal damage to ogre if within attack range
            float damageDealt = ghost->state->atk * (ogre->state->armor / 50);
            ogre->state->health -= damageDealt;

            if (ghost->state->level <= 20) {
                PlaySound(ghost->ghostAtk1);
            }
            else {
                PlaySound(ghost->ghostAtk2);
            }
            if (ogre->state->health < 0) {
                PlaySound(ogre->ogreDead);
                ogre->state->health = 0; // set the health to 0 if ogre die, only matters when health goes below 0
            }
        }
    }
}

// Handle ghost chasing and attacking logic
void EnemyChaseAttack(Ghost *ghost, Ogre *ogre) {
    static unsigned frameIndex = 0;
    static unsigned frameDelayCounter = 0;
    unsigned frameDelay = 3;

    const float aggroRad = 300;
    const float attackRange = 100;

    // Simple straight line find path
    // Normalize the vector to make the magnitude to 1, but the direction remain
    Vector2 chaseVector = Vector2Normalize(Vector2Subtract(ogre->position, ghost->position));

    if (Vector2Distance(ghost->position, ogre->position) <= aggroRad) {
        // Randomly play different sound when ogre is nearby without aggro range
        if (GetRandomValue(1, 2) == 1) {
            PlaySound(ghost->ghostSound1);
        }
        else {
            PlaySound(ghost->ghostSound2);
        }

        ghost->velocity = chaseVector;

        ghost->ActiveTexture = ghost->Texture_move;

        // Turn direction accordingly
        if (chaseVector.x < 0) {
            ghost->frameRect.width = (float) -abs((int) ghost->frameRect.width);
        } else if (chaseVector.x > 0) {
            ghost->frameRect.width = (float) abs((int) ghost->frameRect.width);
        }

        // Record initial position before moving
        float originalPositionX = ghost->position.x;
        float originalPositionY = ghost->position.y;

        // Move slightly closer than the attack range
        if (Vector2Distance(ghost->position, ogre->position) >= attackRange - 20) {
            ghost->position = Vector2Add(ghost->position, ghost->velocity);

            // Backtrack and stop moving if collide
            if (GhostMapCollision(ghost)) {
                ghost->position.x = originalPositionX;
                ghost->position.y = originalPositionY;
                ghost->velocity.x = 0;
                ghost->velocity.y = 0;
            }
        }
    }

    // Perform attack if ogre within attack range
    if (Vector2Distance(ghost->position, ogre->position) <= attackRange) {
        if (ghost->attackCD == 0) {
            ghost->playAttackAnimation = true;
            ghost->attackCD = ghost->maxAttackCD;
        }
    }

    if (ghost->playAttackAnimation) {
        frameDelayCounter++;
        if (frameDelayCounter >= frameDelay) {
            frameDelayCounter = 0;
            frameIndex++;
            ghost->ActiveTexture = ghost->Texture_attack;

            // End animation after one complete animation
            if (frameIndex >= ghost->numFrames) {
                ghost->playAttackAnimation = false;
                frameIndex = 0;
                EnemyDealDamage(ghost, ogre);
            }

            // Play animation
            ghost->frameRect.x = (float) ghost->frameWidth * frameIndex;
        }
    }

    if (ghost->attackCD > 0) {
        ghost->ActiveTexture = ghost->Texture_attack;
        ghost->attackCD--;
    }
}

// Update ghost state after respawning
void UpdateGhostState (Ghost *ghost) {
    ghost->state->level += GetRandomValue(2, 7); // add level randomly
    ghost->state->expDrop = 300 + 300 * ghost->state->level;
    ghost->state->maxHealth = 300 + 300 * ghost->state->level;
    ghost->state->health = ghost->state->maxHealth;
    ghost->state->healthRegen = 5 + 2 * ghost->state->level;
    ghost->state->armor = 10 + 1.5 * ghost->state->level;
    ghost->state->atk = 120 + 50 * ghost->state->level;
}

// Handler of ghost behavior in the game
void EnemyBehavior(Ghost *ghost, Ogre *ogre) {
    bool IsPlayerNearby = false;
    const float alertRad = 330;

    // Check is player nearby
    if (Vector2Distance(ghost->position, ogre->position) <= alertRad) {
        IsPlayerNearby = true;
    } else {
        IsPlayerNearby = false;
    }

    // Attack logic
    if (IsPlayerNearby && ghost->IsAlive && ogre->IsAlive) {
        EnemyChaseAttack(ghost, ogre);
    }

    // Patrol logic
    if (!(IsPlayerNearby && ogre->IsAlive) && ghost->IsAlive) {
        EnemyIdle(ghost);
        EnemyPatrol(ghost);
    }

    // Respawn logic
    if (!ghost->IsAlive) {
        if (ghost->respawnCounter > 0) {
            ghost->respawnCounter--;
        }
        else if (ghost->respawnCounter == 0) {
            ghost->IsAlive = true;
            UpdateGhostState(ghost);
            ghost->respawnCounter = ghost->respawnCD;
        }
    }
    else {
        // Ghost health regen logic
        static unsigned frameDelayCounter = 0;
        unsigned frameDelay = 60;
        if (frameDelayCounter >= frameDelay) {
            frameDelayCounter = 0;
            if (ghost->state->health < ghost->state->maxHealth) {
                ghost->state->health += ghost->state->healthRegen;
                if (ghost->state->health > ghost->state->maxHealth) {
                    ghost->state->health = ghost->state->maxHealth;
                }
            }
        } else {
            frameDelayCounter++;
        }
    }
}

// Draw respawn screen if ogre is dead
void DrawRespawnScreen (Ogre *ogre) {
    DimScreen(0.8f);
    DrawCenteredText(GetScreenHeight() / 2, "Respawning", 200, RED);
    DrawCenteredText(GetScreenHeight() / 2 + 200, TextFormat("%i s", (int) ogre->respawnCounter / 60), 180, WHITE);
}

// Initialize game resources
void InitGameResources(Ogre **ogre, Ghost **ghosts, unsigned ghost_num, Texture2D *map) {
    *ogre = (Ogre *)malloc(sizeof(Ogre));
    *ghosts = (Ghost *)malloc(ghost_num * sizeof(Ghost));

    *map = LoadTexture("resources/map.png");

    InitOgre(*ogre);

    // Create a number of ghost objects based on ghost_num specified
    if (*ghosts != NULL) {
        for (int i = 0; i < ghost_num; i++) {
            InitGhost(&(*ghosts)[i]);
        }
    }
}

// Update game status based on the saved game
void UpdateLoadedGame (Ogre *ogre, Ghost *ghosts, unsigned ghost_num, SavedGame *game) {
    unsigned savedLevel = atoi(game->level);
    float savedPositionX = strtof(game->positionX, NULL);
    float savedPositionY = strtof(game->positionY, NULL);

    ogre->state->level = savedLevel;
    ogre->position.x = savedPositionX;
    ogre->position.y = savedPositionY;

    for (int i = 0; i < ghost_num; i++) {
        ghosts[i].state->level = ogre->state->level + GetRandomValue(-5, 7);
        UpdateGhostState(&ghosts[i]);
        ghosts[i].state->health = ghosts[i].state->maxHealth;
    }

    UpdateOgreState(ogre);
    ogre->state->health = ogre->state->maxHealth;
}

void RenderGame(Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map, SavedGame *game) {
    // Initialize camera object with NULL
    Camera2D camera = {0};

    static bool loaded = false;

    // Update game status when the game is loaded from saved game
    if (!loaded && game != NULL) {
        UpdateLoadedGame(ogre, ghosts, ghost_num, game);
        loaded = true;
    }

    // Configure the camera
    camera.zoom = 1.5f;
    camera.target = (Vector2) {ogre->position.x + 20, ogre->position.y + 30}; // focus on the ogre
    camera.offset = (Vector2) {GetScreenWidth() / 2, GetScreenHeight() / 2}; // place ogre at the centre of the screen

    float minDistance = 600; // minimum distance of displaying ghost information

    // Find nearest ghost
    int nearestGhostIndex = -1;
    for (int i = 0; i < ghost_num; i++) {
        if (ghosts[i].IsAlive) {
            float distance = Vector2Distance(ogre->position, ghosts[i].position);
            if (distance < minDistance) {
                minDistance = distance;
                nearestGhostIndex = i;
            }
        }
    }

    OgreBehavior(ogre, ghosts, ghost_num);

    for (int i = 0; i < ghost_num; i++) {
        EnemyBehavior(&ghosts[i], ogre);
    }

    BeginMode2D(camera);

        DrawTextureEx(map, (Vector2) {0, 0}, 0, MapMagnification,WHITE);

    for (int i = 0; i < ghost_num; i++) {
        if (ghosts[i].IsAlive) {
            DrawTextureRec(ghosts[i].ActiveTexture, ghosts[i].frameRect, ghosts[i].position, WHITE);
        }
    }

    if (ogre->IsAlive) {
        DrawTextureRec(ogre->ActiveTexture, ogre->ActiveFrameRect, ogre->position, WHITE);
    }

    EndMode2D();

    if (!ogre->IsAlive) {
        DrawRespawnScreen(ogre);
    }

    DrawHUD(ogre, ghosts, nearestGhostIndex);
}

// Clean up game resources
void CleanUpGameResources(Ogre *ogre, Ghost *ghosts) {
    free(ogre);
    free(ghosts);
}