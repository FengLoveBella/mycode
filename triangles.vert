#version 330 core

layout (location = 0) in vec3 vPosition;
uniform mat4 modelview;
uniform mat4 projection;



out float depth;

void main()
{

	vec4 pos = modelview * vec4(vPosition, 1.0);
	depth = -pos.z;
	gl_Position = projection * pos;
	//gl_Position = vec4(0.1*vPosition.x, 0.1*vPosition.y, 0.1*vPosition.z, 1.0);
	//gl_Position = projection * modelview * vec4(vPosition, 1.0);
	//gl_Position = vec4(vPosition, 1.0);
}
