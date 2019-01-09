# Introduction
This is a simple implementation of Robby The Soda Can robot GA, as stated by Melanie Mitchell book, "Complexity: A Guided Tour".
You can find Mitchell source code [here](http://web.cecs.pdx.edu/~mm/RobbyTheRobot/). I find that this implementation is a little
easier to follow, it is slower, however it is more readable and provides very good solutions.

# Usage
The usage of the program is very simple, you can at the command line pass a few parameters that can control a little of the GA.
Those are:

    Usage: ./robbyGA options
    Options:
       -h            --help                  This help message
       -o file       --output file           The output result file (CSV format)
       -s selection  --selection selection   The type of selection (0:Roulette, 1: Elite, 2: Tournament)
    Defaults: -o output.csv -s 0

The biggest parameter that can change something is the *selection* parameter, more on this latter.

## Dependencies

* GSL for creating random numbers

# Genetic Algorithm for Robby
The Genetic Algorithm is pretty straightforward:

1. Generate an initial random population
2. See how well each individual can handle an amount of random cleanning sessions
3. Create a new population based on crossover and mutation
4. Execute from 2 again until finished the amount of generations

There are 2 points that are worth mentioning, the strategy (or, what is a strategy) and the selection type.

## What is a strategy?
For robby, a strategy is what action it'll take based on the neighbours it has. You can think of a strategy for robby as a table
like this:

| North | South | East | West | Current | Action |
| ----- | ----- | ---- | ---- | ------- | ------ |
| Clean | Wall  | Dirt | Clean| Clean   |Go North|
| Clean | Wall  | Dirt | Dirt | Dirt    |Clean up|
| Clean | Clean | Dirt | Clean| Clean   |Go South|

And this can go on and on until all neighbours options are exausted, that means that there's 243 different options (each site
can either be a wall, clean or dirt, so 3x3x3x3x3=243). There's actually a little less because the current site can't be a 
wall, but to keep it simple we'll go with a full option.

That being said, a strategy is the Action array of movements for each of the 243 options. The valid actions used here are:

0. Go North
1. Go South
2. Go East
3. Go West
4. Do nothing
5. Clean up
6. Move at random

So for instance, a valid strategy can be:<code>644516003410215120314630331263452145021310422550020315544024211360444663622646663145600513533514131050325000146552114616165340140404330115251155340201601141526416256041211252616234446256410252520203250136205342243003623111111332615012503110065</code>

What we used here was a base 3 representation, so for instance if the neighbours were to be:

* North: Wall
* South: Dirt
* East: Clean
* West: Wall
* Current: Dirt

That would give the base 3 number of 21021, that is 196 in decimal, and by picking up the strategy presented before would be action 2, that is "Go East".
Which is a good solution, it won't hit a wall, however it won't clean up the dirt it currently is in.

## Selection type
There are a lot of different selection types and implementations for a GA, in Melanie Mitchell book she uses a roulette well
selection type, in the code it's being used as well. I implemented 3 different selecction types:

* Elite Only
* Tournament
* Roulette

### Elite only
This type of selection basically picks up the 20% best individuals (bigger fitness values) and keep them. The rest it'll be created by selecting at random
from that 20% best individuals with crossover and mutation.

By using this type of selection, we reached a local optimal solution of near 0 in the very beginning, and we started evolving around the 400th generation, then it quickly reached the maximum value
near the 700th generation. This is a very good result, but we may need to increase the mutation rate to get out of the local optimal solution near 0 in the beginning.


### Tournament
Tournament is very simple, it selected 2 random individuals and returns the id of the biggest fitness one. In this type of
selection the rest of the population is created based on any individual of the old population. By doing this we prevent the issue
with the elite selection that completelly removes bad individuals, however we don't really give a good chance for good individuals.
We can bypass this by increasing the amount of individuals on the tournament.

When using this type of selection we were unable to reach very good solutions such as the Elite or the Roulette selection, but we did got good solutions and a somewhat steady increase of the fitness
after the ~350th generation.

### Roulette
This is the standard selection for a GA. It gives a weigh that is proporcional to the fitness of the individual and then
selects a random number. The individual that has a higher probability to be selected will be selected, but this gives a chance
for slow performing individuals as well.

This gave the best results and a very steady increase right around the 150th generation, after this generation we got a steady increase of fitness till around the 700th generation we reached the maximum
fitness possible for Robby.

### Others
There are other types of selection and I may be implementing them in the future.

### Graphs
![selection_graphs](https://raw.githubusercontent.com/minterciso/robbyga/master/src/outputs/selections.png)


Best regards and have fun

