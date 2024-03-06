# **Magge**
By August Lewén and Mandel Cohen

![](video.gif)


## Project description

Our assignment was to create a simple game using SDL and further develop our skills in C++, Object Oriented Programming and using Design Patterns over a period of 1 - 2 weeks. We chose to re-make the classic arcade game **Space Invaders**, keeping the original look and mechanics, but adding our own twist to it. 

## Cute features we added

* Hand drawn pixel art - Spaceship and Enemies.
* Randomizing the Enemies texture and color when spawning, and the color of the Players projectiles.
* Slight freeze frame when Player takes damage.
* Free sound effects to tie it all togehter.
* Start Screen with credits, Win Screen and Game Over screens with option to "Press R to restart".

## Troubles we encountered

* Weird Player and Enemy movement (Solved by capping frame rate using a timer). Also had some bugs regarding input, like shooting and moving at the same time.
* Library Dependencies (Solved by moving all ```.dll``` files toghether). Setting up all SDL libraries (SDL2, SDL2_IMAGE, SDL2_TTF, SDL2_MIXER) and adding the correct "Environment varaiables" was a bit of a struggle.
* Circular dependencies (Solved by forward declarations and file management). This is by far the most confusing aspect of learning C++. We're still not sure we understand it. 
* Include-explosions (Move definitions to .cpp file). 


## One Class we’re particularly happy about


```
//here is our amazing class
```


## Design Patterns we used
### **Object Pooling**

Our projectiles are only instantiated at the start of the game and added into two Projectile vectors, one for Player Projectiles, and one for the Enemy bombs.
```
std::vector<Projectile*> pooledObjects;

ProjectilePool(int count, int speed, std::string path, int w, int h, bool randomColor, std::vector<GameObject*>* gameObjectList)
{
   this->count = count;
   for (int i = 0; i < count; i++)
   {
       auto* projectile = new Projectile{ speed, path, w, h, randomColor };
       projectile->isActive = false;
       gameObjectList->push_back(projectile);
       pooledObjects.push_back(projectile);
   }
}
```
When shooting projectiles we look for any projectile that is inactive in the pool and place it at the players position and activate it.
Only gameobjects that are active are rendered on the screen.
```
for (Projectile* projectile : projectiles->pooledObjects)
{
	if (!projectile->isActive)
	{
		projectile->isActive = true;
		projectile->Move(mesh.rect.x, mesh.rect.y);
		break;
	}
}
```

### **Update Method** 

All gameobjects run Update function every frame, just like the Update in Unity.
```
for (GameObject* go : gameObjects)
{
   if(go->isActive)
    go->Update();
}
```

Gameobject is a parent class that has a virtual void Update, that the children override for their individual behaviour.
```
virtual void Update(){}
```
Here is an example of the Projectile class Update:
```
virtual void Update() override
{
   if (!isActive)
    return;
   
   if (speed < 0 && mesh.rect.y > Window::SCREEN_HEIGHT || speed > 0 && mesh.rect.y < 0)
    isActive = false;
   
   Move(mesh.rect.x, mesh.rect.y - speed);
}
```

Using the Update Method in this project significantly shortened and cleand up our Main Function. 

## STD Classes we used

### std::vector

We placed all gameobject in a std::vector, we then render all active game objects every frame. Projectiles, Bombs and Enemies are set inactive on collision. The Enemies are erased from the vector on collision, bacause of the random spawning of Bombs at an enemies location. We don't want Bombs to fall from an inactive Enemy. 

Since the order of the gameobjects in this big vector of gameobjects doesn't really matter, we could perhaps have used an unsorted list instead. 

### std::rand

We used a lot of ```rand()``` in our project. We randomize colors on our Projectiles and Enemies, as well as giving the Enemies a random texture when created. We also spawn Bombs from random Enemies, at random intervalls.

We also use ```std::string``` and ```std::array```. 

## Additinal Screenshots
