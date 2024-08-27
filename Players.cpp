#include "Players.h"
#include "Utils.h"

#include <iostream>

/*****************************************************************************/
// Player Methods
// Players play the prisoners dilemma game

/*
The header file declared but didn't define the following
methods, define them here:

strategyName - Before attempting to implement this, read the enums and their
comments in the .h file carefully. Remember that this is a static method.

name
beginRound
incrementScore
*/

string Player::name() {
  // Strategy myStrategy = strategy();
  return strategyName(strategy());
}
void Player::beginRound() { _score = 0; }

string Player::strategyName(Strategy strategy) {
  return StrategyNames[strategy];
}

void Player::incrementScore(int numPoints) {
  _score += numPoints; 
}

/*****************************************************************************/
// Cooperator Methods
// Cooperators always cooperates

/*
The header file declared but didn't define the following
methods, define them here:

strategy
move
*/

Strategy Cooperator::strategy() { return CooperatorStrategy; }
Move Cooperator::move() { return CooperateMove; }

/*****************************************************************************/
// Cheater Methods
// Cheaters always cheats

/*
The header file declared but didn't define the following
methods, define them here:

strategy
move
*/

Strategy Cheater::strategy() { return CheaterStrategy; }
Move Cheater::move() { return CheatMove; }

/*****************************************************************************/
// Random Methods
// Pizza trombone paperclip bananas

// return either a cooperate or a cheat move with 50/50 distribution.
// This calls a more general-purpose random function defined in Utils.
// Use it as-is
//
Move CoopOrCheat() {
  bool coinflip = GetRandom(0, 2) == 0;
  return coinflip ? CooperateMove : CheatMove;
}

/*
The header file declared but didn't define the following
methods, define them here:

strategy
move
*/

Strategy Random::strategy() { return RandomStrategy; }

Move Random::move() { return CoopOrCheat(); }

/*****************************************************************************/
// StatefulPlayer Methods
// StatefulPlayers player determine their moves based on opponents' prior moves

/*
The header file declared but didn't define the following
methods, define them here:

beginRound - Hint: this should first invoke superclass's beginRound
setOpponentMove

HINT: setOpponentMove, before setting the opponentMove member var,
should assign the current value to _priorOpponentMove, saving it.
*/

void StatefulPlayer::beginRound() {
  Player::beginRound();
  _opponentMove = NoMove;
  _priorOpponentMove = NoMove;
}

void StatefulPlayer::setOpponentMove(Move opponentMove) {
  _priorOpponentMove = _opponentMove;
  _opponentMove = opponentMove;
}

/*****************************************************************************/
// Grudger Methods
// Grudger cooperates until opponent cheats, then always cheats

/*
The header file declared but didn't define the following
methods, define them here:

strategy
beginRound - Hint: this should first invoke superclass's beginRound
move
setOpponentMove

HINT: setOpponentMove is the method where players find out what their
opponent just did. If you're into grudges, this is the right place to decide to
hold one. After setting that member var, setOpponentMove must invoke its
superclass to perform the default behavior.

*/

void Grudger::beginRound() {
  StatefulPlayer::beginRound();
  _grudge = false; 
}

Strategy Grudger::strategy() { return GrudgerStrategy; }

Move Grudger::move() { return _grudge ? CheatMove : CooperateMove; }

void Grudger::setOpponentMove(Move opponentMove) {
  StatefulPlayer::setOpponentMove(opponentMove);
  if (opponentMove == CheatMove) {
    _grudge = true;
  }
}

/*****************************************************************************/
// Tit4Tat Methods
// Tit4Tat players cooperate by default, cheat only if the opponent cheats,
// then return to cooperating

/*
The header file declared but didn't define the following
methods, define them here:

strategy
move
*/

Strategy Tit4Tat::strategy() { return Tit4TatStrategy; }

Move Tit4Tat::move() {
  return (_opponentMove == NoMove) ? CooperateMove : _opponentMove; 
}

/*****************************************************************************/
// Tit4TatKitten Methods
// Tit4TatKittens cooperate by default, cheat only if the opponent cheats in
// two consecutive moves, then return to cooperating

/*
The header file declared but didn't define the following
methods, define them here:

strategy
move
*/

Strategy Tit4TatKitten::strategy() { return Tit4TatKittenStrategy; }

Move Tit4TatKitten::move() {
  bool angry = (_opponentMove == CheatMove && _priorOpponentMove == CheatMove);
  return angry ? CheatMove : CooperateMove;
}

/*****************************************************************************/
// Detective Methods
// Detectives are a StatefulPlayer subclass. They open with the sequence:
// cooperate, cheat, cooperate, cooperate. If their opponent cheats in this
// opening sequence, they continue to play like Tit4Tat players do, otherwise
// they cheat forever.

/*
The header file declared but didn't define the following
methods, define them here:

strategy
beginRound
move
setOpponentMove

As in other classes, remember to invoke the superclass behavior where
it is appropriate.

*/

Strategy Detective::strategy() { return DetectiveStrategy; }

void Detective::beginRound() {
  StatefulPlayer::beginRound();
  _openingIndex = 0;
  _grudge = false; 
}

// ====> DJH: ask me about cleaning up early returns if you're interested.
Move Detective::move() {
  if (_openingIndex < _openingMovesCount) {
    return _openingMoves[_openingIndex++];
  }
  else {
    if (_grudge) {
      return CheatMove;
    }
    else {
      return _opponentMove;
    }
  }  
}

void Detective::setOpponentMove(Move opponentMove) {
  StatefulPlayer::setOpponentMove(opponentMove);
  if ((opponentMove == CheatMove) && (_openingIndex < _openingMovesCount)) {
    _grudge = true; 
  }
}

