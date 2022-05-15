# OSProject
This exercices are made to use threads and semaphores.

Exo01 : Compute the syracuse suit using threads and memoriszation (caching).     
Exo02 : Compute the pascal triangle using threads.      

## Installation

Use clang or gcc. 
```bash
sudo apt install clang
```
For gcc use build-essential to get additional libs. 
```bash
sudo apt install build-essential 
```

## Compile 
Use make to build the project. 

```bash
make yourtarget
```

Available target : 

| Target        | Description |
| ------------- | --------------------------|
| all           | Make all possible target  |
| clean         | delete build folder content (bin,objects,etc...)  |
| build         | create build folder  |
| exo1          | compile the first exercise   |
| exo2          | compile the second exercise   |

> You can use the DEBUG flag in Makefile, it will use address sanitizer and g3 to debug.     
> `-pthread` is used at compile time. Make sur that your gcc have lib for pthread, in some case pthread is not included.      

## Exercices Status 
- [x] Exo01
- [x] Exo02

## Run
- Exo 1 : run ```./build/binexo1 10 ``` for flight of 10 
- Exo 2 : run ```./build/binexo2 10 ``` for 10 lines of pascal. 

## Team    

| Name               | Profile            |
|--------------------|--------------------|
| Théo Peuchlestrade | @theopeuchlestrade |
| Julian Rety        | @Julian63800       |
| Dorian Hardy       | @thegostisdead     |

