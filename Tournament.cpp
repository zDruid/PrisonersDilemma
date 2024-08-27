#include "Tournament.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>

static const int kPayoutsAxelrod[2][2][2] = {
  {{1, 1}, {5, 0}},
  {{0, 5}, {3, 3}}
};


/*****************************************************************************/

Tournament::Tournament() {
  for (int i=0; i<kTestStrategyCount; i++) {
    Strategy s = kTestStrategies[i];
    _players[i] = Tournament::createPlayer(s);
  }
  resetScores();
}

Tournament::~Tournament() {
  for (int i=0; i<kPlayerCount; i++) {
    delete _players[i];
  }
}

void Tournament::playTournament() {
  resetScores();
  for (int a=0; a<kPlayerCount; a++) {
    for (int b=0; b<kPlayerCount; b++) {
      playMatch(a, b);
    }
  }
  reportScores();
}

void Tournament::playMatch(int indexA, int indexB) {
  Player *playerA = _players[indexA];
  Player *playerB = nullptr; 
  if (indexA == indexB) {
    playerB = Tournament::createPlayer(playerA->strategy());
  } else {
    playerB = _players[indexB];
  }

  playerA->beginRound();
  playerB->beginRound();

  for (int i = 0; i < kMatchIterations; i++) {
    Move moveA = playerA->move();
    Move moveB = playerB->move();

    moveA = distortedMove(moveA);
    moveB = distortedMove(moveB);

    int payA = kPayoutsAxelrod[moveA][moveB][0];
    int payB = kPayoutsAxelrod[moveA][moveB][1];

    playerA->setOpponentMove(moveB);
    playerA->incrementScore(payA);

    playerB->setOpponentMove(moveA);
    playerB->incrementScore(payB);
  }

  _scores[indexA][indexB] = playerA->score();    
  if (indexA == indexB) delete playerB;
}

void Tournament::reportScores() {
  double maxAverage = -1;
  int maxRow = -1;
  for (int row=0; row<kPlayerCount; row++) {
    double sum = 0;
    for (int col=0; col<kPlayerCount; col++) {
      sum += _scores[row][col];
    }
    double average = sum / kPlayerCount;
    if (average > maxAverage) {
      maxAverage = average;
      maxRow = row;
    }
    // print strategy name, and average score
    string strategyName = Player::strategyName(kTestStrategies[row]);
    cout << setw(18) << strategyName << "  "
      << fixed << setprecision(1) << average << endl;
  }
  string winningStrategyName = Player::strategyName(kTestStrategies[maxRow]);
  cout << "\n Winner is " << winningStrategyName << " with "
    << fixed << setprecision(1) << maxAverage << endl;
}

void Tournament::resetScores() {
  for (int a=0; a<kPlayerCount; a++) {
    for (int b=0; b<kPlayerCount; b++) {
      _scores[a][b] = 0;
    }
  }
}

Move Tournament::distortedMove(Move move) {
  if (move != NoMove && GetRandom(0, 100) < kNoiseProbability) {
    return move == CooperateMove ? CheatMove : CooperateMove;
  }
  return move;
}

Player *Tournament::createPlayer(Strategy strategy) {
  Player *result = nullptr;

  switch (strategy) {
  case CooperatorStrategy:
    result = new Cooperator();
    break;
  case CheaterStrategy:
    result = new Cheater();
    break;
  case RandomStrategy:
    result = new Random();
    break;
  case GrudgerStrategy:
    result = new Grudger();
    break;
  case Tit4TatStrategy:
    result = new Tit4Tat();
    break;
  case Tit4TatKittenStrategy:
    result = new Tit4TatKitten();
    break;
  case DetectiveStrategy:
    result = new Detective();
    break;
  default:
    break;
  }
  return result;
}

