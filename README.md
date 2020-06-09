# Traveling-Salesman-Console-App

## About

This is genetic algorithm implementation which I created in order to pass one of my classes at university.Problem which it tries solving is [the traveling salesman problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem). The requirement was to implement two selection (roulette and tournament), two mutation (inversion and exchange) and crossover function in this case PMX. 
  
I decided to use c ++ over c # (it is the main language I code in) to get best performance. To achieve even better performance I used [Intel threading building blocks](https://software.intel.com/content/www/us/en/develop/tools/threading-building-blocks.html) which enabled me to process algorithm in multi thread. 


## How to use application

1. Download TSP-APP zip from [here](https://github.com/GhooTS/Traveling-Salesman-Console-App/releases/tag/1.0)
2. Extract the project to any location on your computer
3. In main folder run **TravelingSalesmanApp.exe**
4. Use console to specify path to distances or positions file by **DM** command ``` DM [Location of TSP-APP folder on your computer]/TSP-APP/TSP/berlin52.txt ``` (the TSP folder included other traveling salesman problem, more problems you can find [here](http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsplib.html) as well as optimal solution)
5. Use **start** command to start the algorithm or change config by other commands(see **Console commands** section below)

## Building and running project

1. Download tbb from [here](https://github.com/oneapi-src/oneTBB/releases/tag/v2020.1)
2. Add environment variable in your system with name **TBBROOT** and value of tbb root folder location for example ```C:\Program Files (x86)\tbb```
3. Build project
4. Copy tbb.dll or tbb-debug.dll (depends on build setting) to the location of builded .exe file 
5. Run appilcation 


## What you should know about algorithm configuration

### Selection
* **Rulette/Fitness proportional selection** - not recommended for this type of problem, but I had to implement it because of the requirement. gives rather random solutions.
* **Tournament** - this selection work better then rulette selection, the selection depends on the tournamenet size which shoud be equale to 10% of all indviduals(cites in that case). In this selection, x individuals are selected randomly with repetitions, where x is the size of the tournament, from those individuals the one with the shortest path is selected. This process is reapted till all indivduals are selected to next generation.

### Mutation
After selection gens(city index) in every individual is being mutated, there is two type of mutataion you can use in this application.

* **Exchange** - two genes are selected randomly from the individual, after which their position is exchanged.
```
|1| 2 4 |3| > |3| 2 4 |1| // first and last gen was picked
```
 * **Inversion** - in this mutation random subset of genes is selected, and then the subset is inverted.
 ```
 |1 2 3 5| 6 4 7 > |5 3 2 1| 6 4 7
 ```
Mutation through inversion is recommanded with mutation chance on level between 5%-15% (but you can experiment :) ).

### Crossover

there is only PMX crossover in this implementation, you can find more about it in [this article](https://www.hindawi.com/journals/cin/2017/7430125/). Copy chance control how often indviduals are crosed, the smaller the copy chance parameter is, the more likely that 2 individuals will cross each other. 5% procent is recommanded.

### Other parameters

* **Numer of generation** - controls how many generation need to pass, before algorithm terminates.
* **Number of indivduals** - how many different paths will be checked in each population (more doesn't mean better).
* **Display interval** - how often stats about current population is shown during algorithm execution.

## File format

#### example file format for position (.tsp)

```
5 // number of cites
1 37 52 // successively index (can be omitted), x coordination and y coordination
2 49 49
3 52 64
4 20 26
5 40 30
```
## example file format for distance matrix (.txt)

asymmetric
```
5 // number of cites
0 12 19 31 22 //distance between cites
12 0 15 37 21
19 15 0 49 36
31 37 49 0 20
22 21 36 20 0
```
symmetric
```
5 // number of cites
0 //distance between cites
12 0 
19 15 0 
31 37 49 0 
22 21 36 20 0
```
## Console commands 

Commands are not case sensitive

* **start** - start algorithm with current config.
* **exit** - exit appliaction.
* **clear** - clear console.

**Config**
* **DM** - sets distance matrix from file. for example  ```DM G:/TSP/berlin52.txt```.
* **DI** - sets how often information about current generation is shown.
* **NOI** - sets number of individuals.
* **NOG** - sets number of generation.
* **TSize** - sets tournament size for tournament selection.
* **ST** - set selection (1 = roulette 2 = tournament).
```
ST 2 // Set selection type to tournament
```
* **CC** - sets copy chance from 0 (0%) to 1 (100%).
* **MC** - sets mutation chance from 0 (0%) to 1 (100%).
* **MT** - set mutation (1 = inversion 2 = exchange).
```
MT 1 // Set mutation type to inversion
```
**Other**
* **showConfig** - display current config.
* **showResults** - display results type 'all' to see all results or index to display only one. 
```
SHOWRESULTS all //show all results
SHOWRESULTS 2 //show result with index of 2
```
* **saveResult** - save results type 'all' to save all results or index to save only one. file are saved in the same folder as file specified in DM command with name fileName_Result[sessionID].txt.
```
SAVERESULTS all //save all results, if not saved
SAVERESULTS 2 //save result with index of 2, if not saved
```
