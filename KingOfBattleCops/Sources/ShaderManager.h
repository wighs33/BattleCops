#pragma once

class ShaderManager {
public:
	char* File_To_Buf(const char* file);
	bool Init_Program();
	void Mapping();

	GLuint model_loc;
	GLuint view_loc;
	GLuint proj_loc;
	GLuint lightAmbi_loc;
	GLuint lightPos_loc;
	GLuint lightColor_loc;
	GLuint objColor_loc;
	GLuint cameraPos_loc;
	GLuint texture_loc;

	GLuint shader_program_ID;
};