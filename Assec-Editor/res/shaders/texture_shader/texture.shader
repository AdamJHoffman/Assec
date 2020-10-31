vertex:
#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textureCorrd;

out vec2 p_textureCoord;

void main()
{
	p_textureCoord = a_textureCorrd;
	gl_Position = vec4(a_position, 1.0);
}
fragment:
#version 460

in vec2 p_textureCoord;
out vec4 o_color;

uniform sampler2D u_image;

void main()
{
	o_color = texture(u_image, p_textureCoord);
}
