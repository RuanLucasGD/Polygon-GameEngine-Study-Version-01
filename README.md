# Polygon-GameEngine-Study-Version-01
My first game engine 3D i'm developing
A simple 3D game engine made using c++ and OpenGL following tutorials of [Learn OpenGL](https://learnopengl.com/Getting-started/Hello-Triangle) and [Game Programming Patterns](https://gameprogrammingpatterns.com/)

![Screenshot_1](https://user-images.githubusercontent.com/79365912/110024823-f513f880-7d04-11eb-8a38-5525f08e82ad.png)

Used APIs:
* [GLAD](https://glad.dav1d.de/) for load OpenGL 
* [GLM](https://glm.g-truc.net/0.9.9/index.html) Mathematic API for OpenGL
* [GLFW](https://www.glfw.org/) used for create window and manage inputs
* [stb_image](https://github.com/nothings/stb) for load textures

Goals:
- [x] delta time
- [x] scene scripting
- [x] component system
- [x] material scripting
- [x] texture suport
- [ ] import 3D models (.obj)
- [x] point lights
- [x] spot lights
- [x] sun light
- [x] lights specular reflection
- [ ] load and unload scenes
- [x] environment settings
- [ ] ImGui custom editor tools
- [ ] ImGui component editor 
- [ ] file manager 
- [x] global / local moviment
- [x] global / local rotation

Features:
* Scene scripting
  ``` 
  class level_0 : public SceneScripting
  {
  public:
  
    void OnStart()
    {
      // start scene logic
    }
    
    void OnUpdate(float delta)
    {
      // update scene logic
    }
  };
  ```
  * Transformations:
  ```
  void OnStart()
  {
    ...
    player->transform->SetPos(glm::vec3(0, 0, 10);
    player->transform->SetRot(glm::vec3(0, 45, 0);
    ...
  }
  
  void OnUpdate(float delta)
  {
    ...
    player->transform->Move(player->transform->GetForward() * delta * speed);
    ...
  }
  ```
  * Components:
  ```
  void OnStart()
  {
    MeshRenderer* renderer = player->AddComponent<MeshRenderer>();
    renderer->SetMesh(primitives->CUBE);
    renderer->SetMaterial(new SampleMaterial());
  }
  ```
  * Custom Components:
  ```
  class PlayerController : public Component
  {
  public:
    
    float speed = 3.0f;
      
    void OnUpdate(float delta)
    { 
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) transform->Move(transform->GetForward() * delta * speed);
    }
  }
  ```
    
  * Draw Debug Lines:
  ```
  void OnUpdate(float delta)
  {
    glm::vec3 start = glm::vec3();
    glm::vec3 end = glm::vec3(1);
    glm::vec3 color = glm::vec3(1, 0, 0); // red
    gizmos->DrawLine(start, end, color);
  }
  ```
    
  * Custom Materials:
  ```
  class SampleMaterial : public MaterialScripting
  {
   public:
     
    glm::vec3 color = glm::vec3(0.1, 0.1, 1);
      
    void OnStart()
    {
      
      SetShader("shader.vert", "shader.frag");
      Use(); // start shader
        
      SetVec3("color", color);
    }
  }
  ```
  
  * Textures suport:
  ```
  bool useAlfa = true;
  material->SetTexture("texture.png", useAlfa);
  ```
    
  * Lights:
  ```
  void OnStart()
  {
    // suported lights : point and spot
    PointLight* l = AddComponent<PointLight>();
    l->color = glm::vec3(1);
    l->maxDistance = 5;
  }
  ```
    
  Environment:
  ```
  void OnStart()
  {
    scene->environment->backgroundColor = glm::vec3(0.9, 0.9, 1.0);
	  scene->environment->ambientColor = glm::vec3(0.4f);
    scene->sun->color = glm::vec3(1);
    scene->sun->intensity = 1.0f;
    scene->sun->SetRot(glm::vec3(-45, -45, 0));
  }
  ```
  
