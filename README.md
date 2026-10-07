# Flashcards

A desktop flashcard app for studying, written in C++ with Qt 6.

## Features
- Create categories (e.g. "Mathematics")
- Add flashcards (question + answer) to each category
- Test mode: go through all cards in a category, reveal the answer, see progress (Card 1/n)

## Screenshot
<img width="452" height="532" alt="image" src="https://github.com/user-attachments/assets/ef0865e1-8d62-4114-bfdc-dd408fb2ebf0" />
<img width="412" height="507" alt="image" src="https://github.com/user-attachments/assets/b0d5b2a7-dcb5-4fec-9042-62f5748728fc" />
<img width="433" height="517" alt="image" src="https://github.com/user-attachments/assets/01cf6a43-d796-4b7d-8d05-2a727b918ea5" />
<img width="422" height="521" alt="image" src="https://github.com/user-attachments/assets/f2be8282-6f7e-4938-af72-6b0786233d35" />
<img width="415" height="513" alt="image" src="https://github.com/user-attachments/assets/a8d873ce-7890-496f-bf3d-487920370b1b" />
<img width="400" height="496" alt="image" src="https://github.com/user-attachments/assets/bc01fd90-7fdf-40fb-8e4f-441e707e604a" />

## Build (Windows, MSYS2 UCRT64)
```
pacman -S mingw-w64-ucrt-x86_64-qt6-base mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64
cmake --build build
./build/flashcards.exe
```

## What I learned
- Object-oriented C++: classes, encapsulation, `const` correctness, vectors
- Qt: layouts, `QStackedWidget`, signals and lambdas
- Setting up a toolchain (MSYS2, CMake) and using Git/GitHub

## Planned features
- Save and load cards from a file
- Random card order in test mode

## Note
Built as a learning project with AI assistance (Claude) for guidance and explanations.
