# 57. Sorting Visualizer

<p align="center">
<img width="600" alt="URL Components" src="https://github.com/lyndskg/98-Projects-of-Code/blob/main/57.%20Sorting%20Visualizer/example.gif"> 
</p>

## Overview 

<ins>__Language__</ins>: JavaScript  

<ins>__Completed on__</ins>: February 7th, 2023

A webpage displaying different sorting algorithm visualizations using the [p5.js](https://p5js.org) library. Algorithms can be run on differents-sized arrays &mdash; these arrays can be randomized, ordered, shuffled, and/or reversed. 

Currently supports the following sorting algorithms:
- Bubble Sort
- Quick Sort
- Merge Sort
- Insertion Sort
- Selection Sort
- Heap Sort
- Tim Sort
- Shell Sort
- Cycle Sort
- Odd Even Sort

Implementation guided by [this repo](https://github.com/mertturkmenoglu/sorting-visualization). Additional guidance can be found [here](https://github.com/MichaelHolley/p5.js_SortingAlgorithmVisualization) and [here](https://github.com/syzxy/FunSorting).

## To Do

Implementation is finished, but additional sorting algorithms may be added. Stylistically, may take notes from [here](https://github.com/MichaelHolley/p5.js_SortingAlgorithmVisualization). 

Note: Radix sort was removed. 

## Usage

After navigating to the current working directory, install `npm`'s `http-server` module globally on your machine via this command:

```
$ npm install http-server -g 
```

Then, run the module:

```
$ http-server ./ -p 1337
```

Open http://localhost:1337/ in a web browser. 