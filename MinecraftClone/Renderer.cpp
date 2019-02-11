#include "Renderer.h"

Renderer::Renderer(unsigned int sp, Camera& camera, Config& conf):
	shaderProgram(sp), camRef(camera), config(conf)

{
	//glDisable(GL_VSYN)

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Renderer::setShader(unsigned int sp)

{
	shaderProgram = sp;
}

void Renderer::setUniforms(Entity& entity)

{
	int color = glGetUniformLocation(shaderProgram, "u_color");
	glUniform4f(color, 0.2, 0.1, 0.3, 1.0);

	int texF = glGetUniformLocation(shaderProgram, "u_texture");
	glUniform1i(texF, 0);

	int texC = glGetUniformLocation(shaderProgram, "u_cube");
	glUniform1i(texC, 0);

	int proj = glGetUniformLocation(shaderProgram, "projMatrix");
	glm::mat4 projMat = makeProjectionMatrix(config);
	glUniformMatrix4fv(proj, 1, GL_FALSE, &projMat[0][0]);

	int view = glGetUniformLocation(shaderProgram, "viewMatrix");
	glm::mat4 viewMat = makeViewMatrix(camRef);
	glUniformMatrix4fv(view, 1, GL_FALSE, &viewMat[0][0]);

	int model = glGetUniformLocation(shaderProgram, "modelMatrix");
	glm::mat4 modelMat = makeModelMatrix(entity);
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMat[0][0]);

}


