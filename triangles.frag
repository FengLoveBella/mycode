#version 330 core

out vec4 vFragColor;

in float depth;


void main()
{

	float d0 = mod(depth, 256.0) / 256.0;

	float d1 = depth/256.0/256.0;

	vFragColor = vec4(d0, d1, 0.0, 1.0);
	//vFragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
