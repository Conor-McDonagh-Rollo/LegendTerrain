#include "../include/Game.h"

Game::Game()
    : engine{ new Engine("LegendTerrain") }
{
}

void Game::run()
{
    window = engine->getWindow();

    double targetFrameTime = 1.0 / 60.0; // 60 FPS
    double lastFrameTime = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // process input as fast as we can
        processInput();

        if (deltaTime < targetFrameTime) {
            processInput();// process input as fast as we can
            update(deltaTime); // Update and render at 60 FPS
            render();
            glfwSwapBuffers(window); // only swap buffers at 60 FPS
        }

    }

    glfwTerminate();
}

void Game::processInput()
{
    glfwPollEvents(); // Poll for key events

    if (glfwGetKey(engine->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(engine->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        left = true;
    }
    else
    {
        left = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        right = true;
    }
    else
    {
        right = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rot_left = true;
    }
    else
    {
        rot_left = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rot_right = true;
    }
    else
    {
        rot_right = false;
    }

}

void Game::update(float dt)
{
    // Gonna update stuff here eventually
    if (right)
    {
        //box.move(10 * dt);
        plane.move(10 * dt);
    }
    if (left)
    {
        //box.move(-10 * dt);
        plane.move(-10 * dt);
    }
    if (rot_right)
    {
        plane.rotate(100 * dt);
    }
    if (rot_left)
    {
        plane.rotate(-100 * dt);
    }
    plane.rotate(100 * dt);
}

void Game::render()
{
    engine->clearScreen(); // Clear screen and be ready for drawing

    // ----------- DRAW OBJECTS -----------

    //box.draw();
    plane.draw();

    // ------------------------------------
}
