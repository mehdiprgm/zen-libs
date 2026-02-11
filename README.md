<h1 align="left" id="title">zen-libs</h1>

<p id="description">This repository contains useful libraries to help developers build software faster. all of these utilities are tested and i fixed bugs so don't worry.</p>

  
  
<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Terminal utilities
*   Work with text files
*   Access os and hardware information

<h2>🛠️ Installation Steps:</h2>

<p>1. the libraries are already compiled just copy them into your project directory and set the LD_PATH and link them in the runtime.</p>

```
export LD_LIBRARY_PATH=/path/to/project:$LD_LIBRARY_PATH
```

<p>2. compile your project like normal just add " -l "" to the end of command to specify the libraries name</p>

```
g++ -o program main.cpp -L/path/to/libs -lmath -lutils -lnetwork
```

  
  
<h2>💻 Built with</h2>

Technologies used in the project:

*   C++ 17
*   GNU Compiler

<h2>💖Like my work?</h2>

You can contact me about this project i would like to hear your comments.
