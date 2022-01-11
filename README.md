#Final project CGSE

> ***Author:*** Hans Seidel (if20b211) <br>
> *Version:* 0.4 (gitTag: v0.4) <br>
> *Git commit message:* Learning - Uniforms and updated glVertexAttribPointer commants <br>
> *Version Date:* 11.01.2022 


##Description
The aim of this project is to learn openGL and genereate a demonstration project. 
This project is part of a lecture at the *Fachhochschule Technikum Wien*.
The final project shows a endless world with the same house arrayed next to each other.

**In order to setup the project you only need the follwing chapters:**
- [Envirement and Dependencies](#envirement-and-dependencies)
- [Setup](#setup)

##Tasks
The original assignment description is shown at the following link: [Project Submission](https://moodle.technikum-wien.at/mod/assign/view.php?id=850504) *(You need permissions for this link)*
<br>The least expectations are:
- Presentation of three textured objects
- Interactive camera movement
- One little animation (For example a moving object)
- The use of mipmapping in combination with hardware accelarated texture compression
- The use of transparent geometry (Minimum of two objects which cover each other)
  - Sorted by quicksort and center of gravity calculations
- One object with three discrete level of detail instances that are based on range

##Envirement and Dependencies

###Envirement 

> ***Operating System:*** Windows <br>
> *Version:* Windows 10 Education 20H2

> ***Development envirement:*** Visual Studio 2019<br>
> *Version:* 16.11.8

###Dependencies
> ***GLFW Librarby:*** [Windows pre-compiled binaries](https://www.glfw.org/download.html) <br>
> *Version:* 3.3.6 <br>
> *Used library:* 
> - lib-vc2019 
> - include

> ***Glew:*** Windows 32-bit and 64-bit <br>
> *Version:* 2.1.0

##Setup
1. Download the ***GLFW Library*** and put the *include* and the *lib-vc2019* folder inside the *Dependencies/GLFW* folder.
2. Download the ***Glew Library*** and put the whole content into the **Dependencies/GLEW* folder.


## Documentation
The documentation is split into two parts. 
The first part descripes the project(s) i used to repeat deepen my knowlegde about openGl.
This part follows the steps of [this](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=1) tutorial-series.
<br>
The second part descripes the progress of the final project.
<br>
In git the first part is below version 1.0. So any tag with (v0.*)

### Repetition and consolidation
**(v0.0)** -
At the beginning of the project, the setup has been created. In order to check if everything is running 
correct, a simple triangle was created.
**(v0.1)** - The next step was to write our own shaders and get the program running again. 
Within the fragment shader we defined the color of the triangle. 
**(v0.2)** - The shaders have been outsourced into a Basic.shader file.
**(v0.3)** - Next, an indexed buffer has been created and we drew a rectangle.
**(v0.4)** - The color attribute was taken out to the cpu layer by an uniform. With each frame the red channel got incremented. 
The Framerate has been adjusted by glfwSwapInterval(1) which synchronizes with the v-sync of the monitor.

