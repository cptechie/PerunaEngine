#version 410 core

in vec3 position; // orig attribute vertex set in v. shader
in vec3 normal; // orig attribute vertex normal set in v. shader
in vec4 color; // orig attribute color set in v. shader

out vec4 fragColor;

uniform vec4 lightPos;
uniform vec3 lightInt;
uniform vec3 amb;
uniform vec3 diff;
uniform vec3 spec;
uniform float shin;

vec3 adsModel(){
	vec3 n = normalize(normal);
	vec3 s = normalize(vec3(lightPos)-position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(s, n);

	return lightInt * vec3(amb + diff * vec3(color) * max(dot(s, n), 0.0) + 
		spec * pow( max(dot(r, v), 0.0), shin) );
}

void main(){
	fragColor = vec4(adsModel(), 0.0);
}
