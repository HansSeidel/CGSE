#Final project CGSE

> ***Author:*** Hans Seidel (if20b211) <br>
> *Version:* 0.8 (gitTag: v0.8) <br>
> *Git commit message:* Learning - MVP <br>
> *Version Date:* 12.01.2022 


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
> *Architecture:* 32-bit Windows binaries <br>
> *Version:* 3.3.6 <br>
> *Used library:* 
> - lib-vc2019 
> - include

> ***Glew:*** [Windows 32-bit and 64-bit](http://glew.sourceforge.net/) <br>
> *Version:* 2.1.0

> ***GLM Library:*** [G-Truc Creation Github](https://github.com/g-truc/glm/releases/tag/0.9.8.5) <br>
> *Version:* glm-0.9.8.5

##Setup
1. Download the ***GLFW Library*** and put the ***include*** and the ***lib-vc2019*** folder inside the ***Dependencies\GLFW*** folder.
2. Download the ***Glew Library*** and put the whole content into the ***Dependencies\GLEW*** folder.
3. Download the ***GLM Library*** and put the ***glm*** folder inside the ***CGSE-Final\src\vendor*** folder.


## Documentation
The documentation is split into two parts. 
The first part descripes the project(s) i used to repeat and deepen my knowlegde about openGL.
This part follows the steps of [this](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=1) tutorial-series.
<br>
The second part descripes the progress of the final project.

<br>In git the first part is below version 1.0. 

### Repetition and consolidation (v0.*)
**(v0.0)** -
At the beginning of the project, the setup has been created. In order to check if everything is running 
correct, a simple triangle was created.
**(v0.1)** - The next step was to write our own shaders and get the program running again. 
Within the fragment shader we defined the color of the triangle. 
**(v0.2)** - The shaders have been outsourced into a Basic.shader file.
**(v0.3)** - Next, an indexed buffer has been created and we drew a rectangle.
**(v0.4)** - The color attribute was taken out to the cpu layer by an uniform. With each frame the red channel got incremented. 
The Framerate has been adjusted by glfwSwapInterval(1) which synchronizes with the v-sync of the monitor.
**(v0.5)** - Instead of using the default vertex array object (vao) which is created in the background 
(if openGl is running with the compat profile), an own vao has been created and wired with the vertex array buffer.
**(v0.6)** - Now it is time to abstract the written code into different classes and save some lines of code. 
The IndexBuffer, VertexBuffer, VertexArrayObject and shader has been outsourced and they are working as own classes.
**(v0.7)** - To wrap things up, a render class was implemented, so it's easier to pass data in between. 
In order to use a texture, [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) and a Texture class was implemented. 
With little adjustments inside the fragment shader, the texture could be loaded and shown.
**(v0.8)** - Then the [GLM library (v0.9.8.5)](https://github.com/g-truc/glm/releases/tag/0.9.8.5) has been added as well 
which made it possible to add the model-, view-, projection-matrices. 

