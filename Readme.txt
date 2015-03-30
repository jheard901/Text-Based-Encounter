A simple C++ console game that is a discrete simulation of
an RPG-like battle encounter.

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
will conclude the encounter if successfull. Taking
damage earlier reduces the odds of escape.

Created by: Javier Heard
3/27/15