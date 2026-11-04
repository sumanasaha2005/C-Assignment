# C_plus_plus-Assignment
# Smart Farm Management System

A C++ console application that manages crop data and helps farmers record, display, and analyze cultivation details. Built to demonstrate core Object-Oriented Programming concepts.


## Problem Statement

Design a C++ program for a Smart Farm Management System that manages data related to different types of crops and their cultivation details. The system should support recording, displaying, and analyzing data to assist farmers in making decisions.

### Requirements

1. Define a base class `Crop` with attributes `name`, `area`, `season`, and `yieldPerAcre`, using appropriate access specifiers and constructors.
2. Derive two classes, `CerealCrop` and `VegetableCrop`, from `Crop` using inheritance, adding their own data members (fertilizer type, irrigation frequency).
3. Use constructor overloading and a virtual destructor.
4. Apply runtime polymorphism to calculate and display total yield for both crop types.
5. Demonstrate operator overloading to compare two crops based on yield.
6. Create an abstract class `Advisory` with a pure virtual function `giveAdvice()` and implement it in derived classes to provide farming tips.
7. Use file handling to save and retrieve crop data.
8. Include at least one use of static members (e.g., count of crops).
9. Ensure proper input/output formatting and exception handling (e.g., invalid area or yield input).


## Features

- Add cereal and vegetable crops
- Display all crops in a formatted table
- Calculate total yield per crop and for the whole farm
- Compare two crops by yield per acre
- Get crop-specific farming advice
- Save crop data to `crops.txt` and load it back
- Robust input validation and error handling



## OOP Concepts Used

| Requirement | Implementation |
|---|---|
| Base class & access specifiers | `Crop` with `protected` members and `public` methods |
| Inheritance | `CerealCrop` and `VegetableCrop` derive from `Crop` |
| Constructor overloading | `Crop()`, `Crop(name, area)`, `Crop(name, area, season, yield)` |
| Virtual destructor | `virtual ~Crop()` and `virtual ~Advisory()` |
| Runtime polymorphism | `totalYield()`, `display()`, `getType()`, `saveToFile()` are virtual and overridden |
| Operator overloading | `>`, `<`, `==` compare crops by `yieldPerAcre` |
| Abstract class | `Advisory` with pure virtual `giveAdvice()` |
| File handling | `ofstream` / `ifstream` for save and load (`crops.txt`) |
| Static members | `static int count` tracks the number of crop objects |
| Exception handling | `invalid_argument`, `runtime_error`, with `try/catch` in `main` |
| I/O formatting | `setw`, `setprecision`, `fixed`, `left` |

Advisory (abstract)
└── Crop
├── CerealCrop      (fertilizerType)
└── VegetableCrop   (irrigationFreq, 10% post-harvest loss)



