#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void makeTriangle(float x, float y, float width, float height, unsigned int* VAOpointer);
void makePolygon(float* vertices, std::size_t vsize, unsigned int* indices, std::size_t isize, unsigned int* VAOpointer);
void createShaderProgram(unsigned int* shaderProgramPointer, const char* vertexShaderCode, const char* fragmentShaderCode);
void create_pic(float center, float width, float height, unsigned int* VAOpointer);
void test(float center, float width, float height, unsigned int* VAOpointer);
void loadTexture(const char* filePath, unsigned int* texturePointer, GLenum format);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = vec4(aColor, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* vertexShaderSource2 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = vec4(aPos, 0.0);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* vertexShaderSourceforTexture = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"uniform vec2 offset;\n"
"out vec2 texCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0);\n"
"   texCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

const char* fragmentShaderSourceforTexture = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 texCoord;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"   FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);\n"
"}\n\0";

void createShaderProgram(unsigned int* shaderProgramPointer, const char* vertexShaderCode, const char* fragmentShaderCode) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders

    glAttachShader(*shaderProgramPointer, vertexShader);
    glAttachShader(*shaderProgramPointer, fragmentShader);
    glLinkProgram(*shaderProgramPointer);
    // check for linking errors
    glGetProgramiv(*shaderProgramPointer, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgramPointer, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void loadTexture(const char* filePath, unsigned int* texturePointer, GLenum format) {
    glGenTextures(1, texturePointer);
    glBindTexture(GL_TEXTURE_2D, *texturePointer); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" + *filePath << std::endl;
    }
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    unsigned int texture1, texture2;
    loadTexture("../../resources/textures/container.jpg", &texture1, GL_RGB);
    loadTexture("../../resources/textures/awesomeface.png", &texture2, GL_RGBA);

    // build and compile our shader program
    // ------------------------------------
    unsigned int shaderProgram = glCreateProgram();
    createShaderProgram(&shaderProgram, vertexShaderSource, fragmentShaderSource);

    unsigned int shaderProgram2 = glCreateProgram();
    createShaderProgram(&shaderProgram2, vertexShaderSource2, fragmentShaderSource2);

    unsigned int shaderProgram3 = glCreateProgram();
    createShaderProgram(&shaderProgram3, vertexShaderSourceforTexture, fragmentShaderSourceforTexture);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    unsigned int VAO;
    makeTriangle(-0.5f, -0.5f, 1.0f , 1.0f, &VAO);

    unsigned int VAO2;
    makeTriangle(-0.75f, 0.0f, 0.5f, 0.5f, &VAO2);

    unsigned int VAO3;
    makeTriangle(0.25f, 0.0f, 0.5f, 0.5f, &VAO3);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    /*
    unsigned int VAO4;
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,  // top left
         1.5f,  1.5f, 4.0f,  // top right
         1.5f,  0.5f, 4.0f,  // bottom right
         0.5f,  0.5f, 4.0f,  // bottom left
         0.5f,  1.5f, 4.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
        0, 1, 5,
        0, 4, 5,
        4, 5, 7,
        6, 5, 7,
        0, 3, 4,
        7, 3, 4,
        7, 6, 2,
        7, 3, 2,
        6, 2, 1, 
        6, 5, 1
    };
    makePolygon(&vertices[0], sizeof(vertices), &indices[0], sizeof(indices), &VAO4);
    */
    unsigned int VAO5;
    create_pic(0.0f, 0.04f, 0.04f, &VAO5);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    glUseProgram(shaderProgram3);
    glUniform1i(glGetUniformLocation(shaderProgram3, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram3, "texture2"), 1);

    float speed = 0.0005f;
    float vMove = 0.0f;
    float hMove = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            vMove -= speed;
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            vMove += speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            hMove -= speed;
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            hMove += speed;
        glUniform2f(glGetUniformLocation(shaderProgram3, "offset"), hMove, vMove);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        
        
        
        /*
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
        */

        //glUseProgram(shaderProgram);
        /*
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        */
        //glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /*
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */

        

        glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void makeTriangle(float x, float y, float width, float height, unsigned int* VAOpointer) {
    unsigned int VBO;
    float vertices[] = {
         x,  y, 0.0f,
         x + width, y, 0.0f, 
         x + width/2, y + height
    };

    float colors[] = {
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f
    };
    GLuint colors_VBO;
    glGenBuffers(1, &colors_VBO);
    

    glGenVertexArrays(1, VAOpointer);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAOpointer);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    /*
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    */
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    //glDeleteBuffers(1, &VBO);
}

void makePolygon(float* vertices, std::size_t vsize, unsigned int* indices, std::size_t isize, unsigned int* VAOpointer) {
    

    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, VAOpointer);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAOpointer);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    //glDeleteBuffers(1, &VBO);
}

void create_pic(float center, float width, float height, unsigned int* VAOpointer) {
    float vertices[] = {
         center - width / 2, center - height / 2, 0.0f, //bl
         center - width / 2, center + height / 2, 0.0f, //tl
         center + width / 2, center - height / 2, 0.0f, //br
         center + width / 2, center + height / 2, 0.0f //tr
    };

    unsigned int indices[] = {
        0, 2, 1,
        1, 2, 3
    };

    float textureVertices[] = {
        0.0f, 0.0f, 
        0.0f, 1.0f, 
        1.0f, 0.0f, 
        1.0f, 1.0f
    };
    unsigned int VBO;
    GLuint textureVBO;
    unsigned int EBO;

    glGenVertexArrays(1, VAOpointer);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAOpointer);
        
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    //glDeleteBuffers(1, &VBO);
}

void test(float center, float width, float height, unsigned int* VAOpointer) {
    float vertices[] = {
         center - width / 2, center - height / 2, 0.0f, 0.0f, 0.0f, //bl
         center - width / 2, center + height / 2, 0.0f, 0.0f, 1.0f, //tl
         center + width / 2, center - height / 2, 0.0f, 1.0f, 0.0f, //br
         center + width / 2, center + height / 2, 0.0f, 1.0f, 1.0f //tr
    };

    unsigned int indices[] = {
        0, 2, 1,
        1, 2, 3
    };
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, VAOpointer);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAOpointer);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    //glDeleteBuffers(1, &VBO);
}