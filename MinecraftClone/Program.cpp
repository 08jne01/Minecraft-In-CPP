#include "Program.h"


Program::Program(int width, int height, std::string s): w(width), h(height), camera(), eventHandler(camera), seed(s)

{

}

int Program::seedToInt(std::string s)

{
	int se = 0;
	for (int i = 0; i < s.length(); i++)

	{
		unsigned char c = s[i];
		se += (int)c;
	}
	return se;
}

int Program::mainLoop()

{

	if (!glfwInit())

	{
		std::cout << "GLFW did not init!" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(w, h, "MinecraftClone", NULL, NULL);

	if (!window)

	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))

	{
		std::cout << "Failed to init GLAD!" << std::endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}

	glViewport(0, 0, w, h);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	glfwSwapInterval(1);

	glClearColor(0.3, 0.80, 0.80, 1.0);
	

	BasicShader vertexShader(GL_VERTEX_SHADER, "Resources/Shaders/BasicVertex.shader");
	BasicShader fragmentShader(GL_FRAGMENT_SHADER, "Resources/Shaders/BasicFrag.shader");

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader.getID());
	glAttachShader(shaderProgram, fragmentShader.getID());
	glLinkProgram(shaderProgram);
	

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	Config config(w, h, 0, 16, 90);

	TextureAtlas textureAtlas;
	textureAtlas.readData("Resources/Database/BlocksTextureMap.dat");
	Renderer renderer(shaderProgram, camera, config);
	World world(16, seedToInt(seed), camera, renderer);
	//world.getChunksShouldLoad();
	//world.loadChunks(renderer);
	//world.loadChunkSingle(renderer, 16 * 8, -1 * 16, 1);
	//world.updateChunks(renderer, 1);
	//world.loadChunkSingle(renderer, 16 * 8, 0 * 16, 1);
	//world.loadChunkSingle(renderer, 16 * 9, 0 * 16, 1);

	//world.loadChunkSingle(renderer, 16 * 16, 0.0);


	//delete &entity;

	Clock clock;
	Clock tickrate;
	int erased = 0;

	while (!glfwWindowShouldClose(window))

	{
		clock.restart();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		

		
		world.getChunksShouldLoad();
		world.updateChunks();
		world.genChunks();
		world.renderChunks();

		camera.update();

		if (tickrate.elapsed().inSeconds() < 10.0 && erased == 0)

		{
			
		}

		else

		{

			//world.cullChunks();
			//world.getChunksShouldUnload();
			
			
		}

		

		glfwSwapBuffers(window);
		glfwPollEvents();
		double val = clock.elapsed().inSeconds();
		//std::cout << "\rFrame rate: " << (int)(1.0 / val) << "             ";
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void Program::framebuffer_size_callback(GLFWwindow* window, int width, int height)

{
	glViewport(0, 0, width, height);
}

void Program::key_callback(GLFWwindow* window, int button, int scancode, int action, int mods)

{
	if (action == GLFW_RELEASE && button == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
	
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);

	kptr->eventHandler.keyHandler(action, button);
}

void Program::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)

{
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);

	kptr->eventHandler.mouseHandler(xpos, ypos);
}