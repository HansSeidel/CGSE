#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
/*H-Reads in the shader file*/
static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            type = line.find("vertex") != std::string::npos? ShaderType::VERTEX : ShaderType::FRAGMENT;
        }else{
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

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

    /* Reading in shaders */
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
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

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}