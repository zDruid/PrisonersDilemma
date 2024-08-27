#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include <string>
using namespace std;

/*
In each encounter, a player may choose to cheat the other player, or attempt
to cooperate with them. NoMove is used to represent the uninitialized value
of a move.
*/
enum Move { CheatMove, CooperateMove, NoMove };

/*
These are each of the strategies, described more fully elsewhere. Notice the
last strategy is called "StrategyCount". By default, enums are assigned integers
starting at 0, so the last enum is useful knowing how many valid values there
are.
*/
enum Strategy {
  CooperatorStrategy,
  CheaterStrategy,
  RandomStrategy,
  GrudgerStrategy,
  Tit4TatStrategy,
  Tit4TatKittenStrategy,
  DetectiveStrategy,
  StrategyCount
};

/*
Use this array of strings as is. Notice that the strategy names appear in the
same sequence as the Strategy enum, so that StrategyNames[aStrategyEnum] will
evaluate to a string with the corresponding name.
*/
static const string StrategyNames[] = {
    "Cooperator", "Cheater",       "Random",    "Grudger",
    "Tit4Tat",    "Tit4TatKitten", "Detective", "Generic",
};

/*****************************************************************************/
// Player

/*
Declare the Player class here, remembering these details:

A player has one protected member variable: an integer called _score that
should be initialized to 0.

Some of these methods may be declared and defined here in the class declaration.
Those that should be only declared here and defined in the cpp are indicated.
All of these methods are public.

Destructor - Base classes must implement a destructor, and it must be virtual.
This Player's destructor may be implemented simply by assigning to = default.

strategy() - Every player must return its Strategy enum via a strategy() getter.
But this abstract Player base class provides only common code for its derived
classes. Its strategy() getter has no reasonable value to return. Therefore,
this method should be "pure virtual".  Declare and define that here.

beginRound() - This method is called by the Tournament object when a round
begins. The base class implementation resets the player's score to zero. Derived
classes may override this to include additional initialization steps. Declare
this method here in the class declaration, but define it in the cpp.

move() - This is where a player determines its moves, returning a Move
enum. As with strategy(), only the derived classes have reasonable behaviors
for a first move. The declaration here should also be "pure virtual".

setOpponentMove() - This is how a player is informed about its opponent's most
recent move. Some players care about this, basing their future moves on the
opponents' previous moves. The default behavior, this base class behavior,
is to do nothing. Code an empty method here. Derived classes will override it.
Note that an empty implementation not the same as a pure virtual implementation.

strategyName() - Return the string name from a Strategy enum given as a
parameter. All Player instances should share this capability, and it should be
usable by other classes without having any instance of a Player. To accomplish
this, declare this method as static. Define it in the cpp.

name() - This is an instance method that returns the strategy name for this
instance of player. Derived players will inherit this method, and they will
not need to override it. Declare this method here in the class declaration, but
define it in the cpp.

incrementScore() - This adds to the player's score, taking an integer parameter
of the number of points to add. Derived players will inherit but not need
to override it. Declare this method here in the class declaration, but
define it in the cpp.

score() - Declare and define a getter for the player's score.

*/

class Player {
public:
  virtual ~Player() = default;
  virtual Strategy strategy() = 0;
  virtual void beginRound();
  virtual Move move() = 0;
  virtual void setOpponentMove(Move opponentMove){};
  static string strategyName(Strategy strategy);
  // return StrategyNames[strategy]
  string name();
  void incrementScore(int numPoints);
  int score() const { return _score; }

protected:
  int _score = 0;
};

/*****************************************************************************/
// Cooperator

/*
Declare the Cooperator class here. Cooperator is a kind of Player that always
cooperates, no matter what its opponent does.

Have it declare, not define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

move() - Declare this method here, define it in the cpp file to move as
a cooperating player should.

*/

class Cooperator : public Player {
public:
  Strategy strategy() override;
  Move move() override;
};

/*****************************************************************************/
// Cheater

/*
Declare the Cheater class here. Cheater is a kind of Player that always cheats,
no matter what its opponents does.

Have it declare, not define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

move() - Declare this method here, define it in the cpp file to move as
a cheating player should.

*/

class Cheater : public Player {
public:
  Strategy strategy() override;
  Move move() override;
};

/*****************************************************************************/
// Random

/*
Declare the Random class here. Random players is a kind of Player that moves
at random, no matter what its opponents does.

Have it declare, not define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

move() - Declare this method here, define it in the cpp file to move as
a random player should.

*/
class Random : public Player {
public:
  Strategy strategy() override;
  Move move() override;
};

/*****************************************************************************/
// StatefulPlayer

/*
Declare the StatefulPlayer class here. StatefulPlayer is abstract, like the
Player class, but it adds some data and behavior. StatefulPlayer changes its
behavior based on its opponent's moves, so it must have some additional data.

Declare the following public methods:

beginRound() - Since it adds member variables, StatefulPlayer must add behavior
to provide initial values to the opponent's last moves (both of them).

setOpponentMove() - This is a setter for the StatefulPlayer's data member that
remembers the last opponent move, but it does more than a normal setter. When
you define this in the cpp, remember that this kind of player must remember the
*last two* opponent moves. Be sure to save the current value of _opponentMove
before setting it.

opponentMove() - Declare and define this getter method. It returns the
_opponentMove member variable.

In the protected part of this class, declare member data to remember the
opponent's last two moves, both of type Move. They should be called
_opponentMove and _priorOpponentMove for the last move and the move before
the last move, respectively.

*/

class StatefulPlayer : public Player {
public:
  void beginRound() override;
  void setOpponentMove (Move opponentMove) override;
  Move opponentMove() const { return _opponentMove; }

protected:
  Move _opponentMove = NoMove;
  Move _priorOpponentMove = NoMove;
};

/*****************************************************************************/
// Grudger

/*
Declare the Grudger class here. Grudger is a kind of StatefulPlayer who holds
a grudge. It will cooperate by default, but cheat on a Grudger even once, and
it will cheat forever.

Since a Grudger holds a grudge forever, it must know whether it is currently
holding a grudge, requiring another member variable.

Declare but don't define several methods that override inherited behavior.
You will provide the definitions of these methods in the .cpp file:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

beginRound() - Whenever a derived class adds a member variable, it should
override this to give that variable the right value for the start of a round.

move() - Declare this method here, define it in the cpp file to move as
a grudge holding player should.

setOpponentMove() - Declare this method here, define it in the cpp file.
When an opponent cheats on a Grudger, grudgers form a grudge.

Grudgers hold a grudge forever. In the the private part of the class, Grudger
will need another member variable that indicates whether it is holding a grudge.

*/

class Grudger : public StatefulPlayer {
public:
  Strategy strategy() override;
  void beginRound() override;
  Move move() override;
  void setOpponentMove(Move opponentMove) override;

private:
  bool _grudge = false;
};

/*****************************************************************************/
// Tit4Tat

/*
Declare the Tit4Tat class here. Tit4Tat is a strategy that starts by cooperating
and then simply mimics its opponent's previous move. If the opponent cheated
last, Tit4Tat cheats in the next move; if the opponent cooperated, Tit4Tat will
also cooperate.

This class inherits from StatefulPlayer as it relies on remembering the
opponent's last move to decide its current move.

Declare but do not define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

move() - Declare this method here, define it in the cpp file to move as
a tit-for-tat player should.


*/

class Tit4Tat : public StatefulPlayer {
public:
  Strategy strategy() override;
  Move move() override;
};

/*****************************************************************************/
// Tit4TatKitten

/*
Declare the Tit4TatKitten class here. This player is a another subclass of
StatefulPlayer which uses a variant of the Tit4Tat strategy. Tit4TatKitten
cooperates by default and only cheats if the opponent cheats twice
consecutively.

Declare but don't define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

move() - Declare this method here, define it in the cpp file to move as
a tit-for-tat kitten player should. Remember that tit-for-tat kittens are more
forgiving than tit-for-tat players.


*/

class Tit4TatKitten : public StatefulPlayer {
public:
  Strategy strategy() override;
  Move move() override;
};

/*****************************************************************************/
// Detective

/*
Declare the Detective class here. Another StatefulPlayer, Detective players
start with a specific sequence of moves: cooperate, cheat, cooperate, cooperate.
If the opponent cheats during these opening moves, the Detective plays like
Cheater for the rest of the round. If the opponent does not cheat during the
opening sequence, the Detective switches to playing like Tit4Tat.

Declare but don't define the following public methods:

strategy() - All of the classes derived from Player must override the instance
method that returns this Player's strategy. Declare here, define it in the cpp.

beginRound() - Override this method to reset the Detective's behavior at the
start of a round.

move() - Declare this method here, define it in the cpp file to move as
a detective player should.

setOpponentMove() - Override this method to track the opponent's moves and
adjust the Detective's strategy accordingly.

In the private part of this class, in addition to the inherited member data,
declare an integer _openingIndex to track the current index in the _openingMoves
sequence. As with Grudger, you will need an additional member variable.

Use these static declarations to define the opening move sequences. Recall that
declaring them as static allows all instances to share the same data, and
that declaring them as const means the values cannot be modified:

static constexpr Move _openingMoves[] = {
  CooperateMove, CheatMove, CooperateMove, CooperateMove
};

static const int _openingMovesCount = sizeof(_openingMoves) /
sizeof(*_openingMoves);

*/

class Detective : public StatefulPlayer {
public:
  Strategy strategy() override;
  void beginRound() override;
  Move move() override;
  void setOpponentMove(Move opponentMove) override;

private:
  int _openingIndex = 0;
  bool _grudge = false; 
  static constexpr Move _openingMoves[] = { CooperateMove, CheatMove, CooperateMove, CooperateMove };
  static const int _openingMovesCount = sizeof(_openingMoves)/sizeof(*_openingMoves);
};

#endif