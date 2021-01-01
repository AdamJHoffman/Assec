vertex:
#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_textureCoord;
layout(location = 3) in vec3 a_color;
layout(location = 4) in mat4 a_transform;
layout(location = 8) in float a_texID;
layout(location = 9) in uint a_ID;

out vec2 p_textureCoord;
flat out float p_texID;
flat out uint p_ID;

uniform mat4 u_viewProjection;


void main()
{
	p_textureCoord = a_textureCoord;
	p_texID = a_texID;
	p_ID = uint(a_ID);
	gl_Position = u_viewProjection * a_transform * vec4(a_position, 1.0);
}
fragment:
#version 460

in vec2 p_textureCoord;
flat in float p_texID;
flat in uint p_ID;
layout(location = 0) out vec4 o_color;
layout(location = 1) out uint o_id;

uniform sampler2D u_images[32];

void main()
{
	o_color = texture(u_images[int(p_texID)], p_textureCoord);
	o_id = p_ID;
}
