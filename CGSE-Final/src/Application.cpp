#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/*H-No idea what is happening here. My C++ and knowlegde about shaders is to far back for this*/
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* SRC = source.c_str();
    glShaderSource(id, 1, &SRC, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type== GL_VERTEX_SHADER? "vertex" : "fragment") << " shader. Message: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
/*H-No idea what is happening here. My C++ and knowlegde about shaders is to far back for this*/
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* H-Initialize glew Init*/
    glewInit();

    /* H-Create a VertexBuffer */
    //H-Create Data-Array for an triangle
    float triangle[6] = {
        -0.5f, -0.5f,
        0.0f,   0.5f,
        0.5f,  -0.5f
    };

    unsigned int buffer;                    
    glGenBuffers(1, &buffer);
    //H-Create a vertex buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(triangle), triangle, GL_STATIC_DRAW);

    
    //H-Rewatch: https://www.youtube.com/watch?v=x0H--CL2tUI&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=5 to understand glVertexAttribPointer.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 

    //H-Write own Vertex Shader
    std::string vertexShader = 
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main(){\n"
        "gl_Position = position;\n"
        "}";
    //H-Write own Fragment Shader
    std::string fragmentShader =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main(){\n"
        "color = vec4(1.0,0.0,0.0,1.0);\n"
        "}";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*H_Draw the vertex buffer*/
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteShader(shader);

    glfwTerminate();
    return 0;
}