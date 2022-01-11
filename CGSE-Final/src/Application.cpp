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

    glfwSwapInterval(1);

    /* H-Initialize glew Init*/
    glewInit();

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* H-Create a VertexBuffer */
    //H-Create Data-Array for an triangle
    float triangle[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    //H-Create an index-Buffer
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    //H-Creating a Vertex Array Object 
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;                    
    glGenBuffers(1, &buffer);
    //H-Create a vertex buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(triangle), triangle, GL_STATIC_DRAW);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    //H-Create a index buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    //H-GlEnableVertexAttribArray does only work, if an Vertex Array Object (VAO) exists. In newer versions, if no VAO defined, openGL generates a VAO in the Background and binds it to the Array Buffer.
    /*H-These lines enable the GL_ARRAY_BUFFER attributes to be modifies inside the shader. So they define the layout and the locations of the specific attributes*/
    glEnableVertexAttribArray(0);
    // glVert... (index -> Which attribute index we are looking at, size -> Dimension of the attr. (1,2,3 or 4), type, shellNormalise?, stride (Byte size of an vertex), pointer -> How many Bytes are before the attribute we are looking at) 
    // This method tells index 0 of the vao to be bound to the current Array Buffer.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 

    /* H-Reading in shaders */
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    //H-getting the l
    int location = glGetUniformLocation(shader, "u_Color");
    //ASSERT(location != -1);
    float c_r = 0.0f;
    float increment = 0.05f;

    //Clearing all Buffers before starting with render loop.
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //H-Use defined shaders
        glUseProgram(shader);

        glUniform4f(location, c_r, 0.3f, 0.8f, 1.0f);
        
        //H-Buffer should be binded bevore each Drawcall because they could change or be unbinded.
        //In this case they have been cleared before entering the render loop.
        //Because the Vertex Array Object is connected with the GL_ARRAY_BUFFER, we do not need to bind the GL_ARRAY_BUFFER again.
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        /*H-Draw the vertex buffer*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        if (c_r >= 1.0f) {
            increment = -0.05f;
        }
        else if (c_r <= 0.0f) {
            increment = 0.05f;
        }
        c_r += increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}