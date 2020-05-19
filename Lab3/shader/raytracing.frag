#version 430

in vec3 interpolated_vertex;
out vec4 FragColor;

struct Camera
{
	vec3 position;
	vec3 view;
	vec3 up;
	vec3 side;
	vec2 scale;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

struct Sphere
{
	vec3 center;
	float radius;
	vec3 color;
};

struct Material
{
	float ambient;
    float diffuse;
    float specular;
    float specularPower;
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
	int materialType;
};
//--------------------------

Sphere sphere = {vec3(-1.0, -1.0, -2.0), 2, vec3(1.0, 0.0, 0.0)};
Material material = {0.4, 0.9, 0.0, 512.0};
vec3 lightPos = vec3(1, 0, -8);

uniform Camera camera;

//--------------------------

bool IntersectSphere(Ray ray, float start, float final, out float time)
{
	ray.origin -= sphere.center;
	float A = dot(ray.direction, ray.direction);
	float B = dot(ray.direction, ray.origin);
	float C = dot(ray.origin, ray.origin) - sphere.radius * sphere.radius;
	float D = B * B - A * C;
	 
	if ( D > 0.0 )
	{
		D = sqrt ( D );
		float t1 = ( -B - D ) / A;
		float t2 = ( -B + D ) / A;
		 
		if ((t1 < 0) && (t2 < 0))
			return false;

		if(min(t1, t2) < 0)
		{
			time = max(t1, t2);
			return true;
		}
	
		time = min(t1, t2);
		return true;
	 }
	 
	 return false;
};

bool Intersect(Ray ray, float start, float final, inout Intersection intersect)
{
	bool result = false;
	float time = start;
	intersect.time = final;

	if (IntersectSphere(ray, start, final, time) && (time < intersect.time))
	{
		intersect.time = time;
		intersect.point = ray.origin + ray.direction * time;
		intersect.normal = normalize(intersect.point - sphere.center);
		intersect.color = sphere.color;
		result = true;
	}

	return result;
};
/*
float Shadow(vec3 posLight, Intersection intersect)
{
    float shadowing = 1.0;
    vec3 direction = normalize(posLight - intersect.point);
    float distanceLight = distance(posLight, intersect.point);
    
    Ray shadowRay = Ray(intersect.point + direction * 0.001, direction);
    Intersection shadowIntersect;
    shadowIntersect.time = 1000000.0;
    
    if(Intersect(shadowRay, sphere, material, 0, distanceLight, shadowIntersect))
        shadowing = 0.0;
    
    return shadowing;
};
*/
vec3 Phong(Intersection intersect)
{
    vec3 light = normalize(lightPos - intersect.point);
    float diffuse = max(dot(light, intersect.normal), 0.0);
    vec3 view = normalize(camera.position - intersect.point);
    vec3 reflected = reflect(-view, intersect.normal);
    float specular = pow(max(dot(reflected, light), 0.0), material.specularPower);
    
    return material.ambient * intersect.color + 
           material.diffuse * diffuse * intersect.color +
           material.specular * specular;
};

Ray GenerateRay(Camera camera)
{
	vec2 coords = interpolated_vertex.xy * camera.scale;
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
};

vec4 Raytrace(Ray primary_ray)
{
	vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
	Ray ray = primary_ray;

	Intersection intersect;
	intersect.time = 1000000.0;
	
	float start = 0;
	float final = 1000000.0;

	if (Intersect(ray, start, final, intersect))
	{
        //float shadowing = Shadow(lightPos, intersect);
		resultColor += vec4(Phong(intersect), 0.0);
	}

	return resultColor;
};

void main (void)
{
	Ray ray = GenerateRay(camera);
    FragColor = Raytrace(ray);
    //FragColor = vec4(abs(ray.direction.xy), 0, 1.0);
};