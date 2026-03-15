# Trade Route Network Optimization

This project explores a graph optimization problem inspired by the traderoute system in Civilization-style strategy games.

## Problem

While playing the game, I usually ended up with cities a bit too far away from each other.
Since new cities are not capable of producing units quickly, I always had to produce units in more developed cities and move them to places where they are needed.
Without roads, their speed are quite slow. This is where traderoutes comes in handy.
Traderoutes between cities can build roads, and most importantly, they are available in the early game.
Beside that, traderoutes also provide resources. And I started to wonder, what is the most efficient way to allocate traderoutes?

## Modelling

We can see each city as a vertex that we need to connect together.
Each traderoute are seen as an edge, we are interested in the profit and length of them.
Our goal is to maximise the ratio (total profit) / (total distance)

## Funfact

I initially thought of an incorrect solution. But then I realised the mistake via a real life problem while cooking.

## Algorithm

Call the resulting ratio x
We binary search x. At each step, we check if there exist a minimum spanning tree(MST) that gives the ratio not less than x.

For finding the MST:
1. we set the weight of each edge to (profit - x*distance)
2. we apply MST algorithm(I use Kruskal in my implementation)
3. we check the total weight of the tree. If it is smaller than 0 then there doesn't exist a MST with the ratio not less than x.
