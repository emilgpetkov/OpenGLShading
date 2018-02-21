#version 330 core
out vec4 FragColor;
out vec3 Normal;

in vec3 FragPos;
in vec3 v3Color;
in vec3 v3Normal;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main ()
{
	// ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(v3Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    //vec3 color = vec3(1.0 / norm[0], 1.0 / norm[1], 1.0 / norm[2]);
  //  vec3 result = (ambient + diffuse + specular) * objectColor;
//    FragColor = vec4(result, 1.0);
    //vec3 vColor = dot(norm, lightDir) * lightColor * lightDir;
    FragColor = vec4(v3Color, 0.5);
}


