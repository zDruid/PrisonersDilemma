#ifndef __TOURNAMENT_H__
#define __TOURNAMENT_H__

#include "Players.h"

static const Strategy kTestStrategies[] = {
  CooperatorStrategy,
  CheaterStrategy,
  RandomStrategy,
  GrudgerStrategy,
  Tit4TatStrategy,
  Tit4TatKittenStrategy,
  DetectiveStrategy
};

static const int kTestStrategyCount = sizeof(kTestStrategies)/sizeof(*kTestStrategies);
static const int kPlayerCount = kTestStrategyCount;

static const int kMatchIterations = 200;
static const int kNoiseProbability = 3;

class Tournament {
public:
  Tournament();
  ~Tournament();

  static Player *createPlayer(Strategy strategy);
  void playTournament();

private:
  Player *_players[kPlayerCount];
  int _scores[kPlayerCount][kPlayerCount] = {};

  void playMatch(int indexA, int indexB);
  void reportScores();
  void resetScores();
  Move distortedMove(Move move);
};

#endif
