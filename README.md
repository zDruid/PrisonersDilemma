# Instructions

## Background

Does math or computer science have anything to say about how we ought to behave? At least in a narrow sense, the field of game theory does. This project is about a very important game theoretical idea called 'The Prisoner's Dilemma'.

The movie "Oppenheimer" depicted the invention of the first nuclear bomb. The Soviet Union tested its own weapon not long after, in 1949. Beginning at that moment, there were two world powers, both armed with catastrophic weapons, both wary of the other. Each might have chosen to destroy the other first, causing terrible harm, but leaving themselves as the sole nuclear power. Or both might have chosen to refrain from violence and live in peace.

That's the better outcome for both, but imagine yourself making such a decision. You want to remain peaceful, but you know that becoming the sole power might be an attractive option for your opponent. And, rightly or not, your opponent may be thinking the same about you. If your opponent doubts your peaceful intentions, they might decide they must attack you. If that's what they're thinking, shouldn't you consider attacking them first? It may be a terrible act, but it's better than your obliteration. This is one form of the Prisoner's Dilemma.

How can we think about this problem computationally? It doesn't matter whether the domain is about countries or individuals, or about nuclear bombs or splitting a dinner bill. We can imagine a game where two players decide whether to cooperate or cheat, where cheating when the other cooperates pays the most, where both cooperating pays both a lot, and where both cheating pays both the least.

We can try out various strategies for playing this game, pitting each strategy against the others to see which one scores the highest. This is what [Robert Axelrod, a researcher at the University of Michigan](https://en.wikipedia.org/wiki/The_Evolution_of_Cooperation), did in the early 1980s.

Have a look at `Tournament.h` and `Tournament.cpp`. The tournament plays every strategy against every other, each making 200 moves in conjunction with its opponent. A 3 dimensional payoff matrix determines the points players earn for every combination of moves. The payoff matrix used by Axelrod in the U of M experiment pays `{ 3, 3 }` to the players if they both cooperate, `{ 1, 1 }` if they both cheat, and  `{ 5, 0 }` or `{ 0, 5 }` if one cooperates and one cheats, 5 to the cheater and 0 to the cooperator.

## Strategies

In this project, you will implement some of the strategies tested in that experiment. You'll do this by implementing nine 'Player' classes, seven representing different strategies and two serving as abstract base classes. The abstract classes aren't strategies, but they provide data and behavior common to the others.

Players have a lot in common with each other. Every player can be told to begin a round of the Prisoner's Dilemma game, every one can be asked for their move, every one can be told about what their opponent did, and every one can remember and update its score.

These data and behavior are captured in the abstract `Player` class. It's abstract because it is incomplete: it knows *that* it plays the Prisoner's Dilemma game, but it doesn't know *how to play*.

![](assets/pd-classes.png)

The subclasses, or derived classes of `Player` do know how to play. You might be able to guess from their names that `Cooperator` players always cooperate, and `Cheater` players always cheat.

One of the `Player` subclasses is itself an abstract class. The `StatefulPlayer` class adds the ability for a player to remember the last couple moves made by its oppponent. More sophisticated strategies entail behavior changes depending on the opponent's prior moves. Each of the strategies is described further in `Players.h` and `Players.cpp`.


## Steps to Complete

Most of the work in this project is in coding the players' class declarations in Players.h and coding the non-trivial method definitions in Players.cpp.

 1. Complete the class declarations in `Players.h`
 2. Complete the methods for one or two classes, such as 'Cooperator' and 'Cheater' in `Players.cpp`.
 3. You may wish to complete the other classes, but you might find it helpful to stub the methods in the other classes. A "stub" is the simplest do-nothing method that will compile.
 4. Once your project compiles, consider using some of the unit tests defined in `Tests.cpp`. In `main.cpp`, comment out the tournament code, and uncomment the line that invokes  `TestPlayers()`.  In `Tests.cpp` run just the tests that test players you've implemented, commenting out the others. A gradual approach to ensure your code works is to work on one class at a time, having each strategy pass its unit tests before moving to the next.
 5. With all 49 assertions working, you're almost ready to run the tournament. Which strategy do you think will dominate? Think about it first, then try the tournament.

## Further Study

Many important thinkers worked at Los Alamos on the Manhattan project. Advanced computing was essential to that project, and John von Neumann -- considered the father of the digital computer -- was part of the team in Los Alamos. Here's a photo of von Neumann (left) and Oppenheimer (right) posing in front of the "MANIAC" computing machine in Los Alamos. It weighed about 1000 pounds and had about 1,200 bytes of working memory. The phone in your pocket probably has 128-256 billion bytes.

![](assets/oppyandjohny.jpg)

After the war, Von Neumann was outspokenly in favor of a pre-emptive nuclear strike against the Soviet Union. This illustrates a point that's worth remembering: expertise in one domain does not necessarily imply wisdom in others.

The idea of Prisoner's Dilemma applies to all kinds of situations where decision makers must get along. The best exposition of these ideas I know about is [here, created by a developer called Nicky Case](https://ncase.me/trust/). If you think this project is interesting, I strongly recommend spending some time with Nicky's beautiful explanatory simulation.
