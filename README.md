# Horizon
Engine created for programming 4.

## Composition over inheritance

I chose to only inherit once from a base class for my engine, which means no class will have double inheritance. The reason for this was to limit myself because i used inheritance too much in my DAE carreer, when composition was an option.

## Factory

I created a prefab factory that reads in gameObjects, the gameObjects get converted to their respective prefab class if the prefabs are registered in the factory. This makes creating and parsing gameObjects easy. A class needs to contains a gameObject* and a constructor which has a json::value as parameter (ref), this class then needs to be passed in the constructor of the levelReader and potential gameObjects will be converted to the respective prefab class.

## Const correctness

Since i am a big user for const correctness, i tried to make every variable const. I achieved this by using the ? operator. This operator can define if statements in one line. This can make the if statements less readable but variables can be const, which is worth it in my oppinion.

## Math Library

A small basic math library was created for IPoint2 and Rect, this library also has helper functions. I wanted to challenge myself and become accustomed at operator overloading. The math library is used at full effect in the triggerComponent where it checks for overlapping rects and in the movement where it lerp functions are used.

## Engine reusability

Features were added to the engine which were not needed for Qbert but could be usefull for other projects. A fixedUpdate was made which can be usefull for physics if a project would need it. The engine also has lateUpdate and lateInitialize functions which are rarely used in the Qbert project, but are functionable.

