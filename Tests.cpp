#include "Tests.h"
#include "Players.h"
#include "Tournament.h" // for createPlayer()

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

struct MoveTest {
  Move opponentMove = NoMove;
  Move xResponse = NoMove;
};

/*****************************************************************************/

int TestPlayer(Strategy strategy, string xName, Move xOpen, MoveTest moveTests[], int testCount) {
  Player *player = Tournament::createPlayer(strategy);
  assert(player->strategy() == strategy);
  assert(player->name() == xName);
  assert(player->move() == xOpen);
  for (int m=0; m<testCount; m++) {
    player->setOpponentMove(moveTests[m].opponentMove);
    assert(player->move() == moveTests[m].xResponse);
  }

  const int aScore = 4;
  player->incrementScore(aScore);
  assert(player->score() == aScore);

  cout << xName << " tests passed." << endl;
  delete player;
  return testCount + 3;
}
/*****************************************************************************/

int TestCooperator() {
  MoveTest cooperatorTests[] = {
    { CooperateMove, CooperateMove },
    { CheatMove, CooperateMove }
  };
  int testCount = sizeof(cooperatorTests)/sizeof(*cooperatorTests);
  return TestPlayer(
    CooperatorStrategy,
    "Cooperator",
    CooperateMove,
    cooperatorTests,
    testCount
  );
}

int TestCheater() {
  MoveTest cheaterTests[] = {
    { CooperateMove, CheatMove },
    { CheatMove, CheatMove }
  };
  int testCount = sizeof(cheaterTests)/sizeof(*cheaterTests);
  return TestPlayer(
    CheaterStrategy,
    "Cheater",
    CheatMove,
    cheaterTests,
    testCount
  );
}

int TestGrudger() {
  MoveTest grudgerTests[] = {
    { CooperateMove, CooperateMove },
    { CheatMove, CheatMove },
    { CooperateMove, CheatMove },
    { CooperateMove, CheatMove }
  };
  int testCount = sizeof(grudgerTests)/sizeof(*grudgerTests);
  return TestPlayer(
    GrudgerStrategy,
    "Grudger",
    CooperateMove,
    grudgerTests,
    testCount
  );
}

int TestTit4Tat() {
  MoveTest tit4TatTests[] = {
    { CooperateMove, CooperateMove },
    { CheatMove, CheatMove },
    { CooperateMove, CooperateMove },
    { CheatMove, CheatMove },
  };
  int testCount = sizeof(tit4TatTests)/sizeof(*tit4TatTests);
  return TestPlayer(
    Tit4TatStrategy,
    "Tit4Tat",
    CooperateMove,
    tit4TatTests,
    testCount
  );
}

int TestTit4TatKitten() {
  MoveTest tit4TatKittenTests[] = {
    { CooperateMove, CooperateMove },
    { CheatMove, CooperateMove },
    { CheatMove, CheatMove },
    { CooperateMove, CooperateMove },
  };
  int testCount = sizeof(tit4TatKittenTests)/sizeof(*tit4TatKittenTests);
  return TestPlayer(
    Tit4TatKittenStrategy,
    "Tit4TatKitten",
    CooperateMove,
    tit4TatKittenTests,
    testCount
  );
}

int TestDetective() {
  int testCount = 0;
  MoveTest detectiveTests[] = {
    { CooperateMove, CheatMove },
    { CooperateMove, CooperateMove },
    { CooperateMove, CooperateMove },
    // cooperated in opening, expect tit4tat
    { CooperateMove, CooperateMove },
    { CheatMove, CheatMove },
    { CooperateMove, CooperateMove },
    { CheatMove, CheatMove },
  };
  int detectiveTestsCount = sizeof(detectiveTests)/sizeof(*detectiveTests);
  testCount = TestPlayer(
    DetectiveStrategy,
    "Detective",
    CooperateMove,
    detectiveTests,
    detectiveTestsCount
  );

  MoveTest detectiveTests2[] = {
    { CooperateMove, CheatMove },
    { CheatMove, CooperateMove },
    { CooperateMove, CooperateMove },
    // cheated in opening, expect cheater
    { CooperateMove, CheatMove },
    { CheatMove, CheatMove }
  };
  int detectiveTests2Count = sizeof(detectiveTests2)/sizeof(*detectiveTests2);

  testCount += TestPlayer(
    DetectiveStrategy,
    "Detective",
    CooperateMove,
    detectiveTests2,
    detectiveTests2Count
  );
  return testCount;
}

/*****************************************************************************/

void TestPlayers() {
  int testCount = 0;

  testCount += TestCooperator();
  testCount += TestCheater();
  testCount += TestGrudger();
  testCount += TestTit4Tat();
  testCount += TestTit4TatKitten();
  testCount += TestDetective();

  cout << "Strategies passed " << testCount << " assertions." << endl;
}
