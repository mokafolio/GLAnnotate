#include <GLFW/glfw3.h>
#include <GLAnnotate/GLAnnotate.hpp>

#include <random>

int main(int _argc, const char * _args[])
{
    // initialize glfw
    if (!glfwInit())
        return EXIT_FAILURE;

    // and set some hints to get the correct opengl versions/profiles
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    GLFWwindow * window = glfwCreateWindow(800, 600, "GLAnnotateExample", NULL, NULL);
    if (window)
    {
        glfwMakeContextCurrent(window);

        gla::GLAnnotate gla;
        bool error = gla.init();
        if (!error)
        {

            //create a simple texture;
            unsigned int tw = 200;
            unsigned int th = 100;
            unsigned char * texData = static_cast<unsigned char *>(std::malloc(tw * th * 3));
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 255);
            for (int y = 0; y < th; y++)
            {
                for (int x = 0; x < tw; x++)
                {
                    texData[y * tw  * 3 + x * 3 + 0] = dis(gen);
                    texData[y * tw  * 3 + x * 3 + 1] = dis(gen);
                    texData[y * tw  * 3 + x * 3 + 2] = ((float)y / (float)th) * 255.0;
                }
            }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
            glBindTexture(GL_TEXTURE_2D, 0);

            // main loop
            while (!glfwWindowShouldClose(window))
            {
                // clear the background to black
                glClearColor(0, 0, 0, 1);
                glClear(GL_COLOR_BUFFER_BIT);

                gla.ortho(0, 800, 600, 0, -1, 1);
                gla.setColor(1.0, 0.5, 0.25);
                gla.circle(400, 300, 100);

                gla.setColor(0.25, 0.5, 1.0);
                gla.rect(50, 50, 100, 100);

                gla.setColor(1.0, 0.0, 0.0);
                gla.line(100, 100, 400, 300);

                //easy way to draw a texture
                gla.setColor(1.0, 1.0, 1.0);
                gla.texture(tex, 400, 200, tw, th);

                //draw a custom shape
                gla.begin(GL_TRIANGLE_FAN);
                gla.setColor(1.0, 1.0, 1.0);
                gla.vertex(100, 200, 0);
                gla.setColor(1.0, 0.0, 0.3);
                gla.vertex(50, 200, 0);
                gla.setColor(1.0, 1.0, 0.3);
                gla.vertex(100, 100, 0);
                gla.setColor(1.0, 0.25, 0.3);
                gla.vertex(150, 200, 0);
                gla.setColor(1.0, 0.25, 1.0);
                gla.vertex(150, 300, 0);
                gla.setColor(0.0, 0.25, 1.0);
                gla.vertex(50, 300, 0);
                gla.setColor(1.0, 0.0, 0.3);
                gla.vertex(50, 200, 0);
                gla.end();

                //draw a four stop gradient
                gla.begin(GL_TRIANGLE_STRIP);
                gla.setColor(1.0, 1.0, 1.0);
                gla.vertex(700, 200, 0);
                gla.vertex(730, 200, 0);
                gla.setColor(1.0, 0.0, 0.0);
                gla.vertex(700, 250, 0);
                gla.vertex(730, 250, 0);
                gla.setColor(1.0, 1.0, 0.0);
                gla.vertex(700, 300, 0);
                gla.vertex(730, 300, 0);
                gla.setColor(0.0, 0.0, 1.0);
                gla.vertex(700, 350, 0);
                gla.vertex(730, 350, 0);
                gla.end();
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
        else
        {
            std::printf("Error: %s\n", gla.error());
        }
    }
    else
    {
        glfwTerminate();
        printf("Could not open GLFW window :(\n");
        return EXIT_FAILURE;
    }

    // clean up glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
