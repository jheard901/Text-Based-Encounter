A simple C++ console game that is a discrete simulation of
an RPG-like battle encounter.

Contains Windows specific code and is not portable.

Rules of the game:
-Two teams (1 is player, the other is AI)
-The first team to die loses
-Draws occur if a team escapes

Features:
Each character has four actions that can be choosen:
Attack, Defend, Charge, Flee

Attack inflicts damage to another character and has
a chance to critically hit for 3x damage.

Defend mitigates 50% of damage taken and has a chance
to counter attack the attacking character for 200% of
that damage.

Charge increases critical hit and counter chance based
off whether or not the character took damage earlier.

Flee has a character a chance to escape combat which
will conclude the encounter if successful. Taking
damage earlier reduces the odds of escape.

Future Updates:
In the future, my priority would be on tuning the AI to
be much better than it is. It honestly was rushed, and I
think there is a lot more that can be done to tweak it to
be nice. Besides that, there is also the option to work on
adding in multiplayer to the game, but I think it would
take quite a bit of time to add in considering my limited
net coding knowledge (WinSock 2.0). The actual values used
for setting stats (based off difficulty) needs some tweaking
as well.

Created by: Javier Heard
3/27/15