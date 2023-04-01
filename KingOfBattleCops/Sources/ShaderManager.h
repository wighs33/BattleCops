#pragma once

class ShaderManager {
public:
	char* File_To_Buf(const char* file);
	bool Init_Program();
	void Mapping();

	GLuint Get_Model_Loc() const { return model_loc; }
	GLuint Get_View_Loc() const { return view_loc; }
	GLuint Get_Proj_Loc() const { return proj_loc; }
	GLuint Get_LightAmbient_Loc() const { return lightAmbient_loc; }
	GLuint Get_LightPos_Loc() const { return lightPos_loc; }
	GLuint Get_LightColor_Loc() const { return lightColor_loc; }
	GLuint Get_ObjColor_Loc() const { return objColor_loc; }
	GLuint Get_CameraPos_Loc() const { return cameraPos_loc; }
	GLuint Get_Texture_Loc() const { return texture_loc; }

	GLuint Get_Program_Id() const { return shader_program_ID; }

	GLuint model_loc;
	GLuint view_loc;
	GLuint proj_loc;
	GLuint lightAmbient_loc;
	GLuint lightPos_loc;
	GLuint lightColor_loc;
	GLuint objColor_loc;
	GLuint cameraPos_loc;
	GLuint texture_loc;

	GLuint shader_program_ID;
};