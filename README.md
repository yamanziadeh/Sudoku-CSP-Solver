<!-- INTRO. -->
<br />
<p align="center">

  <h3 align="center">Sudoku CSP Solver</h3>

  <p align="center">
Solving Sudoku as a Constraint Optimization Problem <br /><br />
<img src="gitImgs/sudokuIcon.png?raw=true" width="300" >
  </p>
  
</p>

## How to use
1. Clone the repo
```sh
git clone https://github.com/yamanziadeh/Sudoku-CSP-Solver
```
2. Run Makefile command to get executable file
```sh
make build
```
3. Run command to execute the executable file on the existing input
```sh
make run
```
3. Run command to execute the executable file on your custom input by inserting your input file in the inputFiles directory and running the following command
```sh
./main inputFileName.txt
```
## CSP Properties
### Variables: 
* 9*9 (81) Cells
### Domain: 
* 1,2,3,4,5,6,7,8,9
### Constraints: 
* All numbers in a each 3x3 box should be different.
* All numbers in any row should be different.
* All numbers in any column should be different.


## Private Methods
### backtrack: 
* Function that performs backtrack search using the pruned domains of each cell and the isConsistent function for consistency checking.
### isConsistent: 
* Function that makes sure that the possible number assignment doesn't already appear in the same column, row, and box.
### pruneDomains: 
* Function that performs node consistency by pruning the domains of all cells such as the values within each domain satisfy the constraints.

## Public Methods
### solve: 
* Function that wraps the backtrack function.
### readFile: 
* Function that reads the input file line by line and coverts it into a matrix of 2d vectors.
### display: 
* Function that displays the matrix.
